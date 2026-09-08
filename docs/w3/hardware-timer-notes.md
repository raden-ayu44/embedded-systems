# Notes — Hardware Timer

## Line-by-line

```cpp
hw_timer_t *timer = NULL;
```
A pointer to a hardware timer object, initialized once in `setup()`.

```cpp
volatile uint32_t tickCount = 0;
```
`volatile` tells the compiler this variable can change at any moment, from outside the normal flow of whatever code is currently being optimized - specifically, from the ISR below, which can fire between any two instructions in `loop()`. Without `volatile`, the compiler would be free to assume `tickCount` never changes within a stretch of code and could cache its value in a register instead of re-reading memory each time - which would make `loop()` see a stale value indefinitely, even as the real counter keeps incrementing in the background.

```cpp
void IRAM_ATTR onTimer() {
  tickCount++;
}
```
`IRAM_ATTR` forces this function to live in internal RAM rather than flash, keeping it fast and reliably reachable even while flash access is busy elsewhere in the system. The body is kept to the absolute minimum - increment and return - which is the rule for every ISR on this platform.

```cpp
void setup() {
  Serial.begin(115200);
  timer = timerBegin(1000000);
```
1,000,000 Hz tick rate = one tick every 1 microsecond. This is the counting resolution, not the interrupt frequency.

```cpp
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 100000, true, 0);
}
```
Registers `onTimer()` as the function to call whenever the alarm fires, then sets the alarm to fire every 100,000 microseconds (100ms). The `true` sets it to auto-reload - fire repeatedly forever - instead of firing once and stopping.

```cpp
void loop() {
  static uint32_t reported = 0;
```
`static` means this variable keeps its value between calls to `loop()`, unlike a normal local variable which would reset to 0 on every single pass.

```cpp
  uint32_t ticks;
  noInterrupts();
  ticks = tickCount;
  interrupts();
```
Copies the shared variable while interrupts are briefly disabled, so the read can't be interrupted halfway through by `onTimer()` modifying `tickCount` at the exact same instant - relevant because a multi-byte read/write isn't guaranteed to complete as a single atomic step on every platform.

```cpp
  if (ticks != reported) {
    reported = ticks;
    Serial.print("ticks: ");
    Serial.println(ticks);
  }
}
```
Only prints when the tick count has actually changed since the last time it was reported - avoids spamming the serial monitor with identical values on every single `loop()` pass.

## Narrative

Unlike `millis()`-based scheduling, which depends entirely on `loop()` running often enough to notice that time has passed, a hardware timer counts independently in silicon and interrupts the program on its own schedule - regardless of what `loop()` happens to be doing at that moment. This makes it the right tool when timing has to be exact, not just "close enough."

The `volatile` keyword and the `noInterrupts()`/`interrupts()` pairing both exist for the same underlying reason: `tickCount` is being written from two different contexts (the ISR, and the main `loop()`) that can interleave unpredictably, and both the compiler and the CPU need explicit instruction not to take shortcuts that assume single-threaded, sequential behavior.

## Questions worth answering

1. **How many ticks accumulate in ten seconds? Does that match the configured period?** At 100ms per tick, 10 seconds ÷ 0.1 seconds = 100 ticks - confirmed by testing, matching the configuration exactly.
2. **What would the compiler be allowed to do if `tickCount` were not `volatile`?** It could cache the value in a CPU register the first time it's read within some stretch of code, and keep reusing that cached value on subsequent reads - never noticing that the real memory location was updated by the ISR in the meantime. `loop()` could then appear to see the same value forever, even while the actual counter keeps incrementing.
3. **Why copy `tickCount` between `noInterrupts()` and `interrupts()` rather than using it directly?** Because the ISR could fire in the middle of reading the variable, potentially handing `loop()` a value that's part old bytes, part new bytes - a torn read. Copying it inside a brief critical section (interrupts disabled) guarantees the value read is complete and consistent, not a snapshot caught mid-update.
