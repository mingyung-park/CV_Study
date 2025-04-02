#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstring>

using namespace cv;
using namespace std;

#define IM_TYPE CV_8UC1  //기본 8bit grayscale

#if (IM_TYPE == CV_8UC1)
typedef uchar G;
#elif (IM_TYPE == CV_16UC1)
typedef ushort G;
#elif (IM_TYPE == CV_32FC1)
typedef float G;
#endif
// =======================================
// 필터 함수 선언
// =======================================

// Uniform Mean Filter 구현. Separable Filter로 만든다.
Mat UniformMeanFilter(const Mat input, int nx, int ny, const char* opt) {
    int row = input.rows;
    int col = input.cols;

    int kernel_x = 2 * nx + 1;
    int kernel_y = 2 * ny + 1;
    float kx = 1.0f / kernel_x;
    float ky = 1.0f / kernel_y;

    Mat temp = Mat::zeros(row, col, input.type());   // 가로 필터링 결과
    Mat output = Mat::zeros(row, col, input.type()); // 세로 필터링 결과

    // --- Pass 1: 가로 방향 필터링 ---
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            float sum = 0.0f;
            float weight = 0.0f;

            for (int b = -nx; b <= nx; b++) {
                int jj = j + b;

                if (!strcmp(opt, "zero-paddle")) {
                    if (jj >= 0 && jj < col)
                        sum += kx * (float)input.at<G>(i, jj);
                }
                else if (!strcmp(opt, "mirroring")) {
                    if (jj < 0) jj = -jj;
                    else if (jj >= col) jj = 2 * col - jj - 2;
                    sum += kx * (float)input.at<G>(i, jj);
                }
                else if (!strcmp(opt, "adjustkernel")) {
                    if (jj >= 0 && jj < col) {
                        sum += kx * (float)input.at<G>(i, jj);
                        weight += kx;
                    }
                }
            }

            if (!strcmp(opt, "adjustkernel") && weight != 0)
                temp.at<G>(i, j) = (G)(sum / weight);
            else
                temp.at<G>(i, j) = (G)(sum);
        }
    }

    // --- Pass 2: 세로 방향 필터링 ---
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            float sum = 0.0f;
            float weight = 0.0f;

            for (int a = -ny; a <= ny; a++) {
                int ii = i + a;

                if (!strcmp(opt, "zero-paddle")) {
                    if (ii >= 0 && ii < row)
                        sum += ky * (float)temp.at<G>(ii, j);
                }
                else if (!strcmp(opt, "mirroring")) {
                    if (ii < 0) ii = -ii;
                    else if (ii >= row) ii = 2 * row - ii - 2;
                    sum += ky * (float)temp.at<G>(ii, j);
                }
                else if (!strcmp(opt, "adjustkernel")) {
                    if (ii >= 0 && ii < row) {
                        sum += ky * (float)temp.at<G>(ii, j);
                        weight += ky;
                    }
                }
            }

            if (!strcmp(opt, "adjustkernel") && weight != 0)
                output.at<G>(i, j) = (G)(sum / weight);
            else
                output.at<G>(i, j) = (G)(sum);
        }
    }

    return output;
}
