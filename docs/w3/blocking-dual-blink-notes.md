# Notes — Blocking Dual Blink

## Line-by-line

```cpp
const int led1 = 13, led2 = 32;
```
Two LEDs, meant to blink independently at different rates - 1 second for led1, 1.5 seconds for led2.

```cpp
void loop() {
  digitalWrite(led1, HIGH); delay(1000);
  digitalWrite(led1, LOW);  delay(1000);
```
led1's full cycle - on for 1s, off for 1s - already costs 2000ms of total blocking time, during which nothing else in the program can run at all. Not just led2 - anything else that might get added later (a button check, a sensor read) would be frozen out too.

```cpp
  digitalWrite(led2, HIGH); delay(1500);
  digitalWrite(led2, LOW);  delay(1500);
}
```
Same problem repeats for led2 - another 3000ms of blocking before control returns to the top of `loop()` and led1 gets touched again.

## Narrative

This is the naive version, kept specifically as a reference to compare against `non-blocking-dual-blink.ino`. The two LEDs are not actually blinking independently at all - they're forced into strict alternating sequence, because `delay()` doesn't just pause the LED it's attached to, it pauses the *entire* program.

## What to expect physically

The two LEDs never overlap. led2 cannot even begin until led1's two `delay()` calls have fully finished (2000ms total), because there's no way for the processor to "check in" on led2's timing while it's blocked inside led1's delay.

## Questions worth answering

1. **Describe the difference in behaviour precisely between this and the non-blocking version.** In this version, the two LEDs never light up at the same time - they're locked into rigid sequence (led1's full 2000ms cycle, then led2's full 3000ms cycle, repeating). In the non-blocking version, each LED runs on its own independent schedule with no forced ordering, and because 1000ms and 1500ms share a common multiple of 3000ms, their cycles periodically realign - sometimes both on, sometimes both off - purely as a side effect of the math, not because either LED is aware of the other.
2. **In this version, how long (worst case) before the program could notice an imaginary button press?** The full loop cycle blocks for 1000+1000+1500+1500 = 5000ms before returning to the top. In the worst case, a press happening right after the last `digitalRead()`-equivalent check (if one existed) would have to wait the entire remaining blocked duration - up to 5000ms - before the program could even attempt to notice it.
3. **A situation where `delay()` is still the right choice.** A short, deliberate pause during initial hardware bring-up in `setup()` - for example, giving a sensor time to power up and stabilize before its first read - where nothing else needs to run yet and a blocking wait is exactly what's wanted, not a bug.
