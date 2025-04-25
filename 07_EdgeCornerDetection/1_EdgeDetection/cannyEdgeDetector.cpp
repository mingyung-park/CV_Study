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

    Mat canny_edges;
    Canny(img, canny_edges, 100, 200);

    imwrite(output_dir + "canny.png", canny_edges);

    std::cout << "All processing done. Check output folder." << std::endl;
    return 0;
}
