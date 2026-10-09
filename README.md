# Embedded Systems

Personal archive for an embedded system course: Arduino/ESP32 sketches, notes, wiring diagrams, video links, and the final project documentation.

## Structure

```
docs/       → notes (.md) and wiring diagrams (.png), by week
sketches/   → Arduino (.ino) sketches, by week
videos/     → external links to demo recordings (videos captured by me)
finpro/     → final project: hand grip dynamometer (design docs, drawings, calculations)
```

## Weekly work

| Week | Topic | Sketches | Notes |
|---|---|---|---|
| 1 | Board verification | `sketches/w1/` | `docs/w1/` |
| 2 | Non-blocking timing, debounced input, light patterns | `sketches/w2/` | `docs/w2/` |
| 3 | Dual blink (blocking vs. non-blocking), hardware timer | `sketches/w3/` | `docs/w3/` |

## Final project: hand grip dynamometer (`finpro/`)

A hand grip strength meter (group project). Two plates are squeezed, a load cell between them measures the force, an HX711 digitizes it, and an ESP32 shows the result on an LCD and logs it to CSV over USB serial.

- Target range: 20 to 70 kgf.
- Parts: ESP32 DevKit V1, HX711 module, CZL 601 80 kg bending-beam load cell, 16×2 I2C LCD, push button, LED.
- Housing: two plain aluminium plates (170 × 30 × 10 mm) with PLA spacers (28 × 28 × 2.5 mm), joined to the load cell with M6 × 25 bolts.
- Budget: maximum Rp300.000 per team.

**Status:** design and documentation stage. The ESP32 and its six project pins have been tested; the housing, the wiring, and the calibration are still proposals. There is no measurement data from the load cell yet, and nothing in `finpro/` has been verified on hardware.

| File | What it is |
|---|---|
| `finpro/catatan-proyek-hgd.md` | Main project notes: requirements, BOM, decisions, risks, changelog |
| `finpro/desain-housing-load-cell.md` | Housing design: force path, stiffness, spacer and bolt checks, materials, calibration method |
| `finpro/protokol-kalibrasi-hgd.md` | Calibration protocol (dumbbell method; stage 1 up to 20 kg, stage 2 up to 42 kg) |
| `finpro/asumsi_v5.md` | Assumptions and open conflicts behind the v5 housing drawings |
| `finpro/datasheet-library.md` | Datasheet notes for each component |
| `finpro/daftar-isian-datasheet.md` | Checklist of datasheet values still to be filled in |
| `finpro/hgd_perhitungan.xlsx` | Signal, noise, and error-budget calculations (formulas; edit the Input sheet) |
| `finpro/fusion/` | Fusion 360 parameters (CSV) and modelling work instructions |
| `finpro/img/` | Drawings: v5 longitudinal section and exploded view, calibration setup (stage 1), older v4 drawings kept as history |

The project documents are written in Indonesian. Drawings are SVG and open in any browser.

## License

Personal learning archive — shared as-is for reference.
