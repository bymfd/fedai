/*

used in project construction :https://www.hackster.io/Aritro

edited and developed by: https://github.com/bymfd

This repo:https://github.com/bymfd/fedai
*/
 int IN3 = 4; 
int IN4 = 3;
int led=13;
const int buzzer = 5; //sound feedback pins (buzzer)
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  pinMode (led, OUTPUT);//arduino led  
  pinMode (IN3, OUTPUT);//motor left pin
pinMode (IN4, OUTPUT);//motor right pin 
pinMode(buzzer, OUTPUT);
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
  if (content.substring(1) == "55 9E D9 E2" || content.substring(1) == "80 6F DF B0" || content.substring(1) == "40 48 31 A5" || content.substring(1) == "4A 41 56 D3" ) //change here the UID of the card/cards that you want to give access
  {


    Serial.println("Welcome!!!");
    valids();// card true sound 
    Serial.println();
    mdown();//unlock door 
    Serial.println("open door");
    Serial.println("ok!! door relock 5 sec...");
    delay(5000); //wait 5 seconds to enter the room
    valids();//warning to lock door
    mup();//lock door
   Serial.println("door locked");
    
  }
 
 else   {
    Serial.println("invalid card");
   invalids();//warning invalid sound
    
  }
}



void mup()//door unlock 
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
void mdown() //lock door 
{
 digitalWrite (IN3,LOW);
digitalWrite (IN4, HIGH); 
digitalWrite (led,LOW);
delay(50); 
 digitalWrite (led,HIGH);
 delay(1000);
digitalWrite (IN4,LOW); 

}
 void invalids()//invalid card sound if you want change 
 {
for(int hz = 440; hz < 1000; hz++){
    tone(buzzer, hz, 50);
    delay(5);
  } }
    
   void valids()//valid card sound
   {
     tone(buzzer,2000);
    delay(1000);
     noTone(buzzer);
     delay(500);
     
   } 

