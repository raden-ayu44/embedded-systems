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
- Housing: two plain aluminium plates (170 × 30 × 10 mm) with PLA spacers (28 × 28 × 2.5 mm), joined to the load cell with M6 × 25 bolts; cable clamp printed as one piece with spacer A.
- Budget: maximum Rp300.000 per team.

**Status:** design and documentation stage. The ESP32 and its six project pins have been tested; the housing, the wiring, and the calibration are still proposals. There is no measurement data from the load cell yet, and nothing in `finpro/` has been verified on hardware.

| File | What it is |
|---|---|
| `finpro/catatan-proyek-hgd.md` | Main project notes: requirements, BOM, decisions, risks, changelog |
| `finpro/desain-housing-load-cell.md` | Housing design: force path, stiffness, spacer and bolt checks, materials, calibration method |
| `finpro/protokol-kalibrasi-hgd.md` | Calibration protocol (dumbbell method; stage 1 up to 20 kg, stage 2 up to 42 kg) |
| `finpro/asumsi.md` | Compiled assumptions, calculations and decisions behind the housing drawings (v2 to v4 history in section 9) |
| `finpro/koreksi.md` | Compiled instructions for the drawing assistant (replaces `koreksi.md` and `koreksi_v2` to `v11`) |
| `finpro/instruksi_klem_tampak.md` | Task for the two cable-clamp views |
| `finpro/datasheet-library.md` | Datasheet notes for each component |
| `finpro/daftar-isian-datasheet.md` | Checklist of datasheet values still to be filled in |
| `finpro/hgd_perhitungan.xlsx` | Signal, noise, and error-budget calculations (formulas; edit the Input sheet) |
| `finpro/fusion/` | Fusion 360 parameters (`fusion_parameters_housing_grip.csv`) and modelling work instructions (still v5; to be updated) |
| `finpro/img/` | Older drawings (v4, v5; superseded). Current drawings (section v11, exploded v12, calibration setup v11, clamp views v1) are in the Project folder `housing-grip/` and not yet copied here |

The project documents are written in Indonesian. Drawings are SVG and open in any browser.

## License

Personal learning archive — shared as-is for reference.
