# Instruksi: dua gambar baru untuk klem kabel (tampak depan dan tampak kiri)

Tugas ini terpisah dari `koreksi_v12.md`. Jangan mengubah gambar v4 sampai v11 dan jangan mengubah `koreksi_v12.md`. Buat dua berkas SVG baru:

- `klem_kabel_tampak_depan_v1.svg`
- `klem_kabel_tampak_kiri_v1.svg`

Tujuannya agar pemilik proyek melihat dengan tepat bentuk klem kabel (blok penjepit + rak pada Spacer A) sebelum memodelkan kupon uji cetak.

## Aturan keras

1. Anonim. Jangan menulis nama, NPM, kode mata kuliah, kampus, atau nama rekan. Satu-satunya penanda yang boleh ada hanya "embedded system". Sumber protokol hanya ditulis "V1".
2. Semua ukuran diambil dari `fusion_parameters_housing_grip_v8.csv`. Jangan menebak ukuran lain.
3. Tidak ada tulisan "TBD". Nilai yang masih asumsi diberi tanda "(asumsi)".
4. Bahasa label: Indonesia. Satuan mm.
5. Orientasi sama dengan gambar v11: pelat A di atas, pelat B di bawah, ujung tetap (ujung kabel) di kiri, lubang kabel dan kabel di muka depan.
6. Bukan gambar eksplorasi: bentuk blok, rak, dan lubang harus persis seperti di bawah.

## Sistem koordinat

Gunakan x ke kanan dari ujung load cell (x = 0), z ke bawah dari muka bawah pelat A (z = 0), d ke arah luar dari muka samping load cell (d = 0). Skala 10 px per mm.

Lapisan pada z (ke bawah):

- Pelat A: z -10 sampai 0, panjang x -20 sampai 150, lebar 30 (d -29 sampai 1).
- Spacer A (PLA): z 0 sampai 2,5, x 0 sampai 28, d -28 sampai 0.
- Load cell: z 2,5 sampai 24, x 0 sampai 130, d -28 sampai 0.
- Celah load cell ke pelat B: z 24 sampai 26,5.
- Pelat B: z 26,5 sampai 36,5.

Klem (satu cetakan dengan Spacer A):

- Rak: z 0 sampai 2,5, x 0 sampai 16, menjulur sampai d = 10 melewati sisi load cell.
- Blok: x 0,1 sampai 8,3 (lebar 8,2), d 1 sampai 9 (tebal 8, jarak 1 dari sisi load cell), z 0 sampai 17,4. Jarak bebas ke pelat B sekitar 9,1.
- Lubang kabel Ø4,1 menembus blok searah d, sumbu di x = 4,2 dan z = 13,25 (sama dengan tinggi lubang Ø5 load cell: 2,5 + 10,75).
- Dinding: samping 2,05 (kiri dan kanan lubang), atas 2,1, bawah 11,2 sampai ke rak.
- Kabel Ø4 dilem tembak lurus di dalam lubang blok. Tidak ada lem ke aluminium.
- Lubang Ø5 di load cell: pusat x = 4,2, z = 13,25. Kedalaman asumsi 14 (belum terukur), tulis "(asumsi, belum terukur)".
- Setelah blok, kabel menekuk bebas ke arah B dengan radius 10 (asumsi). Ini hanya arah rute.

## Gambar 1: `klem_kabel_tampak_depan_v1.svg` (dari muka kabel)

Pandangan dari muka depan: x ke kanan, z ke bawah. Gambar potongan lapisan sampai x = 40 dan beri garis patah di x = 40.

Isi:

- Pelat A, rak dan badan Spacer A, load cell, pelat B (pelat dan load cell abu-abu, PLA oranye). Rak digambar di depan badan spacer.
- Blok, lingkaran lubang Ø4,1, dan lingkaran kabel Ø4 (gelap) di dalamnya.
- Lingkaran putus-putus Ø5 di balik blok (lubang load cell).
- Pita kabel ke bawah dari lubang, dengan panah menuju B.
- Garis sumbu di x = 4,2 dan z = 13,25.
- Dimensi: rak 16; 4,2 dari ujung; blok 8,2 (garis dimensi di atas pelat A); 13,25; 17,4; jarak bebas ke B sekitar 9,1; celah load cell ke B 2,5.
- Nomor keterangan 1 sampai 4 di bawah gambar: (1) blok penjepit PLA 8,2 x 8 x 17,4 satu cetakan dengan rak Spacer A; (2) lubang Ø4,1 menembus blok, kabel Ø4 dilem tembak lurus tanpa lem ke aluminium; (3) kabel menekuk bebas ke arah B (R10, asumsi), hanya arah rute; (4) garis putus = lubang Ø5 load cell di balik blok.
- Catatan: dinding samping lubang = (8,2 - 4,1) / 2 = 2,05.

## Gambar 2: `klem_kabel_tampak_kiri_v1.svg` (potongan A-A di x = 4,2)

Pandangan dari ujung tetap ke arah +x, dipotong di sumbu lubang. Sumbu horizontal gambar adalah d, kanan gambar = sisi depan (muka kabel). Sumbu vertikal z ke bawah.

Isi:

- Bidang potong diarsir: pelat A (d -29 sampai 1), spacer + rak (d -28 sampai 10, z 0 sampai 2,5), load cell dengan lubang Ø5 (d 0 sampai -14, z 10,75 sampai 15,75), pelat B.
- Blok (d 1 sampai 9) terpotong menjadi dua bagian karena lubang Ø4,1: z 0 sampai 11,2 dan z 15,3 sampai 17,4.
- Kabel Ø4 gelap, dari dalam lubang load cell (d -12) lurus melewati blok, lalu melengkung R10 ke bawah (pusat busur pada d = 9, z = 23,25), lalu lurus ke bawah dengan panah.
- Dimensi: blok 8; rak menjulur 10; 13,25; 17,4; jarak bebas ke B sekitar 9,1; kedalaman lubang Ø5 sekitar 14 (asumsi); label "R10 (asumsi)".
- Catatan bawah: celah blok ke load cell 1; dinding atas lubang 2,1 dan bawah lubang 11,2; celah kabel ke lubang Ø5 = 0,5 per sisi; arah pandang; A di atas, B di bawah.

## Pemeriksaan sebelum selesai (D)

1. Render kedua SVG dengan Chromium dan periksa visual: tidak ada teks yang tertutup, tidak ada label yang terpotong di tepi kanvas, label tidak bertabrakan dengan garis dimensi atau kabel.
2. Cocokkan semua angka dengan CSV v8 (clamp_w, clamp_h, clamp_d, clamp_gap, shelf_t, shelf_L, shelf_out, clamp_hole_d, cable_exit_h, bend_r, cable_hole_d, cable_hole_x, cable_hole_z).
3. Grep kedua berkas: tidak ada nama, NPM, kode mata kuliah, kampus, atau kata "TBD".
4. Pastikan berkas v4 sampai v11 tidak berubah (checksum sebelum dan sesudah).

## Laporan (E)

Singkat: nama kedua berkas, hasil pemeriksaan D, dan apakah ada ukuran yang tidak ada di CSV v8 (bila ada, sebutkan, jangan menebak).
