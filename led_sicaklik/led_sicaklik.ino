#include <LiquidCrystal.h>
 
int lm35Pin = A0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup() 
{
  lcd.begin(16, 2);
  analogReference(INTERNAL);
  lcd.print("Sicaklik Olcumu:");
}
 
void loop()
{
  int sicaklikVolt = analogRead(lm35Pin);
  float sicaklikC = sicaklikC = sicaklikVolt / 9.31; 
  lcd.setCursor(0, 1);
  lcd.print(sicaklikC);
  lcd.setCursor(6,1);
  lcd.print("7C");
  delay(100);
}
