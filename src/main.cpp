#include <Arduino.h>
#include <TinyGPS++.h>
#include <math.h>

#define GPS_BAUDRATE 9600

// Function declarations
void getLocation();
void distanceCalc();

// Including the TinyGPS object
TinyGPSPlus gps;

void setup() {

  Serial.begin(9600);
  Serial2.begin(GPS_BAUDRATE);
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
    Serial.printf("Currently at: ");
    Serial.printf("%f",gps.speed.kmph());

    // Get latitude location
    Serial.printf("At: ");
    Serial.printf("%f",gps.location.lat());
    Serial.printf("lat");

    // Get longitude location
    Serial.printf("At: ");
    Serial.printf("%f",gps.location.lng());
    Serial.printf("longitude");
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