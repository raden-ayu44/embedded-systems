---
title: Catatan Riset & Perencanaan - Hand Grip Dynamometer

---

# Catatan Riset & Perencanaan - Hand Grip Dynamometer
**Final Project - Embedded Systems Course**

> Dokumen ini BUKAN proposal. Ini adalah wadah (vessel) yang menyimpan semua informasi, rujukan, dan keputusan yang sudah diambil sejauh ini, agar penyusunan proposal G1 nanti tinggal menyusun ulang isi dokumen ini ke dalam format yang diminta.

---

## 1. RINGKASAN PROYEK

| Item | Detail |
|------|--------|
| Mata kuliah | Mata kuliah embedded system (biomedik) |
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
| Arsitektur sistem + kelayakan teknis | Sebagian besar - lihat Bagian 6 (state machine 2 lapisan lengkap dengan keputusan teknis per state; pin-out diagram blok komponen belum) |
| BOM dalam anggaran Rp300.000 | **BELUM** |
| Jadwal selaras dengan gerbang proyek | **BELUM** |
| Daftar risiko & mitigasi | **BELUM** |

---

## 4. EVOLUSI PERUMUSAN MASALAH

Keputusan populasi target berubah beberapa kali selama diskusi - dicatat di sini supaya alasan penolakan versi-versi sebelumnya tidak hilang.

| Versi | Populasi target | Alasan ditolak/direvisi |
|-------|------------------|--------------------------|
| v1 | Pasien pasca-stroke | Terlalu besar skopnya untuk proyek satu semester; butuh proses rekrutmen populasi rentan yang lebih rumit dari yang bisa ditangani jadwal kelas |
| v2 | Mahasiswa teknik, argumen berbasis tugas okupasional (mengetik/coding, menyolder, menggambar manual) | Lebih kuat, tapi populasinya (lintas fakultas) masih sulit direkrut secara realistis |
| **v3 (final)** | **Mahasiswa Teknik Elektro, Teknik Biomedik, dan Teknik Komputer** (satu departemen di fakultas teknik) | Dipilih karena: (1) tidak mudah ditebak arah hasilnya - benar-benar pertanyaan terbuka; (2) populasi realistis direkrut karena satu departemen; (3) penulis sendiri adalah mahasiswa Teknik Biomedik, memberi motivasi personal yang sah tanpa anekdot yang perlu dijelaskan |

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

Dirancang berlapis (hierarchical state, lihat §6.4) - bukan satu loop datar seperti draf awal. **Lapisan luar** menangani satu sesi (3 percobaan + istirahat + ringkasan). **Lapisan dalam** menangani satu percobaan tunggal (4 state). Lapisan dalam "bersarang" di dalam satu kotak pada lapisan luar.

### 6.1 Lapisan luar (per sesi)

```
[Siklus percobaan] --(< 3 kali)--> [Istirahat: timer 1 menit] --> kembali ke [Siklus percobaan]
[Siklus percobaan] --(= 3 kali)--> [Ringkasan: rata-rata & histori] --> [Sesi baru dimulai]
```

- **Istirahat**: timer 1 menit sesuai protokol standar (Box 1, Vaishya) untuk mencegah kelelahan otot memengaruhi percobaan berikutnya.
- **Ringkasan**: hitung rata-rata 3 percobaan, ambil riwayat sesi lalu untuk perbandingan ("lebih kuat dari sesi lalu"), kirim ke cloud/log lokal.

### 6.2 Lapisan dalam (satu siklus percobaan): SIAP -> GENGGAM -> HITUNG -> RESPON

**[SIAP]**
- Menunggu interrupt tombol (bukan polling `digitalRead()`), agar tetap non-blocking (Sub-CPMK 3).
- Keputusan terbuka: debounce software (abaikan re-trigger < ~50ms sejak interrupt terakhir) vs debounce hardware (kapasitor).
- Keputusan terbuka: apakah tare otomatis dijalankan setiap kali masuk state ini, supaya drift nol dari percobaan sebelumnya tidak terbawa.
- Tidak ada jalur ke ERROR dari state ini.

**[GENGGAM]**
- Loop baca ADC dari HX711, terapkan `calibration_factor`, lacak nilai puncak (`ref` hanya naik: `if (result >= ref) ref = result;`). Tampilkan real-time ke LCD.
- Keputusan terbuka: `get_units()` pada library HX711 umum bersifat blocking (menunggu pin DOUT turun) - berpotensi bentrok dengan tuntutan non-blocking. Opsi (a) terima sebagai "acceptable blocking window" (~100ms pada 10Hz), dijustifikasi di makalah; opsi (b) polling `is_ready()` non-blocking digabung state kecil di dalam GENGGAM.
- Keputusan terbuka: exit trigger - gaya turun kembali di bawah ambang ATAU durasi maksimum tercapai (misal 5 detik), mengacu protokol Vaishya (tahan 3-5 detik).
- Keputusan terbuka: refresh rate LCD dibuat lebih jarang (misal 100-150ms via timer terpisah) daripada sample rate sensor, supaya tidak membebani I2C/LCD tanpa menambah nilai.
- Transisi keluar: ke HITUNG (normal), atau ke ERROR (HX711 tidak `is_ready()` dalam batas waktu tertentu / nilai ADC mendekati saturasi 24-bit).

**[HITUNG]**
- One-shot (bukan loop), dieksekusi sekali begitu GENGGAM selesai. Validasi rentang nilai `ref` terhadap kapasitas load cell (bukan langsung dipercaya). Simpan ke posisi percobaan ke-1/2/3.
- Sengaja TIDAK menghitung relative HGS di sini - tetap dipindah ke analisis data pasca-pengukuran sesuai keputusan skop di Bagian 5.
- Keputusan terbuka: smoothing (filter moving-average) dijalankan di GENGGAM sebelum dibandingkan ke `ref` (lebih sederhana, direkomendasikan untuk skop kelas), atau di HITUNG sesaat sebelum finalisasi (lebih presisi, lebih kompleks).
- Keputusan terbuka: nilai float mentah tetap disimpan di memori sebelum dibulatkan untuk tampilan LCD, supaya presisi tidak hilang untuk analisis akurasi nanti (lihat §6.4, Bab 5 Marwedel).
- Transisi keluar: ke RESPON (lolos validasi), atau ke ERROR (nilai di luar rentang fisik yang masuk akal).

**[RESPON]**
- Trigger buzzer/LED/motor getar (Sub-CPMK 5) + tampilkan hasil dengan konteks dalam-sesi ("Percobaan 2 dari 3 - 27.1 kg"). Perbandingan lintas sesi BUKAN di sini - itu terjadi di RINGKASAN (lapisan luar).
- Keputusan terbuka: feedback harus non-blocking - catat `millis()` saat masuk state, matikan buzzer/LED setelah durasi lewat ambang, dicek di loop utama (bukan `delay()`).
- Keputusan terbuka: urutan sinyal serentak vs berurutan (misal LCD update dulu, baru buzzer 100ms kemudian) - memengaruhi struktur timer non-blocking.
- Keputusan terbuka: apakah state ini menahan alur sampai buzzer selesai, atau langsung lanjut ke lapisan luar sambil buzzer masih menyala di background (butuh flag status terpisah).
- Tidak ada jalur ERROR dari state ini (nilai sudah tervalidasi di HITUNG).
- Transisi keluar (bercabang ke lapisan luar): percobaan < 3 -> ISTIRAHAT; percobaan = 3 -> RINGKASAN.

### 6.3 Diagram blok komponen (pin-out belum lengkap - lihat Bagian 9)
`Load cell -> HX711 (amplifier + 24-bit ADC) -> ESP32 -> {LCD, buzzer/LED, WiFi/cloud}`

### 6.4 Referensi teori (Marwedel, *Embedded System Design*, ed. 4)
- Formalisasi hierarki dua lapisan di atas: **Bab 2, §2.4 Communicating Finite State Machines**, khususnya **§2.4.2 StateCharts** (hierarchical & orthogonal states).
- Pipeline sensor/ADC (GENGGAM): **Bab 3, §3.2.1 Sensors, §3.2.2 Sample-and-Hold, §3.2.4 ADC**.
- Aktuator/PWM (RESPON): **Bab 3, §3.6.1 DAC, §3.6.3 Pulse-Width Modulation, §3.6.4 Actuators**.
- Metodologi validasi akurasi (untuk Bagian 9): **Bab 5, §5.3 Quality Metrics** (RMSE/MAE terhadap beban referensi).
- Metodologi daftar risiko (untuk Bagian 9): **Bab 5, §5.6.5 Fault Tree Analysis & FMEA**.

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
| Diagram blok komponen lengkap (bukan hanya alur state) | Sebagian | Alur state machine 2 lapisan sudah lengkap (Bagian 6); yang belum cuma pin-out dan interface spesifik (SPI/bit-bang HX711, dst.) |
| BOM dengan harga riil, dalam Rp300.000 | Belum dimulai | |
| Jadwal kerja selaras dengan gerbang G1-G4 | Belum dimulai | |
| Spesifikasi terukur - akurasi | Belum dimulai | Metodologi sudah diidentifikasi: RMSE/MAE terhadap beban referensi (Marwedel Bab 5 §5.3, lihat Bagian 6.4) |
| Daftar risiko & mitigasi | Belum dimulai | Metodologi sudah diidentifikasi: kerangka FMEA (Marwedel Bab 5 §5.6.5, lihat Bagian 6.4); perlu mencakup risiko studi banding 3 jurusan: rekrutmen tidak seimbang, sampel kecil, variabel perancu (usia, olahraga, tangan dominan) |
| Proses consent informal untuk partisipan | Disebutkan, belum didetailkan | Cukup persetujuan lisan/tertulis sederhana, bukan proses etik formal |

---

## 10. CATATAN TERBUKA / PERTANYAAN YANG BELUM TERJAWAB

- Berapa target jumlah partisipan per jurusan? (mempengaruhi validitas perbandingan 3 kelompok)
- Apakah akan menggunakan tangan dominan saja, atau kedua tangan?
- Bagaimana bentuk pencatatan riwayat sesi ditampilkan ke pengguna - cukup di serial monitor untuk demo, atau perlu dashboard sederhana?

---

*Dokumen ini adalah catatan riset dan perencanaan untuk proposal akhir mata kuliah embedded system (biomedik). Bukan proposal final - gunakan sebagai bahan mentah untuk menyusun dokumen proposal G1 sesuai format yang diminta dosen.*
