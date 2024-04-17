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
void timedate();


void setup() {
  Serial.begin(9600);

  // Set the RX and TX pins for the GPS module
  Serial2.begin(GPS_BAUDRATE, SERIAL_8N1,19,21);

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
      timedate();
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
// Define constants
const int16_t CENTER_X = 240;
const int16_t CENTER_Y = 320;
const int16_t RADIUS = 240;
const float pie = 3.14159;
const float ANGLE_INCREMENT = pie / 5; // 32 degrees
const float ANGLE_INCREMENT2 = pie / 25; // 12.8 degrees
const int LINE_WIDTH = 3;
const int LINE_WIDTH2 = 1;

  // Draw a smooth circle
 tft.drawSmoothCircle(CENTER_X, CENTER_Y, RADIUS, TFT_MAROON, TFT_BLACK);
  // Draw more wide lines
 float angle2 = 0;
  for (int i = 0; i < 27; i++) {
    int16_t a = CENTER_X + RADIUS * cos(angle2);
    int16_t b = CENTER_Y - RADIUS * sin(angle2);
    int16_t rounded_a = round(a);
    int16_t rounded_b = round(b);
    tft.drawWideLine(CENTER_X, CENTER_Y, rounded_a, rounded_b, LINE_WIDTH2, TFT_WHITE, TFT_BLACK);
    angle2 += ANGLE_INCREMENT2;
  }
//Draw wide lines
  float angle = 0;
  for (int i = 0; i < 10; i++) {
    int16_t x = CENTER_X + RADIUS * cos(angle);
    int16_t y = CENTER_Y - RADIUS * sin(angle);
    int16_t rounded_x = round(x);
    int16_t rounded_y = round(y);
    tft.drawWideLine(CENTER_X, CENTER_Y, rounded_x, rounded_y,LINE_WIDTH, TFT_RED, TFT_BLACK);
    
    angle += ANGLE_INCREMENT;
    }

  // Fill the center of the circle
  tft.fillCircle(CENTER_X, CENTER_Y, RADIUS - 20, TFT_BLACK);

  // Draw a black circle as the background
  tft.fillCircle(CENTER_X, CENTER_Y, RADIUS - 20, TFT_BLACK);

  // Define the gradient colors
  uint16_t color1 = tft.color565(255, 0, 0); // red
  uint16_t color2 = tft.color565(0, 0, 0);   // black

  // Calculate the step size for the gradient
  float step = 255.0 / (RADIUS - 20);

  // Draw the radial gradient
  for (int16_t r = RADIUS - 20; r > 0; r--) {
    uint8_t red = 255 - (r * step);
    uint8_t green = 0;
    uint8_t blue = 0;
    uint16_t color = tft.color565(red, green, blue);
    tft.drawCircle(CENTER_X, CENTER_Y, r, color);
  }
}

  void timedate (){
// getting and displaying time 
  if (gps.date.isValid()&& gps.time.isValid() && gps.date.isUpdated() && gps.time.isUpdated()){
    
    spr.createSprite(100, 50, 8);
    spr.fillSprite( TFT_BLACK);
  
    spr.drawRoundRect(10,10,80,30,3,TFT_MAROON);
    spr.setTextColor(TFT_WHITE);
    spr.setCursor(10,10,2);
    spr.print(gps.date.day());
    spr.print("/");
    spr.print(gps.date.month());
    spr.print("/");
    spr.println(gps.date.year());

    spr.setCursor(25,10,2);
    spr.print(gps.time.hour());
    spr.print(":");
    spr.print(gps.time.minute());

    spr.pushSprite(0,0);
  }
  else{
    Serial.println("DATE AND TIME UNAVAILABLE");
    
  }
  }









