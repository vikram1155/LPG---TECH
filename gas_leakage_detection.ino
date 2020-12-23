#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

int   sensor=A0;
int   led2=2,led3=3,led4=4,led5=5,led6=6;
int   buzzerpin = 11;
float sensorValue;
float sensor_volt;
float Rc = 6.5; 
float RS_gas;
float ratio;

void setup() {

 lcd.begin(16,2);
 lcd.backlight();
 pinMode(sensor,INPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(led4,OUTPUT);
 pinMode(led5,OUTPUT);
 pinMode(led6,OUTPUT);
 pinMode(buzzerpin,OUTPUT);
 Serial.begin(9600);

}

void loop() {
  

  sensorValue = analogRead(sensor);
  sensor_volt = sensorValue / 1024 * 5.0;
  RS_gas = (5.0 - sensor_volt)/ sensor_volt;
  ratio = sensorValue / Rc;
  float ppm = ratio * 10;
  Serial.print("ppm =");
  Serial.println(ppm);
 
   
  
    if(ppm <= 250){
      noTone(buzzerpin);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      Serial.println("NORMAL RANGE");
      lcd.setCursor(0,0);
      lcd.print("NORMAL RANGE");
      lcd.setCursor(0,1);
      lcd.print("PPM");
      lcd.setCursor(5,1);
      lcd.print(ppm);
     }
     else if((ppm>=251) && (ppm<350)){
     digitalWrite(led2,HIGH); 
     digitalWrite(led3,HIGH);
     digitalWrite(led4,LOW);
     digitalWrite(led5,LOW);
     digitalWrite(led6,LOW);
     Serial.println("LOW CONC RANGE");
     lcd.setCursor(0,0);
     lcd.print("LOW CONC RANGE");
     lcd.setCursor(0,1);
     lcd.print("PPM");
     lcd.setCursor(5,1);
     lcd.print(ppm);
     tone(buzzerpin,1);
     }
     else if((ppm>=351) && (ppm<=700)){
     digitalWrite(led3,HIGH); 
     digitalWrite(led2,HIGH); 
     digitalWrite(led4,HIGH);
     digitalWrite(led5,LOW);
     digitalWrite(led6,LOW);
     Serial.println("MID CONC RANGE");
     lcd.setCursor(0,0);
     lcd.print("MID CONC RANGE");
     lcd.setCursor(0,1);
     lcd.print("PPM");
     lcd.setCursor(5,1);
     lcd.print(ppm);
     tone(buzzerpin,10);
     }
    else if((ppm>=701) && (ppm<=900)){
     digitalWrite(led4,HIGH);
     digitalWrite(led2,HIGH); 
     digitalWrite(led3,HIGH);
     digitalWrite(led5,HIGH);
     digitalWrite(led6,LOW);
     Serial.println("HIGH CONC RANGE");
     lcd.setCursor(0,0);
     lcd.print("HIGH CONC RANGE");
     lcd.setCursor(0,1);
     lcd.print("PPM");
     lcd.setCursor(5,1);
     lcd.print(ppm);
     tone(buzzerpin,20);
     }else{
     digitalWrite(led6,HIGH);
     digitalWrite(led2,HIGH); 
     digitalWrite(led3,HIGH);
     digitalWrite(led5,HIGH);
     digitalWrite(led4,HIGH); 
     Serial.println("EMERGENCY!!!");
     lcd.setCursor(0,0);
     lcd.print("EMERGENCY!!!");
     lcd.setCursor(0,1);
     lcd.print("PPM");
     lcd.setCursor(5,1);
     lcd.print(ppm);
     tone(buzzerpin,100);
  }

  delay(1000);
}
