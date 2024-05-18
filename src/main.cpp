#include <Arduino.h>
#include <math.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);


 // Define constants
const uint16_t MARKERLENGTH = 20;
const int16_t CENTER_X = TFT_HEIGHT/2;
const int16_t CENTER_Y = TFT_WIDTH-10;
const int16_t RADIUS = TFT_WIDTH/2;
const int16_t RADIUS2 = RADIUS-MARKERLENGTH;
const float pie = 3.1415926536;

// Function declarations

void speedometer();
void drawPointer(float);
void drawPointerPrev(float);

void setup() {
  Serial.begin(9600);

  // Set the RX and TX pins for the GPS module


  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK); // Set the background color to black
  tft.setTextColor(TFT_WHITE); // Set the text color to white
  tft.setTextSize(2); // Set the text size
  tft.setCursor(180, 160); // Set the cursor position
  tft.println("Hello World"); // Print the text
  delay(10);
  tft.fillScreen(TFT_BLACK);

  speedometer();
  drawPointer(pie/12);
 

}

void loop() {
for(int i = 0; i< 100; i++)
{
drawPointer(i*pie/100);
delay(10);
}
for(int i = 100; i> 0; i--)
{
drawPointer(i*pie/100);
delay(10);
}
}


void speedometer(){
//adding the sprite functions for the speedometer
const float ANGLE_INCREMENT = pie / 5; // 32 degrees
const float ANGLE_INCREMENT2 = pie / 25; // 12.8 degrees
const int LINE_WIDTH = 3;
const int LINE_WIDTH2 = 1;


  // Draw more wide lines
 float angle2 = 0;
  for (int i = 0; i < 27; i++) {
    int16_t x1 = CENTER_X + (RADIUS-2) * cos(angle2);
    int16_t y1 = CENTER_Y - (RADIUS-2) * sin(angle2);
    int16_t x2 = CENTER_X + (RADIUS2) * cos(angle2);
    int16_t y2 = CENTER_Y - (RADIUS2) * sin(angle2);

    tft.drawWideLine(x1, y1, x2, y2, LINE_WIDTH2, TFT_WHITE, TFT_BLACK);
    angle2 += ANGLE_INCREMENT2;
  }
//Draw wide lines
  float angle = 0;
  for (int i = 0; i < 10; i++) {
    //drawshort lines
    int16_t x1 = CENTER_X + (RADIUS-2) * cos(angle);
    int16_t y1 = CENTER_Y - (RADIUS-2) * sin(angle);
    int16_t x2 = CENTER_X + (RADIUS2) * cos(angle);
    int16_t y2 = CENTER_Y - (RADIUS2) * sin(angle);
    tft.drawWideLine(x1, y1, x2, y2,LINE_WIDTH, TFT_RED, TFT_BLACK);
    
    angle += ANGLE_INCREMENT;
    }
  // Draw a smooth circle
  //  tft.drawSmoothCircle(CENTER_X, CENTER_Y, RADIUS, TFT_MAROON, TFT_BLACK);
  tft.drawSmoothArc(CENTER_X,CENTER_Y,RADIUS,RADIUS-2,90,270,TFT_MAROON,TFT_BLACK,true);
  
  


}
void drawPointer(float pointerAngle)
{
  // float pointerAngle = 4*pie / 5;
  int16_t x1 = CENTER_X + 4 * cos(pointerAngle-pie/2);
  int16_t y1 = CENTER_Y - 4 * sin(pointerAngle-pie/2);
  int16_t x2 = CENTER_X + 4 * cos(pointerAngle+pie/2);
  int16_t y2 = CENTER_Y - 4 * sin(pointerAngle+pie/2);
  int16_t x3 = CENTER_X + (RADIUS2-10) * cos(pointerAngle);
  int16_t y3 = CENTER_Y - (RADIUS2-10) * sin(pointerAngle);
   tft.fillCircle(CENTER_X,CENTER_Y,RADIUS2 - 8,TFT_BLACK);
   tft.fillTriangle(x1,y1,x2,y2,x3,y3,TFT_GREEN);
}
// void drawPointerPrev(float pointerAngle)
// {
//   // float pointerAngle = 4*pie / 5;
//   int16_t x1 = CENTER_X + 8 * cos(pointerAngle-pie/2);
//   int16_t y1 = CENTER_Y - 8 * sin(pointerAngle-pie/2);
//   int16_t x2 = CENTER_X + 8 * cos(pointerAngle+pie/2);
//   int16_t y2 = CENTER_Y - 8 * sin(pointerAngle+pie/2);
//   int16_t x3 = CENTER_X + (RADIUS2-10) * cos(pointerAngle);
//   int16_t y3 = CENTER_Y - (RADIUS2-10) * sin(pointerAngle);
//   //  tft.fillCircle(CENTER_X,CENTER_Y,RADIUS2 - 8,TFT_BLACK);
//    tft.fillTriangle(x1,y1,x2,y2,x3,y3,TFT_BLACK);
// }
