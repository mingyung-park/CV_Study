#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat drawHistogram(const Mat& hist, int histSize, int bar_width, int bar_gap, int hist_h, int margin);

int main() {
	Mat img = imread("sunset.jpg", IMREAD_GRAYSCALE);
	if (img.empty()) {
		cout << "Could not open or find the image!" << endl;
		return -1;
	}

	//원본이미지 약간 어둡게 만들기
	Mat dark(img.size(), CV_8UC1, Scalar(0));
	Mat dark_img;
	addWeighted(img, 0.7, dark, 0.2, 0, dark_img);

	// equalization전의 히스토그램 계산하기
	int histSize = 256;
	Mat hist;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	calcHist(&dark_img, 1, 0, Mat(), hist, 1, &histSize, &histRange);

	Mat histImg = drawHistogram(hist, histSize, 1, 2, 500, 60);
	imshow("Image", dark_img);
	imshow("Histogram", histImg);

	// normalize 함수를 통해서 히스토그램 평활화
	Mat equalized_img;
	Mat hist_equalized;
	equalizeHist(dark_img, equalized_img);
	calcHist(&equalized_img, 1, 0, Mat(), hist_equalized, 1, &histSize, &histRange);

	Mat histImg_ = drawHistogram(hist_equalized, histSize, 1, 2, 500, 60);
	imshow("eaulized_Image", equalized_img);
	imshow("equalized_Histogram", histImg_);


	// 변환전 이미지의 CDF 출력
	Mat PDF = hist / (img.rows * img.cols);

	Mat CDF = Mat::zeros(PDF.size(), CV_32F);
	CDF.at<float>(0) = PDF.at<float>(0);
	for (int i = 1; i < PDF.rows; i++) {
		CDF.at<float>(i) = CDF.at<float>(i - 1) + PDF.at<float>(i);
	}
	Mat CDFImg = drawHistogram(CDF, histSize, 1, 2, 500, 60);
	imshow("CDF", CDFImg);

	waitKey(0);

	return 0;
}


Mat drawHistogram(const Mat& hist, int histSize, int bar_width, int bar_gap, int hist_h, int margin)
{
	// 막대 설정
	int total_bar_width = bar_width + bar_gap;
	int hist_w = histSize * total_bar_width;
	Mat histImg(hist_h + 2 * margin, hist_w + 2 * margin, CV_8UC3, Scalar(0, 0, 0));

	// 최대 히스토그램 값 찾기
	double maxVal;
	minMaxLoc(hist, 0, &maxVal);

	// 히스토그램 막대 그리기
	for (int i = 0; i < histSize; i++) {
		rectangle(histImg,
			Point(margin + total_bar_width * i, margin + hist_h),
			Point(margin + total_bar_width * i + bar_width,
				margin + hist_h - cvRound(hist.at<float>(i) * hist_h / maxVal)),
			Scalar(255, 255, 255), FILLED);
	}

	// x축 (밝기값, 50 단위)
	for (int i = 0; i <= histSize; i += 50) {
		putText(histImg, to_string(i), Point(margin - 10 + total_bar_width * i, margin + hist_h + 20),
			FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));
		line(histImg, Point(margin + total_bar_width * i, margin + hist_h),
			Point(margin + total_bar_width * i, margin + hist_h + 5), Scalar(255, 255, 255));
	}

	// y축 (픽셀 개수, 4단계)
	float step_y = hist_h / 4;
	for (int i = 0; i <= hist_h; i += step_y) {
		float value = static_cast<float>(maxVal - maxVal * i / hist_h);
		ostringstream oss;
		oss.precision(2);  // 소수점 두 자리까지
		oss << fixed << value;

		putText(histImg, oss.str(),
			Point(5, margin + i + 5), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));
		line(histImg, Point(margin - 5, margin + i),
			Point(margin, margin + i), Scalar(255, 255, 255));
	}

	// 축 그리기
	line(histImg, Point(margin, margin), Point(margin, margin + hist_h), Scalar(255, 255, 255));
	line(histImg, Point(margin, margin + hist_h), Point(hist_w + margin, margin + hist_h), Scalar(255, 255, 255));

	return histImg;
}