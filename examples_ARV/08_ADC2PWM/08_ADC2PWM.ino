
//利用电位器来调节灯强度，利用PWM来调节模拟信号输出的强度
//电位器是模拟信号输入，根据该值，调节PWM来进行模拟信号输出。

int analogInPin_sensor = A0;
int analogOutPin_PWM = 9;
int sensorValue =255; 
//用于PWM信号输出强度
int brightness_PWM = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(analogOutPin_PWM,OUTPUT);
  analogWrite(analogOutPin_PWM, brightness_PWM);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(analogInPin_sensor);
  brightness_PWM = map(sensorValue, 0, 1023, 0 ,255);
  analogWrite(analogOutPin_PWM,brightness_PWM);
  delay(30);
}
