# Instruksi untuk Cowork: spesifikasi gabungan (berlaku sampai v12)

Dokumen ini **menggabungkan** `koreksi.md`, `koreksi_v5.md` sampai `koreksi_v11.md`, dan koreksi v12 (arah panah stiker). Berkas lama itu dihapus pada 12 Okt. 2026; yang berlaku hanya dokumen ini. Ukuran dan asumsi rinci ada di `asumsi_v5.md`. Nilai parameter Fusion ada di `fusion_parameters_housing_grip_v8.csv` (tidak ada CSV v9 sampai v12).

Cara memakai: untuk tugas baru, tambahkan satu bagian "Tugas" di bagian 8 dan perbarui bagian lain bila ada nilai yang berubah. Jangan membuat berkas koreksi baru per revisi.

## 1. Aturan keras (berlaku untuk semua tugas)
1. **Jangan menimpa berkas lama.** Gambar baru diberi akhiran versi baru (`_v13`, dan seterusnya). Berkas SVG v4 sampai v12 dan klem v1 tetap utuh.
2. **Anonim.** Tanpa nama mata kuliah, nama orang (termasuk nama penulis sumber), NPM, kampus, atau identitas apa pun, di gambar, komentar, metadata SVG, komentar CSV, nama berkas, dan laporan. Satu-satunya label yang boleh: "embedded system". Sumber protokol cukup ditulis "V1".
3. **Hanya pakai angka dari dokumen ini, `asumsi_v5.md`, dan CSV v8.** Bila ada yang bertentangan dengan sumber lain, catat di laporan; jangan diam-diam diubah.
4. **Tidak ada "TBD".** Nilai asumsi diberi tanda "(asumsi)".
5. **Kabel sambungan dan shielding:** jangan digambar dan jangan dibahas. Tulis "di luar lingkup" bila perlu.
6. Gambar yang tidak berskala ditulis "TIDAK BERSKALA". Frasa "Stop overload belum dirancang" tepat satu kali per SVG yang memuatnya (tidak ada callout atau legenda yang menyebut celah sebagai stop overload).
7. Label Bahasa Indonesia, callout bernomor dengan legenda, satuan mm.
8. Jangan mengarang. Hasil hitungan dilaporkan apa adanya, tidak disesuaikan supaya terlihat lolos.

## 2. Berkas yang berlaku sekarang (folder `housing-grip/`)

| Berkas | Isi |
|---|---|
| `potongan_memanjang_v11_logam.svg` | Potongan memanjang (atas) dan tampak depan dari sisi kabel (bawah, 4,4 px/mm) |
| `exploded_isometrik_v12_logam.svg` | Exploded isometrik, panah stiker menunjuk ke arah B |
| `kalibrasi_setup_v11_20kg.svg` | Setup kalibrasi tahap 1 (sampai 20 kg), rakitan terbalik |
| `klem_kabel_tampak_depan_v1.svg`, `klem_kabel_tampak_kiri_v1.svg` | Tampak depan dan potongan A-A (x = 4,2) klem kabel; spesifikasi di `instruksi_klem_tampak.md` |
| `fusion_parameters_housing_grip_v8.csv` | Parameter Fusion |
| `asumsi_v5.md`, `protokol-kalibrasi-hgd.md`, `instruksi_klem_tampak.md` | Referensi, protokol, instruksi klem |

Potongan v11 dan setup v11 tidak memuat stiker, jadi tidak ada versi v12 untuk keduanya.

## 3. Nilai yang berlaku

### 3.1 Rakitan
| Item | Nilai |
|---|---|
| Load cell CZL 601 80 kg | 130 × 28 × 21,5 mm (terukur) |
| Lubang pasang di load cell | M6, tembus lurus dari kedua sisi, 12 mm dari ujung, 106 mm antar pasangan, 15 mm melintang (angka gambar penjual, ukur ulang) |
| Pelat A/B | Aluminium 6061-T6, 170 × 30 × 10 mm, polos, menjulur 20 mm melewati ujung load cell |
| Lubang pelat | Ø6,6 mm |
| Spacer PLA | 28 × 28 × 2,5 mm, lubang Ø7,0 mm; A di ujung kiri, B di ujung kanan |
| Baut | ISO 4017 M6 × 25, kelas 8.8, kepala segi enam, washer ISO 7089 tebal 1,6 mm; tonjolan kepala + washer 5,6 mm di luar pelat. Empat buah, dua per ujung |
| Torsi | 3 N·m (asumsi); kencangkan ulang sebelum tiap sesi kalibrasi; tanda cat pada kepala baut |
| Celah A/B ke load cell | 2,5 mm (celah bebas-sentuh) |
| Tebal total | 10 + 2,5 + 21,5 + 2,5 + 10 + ridge 5 = 51,5 mm (tanpa kepala baut) |
| Anggaran celah | lenturan pelat 0,24 + load cell 0,5 (asumsi) + penutup 1,0 (asumsi) + margin 0,3 (asumsi) = 2,04 mm; sisa ≈0,46 mm |
| Ridge | PLA tempel, 30 × 3 × 5 mm, dua buah, jarak 22 mm; bidang tumpu = permukaan pelat B |
| Geometri | zona genggam ≈85 mm (42,5–127,5 mm dari ujung pelat); a = 37, x = 102, bentang bebas 74 |
| Overload load cell | 96 kgf aman (120%), 120 kgf merusak (150%), sama dengan protokol bagian 9 |
| Alas karet (kalibrasi) | tebal 6 mm, satu slot 29 × 14 mm di bawah kedua kepala baut A |

### 3.2 Kabel dan klem (semua asumsi desain kecuali yang terukur)
| Item | Nilai |
|---|---|
| Kabel | Ø4 mm (terukur), ≈28 cm (asumsi), sisa jangkauan dari blok ≈27 cm |
| Muka keluar kabel | muka samping panjang load cell (130 × 21,5), **bukan muka ujung**; di muka depan pada gambar (menghadap pengamat) |
| Lubang kabel di load cell | Ø5 mm (terukur), pusat 4,2 mm dari ujung load cell (tepi ke arah tengah 6,7; dinding ke muka ujung 1,7), tengah tinggi: 10,75 mm dari muka atas dan bawah = 13,25 mm di atas permukaan pelat A. Kedalaman ≈14 mm (asumsi, belum terukur). Kabel tidak lewat celah 2,5 mm |
| Ujung berkabel | = ujung tetap = sisi A (kiri di gambar). Titik keluar 24,2 mm dari ujung pelat, di luar zona genggam |
| Spacer A dengan klem | satu cetakan PLA, ditahan baut, tanpa lem ke aluminium |
| Rak | tebal 2,5 mm sebidang spacer; 16 mm sepanjang batang (x 0–16 dari ujung load cell); menjulur 10 mm melewati sisi load cell (≈9 mm melewati tepi pelat A) |
| Blok penjepit | lebar 8,2 (x 0,1–8,3), tebal 8 ke arah luar (mulai 1 mm dari sisi load cell), tinggi ≈17,4 dari permukaan pelat A, berdiri di atas rak. Jarak bebas ke pelat B ≈9,1 (26,5 − 17,4). Letak 20–28 mm dari ujung pelat, di luar zona genggam |
| Lubang di blok | Ø4,1 (Ø kabel + 0,1), menembus menyamping, sumbu 13,25 di atas permukaan A dan 4,2 dari ujung load cell, segaris lubang Ø5. Dinding samping 2,05, atas 2,1 (ke arah B), bawah 11,2 (ke arah A, termasuk rak) |
| Perekat | lem tembak di lubang blok. Tanpa epoksi, tanpa pengikat kabel, tanpa lem ke aluminium |
| Lengkung bebas | kabel lurus menyamping lewat lubang Ø5 dan blok, lalu melengkung bebas, radius 10 mm (asumsi) |
| Panah stiker beban | di muka ujung bebas, sepanjang tebal 21,5, **menunjuk ke arah B** (A di atas), sesuai stiker pada benda asli |

### 3.3 Arah kabel dan arah panah
- **Posisi pakai** (protokol V1: duduk, bahu netral, siku 90°, pergelangan 0–30°): tangan kanan menggenggam, telapak di atas A, jari menekan B ke arah A. Lubang dan kabel di muka depan; lengkung bebas **ke arah B** (menggantung ke bawah), menuju housing LCD di tangan kiri, tidak melintas di atas telapak. Sama dengan model CAD pemilik proyek.
- **Arah lengkung hanya rute kabel**; kabel terpasang lurus di lubang blok.
- **Setup kalibrasi** (rakitan terbalik: A di bawah di atas alas karet): kabel diarahkan **turun ke permukaan atas alas karet** (rute khusus kalibrasi), supaya tidak naik ke ruang di bawah papan (kabel tidak tertekan, papan tidak menyentuh kabel). Ujung kabel bertumpu di atas alas, tidak masuk ke karet.
- **Panah stiker:** digambar menunjuk ke arah B. Jangan menulis klaim bahwa panah searah gaya tekan jari; cukup tulis arahnya. Catatan: gaya tekan sebenarnya (B ke arah A) berlawanan dengan panah, jadi pembacaan bertanda negatif bila skala tidak dibalik; tanda diatur di firmware (kemiringan skala negatif).

## 4. Spesifikasi gambar

### 4.1 Potongan memanjang
- Pertahankan skala, dimensi, ringkasan, catatan, dan legenda. Subjudul: "dilihat dari sisi kabel (depan); bagian di depan bidang potong dilepas dan digambar putus-putus".
- Potongan melewati satu baris lubang pasang (y = 7,5 mm dari garis tengah), sedangkan rak dan blok di y 14–24; jadi rak dan blok digambar putus-putus (di depan bidang potong). Tinggi rak 2,5 (x 0–16), blok 17,4 (x 0,1–8,3).
- Penanda lubang kabel: lingkaran putus-putus Ø5 (22 px) berisi titik penuh (⊙) pada 4,2 mm dan 13,25 mm. **Jangan memakai tanda ⊗** (artinya menjauhi pengamat; kabel keluar ke arah pengamat) dan jangan menggambar lubang Ø5 sebagai lubang bersih di bidang potong (kedalaman belum terukur).
- Legenda 12: "Kabel keluar menyamping ke arah pengamat, lubang Ø5 di muka samping (⊙; putus-putus = di depan bidang potong)". Legenda 13: "Klip pada Spacer A: rak + blok, Ø4,1 (di depan bidang potong; lihat tampak depan)". Legenda 14: "Lengkung kabel bebas R10 (asumsi), ke arah B; lihat exploded".
- Catatan jalur kabel: "Kabel lurus menyamping lewat blok, lalu lengkung bebas R10 (asumsi) ke arah B (ke bawah), menjauhi telapak". Catatan posisi pakai: "Posisi pakai (protokol V1, tangan kanan menggenggam, telapak di atas A): kabel keluar di muka depan, lengkung bebas ke arah B, menggantung ke bawah menuju housing LCD di tangan kiri (asumsi)".
- Ulir load cell digambar tembus (sepanjang 21,5), ujung baut tidak menembus muka seberang. Lubang pelat Ø6,6 dan spacer Ø7,0 pada callout.

### 4.2 Tampak depan (tampak 2 di bawah potongan)
- Judul "Tampak depan dari sisi kabel (tanpa potongan)". Skala 4,4 px/mm pada x dan z, celah 2,5 tidak diperbesar (tulis "celah sesuai skala"). Orientasi seperti potongan: A di atas, B di bawah, ujung tetap di kiri, x selaras dengan potongan (x = 0 di ujung load cell). Nol vertikal z = permukaan dalam pelat A, z positif ke bawah (menuju B).
- Isi (mm, x dari ujung load cell, z dari permukaan dalam A):

| Bagian | x | z |
|---|---|---|
| Pelat A | -20 sampai 150 | -10 sampai 0 |
| Spacer A, rak, blok | spacer 0–28; rak 0–16; blok 0,1–8,3 | spacer dan rak 0–2,5; blok 0–17,4 |
| Load cell | 0–130 | 2,5–24 |
| Spacer B | 102–130 | 24–26,5 |
| Pelat B | -20 sampai 150 | 26,5–36,5 |
| Ridge | seperti pada potongan | 36,5–41,5 |
| Kepala baut + washer | baut A di x 12 (di atas A, tonjolan 5,6); baut B di x 118 (di bawah B, tonjolan 5,6) | batang baut tidak digambar |
| Lubang blok Ø4,1 | pusat x 4,2 | pusat z 13,25 |
| Kabel Ø4 | x 4,2 | ujung kabel di lubang blok, lingkaran Ø4 berisi titik (⊙), mengarah ke pengamat |

- Spacer A, rak, dan blok satu arsiran PLA tanpa garis pemisah (satu cetakan); blok digambar di atas load cell.
- Pita kabel Ø4 dari ⊙ lurus **ke bawah** (ke arah B), digambar di atas pelat A, load cell, dan pelat B, berakhir **di bawah pelat B dan ridge** dengan panah ke bawah dan teks "ke housing elektronik". Teks: "lengkung R10 (asumsi) ke arah B, tampak lurus dari depan". Geser dimensi dan teks yang tertimpa, jangan pitanya.
- Dimensi yang harus ada: 4,2; 13,25; 17,4; 9,1 (tulis "≈9"); 8,2; 16; 2,5. Teks kecil: "rak menjulur 10 mm ke arah pengamat melewati sisi load cell (lihat tampak atas pada setup kalibrasi)".
- Klem hanya menyentuh pelat A lewat bidang Spacer A dan rak (ditahan baut). Blok dan rak tidak menyentuh pelat B (≈9) dan sisi load cell (1 mm).

### 4.3 Exploded isometrik
- Urutan dari atas: pelat A → Spacer A → load cell → Spacer B → pelat B; empat baut pola 2 × 2 (15 melintang, 106 antar pasangan). Warna logam dan PLA dibedakan di legenda.
- Spacer A digambar dengan rak (perpanjangan di sisi kabel) dan blok di atasnya, satu bagian; lubang Ø4,1 segaris lubang Ø5 di muka samping load cell (tengah tinggi, dekat ujung A).
- Jalur kabel: lurus keluar dari lubang menuju pengamat, lalu melengkung R10 **ke bawah, ke arah B**; panah dan teks "ke housing elektronik" di ujung bawah jalur. Pita turun di sisi luar kiri pelat B tanpa menimpa pelat, baut, atau callout.
- Stiker panah di muka ujung bebas (callout 19): kotak kuning tetap; panah dengan pangkal di y 544,2 dan kepala di y 571,8, x 610,6, **menunjuk ke bawah (ke arah B)**. Legenda 19: "Stiker panah beban pada ujung bebas, menunjuk ke arah B". Catatan (dua baris): "Stiker panah beban di muka ujung bebas menunjuk ke arah B (searah tebal 21,5), sesuai stiker pada benda asli. Bila arah panah terhadap gaya tekan terbalik, pembacaan hanya bertanda negatif; tandanya diatur di firmware (kemiringan skala negatif)." Jangan menulis "B → A" untuk stiker; panah gaya F "jari menekan" dan "telapak menekan" tetap.
- Legenda dan catatan klem: "Klip kabel menyatu dengan Spacer A (rak + blok), lubang Ø4,1, kabel dilem tembak, tanpa lem ke aluminium". Catatan jalur dan posisi pakai seperti 4.1.

### 4.4 Setup kalibrasi tahap 1 (sampai 20 kg)
- **Tampak samping memanjang** (seperti potongan, tetapi terbalik: A di bawah, B di atas): pelat A/B aluminium 10, spacer PLA 28 × 28 × 2,5 (A kiri, B kanan), load cell 130 × 28 × 21,5 dengan celah 2,5, baut M6 × 25 + washer (empat; dua terlihat). Kepala baut A di sisi luar bawah (dalam slot alas karet), kepala baut B di sisi luar atas, sekitar 53 mm dari pusat pelat.
- **Alas karet** di bawah A: tebal 6 mm, satu slot 29 × 14 mm di bawah kedua kepala baut.
- **Beban:** ridge di sisi luar B; balok PLA dengan lidah di antara dua ridge (selisih 1 mm dari puncak ridge); papan kayu 480 × 350 × 12; pemandu kayu 1 cm dari papan (tidak menyentuh); dumbbell berpasangan, pasangan 6 kg di bawah dengan pasangan 4 kg di atasnya (total 20 kg, satu di kiri dan satu di kanan garis tengah).
- **Tampak atas** papan dan dumbbell lapisan bawah (dua dumbbell 6 kg), garis putus-putus untuk B dan balok PLA di bawah papan. Rak dan blok klem menjulur ≈9 mm melewati tepi pelat A di sisi kabel; tidak bentrok dengan alas karet (slot 29 × 14).
- **Tabel titik ukur:** nol (tiga kali); dumbbell tunggal 1, 2, 3, 4, 5, 6 kg; pasangan 6 kg (12 kg); tambah pasangan 4 kg di atas 6 kg (20 kg); turun 12 kg dan nol akhir.
- **Inset detail rakitan** (diperbesar): celah 2,5, kepala baut A di dalam lubang alas, kepala baut B di luar balok PLA.
- **Catatan:** tumpukan 20 kg ≈19 cm di atas papan; 20 kg ≈29 persen dari 70 kgf, sisanya ekstrapolasi; usulan, belum diuji. Batas overload: "96 kgf aman (120%), 120 kgf merusak (150%), sama dengan protokol bagian 9".
- **Kabel:** teks di bawah detail: "kabel ke arah pengamat, lalu lengkung bebas R10 (asumsi) diarahkan turun ke alas karet (rute khusus kalibrasi: rakitan terbalik)". Catatan: "Pada posisi pakai kabel melengkung ke arah B; pada setup ini rakitan dibalik, jadi kabel diarahkan turun ke alas dan tidak naik ke ruang di bawah papan (kabel tidak tertekan, papan tidak menyentuh kabel)". Tampak samping dan detail: kabel berhenti di permukaan atas alas karet (y 586 pada tampak samping, y 992 pada detail), dengan panah kecil dan teks "ke housing elektronik".
- Tahap 2 (sampai 42 kg) tidak dikerjakan sekarang.

### 4.5 CSV Fusion
- Format enam kolom: `Name,Unit,Expression,Value,Comments,Favorite` (`Value` berisi nilai terhitung dengan satuan, misalnya `51.5 mm`; `Favorite` true atau false). Jangan memakai empat kolom.
- Wajib ada: `boss_L`, `lever_arm` (37 mm), `grip_zone`, `spA_c` (-51 mm), `spB_c` (51 mm), dengan ekspresi aslinya; `total_t` = `2 * bar_t + 2 * gap + LC_H + ridge_h` harus terbaca 51.5 mm; semua parameter klem, kabel, dan alas karet seperti di CSV v8. Parameter lama `clip_foot_L`, `clip_foot_W`, `clip_arm` sudah dihapus.
- Baris `hole_pitch`, `hole_cross`, `hole_edge` tetap bertanda "dari gambar penjual, ukur ulang". Komentar "asumsi desain" untuk nilai yang berstatus asumsi. CSV v8 adalah acuan; jangan membuat CSV baru bila tidak ada nilai yang berubah.

## 5. Pengecekan sebelum selesai (semua tugas)
1. Render SVG di Chromium: 0 teks tumpang tindih, 0 terpotong (ukur otomatis, lalu lihat hasil render); pita kabel tidak menimpa dimensi atau callout.
2. Pada geometri tanpa beban, bentuk milik A (pelat A, Spacer A + rak + blok, baut A) dan milik B tidak bersentuhan. Blok dan rak tidak menyentuh pelat B atau sisi load cell.
3. Konsistensi: kabel "ke arah B" di potongan dan exploded; "turun ke alas karet (rute kalibrasi)" di setup; lubang kabel dan kabel di muka depan di semua berkas; panah stiker ke arah B di exploded.
4. `grep` semua berkas baru: tidak ada "TBD", "⊗", "epoksi" atau "epoxy" (untuk klip), "bentuk L", "pengikat kabel", "B → A" (untuk stiker), nama orang, atau identitas. "V1" ada di catatan potongan dan exploded.
5. Berkas v4 sampai v12 dan klem v1 identik dengan sebelumnya (bandingkan checksum).
6. Hitung ulang: 10 + 2,5 + 21,5 + 2,5 + 10 + 5 = 51,5; 0,24 + 0,5 + 1,0 + 0,3 = 2,04; 2,5 − 2,04 = 0,46; 26,5 − 17,4 = 9,1; 13,25 − 2,5 = 10,75; 17,4 − 13,25 − 2,05 = 2,1; 13,25 − 2,05 = 11,2; (8,2 − 4,1) / 2 = 2,05; 6,7 − 2,5 = 4,2; 24,2 = 20 + 4,2; 4,2 mm × 4,4 = 18,5 px.

## 6. Laporan akhir (singkat)
Daftar berkas baru, hasil pengecekan di bagian 5, ukuran yang bertentangan antar sumber (bila ada), dan nilai asumsi yang dipakai.

## 7. Keputusan yang dibatalkan (jangan dihidupkan lagi)
| Keputusan lama | Diganti |
|---|---|
| Kabel keluar dari muka ujung, penjepit di zona ujung pelat, radius 20 mm, lubang Ø4,2, epoksi (v6) | Kabel keluar menyamping dari muka samping panjang (v7) |
| Klip PLA bentuk L ditempel epoksi di atas pelat A, lengkung 90° R10 ke ujung pelat, satu pengikat kabel (v7) | Klem menyatu dengan Spacer A, lem tembak, lengkung bebas (v8) |
| Panah stiker ke bawah (v7), lalu ke atas dengan klaim "searah gaya B → A" (v8) | Panah ke arah B, tanpa klaim arah gaya (v12) |
| Lengkung kabel ke arah A di semua gambar (v9, v10) | Ke arah B pada posisi pakai; turun ke alas karet hanya di setup kalibrasi (v11) |
| Tanda ⊗ untuk lubang kabel di potongan (v8) | ⊙ dengan lingkaran putus-putus Ø5 (v9) |
| Ujung kabel masuk ke karet di setup (v8) | Berhenti di permukaan atas alas karet (v9) |
| Orientasi A di bawah, varian PLA, eyelet, celah 1,5 mm (v2 sampai v4) | Lihat riwayat di `asumsi_v5.md` bagian 9 |

## 8. Tugas
Saat ini tidak ada tugas Cowork yang terbuka. Tugas terakhir (klem tampak depan dan kiri, exploded v12) sudah selesai dan diperiksa. Tugas baru ditambahkan di sini sebagai bagian bernomor, lengkap dengan berkas masukan dan keluaran.
