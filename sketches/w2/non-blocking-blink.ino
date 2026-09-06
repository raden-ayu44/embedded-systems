/* Non-blocking blink
 * Blinks an LED on a fixed interval without ever calling delay() in loop().
 */

const int ledPin = 13;
const unsigned long interval = 500; // ms
unsigned long previousMillis = 0;
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Serial.println("Non-blocking blink running.");
}

void loop() {
  unsigned long now = millis();

  if (now - previousMillis >= interval) {
    previousMillis = now;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Serial.print("LED -> ");
    Serial.println(ledState ? "ON" : "OFF");
  }

  // loop() keeps running either way. Anything else added here still gets
  // to execute, whether or not the interval has elapsed this pass.
}
