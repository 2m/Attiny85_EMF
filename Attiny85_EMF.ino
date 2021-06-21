// EMF Detector Attiny85 and 4 led v1.0
// 23.10.2015
// original code/project by Aaron ALAI - aaronalai1@gmail.com
// modified for use by Giovanni Gentile - giovanni@0lab.it
//              Attiny 85
//                ____
//       Reset  -      - vcc+
//          led -      - led
//  4Moh + ante -      - led
//          GND -      - led
//
// Put the 4 Mohm resistor to pin 3 and GND and put antenna

#define NUMREADINGS 15 // Number of readings

int senseLimit = 15; // raise this num to decrease sensitivity
int val = 0;
int antenna = A2;

int LED[] = {2, 0, 1, 3};

// Variables for smoothing
int readings[NUMREADINGS];
int index = 0;
int total = 0;
int averange = 0;

void setup() {

  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(A2, INPUT);

  // Test leds
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], HIGH);
    delay(500);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(LED[i], LOW);
  }

  // Initialize all the readings
  for (int i = 0; i < NUMREADINGS; i++) {
    readings[i] = 0;
  }
}

void loop() {
  int val = analogRead(antenna);

  if (val >= 1) {

    val = constrain(val, 1, senseLimit); // turn any readings higher than the senseLimit into the senseLmit value
    val = map(val, 1, senseLimit, 1, 1023); // remap the values

    total -= readings[index]; // subtract the last reading
    readings[index] = val;    // read from the sensor
    total += readings[index]; // add the reading to the total
    index = (index + 1);      // advance to the next index

    if (index >= NUMREADINGS)
      index = 0;

    averange = total / NUMREADINGS;

    if (averange > 50) {
      digitalWrite(2, HIGH);
    }
    else {
      digitalWrite(2, LOW);
    }

    if (averange > 350) {
      digitalWrite(0, HIGH);
    }
    else {
      digitalWrite(0, LOW);
    }

    if (averange > 750) {
      digitalWrite(1, HIGH);
    }
    else {
      digitalWrite(1, LOW);
    }

    if (averange > 950) {
      digitalWrite(3, HIGH);
    }
    else {
      digitalWrite(3, LOW);
    }
  }
}
