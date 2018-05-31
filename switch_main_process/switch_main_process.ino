
#include <SoftwareSerial.h>
#include <Servo.h>
#include <DS1302.h>


#define BT_RX 7 // 블루투스 송수신 포트
#define BT_TX 8

#define Motor1Port 9 //3개는 서보모터 포트
#define Motor2Port 10
#define Motor3Port 11

#define ServoStandard 90 //서보모터 최초 초기화 각도설정
#define ServoOn 30
#define ServoOff 150



//int i,j=0;

SoftwareSerial HM10(BT_RX,BT_TX);
Servo motor1;
Servo motor2;
Servo motor3;

int switchStat1 = 0;
int switchStat2 = 0;
int switchStat3 = 0;
int funcFlag1 = 0;
int funcFlag2 = 0;
int normalMode = 0;
int elevatorMode = 0;



String inputString;
String outputString;


int modeInitialize(String inputStr);

void alamSettingByTime(int hour, int minute ,int second);
void alamSettingByDate(int year,int month, int date,int hour, int minute,int second);

void normalSwitchServoInitialSetting(int motorNum ,int initialStat);
void normalSwitchServo(int motorNum,int stat);

void elevatorSwitchServoInitialSetting(int initialStat);
void elevatorSwitchServo(int stat);




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
  Serial.print(inputString);
  
  Serial.print(inputString[0]);
  int temp = modeInitialize(inputString);
  
  //Serial.println(inputString.length());

  //Serial.print(inputString[1]);
  
  if (temp){
    Serial.print("initial complite!");
    break;
  }
  }
  
  
  
}

void loop(){
  //Serial -> Data -> BT
  if (HM10.available()) {
    inputString = HM10.readString();
    
    Serial.print(inputString);
    
    Serial.println(inputString.length());
    
  }
  
  // Serial –> Data –> BT
  if (Serial.available()) {
    
    outputString = Serial.readString();
    
    HM10.print(outputString);
    
    HM10.println(outputString.length());
    
  }

 

  
}


int modeInitialize(String inputStr){

  if(inputString[0] == '0'){
    normalMode = 1;
    elevatorMode = 0;
    return 1;
  }
  else if(inputString[0] == '1'){
    elevatorMode = 1;
    normalMode = 0;
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
  if (motorNum == 1){
    motor1.attach(Motor1Port);
    motor1.write(ServoStandard);
  }
  else if (motorNum == 2){
    motor1.attach(Motor1Port);
    motor2.attach(Motor2Port);
    motor1.write(ServoStandard);
    motor2.write(ServoStandard);
  }
  else if (motorNum == 3){
    motor1.attach(Motor1Port);
    motor2.attach(Motor2Port);
    motor3.attach(Motor3Port);
    motor1.write(ServoStandard);
    motor2.write(ServoStandard);
    motor3.write(ServoStandard);
  }

  delay(500);
  
  motor1.detach();
  motor2.detach();
  motor3.detach();
  
}


void normalSwitchServo(int motorNum,int stat){

  if (motorNum == 1){
    motor1.attach(Motor1Port);
    
    switch(stat){

    case 0:
    motor1.write(ServoOff);
    
    case 1:
    motor1.write(ServoOn);

    }
  }
  else if (motorNum == 2){
    
    motor1.attach(Motor1Port);
    motor2.attach(Motor2Port);

    switch(stat){

    case 0:
    motor1.write(ServoOff);
    motor2.write(ServoOff);
    
    case 1:
    motor1.write(ServoOn);
    motor2.write(ServoOff);
    
    case 2:
    motor1.write(ServoOff);
    motor2.write(ServoOn);
    
    case 3:

    motor1.write(ServoOn);
    motor2.write(ServoOn);
    
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
    
    case 1:
    motor1.write(ServoOn);
    motor2.write(ServoOff);
    motor3.write(ServoOff);
    
    case 2:
    motor1.write(ServoOff);
    motor2.write(ServoOn);
    motor3.write(ServoOff);
    
    case 3:

    motor1.write(ServoOn);
    motor2.write(ServoOn);
    motor3.write(ServoOff);

    case 4:

    motor1.write(ServoOff);
    motor2.write(ServoOff);
    motor3.write(ServoOn);

    case 5:

    motor1.write(ServoOn);
    motor2.write(ServoOn);
    motor3.write(ServoOff);
    
    case 6:

    motor1.write(ServoOff);
    motor2.write(ServoOn);
    motor3.write(ServoOn);
    
    case 7:

    motor1.write(ServoOn);
    motor2.write(ServoOn);
    motor3.write(ServoOn);
    
    }
  }

  delay(500);
  
  motor1.detach();
  motor2.detach();
  motor3.detach();

  
}



void elevatorSwitchServoInitialSetting(int angle){
  
}

void elevatorSwitchServo(int stat){

  
}

