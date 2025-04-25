#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

Mat computeZeroCrossing(const Mat& laplacian, double threshold = 0.0) {
    CV_Assert(laplacian.type() == CV_64F);  // 반드시 double

    Mat edge = Mat::zeros(laplacian.size(), CV_8U);

    for (int y = 1; y < laplacian.rows - 1; ++y) {
        for (int x = 1; x < laplacian.cols - 1; ++x) {
            double center = laplacian.at<double>(y, x);

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dy == 0 && dx == 0) continue;

                    double neighbor = laplacian.at<double>(y + dy, x + dx);
                    if (center * neighbor < 0 && std::abs(center - neighbor) > threshold) {
                        edge.at<uchar>(y, x) = 255;
                        goto next_pixel;
                    }
                }
            }
        next_pixel:;
        }
    }

    return edge;
}

int main() {
    // 이미지 읽기 (Grayscale)
    Mat img = imread("bridge.jpg", IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Image load failed!" << std::endl;
        return -1;
    }

    // 결과 저장 폴더
    std::string output_dir = "./output/";

    imwrite(output_dir + "original.png", img);

    //---------------------------
    // Laplacian of Gaussian (LoG)
    //---------------------------
    Mat blurred, log1,log2, zc_log1,zc_log2;

    // Gaussian Blur
    GaussianBlur(img, blurred, Size(5, 5), 1.0);

    // Laplacian
    Laplacian(blurred, log1, CV_64F);
    Laplacian(img, log2, CV_64F);

	// LoG (Laplacian of Gaussian) - Zerocrossing으로 threshold 이상 차이나는 경우 edge검출
    zc_log1 = computeZeroCrossing(log1, 20.0);
    zc_log2 = computeZeroCrossing(log2, 20.0);

    // 타입 변환 -> CV_8U
    convertScaleAbs(log1, log1);
    convertScaleAbs(log2, log2);

    // 저장
    imwrite(output_dir + "gaussian_blur.png", blurred);
    imwrite(output_dir + "log.png", log1);
    imwrite(output_dir + "log_zc.png", zc_log1);
    imwrite(output_dir + "wo_blur_log.png", log2);
    imwrite(output_dir + "wo_zc_log.png", zc_log2);

    std::cout << "All processing done. Check output folder." << std::endl;
    return 0;
}
