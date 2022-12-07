# Hangman

Hangman adalah permainan kata yang dapat meningkatkan perbendaharaan kosakata bahasa. Pada program yang kami buat, program akan memilihkan kata secara acak sesuai level yaang dipilih dan pemain bertugas untuk menebak kata tersebut sebelum _figure_ hangman tergantung seluruhnya

## Informasi

Program dapat dijalankan di terminal yang menyediakan support untuk karakter standar ANSI (American National Standard Institute) karena pada beberapa line program menggunakan kode berikut :

```cpp
printf("\33[2K\r" "\33[A\r" "\33[K\r" "\33[A\r" "\33[K\r");
```

Kode di atas bertujuan untuk menggeser kursor dan menghapus line di mana letak kursor berada dengan menggunakan karakter ESC bervalue "\33[".

Program dibuat dengan menggunakan C++ 17.

## Penggunaan
Program dapat dijalankan di terminal Windows, dan mungkin dapat pula dijalankan di terminal Linux dan/atau MAC.

Pada Windows, program dapat dicompile dengan menggunakan compiler C++ seperti DevC++, CodeBlocks, dengan text editor seperti VS Code.

Untuk proses compile pada cmd / Command Prompt, dapat dijalankan command berikut :
```bash
g++ -o hangman hangman.cpp
```

Pastikan terdapat file "words.txt" sebelum melakukan proses compile. Jika tidak ada file "words.txt", program tidak akan bisa menentukan kata secara acak dan akan keluar dengan kode exit 1.
