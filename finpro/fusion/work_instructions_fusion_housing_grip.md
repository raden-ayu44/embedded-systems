# Work instructions: grip housing in Fusion (v4 layout)

Scope: the load cell grip housing only (two bars, load cell, ridges, calibration platform, cable clamp). The electronics housing is separate. All values marked "working" or "TBD" are provisional; the model is built so they can be changed in one place.

Inputs you need open: `potongan_memanjang_v4_logam.svg`, `exploded_isometrik_v4_logam.svg`, `asumsi_v4.md` (also merged as Appendix A of `desain-housing-load-cell.md`), `fusion_parameters_housing_grip.csv`, and `desain-housing-load-cell.md` (and `catatan-proyek-hgd.md` for the caliper table).

## Layout reference (all numbers come from parameters)

Directions: length axis = along the load cell (fixed end on the left, free end on the right); width axis = across the bars (30 mm); stack axis = A at the top, B at the bottom. In Fusion, use whichever origin plane contains length and width, and extrude along the stack axis.

Stack levels, with the bottom face of the load cell at 0:

| Part | Stack range |
|---|---|
| Bar A (palm side, fixed) | `LC_H + gap` to `LC_H + gap + bar_t` |
| Boss A (under bar A, left end) | `LC_H` to `LC_H + gap` |
| Load cell | 0 to `LC_H` |
| Boss B (above bar B, right end) | `-gap` to 0 |
| Bar B (finger side, moving) | `-gap - bar_t` to `-gap` |
| Ridges (PLA, outside bar B) | below bar B, height `ridge_h` |

Length positions, with the left end of the load cell at 0:
- Load cell: 0 to `LC_L`.
- Both bars: from `-(bar_L - LC_L)/2` to `LC_L + (bar_L - LC_L)/2` (load cell centred, about 11.5 mm of spare bar on each end).
- Boss A: 0 to `boss_L`. Boss B: `LC_L - boss_L` to `LC_L`.
- Grip zone centre: `LC_L / 2`. This is `lever_arm` (60 mm) from the inner edge of each boss.

Total thickness: `2*bar_t + 2*gap + LC_H + ridge_h` = 52 mm.

## Phase 1: setup

- [ ] Create a new design and save it with a clear name. If this part is also submitted for the 3D printing module, use the module's naming format.
- [ ] Check the document units are mm (Browser, Document Settings; menu names can vary by version).
- [ ] Open Change Parameters and use Import Parameters with `fusion_parameters_housing_grip.csv`.
- [ ] Check the Value column: `total_t` reads 52 mm, `gap` reads 2.5 mm, `boss_L` reads 13.5 mm. If decimals look wrong, retype them.
- [ ] Do not model holes yet. The hole parameters are placeholders until the load cell is measured.

## Phase 2: reference load cell

- [ ] New component `LoadCell_ref`. Activate it before sketching.
- [ ] Sketch a rectangle on the horizontal plane (`LC_L` by `LC_W`), centred on the width axis, and extrude `LC_H`. Type parameter names in the dimension boxes, not numbers.
- [ ] Ground it (right-click in the Browser).
- [ ] Mark it as reference only (do not export it for printing).
- [ ] Add a note in the component description: orientation of the load arrow is unconfirmed (C5).

## Phase 3: Bar A and Bar B

For each bar, create a new component and activate it first.

- [ ] Create offset construction planes at the stack levels in the table above, using parameter expressions (for example `LC_H + gap`).
- [ ] Bar A plate: rectangle `bar_L` by `bar_W`, centred on the cell, extruded `bar_t` from the Bar A level.
- [ ] Boss A: rectangle `boss_L` by `LC_W`, at the left end of the cell, extruded `gap` toward the load cell, joined to the plate.
- [ ] Bar B: same plate on the lower level; boss B at the right end, extruded `gap` toward the load cell, joined.
- [ ] Assign aluminium to both bars (material is only used for appearance and the mass check).
- [ ] Mass check (right-click the component, Properties): each bar should read about 140 g (plate 51 cm3 plus boss about 1 cm3, at 2.7 g/cm3). A big difference means a wrong parameter.

## Phase 4: PLA parts (rough shapes only)

- [ ] Ridges on the outer face of bar B: two ridges around the grip zone centre, `ridge_h` tall, with about 22 mm of flat platform between them (the calibration platform). Width and exact shape are placeholders.
- [ ] Cable clamp: a small block on the inner side of bar A in the spare bar length on the left. Placeholder size only.
- [ ] Put these in their own component(s) so they can be exported and printed separately.

## Phase 5: checks

- [ ] Inspect > Interference: select all bodies. Expected result: no interference (the bosses touch the load cell faces, which is not an overlap).
- [ ] Inspect > Measure: gap between bar A and the load cell at the free end is 2.5 mm; gap between bar B and the load cell at the fixed end is 2.5 mm; overall thickness matches `total_t`.
- [ ] Inspect > Section Analysis through the length: compare with the cross-section drawing (A on top, B at the bottom, bosses on opposite ends).
- [ ] Parameter test: change `gap` to 3 mm, confirm everything updates and `total_t` reads 53 mm, then change it back to 2.5.
- [ ] Save with a version description.

What this does not check: whether the bars bend into the load cell under load. Rely on `desain-housing-load-cell.md`, HL9 (aluminium 10 mm leaves at least 1.70 mm of clearance before the load cell flexing and cover height are known).

## Phase 6: while you wait for the load cell

- [ ] Build the cardboard mock-up at about 52 mm total thickness and check hand comfort.
- [ ] Confirm with the TA that a hybrid grip (metal plates plus printed parts) is acceptable.
- [ ] Do not order plates until the thickness is decided. Keywords and the seller checklist are in `desain-housing-load-cell.md`, HL11.
- [ ] Optional: print a 30 x 7 mm PLA strip and do the cantilever test in 14.9 to check the beam model.

## Phase 7: when the load cell arrives

Measure with the caliper (Section 15 table in `catatan-proyek-hgd.md`, rows C1 to C8) and write the results down before touching the model:
- [ ] Hole diameter, pitch along the length and across the width, and distance from the end of the body (C2 to C4).
- [ ] Whether the holes are through or blind (C6). If blind, the bolting scheme changes; stop and review.
- [ ] Which side is along the load (arrow, C5) and which end the cable leaves (C7).
- [ ] Height of the white strain-gauge cover above the metal (and whether the other side has one).
- [ ] Bolt thread size.

Then:
- [ ] Update the parameters (replace the TBD rows; split `hole_pitch` into length and width pitch if they differ).
- [ ] Check that `boss_L` fits the hole pattern. If not, recompute the lever arm.
- [ ] Add holes (with counterbores in the metal plates) only after this.
- [ ] Send a short correction file with the measured values to Cowork so it redraws the schematics (it should not receive the CSV).
- [ ] Send the plate drawings to the workshop or drilling service.

## Printing rules to remember (from the 3D printing module)

- PLA only; slot booked in advance; print only after the slice review is approved.
- Clearance 0.2 to 0.3 mm per side; M3 through-hole modelled at 3.4 mm; wall at least 1.2 mm (use about 2 mm where loaded); overhang at most 45 degrees; chamfer 0.3 to 0.5 mm on bottom edges.
- Print flat with the boss side down so layers run along the part length. Print a small test coupon (boss and hole pattern) before the full part.
- The metal bars are not printed. Only ridges, platform, cable clamp, and the electronics housing are.

## Decision gates

1. Before ordering plates: thickness decided (cardboard check and TA answer).
2. Before drilling: all hole measurements recorded and through/blind known.
3. Before printing: slice review approved.
4. Before calibration: decide how to apply 70 kg safely (`desain-housing-load-cell.md`, HL10 lists the open problem).
