#include<Arduino.h>
#include <Wire.h>
int L;
float t=-25.66;
 union temp
{
  float Float;
  byte Byte[4];
}temp1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();  //括号内补充本机地址，作为从机
  
  }

void loop() {
  delay(1000);
  Trans();

}

void Trans()             //传输函数
{
  Wire.beginTransmission(0x99);//括号内补充从机地址
  temp1.Float=t;
  Wire.write(temp1.Byte[0]);
    Wire.write(temp1.Byte[1]);
      Wire.write(temp1.Byte[2]);
        Wire.write(temp1.Byte[3]);
  Wire.endTransmission();
}
