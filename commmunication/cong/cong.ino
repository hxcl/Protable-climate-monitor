#include<Arduino.h>
#include <Wire.h>
 union temp
{
  float Float;
  byte Byte[4];
}temp1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(0x99);  //括号内补充本机地址，作为从机
  Wire.onReceive(receiveEvent);       //接收数据的函数
}
void loop() {
  delay(1000);
}
void receiveEvent()

{
  float L;
  while(Wire.available()>0)

  {
    int x,y;
    //x=Wire.read();
    //y=Wire.read();
    //L=((x<<8) | y)/1.2;
    //Serial.print(x);
    //Serial.println(y);
    temp1.Byte[0]=Wire.read();
        temp1.Byte[1]=Wire.read();
            temp1.Byte[2]=Wire.read();
                temp1.Byte[3]=Wire.read();
                L=temp1.Float;
    Serial.println(L);
  }
}
