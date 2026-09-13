---
title: Catatan Riset & Perencanaan - Hand Grip Dynamometer

---

# Catatan Riset & Perencanaan - Hand Grip Dynamometer
**Final Project - Sistem Embedded Biomedik dan Praktikum (ENBM605026)**
**Universitas Indonesia - Program Studi Teknik Biomedik**

> Dokumen ini BUKAN proposal. Ini adalah wadah (vessel) yang menyimpan semua informasi, rujukan, dan keputusan yang sudah diambil sejauh ini, agar penyusunan proposal G1 nanti tinggal menyusun ulang isi dokumen ini ke dalam format yang diminta.

---

## 1. RINGKASAN PROYEK

| Item | Detail |
|------|--------|
| Mata kuliah | Sistem Embedded Biomedik dan Praktikum (ENBM605026) |
| Institusi | Universitas Indonesia, Fakultas Teknik, Program Studi Teknik Biomedik |
| Posisi saat ini | Minggu ke-4 (topik: ADC, sensor analog, peripheral serial) |
| Platform wajib | ESP32 (Arduino IDE) |
| Anggaran komponen | Maksimum Rp300.000 per kelompok, dengan bukti pembelian |
| Filosofi cakupan | Menguji keterampilan teknis mahasiswa - BUKAN prototipe siap produksi massal |
| Perangkat | Hand grip dynamometer |

---

## 2. SUMBER RUJUKAN

| Sumber | Fokus utama | Kontribusi ke proyek ini |
|--------|-------------|---------------------------|
| Ramadhani et al. 2019 (IJEEEMI) | Alat ukur genggam pasien pasca-stroke: Arduino Uno + HX711 + load cell batang + LCD 16x2 + indikator 3-tingkat | Arsitektur paling sederhana dan paling dekat dengan skala proyek kelas - jadi referensi utama arsitektur hardware |
| Gotthelf et al. 2021 (J NeuroEng Rehab) | Sistem grip berbasis game (Rocket Launch), tracking MVC + fatigue selama sesi, divalidasi terhadap data normatif literatur | Sumber ide "pengukuran serial dari waktu ke waktu", TIDAK diadopsi fitur game-nya (di luar skop kelas) |
| Becerra et al. 2021 (Applied Sciences, UIB) | Perangkat wireless multi-sensor: gaya genggam + tekanan jari (FSR) + orientasi/tremor (IMU) + Bluetooth | Referensi untuk memahami instrumentation amplifier (AD627) sebagai alternatif HX711 - TIDAK diadopsi multi-sensornya (di luar skop kelas) |
| Chang & Chen 2015 (Bio-Med Mat & Eng, Taiwan) | Dynamometer + NI DAQ + LabView, data normatif Taiwan berdasarkan usia/tinggi/berat/panjang telapak | Referensi metodologi korelasi (tinggi, berat, panjang tangan vs kekuatan genggam) - platform (NI DAQ) TIDAK relevan untuk ESP32 |
| Vaishya et al. 2024 (J Health Pop & Nutrition) | Narrative review: HGS sebagai vital sign baru, cutoff per populasi, asosiasi dengan T2D/CVD/mortalitas/sarcopenia, protokol pengukuran (Box 1) | Sumber argumen medis utama proposal + protokol pengukuran standar (duduk, siku 90 derajat, tahan 3-5 detik, 3 kali percobaan, istirahat 1 menit antar percobaan) + konsep relative HGS (HGS/BMI) |
| Marwedel, *Embedded System Design* (ed. 4) | Buku teks embedded system | Bab 1 dipakai untuk definisi formal dan justifikasi pemilihan platform (lihat Bagian 8) |

---

## 3. KEBUTUHAN DARI BRP (Buku Rancangan Pengajaran)

### 3.1 Gerbang Proyek & Tenggat Waktu

| Minggu | Tonggak |
|--------|---------|
| 5-6 | Proposal + Design Review (**G1**) - draf disusun sekarang |
| 7 | Tenggat berkas gerber (wajib untuk ikut batch fabrikasi kolektif) |
| 9 | **G2** - jalur penginderaan & aktuasi hidup di breadboard, PCB dipesan kolektif |
| 11-12 | PCB diterima; **G3** - PCB dirakit & lolos uji dasar |
| 14 | **G4** - purwarupa terintegrasi lolos uji mandiri |
| 16 | UAS - demo expo, makalah, viva individu |

### 3.2 Rubrik G1: Proposal dan Design Review (checklist)

| Bagian wajib | Status di dokumen ini |
|---|---|
| Perumusan masalah medis | Selesai - lihat Bagian 4 |
| Spesifikasi terukur (range, akurasi, waktu respons, daya) | **BELUM** |
| Arsitektur sistem + kelayakan teknis | Sebagian - lihat Bagian 6 (alur state machine ada, diagram blok komponen lengkap belum) |
| BOM dalam anggaran Rp300.000 | **BELUM** |
| Jadwal selaras dengan gerbang proyek | **BELUM** |
| Daftar risiko & mitigasi | **BELUM** |

---

## 4. EVOLUSI PERUMUSAN MASALAH

Keputusan populasi target berubah beberapa kali selama diskusi - dicatat di sini supaya alasan penolakan versi-versi sebelumnya tidak hilang.

| Versi | Populasi target | Alasan ditolak/direvisi |
|-------|------------------|--------------------------|
| v1 | Pasien pasca-stroke | Terlalu besar skopnya untuk proyek satu semester; butuh proses rekrutmen populasi rentan yang lebih rumit dari yang bisa ditangani jadwal kelas |
| v2 | Mahasiswa teknik secara umum, argumen berbasis hobi personal (crafting, menggambar) | Terlalu bergantung pada anekdot pribadi, sulit digeneralisasi ke pembaca proposal |
| v3 | Mahasiswa teknik, argumen berbasis tugas okupasional (mengetik/coding, menyolder, menggambar manual) | Lebih kuat, tapi populasinya (lintas fakultas) masih sulit direkrut secara realistis |
| **v4 (final)** | **Mahasiswa Teknik Elektro, Teknik Biomedik, dan Teknik Komputer** (satu departemen: Departemen Teknik Elektro UI) | Dipilih karena: (1) tidak mudah ditebak arah hasilnya - benar-benar pertanyaan terbuka; (2) populasi realistis direkrut karena satu departemen; (3) penulis sendiri adalah mahasiswa Teknik Biomedik, memberi motivasi personal yang sah tanpa anekdot yang perlu dijelaskan |

> **Rumusan masalah (draf kerja):**
> Berbagai jurusan di Departemen Teknik Elektro menuntut penggunaan tangan secara berbeda dan berkelanjutan - mahasiswa Teknik Komputer terbiasa mengetik/coding dalam waktu lama, mahasiswa Teknik Elektro banyak menyolder dan menangani komponen kecil, sementara mahasiswa Teknik Biomedik kerap melakukan keduanya. Belum ada cara sederhana untuk memantau apakah pola penggunaan tangan ini memengaruhi kekuatan genggam dari waktu ke waktu - celah inilah yang coba dijawab alat ini, sekaligus menguji apakah perbedaan jurusan benar-benar berkorelasi dengan kekuatan genggam atau tidak.

---

## 5. FUNGSI PERANGKAT (Keputusan Skop)

| # | Fungsi | Sub-CPMK terkait | Sumber ide | Status |
|---|--------|-------------------|------------|--------|
| 1 | Pembacaan gaya real-time (kg/N) | Sub-CPMK 4 (ADC) | Semua paper referensi | Wajib |
| 2 | Penangkapan gaya puncak per percobaan (MVC) | Sub-CPMK 4 | Ramadhani, Gotthelf, protokol Vaishya (Box 1) | Wajib |
| 3 | Tampilan hasil (LCD/serial) | Sub-CPMK 4 | Semua paper referensi | Wajib |
| 4 | Umpan balik aktuator (buzzer/LED/motor getar) saat percobaan selesai | Sub-CPMK 5 (aktuator) | Tidak ada di paper - ditambahkan agar Sub-CPMK 5 punya tempat wajar di perangkat ini | Wajib |
| 5 | Pencatatan data lintas-sesi (cloud/lokal) | Sub-CPMK 7 (IoT) | Argumen utama Vaishya: nilai klinis HGS datang dari **pengukuran serial**, bukan sekali baca | Wajib |
| 6 | Rata-rata 3 percobaan + timer istirahat | - | Protokol standar Box 1 (Vaishya): 3 percobaan per tangan, istirahat ~1 menit | Opsional (murah, hanya logika software) |

**Sengaja TIDAK dimasukkan** (di luar skop "uji keterampilan teknis"):
- Relative HGS (butuh input tinggi/berat + logika tambahan) - **dipindah ke tahap analisis data pasca-pengukuran**, bukan fitur firmware
- Game biofeedback penuh ala Gotthelf - itu proyek software/UX, bukan embedded
- Sensor jari (FSR) + IMU tremor ala Becerra - di luar cakupan penilaian mata kuliah

**Variabel yang tetap dicatat manual (bukan fitur firmware), untuk analisis data di makalah akhir:**
tinggi badan, berat badan, tangan dominan, jam coding/menyolder/menggambar per minggu, frekuensi olahraga. (Dipakai untuk menghitung relative HGS dan mengendalikan variabel perancu saat membandingkan 3 jurusan.)

---

## 6. ARSITEKTUR SISTEM (Alur State Machine)

```
MULAI
│
└─ LOOP (setiap sesi pengukuran)
   │
   ├─ [WAIT] Menunggu tombol mulai ditekan
   │
   ├─ [SENSE] Baca ADC dari HX711 (load cell)
   │
   ├─ [PROCESS] Terapkan calibration_factor -> nilai kg/N
   │             (opsional: filter moving-average, rata-rata 3 percobaan)
   │
   ├─ [OUTPUT] Tampilkan di LCD + bunyikan buzzer/nyalakan LED
   │            + kirim ke cloud/log lokal
   │
   └─ Kembali ke [WAIT] untuk sesi berikutnya
```

**Diagram blok komponen (belum lengkap - lihat Bagian 3.2):**
`Load cell -> HX711 (amplifier + 24-bit ADC) -> ESP32 -> {LCD, buzzer/LED, WiFi/cloud}`

---

## 7. NARASI PENGALAMAN PENGGUNA

- Pengguna: mahasiswa teknik, tidak diasumsikan punya latar belakang teknis alat ini
- Mengambil alat: cukup kecil digenggam satu tangan, layar/lampu menunjukkan alat siap
- Memulai: satu tombol, konfirmasi jelas ("Squeeze now")
- Saat meremas: umpan balik visual real-time (angka naik / bar terisi)
- Selesai: sinyal jelas (bunyi/getar/visual), hasil ditampilkan dengan konteks ("lebih kuat dari sesi lalu"), bukan angka mentah tanpa makna
- Antar sesi: alat/dashboard mengingat riwayat, menunjukkan tren - ini adalah **inti nilai alat**, bukan fitur tambahan
- Yang harus dihindari: pengguna tidak boleh melihat angka mentah belum terkalibrasi; kegagalan pembacaan tidak boleh senyap

---

## 8. CATATAN PLATFORM: ESP32 vs RASPBERRY PI

- G1 (proposal) jatuh tempo minggu 5-6; Raspberry Pi baru diajarkan minggu 10 (Sub-CPMK 8) - artinya arsitektur inti proyek **realistisnya harus ESP32-only** saat proposal ditulis
- Raspberry Pi dicatat sebagai **kemungkinan ekstensi pasca-minggu 10** (mis. sebagai local data hub/dashboard), bukan kebutuhan wajib
- Edge AI (minggu 11, Sub-CPMK 9) dinilai **tidak relevan** dipaksakan ke proyek ini - tidak ada tugas inferensi on-device yang bermakna untuk dynamometer

**Justifikasi ESP32 (dari Marwedel Bab 1, Definisi 1.1 & Tabel 1.2):**
> "Embedded systems are information processing systems embedded into enclosing products." - ESP32 di dalam alat genggam ini persis memenuhi definisi ini.

| Kriteria (Tabel 1.2 Marwedel) | Embedded (ESP32) | PC-like |
|---|---|---|
| Arsitektur | Kompak, heterogen | Tidak kompak, homogen |
| Tujuan optimasi | Energi, ukuran | Performa rata-rata |
| Relevansi real-time | Sering penting | Jarang |
| Safety-critical | Mungkin | Biasanya tidak |

Argumen proposal: alat genggam butuh ukuran kompak, daya rendah, dan pewaktuan yang bisa diprediksi (non-blocking) - ESP32 cocok, PC/laptop tidak.

---

## 9. AREA YANG BELUM DIBAHAS (Checklist Terbuka)

| Area | Status | Catatan |
|------|--------|---------|
| Spesifikasi terukur (range gaya, akurasi, waktu respons, anggaran daya) | Belum dimulai | Perlu ditentukan sebelum BOM (kapasitas load cell bergantung pada range target) |
| Diagram blok komponen lengkap (bukan hanya alur state) | Sebagian | Perlu pin-out dan interface spesifik (SPI/bit-bang HX711, dst.) |
| BOM dengan harga riil, dalam Rp300.000 | Belum dimulai | |
| Jadwal kerja selaras dengan gerbang G1-G4 | Belum dimulai | |
| Daftar risiko & mitigasi | Belum dimulai | Perlu mencakup risiko studi banding 3 jurusan: rekrutmen tidak seimbang, sampel kecil, variabel perancu (usia, olahraga, tangan dominan) |
| Proses consent informal untuk partisipan | Disebutkan, belum didetailkan | Cukup persetujuan lisan/tertulis sederhana, bukan proses etik formal |

---

## 10. CATATAN TERBUKA / PERTANYAAN YANG BELUM TERJAWAB

- Berapa target jumlah partisipan per jurusan? (mempengaruhi validitas perbandingan 3 kelompok)
- Apakah akan menggunakan tangan dominan saja, atau kedua tangan?
- Bagaimana bentuk pencatatan riwayat sesi ditampilkan ke pengguna - cukup di serial monitor untuk demo, atau perlu dashboard sederhana?

---

*Dokumen ini adalah catatan riset dan perencanaan untuk proposal akhir mata kuliah Sistem Embedded Biomedik dan Praktikum (ENBM605026), Universitas Indonesia. Bukan proposal final - gunakan sebagai bahan mentah untuk menyusun dokumen proposal G1 sesuai format yang diminta dosen.*
