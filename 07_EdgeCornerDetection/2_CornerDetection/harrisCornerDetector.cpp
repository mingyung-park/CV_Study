#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

float thresh = 0.005f;


int main(int argc, char** argv)
{
    // 이미지 읽기 
    Mat img = imread("plant.jpg", IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Image load failed!" << std::endl;
        return -1;
    }

    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);

    // Harris Corner Detection
    Mat dst, dst_norm, dst_norm_scaled;
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.05;

    cornerHarris(img_gray, dst, blockSize, apertureSize, k); //여기서 R 계산
    // threshold 이상인 코너 시각화 (원본에 표시)
    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            if (dst.at<float>(i, j) > thresh) {
                circle(img, Point(j, i), 20, Scalar(255, 0, 0), 1);
            }
        }
    }

    // Harris Response R 시각화를 위한 스케일링, 8U 로 변환
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);

    // 결과 저장 폴더
    std::string output_dir = "./output/";

    imwrite(output_dir + "harris_corner.png", img);
    imwrite(output_dir + "harris_corner_R.png", dst_norm_scaled);

    waitKey();
    return 0;
}