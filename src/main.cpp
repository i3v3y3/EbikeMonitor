#include <Arduino.h>
#include <math.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr1 = TFT_eSprite(&tft);
TFT_eSprite spr2 = TFT_eSprite(&tft);

// Define constants
const uint16_t MARKERLENGTH = 20;
const int16_t CENTER_X = 240;
const int16_t CENTER_Y = 310; // Adjusted for the bottom center of the 480x320 screen
const int16_t RADIUS = 230;
const int16_t RADIUS2 = RADIUS - MARKERLENGTH;
const float pie = 3.1415926536;

// Function declarations
void pointerdraw(float);
void Speedometer();
void batteryManagementSystem();

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  spr1.setColorDepth(8);  // Reduce color depth to save memory
  spr2.setColorDepth(8);  // Reduce color depth to save memory
  spr1.createSprite(100, 50); // Smaller sprite for battery display
  spr2.createSprite(240, 240); // Reduced sprite size to 240x240
  Speedometer();
}

void loop() {
  batteryManagementSystem();
  for (int i = 0; i <= 50; i++) {
    pointerdraw(i * pie / 50);
    delay(1000);
  }
  for (int i = 50; i >= 0; i--) {
    pointerdraw(i * pie / 50);
    delay(1000);
  }
}

void Speedometer() {
  tft.fillScreen(TFT_BLACK);
  const float ANGLE_INCREMENT = pie / 5; // 32 degrees
  const float ANGLE_INCREMENT2 = pie / 25; // 12.8 degrees
  const int LINE_WIDTH = 3;
  const int LINE_WIDTH2 = 1;

  // Draw more wide lines
  float angle2 = 0;
  for (int i = 0; i < 27; i++) {
    int16_t x1 = CENTER_X + (RADIUS - 2) * cos(angle2);
    int16_t y1 = CENTER_Y - (RADIUS - 2) * sin(angle2);
    int16_t x2 = CENTER_X + RADIUS2 * cos(angle2);
    int16_t y2 = CENTER_Y - RADIUS2 * sin(angle2);

    tft.drawWideLine(x1, y1, x2, y2, LINE_WIDTH2, TFT_WHITE, TFT_BLACK);
    angle2 += ANGLE_INCREMENT2;
  }

  // Draw wide lines
  float angle = 0;
  for (int i = 0; i < 10; i++) {
    int16_t x1 = CENTER_X + (RADIUS - 2) * cos(angle);
    int16_t y1 = CENTER_Y - (RADIUS - 2) * sin(angle);
    int16_t x2 = CENTER_X + RADIUS2 * cos(angle);
    int16_t y2 = CENTER_Y - RADIUS2 * sin(angle);

    tft.drawWideLine(x1, y1, x2, y2, LINE_WIDTH, TFT_RED, TFT_BLACK);
    angle += ANGLE_INCREMENT;
  }

  // Draw a smooth arc
  tft.drawSmoothArc(CENTER_X, CENTER_Y, RADIUS, RADIUS - 2, 90, 270, TFT_MAROON, TFT_BLACK, true);
}

void pointerdraw(float pointerAngle) {
  spr2.fillSprite(TFT_BLACK); // Clear the sprite

  int16_t local_center_x = 120; // Local center for the sprite
  int16_t local_center_y = 120;

  int16_t x1 = local_center_x + 4 * cos(pointerAngle - pie / 2);
  int16_t y1 = local_center_y - 4 * sin(pointerAngle - pie / 2);
  int16_t x2 = local_center_x + 4 * cos(pointerAngle + pie / 2);
  int16_t y2 = local_center_y - 4 * sin(pointerAngle + pie / 2);
  int16_t x3 = local_center_x + (180 - 10) * cos(pointerAngle);
  int16_t y3 = local_center_y - (180 - 10) * sin(pointerAngle);

  spr2.fillTriangle(x1, y1, x2, y2, x3, y3, TFT_GREEN);
  spr2.pushSprite(CENTER_X - 120, CENTER_Y - 120); // Adjusted push position
}

void batteryManagementSystem() {
  int x = 10;
  int y = 10;

  // Clear the sprite
  spr1.fillSprite(TFT_BLACK);

  // Create charging symbol
  spr1.fillTriangle(6, y + 4, 6, y + 16, x, y + 16, TFT_GREEN); // Charging symbol
  spr1.fillTriangle(3, y + 10, 9, y + 10, 3, y + 16, TFT_GREEN);

  // Create charging bar
  spr1.drawRect(12, y, 24, 12, TFT_WHITE);
  spr1.fillRect(36, y + 3, 3, 6, TFT_WHITE);

  // Percentage block
  spr1.fillRect(14, y + 2, 20, 8, TFT_WHITE);

  // Create percentage bar
  spr1.setTextColor(TFT_WHITE); // Set the text color to white
  spr1.setTextSize(1); // Set the text size
  spr1.setCursor(43, y + 2); // Set the cursor position
  spr1.println("100%"); // Print the text

  spr1.pushSprite(10, 10);
}
