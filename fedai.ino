/*

used in project construction :https://www.hackster.io/Aritro

edited and developed by: https://github.com/bymfd

This repo:https://github.com/bymfd/fedai
*/
 int IN3 = 4; 
int IN4 = 3;
int led=13;
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  pinMode (led, OUTPUT); 
  pinMode (IN3, OUTPUT);
pinMode (IN4, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("wait card...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("card UID :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("message: ");
  content.toUpperCase();
  if (content.substring(1) == "55 9E D9 E2" ) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Welcome!!!");
    Serial.println();
    asagi();
    digitalWrite (IN4, HIGH);
    Serial.println("Asagi");
    delay(5000);
    Serial.println("yukari");
    digitalWrite (IN4, LOW);
    
  }
 
 else   {
    Serial.println("invalid card");
    delay(500);
    digitalWrite (IN3, HIGH);
    delay(500);
    digitalWrite (IN3, LOW);
    delay(500);
    digitalWrite (IN3, HIGH);
    delay(500);
    digitalWrite (IN3, LOW);
    delay(500);
    digitalWrite (IN3, HIGH);
    delay(500);
    digitalWrite (IN3, LOW);
  }
}



void yukari()
{
  digitalWrite (IN4, LOW); 
digitalWrite (IN3, HIGH);
digitalWrite (led,LOW); 
delay(50);
digitalWrite (led,HIGH);
delay(1000);
digitalWrite (IN3,LOW);
digitalWrite (IN4,LOW);

} 
void asagi()
{
 digitalWrite (IN3,LOW);
digitalWrite (IN4, HIGH); 
digitalWrite (led,LOW);
delay(50); 
 digitalWrite (led,HIGH);
 delay(1000);
digitalWrite (IN4,LOW); 

}

