#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>

using namespace std;

// Gaussian Noise 추가 함수
void addGaussianNoise(cv::Mat& image, double mean = 0.0, double stddev = 20.0) {
    cv::Mat noise(image.size(), CV_32FC1);
    cv::randn(noise, mean, stddev); // 평균, 표준편차

    cv::Mat image32f;
    image.convertTo(image32f, CV_32FC1); // float 변환
    image32f += noise;

    cv::Mat noisyImage;
    cv::normalize(image32f, image32f, 0, 255, cv::NORM_MINMAX); // 값 범위 정규화
    image32f.convertTo(noisyImage, CV_8UC1); // 다시 uchar로

    image = noisyImage.clone();
}

// 메인 함수
int main() {
    // 그레이스케일 이미지 로드
    cv::Mat img = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    // 원본 복사 후 Gaussian 노이즈 추가
    cv::Mat noisy = img.clone();
    addGaussianNoise(noisy);

    // 설정값 (공간 시그마)
    int kernelSize = 5;         // Gaussian 커널 크기 (홀수)
    double sigmaSpace = 2.0;    // 공간 시그마 (두 필터에 동일 적용)
    double sigmaColor = 75.0;   // Bilateral 필터의 밝기 시그마


    // Gaussian 필터 적용
    cv::Mat gaussianFiltered;
    cv::GaussianBlur(noisy, gaussianFiltered, cv::Size(kernelSize, kernelSize), sigmaSpace);

    // Bilateral 필터 적용
    cv::Mat bilateralFiltered;
    cv::bilateralFilter(noisy, bilateralFiltered, kernelSize, sigmaColor, sigmaSpace);

    // 결과 출력
    cv::imshow("Original", img);
    cv::imshow("Gaussian Noise", noisy);
    cv::imshow("Gaussian Filter", gaussianFiltered);
    cv::imshow("Bilateral Filter", bilateralFiltered);

    cv::waitKey(0);
    return 0;
}
