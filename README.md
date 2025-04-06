# Computer Vision & OpenCV 😎

Computer Vision을 공부하면서 정리하고, 구현한 코드를 올립니다.  
학습 내용은 관련 포스팅을 통해 확인할 수 있습니다.

***[🔗 블로그 방문하기](https://he-kate1130.tistory.com/category/%F0%9F%A6%84AI/Computer%20Vision)***
<br>



## Table of Contents

- 🧮 [03. Image Histogram](https://github.com/mingyung-park/CV_Study/tree/main/03_Histogram)
- 🧹 [04. Filtering](https://github.com/mingyung-park/CV_Study/tree/main/04_Filtering)
- 🧼 [05. Image Restoration](https://github.com/mingyung-park/CV_Study/tree/main/05_Resotration)

<br>

> 🚧 *아래 컨텐츠는 재정비 중입니다. 순차적으로 업데이트될 예정입니다* 🚧

- 🔧 **07. Edge & Corner Detection**  
  - `1_EdgeDetection`: 다양한 엣지 검출 알고리즘 (Canny, LoG 등) 
  - `2_CornerDetection`: Harris, Shi-Tomasi 등의 코너 검출 기법 구현 및 정리 

- 🔧 **08. Feature Descriptor**  
  - `1_SIFT`: 이론 설명 및 구현
  - `2_SURF`: 비교 및 응용 사례 추가 예정  
  - ORB, BRIEF 등의 경량 디스크립터도 추후 추가 고려  

- 🔧 **09. Fitting**  
  - `1_RANSAC`: 직선/평면 추정 예제 추가 예정  
  - `2_HoughTransform`: Hough Transform 이론 및 실습 예제 작성 예정  

- 🔧 **10. Deep Learning**  
  - `1_Introduction`: 딥러닝 기초 개념 정리  
  - `2_LossFunction`: CrossEntropy, MSE 등 주요 Loss 함수 소개  
  - `3_Optimization`: SGD, Adam 등 옵티마이저 비교  
  - `4_Regularization`: Dropout, L2 정규화 설명 예정  
  - `5_BackPropagation`: 수식 유도 및 직관적 이해 자료 준비 중  

- 🔧 **11. CNN**  
  - `1_Introduction`: CNN 개요, 특징 맵과 필터 설명  
  - `2_Architectures`: LeNet, AlexNet, VGG, ResNet 등 주요 구조 소개 예정  

- 🔧 **12. Encoder-Decoder**  
  - `1_Introduction`: Encoder-Decoder 기본 구조 및 개념  
  - `2_Architectures`: U-Net, SegNet 등 대표 구조 비교 및 예제 추가 예정  

- 🔧 **13. Project**  
  - 실제 이미지 처리 기반 프로젝트 업로드 예정  
  - Segmentation, Detection 등 Task별 프로젝트 구성 계획 중

<br>

## File Structure
```
📂 CV_Study
├─01_Interpolation
├─02_GeometricTransformation
├─03_Histogram
│  ├─1_Histogram_PDF_CDF
│  ├─2_HistogramStretching
│  ├─3_HistogramEqualization
│  └─4_HistogramMatching
├─04_Filtering
│  ├─GaussianFiltering
│  ├─LaplacianFiltering
│  ├─SobelFiltering
│  ├─Spatial Filtering
│  ├─UniformMeanFiltering
│  └─UnsharpMasking
├─05_Restoration
│  └─images
├─06_Segmentation
│  ├─1_Thresholding
│  ├─2_K-meanClustering
│  └─3_MeanShiftSegmentation
├─07_EdgeCornerDetection
│  ├─1_EdgeDetection
│  └─2_CornerDetection
├─08_FeatureDescriptor
│  ├─1_SIFT
│  └─2_SURF
├─09_Fitting
│  ├─1_RANSAC
│  └─2_HoughTransform
├─10_DeepLearning
│  ├─1_Introduction
│  ├─2_LossFunction
│  ├─3_Optimization
│  ├─4_Regularization
│  └─5_BackPropagation
├─11_CNN
│  ├─1_Introduction
│  └─2_Architectures
├─12_EncoderDecoder
│  ├─1_Introduction
│  └─2_Architectures
└─13_Project
```
<br>
## 🧰 Useful Resources

- [OpenCV 공식 문서 - 4.11.0](https://docs.opencv.org/4.11.0/)
- [Awesome Computer Vision](https://github.com/jbhuang0604/awesome-computer-vision)
