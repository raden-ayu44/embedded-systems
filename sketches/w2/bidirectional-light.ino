/* Bidirectional light
 * Like walking-light.ino, but the direction reverses at each end (last LED
 * to first, then back) instead of wrapping. A second button reverses
 * direction immediately, wherever the light currently is. Debounce logic
 * is written once and reused for both buttons via isButtonPressed().
 */

const int ledPin[] = {32, 33, 25, 26, 27, 14, 12, 13};

const int buttonStepPin = 4;       // advances the lit position
const int buttonDirectionPin = 23; // reverses direction

const unsigned long debounceDelay = 50;

int ledNumber = 0;
int directionStep = 1; // 1 = forward (index increases), -1 = backward

int lastReadingStep = HIGH;
int buttonStateStep = HIGH;
unsigned long lastChangeTimeStep = 0;

int lastReadingDirection = HIGH;
int buttonStateDirection = HIGH;
unsigned long lastChangeTimeDirection = 0;

bool isButtonPressed(int pin, int &lastReading, int &buttonState, unsigned long &lastChangeTime) {
  // Wraps the full three-stage debounce logic so it can be reused for any
  // pin without copying the block - this is how the debounce code stays
  // written once instead of duplicated per button.
  // Parameters are passed by reference (&) so changes here persist back
  // to the caller's variables.

  int reading = digitalRead(pin);
  bool pressedEvent = false;

  if (reading != lastReading) {
    lastChangeTime = millis();
  }

  if ((millis() - lastChangeTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        pressedEvent = true;
      }
    }
  }

  lastReading = reading;
  return pressedEvent;
}

void setup() {
  Serial.begin(115200);

  for (int pin : ledPin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  pinMode(buttonStepPin, INPUT_PULLUP);
  pinMode(buttonDirectionPin, INPUT_PULLUP);

  digitalWrite(ledPin[0], HIGH);
}

void loop() {
  if (isButtonPressed(buttonStepPin, lastReadingStep, buttonStateStep, lastChangeTimeStep)) {
    digitalWrite(ledPin[ledNumber], LOW);

    ledNumber += directionStep;

    if (ledNumber > 7) {
      ledNumber = 6;
      directionStep = -1; // hit the top end, now heading back down
    } else if (ledNumber < 0) {
      ledNumber = 1;
      directionStep = 1; // hit the bottom end, now heading up again
    }

    digitalWrite(ledPin[ledNumber], HIGH);

    Serial.print("Step | active LED index: ");
    Serial.println(ledNumber);
  }

  if (isButtonPressed(buttonDirectionPin, lastReadingDirection, buttonStateDirection, lastChangeTimeDirection)) {
    directionStep = -directionStep;
    // Reverses direction instantly - doesn't touch ledNumber, so the
    // light stays where it is; only the direction of the next step changes.

    Serial.print("Direction reversed - now: ");
    Serial.println(directionStep == 1 ? "forward (1)" : "backward (-1)");
  }
}
