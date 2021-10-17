
int pushButton = 2;
int LEDPin = 13;
//Serial is used to display message . If you has not serial port, it can be comment.
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pushButton,INPUT);
  pinMode(LEDPin,OUTPUT);
}

// 若直接如下代码，按下则亮，松开则暗。
// 而且，会出现按键抖动，因为按键属于机械硬件，按下时间内到稳定电压期间，单片机已经读取了可能几十次数据。
//因此需要消除抖动影响。
void testSwitchLED()
{
  int buttonState = digitalRead(pushButton);
  digitalWrite(LEDPin,buttonState);
  Serial.println(buttonState);
  delay(10);
}


int LEDState= HIGH;
int buttonState ;
int lastButtonState = LOW;
long lastDeBounceTime = 0;
long debounceDelay = 50;
//消除抖动。  而且按下松开，才会切换一次灯的状态。 
void testSwitchLED2()
{
	 int reading = digitalRead(pushButton);
   if(reading != lastButtonState) {
    lastDeBounceTime = millis();
    
   }
   if((millis()-lastDeBounceTime) > debounceDelay){
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState == HIGH){
        LEDState = !LEDState;
      }
    }
   }

   digitalWrite(LEDPin, LEDState);
   lastButtonState = reading;
}


void loop() {
  // put your main code here, to run repeatedly:
testSwitchLED2();
}
