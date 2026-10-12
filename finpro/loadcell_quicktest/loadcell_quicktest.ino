// Quick load cell sanity test: ESP32 DevKit V1 + HX711 (no library needed)
// Wiring (module side): DT -> GPIO18, SCK -> GPIO19, VCC -> 3V3, GND -> GND
// Serial Monitor: 115200 baud. Send 't' to re-zero (tare).

const int PIN_DT  = 18;
const int PIN_SCK = 19;

// Assumes CZL601 80 kg, 2.0 mV/V, gain 128, HX711 supply = excitation:
//   counts per kg = 0.002 * 2 * 128 * 2^23 / 80 = about 53687
// If your label says another capacity, change both numbers (this is only an estimate).
const float CAPACITY_KG     = 80.0;
const float SENSITIVITY_MVV = 2.0;
const float COUNTS_PER_KG   = (SENSITIVITY_MVV / 1000.0) * 2.0 * 128.0 * 8388608.0 / CAPACITY_KG;

const int32_t NOT_READY = INT32_MIN;
long tareValue = 0;

int32_t readHX711() {
  uint32_t t0 = millis();
  while (digitalRead(PIN_DT) == HIGH) {          // HX711 pulls DT LOW when a sample is ready
    if (millis() - t0 > 1000) return NOT_READY;  // no response within 1 s
  }
  int32_t v = 0;
  noInterrupts();
  for (int i = 0; i < 24; i++) {
    digitalWrite(PIN_SCK, HIGH);
    delayMicroseconds(1);
    v = (v << 1) | digitalRead(PIN_DT);
    digitalWrite(PIN_SCK, LOW);
    delayMicroseconds(1);
  }
  digitalWrite(PIN_SCK, HIGH);                   // 25th pulse = channel A, gain 128
  delayMicroseconds(1);
  digitalWrite(PIN_SCK, LOW);
  interrupts();
  if (v & 0x800000) v |= 0xFF000000;             // sign-extend 24 -> 32 bit
  return v;
}

// average of n samples, also reports min and max to show noise
bool readAvg(int n, long &avg, long &mn, long &mx) {
  long long sum = 0; mn = 0x7FFFFFFF; mx = -0x7FFFFFFF;
  for (int i = 0; i < n; i++) {
    int32_t v = readHX711();
    if (v == NOT_READY) return false;
    sum += v;
    if (v < mn) mn = v;
    if (v > mx) mx = v;
  }
  avg = (long)(sum / n);
  return true;
}

void tare() {
  long a, mn, mx;
  if (readAvg(10, a, mn, mx)) { tareValue = a; Serial.println(">> zeroed"); }
  else Serial.println(">> tare failed: HX711 not responding");
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_DT, INPUT);
  pinMode(PIN_SCK, OUTPUT);
  digitalWrite(PIN_SCK, LOW);
  delay(1500);
  Serial.println("\nLoad cell quick test. Do not touch the load cell for 3 seconds...");
  delay(3000);
  tare();
  Serial.printf("Assuming %.0f kg, %.1f mV/V -> %.0f counts per kg\n", CAPACITY_KG, SENSITIVITY_MVV, COUNTS_PER_KG);
}

void loop() {
  if (Serial.available() && Serial.read() == 't') tare();
  long a, mn, mx;
  if (!readAvg(5, a, mn, mx)) {
    Serial.println("NO RESPONSE from HX711 (check wiring / power / pins)");
    delay(500);
    return;
  }
  long delta = a - tareValue;
  Serial.printf("raw=%ld  delta=%ld  est=%.2f kg  noise(max-min)=%ld", a, delta, delta / COUNTS_PER_KG, mx - mn);
  if (a >= 8388600 || a <= -8388600 || a == 0) Serial.print("   <-- stuck value: not connected or saturated");
  Serial.println();
}
