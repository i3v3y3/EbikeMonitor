#include <Arduino.h>
#include <TinyGPS++.h>
#include <math.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
TinyGPSPlus gps;
#define GPS_BAUDRATE 9600

// Function declarations
void getLocation();
void distanceCalc();
void speedometer();


void setup() {
  Serial.begin(9600);
  Serial2.begin(GPS_BAUDRATE);

 tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK); // Set the background color to black
  tft.setTextColor(TFT_WHITE); // Set the text color to white
  tft.setTextSize(2); // Set the text size
  tft.setCursor(180, 160); // Set the cursor position
  tft.println("Hello World"); // Print the text
  delay(5000);
  tft.fillScreen(TFT_BLACK);

  speedometer();
}

void loop() {
  if (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
      getLocation();
      distanceCalc();
    }
  } else {
    if (millis() > 5000 && gps.charsProcessed() < 10) {
      Serial.printf("GPS module not receiving data");
    }
  }
}

void getLocation() {
  if (gps.location.isValid() && gps.speed.isValid()) {
    // Get speed
    Serial.printf("\n\n Currently at: ");
    Serial.printf("%f",gps.speed.kmph());

      delay(2000);

    // Get latitude location
    Serial.printf("\n\n At: ");
    Serial.printf("%f",gps.location.lat());
    Serial.printf("lat");
      delay(2000);

    // Get longitude location
    Serial.printf("\n\n At: ");
    Serial.printf("%f",gps.location.lng());
    Serial.printf("longitude");
      delay(2000);
  } else {
    Serial.printf("Location and speed not found");
  }
}

void distanceCalc() {
  // This first double data will be introduced in by user
  double wantlat = 50.00;
  double wantlong = 0.00;

  // This is obtained from gps.
  double curlat = gps.location.lat();
  double curlong = gps.location.lng();

  double latt = curlat - wantlat;
  double longg = curlong - wantlong;

  double a2 = pow(latt, 2);
  double b2 = pow(longg, 2);
  double c2 = a2 + b2;

  unsigned distance = sqrt(c2);
}


void speedometer(){
//adding the sprite functions for the speedometer

tft.drawSmoothCircle(240,320,240,TFT_MAROON, TFT_BLACK);

  int16_t x, y;
  float angle = 0;
  float angleIncrement =  3.14159 / 5;; // 32 degrees
  float radius = 240;

  for (int i = 0; i <11 ; i++) {
    x = 240 + radius * cos(angle);
    y = 320 - radius * sin(angle);
    tft.drawWideLine(240,320,x,y,3,TFT_WHITE,TFT_BLACK);
    angle += angleIncrement;
  }
    int16_t a, b;
  float angle2 = 0;
  float angleIncrement2 =  3.14159 /50 ; // 6.degrees
  

  for (int i = 0; i <57 ; i++) {
    a = 240 + radius * cos(angle2);
    b = 320 - radius * sin(angle2);
    tft.drawWideLine(240,320,a,b,1,TFT_WHITE,TFT_BLACK);
    angle2 += angleIncrement2;
  }
  
  tft.fillCircle(240,320,200, TFT_BLACK);

}



