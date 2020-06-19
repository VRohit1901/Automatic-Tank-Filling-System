#include<LiquidCrystal.h>
#include<OneWire.h>
LiquidCrystal lcd(13,11,5,4,3,2);
#define echo 9
#define trigger 8
#define buzzer 10
#define motor 6

//Initialize variables
float distance=0,time=0,count;
float turbidity = 0.0;

void setup()
{
  //Intialize input/output mode
  lcd.begin(16,2);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(motor,OUTPUT);
  pinMode(buzzer,OUTPUT);

  //Print welcome message
  lcd.print(" Automatic Tank ");
  lcd.setCursor(0,1);
  lcd.print(" Filling System ");
  delay(2000);

}

void loop()
{
  //Check and print the turbidity of water
  turbidity = analogRead(A1);
  turbidity = turbidity * (5.0 / 1024.0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Turbidity = ");
  lcd.print(turbidity); 
  delay(2000);      

  //Program wont proceed further untill turbidity is below threshold
  if(turbidity>3)
  {
    digitalWrite(motor,LOW);
    lcd.clear();
    lcd.print("Tank Dirty");
    lcd.setCursor(0,1);
    lcd.print("Clean the Tank");
    delay(3000); 
  }
  
  //When turbidity is above threshold
  else
  { 
    loop1();
  }

}

void loop1()
{
  //Check water level in the tank
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(20);
  digitalWrite(trigger,LOW);
  delayMicroseconds(20);
  time=pulseIn(echo,HIGH);
  distance=(time*0.034)/2;

  //Print the water level
  lcd.clear();
  lcd.print("Empty Space In");
  lcd.setCursor(0,1);
  lcd.print("Tank is: ");
  lcd.print(distance);
  lcd.print("CM");
  delay(2000);

  //Execute when water level above threshold
  if(distance<20 && count==0)
  { 
    //Stop motor and buzzer
    digitalWrite(motor,LOW);
    noTone(buzzer);
    lcd.clear();
    lcd.print("Water Tank Full");
    lcd.setCursor(0,1);
    lcd.print("Motor Turned OFF");
    delay(2000);
    count=1;
  }

  else if (distance<20 && count==1)
  {
    //Count is used to avoid the usage of motor and buzzer off overwrite
    lcd.clear();
    lcd.print("Water Tank Full");
    lcd.setCursor(0,1);
    lcd.print("Motor Turned OFF");
    delay(2000);
  }

  //Execute when water level below threshold
  else if (distance>22)
  {
    //Start motor
    digitalWrite(motor,HIGH);
    lcd.clear();
    lcd.print("LOW Water Level");
    lcd.setCursor(0,1);
    lcd.print("Motor Turned ON");
    delay(2000);
    //Play buzzer
    tone(buzzer,50,1000);
    count=0;
  }

}