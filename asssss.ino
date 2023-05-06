#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 2);
int a;
int l;
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
void setup() {
  Serial.begin(115200);
  Serial.println("NodeMCU USB serial initialize");
  mySerial.begin(9600);
  Serial.println("SIM800L serial initialize");

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CBC"); //Battery
  updateSerial();
  pinMode(13, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  // put your setup code here, to run once:
}

void loop() {
  a=digitalRead(13)+digitalRead(12)+digitalRead(14);
  if (a!=l){
 switch(a){
   case 3:
   digitalWrite(4, LOW);
   Serial.println("0");
   break;
   case 2:
   Serial.println("33");
   digitalWrite(4, LOW);
  mySerial.println("AT+CMGS=\"+639673190911\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Water level is 33%"); //text content
  updateSerial();
   break;
   case 1:
  digitalWrite(4, LOW);
  Serial.println("Water level is 66");
  mySerial.println("AT+CMGS=\"+639673190911\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Water level is 66%"); //text content
   break;
   case 0:
  digitalWrite(4, HIGH);
  Serial.println("99");
  mySerial.println("AT+CMGS=\"+639673190911\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("Water level is 99%"); //text content
  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
   mySerial.println("ATD+ +639673190911"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(10000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();
   break;
 }
  }
 l=a;

  updateSerial();
}
