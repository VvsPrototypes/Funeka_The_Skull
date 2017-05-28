#include <Servo.h>  
#include <Wire.h>  
  
#define D6T_addr 0x0A  
#define D6T_cmd 0x4C  
Servo myservo;  
int a;  
int b;  
int tmax, imax;  
int numbytes = 19;  
int numel = 8;  
int rbuf[19];  
int tdata[8];  
float t_PTAT;  
int deg;  
int i;  
  
void setup()  
{  
  pinMode(12, INPUT);  
  pinMode(13, INPUT);  
  for (i = 2; i < 6; i++)  
  {  
    pinMode(i, OUTPUT);  
  
    pinMode(8, OUTPUT);  
    pinMode(9, OUTPUT);  
    pinMode(10, OUTPUT);  
  
    Wire.begin();  
    myservo.attach(11);  
    myservo.write(90);  
    system("python /Skull/intro.py");  
    eyeblink();  
    wings();  
  }  
  
  
  void loop() {  
    a = digitalRead(12);  
    b = digitalRead(13);  
    voice(a);  
    music(b);  
    eyes(a, b);  
  }  
  
  void offall()  
  {  
    for (int i = 2; i < 6; i++)  
    { digitalWrite(i, LOW);  
      delay(1);  
    }  
  }  
  
  void music(int o)  
  {  
    if (o == 1)  
    {  
      int L = analogRead(A0);  
      int R = analogRead(A1);  
      if (150 < L && L < 250)  
      {  
        digitalWrite(2, HIGH);  
      }  
      if (351 < L && L < 1023)  
      {  
        digitalWrite(2, HIGH);  
        delay(10);  
        digitalWrite(3, HIGH);  
        delay(10);  
      }  
  
      if (150 < R && R < 250)  
      {  
        digitalWrite(4, HIGH);  
      }  
      if (351 < R && R < 1023)  
      {  
        digitalWrite(4, HIGH);  
        delay(10);  
        digitalWrite(5, HIGH);  
        delay(10);  
      }  
    }  
    offall();  
    delay(10);  
  }  
  
  void voice(int p)  
  {  
    if (p == 1)  
    {  
      system("python /Skull/speech.py");  
      delay(100);  
    }  
  }  
  
  
  void eyes(int m, int n)  
  {  
    if (m == 0 && n == 0)  
    {  
      tmax = 0;  
      imax = 0;  
      Wire.beginTransmission(D6T_addr);  
      Wire.write(D6T_cmd);  
      Wire.endTransmission();  
      delay(70);  
      Wire.requestFrom(D6T_addr, numbytes); // D6T-8 returns 19 bytes  
  
      if (0 <= Wire.available()) { // If there is data still left in buffer  
        i = 0;  
        for (i = 0; i < numbytes; i++) {  
          rbuf[i] = Wire.read();  
        }  
        t_PTAT = (rbuf[0] + (rbuf[1] << 8) ) * 0.1;  
        for (i = 0; i < numel; i++) {  
          tdata[i] = (rbuf[(i * 2 + 2)] + (rbuf[(i * 2 + 3)] << 8 )) * 0.1;  
        }  
      }  
  
      for (i = 0; i < numel; i++)  
      {  
        if (tmax <= tdata[i])  
        { tmax = tdata[i];  
          imax = i;  
          Serial.println(imax);  
        }  
      }  
      deg = map(imax, 0, 7, 60 , 120);  
      myservo.write(deg);  
      delay(10);  
    }  
  }  
  
  void eyeblink()  
  {  
    digitalWrite(8, HIGH);  
    delay(300);  
    digitalWrite(8, LOW);  
    delay(100);  
    digitalWrite(8, HIGH);  
    delay(400);  
    digitalWrite(8, LOW);  
    delay(200);  
    digitalWrite(8, HIGH);  
    delay(100);  
    digitalWrite(8, LOW);  
    delay(500);  
    digitalWrite(8, HIGH);  
  }  
  void wings()  
  {  
    digitalWrite(10, OUTPUT);  
    for (i = 0; i < 21; i++)  
    { digitalWrite(9, HIGH);  
      delay(20);  
      digitalWrite(9, LOW);  
      delay(20);  
  
    }  
  }  
