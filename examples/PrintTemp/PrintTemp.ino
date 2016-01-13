#include <Wire.h>
#include <TPA81.h>

// Create new TPA81 instance
TPA81 tpa;

void setup() {
  Serial.begin(9600);

  // You need to begin the Wire library to use TPA81 library
  Wire.begin();
}

void loop() {
  // Print temperature light
  Serial.print(tpa.getAmbient());
  Serial.print(" ");

  // Print all temperature point
  for (int i = 1; i <= 8; i++)
  {
    Serial.print(tpa.getPoint(i));
    Serial.print(" ");
  }
  Serial.println("\n");
  
  delay(500);
}
