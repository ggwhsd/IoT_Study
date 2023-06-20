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
#include <DS1302.h>  //使用1302时钟模块+768晶振

LiquidCrystal_I2C mylcd(0x20, 16, 2);  
DS1302 myRTC(5,6,7); //对应uno r3上的5、6、7接口，8号口不接线

void setup() {
  // put your setup code here, to run once:
 mylcd.init();
 mylcd.backlight();

  mylcd.display();
  //myRTC.setDate(2023,6,8);
  //myRTC.setDOW(2023,6,8);
  //myRTC.setTime(22,29,15);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  mylcd.setCursor(0, 0);
  mylcd.print("ch2:0.0001");
  //mylcd.print(String((myRTC.getYear())) + String((String("/") + String((String((myRTC.getMonth())) + String((String("/") + String((myRTC.getDay())))))))));
  //mylcd.setCursor(0, 1);
  //mylcd.print(String((myRTC.getHour())) + String((String(":") + String((String((myRTC.getMinute())) + String((String(":") + String((myRTC.getSecond())))))))));

}
