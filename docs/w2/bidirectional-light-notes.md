# Notes — Bidirectional Light

## Line-by-line

```cpp
const int buttonStepPin = 4;
const int buttonDirectionPin = 23;
```
Two button pins now, replacing the single `buttonPin` from the earlier examples - one advances the position, the other reverses direction.

```cpp
int directionStep = 1;
```
New variable: current direction of travel. 1 = forward (index increases), -1 = backward. Doesn't exist in `walking-light.ino`, since that sketch only ever moves in one direction (always forward, wrapping to 0).

```cpp
int lastReadingStep = HIGH;
int buttonStateStep = HIGH;
unsigned long lastChangeTimeStep = 0;

int lastReadingDirection = HIGH;
int buttonStateDirection = HIGH;
unsigned long lastChangeTimeDirection = 0;
```
Two full sets of debounce variables, one per button. Base names are identical to the earlier examples (`lastReading`, `buttonState`, `lastChangeTime`), just suffixed to tell the two instances apart.

```cpp
bool isButtonPressed(int pin, int &lastReading, int &buttonState, unsigned long &lastChangeTime) {
```
A helper function wrapping the entire three-stage debounce routine from `debounced-button.ino`, so it can be reused for any pin without copying the block - this is the answer to "write the debouncing logic once, not copied twice."

Parameters are passed by reference (`&`) - important, since without it, changes made inside the function wouldn't persist back to the caller's original variables.

```cpp
  int reading = digitalRead(pin);
  bool pressedEvent = false;
  ...
  return pressedEvent;
}
```
Identical three-stage structure to the earlier examples. The difference: the result (`pressedEvent`) is returned as a bool rather than directly triggering an action inside the function - keeping the function generic, with no knowledge of LEDs or direction at all.

```cpp
ledNumber += directionStep;
```
Advance the index following the current direction - different from `walking-light.ino`, which always does `ledNumber++` (forward only).

```cpp
if (ledNumber > 7) {
  ledNumber = 6;
  directionStep = -1;
} else if (ledNumber < 0) {
  ledNumber = 1;
  directionStep = 1;
}
```
Past the top end: correct the index back one step, AND flip direction to backward - this is what makes "reverse at the ends" happen. Symmetric for the bottom end.

```cpp
directionStep = -directionStep;
```
Reverses direction instantly - doesn't touch `ledNumber` at all, so the light stays exactly where it is; only the direction of the *next* step changes.

## Narrative

This sketch inherits both the debounce logic and the LED-shifting mechanism from `walking-light.ino`, adding two new concepts: direction of travel, and a reusable debounce function.

When the light is at index 7 (the top end) moving forward, `ledNumber + directionStep` would produce 8 - out of bounds for an 8-element array. At that exact point, two things happen together: direction flips (forward becomes backward), AND the index is corrected back one step from there (to 6) - not reset to 0 as in the one-directional version, and not left sitting at 7 either. This keeps the "8, 7, 6..." sequence moving smoothly with no skip or pause.

The biggest structural difference from `walking-light.ino` is the `isButtonPressed()` function. Instead of writing out the full three-stage debounce block again for a second button, that logic is wrapped into one function taking a pin and references to its three state variables as parameters, returning true/false in answer to "was this pin just pressed, genuinely?" Both buttons call the same function, each with its own set of state variables.

## Debugging process and lessons

### 1. Pin mismatch (again)
Same as in `walking-light.ino` - the code sometimes pointed at a different pin than where the button was actually wired (e.g. `buttonDirPin = 18` in code, while the physical wire sat on GPIO22/23). Symptom: the button "does nothing at all," not a logic bug. Diagnosed by printing the raw pin value and checking whether it changes at all on a press.

### 2. Comparing two approaches: function vs. manual duplication
At one point during debugging, a version with the entire debounce block **manually duplicated** twice (one copy per button, no wrapper function) was tried. That version worked functionally, but didn't meet the requirement to avoid duplicating the debounce logic.

Once the correct pins were identified (through debugging the duplicated version), the function-based version (`isButtonPressed()`) was tried again with the now-confirmed pins - and it worked. This suggests the earlier failure of the function version was most likely the same pin mismatch, not a flaw in the function's structure itself.

### 3. Wrapping in a function must preserve the two-variable structure
Critical point: wrapping the debounce logic in a function has to keep the two-variable structure (`lastReading` vs. `buttonState`) that was already proven correct. Simplify the function down to a single variable, and the same bug as before (the comparison variable "catching up" to the reading too quickly) reappears, regardless of whether the code is wrapped in a function or not.

## The specific requirement this addresses

*"Explain how you avoided duplicating the debounce code."*

Answer: the debounce logic is wrapped in a function, `isButtonPressed(pin, &lastReading, &buttonState, &lastChangeTime)`, which takes a pin and references to its state variables as parameters. This function is called twice in `loop()` - once for the step button, once for the direction button - each with its own independent set of state variables, so the debounce logic itself is written exactly once but serves both buttons.
