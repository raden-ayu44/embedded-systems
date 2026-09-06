# Notes — Debounced Button

## Line-by-line

```cpp
const unsigned long debounceDelay = 50; // ms
```
The settling time required before a reading is trusted. 50ms is chosen because mechanical bounce usually lasts only 1-10ms, so 50ms is comfortably longer than the chatter, but still far faster than a human press.

```cpp
int lastReading = HIGH;
```
The raw pin value from the previous pass. Used only to detect "did the reading just change" - not trusted as the actual button state.

```cpp
int buttonState = HIGH;
```
The value that's actually trusted, updated only after debounce confirms it's genuine. This is the piece missing from `bounce-demo.ino` - the difference between:
- `lastReading`: "what was just read, raw"
- `buttonState`: "what we believe is actually true, once it's settled"

```cpp
unsigned long lastChangeTime = 0;
```
When the raw reading last changed - the reference point for measuring "how long has it been quiet."

```cpp
pinMode(buttonPin, INPUT_PULLUP);
```
Enables the internal pull-up so the pin idles at HIGH (pulled to 3.3V) when the button isn't pressed. Pressing connects the pin straight to GND, reading LOW. Without this, the pin would float - picking up noise instead of a clean, stable value when not pressed.

```cpp
if (reading != lastReading) {
  lastChangeTime = millis();
}
```
Any raw change at all - bounce or a genuine press/release, we don't know which yet - resets the settling clock.

```cpp
if (millis() - lastChangeTime > debounceDelay) {
```
Only once more than 50ms has passed since the last raw change is the signal considered quiet enough to trust.

```cpp
  if (reading != buttonState) {
    buttonState = reading;
```
And only if this settled value differs from what was previously trusted is this a genuine change - update `buttonState` to reflect it.

```cpp
    if (buttonState == LOW) {
```
Act only on the falling edge (transition to LOW - the moment of pressing), not on release. This keeps exactly one action per press instead of two (one on press, one on release).

## Why two state variables, not one

If there were only one variable (as in `bounce-demo.ino`), it would "chase" the raw reading within microseconds - far faster than the 50ms wait. By the time 50ms has passed, that comparison variable has already updated to match the new reading, so the "did this genuinely change" check always fails. A second variable that deliberately updates late - only after confirmed stability - is what makes the comparison meaningful.

## The most common mistake

Remove the `if (reading != buttonState)` check, and the code appears to work - until the button is held down. Because `lastChangeTime` stops updating once the reading is steady, the "stable long enough" condition stays true continuously, so the LED toggles on every single loop pass for as long as the button is held.

## Questions worth answering

1. **What does `millis()` return, and why compare a time difference rather than counting loop passes?** `millis()` returns milliseconds since boot. Counting loop passes isn't reliable because loop speed isn't constant - it depends on whatever else runs each pass.
2. **A hardware debouncing method, and when it's preferred?** An RC filter or Schmitt trigger on the line. Preferred when the edge itself has to drive an interrupt or a safety-critical function, since it needs no CPU time and reacts immediately.
3. **Why react on the falling edge (LOW) rather than on release?** So one press produces exactly one action, matching the usual convention that a button's action happens on press, not release.
