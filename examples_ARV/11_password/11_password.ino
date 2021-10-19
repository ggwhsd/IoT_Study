
//输入正确密码，LED灯亮，否则不亮
const int numRows = 4;
const int numCols = 4;
const int debounceTime = 20;
const char keymap[numRows][numCols]={
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'*','0','#','/'}
  };
const int rowPins[numRows]={4,5,6,7};
const int colPins[numCols]={8,9,10,11};
//全部设置为HIGH，因为按键未按下，所以每个按键电路都不通，每个pins上都是HIGH
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(2,OUTPUT); //显示LED灯
   digitalWrite(0,LOW);
   for(int row = 0; row< numRows; row++)
   {
     pinMode(rowPins[row],INPUT);  //输入
     digitalWrite(rowPins[row],HIGH); 
    }

    for(int column = 0; column < numCols; column++)
    {
      pinMode(colPins[column], OUTPUT);  //输出
      digitalWrite(colPins[column],HIGH);
      }
}
char getKey()
{
  char key = -1;
  for(int column = 0; column < numCols; column++)
  {
    digitalWrite(colPins[column],LOW);
    for(int row=0; row < numRows; row++){
      if(digitalRead(rowPins[row]) == LOW)
      {
        delay(debounceTime);
        while(digitalRead(rowPins[row])==LOW){
            //等待按键释放
          }
          key = keymap[row][column];
        
        }
    }
    digitalWrite(colPins[column],HIGH);
   }
   return key;
}

 char inputCode[6] = {0};
 int inputIndex = 0;
//先将第一列输出Pin设为LOW，这列的所有行因为都是HIGH，所以只要这些行里面有一个按键按下，就立即通路，输入LOW信号到行所在的输入Pin中
void loop() {
  // put your main code here, to run repeatedly:
  char key = getKey();
  
  if(key!=-1) {
    
    Serial.print(key);

    if(key=='#')
    {
      inputCode[5]='\0';
      Serial.println();
      Serial.println(inputCode);
      if(strcmp(inputCode,"12345")==0)
      {
        Serial.println("you password is correct");
        digitalWrite(2,HIGH);
      }
      else
      {
        Serial.println("you password is not correct");
        inputIndex = 0;
        memset(&inputCode,0,6);
        digitalWrite(2,LOW);
      }
    }
    else 
    {
      if(inputIndex<5)
        inputCode[inputIndex]=key;
      inputIndex++;
      if(inputIndex==6)
      {
        inputIndex=0;
        memset(&inputCode,0,6);
      }
      
        
    }
  }
}
