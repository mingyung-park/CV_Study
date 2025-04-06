#pragma once
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 이미지를 그레이스케일로 변환
inline Mat convertToGrayscale(const Mat& img) {
    Mat grayImg;
    if (img.channels() == 3)
        cvtColor(img, grayImg, COLOR_BGR2GRAY);
    else
        grayImg = img;
    return grayImg;
}


// 히스토그램 계산
inline vector<Mat> calculateHistogram(const Mat& img) {
    vector<Mat> histograms;

    if (img.channels() == 1) {  // Grayscale Image
        Mat hist;
        int histSize = 256;
        float range[] = { 0, 256 };
        const float* histRange = { range };

        calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, &histRange);
        histograms.push_back(hist);
    }
    else if (img.channels() == 3) {  // Color Image (BGR or RGB)
        vector<Mat> channels;
        split(img, channels);

        int histSize = 256;
        float range[] = { 0, 256 };
        const float* histRange = { range };

        for (int i = 0; i < 3; ++i) {
            Mat hist;
            calcHist(&channels[i], 1, 0, Mat(), hist, 1, &histSize, &histRange);
            histograms.push_back(hist);
        }
    }

    return histograms;
}

// 확률 밀도 함수(PDF) 계산
inline Mat computePDF(const Mat& hist) {
    return hist / sum(hist)[0];
}

// 누적 분포 함수(CDF) 계산
inline Mat computeCDF(const Mat& pdf) {
    Mat cdf = pdf.clone();
    for (int i = 1; i < cdf.rows; ++i) {
        cdf.at<float>(i) += cdf.at<float>(i - 1);
    }
    return cdf;
}

// 매칭을 위한 Lookup Table 생성
inline Mat generateLookupTable(const Mat& sourceCDF, const Mat& referenceCDF) {
    Mat lookupTable(1, 256, CV_8U);
    for (int i = 0; i < 256; ++i) {
        float sourceValue = sourceCDF.at<float>(i);
        uchar matchedValue = 0;
        for (int j = 0; j < 256; ++j) {
            if (referenceCDF.at<float>(j) >= sourceValue) {
                matchedValue = static_cast<uchar>(j);
                break;
            }
        }
        lookupTable.at<uchar>(i) = matchedValue;
    }
    return lookupTable;
}

// Lookup Table 적용
inline Mat applyLookupTable(const Mat& img, const Mat& lookupTable) {
    Mat result;
    LUT(img, lookupTable, result);
    return result;
}

// 히스토그램 매칭inline Mat histogramMatching
inline Mat histogramMatching(
    const Mat& src,
    const Mat& ref,
    vector<Mat>& hist_src,
    vector<Mat>& hist_dst,
    vector<Mat>& hist_result,
    bool Color = false)
{
    if (src.channels() == 3 && Color) {// 컬러 이미지 처리 (YUV 변환 후 Y 채널 매칭)
        Mat srcYUV, refYUV;
        cvtColor(src, srcYUV, COLOR_BGR2YUV);
        cvtColor(ref, refYUV, COLOR_BGR2YUV);
        
        // 채널 분리
        vector<Mat> srcChannels, refChannels;
        split(srcYUV, srcChannels);
        split(refYUV, refChannels);

        // Y 채널의 히스토그램 계산
        hist_src = calculateHistogram(srcChannels[0]);
        hist_dst = calculateHistogram(refChannels[0]);

        // PDF 및 CDF 계산
        Mat pdf_src = computePDF(hist_src[0]);
        Mat pdf_dst = computePDF(hist_dst[0]);

        Mat cdf_src = computeCDF(pdf_src);
        Mat cdf_dst = computeCDF(pdf_dst);

        // Lookup Table 생성 및 적용
        Mat lookupTable = generateLookupTable(cdf_src, cdf_dst);
        srcChannels[0] = applyLookupTable(srcChannels[0], lookupTable);

        // 매칭된 이미지 병합 및 색상 복원
        Mat matchedYUV, result;
        merge(srcChannels, matchedYUV);
        cvtColor(matchedYUV, result, COLOR_YUV2BGR);

        // 매칭된 이미지의 Y 채널 히스토그램 계산
        hist_result = calculateHistogram(srcChannels[0]);

        return result;
    }
    else {  // 그레이스케일 이미지 처리
        Mat srcGray = convertToGrayscale(src);
        Mat refGray = convertToGrayscale(ref);

        hist_src = calculateHistogram(srcGray);
        hist_dst = calculateHistogram(refGray);

        Mat pdf_src = computePDF(hist_src[0]);
        Mat pdf_dst = computePDF(hist_dst[0]);

        Mat cdf_src = computeCDF(pdf_src);
        Mat cdf_dst = computeCDF(pdf_dst);

        Mat lookupTable = generateLookupTable(cdf_src, cdf_dst);

        Mat result = applyLookupTable(srcGray, lookupTable);

        hist_result = calculateHistogram(result);

        return result;
    }
}


// 히스토그램 이미지로 그리기
inline Mat drawHistogram(
    const vector<Mat>& hists,  // 히스토그램 목록 (Y, BGR or YUV)
    int histSize = 256,
    int hist_w = 512,
    int hist_h = 500,
    int margin = 60) {

    Mat histImg(hist_h + 2 * margin, hist_w + 2 * margin, CV_8UC3, Scalar(0, 0, 0));
    Scalar colors[3] = { Scalar(255, 255, 255), Scalar(0, 255, 0), Scalar(0, 0, 255) };  // B, G, R or Y, U, V
    int channelCount = hists.size();

    for (int ch = 0; ch < channelCount; ++ch) {
        Mat hist = hists[ch];

        // 정규화하여 최대값을 hist_h에 맞춤
        normalize(hist, hist, 0, hist_h, NORM_MINMAX);

        for (int i = 1; i < histSize; ++i) {
            line(histImg,
                Point(margin + (i - 1) * (hist_w / histSize), margin + hist_h - cvRound(hist.at<float>(i - 1))),
                Point(margin + i * (hist_w / histSize), margin + hist_h - cvRound(hist.at<float>(i))),
                colors[ch % 3], 1);  // 선으로 표시
        }
    }

    // 축 그리기
    line(histImg, Point(margin - 2, margin), Point(margin - 2, margin + hist_h+2), Scalar(255, 255, 255)); // Y��
    line(histImg, Point(margin - 2, margin + hist_h+2), Point(margin + hist_w, margin + hist_h+2), Scalar(255, 255, 255)); // X��

    return histImg;
}

#endif // HISTOGRAM_H