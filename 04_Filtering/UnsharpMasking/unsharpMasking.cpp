#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main() {
	//이미지 파일을 읽어온다.
	Mat img = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (img.empty()) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	// 0. 이미지 정규화: 원활한 unsharp masking을 위해 float형으로 변환
	img.convertTo(img, CV_32F, 1.0 / 255.0);

	// 1. 이미지를 lowpass filter로 처리한다.
	Mat img_blurred;
	GaussianBlur(img, img_blurred, Size(3, 3), 0);

	// 2. scale with k<1
	Mat blurred_scaled;
	float k = 0.75;
	img_blurred.convertTo(blurred_scaled, CV_32F, k);

	// 3. subtract
	Mat img_subtracted;
	subtract(img, blurred_scaled, img_subtracted);

	// 3. scale for display
	Mat img_scaled;
	img_subtracted.convertTo(img_scaled, CV_32F, 1/(1-k));

	// 간단 버전
	Mat simple_blurred;
	GaussianBlur(img, simple_blurred, Size(3, 3), 0);
	Mat simple_unsharp = (img - k * simple_blurred) * (1 / (1 - k));


	//이미지 show
	imshow("Original", img);
	imshow("Blurred", img_blurred);
	imshow("Blurred Scaled", blurred_scaled);
	imshow("Subtracted", img_subtracted);
	imshow("Scaled", img_scaled);
	imshow("Simple Unsharp Masking", simple_unsharp);
	waitKey(0);

	return 0;
}
