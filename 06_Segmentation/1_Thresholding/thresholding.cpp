#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    // 이미지 로드
    Mat src = imread("flower.jpg", IMREAD_GRAYSCALE);
    if (src.empty()) {
        cerr << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    Mat binary;

    // 1. Simple Thresholding
    threshold(src, binary, 128, 255, THRESH_BINARY);
    imwrite("output_simple.png", binary);

    // 2. Otsu's Method (자동 임계값 계산)
    threshold(src, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    imwrite("output_otsu.png", binary);

    // 3. Adaptive Thresholding
    adaptiveThreshold(src, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 5);
    imwrite("output_adaptive.png", binary);

    return 0;
}
