#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


int main(int argc, const char* argv[])
{
    // 이미지 읽기 
    Mat img_1 = imread("peters_1.jpg", IMREAD_COLOR);
    if (img_1.empty()) {
        std::cerr << "Image load failed!" << std::endl;
        return -1;
    }
    Mat img_2 = imread("peters_2.jpg", IMREAD_COLOR);
    if (img_2.empty()) {
        std::cerr << "Image load failed!" << std::endl;
        return -1;
    }

    //-- Step 1: Detect the keypoints
    Ptr<SIFT> detector = SIFT::create(500);

    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    detector->detectAndCompute(img_1, noArray(), keypoints1, descriptors1);
    detector->detectAndCompute(img_2, noArray(), keypoints2, descriptors2);

    //-- Step 2: Matching descriptor vectors with a brute force matcher
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    std::vector< DMatch > matches;
    matcher->match(descriptors1, descriptors2, matches);

    //-- Step 2: Matching descriptor vectors with a FLAN
    Ptr<DescriptorMatcher> matcher2 = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<DMatch> > knn_matches;
    matcher2->knnMatch(descriptors1, descriptors2, knn_matches, 2);
    const float ratio_thresh = 0.8f;
    std::vector<DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++)
    {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
        {
            good_matches.push_back(knn_matches[i][0]);
        }
    }

    //-- Draw keypoints
    Mat img_keypoints_1, img_keypoints_2, img_gray_1, img_gray_2;
    cvtColor(img_1, img_gray_1, COLOR_BGR2GRAY);
    cvtColor(img_2, img_gray_2, COLOR_BGR2GRAY);
    drawKeypoints(img_gray_1, keypoints1, img_keypoints_1);
    drawKeypoints(img_gray_2, keypoints2, img_keypoints_2);

    //-- Draw matches
    Mat img_matches, img_matches_2;
    drawMatches(img_1, keypoints1, img_2, keypoints2, matches, img_matches);
    drawMatches(img_1, keypoints1, img_2, keypoints2, good_matches, img_matches_2, Scalar::all(-1),
        Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    //-- Show detected matches
    imshow("Matches", img_matches);
    imshow("Good Matches", img_matches_2);

    // 결과 저장 폴더
    std::string output_dir = "./output/";
    imwrite(output_dir + "sift_keypoint_1.png", img_keypoints_1);
    imwrite(output_dir + "sift_keypoint_2.png", img_keypoints_2);
    imwrite(output_dir + "sift_matching.png", img_matches);
    imwrite(output_dir + "sift_matching_flan.png", img_matches_2);


    waitKey();
    return 0;
}
