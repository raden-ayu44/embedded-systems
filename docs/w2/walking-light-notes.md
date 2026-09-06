# Notes — Walking Light

## Line-by-line

```cpp
const int ledPin[] = {32, 33, 25, 26, 27, 14, 12, 13};
```
Eight LED pins as an array. Order must match the physical layout on the breadboard (index 0 = first LED, etc.) - if it doesn't, the LEDs still light up in sequence, but visually the "walking" order looks scrambled rather than sequential.

```cpp
int ledNumber = 0;
```
Index of the LED currently lit (0-7). Must not be `const` - it has to change on every valid press. This replaces the boolean `ledState` used in the debounce examples, because this sketch needs to represent a **position** among 8 options, not just two states (on/off).

```cpp
digitalWrite(pin, LOW); // LOW = off (normal, non-inverted wiring)
...
digitalWrite(ledPin[0], HIGH); // on
```
Light the first LED before `loop()` ever runs at all - this is the required starting state ("exactly one LED lit, starting at LED 1"), not something that only happens after the first press. Whether HIGH means "on" depends entirely on how the LED is physically wired - check polarity before assuming.

```cpp
if (buttonState == LOW) {
  digitalWrite(ledPin[ledNumber], LOW);   // turn off the OLD position
```
Turn off the LED at the OLD index - done using `ledNumber` before it's changed.

```cpp
  ledNumber++;
  if (ledNumber >= 8) {
    ledNumber = 0;
  }
```
Advance the index; wrap back to 0 once past the last LED, per the "after the last LED, the next press returns to the first" requirement.

```cpp
  digitalWrite(ledPin[ledNumber], HIGH);  // turn on the NEW position
```
Turn on the LED at the NEW index - `ledNumber` has already been updated by this point.

## Narrative

This sketch inherits the full three-stage debounce logic unchanged from `debounced-button.ino` - only the action taken at the falling edge changes.

The key conceptual difference from the earlier examples: there, the action is always "flip from whatever it currently is" (`ledState = !ledState`), because there are only two possible states and the program never really knows which one it's in without checking a variable. Here, the action is "move to a specific position" - the old LED is explicitly turned off, the new one explicitly turned on, with no need to "guess" a direction to flip. Because of that, a boolean state no longer fits; an integer index does.

**Order matters**: turning off the old LED has to happen using the OLD value of `ledNumber`, before it's incremented. Reverse that order and the program loses track of which LED needs to be turned off.

## Bugs found along the way (useful material for a "what didn't work" writeup)

1. **`ledNumber` was briefly declared `const`** - caused a compile error, since its value needs to change in `loop()`, but `const` forbids any change after declaration.
2. **An "turn off all LEDs" loop placed outside every `if` condition** - tried early on, but wrong: since it ran on every single pass of `loop()` (thousands of times per second) unconditionally, an LED that had just been turned on would immediately be turned off again the very next pass, before it could ever be visible to the eye.
3. **Pin mismatch between code and physical wiring** - the code pointed at one pin while the button's wire was physically connected to a different one, so the button was never detected at all. Fixed by temporarily printing the raw reading to serial to confirm whether the value changes at all when the button is pressed.
4. **Boolean toggle (`ledState = !ledState`) was briefly tried here too** - conceptually wrong, since this sketch needs "set explicitly to a specific position," not "flip from the previous state."
