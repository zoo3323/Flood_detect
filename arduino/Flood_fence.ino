#include<Servo.h>
int flood=0;//침수 상황 판단
int single_servo_pin=9;//왼쪽 서보모터 핀 9번
//int right_servo_pin=10;//오른쪽 서보모터 핀 10번
int bu_pin=8;//버튼 핀 8번
int buzz_pin=7;//부저 핀 7번
Servo single_servo;
//Servo right_servo;
int shield;//차수막
void setup()
{
  Serial.begin(9600);
  single_servo.attach(single_servo_pin);
  //right_servo.attach(right_servo_pin);
  pinMode(bu_pin,INPUT_PULLUP);
  pinMode(buzz_pin,OUTPUT);
}
void loop()
{
  while(Serial.available())//파이썬과 시리얼 통신
  {
    shield=Serial.read();
  }

   single_servo.write(90);
   //right_servo.write(90);//모터 작동 중지

   if(digitalRead(bu_pin)==1&&shield=='1')//부저 작동
   {
    tone(buzz_pin,523);
    delay(500);
    noTone(buzz_pin);
    delay(500);
   }

   else if(digitalRead(bu_pin)==1&&shield=='2')//차수막 신호
   {
    if(flood==0)
    {
      for(int i=0;i<3;i++)
      {
        single_servo.write(95);
        //right_servo.write(80);
        tone(buzz_pin,523);
        delay(500);
        noTone(buzz_pin);
        delay(500);
      }
    }
    flood=1;
    tone(buzz_pin,523);
    delay(500);
    noTone(buzz_pin);
    delay(500);
   }
  if(digitalRead(bu_pin)==0&&flood==1)//사용자 버튼 누름, 차수막 해제
  {
     single_servo.write(80);
     //right_servo.write(100);
     delay(3000);
     flood=0;
     shield='0';
  }
}