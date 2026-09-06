/* Walking light
 * Exactly one LED out of eight is lit at a time. Each debounced button
 * press advances the lit LED by one position, wrapping from the last
 * LED back to the first.
 */

const int ledPin[] = {32, 33, 25, 26, 27, 14, 12, 13};
// Order must match the physical layout on the breadboard (index 0 = LED 1).

const int buttonPin = 4;
const unsigned long debounceDelay = 50;

int lastReading = HIGH;
int buttonState = HIGH;
unsigned long lastChangeTime = 0;

int ledNumber = 0;
// Index of the LED currently lit (0-7). Not const - it has to change on
// every valid press. Starts at 0 so ledPin[0] is the starting LED.

void setup() {
  Serial.begin(115200);

  for (int pin : ledPin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // LOW = off (normal, non-inverted wiring)
  }

  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(ledPin[0], HIGH);
  // Light the first LED before loop() ever runs - this is the required
  // starting state, not something that happens after the first press.
  // NOTE: if your LEDs are wired inverted, flip every HIGH/LOW pair in
  // this file for "on" and "off" to mean the right thing physically.
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastChangeTime = millis();
  }

  if (millis() - lastChangeTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        digitalWrite(ledPin[ledNumber], LOW);  // turn off the old position

        ledNumber++;
        if (ledNumber >= 8) {
          ledNumber = 0; // wrap back to the first LED
        }

        digitalWrite(ledPin[ledNumber], HIGH); // turn on the new position

        Serial.println("toggle");
      }
    }
  }

  lastReading = reading;
}

/* Note on approach: this does NOT use a boolean "toggle" the way the
 * debounce examples do. There, flipping between exactly two states makes
 * sense. Here, the action is "move to a specific position" - the old LED
 * is always turned off and the new one is always turned on explicitly,
 * which is why ledNumber is an int index rather than a bool.
 *
 * Order matters: the old LED must be turned off using ledNumber BEFORE
 * it's incremented. Do it after, and you lose track of which LED needs
 * to be turned off.
 */
