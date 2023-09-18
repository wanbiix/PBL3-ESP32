#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DOUT 4
#define CLK 5
HX711 scale;
 
int rbutton = 8; // this button will be used to reset the scale to 0.
float weight;
float nang;
float a;
float b;
float e;
int c;
float calibration_factor = -255865; //259225 // 255825 // for me this vlaue works just perfect 419640
 
void setup() 
{
  delay(700);
  scale.begin(DOUT, CLK);
  Serial.begin(9600);
  pinMode(rbutton, INPUT_PULLUP); 
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  
  lcd.init();                    
  lcd.backlight(); 
  
}
 
void loop() 
 
{
  e =0;
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
 
  weight = scale.get_units(10);
  nang = weight * 1000; 
  a = nang * 1;
  b = weight * 1;
   if (a<0) 
  { 
    a =0;
  }
  if (b<0)
  {
    b=0;
  }
  
  c = round(a);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WEIGHT");
  lcd.setCursor(8, 0);
  lcd.print(b);
  lcd.print(" KG");
  lcd.setCursor(0, 1);
  //lcd.print("LUONG");
  lcd.setCursor(8, 1);
  lcd.print(c);
  lcd.print(" G");
  delay(500);
 
  
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" KG");
  Serial.println();
  
 
  if ( digitalRead(rbutton) == LOW)
{
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
}
 
}
