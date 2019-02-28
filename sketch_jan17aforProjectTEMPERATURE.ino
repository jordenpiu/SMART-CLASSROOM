#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//int tim = 500; 
LiquidCrystal_I2C lcd(0x27,16,2); 

int lm=A3;
int Min=10;
int Max=40;          //LM and FAN
int x=0;
int fan=10;
int in1=13;
int in2=12;
//power
int led4 = 9; 
int led3=6;      
int ir=8;           //LED nad IR Sensor
int count=0;
int fadeValue;
int capacity=6;
int n;
int ir2=7;
//fire sensor
int smoke=4;       //SMOKE SENSOR and Fire Alarm
int fire=5;

//attendance
#include <IRremote.h>
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

int my_Array[10];                     //TSOP
int i;
int a;
int b;
int c;                                   
int d;
int e;
int f;
int g;
int h;
int j;

void setup() {
  lcd.begin(9600);

  pinMode(A3,INPUT);  //TEMPERATURE SENSOR
  pinMode(13,OUTPUT);  //FAN I1
  pinMode(12,OUTPUT);  //FAN I2

  irrecv.enableIRIn();  //REMOTE
  //power
  pinMode(8,INPUT);    
 pinMode(2,INPUT);
 pinMode(9,OUTPUT);
    pinMode(6,OUTPUT);
//fire sensor
  pinMode(smoke,INPUT);
  pinMode(fire,OUTPUT);
  }

void loop() {
//power

 int ir2state=digitalRead(7);
  if (ir2state==1)
  {n++;
  Serial.print("person inside= ");
  Serial.println(n);
  delay(1000);}
  
  int ir1state=digitalRead(8);
  if (ir1state==1)
 {  count++;
    Serial.println(count);
    delay(1000);
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight

 int lmv=analogRead(A3);
 float milivolt=(lmv/1024.0)*5000;
 float celsius=milivolt/10;
 lcd.setCursor(6,0); 
 lcd.print(celsius);
 delay(2000);
 
  x=analogRead(A3);
  lcd.setCursor(1,1);
  lcd.print(x);
  x=map(x,Min,Max,100,200);
 lcd.setCursor(11,1);
 lcd.println(x);
  delay(4000);
  
if (celsius>70 && celsius<35)
{analogWrite(10,190);
digitalWrite(13,HIGH);
digitalWrite(12,LOW);
}
if (celsius>35)
{analogWrite(10,255);                       //fan
digitalWrite(13,HIGH);
digitalWrite(12,LOW);}


    if(n==10 || n>5)
    {
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 50) 
  {
    analogWrite(9, fadeValue);
    analogWrite(6, fadeValue);
    delay(30);
     }
     }
      if(n==5 || n<=5)                                                    //light on
    {
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 50) 
  {
    analogWrite(9, fadeValue); 
    delay(30);
     }
     }
  }
if (ir1state==1 && count==2)
{
    fadeValue = -fadeValue;
    analogWrite(9, fadeValue);
    analogWrite(6, fadeValue);
    digitalWrite(13,LOW);                     //lcd
    digitalWrite(12,LOW);
    lcd.noBacklight();
    count=count-2;
    
  }


                                                                          //attendance
{
if(irrecv.decode(&results))
{
//Serial.println(results.value,DEC);
irrecv.resume();
delay(800);

if(results.value==33480735)

{
a++;
Serial.println(a);
  Serial.println("1 present");
delay(800);
}

if(results.value==33444015)
{
b++;
 Serial.println("2 present");

 delay(800);
}


if(results.value==33478695)
{
c++;
  Serial.println("3 present");
  //Serial.println(count++);
delay(800);
}


if(results.value==33486855)
{
d++;
  Serial.println("4 present");
  //Serial.println(count++);
delay(800);
}



if(results.value==33435855)
{
e++;
Serial.println("5 present");
//Serial.println(count++);
delay(800);
}

if(results.value==33468495)
{
f++;
Serial.println("6 present");
//Serial.println(count++);
delay(800);
}


if(results.value==33452175)
{
g++;
Serial.println("7 present");
//Serial.println(count++);
delay(800);
}


if(results.value==33423615)
{
h++;
Serial.println("8 present");
delay(800);
}

if(results.value==33484815)
{
i++;
Serial.println("9 present");
delay(800);
}

if(results.value==33444015 && 33480735)
{
j++;
Serial.println("10 present");
delay(800);
}

if(results.value==33431775)
{int x=a+b+c+d+e+f+g+h+i+j;
Serial.println(x);
 //int sum=a+b+c+d+e+f+g+h+i+j;
  float percent=x*100/10  ;
Serial.println(percent);                             //attendance percentage
delay(800);
}

//fire sensor
int smokestate=digitalRead(4);
 Serial.println(smokestate);
 if (smokestate==1 )
 {digitalWrite(fire,HIGH);
 Serial.println("b");
 delay(200);
 digitalWrite(fire,LOW);
 delay(200);
} 
}
}
}
