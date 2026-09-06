# Notes — Bounce Demo (Before Fix)

This version is deliberately left unfixed, to see contact bounce happen before correcting it in `debounced-button.ino`.

## Line-by-line

```cpp
int lastReading = HIGH;
```
The raw pin value from the previous loop pass. There is only ONE state variable here - no separate "trusted" value like `debounced-button.ino` has. That's the whole problem.

```cpp
if (reading != lastReading && reading == LOW) {
```
Two conditions combined into one check: the reading just changed, AND the new value is LOW (pressed). The moment both are true, the code trusts it immediately - there's no waiting period to confirm the signal has actually settled versus just chattering for a moment.

```cpp
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Serial.println("toggle");
  }
```
Same toggle action as the fixed version - but here it can fire several times for a single physical press, if the mechanical contact bounces a few times within milliseconds.

## Narrative

While idle, the pin sits at HIGH via the internal pull-up. When pressed, it reads LOW - but a real mechanical switch doesn't transition cleanly; its contacts strike, separate, and strike again a few times before settling, all within about 1-10ms. Because `loop()` runs far faster than that chatter, this code sees each bounce as a separate signal change and toggles on every one that happens to land on LOW.

The code compiles and the LED does turn on/off when the button is touched - so in that sense it "works." But it isn't correct: the number of "toggle" lines in the serial monitor won't match the number of actual physical presses. This is the clearest demonstration in the whole repo that **working** and **correct** are two different things.

## What to try

Press the button exactly 10 times and count the "toggle" lines. It'll almost always be more than 10 - that's the evidence bounce is real, before moving on to the fix.
