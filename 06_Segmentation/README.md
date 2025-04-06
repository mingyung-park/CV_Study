# 🧩 Image Segmentation

이미지 세그멘테이션은 이미지를 의미 있는 영역으로 나누는 작업입니다.  
Thresholding, K-means Clustering, Mean Shift와 같은 다양한 접근 방식들을 실습과 함께 정리하였습니다.

<br>

## 📂 주요 주제

### 1. Thresholding
- `Simple Thresholding`
- `Otsu’s Method`
- `Adaptive Thresholding`

### 2. Clustering 기반 세그멘테이션
- `K-means Clustering`
- `Mean Shift Algorithm`

<br>

## 📌 결과 미리보기

> **✅ Thresholding 결과**  


| 원본 | Simple Thresholding | Otsu's Method | Adaptive Thresholding |
|:--:|:-------------:|:-------------:|:-------------:|
| ![](images/flower.jpg) | ![](images/output_simple.png) | ![](images/output_otsu.png) | ![](images/output_adaptive.png) |

> **✅ K-means Clustering 결과**  

|원본|K = 10|K = 20|
|:--:|:--:|:--:|
|![](images/flower.jpg) |![](images/output_kmeans_rgbxy_10.png)|![](images/output_kmeans_rgbxy_20.png)|

> **✅ Mean Shift Segmentation 결과**  

|원본|Window size 20|
|:--:|:--:|
|![](images/flower.jpg) |![](images/output_meanshift.png)|

<br>

## 🔗 작성 포스팅

- 🧠 [Segmentation 이론 정리](https://he-kate1130.tistory.com/144)  


<br>

## 📖 참고 자료