#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 불러오기 (Grayscale)
    cv::Mat img = cv::imread("flower.jpg", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "이미지를 불러올 수 없습니다.\n";
        return -1;
    }

    // Gaussian kernel size
    std::vector<int> kernel_sizes = { 1, 3, 5, 9 };

    for (int ksize : kernel_sizes) {
        cv::Mat blurred, grad_x, grad_y, grad, abs_grad_x, abs_grad_y;

        // Gaussian Blur
        if (ksize > 1) {
            cv::GaussianBlur(img, blurred, cv::Size(ksize, ksize), 0);
        }
        else {
            blurred = img.clone(); // ksize == 1이면 blur 없이 원본 사용
        }

        // Sobel 필터 적용 (X, Y 방향)
        cv::Sobel(blurred, grad_x, CV_16S, 1, 0, 3);
        cv::Sobel(blurred, grad_y, CV_16S, 0, 1, 3);

        // 절댓값 및 합성
        cv::convertScaleAbs(grad_x, abs_grad_x);
        cv::convertScaleAbs(grad_y, abs_grad_y);
        cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

        // 결과 이미지 저장
        std::string filename = "edge_blur_ksize_" + std::to_string(ksize) + ".png";
        cv::imwrite(filename, grad);
        std::cout << "저장 완료: " << filename << std::endl;
    }

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
