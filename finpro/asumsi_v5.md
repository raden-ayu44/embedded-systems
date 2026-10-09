# Asumsi — Gambar Skematik Housing Grip Load Cell (v5, varian logam)

Dikerjakan satu kali, langsung dari v4 ke v5. Sumber yang dipakai:
- `koreksi_v4.md` (utama);
- bagian `koreksi_v3.md` yang tidak digantikan (spacer PLA terpisah, pelat polos, urutan exploded, kesalahan yang pernah terjadi);
- instruksi pengguna di chat;
- gambar penjual Automa-88 "Loadcell CZL-601, Size & Dimensions", disimpan sebagai `czl601_dimensi_automa88.png`.

Berkas v4 tidak ditimpa. Semua gambar **tidak berskala**, dan celah 2,5 mm digambar diperbesar.

| File v5 | Isi |
|---|---|
| `potongan_memanjang_v5_logam.svg` | Potongan memanjang melalui satu baris lubang. Pelat Al 10 polos, Spacer A/B PLA, load cell 130 mm, baut M6 × 25 + washer. Dimensi a = 37, x = 102, spacer 28, bentang bebas 74, lubang 12 dari ujung, 106 antar pasangan |
| `exploded_isometrik_v5_logam.svg` | Urutan dari atas: pelat A → Spacer A → load cell → Spacer B → pelat B. 4 baut pola 2 × 2 (15 melintang, 106 antar pasangan) |
| `kalibrasi_setup_v5.svg` | **Tidak dibuat**, sesuai permintaan (lihat Pertentangan 6) |

## 1. Perubahan dari v4

1. **Load cell diganti** dengan CZL601 sesuai gambar penjual (belum diukur): 130 × 28 × 22 mm. Ukuran lama 147 × 30 × 22 mm dari load cell 180 kg tidak dipakai lagi. Load cell ditaruh di tengah pelat 170 mm, jadi sisa pelat 20 mm di tiap ujung.
2. **Lubang pasang:** 4 × M6, dua per ujung. Pusat lubang 12 mm dari ujung load cell, 106 mm antar pasangan, dan 15 mm melintang. Lubang pelat dan spacer sejajar dengan lubang load cell. Diameternya ditulis "Ø TBD (kasus hitungan 5,5 dan 6,5)" tanpa angka di gambar.
3. **Tonjolan dihapus**, dan pelat A/B menjadi **pelat aluminium 10 mm polos** (sudah diputuskan; paduan TBD). Counterbore v4 juga dihapus, karena pelat polos tidak difrais.
4. **Spacer PLA terpisah:**
   - Spacer A dan Spacer B, masing-masing 28 × 28 × 2,5 mm, menutup kedua lubang di ujungnya.
   - Callout 4 = Spacer A, callout 5 = Spacer B. Nomor callout lain tetap. Arsirannya dibedakan dari aluminium dan load cell.
5. **Baut:** M6 × 25 + washer logam, 4 buah, langsung masuk ulir load cell tanpa mur. Kepala dan washer menonjol di luar pelat (lihat 3.3).
6. **Geometri turunan (boss_L = 28):** lengan tuas a = 37 mm, ujung jauh x = 102 mm, bentang bebas 74 mm. Nilai lama 60/133 (v4) dan 43,5/117/30/87 (`koreksi_v3.md`) tidak dipakai.
7. **Zona genggam ≈85 mm**, sebelumnya ≈90 di v4. Zona ini lebih panjang daripada bentang bebas 74 mm, jadi sebagian beban jatuh di atas spacer. Model beban terpusat di tengah tetap dipakai dan konservatif untuk momen.
8. **Area tengah load cell** yang berarsir di gambar penjual digambar sebagai area tengah/penutup dengan arti dan tinggi TBD (callout 17).
9. **Lubang binokular** digambar sebagai dua lubang bulat yang disambung celah, mengikuti bentuk di gambar penjual. Ukurannya skematik, tanpa angka.
10. **Kabel:** panjang kabel CZL601 belum diketahui, jadi panjang kabel ditulis TBD di gambar dan legenda ("ke housing elektronik (panjang kabel TBD)").
11. **Tetap sama:** celah 2,5 mm sebagai celah bebas-sentuh, tebal total ≈52 mm, ridge dan bidang tumpu di sisi luar B, jepit kabel di A, arah beban remasan, jalur gaya tunggal, dan catatan "Stop overload belum dirancang".
12. **Asumsi baru (revisi v5): diameter kabel load cell = 5 mm**, sebagai **asumsi kerja 5 mm, belum diukur**. Dokumen distributor menulis 4 mm; ukur saat barang tiba. Yang diterapkan (rincian di bagian 4.1):
    - penjepit kabel di batang A: lubang ≈ Ø kabel, lebar dan tinggi penjepit menyesuaikan;
    - lengkungan sisa kabel di dekat penjepit: radius tekuk TBD;
    - tempat kabel keluar dari ujung load cell ke penjepit.

    Kabel digambar lebih tebal dan diberi label "kabel Ø5 (asumsi kerja, belum diukur)". Angka lain tidak berubah.

## 2. Hitungan kekakuan

### Model
- **Model:** sama dengan `asumsi_v4.md`. Kantilever, F = 686 N (70 kgf), lebar pelat b = 30 mm, I = b·h³/12, E aluminium 70 GPa.
- **Beban:** terpusat di tengah load cell.
- **Geometri:** a = 130/2 − boss_L, x = 130 − boss_L.
- **Rumus:**
  - δ(a) = F·a³ / (3EI)
  - δ(x) = F·a²(3x − a) / (6EI)
  - σ = F·a·(h/2) / I
  - σ_net = σ·b / (b − 2d)
- **Keterbatasan:**
  - Spacer dan baut dianggap kaku.
  - Lenturan load cell sendiri, tinggi penutup, dan margin rakit tidak termasuk.
  - σ_net konservatif, karena lubang berada 16 mm di dalam spacer (12 mm dari ujung), bukan di tepi dalam spacer tempat momen terbesar.
  - Ini hitungan kasar untuk arah desain, bukan verifikasi.

### 2.1 Hasil (dihitung ulang) dan perbandingan dengan tabel `koreksi_v4.md` bagian E

| Pelat | boss_L | a / x | δ titik beban | δ ujung jauh | Sisa celah 2,5* | σ pangkal | σ_net Ø5,5 / Ø6,5 |
|---|---|---|---|---|---|---|---|
| **Al 10 mm (digambar)** | **28** | **37 / 102** | **0,066 mm** | **0,241 mm** | **≥ 2,26 mm** | **50,8 MPa** | **80 / 90 MPa** |
| Al 8 mm (pembanding) | 28 | 37 / 102 | 0,129 mm | 0,470 mm | ≥ 2,03 mm | 79,3 MPa | 125 / 140 MPa |
| Al 10 mm | 24 | 41 / 106 | 0,090 mm | 0,304 mm | ≥ 2,20 mm | 56,3 MPa | 89 / 99 MPa |
| Al 8 mm (pembanding) | 24 | 41 / 106 | 0,176 mm | 0,594 mm | ≥ 1,91 mm | 87,9 MPa | 139 / 155 MPa |

\* Sisa celah = 2,5 mm dikurangi lenturan ujung jauh saja.

Aluminium 8 mm hanya pembanding dan tidak digambar.

**Selisih lebih dari 2% terhadap tabel acuan:**

| Sel | Acuan | Hitungan ini | Selisih | Sebab |
|---|---|---|---|---|
| Al 10 / boss 28, δ titik beban | 0,07 mm | 0,066 mm | −5,4% | **Pembulatan.** 0,0662 dibulatkan ke 2 desimal menjadi 0,07. Dengan 3 desimal nilainya 0,066. Tidak ada beda model. |
| Al 8 / boss 24, δ titik beban | 0,16 mm | 0,176 mm | +9,9% | **Nilai acuan tidak konsisten**, bukan pembulatan. Dengan a dan E yang sama, rasio Al 8 terhadap Al 10 harus (10/8)³ = 1,95. Hitungannya 0,090 × 1,95 = 0,176. Nilai 0,16 hanya keluar bila a ≈ 39,7 mm. Kemungkinan salah hitung atau salah ketik di acuan. Kolom lain di baris yang sama (δ ujung jauh 0,59, σ 88) cocok dengan a = 41. |

Semua sel lain berselisih ≤ 1,4%. Tabel lama di `koreksi_v3.md` (a = 43,5, x = 117) sudah digantikan dan tidak dipakai.

### 2.2 Apakah celah 2,5 mm terlampaui di bawah beban?
- **Al 10 mm (digambar):** lenturan ujung jauh 0,24 mm (boss 28) sampai 0,30 mm (boss 24). **Celah tidak terlampaui** oleh lenturan pelat. Sisa celah ≥ 2,20–2,26 mm sebelum nilai TBD diketahui.
- **Dibanding v4:** lenturan ujung jauh turun dari 0,80 mm menjadi 0,24 mm. Penyebabnya, a turun dari 60 ke 37 mm berkat spacer 28 mm, padahal v4 memakai tonjolan ≈13,5 mm dengan load cell 147 mm.

### 2.3 Anggaran celah (Al 10, boss 28)

| Komponen | Nilai |
|---|---|
| Lenturan ujung jauh pelat | 0,24 mm |
| Lenturan load cell sendiri pada 70 kgf | **TBD** |
| Tinggi penutup/area tengah di atas permukaan | **TBD** |
| Margin rakit (kerataan pelat, spacer, baut) | **TBD** |
| **Sisa sebelum nilai TBD** | **≥ 2,26 mm** |

### 2.4 Catatan Ø lubang
Kasus Ø5,5 dihitung sesuai instruksi, tetapi **tidak mungkin dipakai sebagai lubang lewat baut M6**, karena diameter nominal ulir M6 = 6 mm. Kasus Ø6,5 lebih realistis. Sebagai pembanding, lubang lewat M6 menurut ISO 273 biasanya 6,4 / 6,6 / 7,0 mm. Dengan Ø7,0, σ_net Al 10 / boss 28 ≈ 95 MPa. Semua kasus masih jauh di bawah kisaran luluh paduan aluminium (≈200–275 MPa, paduan TBD). Ø lubang pelat tetap **TBD**.

## 3. Pemeriksaan spacer PLA dan baut

### 3.1 Kompresi spacer (E PLA ≈3 GPa, F = 686 N, tebal 2,5 mm)

| Kasus | Luas bersih | Kompresi | Tekanan rata-rata |
|---|---|---|---|
| Geometri v5: 28 × 28, **2 lubang** Ø6,5 per spacer | 717,6 mm² | 0,0008 mm | 0,96 MPa |
| Sesuai teks instruksi: 28 × 28, 4 lubang Ø6,5 | 651,3 mm² | 0,0009 mm | 1,05 MPa |
| Lama (`koreksi_v3.md`): 30 × 30, 4 lubang | 767 mm² | 0,0007 mm (dibulatkan "≈0,001") | — |

Kompresi spacer dapat diabaikan terhadap celah 2,5 mm di semua kasus. Tiap spacer hanya menutup dua lubang (lihat Pertentangan 4).

### 3.2 Tekanan tepi spacer
- **Metode lama** (seluruh momen ditahan kontak spacer, penampang utuh, tanpa preload):
  - M = F·a = 686 × 37 = 25 382 N·mm.
  - S = 28·28²/6 = 3 659 mm³.
  - **M/S ≈ 6,9 MPa** (lama 6,6 MPa dengan a = 43,5 dan spacer 30 × 30).
  - Ditambah tekanan rata-rata ≈1 MPa, tekanan tepi maksimum **≈7,9 MPa**.
- ⚠ **Keterbatasan metode itu:** baut hanya ada 12 mm dari ujung, yaitu 16 mm dari tepi dalam spacer. Tanpa preload yang cukup, pelat cenderung berungkit di tepi dalam spacer:
  - tarik baut per ujung ≈ F·a / 16 ≈ 1,6 kN (≈0,8 kN per baut);
  - gaya kontak di tepi dalam ≈ F·(a + 16) / 16 ≈ 2,3 kN, terpusat di dekat tepi;
  - tekanan lokalnya bergantung pada lebar kontak (**TBD**) dan bisa jauh di atas 7,9 MPa.
- **Kesimpulan 3.2:** angka 6,9–7,9 MPa hanya berlaku bila preload baut cukup untuk menjaga seluruh permukaan spacer tetap tertekan. Torsi dan preload baut: **TBD**.
- **Risiko PLA:** creep/relaksasi preload. Washer logam di bawah kepala baut mengurangi tekanan di bawah kepala. Washer tidak mencegah creep spacer itu sendiri, jadi perlu cek ulang torsi setelah beberapa kali pakai (prosedur TBD).

### 3.3 Panjang baut M6 × 25
- **Panjang ulir masuk:** 25 − washer (≈1,6 mm, nilai tipikal ISO 7089; TBD) − pelat 10 − spacer 2,5 ≈ **10,9 mm**.
- **Ujung baut tidak menembus** permukaan seberang load cell (tinggi 22 mm), bila lubangnya tembus.
- **Bila lubang buta** dengan kedalaman ulir < ≈11 mm, baut akan mentok. Kedalaman ulir: **TBD**.
- **Kecukupan ulir:** ≈10,9 mm ≈ 1,8 × d. Untuk ulir di aluminium perlu dicek dengan kedalaman ulir sebenarnya.
- **Kepala baut dan washer** menonjol di luar pelat A (ujung tetap) dan pelat B (ujung bebas), 32 mm dari ujung pelat. Posisinya **di luar zona genggam** (42,5–127,5 mm). Ketebalan lokal di ujung bertambah setinggi washer + kepala (jenis kepala TBD). Tebal total ≈52 mm belum memasukkan kepala baut.

### 3.4 Lebar dan panjang spacer
- **Lebar:** spacer 28 mm. Bila load cell ternyata 30 mm, spacer lebih sempit 1 mm per sisi, tetapi tetap menutup kedua lubang: pusat ±7,5 mm + jari-jari 3,3 mm = 10,8 mm < 14 mm.
- **Panjang:** spacer 28 mm tidak boleh melewati blok ujung ke area tengah. Panjang blok ujung ≈27–28 mm hanya taksiran dari skala gambar penjual, jadi **ukur**. Bila blok hanya 27 mm, spacer 28 mm menumpang 1 mm di area tengah. Kasus boss_L = 24 mm sudah dihitung dan tetap lolos (2.1).

## 4. Catatan lain
- **Kapasitas load cell:** judul `koreksi_v4.md` menyebut CZL601 **80 kg**, sehingga 70 kgf (batas atas S1) = **87,5% dari kapasitas**.
  - Spesifikasi lama (2,0 mV/V, safe overload 150%, panjang kabel, dan seterusnya) milik load cell 180 kg dan **tidak berlaku lagi**. Datasheet CZL601 80 kg: **TBD**.
  - Karena stop overload belum dirancang, remasan di atas ≈80 kg tidak terlindungi. Ini perlu dipertimbangkan bersama batas overload dari datasheet.
- **Massa B:** pelat B Al 10 mm ≈138 g di ujung bebas, jauh di atas tolerance ±36 g di S1. Tare dan pengukuran harus dilakukan pada orientasi yang sama.
- **Grip hibrida:** pelat logam (potong dan bor di bengkel) + spacer dan penjepit PLA. Baut tidak masuk ke PLA, tetapi menembus spacer PLA yang ikut terjepit.

### 4.1 Asumsi kabel: diameter 5 mm (asumsi kerja, belum diukur)
- **Diameter kabel:** 5 mm, asumsi kerja dan belum diukur. Dokumen distributor menulis 4 mm. Ukur dengan jangka sorong saat barang tiba. Asumsi 5 mm lebih besar dari 4 mm, jadi aman untuk ruang. Bila kabel ternyata 4 mm, lubang penjepit harus diperkecil supaya kabel tetap terjepit.
- **Penjepit kabel di batang A:**
  - Lubang penjepit ≈ Ø kabel (5 mm). Kelonggaran atau jepitan (interferensi) supaya kabel tertahan tanpa tergencet: TBD.
  - Lebar dan tinggi penjepit ≥ Ø kabel + 2 × dinding. Dengan aturan dinding modul 3D printing (minimal 1,2 mm; ≈2 mm untuk bagian penahan beban), hasilnya ≈7,4–9 mm. Exploded menggambar ≈9 mm secara simbolik. Ukuran final TBD.
  - Penjepit tetap berada di sisa pelat A (0–20 mm dari ujung pelat) dan tidak masuk ke area di atas load cell.
- **Tempat kabel keluar dari ujung load cell ke penjepit:**
  - Ø5 mm lebih besar daripada celah 2,5 mm. Kabel **tidak boleh** dirutekan lewat celah A–LC atau B–LC.
  - Kabel harus keluar dari muka ujung load cell lalu naik ke penjepit di zona ujung pelat. Jarak dari ujung load cell ke ujung pelat 20 mm, dan sebagian dipakai penjepit.
  - Titik keluar kabel di muka ujung load cell (posisi dan tinggi): TBD. Ujung mana yang punya kabel: TBD.
- **Lengkungan sisa kabel di dekat penjepit:**
  - Radius tekuk **TBD**. Kaidah umum: beberapa kali diameter kabel; cek datasheet kabel.
  - ⚠ **Ruang tekuk:** tekukan dari titik keluar ke penjepit harus muat di zona ujung pelat (≤ 20 mm, dikurangi panjang penjepit). Bila radius tekuk minimum ternyata beberapa kali 5 mm, ruang ini mungkin tidak cukup. Penjepit mungkin harus digeser lebih jauh atau tekukan diletakkan di luar ujung pelat. Cek setelah radius tekuk diketahui.
- **Panjang kabel:** TBD. Listing penjual menulis sekitar 28 cm, dokumen distributor 0,42 m. Rencana housing elektronik terpisah di meja (Catatan Proyek 14.1) disusun dengan kabel load cell lama yang lebih panjang. Dengan kabel sependek ini, housing elektronik harus berada dalam jangkauan kabel, atau perlu kabel sambungan (cara sambung dan shielding: TBD).

## 5. Pertentangan dan cara penyelesaiannya
Aturan: ikuti instruksi yang lebih spesifik.

1. **Ukuran spacer dan geometri.** `koreksi_v3.md`: spacer 30 × 30, a = 43,5, x = 117, bentang 87. `koreksi_v4.md`: 28 × 28, a = 37, x = 102, bentang 74. → **Ikut `koreksi_v4.md`** (menggantikan v3 secara eksplisit, dan memakai ukuran load cell yang berlaku).
2. **Posisi lubang.** `koreksi_v3.md`: "posisi lubang TBD, jangan menulis angka koordinat". `koreksi_v4.md` dan instruksi pengguna: 12 dari ujung, 106 antar pasangan, 15 melintang. → **Angka ditulis.** Sumbernya gambar penjual dan instruksinya lebih spesifik. Diameter tetap TBD.
3. **Jumlah lubang.** `koreksi_v3.md`: "pola lubang 2 × 2 per ujung" (8 lubang). `koreksi_v4.md` dan pengguna: 4 × M6, dua per ujung. → **4 lubang.**
4. **Luas bersih spacer.** `koreksi_v4.md` E: "28 × 28 setelah empat lubang". Menurut geometri, tiap spacer hanya menutup dua lubang di ujungnya. → **Hitungan utama memakai 2 lubang**, dan nilai 4 lubang ditampilkan sebagai pembanding (3.1).
5. **Tabel acuan `koreksi_v4.md` E:** dua sel berbeda > 2% (lihat 2.1). Satu karena pembulatan, satu karena acuan tidak konsisten (Al 8 / boss 24, δ titik beban 0,16 → 0,176). Angka tidak disamakan.
6. **Setup kalibrasi.** `koreksi_v3.md` F.1 meminta `kalibrasi_setup_v5.svg`, `koreksi_v4.md` D meminta bertanya dulu, dan pengguna meminta jangan dibuat. → **Tidak dibuat.** Setup kalibrasi yang berlaku sekarang adalah protokol dumbbell (`kalibrasi_protokol.svg`), menurut `koreksi_v4.md`.
7. **Zona genggam.** v4 ≈90 mm, sedangkan `koreksi_v3.md` dan `koreksi_v4.md` menyebut ≈85 mm. → **85 mm.**
8. **Kasus Ø5,5.** Diminta sebagai kasus hitungan, tetapi tidak cocok untuk baut M6 (2.4). → Dihitung dan diberi tanda, tidak dihapus.
9. **"Stop overload".** Frasa ini muncul tepat satu kali di tiap SVG v5, sebagai catatan "Stop overload belum dirancang".
10. **Ujung tetap/bebas fisik TBD**, padahal gambar butuh satu ujung tetap. → Ujung tetap digambar di kiri sebagai konvensi gambar. Ujung fisik load cell (termasuk ujung kabel) yang dijadikan ujung tetap tetap TBD. Desain mengharuskan kabel keluar di ujung tetap.

## 6. TBD
- **Load cell:** lebar (28 atau 30), panjang blok ujung dan arti arsiran tengah, ujung tetap/bebas fisik, ujung keluar kabel, ulir tembus atau buta beserta kedalamannya, arah panah beban, tinggi penutup/area tengah, lenturan load cell pada 70 kgf, datasheet CZL601 80 kg (termasuk batas overload), dan kabel: diameter (asumsi kerja 5 mm, distributor 4 mm), panjang (listing ≈28 cm, distributor 0,42 m), radius tekuk minimum, serta titik keluar di muka ujung.
- **Pelat dan spacer:** Ø lubang pelat dan spacer, serta grade aluminium.
- **Baut:** jenis kepala, tebal washer, torsi dan preload, serta prosedur cek ulang torsi (creep PLA).
- **Bagian lain:** bahan dan bentuk akhir ridge dan bidang tumpu. Untuk penjepit kabel: bahan, lebar/tinggi final, serta kelonggaran atau jepitan lubang terhadap kabel.

## 7. Pengecekan sebelum selesai
1. **Teks:** kedua SVG v5 dirender di Chromium. Batas semua teks diukur otomatis: 0 tumpang tindih, 0 terpotong. Hasil render juga diperiksa visual.
2. **Bersentuhan:** di potongan, semua bentuk milik A (pelat, Spacer A, baut + washer, penjepit) dan milik B (pelat, Spacer B, baut + washer, ridge, bidang tumpu) dicek tidak bersentuhan pada geometri tanpa beban. Cek di bawah beban ada di bagian 2.2–2.3.
3. **Label dan frasa:** semua gambar bertanda "TIDAK BERSKALA". "Stop overload" muncul satu kali per SVG. Tidak ada eyelet.
4. **Berkas lama:** berkas v4 tidak diubah.
5. **Revisi kabel Ø5:** kedua SVG v5 dirender ulang dan dicek otomatis: 0 teks tumpang tindih, 0 terpotong. Hasil render juga diperiksa visual. A dan B tetap tidak bersentuhan pada geometri tanpa beban (penjepit kabel hanya terikat ke A). Tidak ada angka panjang kabel di gambar.
