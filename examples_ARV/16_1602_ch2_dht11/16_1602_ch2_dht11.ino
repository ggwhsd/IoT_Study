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
#include "DHT.h"
#include <SoftwareSerial.h>

LiquidCrystal_I2C mylcd(0x20, 16, 2);  
SoftwareSerial mySerial1(8,3); //利用普通pin口进行虚拟软串口，2为RX，3为TX
SoftwareSerial mySerial2(6,5); //利用普通pin口进行虚拟软串口，6为RX，5为TX
DHT dht4(4,11); //温度湿度传感器。pin = 4，11为参数型号

long recv_count = -1;
int CH2_input[8] = {0};
double CH2_value = 0.00;
int flag_start = 0xFF;
int data_input[9] = {0};
double value_tvoc = 0.00;
double value_CH2O = 0.00;
int value_CO2 = 0;
int data_start = 0x2C;
int input_temp = -1;

long loop_count = 0;
void setup() {
  // put your setup code here, to run once:
 mylcd.init();
 mylcd.backlight();

 mylcd.display();
 mySerial1.begin(9600);
 mySerial2.begin(9600);
 dht4.begin();
 Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  loop_count++;
  if(loop_count%2==0)
  {
    mySerial1.listen();
    Serial.println("mySerial1:");
     
  }
  delay(1000);
  ///读取ch2串口数据
  int num = mySerial1.available();
  Serial.println(num);
  if(mySerial1.available()>=9){
    while(mySerial1.available()>0){
      input_temp = mySerial1.read();
      if(input_temp == flag_start)
      {
        recv_count=0;
      }
      CH2_input[recv_count] = input_temp;
      if(recv_count==8)
      {
        CH2_value = CH2_input[4]*256 + CH2_input[5];
        break;
      }
      recv_count++;
    }  
  }
  /// 显示ch2数据
  //if((loop_count%7==1))
  {
    mylcd.clear();
    mylcd.setCursor(0, 0);
    mylcd.print("ch2o,T,H");
    mylcd.setCursor(0, 1);
    mylcd.print((CH2_value*0.001));
    mylcd.print(",");
    /// 显示温度和湿度数据
    mylcd.print(dht4.readTemperature());
    mylcd.print(",");
    mylcd.print(dht4.readHumidity());
  }
   //Serial.println(value/1000.0);
  
  ///读取串口数据.
 
  recv_count=0;
 if(loop_count%2==1)
  {
    mySerial2.listen();
    
  }
  delay(1000);
  if(mySerial2.available()>=9)
  {
    while(mySerial2.available()>0){
      input_temp = mySerial2.read();
      
      if(input_temp == data_start)
      {
        recv_count=0;
      //  Serial.println("one package start");
      }
     // Serial.println(input_temp,HEX);
      data_input[recv_count] = input_temp;
      
      if(recv_count==8)
      {
       // Serial.println("one package end");
        value_tvoc = (data_input[2]*256 + data_input[3])*0.001;
     value_CH2O =  (data_input[4]*256 + data_input[5])*0.001;
     value_CO2 =  (data_input[6]*256 + data_input[7])*1;
        break;
      }
      recv_count++;
    }  
  }
  /// 显示ch2数据
  
  //if((loop_count%7==4))
  {
    
    mylcd.clear();
    mylcd.setCursor(0, 0);
    mylcd.print("voc,ch2o,co2");
    mylcd.setCursor(0, 1);
    mylcd.print(value_tvoc);mylcd.print(",");
    mylcd.print(value_CH2O);mylcd.print(",");
    mylcd.print(value_CO2);
  }
 
}
