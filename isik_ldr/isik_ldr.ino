#define led 3                       // 3.Pinde LED olduğunu tanımlıyoruz


void setup() {
  pinMode(led,OUTPUT);              // Led dijital olarak kullanacağımız için çıkış tanımlaması yapılmalıdır.
  Serial.begin(9600);
}

void loop() {
   int Deger = analogRead(A0);      // Deger isimli bir değişken tanımlıyoruz. Bu değişken A0 Analog Pininden gelen veriyi tutacak.
   Serial.println(Deger);
  

    if(Deger <= 15)                  // analogRead ile Deger değişkenine gelen veri 15'ten küçük ise LED yanmayacak.
      {
        digitalWrite(led,HIGH);
      }
    
    else                             // analogRead ile Deger değişkenine gelen veri 15'ten büyük ise LED yanacak.
      {
        digitalWrite(led,LOW);
      }
}
