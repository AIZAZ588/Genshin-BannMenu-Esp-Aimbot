#include <SPI.h>

byte s_rec = 0;
volatile bool pin;
char receivedData[50];
int index = 0;

void setup(void) {
    Serial.begin(115200);
    pinMode(MISO, OUTPUT);
    SPCR = 0x50;  // Set SPI to mode 0 (CPOL=0, CPHA=0)

    SPI.attachInterrupt();  // Enable SPI interrupt
    sei();                  // Enable global interrupts
}

// Interrupt Service Routine (ISR)
ISR(SPI_STC_vect) {
    s_rec = SPDR;  // Read byte from SPI Data Register
    pin = true;
}

void loop(void) {
    if (pin) {
        receivedData[index++] = s_rec;  // Store the received byte
        pin = false;

        if (s_rec == '\n') {  // Check for end of message
            receivedData[index] = '\0';  // Null-terminate the string
            Serial.println(receivedData);  // Print the received message
            index = 0;  // Reset index for next message
        }
    }
    delay(50);
}
