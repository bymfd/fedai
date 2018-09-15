 
#include <SPI.h>
#include <MFRC522.h>


int IN3 = 4; 
int IN4 = 3;

 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   
 
void setup() 
{
   pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("karti yanastir...");
  Serial.println();

}
void loop() 
{
  // yeni karta bak
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // birini seç
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //kart idsi
  Serial.print("kart id :");
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
  Serial.print("Durum : ");
  content.toUpperCase();
  if (content.substring(1) == "55 9E D9 E2") 
  {
    Serial.println("giris onaylandi");
    Serial.println();
    yukari();
    delay(3000);
    asagi();
  }
 
 else   {
    Serial.println("ded yalli gidi");
    Serial.println();
    delay(3000);
  }
}


void yukari()
{
  digitalWrite (IN4, LOW); 
digitalWrite (IN3, HIGH);
 
delay(50);

delay(1000);
digitalWrite (IN3,LOW);
digitalWrite (IN4,LOW);
durum=1;
} 
void asagi()
{
 digitalWrite (IN3,LOW);
digitalWrite (IN4, HIGH); 

delay(50); 
 
 delay(1000);
digitalWrite (IN4,LOW); 
durum=2;
}


