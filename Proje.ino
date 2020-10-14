#include<Servo.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#define led 3 // 3.Pinde LED olduğunu tanımlıyoruz
#define DHTPIN 11  //dhtyi bağladığımız pini yazdık
#define DHTTYPE DHT11  //dhtp sensör tipini yazdık
Servo motor; //motor adında bir servo nesnesi oluşturduk.
DHT sicaklikSensor(DHTPIN, DHTTYPE); //sensorumuz isimli bir nesne oluşturduk
LiquidCrystal lcd(2,4,5,6,7,10);

char veri; 
int suVeri;
int alarm = 0;
int pirPin = 8;                   //Sensörü takacağımız pin
int servoPin = 9;
int hareket;                      //Sensörden aldığımız veri
int buzzerPin = 12;
int C = 262;
int deger = 0;
int otopark = false;
int suSensor = false;
int sensorPin = A0;                //Sensörü bağlayacağımız pin
int esikDegeri = 100;              //Su miktarı için eşik değeri                    

void setup() {
  sicaklikSensor.begin(); 
  lcd.begin(16, 2);
  lcd.print("Sicaklik ve Nem:");
  pinMode(led,OUTPUT);              // Led dijital olarak kullanacağımız için çıkış tanımlaması yapılmalıdır.
  pinMode(pirPin, INPUT);         //Sensör pinimizi giriş olarak ayarlyoruz.
  motor.attach(servoPin); // Servo motorun data pinini arduino 3 numaralı 
  Serial.begin(9600);               //Seri haberleşmeyi başlatıyoruz
}
void loop() {
  float sicaklik = sicaklikSensor.readTemperature();
  float nem = sicaklikSensor.readHumidity();
  lcd.setCursor(0, 1);
  lcd.print(sicaklik);
  lcd.print("C");
  lcd.setCursor(7,1);
  lcd.print(nem);
  lcd.print("%");
  delay(100);
  hareket = digitalRead(pirPin);  //Sensörden okuma yapıyoruz.
  deger = digitalRead(pirPin); // Dijital pin okunuyor
  
  if(Serial.available()>0){         //Seri haberleşmeden veri gelmesini bekliyoruz.
    veri = Serial.read();           //Seri haberleşmeden gelen veriyi okuyoruz.
  }
  if(veri == 'A')
  {
    if(otopark == false){
      lcd.setCursor(0,0);
      lcd.print("                                    ");
      lcd.setCursor(0,0);
      lcd.print("Otopark Acildi.");
      motor.write(0); //Otopark Açıldı.
      delay(3000);
      lcd.setCursor(0,0);
      lcd.print("                                    ");
      lcd.setCursor(0,0);
      lcd.print("Otopark Kapandi.");
      otopark = true; 
      motor.write(95); //Otopark Kapandı.
      delay(5000);
    }else{
      motor.write(94);
      otopark = false;
    }
  }else if(veri == 'B'){
    if(alarm == 1){
       alarm = 0;
    }else{
      alarm = 1;
      lcd.setCursor(0,0);
      lcd.print("                                    ");
      delay(1300);
      lcd.setCursor(0,0);
      lcd.print("Alarm Aktif!");
    }
  }
  
  if(veri == 'C'){
    if(suSensor == false){
      lcd.setCursor(0,0);
      lcd.print("                                    ");
      delay(1500);
      lcd.setCursor(0,0);
      lcd.print("Su Alarmi Aktif!");
      suSensor == true;
      suVeri = analogRead(sensorPin);    //Sensörden analog veriyi okuyoruz.
      if(suVeri > esikDegeri){           //Sensör verisi eşik değerini geçerse if içerisindeki kodlar uygulanır.
        lcd.setCursor(0,0);
        lcd.print("                                    ");
        lcd.setCursor(0,0);
        lcd.print("Su Alarmi!");   
        tone(buzzerPin, C);
        digitalWrite(buzzerPin, HIGH); 
        delay(100);
        digitalWrite(buzzerPin, LOW);
        delay(100);
        noTone(buzzerPin);
      }
      else{                            //Sensör verisi eşik değerinden küçük olursa if içerisindeki kodlar uygulanır.
        digitalWrite(buzzerPin, LOW);
      }
    }else{
      
      suSensor == false;
    }
  }

  if(veri == 'D'){
    lcd.setCursor(0,0);
    lcd.print("                                    ");
    lcd.setCursor(0,0);
    lcd.print("Sensor Acik");
    delay(3000);
    int IsikDeger = analogRead(A1);      // Deger isimli bir değişken tanımlıyoruz. Bu değişken A0 Analog Pininden gelen veriyi tutacak.  
    if(IsikDeger <= 15){
        lcd.setCursor(0,0);
        lcd.print("                                    ");
        lcd.setCursor(0,0);
        lcd.print("Led Yaniyor!");
        digitalWrite(led,HIGH);
        delay(3000);
    }else{
      lcd.setCursor(0,0);
      lcd.print("                                    ");
      lcd.setCursor(0,0);
      lcd.print("Led Kapali");
      digitalWrite(led,LOW);
      delay(3000);
    }
  }

if (veri == 'F'){
  lcd.setCursor(0,0);
  lcd.print("Sicaklik ve Nem:");
}
  
  if(alarm == 1){
    if(hareket == HIGH){            //Hareketlilik var ise içerideki komutlar uygulanır.
      lcd.setCursor(0,0);
      lcd.print("                                    ");
      lcd.setCursor(0,0);
      lcd.print("Hareket Alarmi!"); 
      tone(buzzerPin, C);
      digitalWrite(7, HIGH);
      delay(1000);
      digitalWrite(7, LOW);
      noTone(buzzerPin);
      delay(1000);
      
      noTone(buzzerPin);
      alarm = 0;
    }
  }
}
