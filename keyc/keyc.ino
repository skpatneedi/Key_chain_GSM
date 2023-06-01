#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 11); // RX, TX pins for SIM800L module
void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.println("AT+CSQ"); // Check GSM signal strength
}
void loop() {
  if (mySerial.available()) {
    String inData = mySerial.readStringUntil('\n');
    Serial.println(inData); // Print incoming call data to serial monitor
    if (inData.indexOf("RING") >= 0) {
      digitalWrite(6, HIGH); 
      digitalWrite(7, HIGH); 
      digitalWrite(9, LOW); // Turn on the buzzer
      Serial.println("ON");}
     else if (inData.indexOf("RING") != 0||inData.indexOf("RING")<0 ){
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(9, LOW);
      Serial.println("Off");
      }   
    }
  }
