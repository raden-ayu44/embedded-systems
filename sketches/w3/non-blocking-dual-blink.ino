/* Non-blocking dual blink
 * Same intent as blocking-dual-blink.ino - two LEDs blinking at different
 * rates - but written so neither LED ever waits on the other.
 */

const int led1 = 13, led2 = 32;
const unsigned long period1 = 1000, period2 = 1500;

unsigned long prev1 = 0, prev2 = 0;
bool state1 = LOW, state2 = LOW;
// Two full sets of state variables - one per LED. Each pair is completely
// independent; neither knows or cares that the other exists.

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  // Read the clock once per pass and reuse it for both checks below,
  // rather than calling millis() twice.

  if (now - prev1 >= period1) {
    prev1 = now;
    state1 = !state1;
    digitalWrite(led1, state1);
  }
  // Exact same non-blocking pattern used throughout the previous sketch
  // set (see non-blocking-blink.ino) - just applied to led1's own timer.

  if (now - prev2 >= period2) {
    prev2 = now;
    state2 = !state2;
    digitalWrite(led2, state2);
  }
  // Identical pattern again, independently, for led2. Adding a second
  // periodic task cost four lines, not a redesign.
}

/* What to expect physically: the two LEDs blink on their own schedules,
 * with no forced sequencing. Because 1000ms and 1500ms share a common
 * multiple of 3000ms, the two cycles realign every 3 seconds - sometimes
 * landing both ON, sometimes both OFF, purely as a byproduct of the math,
 * not because either LED is aware of the other.
 */
