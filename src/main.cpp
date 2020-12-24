#include <Arduino.h>

const uint8_t ledPin = D4; // Equals 0x02
const uint8_t bindPin = D9;
const uint8_t numPulses = 8;

enum BIND_MODES {
  DSM2_INTERNAL_22MS = 3,
  DSM2_EXTERNAL_22MS = 4,
  DSM2_INTERNAL_11MS = 5,
  DSM2_EXTERNAL_11MS = 6,
  DSMX_INTERNAL_22MS = 7,
  DSMX_EXTERNAL_22MS = 8,
  DSMX_INTERNAL_11MS = 9,
  DSMX_EXTERNAL_11MS = 10
};

uint8_t bindMode = DSMX_INTERNAL_11MS;
char buffer[512];

void setup() {
  
  // put your setup code here, to run once:
  pinMode(bindPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(bindPin, 1);

  delay(50);

  // send out number of negative pulses to set the bind mode
  for(uint8_t p = 0; p <= bindMode; p++)
  {
    delay(50);
    digitalWrite(bindPin, 0);
    delay(50);
    digitalWrite(bindPin, 1);
  }

  delay(200);

  // start serial port (USB)
  Serial.begin(115200);
  Serial.setTimeout(10);

}

void blinkWithoutDelay(int pin, int off, int on)
{
  int blinkPhase=millis()%(off+on);
  if (blinkPhase<off) digitalWrite(pin, LOW);
  else digitalWrite(pin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  blinkWithoutDelay(ledPin, 100, 100);
  // Serial.println("Main loop...");
  uint8_t num = Serial.readBytes(buffer, 256);
  if(num > 0)
  {
    Serial.println(buffer);
  }
 //  memset(buffer, 0, sizeof(buffer));
}