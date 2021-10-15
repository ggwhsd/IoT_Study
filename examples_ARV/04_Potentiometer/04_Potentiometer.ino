
// describe: a simple example use 8 LEDs 
// author : GUGU
//

const int analogPin = A0;

const int LEDCount = 8;
int LEDPins[8] = {0,1,2,3,4,5,6,7};


void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < LEDCount; i++)
  {
    pinMode(LEDPins[i],OUTPUT);
  }
}
// use vcc=5v and pin 0,1,2,3,4,5,6,7.  so  LOW means light and HIGH means dark
void loop() {
  // put your main code here, to run repeatedly:

  //read the Potentiometer value
    int sensorReading = analogRead(analogPin);
    int LEDLevel =  map(sensorReading, 0, 1023,0, LEDCount);
    
    for(int i = 0; i < LEDCount; i++)
    {
      if(i<LEDLevel)
        digitalWrite(LEDPins[i],LOW);
      else
        digitalWrite(LEDPins[i],HIGH);
    }     
   
}
