/* Bounce demo (before fix)
 * Deliberately not debounced - toggles the LED on every raw signal change,
 * so a single physical press can register as several toggles. Used to see
 * the bounce problem before fixing it in debounced-button.ino.
 */

const int ledPin = 13;
const int buttonPin = 19;
bool ledState = LOW;
int lastReading = HIGH; // idle HIGH, pressed LOW (INPUT_PULLUP)

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastReading && reading == LOW) {
    // Trusts every raw change to LOW immediately, with no settling time.
    // If the mechanical contact chatters a few times within milliseconds,
    // each chatter that happens to read LOW counts as a separate press.
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Serial.println("toggle");
  }

  lastReading = reading;
}

/* Try this: press the button exactly 10 times and count the "toggle"
 * lines in the serial monitor. It will almost always be more than 10 -
 * that's contact bounce, and it's the reason debounced-button.ino exists.
 */
