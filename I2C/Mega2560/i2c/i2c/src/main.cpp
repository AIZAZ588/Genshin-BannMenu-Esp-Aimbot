#include <Arduino.h>
#include <Wire.h>

#define address 0x55 // 7-bit slave address

void receiveEvent(int bytes) {
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);  // Print received character
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Wire.begin(address);  // Join I2C bus as slave
  Wire.onReceive(receiveEvent);  // Register receive event
  Serial.println("Slave is ready");
}

void loop() {
  // Main loop can be left empty as the receiveEvent function handles incoming data
}
