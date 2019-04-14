#include<Arduino.h>
#include <Wire.h>
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
int x[14];
int clockwise=0,states;
int a=200,b=500;//光强的上下界，初始值为起居室的适宜光强
unsigned int mode=1;//光照模式，0，1，2三档，初始值为第一档；
void rotate(int,int);
unsigned long triggertime=0;
 union temp
{
  float Float;
  byte Byte[4];
}temp1;

void setup() 
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  Serial.begin(9600);
  rotate(102,0);    //百叶窗启动调零
    delay(1000);
  rotate(102,0);
    delay(1000);
  rotate(102,0);
    delay(1000);
  rotate(102,0);
    delay(1000);
  rotate(102,1);
  Wire.begin(0x99);  //括号内补充本机地址，作为从机
  Wire.onReceive(receiveEvent);       //接收数据的函数
  attachInterrupt(0,changeMode,FALLING);  //添加按键中断
  states=1;
}

void changeMode()           //按键中断修改模式函数
{
  if(millis()-triggertime>100)      //消除抖动
  {
triggertime=millis();
  mode++;
  mode=mode%3;
  switch (mode)
   {
    case 0:a=0;b=200;break;
    case 1:a=200;b=500;break;
    case 2:a=500;b=800;break;
   }
  }
}

void receiveEvent()

{
  int L;
  while(Wire.available()>0)

  {
    for(int i=0;i<14;i++)
    {
      x[i]=Wire.read();
    }
    L=((x[0]<<8) | x[1])/1.2;
    
  }
  for(int i=2;i<6;i++)
    {
      temp1.Byte[i-2]=x[i];
    }
  Serial.println(temp1.Float);
    for(int i=6;i<10;i++)
    {
      temp1.Byte[i-6]=x[i];
    }
  Serial.println(temp1.Float);
    for(int i=10;i<14;i++)
    {
      temp1.Byte[i-10]=x[i];
    }
  Serial.println(temp1.Float);
  Serial.println(L);                      
  clockwise=judge(a,b,L);
  if(clockwise==1&&states!=0) //states记录电机的当前位置
  {
    rotate(50,clockwise);                
    states--;
  }
   if(clockwise==0&&states!=10) //states记录电机的当前位置
  {
    rotate(50,clockwise);                
    states++;
  }
}
int judge(int a,int b,float L)    //判断当前光强是否是
{                       //预定范围
  if(L>=a&&L<=b) return -1;
  else if(L<a) return 0;
  else return 1;
}

void STEP(int i)              //驱动步进电机的函数
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
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
      break;
    }
  }
}

void rotate(int times, int clockwise=1)
{
  //times为多少次8相，times=512对应一周。
 //clockwise是标记顺逆时针，0为顺时针转动，1为逆时针转动
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
  STEP(8);
  delay(1000);
}
