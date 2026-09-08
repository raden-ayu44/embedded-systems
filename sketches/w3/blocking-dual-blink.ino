/* Blocking dual blink
 * Two LEDs meant to blink at different rates, using delay() - the naive
 * approach. Kept as a reference to compare against non-blocking-dual-blink.ino.
 */

const int led1 = 13, led2 = 32;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  digitalWrite(led1, HIGH); delay(1000);
  digitalWrite(led1, LOW);  delay(1000);
  // led1's full on/off cycle already costs 2000ms of total blocking time
  // before the processor even looks at led2.

  digitalWrite(led2, HIGH); delay(1500);
  digitalWrite(led2, LOW);  delay(1500);
  // Same problem here - led2's cycle blocks for another 3000ms before
  // control returns to the top of loop() and led1 gets touched again.
}

/* What to expect physically: led1 and led2 never overlap. led2 cannot even
 * begin until led1's two delay() calls (2000ms total) have fully finished,
 * because nothing else can run while delay() is blocking - not even a
 * check on led2's timing. The two LEDs are forced into strict sequence,
 * not real independent blinking.
 */
