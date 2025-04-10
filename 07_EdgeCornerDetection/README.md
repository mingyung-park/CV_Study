# 📐 Edge & Corner Detection
이미지 처리 및 컴퓨터 비전에서 **Edge Detection(에지 검출)**과 **Corner Detection(코너 검출)**은 물체의 형태와 구조를 인식하는 데 핵심적인 기법입니다.

에지는 이미지 내에서 픽셀 값이 급격하게 변하는 부분으로, 객체의 경계나 윤곽선을 나타냅니다. 이러한 에지를 검출함으로써 우리는 물체의 위치나 형상을 파악할 수 있습니다.

코너는 에지보다 더욱 국소적인 특징으로, 두 개 이상의 에지가 만나는 지점에서 나타납니다. 코너는 위치 변화에 민감하지 않으면서도 명확한 위치 정보를 제공하기 때문에, 이미지 정합(image matching), 트래킹(tracking), 3D 재구성 등 다양한 응용에서 중요한 역할을 합니다.

이 디렉토리에서는 대표적인 에지 검출 기법들과 해리스 코너 검출 알고리즘에 대해 살펴보고, 각 방법에 따른 결과 차이를 함께 살펴보도록 하겠습니다.


<br>

## 📂 주요 주제

### 1. Edge Detection
- `Smoothing & Edge Tradeoff`
- `Sobel Filter`
- `Laplacian Filter`
- `Laplacian of Gaussian Filter (LoG)`
- `Canny Edge Detection`

### 2. Corner Detection 
- `Harris Corner Detection`

<br>

## 📌 결과 미리보기

> **Edge Detection - 1. Smoothing & Edge Tradeoff 결과**
<br>
kernel size 커질 수록 edge가 blurred된다. (localization 문제)

|kernel size = 1|kernel size = 1|kernel size = 1|kernel size = 1|
|:--:|:--:|:--:|:--:|
|![](images/edge_blur_ksize_1.png)|![](images/edge_blur_ksize_3.png)|![](images/edge_blur_ksize_5.png)|![](images/edge_blur_ksize_9.png)|


<br>

## 🔗 작성 포스팅

- 📐 [**Image Detection과 Edge-Smoothing Tradeoff에 대해서 알아보자**](https://he-kate1130.tistory.com/145)


<br>

## 📖 참고 자료

