// thereminimum code for the tiny theremin I built using a Seeed XIAO ESP32-S3 and a VLS53L1X range finder
// A few debug statements in the code, commented out.

// Library for laser range-finder (https://github.com/adafruit/Adafruit_VL53L1X)
#include "Adafruit_VL53L1X.h"
#include <Wire.h>
// just a file defining standard notes
#include "note_frequencies.h"

// A few pin definitions
#define IRQ_PIN 5
#define XSHUT_PIN 4
#define BUZZER_PIN 6

// Set up VL53L!X laser rangefinder
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

// Frequencies of autotuned notes
float fnote[] = {NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6, NOTE_C7, NOTE_D7};
int Nnotes = sizeof(fnote)/sizeof(fnote[0]);

// Define minimum and maximum distance of hand from sensor where notes are played (in mm)
const float Dmin = 20;
const float Dmax = 220;

// current (smoothed) frequency being played
float fbar;



void setup() {
  // Set up buzzer speaker
  pinMode(BUZZER_PIN, OUTPUT);
  
// For some reason, I set up I2C communications using non-standard pins
  Wire.setPins(43, 44);
  Wire.begin();
  if (! vl53.begin(0x29, &Wire)) {
    //Serial.print(F("Error on init of VL sensor: "));
    //Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  //Serial.println(F("VL53L1X sensor OK!"));

  if (! vl53.startRanging()) {
    //Serial.print(F("Couldn't start ranging: "));
    //Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  //Serial.println(F("Ranging started"));

  vl53.setTimingBudget(50);
  
  
}

void loop() {
  int16_t distance;
  float fnow;
  int inow;

  if (vl53.dataReady()) {
    // measure distance of hand from sensor
    distance = vl53.distance();
    if (distance == -1) {
      // something went wrong!
      //Serial.print(F("Couldn't get distance: "));
      //Serial.println(vl53.vl_status);
      return;
    }

    // Keep within the range we set
    if (distance > Dmax) distance = Dmax;
    if (distance < Dmin) distance = Dmin;
    

    if (distance < Dmax) {
      // figure out mapping from hand distance to frequency
      inow = Nnotes - 1 - (distance - Dmin)/(Dmax - Dmin) * (Nnotes - 1) ;
      fnow = fnote[inow];
      // Smooth a bit with previous frequncy played
      fbar = 0.1*fnow + 0.9*fbar;
      // And play the tone
      tone(BUZZER_PIN, fbar);
    } else {
      // Switch off buzzer if hand out of range
      noTone(BUZZER_PIN);
    }

    // Time for another reading
    vl53.clearInterrupt();
  }
}
