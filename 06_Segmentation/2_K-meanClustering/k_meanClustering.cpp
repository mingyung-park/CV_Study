#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("flower.jpg");
    if (src.empty()) {
        cerr << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    int rows = src.rows;
    int cols = src.cols;

    // (rows * cols) x 5 행렬 만들기 (R, G, B, x, y)
    Mat data(rows * cols, 5, CV_32F);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Vec3b color = src.at<Vec3b>(y, x);
            int idx = y * cols + x;
            data.at<float>(idx, 0) = static_cast<float>(color[0]); // B
            data.at<float>(idx, 1) = static_cast<float>(color[1]); // G
            data.at<float>(idx, 2) = static_cast<float>(color[2]); // R
            data.at<float>(idx, 3) = static_cast<float>(x);        // X
            data.at<float>(idx, 4) = static_cast<float>(y);        // Y
        }
    }

    // K-means 파라미터
    int K = 10;
    Mat labels, centers;
    TermCriteria criteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0);
    kmeans(data, K, labels, criteria, 5, KMEANS_PP_CENTERS, centers);

    // 결과 재구성 (색상만 이용)
    Mat segmented(rows, cols, CV_8UC3);
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            int idx = y * cols + x;
            int label = labels.at<int>(idx);
            Vec3b color;
            color[0] = static_cast<uchar>(centers.at<float>(label, 0)); // B
            color[1] = static_cast<uchar>(centers.at<float>(label, 1)); // G
            color[2] = static_cast<uchar>(centers.at<float>(label, 2)); // R
            segmented.at<Vec3b>(y, x) = color;
        }
    }

    imwrite("output_kmeans_rgbxy_10.png", segmented);
    cout << "K - means(RGB + XY) segmentation 완료" << endl;

    return 0;
}
