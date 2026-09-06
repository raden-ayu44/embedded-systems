# Notes — Board Verification

Purpose: prove the entire toolchain works (IDE, board package, USB driver, upload, serial link) before moving on to real GPIO work.

## Line-by-line

```cpp
const int ledPin = 2;
```
The onboard LED, not an external one - most ESP32 dev boards wire it to GPIO 2. This is why this sketch uses pin 2 while everything else in this repo uses pin 13 for an external LED.

```cpp
Serial.begin(115200);
delay(200);
```
The one deliberate `delay()` in this whole repo. It's fine here specifically because it runs once in `setup()`, not in `loop()` - it doesn't block anything repeatedly. It just gives the USB-to-serial bridge a moment to settle right after the connection opens, so the first printed lines aren't lost before the port is ready to receive.

```cpp
Serial.printf("Chip model     : %s\n", ESP.getChipModel());
...
Serial.printf("CPU frequency  : %lu MHz\n", (unsigned long)getCpuFrequencyMhz());
```
First use of `Serial.printf()` in this repo - a format string with placeholders (`%s` for text, `%d` for a plain integer, `%lu` for an unsigned long) instead of chaining `print()`/`println()` calls. Some values need an explicit `(unsigned long)` cast so their type matches the `%lu` placeholder exactly.

The most important line to check is `Core version` - it must start with `3`, since the timer, PWM, and networking APIs used later assume core 3.x, not 2.x.

```cpp
void loop() {
  unsigned long now = millis();
  if (now - previousMillis >= interval) {
    ...
  }
}
```
Same non-blocking blink pattern as `non-blocking-blink.ino`. No per-toggle serial print here though - this sketch's diagnostic report already happened once in `setup()`; the blink is just a simple visual confirmation the board is still alive and responsive.

## Summary

Two things introduced here that don't appear anywhere else in this repo: `Serial.printf()` with placeholders and type casting, and a legitimate use of `delay()` - legitimate specifically because it's in `setup()`, for a real hardware-settling reason, not as a shortcut instead of `millis()`.
