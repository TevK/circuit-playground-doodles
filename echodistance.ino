#include <Adafruit_CircuitPlayground.h>

#define ECHO_PIN 6    // Echo Pin on HR-S04
#define TRIG_PIN 12    // Trigger Pin on HR-S04
#define YELLOW 255    // Value of Green (in RGB) to make NeoPixel look yellow
#define MAX_RANGE 200 // Maximum allowed sensor distance (in cm)
#define MIN_RANGE 0   // Minimum allowed sensor distance (in cm) -- note sensor is not capable of reading 0 cm

long pulseLength_us; // pulseLength_us of pulse length (in microseconds)
long distance_cm;    // Calculated distance of reported object (in centimeters)

/* Note than an int (16 bits) is large enough to hold the maximum color_value (51000 when MAX_RANGE = 200
   but if MAX_RANGE is significantly larger (over 257) then a larger variable may be needed) */
int color_value;     // Used to vary NeoPixel color from yellow (255) to red (0)
int threshold = 10;
int red = 0;
int maxrange = threshold * 11;

void setup() {
  CircuitPlayground.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  /* The following TRIG_PIN/ECHO_PIN cycle is used to determine the
    distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);
  pulseLength_us = pulseIn(ECHO_PIN, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance_cm = pulseLength_us / 58.2;

  if (distance_cm < maxrange || distance_cm > MIN_RANGE) {
    for (int i = 0; i < 10; i++) {
      if ((maxrange - distance_cm) > threshold * (i + 1)) {
        red = 255;
      } else {
        red = 0;
      }
      CircuitPlayground.setPixelColor(i , red, 0, 0);
    }
  }

  //Delay 50ms before next reading.
  delay(50);
}

