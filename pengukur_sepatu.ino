/*
  I => Indonesia
  J => Japan
  E => Inggris
  U => Amerika
  R => Reset
*/
#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <UltraDistSensor.h>
//pasang pin
#define TRIGGER_PIN 8
#define ECHO_PIN 7
#define TRIGGER2_PIN 27
#define ECHO2_PIN 29
#define MAX_DISTANCE 200

#define BTN_US 53
#define BTN_ING 51
#define BTN_JPN 49
#define BTN_IND 47
#define LIMIT_PANJANGS 2
#define LIMIT_LEBARS 3
#define buzzer 20

// inisiasi ultrasonik
UltraDistSensor sensorUS1;
UltraDistSensor sensorUS2;
//float readSensorUS1;
LiquidCrystal_I2C lcd(0x27, 16, 2);
// inisiasi servo
Servo servo1;
Servo servo2;
//inisisasi ultrasonik
//NewPing sonar1(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

SoftwareSerial mySerial(10, 11); // RX, TX
char BluetoothData;
int pos = 0;
int servo_speed = 25;

float US1;
float US2;
float panjangMax = 31;
float jarakPapanAwal = 1;
float lebarMax = 10;
float jarakPapanAwal2 = 1;
float panjang = 0;
float lebar = 0;
float totalPanjang = 0;
float totalLebar = 0;
float ukuranSepatu = 0;
int limitPanjang, limitLebar, dataUs, dataIng, dataJpn, dataInd;
int stt1=0;
int stt2=0;

int sttPos1 = 60;
int sttr = 0;
char konDataUs[4];
char konDataSepatu[4];
char konDataUs2[4];
float hasilSepatu = 0;

void setup() {
  pinMode(BTN_US, INPUT_PULLUP);
  pinMode(BTN_ING, INPUT_PULLUP);
  pinMode(BTN_JPN, INPUT_PULLUP);
  pinMode(BTN_IND, INPUT_PULLUP);
  pinMode(LIMIT_PANJANGS, INPUT_PULLUP);
  pinMode(LIMIT_LEBARS, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(LIMIT_PANJANGS), rpm_fun1, FALLING);
  attachInterrupt(digitalPinToInterrupt(LIMIT_LEBARS), rpm_fun2, FALLING);
  
  sensorUS1.attach(TRIGGER_PIN, ECHO_PIN);//Trigger pin , Echo pin
  sensorUS2.attach(TRIGGER2_PIN, ECHO2_PIN);//Trigger pin , Echo pin
  Serial.begin(9600);
  mySerial.begin(9600);
  // lcd  
  lcd.begin();
  lcd.backlight();
  // tampil awal lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selamat Datang");
  lcd.setCursor(0, 1);
  lcd.print("Pengukur Sepatu");
  // setting servo  
  servo1.attach(5);
  servo2.attach(6);
  servo1.write(0);
  servo2.write(60);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(1000);
  
}

void loop() {
  US1 = prosesBacaUltrasonik();
  US2 = prosesBacaUltrasonik2();
  
  stt1=0;stt2=0;
  
  dataUs = digitalRead(BTN_US);
  if(dataUs == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Proses Pembacaan...");
    attachInterrupt(digitalPinToInterrupt(LIMIT_PANJANGS), rpm_fun1, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIMIT_LEBARS), rpm_fun2, FALLING);  
    servo1.attach(5);
    servo2.attach(6);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    gerakServo(180, "U");
  }
  dataIng = digitalRead(BTN_ING);
  if(dataIng == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Proses Pembacaan...");
    attachInterrupt(digitalPinToInterrupt(LIMIT_PANJANGS), rpm_fun1, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIMIT_LEBARS), rpm_fun2, FALLING);  
    servo1.attach(5);
    servo2.attach(6);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    gerakServo(180, "E");
  }
  dataJpn = digitalRead(BTN_JPN);
  if(dataJpn == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Proses Pembacaan...");
    attachInterrupt(digitalPinToInterrupt(LIMIT_PANJANGS), rpm_fun1, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIMIT_LEBARS), rpm_fun2, FALLING);  
    servo1.attach(5);
    servo2.attach(6);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    gerakServo(180, "J");
  } 
  dataInd = digitalRead(BTN_IND);
  if(dataInd == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Proses Pembacaan...");
    attachInterrupt(digitalPinToInterrupt(LIMIT_PANJANGS), rpm_fun1, FALLING);
    attachInterrupt(digitalPinToInterrupt(LIMIT_LEBARS), rpm_fun2, FALLING);  
    servo1.attach(5);
    servo2.attach(6);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    gerakServo(180, "I");
  }
//  smartphone 
  while(mySerial.available()){
     char data1 = mySerial.read();
     if(data1 == 'U'){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Proses Pembacaan...");
        attachInterrupt(digitalPinToInterrupt(LIMIT_PANJANGS), rpm_fun1, FALLING);
        attachInterrupt(digitalPinToInterrupt(LIMIT_LEBARS), rpm_fun2, FALLING);  
        servo1.attach(5);
        servo2.attach(6);
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        gerakServo(180, "U");
        
     }
     if(data1 == 'E'){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Proses Pembacaan...");
        attachInterrupt(digitalPinToInterrupt(LIMIT_PANJANGS), rpm_fun1, FALLING);
        attachInterrupt(digitalPinToInterrupt(LIMIT_LEBARS), rpm_fun2, FALLING);  
        servo1.attach(5);
        servo2.attach(6);
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        gerakServo(180, "E");
     }
     if(data1 == 'J'){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Proses Pembacaan...");
        attachInterrupt(digitalPinToInterrupt(LIMIT_PANJANGS), rpm_fun1, FALLING);
        attachInterrupt(digitalPinToInterrupt(LIMIT_LEBARS), rpm_fun2, FALLING);  
        servo1.attach(5);
        servo2.attach(6);
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        gerakServo(180, "J");
     }
     if(data1 == 'I'){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Proses Pembacaan...");
        attachInterrupt(digitalPinToInterrupt(LIMIT_PANJANGS), rpm_fun1, FALLING);
        attachInterrupt(digitalPinToInterrupt(LIMIT_LEBARS), rpm_fun2, FALLING);  
        servo1.attach(5);
        servo2.attach(6);
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        gerakServo(180, "I");
     } 
  }
}

void gerakServo(int data1, String tipeNeg){
    for (pos = 0; pos <= data1; pos += 1){   
      servo1.write(pos);
      sttPos1--; 
      servo2.write(sttPos1);
      delay(servo_speed);
      US1 = prosesBacaUltrasonik();
      US2 = prosesBacaUltrasonik2();

      if((stt1 == 1) && (stt2 == 1)){
        totalLebar = (lebarMax - (jarakPapanAwal2 + US2));
        totalPanjang = (panjangMax - (jarakPapanAwal + US1));
        hasilSepatu = tabelSepatu(totalPanjang, tipeNeg);

        mySerial.write(dtostrf(totalPanjang, 4, 1, konDataUs));
        mySerial.write("-");
        mySerial.write(dtostrf(totalLebar, 4, 1, konDataUs2));
        mySerial.write("-");
        mySerial.write(dtostrf(hasilSepatu, 5, 1, konDataSepatu));
        
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("P=" + String(totalPanjang));
        lcd.setCursor(10, 0);
        lcd.print(" L=" + String(totalLebar));
        lcd.setCursor(0,1);
        lcd.print("Sepatu = " + String(hasilSepatu));
        
        delay(6000);
        servo1.attach(5);
        servo2.attach(6);
        servo1.write(0);
        servo2.write(60);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Letakkan Kaki...");
        lcd.setCursor(0,1);
        lcd.print("Kembali...");
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        delay(500);
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        
        data1 = 0; stt1 = 0; stt2 = 0;sttPos1 = 60;    
        ukuranSepatu = 0;   
      }else{
         prosesBacaUltrasonik();
         prosesBacaUltrasonik2(); 
      }
   }
}

float prosesBacaUltrasonik(){
    panjang = sensorUS1.distanceInCm();
    Serial.println(panjang);
    return panjang;  
}

float prosesBacaUltrasonik2(){
  lebar = sensorUS2.distanceInCm();
  
  return lebar;  
}

void rpm_fun1(){  
  stt1=1;    
  servo2.detach();    
}

void rpm_fun2(){           
  stt2=1;
  servo1.detach();
}
