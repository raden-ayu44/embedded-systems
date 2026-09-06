/* Debounced button
 * Same idea as bounce-demo.ino, but the reading is only trusted once it has
 * held steady for debounceDelay - fixing the false-toggle problem.
 */

const int ledPin = 13;
const int buttonPin = 19;
const unsigned long debounceDelay = 50; // ms

bool ledState = LOW;
int lastReading = HIGH;   // raw pin value from the previous loop pass
int buttonState = HIGH;   // the value we've decided to trust
unsigned long lastChangeTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Any raw change at all restarts the settling clock.
  if (reading != lastReading) {
    lastChangeTime = millis();
  }

  // Only proceed once the reading has been stable long enough to trust.
  if (millis() - lastChangeTime > debounceDelay) {
    if (reading != buttonState) {
      // A genuine, settled change - not just a raw flicker.
      buttonState = reading;

      if (buttonState == LOW) {
        // Act on the press edge only (falling edge), not the release.
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
        Serial.println("toggle");
      }
    }
  }

  lastReading = reading;
}

/* Why two state variables instead of one:
 * - lastReading: the raw pin value, updated every pass, used only to
 *   detect "did anything just flicker" and reset the settling clock.
 * - buttonState: the value we actually trust, updated only after it has
 *   held steady past debounceDelay.
 *
 * Common mistake: drop the "if (reading != buttonState)" check and the
 * code looks fine at first - until the button is held down. Then it
 * toggles on every loop pass for as long as it's held, because
 * lastChangeTime stops updating once the reading is steady, so the
 * "stable long enough" condition stays true continuously.
 */
