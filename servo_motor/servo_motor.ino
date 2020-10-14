//Servo motor çalışması  için gerekli kütüphane dosyasını ekledik.
#include<Servo.h>
Servo motor; //motor adında bir servo nesnesi oluşturduk.
void setup() {
motor.attach(9); // Servo motorun data pinini arduino 3 numaralı 
//pine bağladığımızı belirttik.
}
void loop() {
motor.write(90); // Servo motora açı değeri olarak 90 dereceye döndürdük.
}
