/* ------------------------------------------------------------------------
   Created by: Tauseef Ahmad
   Created on: 2 May, 2022

   Tutorial: https://youtu.be/M9Sci4nsTEk
   ------------------------------------------------------------------------*/

#include <SoftwareSerial.h>

#define rxPin 13
#define txPin 12
SoftwareSerial sim800L(rxPin, txPin);

String buff = "";
void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM800L
  sim800L.begin(9600);

  Serial.println("Initializing...");

  sim800L.println("AT");
  waitForResponse();

  sim800L.println("ATE1");
  waitForResponse();

  sim800L.println("AT+CMGF=1");
  waitForResponse();

  sim800L.println("AT+CNMI=1,2,0,0,0");
  waitForResponse();
  sim800L.println("AT+CMGL=\"REC UNREAD\""); // Read unread messages
  waitForResponse();
  sim800L.println("AT+CMGDA=\"DEL ALL\"");
  waitForResponse();
  Serial.println("Ready to receive Commands..");
  pinMode(4, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  while (sim800L.available()) { 
    buff = sim800L.readString();
    Serial.println(buff);
    Serial.println(buff.length());
    buff.trim();
    Serial.println(buff);
  }
  if (buff == "RING") {
    digitalWrite(4, HIGH); 
    digitalWrite(9, LOW);
  }
  else{
    digitalWrite(4, LOW);
    digitalWrite(9, LOW);
  }
}

void send_sms() {
  sim800L.print("AT+CMGS=\"+918754470664\"\r");
  waitForResponse();

  sim800L.print("Hello from SIM800L");
  sim800L.write(0x1A);
  waitForResponse();
}


void make_call() {
  sim800L.println("ATD+918754470564;");
  waitForResponse();
}

void waitForResponse() {
  delay(1000);
  while (sim800L.available()) {
    Serial.println(sim800L.readString());
  }
  sim800L.read();
}
