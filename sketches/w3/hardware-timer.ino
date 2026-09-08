/* Hardware timer
 * millis() scheduling depends on loop() running often enough to notice.
 * A hardware timer counts in silicon instead and interrupts on its own
 * schedule, independent of whatever loop() happens to be doing.
 *
 * Targets Arduino-ESP32 core 3.x, where timerBegin() takes a frequency in
 * hertz. On core 2.x the API differs (timerBegin(0, 80, true), then
 * timerAlarmWrite() / timerAlarmEnable()).
 */

hw_timer_t *timer = NULL;

volatile uint32_t tickCount = 0;
// volatile tells the compiler this variable can change at any moment,
// from outside the normal flow of the code it's currently optimizing -
// specifically, from the ISR below, which can fire between any two
// instructions in loop(). Without volatile, the compiler would be free to
// assume tickCount never changes between reads within loop() and could
// cache it in a register instead of re-reading memory each time, causing
// loop() to see a stale value indefinitely.

void IRAM_ATTR onTimer() {
  tickCount++;
  // Keep ISRs this short - increment a counter and return, nothing else.
}
// IRAM_ATTR forces this function to live in internal RAM rather than
// flash, so it stays fast and reliably reachable even while flash access
// is busy elsewhere.

void setup() {
  Serial.begin(115200);

  timer = timerBegin(1000000);
  // 1,000,000 Hz tick rate = one tick every 1 microsecond.

  timerAttachInterrupt(timer, &onTimer);
  // Registers onTimer() as the function to call whenever the alarm fires.

  timerAlarm(timer, 100000, true, 0);
  // Fire every 100,000 microseconds = 100ms. The `true` sets it to
  // auto-reload (repeat indefinitely) instead of firing once.
}

void loop() {
  static uint32_t reported = 0;
  // static means this variable keeps its value between calls to loop(),
  // unlike a normal local variable which would reset to 0 every pass.

  uint32_t ticks;

  noInterrupts();
  ticks = tickCount;
  interrupts();
  // Copy the shared variable while interrupts are briefly disabled, so
  // the read can't be interrupted halfway through by onTimer() modifying
  // tickCount at the same instant - which matters on platforms where a
  // multi-byte read/write isn't guaranteed to happen as one atomic step.

  if (ticks != reported) {
    reported = ticks;
    Serial.print("ticks: ");
    Serial.println(ticks);
  }
}

/* Questions worth answering:
 * 1. How many ticks accumulate in ten seconds? At 100ms per tick,
 *    10 seconds / 0.1 seconds = 100 ticks - confirmed by testing.
 * 2. Without volatile, the compiler could cache tickCount in a register
 *    and never re-read it from memory, so loop() could see the same
 *    stale value forever even as the ISR keeps incrementing the real one.
 * 3. tickCount is copied between noInterrupts()/interrupts() rather than
 *    read directly because the ISR could fire mid-read, potentially
 *    handing loop() a value that's half-old, half-new - copying inside a
 *    brief critical section guarantees a clean, complete value.
 */
