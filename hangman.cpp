#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <algorithm>
using namespace std;

#define MAX_ATTEMPT 7

//Deklarasi variabel global
string word, answer, alphabet, status, suggest, guess;
string bar = string(77, '=') + "\n";
string line = string(77, '-') + "\n";
char sel1, sel2, mode;
int misses, lvl, help;
vector<char> incorrect, guessed, letters;
double percentage;

//Deklarasi Struct untuk kata yang akan ditebak
struct Level{
    string easy, medium, hard;
} w[213];

//ASCII value untuk Main Menu dan Title Hangman
char mainmenu[20][103] = {{32, 32, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 32, 32, 32, 32, 32, 47, 36, 36, 32, 32, 32, 47, 36, 36, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 64, 32, 32, 32, 32, 32, 32, 64, 32, 32, 32, 32, 32, 64, 42, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 124, 32, 36, 36, 32, 32, 124, 32, 36, 36, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 64, 32, 32, 32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 124, 32, 36, 36, 32, 32, 124, 32, 36, 36, 32, 32, 47, 36, 36, 36, 36, 36, 36, 32, 32, 47, 36, 36, 36, 36, 36, 36, 36, 32, 32, 32, 47, 36, 36, 36, 36, 36, 36, 32, 32, 47, 36, 36, 36, 36, 36, 36, 47, 36, 36, 36, 36, 32, 32, 32, 47, 36, 36, 36, 36, 36, 36, 32, 32, 47, 36, 36, 36, 36, 36, 36, 36, 32, 10},
                          {32, 32, 64, 32, 46, 40, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 124, 32, 36, 36, 36, 36, 36, 36, 36, 36, 32, 124, 95, 95, 95, 95, 32, 32, 36, 36, 124, 32, 36, 36, 95, 95, 32, 32, 36, 36, 32, 47, 36, 36, 95, 95, 32, 32, 36, 36, 124, 32, 36, 36, 95, 32, 32, 36, 36, 95, 32, 32, 36, 36, 32, 124, 95, 95, 95, 95, 32, 32, 36, 36, 124, 32, 36, 36, 95, 95, 32, 32, 36, 36, 10},
                          {32, 32, 64, 46, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 124, 32, 36, 36, 95, 95, 32, 32, 36, 36, 32, 32, 47, 36, 36, 36, 36, 36, 36, 36, 124, 32, 36, 36, 32, 32, 92, 32, 36, 36, 124, 32, 36, 36, 32, 32, 92, 32, 36, 36, 124, 32, 36, 36, 32, 92, 32, 36, 36, 32, 92, 32, 36, 36, 32, 32, 47, 36, 36, 36, 36, 36, 36, 36, 124, 32, 36, 36, 32, 32, 92, 32, 36, 36, 10},
                          {32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 32, 38, 38, 92, 32, 32, 32, 32, 32, 32, 32, 32, 124, 32, 36, 36, 32, 32, 124, 32, 36, 36, 32, 47, 36, 36, 95, 95, 32, 32, 36, 36, 124, 32, 36, 36, 32, 32, 124, 32, 36, 36, 124, 32, 36, 36, 32, 32, 124, 32, 36, 36, 124, 32, 36, 36, 32, 124, 32, 36, 36, 32, 124, 32, 36, 36, 32, 47, 36, 36, 95, 95, 32, 32, 36, 36, 124, 32, 36, 36, 32, 32, 124, 32, 36, 36, 10},
                          {32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 47, 32, 32, 32, 37, 32, 32, 32, 32, 32, 32, 32, 124, 32, 36, 36, 32, 32, 124, 32, 36, 36, 124, 32, 32, 36, 36, 36, 36, 36, 36, 36, 124, 32, 36, 36, 32, 32, 124, 32, 36, 36, 124, 32, 32, 36, 36, 36, 36, 36, 36, 36, 124, 32, 36, 36, 32, 124, 32, 36, 36, 32, 124, 32, 36, 36, 124, 32, 32, 36, 36, 36, 36, 36, 36, 36, 124, 32, 36, 36, 32, 32, 124, 32, 36, 36, 10},
                          {32, 32, 40, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 46, 44, 64, 42, 38, 47, 64, 32, 32, 32, 32, 32, 32, 32, 32, 124, 95, 95, 47, 32, 32, 124, 95, 95, 47, 32, 92, 95, 95, 95, 95, 95, 95, 95, 47, 124, 95, 95, 47, 32, 32, 124, 95, 95, 47, 32, 92, 95, 95, 95, 95, 32, 32, 36, 36, 124, 95, 95, 47, 32, 124, 95, 95, 47, 32, 124, 95, 95, 47, 32, 92, 95, 95, 95, 95, 95, 95, 95, 47, 124, 95, 95, 47, 32, 32, 124, 95, 95, 47, 10},
                          {32, 32, 42, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 36, 32, 38, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 47, 36, 36, 32, 32, 92, 32, 36, 36, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 37, 32, 32, 64, 32, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 124, 32, 32, 36, 36, 36, 36, 36, 36, 47, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 64, 92, 32, 32, 32, 32, 32, 32, 32, 32, 37, 32, 32, 37, 32, 37, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 92, 95, 95, 95, 95, 95, 95, 47, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 32, 47, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 35, 32, 96, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 32, 40, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 92, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 10},
                          {32, 32, 32, 37, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 47, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 87, 101, 108, 99, 111, 109, 101, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 10},
                          {32, 32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 49, 46, 32, 80, 108, 97, 121, 32, 97, 32, 103, 97, 109, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 32, 64, 32, 32, 32, 32, 32, 32, 32, 32, 64, 32, 35, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 50, 46, 32, 72, 111, 119, 32, 116, 111, 32, 112, 108, 97, 121, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 32, 37, 32, 37, 44, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 51, 46, 32, 69, 120, 105, 116, 32, 71, 97, 109, 101, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 10},
                          {32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 10},
                          {32, 32, 32, 38, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 67, 104, 111, 111, 115, 101, 32, 58, 32, 0}};

//Menentukan Jenis Level
int level(int &lvl, int &help) {
    system("cls");
    //Print Title Hangman
    for(int i = 0; i < 11; i++) {
        for(int j = 27; j < 102; j++) {
            cout<<mainmenu[i][j];
        } cout<<endl;
    }
    cout<<endl;

    //Print Opsi Level
    cout<<bar<<"  1. Easy\n  2. Medium\n  3. Hard\n"<<bar; 
    sel1:
        sel1 = ' ';
        cout<<"  Pick a level (Insert the number) : "; cin>>sel1; 
        cout<<bar;
    
    switch (sel1) {
        case '1':
            lvl = 1;
            break;
        case '2':
            lvl = 2;
            break;
        case '3':
            lvl = 3;
            break;
        default:
            cout<<"  Invalid Option!";
            Sleep(650);
            printf("\33[2K\r" "\33[A\r" "\33[K\r" "\33[A\r" "\33[K\r");
            goto sel1;
            break;
    }

    sel2:
        sel2 = ' ';
        cout<<"  Enable hint? (y/n) "; cin>>sel2;
        cout<<bar;

    switch (sel2) {
        case 'y':
            help = 1;
            break;
        case 'n':
            help = 0;
            break;
        default:
            cout<<"  Invalid Option!";
            Sleep(650);
            //karakter ANSI untuk menghilangkan 3 baris terakhir di terminal
            printf("\33[2K\r" "\33[A\r" "\33[K\r" "\33[A\r" "\33[K\r");
            goto sel2;
            break;
    }

    return lvl, help;
}

//Instruksi cara bermain Hangman
void howto() {
    system("cls");
    //Print title hangman
    for(int i = 0; i < 11; i++) {
        for(int j = 27; j < 102; j++) {
            cout<<mainmenu[i][j];
        } cout<<endl;
    }
    cout<<endl;

    cout<<bar;
    cout<<"  Instructions\n"
        <<"  1. Select the level you want to play, each level has it's own difficulty.\n"
        <<"  2. You can also decide whether you want to have hint enabled or not.\n"
        <<"  3. Your goal is to save the man from being hanged!\n"
        <<"  4. You can only guess 1 letter at a time or guess the entire word in one\n     go.\n"
        <<"  5. If you guees it incorrectly, an additional part will be drawn to the\n     \"hanger\".\n"
        <<"  5. If you guess the letter correctly, it will show where the letter is\n     located.\n"
        <<"  7. If all the body part has been drawn, the man is hanged, and you lost\n     the game.\n"
        <<"  8. Good Luck and enjoy!\n";
    cout<<bar;
}

//End Credits
void credits() {
    system("cls");
    //Print title hangman
    for(int i = 0; i < 11; i++) {
        for(int j = 27; j < 102; j++) {
            cout<<mainmenu[i][j];
        } cout<<endl;
    }
    cout<<endl;

    cout<<bar;
    cout<<"  Credits :\n"<<line
        <<"  This program was made by :\n"
        <<"  1. Davin Jason Evan Raharjo (22/493367/PA/21184)\n"
        <<"  2. Fakih Widatmojo          (22/494024/PA/21238)\n"
        <<"  3. Kawakib Nurin Mubaraka   (22/498440/PA/21518)\n"<<line
        <<"  Special thanks to all the people who helped by giving us feedbacks and\n"
        <<"  ideas to make sure that the user playing gets a good user experience.\n\n"
        <<"  I hope you personally enjoy this game as much as we enjoy when making\n  this game.\n"<<line
        <<"  Thank you for playing this game!\n  Peace out\n"
        <<bar;
}

//Menentukan kata yang akan ditebak secara acak
string wordselect(Level *w, string &word, string &answer, int lvl) {
    //Buka File
    ifstream in("words.txt");

    if (!in){
    cerr<<"File can't be opened!\n";
    system("PAUSE");
    exit(1);
    }

    //Input data dari file ke struct
    for (int i = 0; i < 213; i++) {
        in>>w[i].easy>>w[i].medium>>w[i].hard;
    }

    //Pemilihan kata berdasarkan level yang dipilih
    srand(time(NULL)); 
    switch(lvl) {
        case 1:
            word = w[rand()%213].easy;
            break;
        case 2:
            word = w[rand()%213].medium;
            break;
        case 3:
            word = w[rand()%213].hard;
            break;
    }
    //Kata yang akan didisplay
    letters.insert(letters.end(), word.begin(), word.end());
    answer = string(word.size(), '_');
    return word;
}

//Reset value sebelum memulai permainan
void clear() {
    guessed.clear();
    incorrect.clear();
    letters.clear();
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    misses = lvl = help = 0;
    sel1 = sel2 = mode = ' ';
}

//Menampilkan "hangman" sesuai jumlah kesalahan yang dibuat
void display_misses(int misses) {
    switch (misses) {
        case 0:
            {
                cout<<"  @@@@@@@@@@@@@@@@@@@@@@\n"
                    <<"  @      @\n"
                    <<"  @    @\n"
                    <<"  @ .(\n"
                    <<"  @.\n"
                    <<"  @\n"
                    <<"  @\n"
                    <<"  (\n"
                    <<"  *\n"
                    <<"  #\n"
                    <<"  @\\\n"
                    <<"   /\n"
                    <<"   (\n"
                    <<"   %\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   &\n"
                    <<"   &\n"
                    <<"   &\n";
                break;
            }
        case 1:
            {
                cout<<"  @@@@@@@@@@@@@@@@@@@@@@\n"
                    <<"  @      @     @*\n"
                    <<"  @    @       @\n" 
                    <<"  @ .(         @\n"
                    <<"  @.           @\n"
                    <<"  @            @\n"
                    <<"  @            @\n"
                    <<"  (\n"
                    <<"  *\n"
                    <<"  #\n"
                    <<"  @\\\n"
                    <<"   /\n"
                    <<"   (\n"
                    <<"   %\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   &\n"
                    <<"   &\n"
                    <<"   &\n";
                break;
            }
        case 2:
            {
                cout<<"  @@@@@@@@@@@@@@@@@@@@@@\n"
                    <<"  @      @     @*\n"
                    <<"  @    @       @\n" 
                    <<"  @ .(         @\n"
                    <<"  @.           @\n"
                    <<"  @            @ &&\\\n"
                    <<"  @            @/   %\n"
                    <<"  (            @*&/@\n"
                    <<"  *\n"
                    <<"  #\n"
                    <<"  @\\\n"
                    <<"   /\n"
                    <<"   (\n"
                    <<"   %\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   &\n"
                    <<"   &\n"
                    <<"   &\n";
                break;
            }
        case 3:
            {
                cout<<"  @@@@@@@@@@@@@@@@@@@@@@\n"
                    <<"  @      @     @*\n"
                    <<"  @    @       @\n"
                    <<"  @ .(         @\n"
                    <<"  @.           @\n"
                    <<"  @            @ &&\\\n"
                    <<"  @            @/   %\n"
                    <<"  (            @*&/@\n"
                    <<"  *            &\n"
                    <<"  #            @\n"
                    <<"  @\\           %\n"
                    <<"   /           #\n"
                    <<"   (           @\n"
                    <<"   %\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   &\n"
                    <<"   &\n"
                    <<"   &\n";
                break;
            }
        case 4:
            {
                cout<<"  @@@@@@@@@@@@@@@@@@@@@@\n"
                    <<"  @      @     @*\n"
                    <<"  @    @       @\n" 
                    <<"  @ .(         @\n"
                    <<"  @.           @\n"
                    <<"  @            @ &&\\\n"
                    <<"  @            @/   %\n"
                    <<"  (          .,@*&/@\n"
                    <<"  *          $ &\n"
                    <<"  #         %  @\n"
                    <<"  @\\        %  %\n"
                    <<"   /           #\n"
                    <<"   (           @\n"
                    <<"   %\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   &\n"
                    <<"   &\n"
                    <<"   &\n";
                break;
            }
        case 5:
            {
                cout<<"  @@@@@@@@@@@@@@@@@@@@@@\n"
                    <<"  @      @     @*\n"
                    <<"  @    @       @\n" 
                    <<"  @ .(         @\n"
                    <<"  @.           @\n"
                    <<"  @            @ &&\\\n"
                    <<"  @            @/   %\n"
                    <<"  (          .,@*&/@\n"
                    <<"  *          $ &&\n"
                    <<"  #         %  @ &\n"
                    <<"  @\\        %  % %\n"
                    <<"   /           # `\n"
                    <<"   (           @\n"
                    <<"   %\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   @\n"
                    <<"   &\n"
                    <<"   &\n"
                    <<"   &\n";
                break;
            }
        case 6:
            {
                cout<<"  @@@@@@@@@@@@@@@@@@@@@@\n"
                    <<"  @      @     @*\n"
                    <<"  @    @       @\n" 
                    <<"  @ .(         @\n"
                    <<"  @.           @\n"
                    <<"  @            @ &&\\\n"
                    <<"  @            @/   %\n"
                    <<"  (          .,@*&/@\n"
                    <<"  *          $ &&\n"
                    <<"  #         %  @ &\n"
                    <<"  @\\        %  % %\n"
                    <<"   /           # `\n"
                    <<"   (           @\n"
                    <<"   %           /\n"
                    <<"   @          @\n"
                    <<"   @         @\n"
                    <<"   @        @\n"
                    <<"   &        %\n"
                    <<"   &\n"
                    <<"   &\n";
                break;
            }
        case 7:
            {
                cout<<"  @@@@@@@@@@@@@@@@@@@@@@        /$$$$$$\n"
                    <<"  @      @     @*              /$$__  $$\n"
                    <<"  @    @       @              | $$  \\__/  /$$$$$$  /$$$$$$/$$$$   /$$$$$$\n"
                    <<"  @ .(         @              | $$ /$$$$ |____  $$| $$_  $$_  $$ /$$__  $$\n"
                    <<"  @.           @              | $$|_  $$  /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$\n"
                    <<"  @            @ &&\\          | $$  \\ $$ /$$__  $$| $$ | $$ | $$| $$_____/\n"
                    <<"  @            @/   %         |  $$$$$$/|  $$$$$$$| $$ | $$ | $$|  $$$$$$$\n"
                    <<"  (          .,@*&/@           \\______/  \\_______/|__/ |__/ |__/ \\_______/\n"
                    <<"  *          $ &&\n"
                    <<"  #         %  @ &              /$$$$$$                                /$$\n"
                    <<"  @\\        %  % %             /$$__  $$                              | $$\n"
                    <<"   /           # `            | $$  \\ $$ /$$    /$$ /$$$$$$   /$$$$$$ | $$\n"
                    <<"   (           @\\             | $$  | $$|  $$  /$$//$$__  $$ /$$__  $$| $$\n"
                    <<"   %           /@             | $$  | $$ \\  $$/$$/| $$$$$$$$| $$  \\__/|__/\n"
                    <<"   @          @ @             | $$  | $$  \\  $$$/ | $$_____/| $$\n"
                    <<"   @         @ @              |  $$$$$$/   \\  $/  |  $$$$$$$| $$       /$$\n"
                    <<"   @        @ #                \\______/     \\_/    \\_______/|__/      |__/\n"
                    <<"   &        % %,\n"
                    <<"   &\n"
                    <<"   &\n";
                break;
            }
        default:
            break;
    }
}

//Menghitung persentase huruf yang berhasil ditebak
double percent(double &percentage) {
    double n = word.size();
    double letter = n - count(answer.begin(), answer.end(), '_');
    percentage = letter / n * 100;
    return percentage;
}

//Memberi player hint berupa huruf yang dipilih secara acak
void hint(bool selected, string guess) {
    string info;
    //Pemberian hint secara random saat hint enabled
    if (selected) {
        info = "  Type '?' on input to use hint\n";
        //Hint akan diberikan selama kata kurang dari 66.67% tertebak
        if (percent(percentage) < 66.66667) {
            status = "Available"; //Ubah status hint
            if (guess == "?") { //Pemberian hint saat player menggunakannya
                srand(time(NULL));
                int random = rand()%letters.size();
                suggest = letters[random];
                info = "  The word contains the letter " + suggest + '\n';
            }
        } else { //Saat kata lebih dari 66.67% tertebak
            status = "Unavailable"; //Ubah status hint
            info = "  You have guessed more than 2/3 of the word!\n"; //Info tambahan
        }
    } else { //Saat hint disabled
        status = "Unavailabe";
        info = "  You didn't enable hint for this round\n"; //Info tambahan
    }
    
    cout<<"  Hint (Status = "<<status<<")\n"<<info;
}

//Menampilkan info selama proses guessing
void display() {
    cout<<'\n'<<bar;
    //Menampilkan letak huruf tebakan yang ada di kata
    printf("  Word =\t%.2f%% completed\n  ", percent(percentage));
    for (int i = 0; i < answer.size(); i++) printf("%c ", answer[i]);
    cout<<'\n'<<line;

    //Menampilkan berapa banyak toleransi kesalahan sebelum game over
    printf("  Remaining Lives = %d\n", MAX_ATTEMPT - misses);
    
    //Menampilkan huruf yang belum digunakan untuk menebak
    cout<<line<<"  Available Letters =\n ";
    for (int i = 0; i < alphabet.size(); i++) printf(" %c", alphabet[i]); 
    cout<<endl;
    
    //Menampilkan huruf yang sudah ditebak dan salah
    cout<<line<<"  Wrong guess =\n ";
    //Penampilan diurutkan secara ascending
    sort(incorrect.begin(), incorrect.end());
    for (int i = 0; i < incorrect.size(); i++) cout<<" "<<incorrect[i];
    cout<<'\n';
    cout<<line;
    hint(help, guess);
}

//Mengecek apakah huruf tebakan ada pada kata / tebakan sama dengan kata
void check(string guess) {
    bool found = false;
    int n;
    //Fungsi untuk mengecek apabila pemain menebak sebuah kata
    if (guess.size() == word.size()) {
        if (guess == word) {
            answer = guess;
            found = true;
        }
    } else if (guess.size() == 1) { //Fungsi untuk mengecek apabila pemain menebak sebuah huruf
        guessed.push_back(guess[0]);
        n = int(guess[0]) - 65;
        alphabet[n] = ' ';
        for (int i = 0; i < word.size(); i++) {
            if (word[i] == guess[0]) {
                answer[i] = guess[0];
                found = true;
                letters.erase(remove(letters.begin(), letters.end(), guess[0]), letters.end());
            }
        }
    }

    //Indikator hasil tebakan
    if (found) cout<<"  Correct!\n";
    else {
        cout<<"  Incorrect!\n";
        if (guess.size() == 1) {
            incorrect.push_back(guess[0]);
        }
        misses++;
    }
}

//Interface saat menang / kalah
void end() {
    if (word == answer) {
        system("cls");
        cout<<"    /$$$$$$                                                     /$$              /$$\n"
            <<"   /$$__  $$                                                   | $$             | $$\n"
            <<"  | $$  \\__/  /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$  /$$$$$$  /$$$$$$   /$$$$$$$| $$\n"
            <<"  | $$       /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$|____  $$|_  $$_/  /$$_____/| $$\n"
            <<"  | $$      | $$  \\ $$| $$  \\ $$| $$  \\ $$| $$  \\__/ /$$$$$$$  | $$   |  $$$$$$ |__/\n"
            <<"  | $$    $$| $$  | $$| $$  | $$| $$  | $$| $$      /$$__  $$  | $$ /$$\\____  $$\n"
            <<"  |  $$$$$$/|  $$$$$$/| $$  | $$|  $$$$$$$| $$     |  $$$$$$$  |  $$$$//$$$$$$$/ /$$\n"
            <<"   \\______/  \\______/ |__/  |__/ \\____  $$|__/      \\_______/   \\___/ |_______/ |__/\n"
            <<"                                 /$$  \\ $$\n"
            <<"                                |  $$$$$$/\n"
            <<"                                 \\______/\n"
            <<"       /$$     /$$                        /$$      /$$                     /$$\n"
            <<"      |  $$   /$$/                       | $$  /$ | $$                    | $$\n"
            <<"       \\  $$ /$$//$$$$$$  /$$   /$$      | $$ /$$$| $$  /$$$$$$  /$$$$$$$ | $$\n"
            <<"        \\  $$$$//$$__  $$| $$  | $$      | $$/$$ $$ $$ /$$__  $$| $$__  $$| $$\n"
            <<"         \\  $$/| $$  \\ $$| $$  | $$      | $$$$_  $$$$| $$  \\ $$| $$  \\ $$|__/\n"
            <<"          | $$ | $$  | $$| $$  | $$      | $$$/ \\  $$$| $$  | $$| $$  | $$\n"
            <<"          | $$ |  $$$$$$/|  $$$$$$/      | $$/   \\  $$|  $$$$$$/| $$  | $$ /$$\n"
            <<"          |__/  \\______/  \\______/       |__/     \\__/ \\______/ |__/  |__/|__/\n\n";
        cout<<bar<<"  Your word was "<<word<<'\n'<<bar;
    } else if (misses == 7) {
        system("cls");
        display_misses(misses);
        cout<<bar<<"  Oh no! The man is hanged!\n";
        cout<<"  Your word was "<<word<<'\n'<<bar;
    }
}

//Fungsi hangman
void hangman() {
    int n = word.size();
    system("cls");

    display_misses(misses);
    display();
    guess.clear();
    cout<<bar;
    cout<<"  - You can only guess 1 letter at a time or guess the entire word\n"
        <<"  - If you accidentally type more than one letter or your guess is longer\n"
        <<"    than the word length, it will be considered as a mistake\n"
        <<"  - Hint is only available if your guess is less than 66.67%% completed\n";
    //Input kata / huruf
    cout<<bar;
    cout<<"  Input your guess : "; cin>>guess;
    transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

    if (guess == "?") { //Deteksi apabila player memilih untuk menggunakan hint
        if (!help) {
            cout<<"  You didn't enable hint for this round";
            Sleep(650);
        } else if (percent(percentage) > 66.67) {
            cout<<"  You cant use hint if you have guessed more than 2/3 of the word!";
            Sleep(650);
        }
    } else if (guess.size() == 1) {
        //Deteksi apabila kata yang ingin ditebak sudah dipilih sebelumnya
        if (find(guessed.begin(), guessed.end(), guess[0]) != guessed.end()) {
            cout<<"  You already guessed that letter!";
            Sleep(650);
        } else if (guess[0] < 'A' || (guess[0] > 'Z' && guess[0] < 'a') || guess[0] > 'z') {
            //Deteksi apabila kata yang ditebak adalah selain yang ada di opsi
            cout<<"  You can't guess any letter other than the available alphabet!";
            Sleep(650);
        } else {
            check(guess);
            Sleep(650);
        }
    } else {
        check(guess);
        Sleep(650);
    }

    //Deteksi apabila kata sudah ditebak atau kesalahan mencapai batas maksimal
    if (answer != word && misses < MAX_ATTEMPT) hangman();
    else end();
}

//Menu Utama
void menu() {
    system("cls");
    while (true) {
        //Print tampilan main menu
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 103; j++) {
                if (mainmenu[i][j] == 0) break;
                cout<<char(mainmenu[i][j]);
            }
        } cin>>mode;

        switch (mode) {
            case '1': //Mengarahkan ke permainan
                clear();
                level(lvl, help);
                wordselect(w, word, answer, lvl);
                hangman();
                cout<<"  Press any key to return to main menu\n  ";
                getch();
                system("cls");
                continue;
            case '2': //Mengarahkan ke instruksi bermain
                howto();
                cout<<"  Press any key to return to main menu\n  ";
                getch();
                system("cls");
                continue;
            case '3': //Menampilkan end credits
                credits();
                Sleep(3500);
                system("cls");
                break;
            default: //Saat nilai mode tidak ada dalam case
                cout<<string(28, ' ')<<"Invalid Input!";
                Sleep(650);
                continue;
        }
        break;
    }
}

int main() {
    menu();
    return 0;
}