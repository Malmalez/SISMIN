#include<LiquidCrystal_SR_LCD3.h>
int strobe = 2;
int data = 3;
int clk = 4;
LiquidCrystal_SR_LCD3 lcd(data, clk, strobe);

int senData1 = A0;
int senData2 = A1;
int senData3 = A2;
int senData4 = A3;
int senData5 = A4;
int senData6 = A5;

int rodaKananMaju = 9;
int rodaKananMundur = 10;
int rodaKiriMaju = 5;
int rodaKiriMundur = 6;

int nilai, rotary = 60;
const int trig = 8;
const int echo = 7;

int data1;
int data2;
int data3;
int data4;
int data5;
int data6;
long duration, cm;
bool obstacle = false;
void setup() {
  // put your setup code here, to run once:
  lcd.home();
  lcd.begin(16, 2);

  pinMode(rodaKananMaju, OUTPUT);
  pinMode(rodaKananMundur, OUTPUT);
  pinMode(rodaKiriMaju, OUTPUT);
  pinMode(rodaKiriMundur, OUTPUT);
  digitalWrite(rodaKananMaju, LOW);
  digitalWrite(rodaKiriMaju, LOW);
  digitalWrite(rodaKananMundur, LOW);
  digitalWrite(rodaKiriMundur, LOW);

  pinMode(senData1, INPUT);
  pinMode(senData2, INPUT);
  pinMode(senData3, INPUT);
  pinMode(senData4, INPUT);
  pinMode(senData5, INPUT);
  pinMode(senData6, INPUT);


  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
}

void loop() {
  lcd.clear();
  data1 = analogRead(senData1);
  data2 = analogRead(senData2);
  data3 = analogRead(senData3);
  data4 = analogRead(senData4);
  data5 = analogRead(senData5);
  data6 = analogRead(senData6);

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);

  if (cm < 5) {
    obstacle = true;
    rotary = 60;
    //diem dulu
    analogWrite(rodaKananMaju, 0);
    analogWrite(rodaKiriMaju, 0);
    //      lcd.clear();
    //      lcd.setCursor(2, 0);
    //      lcd.print("ADA OBSTACLE");
    delay(1000);
    //mundur dulu
    analogWrite(rodaKananMaju, 0);
    analogWrite(rodaKiriMaju, 0);
    analogWrite(rodaKananMundur, rotary);
    analogWrite(rodaKiriMundur, rotary);
    delay(500);
    //hindarin ke kiri
    analogWrite(rodaKananMundur, 0);
    analogWrite(rodaKiriMundur, 0);
    analogWrite(rodaKananMaju, rotary);
    delay(500);
    //maju dikit
    analogWrite(rodaKananMaju, rotary);
    analogWrite(rodaKiriMaju, rotary);
    delay(1000);
    //balik ke kanan
    analogWrite(rodaKananMaju, 0);
    analogWrite(rodaKiriMaju, rotary);
    delay(999);
    //maju terus sampe jalur
    while (obstacle == true) {
      rotary = 35;
      analogWrite(rodaKananMaju, rotary);
      analogWrite(rodaKiriMaju, rotary);
      //pas udah balik lagi
      if ((analogRead(senData3) > 850) && (analogRead(senData4) > 850)) {
        analogWrite(rodaKananMaju, 0);
        analogWrite(rodaKiriMaju, 0);
        analogWrite(rodaKananMundur, 0);
        analogWrite(rodaKiriMundur, 0);
        //          lcd.setCursor(2, 0);lcd.print("BALIK KE JALUR");
        //          lcd.setCursor(2, 1);lcd.print("rotary : ");
        //          lcd.setCursor(8, 1);lcd.print(rotary);
        delay(1000);
        obstacle = false;
        cm = 0;
      }
    }
  }
  if ((data3 > 850) || (data4 > 850)) {
    rotary = 60;
    maju(rotary);
    if ((data6 > 850) || (data1 > 850)) {
      if (data6 > 850) {
        while (data6 > 850) {
          kanana(rotary);
          data6 = analogRead(senData6);
        }
      }
      if (data1 > 850) {
        while (data1 > 850) {
          kiria(rotary);
          data1 = analogRead(senData1);
        }
      }
    }
    else {
      if (data2 > 900) {
        analogWrite(rodaKiriMaju, rotary - 10);
        analogWrite(rodaKananMaju, rotary);
      }
      if (data5 > 900) {
        analogWrite(rodaKiriMaju, rotary);
        analogWrite(rodaKananMaju, rotary - 10);
      }
    }
  }

}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void maju(int nilai) {
  analogWrite(rodaKananMaju, nilai);
  analogWrite(rodaKiriMaju, nilai);
  analogWrite(rodaKiriMundur, 0);
  analogWrite(rodaKananMundur, 0);
}

void kiri(int nilai) {
  analogWrite(rodaKananMundur, 0);
  analogWrite(rodaKiriMundur, nilai - 5);
  analogWrite(rodaKiriMaju, 0);
  analogWrite(rodaKananMaju, nilai);
}

void kanan(int nilai) {
  analogWrite(rodaKiriMundur, 0);
  analogWrite(rodaKananMaju, 0);
  analogWrite(rodaKananMundur, nilai - 5);
  analogWrite(rodaKiriMaju, nilai);
}

void kiria(int nilai) {
  analogWrite(rodaKananMundur, 0);
  analogWrite(rodaKiriMundur, 12);
  analogWrite(rodaKiriMaju, 0);
  analogWrite(rodaKananMaju, nilai);
}

void kanana(int nilai) {
  analogWrite(rodaKiriMundur, 0);
  analogWrite(rodaKananMaju, 0);
  analogWrite(rodaKananMundur, 12);
  analogWrite(rodaKiriMaju, nilai);
}
