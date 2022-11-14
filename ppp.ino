//#include <ESP8266WiFi.h>
//#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27,16,2);

#define Relay D0
#define SS_PIN    D3
#define RST_PIN   D4
#define LED D8
     
MFRC522 mfrc522 (SS_PIN, RST_PIN);
String card1 = "99 08 5E D3"; 
String card2 = "04 79 2D 7A 0E 66 80";

void setup() {
    Serial.begin(9600);   // Initiate a serial communication
    SPI.begin();          // Initiate  SPI bus
    lcd.begin();
    mfrc522.PCD_Init();   // Initiate MFRC522
    
    pinMode(Relay, OUTPUT);
    pinMode(LED, OUTPUT);
    Serial.println("Tempelkan Kartu RFID");
    Serial.println();
    lcd.print("Tempelkan Kartu");
    lcd.setCursor(0,1);
    
    

    
}


void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  //Show UID on serial monitor
  Serial.print("Tag : ");
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
  Serial.print("Message : ");
  content.toUpperCase();
    if (content.substring(1) == card1) //|| (content.substring(1) == card2))
    {
      Serial.println("Authorized access");
      lcd.print("Authorized access");
      lcd.setCursor(1,1);
      digitalWrite(Relay, LOW);
      digitalWrite(LED, HIGH);
      delay(3000);
      
      digitalWrite(Relay, HIGH);
      digitalWrite(LED, LOW);
      lcd.clear();
    }

    else {
      Serial.println("Access denied");
      lcd.print("Access denied");
      lcd.setCursor(1,1);
      digitalWrite(Relay, HIGH);
      digitalWrite(LED, LOW);
      delay(2000);
      lcd.clear();
    }
}
