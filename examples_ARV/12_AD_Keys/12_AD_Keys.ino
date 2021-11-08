//模拟信号输入引脚
const int analogInPin = A0;
//保存从模拟信号读取的数值
int sensorValue = 0;

int keyValue =0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   //读取分压之后的电压值并转换为0-1024之间的数值
   sensorValue = analogRead(analogInPin);
   //先读取一下所有按键的数值，由于是模拟信号转换为数字信号，所以这个数字未必固定值，大概率是一个范围代表一个按键，
   //然后才可以根据这些数值设计对应多少数值范围是哪个按键。
   Serial.print("K[");
   Serial.print( sensorValue);
   Serial.print("]\r\n");
   delay(2000);
}
