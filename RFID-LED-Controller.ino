#include <FastLED.h>
#include <SPI.h>
#include <MFRC522.h>

// LED 
#define LED_PIN 6
#define NUM_LEDS 60
#define BRIGHTNESS 128

CRGB leds[NUM_LEDS];

// RFID 
#define SS_PIN 10
#define RST_PIN 7

MFRC522 rfid(SS_PIN, RST_PIN);

//ON and OFF tracking
bool lightsOn = false;
CRGB currentColor = CRGB::Black;

//COMBO TRACKING
String lastUid = "";
unsigned long lastScanTime = 0;
const unsigned long mixWindow = 3000; // 3 SECONDS


// SETUP 
void setup() {
  Serial.begin(115200);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  SPI.begin();
  rfid.PCD_Init();

  Serial.println("Scan a card...");
}

// LOOP
void loop() {

  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  // Convert UID to string
  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  uid.toUpperCase();  // important

  Serial.print("UID: ");
  Serial.println(uid);


  //setting a "current scan time" for mixing
  unsigned long currentScanTime = millis();

  // Defaulting two cards for mixing
  String RED_UID_mix = "66A29C1E";
  String BLUE_UID_mix = "C4A9D1E";

  // A3989C1E = RED
  // C5D9C1E = BLUE
  // B75C9D1E = GREEN
  // BLUE MIXed FIRST (C4A) THEN RED MIX(66A) = PURP


  if(uid == RED_UID_mix && lastUid == BLUE_UID_mix && currentScanTime - lastScanTime <= mixWindow){
    handleColorCard(CRGB::Purple);
    Serial.println("Mixed color: Purple");
  } else if (uid == RED_UID_mix) {
    handleColorCard(CRGB::Red); 
  } else if (uid == BLUE_UID_mix){
    handleColorCard(CRGB::Blue);
  } else if (uid == "A3989C1E") {
    handleColorCard(CRGB::Red);  // RED
  } else if(uid == "C5D9C1E") {
    handleColorCard(CRGB::Blue); // BLUE
  } else if(uid == "B75C9D1E"){
    handleColorCard(CRGB::Green); //GREEN
  } else {
    Serial.println("unknown card");
  }

  lastUid = uid;
  lastScanTime = currentScanTime;

  delay(1000);
  rfid.PICC_HaltA();
}

//TRIGGERING ON AND OFF
void handleColorCard(CRGB color){
  if(lightsOn && currentColor == color){
    turnOff();
  } else {
    currentColor = color;
    lightsOn = true;
    setColor(color);
  }
}

// Turning off all LEDS
void turnOff(){
  lightsOn = false;
  FastLED.clear();
  FastLED.show();
}

// Set Color Function
void setColor(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
}
