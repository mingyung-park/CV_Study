#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

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
    // Sobel Filtering
    //---------------------------
    Mat sobelx, sobely, sobel_magnitude;

    Sobel(img, sobelx, CV_64F, 1, 0, 3);
    Sobel(img, sobely, CV_64F, 0, 1, 3);

    // Magnitude 계산
    magnitude(sobelx, sobely, sobel_magnitude);

    //// 타입 변환 8U
    convertScaleAbs(sobelx, sobelx);
    convertScaleAbs(sobely, sobely);
    convertScaleAbs(sobel_magnitude, sobel_magnitude);

    // 저장
    imwrite(output_dir + "sobel_x.png", sobelx);
    imwrite(output_dir + "sobel_y.png", sobely);
    imwrite(output_dir + "sobel_magnitude.png", sobel_magnitude);

    std::cout << "All processing done. Check output folder." << std::endl;
    return 0;
}
