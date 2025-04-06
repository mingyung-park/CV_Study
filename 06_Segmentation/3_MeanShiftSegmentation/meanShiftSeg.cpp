#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 이미지 로드
    Mat src = imread("flower.jpg");
    if (src.empty()) {
        cerr << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    // Mean Shift Filtering
    Mat result;
    pyrMeanShiftFiltering(src, result, 20, 20); // sp=20, sr=20

    // 결과 저장
    imwrite("output_meanshift.png", result);
    cout << "Mean Shift Filtering 완료" << endl;

    return 0;
}
