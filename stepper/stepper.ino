#include<Arduino.h>
#include <Wire.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

int clockwise=0;
void rotate(int,int);

void setup() 
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  Serial.begin(9600);
  Wire.begin(0x99);//括号内补充本机地址，作为从机
  Wire.onReceive(receiveEvent);
}

void receiveEvent()
{
  while(Wire.available()>0)
  {
    clockwise=Wire.read();
  }
  Serial.println(clockwise);
  rotate(100,clockwise);
}

void STEP(int i)
{
  switch (i)
  {
    case 0:
    {
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 1);
      break;
    }
    case 1:
    {
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 1);
      break;
    }
    case 2:
    {
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 1);
      break;
    }
    case 3:
    {
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
      break;
    }
    case 4:
    {
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
      break;
    }
    case 5:
    {
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
    }
    case 6:
    {
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
      break;
    }
    case 7:
    {
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
      break;
    }
    case 8:
    {
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 1);
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 1);
      break;
    }
  }
}

void rotate(int times, int clockwise=1)
{
  //times为多少次8相，times=512对应一周。
  int j=times;
  while(j--)
  {
    if(clockwise==0)
    {
      for(int i=0;i<8;++i)
      {
        STEP(i);
        delay(2);
      }
      STEP(8);
      delay(1);
    }
    if(clockwise==1)
    {
      for(int i=7;i>=0;--i)
      {
        STEP(i);
        delay(2);
      }
      STEP(8);
      delay(1);
    }
  }
}


void loop() 
{
  delay(100);

}
