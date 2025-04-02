#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 직접 구현한 필터 함수 포함된 헤더
#include "meanfilter.h"

int main() {
    Mat src = imread("lena.jpg", IMREAD_GRAYSCALE);
    if (src.empty()) {
        cout << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    int nx = 3;  // 가로 방향 절반 크기 → 전체 커널 크기: 7
    int ny = 3;  // 세로 방향 절반 크기 → 전체 커널 크기: 7

    // 직접 구현한 필터 (zero-padding 방식), separable filter구현
    Mat custom_filtered = UniformMeanFilter(src, nx, ny, "zero-paddle");
    
    // OpenCV sepFilter2D 사용, separable filter
    int kernel_x = 2 * nx + 1;
    int kernel_y = 2 * ny + 1;
    Mat kernelX = Mat::ones(1, kernel_x, CV_32F) / static_cast<float>(kernel_x);
    Mat kernelY = Mat::ones(kernel_y, 1, CV_32F) / static_cast<float>(kernel_y);

    Mat sep_filtered;
    sepFilter2D(src, sep_filtered, -1, kernelX, kernelY, Point(-1, -1), 0, BORDER_CONSTANT);

    // OpenCV boxFilter 사용
    Mat box_filtered;
    boxFilter(src, box_filtered, -1, Size(kernel_x, kernel_y), Point(-1, -1), true, BORDER_CONSTANT);

    // OpenCV blur 사용
    Mat blur_filtered;
    blur(src, blur_filtered, Size(kernel_x, kernel_y));

    
    // 결과 출력
    imshow("Original", src);
    imshow("Custom Uniform Mean Filter", custom_filtered);
    imshow("OpenCV sepFilter2D", sep_filtered);
    imshow("OpenCV boxFilter", box_filtered);
    imshow("OpenCV blur", blur_filtered);


    waitKey(0);

    return 0;
}
