#include<LiquidCrystal.h>
#include<OneWire.h>
LiquidCrystal lcd(13,11,5,4,3,2);
#define echo 9
#define trigger 8
#define buzzer 10
#define motor 6

float distance=0,time=0,temp;
float turbid = 0.0;

void setup()
{
  lcd.begin(16,2);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(motor,OUTPUT);
  pinMode(buzzer,OUTPUT);
  lcd.print(" Automatic Tank ");
  lcd.setCursor(0,1);
  lcd.print(" Filling System ");
  delay(2000);
}

void loop()
{
   turbid = analogRead(A1);
   turbid = turbid * (5.0 / 1024.0);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Turbidity = ");
   lcd.print(turbid); 
   delay(2000);          
    
    if(turbid<3)
    {
       lcd.clear();
       lcd.print("Tank Dirty");
       lcd.setCursor(0,1);
       lcd.print("Clean the Tank");
       delay(3000);  
    }
 
    else
    { 
       loop1();
    }
}

void loop1()
{
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(20);
  digitalWrite(trigger,LOW);
  delayMicroseconds(20);
  time=pulseIn(echo,HIGH);
  distance=(time*0.034)/2;
  lcd.clear();
  lcd.print("Empty Space In");
  lcd.setCursor(0,1);
  lcd.print("Tank is: ");
  lcd.print(distance);
  lcd.print("CM");
  delay(2000);
  if(distance<20 && temp==0)
  {
  digitalWrite(motor,LOW);
  lcd.clear();
  lcd.print("Water Tank Full");
  lcd.setCursor(0,1);
  lcd.print("Motor Turned OFF");
  delay(2000);
  temp=1;
  }
  else if (distance<20 && temp==1)
  {
   digitalWrite(motor,LOW);
   lcd.clear();
   lcd.print("Water Tank Full");
   lcd.setCursor(0,1);
   lcd.print("Motor Turned OFF");
   delay(2000);
  }

 else if (distance>22)
  {
    digitalWrite(motor,HIGH);
    lcd.clear();
    lcd.print("LOW Water Level");
    lcd.setCursor(0,1);
    lcd.print("Motor Turned ON");
    delay(2000);
    tone(buzzer,50,1000);
    delay(1000);
    temp=0;
  }
}
