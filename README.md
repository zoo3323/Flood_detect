## 딥러닝 캡스톤 디자인 프로젝트<br/>[230927 ~ 231210]
_**딥러닝 기반 건물 침수 대응 프로그램**_

## 팀원
김남주 박수영 안중보

## 목적
기후변화로 인한 물 관련 재해가 최근 많이 늘어나고 있습니다.<br/>
cctv를 통해 주변 지역의 침수를 감지하면 건물 내의 인원들에게 경보를 울리고 치수막을 올려<br/> 침수에 대응할 수 있도록 하는 프로젝트를 만들었습니다. 

## 과제 세부 내용
1. 크롤링과 kaggle에서 이미지 데이터셋 수집
2. 이미지 전처리
3. Transfer Learning & Fine tuning ResNet50
4. Resnet50 Fine tuning을 적용
5. 오작동 방지를 위한 기상청 날씨 크롤링
6. 웹캠을 사용하여 실시간 이미지 분석<br/>
   

- 하드웨어 : 아두이노 우노, 서보모터, 피에조부저, GPU가 있는 PC
- 소프트웨어 : Arduino IDE, Python
- 과제 설계목표
  - 실시간 강수량을 받아올 수 있도록 함.
  - 침수, 비, 이상없음 3개의 클래스로 분류하도록 함.
  - 아두이노를 사용해 실제로 차수막이 올라가도록 함.<br/><br/>
 
  

> 모델 학습 부분은 [Image_classification_pipeline_Project](https://github.com/inhovation97/Image_classification_pipeline_Project.git)의 소스코드를 수정하여 사용하였습니다.

## 제작 과정
|구분|내용|
|:-----:|---|
|데이터셋 수집|1. 구글 이미지 크롤링으로 이미지들을 수집<br/> 2. Kaggle에서 Flood 이미지 추가 수집|
|이미지 전처리|1. 이미지 사이즈가 달라 resize 진행<br/> 2. 정확도를 높이기 위해 albumentations로 Image augmentation 진행<br/> 3. 모델을 학습시키기 위해 텐서 형태로 변환|
|모델 학습|1. 중간과정 fc layer를 선행학습<br/>2. 사전 학습한 fc layer를 연결하여 transfer learning 진행<br/>3. 100 epochs 로 학습|
|하드웨어 적용|1. 파이썬과 아두이노 시리얼 통신 연결<br/>2. 경고 신호를 보내면 피에조부저에서 신호 발생<br/>3. 차수막 신호를 보내면 서보모터 작동으로 차수막 가동<br/>4. 사용자가 버튼을 눌러 차수막 내림|

### 데이터셋 수집
이미지 검수 후 학습할 최종 데이터
Flood Image : 1089
Not Flood Image : 1004
Rainy Image : 979
각각8:2의 비율로 나누어 train, test set을 나누었다.

### 이미지 전처리
직접 수집한 이미지들에 모델이 학습을 더 잘 하기 위해서 여러 전처리를 진행했다.
1. 이미지 사이즈가 모두 달라 resize 진행<br/>

![전처리1](https://github.com/zoo3323/Flood_detect/assets/95582592/f8896e79-2d22-4958-8f8e-af4d03d77323)

2. albumentations로 Image augmentation를 하였다.

<pre>
<code>
transforms.Resize((128, 128)), # 이미지 resize
transforms.RandomCrop(124), # 이미지를 랜덤으로 크롭
transforms.ColorJitter(brightness=0.2, contrast=0.2, saturation=0.2, hue=0.2), # 이미지 지터링(밝기, 대조, 채비, 색조)
transforms.RandomHorizontalFlip(p = 1), # p확률로 이미지 좌우반전
transforms.RandomVerticalFlip(p = 1), # p확률로 상하반전
</code>
</pre>

![전처리2](https://github.com/zoo3323/Flood_detect/assets/95582592/b0591900-e1e9-45c5-8fae-674958a165b4)

## 결과
fine tuning 을 하여 성능을 높였다.
Data의 양이 적어 transfer learning을 하였다.
100epoch로 학습결과 86%의 정확도가 나왔다.
> rainy 데이터셋의 우산이 나온 사진이 많아 정확도가 떨어지는 것으로 예상

![정확도와로스](https://github.com/zoo3323/Flood_detect/assets/95582592/0097780b-0abc-428f-b4fd-77238c00b1c0)

<br/>

- 프로그램 순서도
1. 입력한 도시의 강수량이 시간당 30mm 이상일 때 침수 이미지 판별을 시작한다.
2. 웹캠에서 1초마다 이미지를 캡쳐해 인식시킨다.
3. 침수된 이미지로 판단하면 Flood count에 
  1을 더해준다.
4. 비가 오거나 침수가 아닌 이미지를 인식하면 Flood count에 –3을 한다.
5. Flood count가 10 이상이면 경보
6. Flood count가 20 이상이면 차수막을 올린다.
7. 사용자가 차수막을 내리기 전까지 작동한다.

> - flood count 사용 이유
> Flood count를 사용하여 모델이 잘못 인식했을 때 차수막이 바로 작동되는 오작동을 줄이기 위해 차수막 작동까지 20초의 count를 주었다.

<img src="https://github.com/zoo3323/Flood_detect/assets/95582592/946c611a-f84d-4a80-9ffe-1c852c6b7f1d" width="500" height="500">

## 결과물 형태
1. 오작동 방지를 위해 도시를 입력받고 기상청 날씨누리 홈페이지에서 실시간 강수량을 측정해 시간당 강수량이 30mm 이상일 때부터 비, 침수를 감지한다.

> - 강수량 30mm 이상 설정 이유 <br/>
>손해보험업계에 따르면 현대해상 교통기후환경연구소가 2006년부터 2012년까지 7년간 서울 강남구에서 발생한 차량 침수 사고를 분석했더니 차량 침수 사고의 56.3%가 시간당 강수량 35㎜ 이상일 때 일어났다.
>특히, 시간당 강수량이 55~60㎜ 일 때 침수 사고 확률이 가장 높았다.
![기상청](https://github.com/zoo3323/Flood_detect/assets/95582592/8aa65e37-e7d5-445e-9aa6-905cff5f46f7)

3. 침수가 아닌 이미지를 감지하면 이상없음을 출력한다.
![이상없음](https://github.com/zoo3323/Flood_detect/assets/95582592/14132ef7-4853-4297-909b-778b71a349cf)

4. 비가오는 이미지를 인식하여 비가와도 침수로 인식하지 않는다.
![비감지](https://github.com/zoo3323/Flood_detect/assets/95582592/223a07cd-a775-4994-9534-429c45a17c60)

파이썬 시리얼 통신으로 값을 받아 피에조부저와 서보모터가 작동하도록 최종 형태를 만들었다.

![결과](https://github.com/zoo3323/Flood_detect/assets/95582592/adf803bc-60b6-492c-9bb7-99d098ee337d)

