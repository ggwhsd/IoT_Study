

int LEDCount = 8;
//数字1-9的数码管编码
const unsigned char DuanMa[10] = {
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
//灯管的引脚是从左下角开始计数 1开始，逆时针计数 1 - 10。
// 单片机Pins 和 数码灯管的对应关系： 76543210 -> abcdefgh。   而灯管 abcdefgh和灯管指针的关系参考说明书 7 6 4 2 1 9 10 5， 3和8内部已经连在一起，需要连接共阳Vcc或者共阴GND，
int LEDPins[8]={0,1,2,3,4,5,6,7};


void setup() {
  // put your setup code here, to run once:
    for(int i =0; i < LEDCount; i++)
    {
      pinMode(LEDPins[i], OUTPUT);
    }
}



void loop() {
  // put your main code here, to run repeatedly:
   
 for(int i =0; i < LEDCount; i++)
    {
      digitalWrite(LEDPins[i],HIGH); 
    }
   delay(1000);
   
   
}
