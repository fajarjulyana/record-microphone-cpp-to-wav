# Program Perekaman Mikrofon ke WAV

Program ini memungkinkan Anda untuk merekam input dari mikrofon dan menyimpannya sebagai file WAV menggunakan C++ di sistem operasi Ubuntu.

## Prasyarat

Sebelum menjalankan program ini, pastikan Anda sudah menginstal beberapa dependensi berikut:

- **PortAudio** untuk pengolahan audio.
- **libsndfile** untuk penulisan file WAV.

Untuk menginstal dependensi ini di Ubuntu, jalankan perintah berikut:

```bash
sudo apt-get install libportaudio2 libsndfile1-dev
```

## Cara Penggunaan

1. **Kompilasi Program**  
   Setelah menginstal dependensi, kompilasi program menggunakan perintah berikut:

   ```bash
   g++ -o record_audio record_audio.cpp -lportaudio -lsndfile
   ```

2. **Jalankan Program**  
   Setelah kompilasi selesai, jalankan program dengan perintah:

   ```bash
   ./record_audio
   ```

3. **Perekaman**  
   Program akan mulai merekam audio dari mikrofon. Tekan Enter untuk berhenti merekam dan audio akan disimpan dalam file `output.wav`.

## Deskripsi Kode

- Program ini menggunakan **PortAudio** untuk merekam input audio.
- **libsndfile** digunakan untuk menulis data audio ke dalam file WAV.
- Format audio yang digunakan adalah **mono (1 saluran)** dengan **sample rate 44.1kHz**. Anda bisa menyesuaikan pengaturan ini sesuai kebutuhan.

## Lisensi

Program ini dilisensikan di bawah **MIT License**. Lihat file `LICENSE` untuk informasi lebih lanjut.

```

## Lisensi MIT

