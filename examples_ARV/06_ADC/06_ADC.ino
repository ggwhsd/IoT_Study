
// 两个灯，D13的灯用于按照模拟数值 进行闪烁频率设定。 
// D2 用于当模拟信号数值大于等于1023时，进行点亮，其他时候熄灭。
// A0 用于接收电位器的模拟信号输入
// 模拟信号的Pin无需设置输出输入模式。

int sensorPin = A0;

int LEDPin = 13;
int LEDPin2 = 2;

int sensorValue = 100;



void setup() {
  // put your setup code here, to run once:
pinMode(LEDPin, OUTPUT);
pinMode(LEDPin2, OUTPUT);

}
// I found that  the L LED is default equals D13 OUTPUT in UNO R3 board.
void loop() {
  // put your main code here, to run repeatedly:
sensorValue = analogRead(sensorPin);
if(sensorValue<300&&sensorValue>0)
  sensorValue = 300;
else if(sensorValue<0)
  sensorValue = 2000;
else
{
  if(sensorValue>=1023)
    digitalWrite(LEDPin2, HIGH);
    else
    digitalWrite(LEDPin2, LOW);
  }
digitalWrite(LEDPin, HIGH);
delay(sensorValue);
digitalWrite(LEDPin, LOW);
delay(sensorValue);
}
