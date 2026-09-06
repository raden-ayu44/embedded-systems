/* Week 1 - Board verification sketch
 * Confirms the toolchain works end to end: reports chip info over serial,
 * then blinks the onboard LED without ever calling delay() in loop().
 */

const int ledPin = 2;
// Onboard LED pin. Different from the other sketches in this repo (which use
// pin 13 for an external LED) - most ESP32 dev boards wire their onboard LED
// to GPIO 2.

const unsigned long interval = 500; // ms
unsigned long previousMillis = 0;
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  delay(200);
  // The one deliberate exception to "never use delay()" in this whole repo.
  // This runs once in setup(), not in loop(), so it doesn't block the main
  // loop at all. It just gives the USB-to-serial bridge a moment to settle
  // before the first print, so the opening lines aren't lost.

  pinMode(ledPin, OUTPUT);

  Serial.println();
  Serial.println("=== board verification ===");

  Serial.printf("Chip model     : %s\n", ESP.getChipModel());
  Serial.printf("Chip revision  : %d\n", ESP.getChipRevision());
  Serial.printf("CPU cores      : %d\n", ESP.getChipCores());
  Serial.printf("CPU frequency  : %lu MHz\n", (unsigned long)getCpuFrequencyMhz());
  Serial.printf("Flash size     : %lu bytes\n", (unsigned long)ESP.getFlashChipSize());
  Serial.printf("Free heap      : %lu bytes\n", (unsigned long)ESP.getFreeHeap());
  Serial.printf("Core version   : %s\n", ESP_ARDUINO_VERSION_STR);
  // Serial.printf() lets a format string carry placeholders (%s for text,
  // %d for a plain int, %lu for an unsigned long) instead of chaining
  // print()/println() calls. Some values are cast to (unsigned long) first
  // so their type matches the %lu placeholder exactly.

  Serial.println("If you can read this, the toolchain works.");
}

void loop() {
  unsigned long now = millis();
  if (now - previousMillis >= interval) {
    previousMillis = now;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}
