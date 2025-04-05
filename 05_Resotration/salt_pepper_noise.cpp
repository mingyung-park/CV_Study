#include <opencv2/opencv.hpp>
#include <iostream>
#include <random>
#include <numeric>

using namespace cv;
using namespace std;


// Salt and Pepper Noise 추가
void addSaltAndPepperNoise(cv::Mat& image, double amount) {
    srand(42); // 고정 시드

    //전체 픽셀수를 고려해서 amount만큼의 노이즈 추가
    int totalPixels = image.rows * image.cols;
    int numSalt = static_cast<int>(amount / 2 * totalPixels);
    int numPepper = static_cast<int>(amount / 2 * totalPixels);

	// Salt 노이즈 추가
    for (int i = 0; i < numSalt; ++i) {
        int y = rand() % image.rows;
        int x = rand() % image.cols;
        image.at<uchar>(y, x) = 255; // salt
    }

	// Pepper 노이즈 추가
    for (int i = 0; i < numPepper; ++i) {
        int y = rand() % image.rows;
        int x = rand() % image.cols;
        image.at<uchar>(y, x) = 0; // pepper
    }
}

// Gaussian 필터링 (평균 필터보다 더 부드럽게 처리됨)
Mat averageFilter(const Mat& input, int ksize) {
    Mat output;
    // sigmaX는 자동 추정된다. ksize는 홀수여야 함
    GaussianBlur(input, output, Size(ksize, ksize), 0);
    return output;
}

// 중앙값 필터링 (Rank-order 필터의 대표적인 예)
Mat medianFilter(const Mat& input, int ksize) {
    Mat output;
    medianBlur(input, output, ksize); // ksize는 홀수만 가능
    return output;
}
// Outlier Rejection 필터링
Mat outlierRejectionFilter(const Mat& input, int ksize, int threshold = 35) {
    Mat output = input.clone();
    int half = ksize / 2;

    for (int y = half; y < input.rows - half; ++y) {
        for (int x = half; x < input.cols - half; ++x) {
            std::vector<uchar> neighbors;
            for (int j = -half; j <= half; ++j) {
                for (int i = -half; i <= half; ++i) {
                    if (i == 0 && j == 0) continue; // center 제외
                    neighbors.push_back(input.at<uchar>(y + j, x + i));
                }
            }
            double mean = accumulate(neighbors.begin(), neighbors.end(), 0.0) / neighbors.size();
            uchar center = input.at<uchar>(y, x);
            if (abs(center - mean) > threshold) {
                output.at<uchar>(y, x) = static_cast<uchar>(mean);
            }
        }
    }

    return output;
}

int main() {
    // 그레이스케일 이미지 로드
    cv::Mat img = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "이미지를 불러올 수 없습니다." << std::endl;
        return -1;
    }

    // 노이즈 추가
    Mat noisy = img.clone();
    addSaltAndPepperNoise(noisy, 0.10); // 10% 노이즈

    // 필터링
    Mat avgFiltered = averageFilter(noisy, 3);
    Mat medFiltered = medianFilter(noisy, 3);
    Mat outlierFiltered = outlierRejectionFilter(noisy, 3);

    // 결과 출력
    imshow("Original", img);
    imshow("Noisy", noisy);
    imshow("Average Filter", avgFiltered);
    imshow("Median Filter", medFiltered);
    imshow("Outlier Rejection", outlierFiltered);
    waitKey(0);

    return 0;
}
