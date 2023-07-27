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
6. 웹캠을 사용하여 실시간 이미지 분석

> 모델 학습 부분은 [Image_classification_pipeline_Project](https://github.com/inhovation97/Image_classification_pipeline_Project.git)의 소스코드를 수정하여 사용하였습니다.

## 결과
![정확도와로스](https://github.com/zoo3323/Flood_detect/assets/95582592/0097780b-0abc-428f-b4fd-77238c00b1c0)

## 결과물 형태
파이썬 시리얼 통신으로 값을 받아 피에조부저와 서보모터가 작동하도록 최종 형태를 만들었다.

![결과](https://github.com/zoo3323/Flood_detect/assets/95582592/adf803bc-60b6-492c-9bb7-99d098ee337d)
