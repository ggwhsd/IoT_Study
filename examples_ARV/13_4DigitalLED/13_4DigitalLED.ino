int LEDCount = 8;
int segCount = 4;
long previousMillis = 0;
//显示数字0-9的编码
const unsigned char dofly_DuanMa[10] = {
  0x3f,
  0x06,
  0x5b,
  0x4f,
  0x66,
  0x6d,
  0x7d,
  0x07,
    0x7f,
  0x6f
  };
//对应输出单个LED段位的引脚Pin
int LEDPins[]={12,8,5,3,2,11,6,4};
//对应选择哪个LED的Pin
int segPins[] = {13,10,9,7};
//显示的数字
unsigned char displayTemp[4];

void setup(){
  for(int thisLED = 0; thisLED < LEDCount; thisLED++){
    pinMode(LEDPins[thisLED], OUTPUT);
  }
  for(int thisSeg = 0; thisSeg < segCount; thisSeg++){
    pinMode(segPins[thisSeg],OUTPUT);
  }
}
//显示LED灯，value为对应数字的编码值
void deal(unsigned char value){
  for(int i =0; i < 8; i++)
  {
    digitalWrite(LEDPins[i],bitRead(value,i));
    }
}



void loop() {
  // put your main code here, to run repeatedly:
  static unsigned int num;
  static unsigned long lastTime = 0 ;
  if(millis() - lastTime >= 1000){
    lastTime = millis();
    num++;
    displayTemp[0] = dofly_DuanMa[num%10];;
    displayTemp[1] = dofly_DuanMa[(num+1)%10];
    displayTemp[2] = dofly_DuanMa[(num+2)%10];
    displayTemp[3] = dofly_DuanMa[(num+3)%10];
  }

  static int i ;
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >0){
    previousMillis = currentMillis;
    deal(0); //清楚影子
    //先将4位都断开
    for(int a =0; a<4; a++){
      digitalWrite(segPins[a],1);
    }
    //选中一位
      digitalWrite(segPins[i],0);
      //显示
      deal(displayTemp[i]);
      i++;
      if(i==4)
      i=0;

  }
  //由于延迟很短，所以看到四位数字，若延迟设为1秒。则只会一位一位显示。
  delay(1);
}
