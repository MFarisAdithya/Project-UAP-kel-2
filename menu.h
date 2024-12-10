#ifndef MENU_H

#include <iostream> // cin cout
#include <fstream> // untuk membuat file txt
#include <ncurses/curses.h>
#include <string> //untuk menyimpan kalimat di string
#include <cstdlib> //Mengonversi string ke integer
#include <cstring> //string berbasis array karakter
#include <vector> //flexibel array
#include <thread> // delay

using namespace std;
void login();
void point(bool exist,string UserLog);
void cb();
void loading(int hw);
void registration();
void kotak(short int baris1,short int kolom1, short int baris2,short int kolom2);
string input(int a, int b, char *inp, int c);
WINDOW *menu = newwin(10, 50, 16, 60);
void login() {
	clear();
	wrefresh(menu);
	refresh();
    ifstream myFile;
    char userLog[8], passLog[8];
    string  userData, storedPass;

    bool exist = false;

	cb(); 

	//echo();
    mvprintw(18,62,"----------->NAMA GAME :P<-----------");
//    mvprintw(18,45, "Enter username: ");
    //mvgetnstr(11,61,userLog,99);
    //input(18,61,userLog,99);
    keypad(stdscr, TRUE);
    
    const char *opsi[] = {
    "Enter username:",
    "Enter password:",
    "Sign in",
    "Sign up",
    };
    
    int jumlahopsi = sizeof(opsi) / sizeof(char *);
    int pilihanTerpilih = 0; // Indeks pilihan pertama
    int pilihan = -1; 
	loading(3);
	//game();
	nodelay(stdscr, FALSE);
	//gameover();
	
	//getch();
    while (1) {
         // Menampilkan menu
        kotak(19,71,24,100);
		for (int i = 0; i < 4; i++) {
			if (pilihanTerpilih == i) attron(COLOR_PAIR(2));
			mvprintw(i+20,72, opsi[i]);
			refresh();
			if (pilihanTerpilih == i) attroff(COLOR_PAIR(2));
		}
		pilihanTerpilih;
        int tombol = wgetch(stdscr); // Membaca input dari keyboard
        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih == 0) {
                    pilihanTerpilih = 2; // Kembali ke pilihan terakhir
                } else {
                    --pilihanTerpilih; // Pindah ke pilihan sebelumnya
                }
                break;

            case KEY_DOWN:
                if (pilihanTerpilih == 3) {
                    pilihanTerpilih = 0; // Kembali ke pilihan pertama
                } else {
                    ++pilihanTerpilih; // Pindah ke pilihan berikutnya
                }
                break;

            case 10: // Enter
                pilihan = pilihanTerpilih; // Menyimpan pilihan yang dipilih
                break;
        }

        refresh(); 
        if (pilihan == 0) { // Pilih "Keluar"
        	mvprintw(20,88,"        ");
        	memset(userLog, 0, sizeof(userLog));
			//char userLog1[8];
        	//userLog = userLog1;
        	//for (int i = 0; i < 8; i++) userLog[i] = userLog1[i];
            input(20,88,userLog,8);
			pilihan = -1; // Keluar dari loop jika "Keluar" dipilih
        } else 
        if (pilihan == 1) { //pilih Register
        	mvprintw(21,88,"        ");
        	memset(passLog, 0, sizeof(passLog));
			//char passLog1[8];
        	//passLog = passLog1;
        	//for (int i = 0; i < 8; i++) passLog[i] = passLog1[i];
			input(21,88,passLog,8); // masuk ke fungsi register
			pilihan = -1; //mengembalikan nilai pilihan
		} else
        if (pilihan == 2) {
        	// Memeriksa apakah username ada di daftar
		    myFile.open("ListAccount.txt");
		    while (myFile >> userData) {
		        if (userData == userLog) {
		            exist = true;
		            break;
		        }
		    }
		    myFile.close();
		    string UserLog = userLog;
		    string PassLog = passLog;
		  
		    // Memeriksa apakah password benar
		    if (exist){
		    	exist= false;
		    	myFile.open(UserLog + ".txt");
		    	myFile >> storedPass;	
		    	if (storedPass == PassLog){
		    		exist = true;
				}
			}
			cb();
		    myFile.close();
		    loading(1);
			point(exist, UserLog);
		 
	    	pilihan = -1;
	    } else
        if (pilihan == 3) {
        	loading(1);
        	registration();
        	pilihan = -1;
		}
    }
    getch();
}

void point(bool exist,string UserLog){
	string storedPass;
	 if (exist) {

        if (exist) {
            mvprintw(13,55,"Login successful!");
            
            
            ifstream scoreCheck;
            ofstream scoreFile;
            char topScore[100];
			int currentScore;
            string tumbal;

            scoreCheck.open(UserLog + ".txt");
            getline(scoreCheck, tumbal);  
            scoreCheck >> currentScore;      
            scoreCheck.close();

            mvprintw(16,55,"Input top score: ");
            echo();
            input(16,71,topScore,99);
            noecho();
			cb();
            // Update skor jika skor baru lebih tinggi
            if (atoi(topScore) > currentScore) {
                scoreFile.open(UserLog + ".txt");
                scoreFile << tumbal << endl;  // Simpan kembali password
                scoreFile << topScore;           // Simpan skor baru
                scoreFile.close();
                loading(3);
                mvprintw(14,55,"Your Top Score Is: %s",topScore);
            } else {
            	loading(3);
                mvprintw(14,55,"Your Top Score: %d", currentScore);
            }
        } else {
        	loading(3);
            mvprintw(19,45,"Incorrect password. Please try again."); 
        }
    } else {
        // Jika username tidak ditemukan
        mvprintw(11,40,"----------------------------------------");
        mvprintw(12,40,"                LOGIN ERROR             ");
        mvprintw(13,40,"Please check your username and try again");
        mvprintw(14,40,"----------------------------------------");
    }
    refresh();
    getch();
    cb();
    
}

void cb(){
	clear();
	box(stdscr,0,0);
}
void cbs() {
	kotak(5,5,25,25);
}

void loading(int hw) {
	cb();
	mvprintw(17, 75, "Loading...");
	for (int i = 0; i < hw; i++) {
		for (int i = 0; i < 55; i++) {
	        start_color(); 
	        init_pair(1, COLOR_CYAN, COLOR_BLACK);
	        attron(COLOR_PAIR(1));
	       mvaddch(20, 50 + i, ACS_CKBOARD);
	        attroff(COLOR_PAIR(1));
	        refresh();
	        napms(10);
	    }
		 mvprintw(20, 50, "                                                          ");
		 refresh();
	}
	cb();
}

void registration() {
	cb();
    ofstream myFile, accList;
    string userReg, passReg;
	char username[100];
	char password[100];
    mvprintw(9,45, "----------->REGISTER<-----------");
    mvprintw(11,45, "Enter username: ");
	echo();
    input(11,61,username,99);
    mvprintw(12,45,"Enter Password: ");
    input(12,61, password, 99);
    
	string me = username;
	string mu = password;
    myFile.open(me + ".txt");
    myFile << mu << endl;  
    myFile << 0;               
    myFile.close();

    accList.open("ListAccount.txt", ios::app);
    accList << me << endl;
    accList.close();
    cb();
    loading(1);
    mvprintw(13,45,"Registration Successfully");
    getch();
    cb();
}

string input(int a, int b, char *inp, int c) {
    echo();
    curs_set(1);
    
    mvgetnstr(a, b, inp, c);
//    string inpt;
//    int i = 0;
    
//    while (true) {
//    	int me = getch();
//    	mvprintw(6,6,"%d",i);
//    	if (me == 8) {
//    		if (i > 0) {
//    			i--;
//    			inpt.pop_back();
//	    		mvaddch(a,b+i,' ');		
//	    		mvaddch(a,b+i-1,inpt.back());
//	    			
//			}
//			continue;
//		}
//    	if (me == 10) {
//    		break;
//		}
//    	inpt.push_back(me);
//    	mvaddch(a,b+i,me);
//    	i++;
//	}
    noecho();
    curs_set(0);
}
void kotak(short int baris1,short int kolom1, short int baris2,short int kolom2) {
    short int baris,kolom;

  // mencetak karakter pokok kiri atas
  mvaddch(baris1,kolom1,ACS_ULCORNER);
  
  // mencetak garis mendatar
  for (kolom=kolom1+1;kolom<=kolom2-1;kolom++)
      {
        mvaddch(baris1,kolom,ACS_HLINE);
      }
  // mencetak karakter pokok kiri atas
  mvaddch(baris1,kolom2,ACS_URCORNER);

  // mencetak garis vertikal
  for (baris=baris1+1;baris<=baris2-1;baris++)
      {
        mvaddch(baris,kolom2,ACS_VLINE);
      }
  // mencetak karakter pokok kanan bawah
  mvaddch(baris2,kolom2,ACS_LRCORNER);

  // mencetak garis mendata di bagian bawah
  // dari atas ke bawah
  for (kolom=kolom2-1;kolom>=kolom1+1;kolom--)
      {
        mvaddch(baris2,kolom,ACS_HLINE);
      }

  // mencetak karakter pokok kiri bawah
  mvaddch(baris2,kolom1,ACS_LLCORNER);

  // mencetak garis vertikal di sebelah kiri
  for (baris=baris2-1;baris>=baris1+1;baris--)
      {
        mvaddch(baris,kolom1,ACS_VLINE);
      }
  refresh();
  // return null;
}

#endif
