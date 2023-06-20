/*1602 SHOW
 * vss -> GND
 * vdd -> +5V
 * v0 -> 对比度
 * RS RW -> 组合 0 0 写入指令， 0 1 读取计数器 等
 * D0-D7 双向数据总线
 * A（bla） K（blk）  背光的+，背光的-，两者导通，背光亮
 * 
 * 这里用了一个转接器德飞莱的ly-s3005，可以简化操作1602，变成iic总线方式，只有四个pin口。
 * 亮度调节ly-s3005背板上的一个十字口的地方，向右调整对比度更容易看清字体。
 * scl->a5
 * sda->a4
 * vcc->+5v
 * gnd->gnd
 */

#include "LiquidCrystal_I2C.h"
#include <SoftwareSerial.h>

LiquidCrystal_I2C mylcd(0x20, 16, 2);  
SoftwareSerial mySerial(2,3); //利用普通pin口进行虚拟软串口，2为RX，3为TX

long recv_count = 0;
int CH2_input[8] = {0};
int input_temp = -1;
int flag_start = 0xFF;
void setup() {
  // put your setup code here, to run once:
 mylcd.init();
 mylcd.backlight();

 mylcd.display();
 mySerial.begin(9600);
 // Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:


  ///读取ch2串口数据
  while(mySerial.available()>0){
    input_temp = mySerial.read();
    recv_count++;
    if(input_temp == flag_start)
    {
      recv_count=0;
    //  Serial.println("one package start");
    }
   // Serial.println(input_temp,HEX);
    CH2_input[recv_count] = input_temp;
    
    if(recv_count==8)
    {
     // Serial.println("one package end");
      break;
    }
  }  
  /// 显示数据
  int value = CH2_input[4]*256 + CH2_input[5];
  mylcd.setCursor(0, 0);
  mylcd.print("ch2(mg/m3):");
  mylcd.setCursor(0, 1);
  mylcd.print((value/1000.0));
   //Serial.println(value/1000.0);
  delay(1000);


  ///读取ch2串口数据
  while(mySerial.available()>0){
    input_temp = mySerial.read();
    recv_count++;
    if(input_temp == flag_start)
    {
      recv_count=0;
    //  Serial.println("one package start");
    }
   // Serial.println(input_temp,HEX);
    CH2_input[recv_count] = input_temp;
    
    if(recv_count==8)
    {
     // Serial.println("one package end");
      break;
    }
  }  
  /// 显示数据
  int value = CH2_input[4]*256 + CH2_input[5];
  mylcd.setCursor(0, 0);
  mylcd.print("ch2(mg/m3):");
  mylcd.setCursor(0, 1);
  mylcd.print((value/1000.0));
   //Serial.println(value/1000.0);
  delay(1000);
  
 
}
