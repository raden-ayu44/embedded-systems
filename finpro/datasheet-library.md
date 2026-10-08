# DS Library - rak "Komponen & Datasheet"

Rak ini menampung sumber tingkat komponen. Rak teori dan literatur (buku dan paper teoretis) ada di Bagian 11 `catatan-proyek-hgd.md`. Satu komponen = satu entri `DS-xxx`.

**Konvensi sumber untuk setiap entri**

| Kode | Sumber | Peran | Bisa disitasi sebagai sumber akademik? |
|---|---|---|---|
| S1 | Spesifikasi vendor (halaman produk) | Nilai spesifikasi barang yang kita beli. **Kolom spesifikasi selalu diisi dari S1.** | Tidak (dokumen penjual) |
| S2 | Datasheet pabrikan chip/komponen | Nilai yang diharapkan; dipakai untuk **memeriksa silang** S1 | Ya |
| S3 | Manual atau dokumen pihak ketiga | Pengamatan: keunggulan dan kelemahan yang ditemukan pada penerapan nyata | Dengan catatan (bukan pabrikan) |

**Label hasil pemeriksaan silang (S1 terhadap S2):** Konsisten / Lebih konservatif (S1 lebih ketat dari S2) / Tidak dinyatakan (S1 diam) / Konflik (S1 berbeda dengan S2 atau dokumen komponen lain).

## Indeks entri

| Kode | Komponen | Status |
|---|---|---|
| DS-HX1 | Modul HX711 (papan XFW-HX711, chip Avia) | Terisi, menunggu verifikasi saat barang tiba |
| DS-LC1 | Load cell Eagle Weigh CZL 601, 80 kg | Belum dipindahkan (lihat `daftar-isian-datasheet.md`) |
| DS-ESP1 | ESP32 (modul dan papan DevKit) | Belum |
| DS-LCD1 | LCD 1602 + backpack I2C | Belum |
| DS-LED1, DS-RES1, DS-BTN1 | LED, resistor, tombol | Belum |
| DS-PWR1 | Catu daya dan regulator | Belum |
| DS-MAT1 | Bahan (aluminium, PLA, baut M6) | Belum |
| DS-STD1 | OIML R60, VPG 11864 (standar dan catatan teknis) | Belum |

---

## DS-HX1: Modul HX711

### Identitas dan bukti

| Item | Isi |
|---|---|
| Modul | Papan hijau bertanda **XFW-HX711**, 24 x 16 mm (dari foto listing; ukur ulang dengan jangka sorong) |
| Chip | HX711 buatan **Avia Semiconductor** |
| S1 | Listing vendor CNC Store (Bandung) [1]: daftar spesifikasi di bawah dan foto papan. Tautan listing: https://shopee.co.id/MODULE-HX711-HX-711-AMPLIFIER-LOAD-CELL-ADC-CONVERTER-SENSOR-BERAT-i.62956347.3613589309 (tanggal akses: **ISI**) |
| S2 | Avia Semiconductor, *HX711 24-Bit Analog-to-Digital Converter (ADC) for Weigh Scales* (datasheet resmi, chip) [2]. Tautan: https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf (salinan di SparkFun; pabrikan Avia) |
| S3 | *HX711: 24-bit Delta Sigma ADC interface for weight scale*, PSoC Creator Component datasheet, v0.0.b, Rev. *B, 30 Maret 2020 (pihak ketiga, bukan pabrikan; berisi manual pemakaian dan catatan pengamatan) [3]. Tautan: https://community.infineon.com/gfawx74859/attachments/gfawx74859/CodeExamples/546/7/HX711_v0_0_B.pdf (tanggal akses: **ISI**). Dokumen ini sendiri merujuk S2 pada alamat SparkFun yang sama. |
| Bukti bahwa S3 membahas papan yang sama | Gambar 1 di S3 menunjukkan papan hijau bertanda XFW-HX711 dengan label pin yang sama dengan foto listing S1 (E+, E-, A-, A+, B-, B+ dan GND, DT, SCK, VCC) dan penanda 80Hz/10Hz di sisi atas. Foto S1 menunjukkan tanda "10Hz" di posisi yang sama. |
| Pendukung (bukan sumber utama) | Halaman produk e-Gizmo (Filipina) yang menyalin deskripsi Avia dan menampilkan papan yang sama |
| Catatan | Avia adalah pabrikan **chip**, bukan papan modul. Papan XFW-HX711 adalah desain pihak ketiga. Bagian papan (transistor regulator, filter RC input, resistor pemilih rate) tidak tercakup dalam S2. |

### Tabel A: spesifikasi vendor (S1), pemeriksaan silang ke S2, dan catatan S3

| No | Parameter | S1: vendor | S2: pemeriksaan silang ke Avia | Hasil | S3: catatan manual (pengamatan) |
|---|---|---|---|---|---|
| 1 | Kabel merah | Excitation+ atau VCC | Datasheet chip tidak mengatur warna kabel. Terminal papan bernama E+ (excitation positif jembatan). | Tidak dinyatakan (S2) | Banyak papan murah memiliki cacat PCB: terminal E- tidak tersambung ke ground dan mengambang di sekitar 0,6 V, sehingga E+ tidak teregulasi (sekitar 4,9-5 V). Kalau E- disambung ke GND, E+ stabil di sekitar 4,3 V (Lampiran 3). **Kelemahan.** |
| 2 | Kabel hitam | Excitation- atau GND | Idem; terminal E-. | Tidak dinyatakan (S2) | Idem (cacat E- mengambang). Perbaikan: kabel pendek dari E- ke pin GND (Gambar 14). |
| 3 | Kabel putih | Amplifier+, Signal+ atau Output+ | Chip memiliki masukan INA+ untuk kanal A. | Tidak dinyatakan (S2) | - |
| 4 | Kabel hijau | A-, S- atau O- | Chip memiliki masukan INA-. | Tidak dinyatakan (S2) | - |
| 5 | Tegangan operasi | 2,7 V - 5 V | AVDD dan DVDD 2,6 - 5,5 V; VSUP (regulator) 2,7 - 5,5 V. | **Lebih konservatif** | Skala penuh kanal A adalah +-20 mV (gain 128) pada AVDD 5 V. Pada papan tanpa cacat, E+ sekitar 4,3 V. |
| 6 | Arus operasi | < 1,5 mA | Operasi normal < 1,5 mA (analog 1400 uA, digital 100 uA tipikal); power down < 1 uA. | **Konsisten** | Kode komponen S3 dapat menghentikan ADC dan menaruhnya pada mode arus rendah. |
| 7 | Laju data | 10 SPS atau 80 SPS (dapat dipilih) | 10 SPS (RATE = 0) atau 80 SPS (RATE = DVDD) dengan osilator internal. | **Konsisten** | Pada papan, pemilihan dilakukan dengan memindahkan resistor 0 ohm (Gambar 4), **bukan lewat firmware**. Bawaan 10 Hz. **Kelemahan:** 80 SPS butuh modifikasi perangkat keras. |
| 8 | Penolakan 50 dan 60 Hz | Serentak (simultaneous) | Tercantum pada daftar fitur: "Simultaneous 50 and 60Hz supply rejection". Tanpa angka dB khusus untuk 50/60 Hz (yang tercantum: PSRR 100 dB pada gain 128, RATE = 0). | **Konsisten** (hanya sebagai klaim fitur) | Tidak dibahas. |
| 9 | Dual-channel 24 bit | Dual-channel, 24 bit | Dua masukan diferensial yang dapat dipilih; ADC 24 bit. Kanal A gain 128 atau 64; kanal B gain tetap 32 (+-80 mV pada 5 V). | **Konsisten** | Kode 24 bit adalah lebar kode, bukan resolusi efektif. Dengan noise 50 nV rms dan LSB sekitar 2,3 nV (hitungan kita, gain 128, AVDD 5 V), noise sekitar 21 LSB rms. Gain tidak dapat diubah saat berjalan pada komponen S3. |

### Tabel B: parameter yang kita pakai tetapi tidak disebut vendor (sumber: S2)

| Parameter | S1: vendor | S2: Avia | S3: catatan manual | Dipakai di |
|---|---|---|---|---|
| Skala penuh diferensial | Tidak dinyatakan | +-0,5 x (AVDD / gain): +-19,5 mV (5 V), +-12,9 mV (3,3 V), gain 128 (hitungan kita) | S3 membulatkan ke +-20 mV pada 5 V | Skala penuh dan resolusi |
| Rentang tegangan common-mode | Tidak dinyatakan | AGND + 1,2 V sampai AVDD - 1,3 V | - | Mengapa jembatan tidak boleh dieksitasi langsung 10 V |
| Noise masukan (gain 128) | Tidak dinyatakan | 50 nV rms (10 SPS), 90 nV rms (80 SPS) | Contoh S3: sel 1 kg, filter median 19 titik, akurasi jangka pendek sekitar 27 mg (sel dan papan mereka, bukan sel kita) | Jawaban noise ke asisten |
| Waktu settling | Tidak dinyatakan | 400 ms (10 SPS), 50 ms (80 SPS) | Empat pembacaan pertama setelah mulai (400 ms pada 10 Hz) berisi galat dan harus dibuang | Firmware (SIAP) |
| Drift suhu | Tidak dinyatakan | Offset +-6 nV/derajat C, gain +-5 ppm/derajat C | - | Pemanasan, tare |
| PSRR dan CMRR | Tidak dinyatakan | 100 dB (gain 128, RATE = 0) | - | Catu daya |
| Rentang suhu | Tidak dinyatakan | -40 sampai +85 derajat C | - | Batas pemakaian |
| Level logika DT dan SCK | Tidak dinyatakan | DVDD sebaiknya sama dengan catu MCU | - | Lihat Peringatan 2 |

### Catatan merit dan demerit dari S3

| Jenis | Isi |
|---|---|
| Merit | Menjelaskan komposisi papan tipikal: transistor regulasi dan jaringan RC sebagai low-pass di masukan. |
| Merit | Mencantumkan alur baca 2 kawat (24 clock data, 1-3 clock gain), tare dengan mengurangi offset, dan contoh filter median 19 titik (penundaan sekitar 1 s). |
| Merit | Contoh nyata: sensitivitas sekitar 920 counts/g pada sel 1 kg, akurasi jangka pendek sekitar 27 mg setelah filter. |
| Demerit | Cacat PCB E- mengambang pada banyak papan murah; dokumen tidak menyebut papan mana yang terkena. |
| Demerit | Kode dan API ditulis untuk PSoC, bukan ESP32; hanya konsepnya yang bisa dipakai. |
| Demerit | Dokumen pihak ketiga (2020), bukan peer-review, bukan dari pabrikan. |

### Peringatan untuk desain kita

1. **Warna kabel signal bertentangan dengan datasheet load cell.** S1 menyebut putih = Signal+ dan hijau = Signal-. Datasheet Eagle Weigh CZL 601 menyebut hijau = S+ dan putih = S-. Merah (E+) dan hitam (E-) sama. Kalau tertukar, pembacaan hanya berbalik tanda (tanpa kerusakan); sambungkan sesuai datasheet CZL 601 dan periksa tanda pembacaan saat uji pertama. Kalau tanda negatif, tukar kabel sinyal atau pakai kemiringan negatif saat kalibrasi.
2. **Level logika.** Avia menyarankan DVDD memakai catu yang sama dengan MCU. Pada papan tipikal, VCC memberi DVDD, sehingga jika modul dicatu 5 V, pin DT mengeluarkan logika 5 V ke GPIO ESP32 (3,3 V). Pilihan: (a) catu modul 3,3 V (perkiraan noise dan skala penuh di bawah), atau (b) catu 5 V dengan pembagi tegangan atau level shifter pada DT. **Periksa pada papan Anda** apakah VCC memberi DVDD.
3. **Cacat E-.** Ukur E- terhadap GND dan E+ terhadap GND saat papan tiba (lihat daftar cek).

**Perkiraan noise load cell 80 kg (eksitasi 2 mV/V, gain 128):**

| Eksitasi E+ | Skala penuh jembatan | Noise 10 SPS | Noise 80 SPS |
|---|---|---|---|
| 5,0 V | 10,0 mV | sekitar 0,40 g | sekitar 0,72 g |
| 4,3 V (papan tanpa cacat pada 5 V) | 8,6 mV | sekitar 0,47 g | sekitar 0,84 g |
| 3,3 V (catu 3,3 V) | 6,6 mV | sekitar 0,61 g | sekitar 1,09 g |

Ini hitungan dari noise Avia, **bukan** pengukuran; E+ yang sebenarnya pada catu 3,3 V bisa lebih rendah akibat drop regulator. Ukur E+ dan ganti angka ini dengan hasil uji noise 1000 sampel.

### Daftar cek saat modul tiba

| No | Pemeriksaan | Hasil |
|---|---|---|
| 1 | Foto papan: penanda XFW-HX711 dan pad 10Hz/80Hz | |
| 2 | Ukur PCB dengan jangka sorong (24 x 16 mm?) | |
| 3 | Catu modul pada tegangan pilihan; ukur E- terhadap GND (seharusnya sekitar 0 V; cacat bila sekitar 0,6 V) | |
| 4 | Ukur E+ terhadap GND dengan load cell tersambung (sekitar 4,3 V pada catu 5 V bila baik) | |
| 5 | Ukur AVDD dan tegangan pada pin VCC | |
| 6 | Status pad rate (10 SPS bawaan?) | |
| 7 | Tegangan logika pada DT saat bekerja | |
| 8 | Polaritas pembacaan dengan kabel sesuai datasheet CZL 601 | |
| 9 | Uji noise 1000 sampel, 10 dan 80 SPS | |

### Daftar pustaka DS-HX1 (IEEE)

Nomor [1]-[3] mengikuti urutan kemunculan di tabel Identitas. Seperti kode lokal lain di catatan ini, nomor ini baru berlaku di dokumen ini; saat disalin ke laporan, nomornya harus disesuaikan dengan daftar pustaka laporan.

[1] CNC Store Bandung, "Module HX711 HX-711 amplifier load cell ADC converter sensor berat," Shopee Indonesia, product listing. [Online]. Available: https://shopee.co.id/MODULE-HX711-HX-711-AMPLIFIER-LOAD-CELL-ADC-CONVERTER-SENSOR-BERAT-i.62956347.3613589309 (diakses 8 Okt. 2026).

[2] Avia Semiconductor, "HX711: 24-bit analog-to-digital converter (ADC) for weigh scales," datasheet, n.d. [Online]. Available: https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf (diakses 8 Okt. 2026).

[3] "HX711: 24-bit delta sigma ADC interface for weight scale," PSoC Creator Component Datasheet, v0.0.b, Rev. *B, Infineon Developer Community, Code Examples, Mar. 30, 2020. [Online]. Available: https://community.infineon.com/gfawx74859/attachments/gfawx74859/CodeExamples/546/7/HX711_v0_0_B.pdf (diakses 8 Okt. 2026).

**Catatan sitasi (hapus setelah dicek):**
- [1]: nama toko "CNC STORE BANDUNG" sudah dicocokkan dengan tangkapan layar halaman toko pada tautan yang sama (8 Okt. 2026). Judul diambil dari bagian URL; samakan dengan judul di halaman produk. Ganti tanggal akses bila Anda membukanya di tanggal lain. Parameter pelacak (`?xptdk=...`) pada tautan asli sengaja dibuang.
- [2]: dokumen tidak mencantumkan tanggal atau revisi pada halamannya ("n.d."); tautan adalah salinan yang di-hosting SparkFun, bukan situs Avia.
- [3]: penulis tidak tertulis di halaman dokumen (metadata PDF menyebut nama "Irina", tetapi itu bukan data yang dicetak, jadi tidak dipakai sebagai penulis). Tautan adalah lampiran komunitas, bukan dokumen resmi pabrikan.
- Halaman e-Gizmo (pendukung) tidak diberi nomor karena bukan sumber utama.
