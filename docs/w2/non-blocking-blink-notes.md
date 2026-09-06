# Notes — Non-blocking Blink

## Line-by-line

```cpp
const unsigned long interval = 500; // ms
```
`interval` is the variable name; its value is 500 (milliseconds) - the gap between blinks. `unsigned` means this type can only hold non-negative numbers. `long` is a data type for large whole numbers (at least 32 bits) - it isn't itself "a variable," it's the type of the variable.

```cpp
unsigned long previousMillis = 0;
```
Stores exactly when (in milliseconds since boot) the LED last changed state. It's a reference point for the comparison in `loop()`, not a stored duration.

```cpp
pinMode(ledPin, OUTPUT);
```
This sets the pin's **direction** (it will drive a signal out), not its voltage. The actual HIGH/LOW value is decided later by `digitalWrite()` - `pinMode` alone doesn't push any voltage.

```cpp
void loop() {
  unsigned long now = millis();
  if (now - previousMillis >= interval) {
```
Every pass, ask the same question: has 500ms passed since the last toggle? If not, skip the block entirely and fall through - `loop()` doesn't pause or wait, it just checks very quickly, over and over, until the condition is true.

```cpp
    previousMillis = now;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
```
Three things happen once the interval has elapsed: the reference time resets to now; `ledState` flips from whatever it currently is (not set to a fixed value - toggled); and `digitalWrite()` is what actually changes the physical pin's voltage - the line above it only changes a variable in memory.

## Narrative

Because there's no `delay()` anywhere, one pass of `loop()` finishes in microseconds whenever the interval hasn't elapsed yet. That's what makes this pattern non-blocking: even if other work gets added later (reading a sensor, checking a button), it still gets to run thousands of times a second, never blocked waiting on the blink.

## Questions worth answering

1. **What would change if the if-block were replaced with `digitalWrite(HIGH); delay(500); digitalWrite(LOW); delay(500);`?** The processor would sit completely idle for 500ms at a time, unable to read a button, respond on serial, or do anything else during that window.
2. **`previousMillis` is `unsigned long` - what happens after about 49 days?** `millis()` wraps back to 0 after roughly 49.7 days. Because `now - previousMillis` is unsigned arithmetic, the subtraction still comes out correct across that wraparound, so the comparison keeps working without any special handling.
