# Notes — Non-blocking Dual Blink

## Line-by-line

```cpp
unsigned long prev1 = 0, prev2 = 0;
bool state1 = LOW, state2 = LOW;
```
Two complete, separate sets of state variables - one pair per LED. Each pair is fully independent; neither knows or cares that the other exists.

```cpp
void loop() {
  unsigned long now = millis();
```
The clock is read once per pass and reused for both checks below, rather than calling `millis()` twice - a small efficiency, and it also guarantees both comparisons use the exact same instant.

```cpp
  if (now - prev1 >= period1) {
    prev1 = now;
    state1 = !state1;
    digitalWrite(led1, state1);
  }
```
Exact same non-blocking pattern from the earlier non-blocking blink example - applied here to led1's own timer, completely self-contained.

```cpp
  if (now - prev2 >= period2) {
    prev2 = now;
    state2 = !state2;
    digitalWrite(led2, state2);
  }
}
```
The identical pattern again, independently, for led2. Adding this second periodic task cost four lines - not a redesign of the first one.

## Narrative

This is the direct fix for the blocking version's core problem: instead of one long sequential chain of waits, `loop()` runs continuously and asks two independent questions every pass - "has period1 elapsed?" and "has period2 elapsed?" - each answered by its own pair of state variables, with no interaction between the two.

## What to expect physically

The two LEDs blink on their own schedules with no forced sequencing. Since 1000ms and 1500ms share a common multiple of 3000ms, their cycles realign every 3 seconds - sometimes landing both ON, sometimes both OFF - purely as a byproduct of the numbers involved, not because either LED is aware of the other's state.

## Why this generalizes

This is the same pattern used for a single periodic task, just duplicated per task with its own variable pair. Any number of independent periodic behaviors can be added this way without ever needing `delay()` or restructuring existing tasks - each one just needs its own `prevX`/`periodX` pair and an `if` block.
