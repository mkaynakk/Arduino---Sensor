int pirPin = 8;                   //Sensörü takacağımız pin
int servoPin = 9;                 //Servoyu takacağımız pin
int hareket;                      //Sensörden aldığımız veri
int buzzerPin = 12;
int C = 262;
int deger = 0;
void setup() {
  pinMode(pirPin, INPUT);         //Sensör pinimizi giriş olarak ayarlyoruz.
Serial.begin(9600);
}

void loop() {
  hareket = digitalRead(pirPin);  //Sensörden okuma yapıyoruz.
  deger = digitalRead(pirPin); // Dijital pin okunuyor
Serial.println(deger); 
  if(hareket == HIGH){            //Hareketlilik var ise içerideki komutlar uygulanır.

  
    tone(buzzerPin, C);
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    noTone(buzzerPin);
    delay(1000);
  
  noTone(buzzerPin);
  }
  
  }
