#include <iostream>
#include <fstream>
#include <ncurses/curses.h>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;
void point(bool exist,string ul);
void registration();
void login();

void test() {
	mvprintw (20, 40, "Ini bisa");
}

void registration() {
    ofstream myFile, accList;
    string userReg, passReg;
	char username[100];
	char password[100];
    //system("cls");
    mvprintw(0,0, "----------->REGISTER<-----------");
    
    mvprintw(1,0, "Enter username: ");
	echo();
    mvgetnstr(1,16, username, 99);
    
    mvprintw(2,0,"Enter Password: ");
    mvgetnstr(2,16, password, 99);
    
    //cin >> passReg;


    //cout << endl;
	string me = username;
	string mu = password;
    // Membuat file untuk pengguna
    myFile.open(me + ".txt");
    myFile << mu << endl;  // Simpan password di baris pertama
    myFile << 0;               // Awal skor diatur ke 0
    myFile.close();

    // Menambahkan username ke daftar akun
    accList.open("ListAccount.txt", ios::app);
    accList << me << endl;
    accList.close();
	mvprintw(1,0, "                                                 ");
	mvprintw(2,0, "                                                 ");
    //system("cls");
    //cout << "Registration successful!" << endl;
}

void login() {
    ifstream myFile;
    char userLog[100], passLog[100];
    string  userData, storedPass;

    bool exist = false;

//    system("cls");
	clear();
	echo();
    mvprintw(0,0,"----------->LOGIN<-----------");
    mvprintw(1,0, "Enter username: ");
    mvgetnstr(1,16,userLog,99);

    mvprintw(2,0,"Enter password: ");
    mvgetnstr(2,16,passLog,99);
    noecho();


    // Memeriksa apakah username ada di daftar
    myFile.open("ListAccount.txt");
    while (myFile >> userData) {
        if (userData == userLog) {
            exist = true;
            mvprintw(14,0, "username ada");
            break;
        }
    }
    myFile.close();
    string ul = userLog;
    string pl = passLog;
    //mvprintw(15,0, "%b",exist);
    if (exist){
    	exist= false;
    	myFile.open(ul + ".txt");
    	getline(myFile, storedPass); 
    	//getline(myFile, storedPass); 
    	
    	mvprintw(16,0, storedPass.c_str());	
    	mvprintw(17,0, pl.c_str());	
    	if (!strcmp(storedPass.c_str(), pl.c_str())){
    		exist = true;
			mvprintw(18,0, "pass ada");	
		}
		
	}
	clear();
    myFile.close();
	point(exist, ul);
   
}
void point(bool exist,string ul) {
	string storedPass;
	//clear();
	 if (exist) {

        if (exist) {
            mvprintw(0,0,"Login successful!");
            

            // Proses skor
            ifstream scoreCheck;
            ofstream scoreFile;
            char topScore[100];
			int currentScore;
            string tumbal;

            scoreCheck.open(ul + ".txt");
            getline(scoreCheck, tumbal);  // Skip password di baris pertama
            scoreCheck >> currentScore;       // Ambil skor di baris kedua
            scoreCheck.close();

            mvprintw(10,0,"Input top score: ");
            echo();
            mvgetnstr(10,16,topScore,99);
            noecho();
			int tTS = atoi(topScore);
			clear();
            // Update skor jika skor baru lebih tinggi
            if (tTS > currentScore) {
                scoreFile.open(ul + ".txt");
                scoreFile << tumbal << endl;  // Simpan kembali password
                scoreFile << topScore;           // Simpan skor baru
                scoreFile.close();
                mvprintw(0,0,"Your Top Score Is: %d",topScore);
            } else {
                mvprintw(0,0,"Your Top Score: %d", currentScore);
            }
        } else {
            mvprintw(0,0,"Incorrect password. Please try again."); 
        }
    } else {
        // Username tidak ditemukan
        //system("cls");
        mvprintw(0,0,"----------------------------------------");
        mvprintw(1,0,"                LOGIN ERROR             ");
        mvprintw(2,0,"Please check your username and try again");
        mvprintw(3,0,"----------------------------------------");
    }
    refresh();
    getch();
}
void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahopsi);
void main_menu() {
	
}
int main() {
    initscr();
    clear();
    noecho();
    cbreak();

    int awalx = 0, awaly = 0; // Inisialisasi posisi awal
    int lebar = 20, tinggi = 10;

    // Membuat window menu
    //WINDOW *menu_win = newwin(tinggi, lebar, awaly, awalx);

    keypad(stdscr, TRUE);

    // Daftar pilihan menu
    const char *opsi[] = {
        "Registration",
        "Login",
        "Keluar"
    };

    int jumlahopsi = sizeof(opsi) / sizeof(char *);
    int pilihanTerpilih = 0; // Indeks pilihan pertama
    int pilihan = -1; // Pilihan default -1

    while (1) {
        //print_menu(menu_win, pilihanTerpilih, opsi, jumlahopsi); // Menampilkan menu
		for (int i = 0; i < 3; i++) {
			if (pilihanTerpilih == i) attron(A_REVERSE);
			mvprintw(i,0, opsi[i]);
			refresh();
			if (pilihanTerpilih == i) attroff(A_REVERSE);
		}
		pilihanTerpilih;
		mvprintw(15,0, "%d", pilihanTerpilih);
        int tombol = wgetch(stdscr); // Membaca input dari keyboard
		//int tombol = wgetch();
        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih == 0) {
                    pilihanTerpilih = 0; // Kembali ke pilihan terakhir
                } else {
                    --pilihanTerpilih; // Pindah ke pilihan sebelumnya
                }
                break;

            case KEY_DOWN:
                if (pilihanTerpilih == 2) {
                    pilihanTerpilih = 2; // Kembali ke pilihan pertama
                } else {
                    ++pilihanTerpilih; // Pindah ke pilihan berikutnya
                }
                break;

            case 10: // Enter
                pilihan = pilihanTerpilih; // Menyimpan pilihan yang dipilih
                break;
        }

        clrtoeol(); // Membersihkan garis
        refresh(); // Menyegarkan layar

        if (pilihan == 2) { // Pilih "Keluar"
            break; // Keluar dari loop jika "Keluar" dipilih
        } else 
        if (pilihan == 0) {
        	clear();
			registration(); 
			clear();
			pilihan = -1;// Pilih "Keluar"  // Keluar dari loop jika "Keluar" dipilih
			//wrefresh(menu_win);
		} else
        if (pilihan == 1) {
        	login();
        	
		}
    }

    endwin(); // Mengakhiri ncurses
    return 0;
}

void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahopsi) {
    for (int i = 0; i < jumlahopsi; ++i) {
        if (i == pilihanTerpilih) {
            wattron(menu_win, A_REVERSE); // Menandai pilihan yang dipilih
        }

        mvwprintw(menu_win, i + 1, 1, opsi[i]); // Menampilkan opsi

        if (i == pilihanTerpilih) {
            wattroff(menu_win, A_REVERSE); // Menghilangkan penandaan pilihan
        }
    }

    wrefresh(menu_win); // Menyegarkan window menu
}
