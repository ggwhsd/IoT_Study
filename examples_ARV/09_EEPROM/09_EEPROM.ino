
#include <EEPROM.h>

//UNO r3 内有EEPROM， 就是一种断电后也可以保存数据的地方，类似flash存储，比其擦除次数更多，这样可以做到记录一些个性化数据。
//记录开机次数或者reset次数。
//串口用来输出消息，以便调试程序。
int address =0;
byte value ;


void setup() {
  // put your setup code here, to run once:
   pinMode(3,OUTPUT);
   pinMode(2,OUTPUT);
   
   value = EEPROM.read(address);
   value = value +1;
   value = value %255;
   EEPROM.write(address,value);

   Serial.begin(9600);
   Serial.print("power on times:");
   Serial.print(value, DEC);
   Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(value%2==1)
    digitalWrite(3, HIGH);
  if(value%2==0)
    digitalWrite(2, HIGH);
      
  delay(1000);
}
