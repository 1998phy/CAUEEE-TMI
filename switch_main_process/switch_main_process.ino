
#include <SoftwareSerial.h>
#include <Servo.h>
#include <DS1302.h>


#define BT_RX 7 // 블루투스 송수신 포트
#define BT_TX 8

#define Motor1Port 9 //3개는 서보모터 포트
#define Motor2Port 10
#define Motor3Port 11

#define ServoStandard 90 //서보모터 최초 초기화 각도설정
#define ServoUp 0        //버튼 3개일때 서보 조정 각도
#define ServoDown 180     //버튼 3개일때 서보 조정 각도
#define ServoUp2 30       //버튼 2개일때 서보 조정 각도
#define ServoDown2 120    //버튼 2개일때 서보 조정 각도
#define ServoOn 30        //스위치를 움직이는 2개의 모터 조정 각도
#define ServoOff 150
#define Action 1000       //서보 움직임을 기다려주는 수치


//int i,j=0;

SoftwareSerial HM10(BT_RX,BT_TX);
Servo motor1;
Servo motor2;
Servo motor3;

/*
int switchStat1 = 0;
int switchStat2 = 0;
int switchStat3 = 0;*/

int funcFlag1 = 0;
int funcFlag2 = 0;

int normalMode = 0;
int elevatorMode = 0;

int initialStat1=0;
int initialStat2=0;
int initialStat3=0;

int numberOfButton = 0;



String inputString;
String outputString;


int modeInitialize(String inputStr);

void alamSettingByTime(int hour, int minute ,int second);
void alamSettingByDate(int year,int month, int date,int hour, int minute,int second);

void normalSwitchServoInitialSetting(int motorNum ,int initialStat);
void normalSwitchServo(int switchNum,int stat);

void elevatorSwitchServoInitialSetting(int initialStat);
void elevatorSwitchServo(int stat);

void on();
void off();


void setup() {
  // put your setup code here, to run once:


  Serial.begin(9600);
  HM10.begin(9600);
  //Serial.print("");
  
  while(1){
  
  Serial.println("initializing - wait for signal");
  while(HM10.available()==0){
  
  }
  
  
  inputString = HM10.readString();
  Serial.println(inputString);
  
  
  int temp = modeInitialize(inputString);
  
  
  if (temp){
    Serial.print("complete!!");
    break;
    }
  }
  
    char string0 = '0';
    char string1 = '0';
    char string2 = '0';
    string0 = inputString[0];
    string1 = inputString[1];
    string2 = inputString[2];
    int string0num = atoi(&string0);
    int string1num = atoi(&string1);
    int string2num = atoi(&string2);


  if (normalMode == 1){
    
    normalSwitchServoInitialSetting(numberOfButton,string2num);
  }

  Serial.print("설정된 버튼수는 ");
  Serial.println(numberOfButton);
  inputString.remove(0);
}

void loop(){
  //BT -> Data -> Serial
  if (HM10.available()) {
    inputString = HM10.readString();
    
    Serial.println(inputString);
    
    //Serial.println(inputString.length());
    
  }
  
  // Serial –> Data –> BT
  if (Serial.available()) {
    
    outputString = Serial.readString();
    
    HM10.println(outputString);
    
    //HM10.println(outputString.length());
    
  }
  //데이터 파싱
    




  //작동 시작하는 부분
  if(normalMode == 1 && elevatorMode == 0){
    //일반 스위치 모드
    char string0 = '0';
    char string1 = '0';
    string0 = inputString[0];
    string1 = inputString[1];
    int string0num = atoi(&string0);
    int string1num = atoi(&string1);

    normalSwitchServo(numberOfButton,string0num,string1num);
    
    
  

    
  }

  else if (normalMode == 0 && elevatorMode == 1){
    //엘리베이터 비롯한 누르기만하는 스위치 모드




    
  }
 

  inputString.remove(0);//string buffer 초기화
  outputString.remove(0);
}


int modeInitialize(String inputStr){ // 처음 모드 설정해주기

  if(inputString[0] == '0'){
    normalMode = 1;
    elevatorMode = 0;
    char temp = '0';
    temp = inputString[1];
    int tempnum = atoi(&temp);
    numberOfButton = tempnum;
    //Serial.print(numberOfButton);
    Serial.println("mode 1");
    
    return 1;
  }
  else if(inputString[0] == '1'){
    elevatorMode = 1;
    normalMode = 0;
    numberOfButton = 1;
    Serial.println("mode 2");
    return 1;
    
  }
  else {
    Serial.println("initial ERR");
    return 0;
  }

  
  
}

void alamSettingByTime(int hour, int minute ,int second){
  
  
}

void alamSettingByDate(int year,int month, int date,int hour, int minute,int second){
  
  
}


void normalSwitchServoInitialSetting(int motorNum ,int stat){
  
    
    motor1.attach(Motor1Port);
    motor2.attach(Motor2Port);
    motor3.attach(Motor3Port);


    motor2.write(ServoOff);
    delay(Action);
    motor3.write(ServoOff);
    delay(Action);
    motor1.write(ServoStandard);
    delay(Action);
    
    numberOfButton = motorNum;
    
  //delay(500);


  switch(stat){

    case 0:
    initialStat1 = 0;
    initialStat2 = 0;
    initialStat3 = 0;
    
    break;
    
    case 1:
    initialStat1 = 1;
    initialStat2 = 0;
    initialStat3 = 0;
    break;
    
    case 2:
    initialStat1 = 0;
    initialStat2 = 1;
    initialStat3 = 0;
    
    break;
    
    case 3:
    initialStat1 = 1;
    initialStat2 = 1;
    initialStat3 = 0;
    break;
    
    case 4:
    initialStat1 = 0;
    initialStat2 = 1;
    initialStat3 = 1;
    break;
    
    case 5:
    initialStat1 = 1;
    initialStat2 = 0;
    initialStat3 = 1;
    break;
    
    case 6:
    initialStat1 =0;
    initialStat2 =1;
    initialStat3 =1;
    break;

    
    case 7:
    initialStat1 = 1;
    initialStat2 = 1;
    initialStat3 = 1;
    break;

  }




  
  //motor1.detach();
  //motor2.detach();
  //motor3.detach();

  
}


void normalSwitchServo(int switchNum, int num, int stat){ //switchNum 은 스위치 개수 , num은 몇번째 스위치인지.

  if (switchNum == 1){
    if(num == 1 &&stat == 1){
      
      motor1.write(ServoUp2);
      delay(Action);
      on();
      initialStat1 = 1;
      Serial.println("switch 1 on");
    }
    
    if(num == 1 &&stat == 0){
      
      motor1.write(ServoUp2);
      delay(Action);
      off();
      initialStat1 = 0;
      Serial.println("switch 1 off");
    }


  }

  if(switchNum == 2){
    if(num ==2 && stat ==1){
      motor1.write(ServoDown2);
      delay(Action);
      on();
      initialStat2 = 1;
      Serial.println("switch 2 on");
    }
    if(num ==2&& stat ==0){
      motor1.write(ServoDown2);
      delay(Action);
      off();
      initialStat2 = 0;
      Serial.println("switch 2 off");
    }
  }

  if(switchNum == 3){
    
    if(num ==1 && stat ==1 && initialStat1 == 0){
      motor1.write(ServoUp);
      delay(Action);
      on();
      initialStat1 = 1;
      Serial.println("switch 1 on");
    }
    if(num ==1 && stat ==0 && initialStat1 == 1){
      motor1.write(ServoUp);
      delay(Action);
      off();
      initialStat1 = 0;
      Serial.println("switch 1 off");
    }
    if(num ==2 && stat ==1 && initialStat2 == 0){
      motor1.write(ServoStandard);
      delay(Action);
      on();
      initialStat2 = 1;
      Serial.println("switch 2 on");
    }
    if(num ==2 && stat ==0 && initialStat2 == 1){
      motor1.write(ServoStandard);
      delay(Action);
      off();
      initialStat2 = 0;
      Serial.println("switch 2 off");
    }
    if(num ==3 && stat ==1 && initialStat3 == 0){
      motor1.write(ServoDown);
      delay(Action);
      on();
      initialStat3 = 1;
      Serial.println("switch 3 on");
    }
    if(num ==3 && stat ==0 && initialStat3 == 1){
      motor1.write(ServoDown);
      delay(Action);
      off();
      initialStat3 = 0;
      Serial.println("switch 3 off");
    }
  }
}







/*void normalSwitchServo(int motorNum,int stat){

  if (motorNum == 1){
    motor1.attach(Motor1Port);
    
    switch(stat){

    case 0:
    motor1.write(ServoOff);
    break;
    
    case 1:
    motor1.write(ServoOn);
    break;

    }
  }
  else if (motorNum == 2){
    
    motor1.attach(Motor1Port);
    motor2.attach(Motor2Port);

    switch(stat){

    case 0:
    motor1.write(ServoOff);
    motor2.write(ServoOff);
    break;
    
    case 1:
    motor1.write(ServoOn);
    motor2.write(ServoOff);
    break;
    
    case 2:
    motor1.write(ServoOff);
    motor2.write(ServoOn);
    break;
    
    case 3:

    motor1.write(ServoOn);
    motor2.write(ServoOn);
    break;
    
    }
  }

  
  else if (motorNum == 3){
    
    motor1.attach(Motor1Port);
    motor2.attach(Motor2Port);
    motor3.attach(Motor3Port);

    switch(stat){
    case 0:
    motor1.write(ServoOff);
    motor2.write(ServoOff);
    motor3.write(ServoOff);
    break;
    
    case 1:
    motor1.write(ServoOn);
    motor2.write(ServoOff);
    motor3.write(ServoOff);
    break;
    
    case 2:
    motor1.write(ServoOff);
    motor2.write(ServoOn);
    motor3.write(ServoOff);
    break;
    
    case 3:

    motor1.write(ServoOn);
    motor2.write(ServoOn);
    motor3.write(ServoOff);
    break;

    case 4:

    motor1.write(ServoOff);
    motor2.write(ServoOff);
    motor3.write(ServoOn);
    break;

    case 5:

    motor1.write(ServoOn);
    motor2.write(ServoOn);
    motor3.write(ServoOff);
    break;
    
    case 6:

    motor1.write(ServoOff);
    motor2.write(ServoOn);
    motor3.write(ServoOn);
    break;
    
    case 7:

    motor1.write(ServoOn);
    motor2.write(ServoOn);
    motor3.write(ServoOn);
    break;
    
    }
  }

  delay(1000);
  
  motor1.detach();
  motor2.detach();
  motor3.detach();

  
}*/



void elevatorSwitchServoInitialSetting(int angle){
  
}

void elevatorSwitchServo(int stat){

  
}



void on(){
  motor3.write(ServoOn);
  delay(Action);
  motor3.write(ServoOff);
  delay(Action);
}

void off(){
  motor2.write(ServoOn);
  delay(Action);
  motor2.write(ServoOff);
  delay(Action);
}

