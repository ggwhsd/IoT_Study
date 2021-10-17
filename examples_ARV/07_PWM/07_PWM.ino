
//呼吸灯效果，利用PWM来调节模拟信号输出的强度


int PWMPin = 9;
//用于PWM信号输出强度
int brightness = 0;
//这个数字越小，呼吸灯的节奏越慢
int fadeAmount = 5;  

void setup() {
  // put your setup code here, to run once:
  pinMode(PWMPin,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(PWMPin, brightness);
  brightness = brightness + fadeAmount;
  if(brightness <0)
      brightness = 0;
  if(brightness > 255)
      brightness = 255;
  // in UNO r3, it is 0~255 for PWM output.
  if(brightness == 0|| brightness == 255)
     fadeAmount = - fadeAmount;
  delay(30);
}
