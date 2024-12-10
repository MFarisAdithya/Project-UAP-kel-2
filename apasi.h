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
string input(int a, int b, char *inp, int c);
WINDOW *menu = newwin(10, 50, 16, 60);

void draw_box(int mulaiY, int mulaiX, int tinggi, int lebar) {
    mvaddch(mulaiY, mulaiX, '+');
    mvaddch(mulaiY, mulaiX + lebar - 1, '+');
    for (int x = 1; x < lebar - 1; x++) {
        mvaddch(mulaiY, mulaiX + x, '-');
    }
    for (int y = 1; y < tinggi - 1; y++) {
        mvaddch(mulaiY + y, mulaiX, '|');
        mvaddch(mulaiY + y, mulaiX + lebar - 1, '|');
    }
    mvaddch(mulaiY + tinggi - 1, mulaiX, '+');
    mvaddch(mulaiY + tinggi - 1, mulaiX + lebar - 1, '+');
    for (int x = 1; x < lebar - 1; x++) {
        mvaddch(mulaiY + tinggi - 1, mulaiX + x, '-');
    }
}

void login() {
	clear();
	wrefresh(menu);
	refresh();
    ifstream myFile;
    char userLog[100], passLog[100];
    string  userData, storedPass;

    bool exist = false;

	cb(); 

	//echo();
    mvprintw(18,62,"----------->NAMA GAME :P<-----------");
//    mvprintw(18,45, "Enter username: ");
    //mvgetnstr(11,61,userLog,99);
    //input(18,61,userLog,99);
    keypad(stdscr, TRUE);
    
//    const char *opsi[] = {
//    "Enter username:",
//    "Enter password:",
//    "Sign in",
//    "Sign up",
//    };
    
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    int tinggiB = 10;
    int lebarB = 40;
    int mulaiBY = 5;
    int mulaiBX = 5;

    while (true) {
        clear();
        attron(COLOR_PAIR(1));
        draw_box(mulaiBY, mulaiBX, tinggiB, lebarB);
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(2));
        mvprintw(mulaiBY + 1, mulaiBX + 1, "Option 1: Enter Username");
        mvprintw(mulaiBY + 2, mulaiBX + 1, "Option 2: Enter Password");
        mvprintw(mulaiBY + 3, mulaiBX + 1, "Option 3: Sign In");
        mvprintw(mulaiBY + 4, mulaiBX + 1, "Option 4: Sign Up");
        attroff(COLOR_PAIR(2));

        // Highlight selected option
        for (int i = 1; i <= 4; i++) {
            if (i == selected_option + 1) {
                attron(A_REVERSE); // Highlight
            }
            mvprintw(mulaiBY + i, mulaiBX + 1, "Option %d", i);
            attroff(A_REVERSE);
        }
        
//	initscr();
//	start_color();
//	    
//	init_pair(1, COLOR_WHITE, COLOR_BLUE);
//    init_pair(2, COLOR_BLACK, COLOR_WHITE);
//    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
//    
//    int tinggiB = 10;
//    int lebarB = 40;
//    int yB = 7;
//    int xB = 7;
//	
//	WINDOW *menuB = newwin(tinggiB, lebarB, yB, xB);
//    
//    wbkgd(menuBox, COLOR_PAIR(1));
//    box(menuBox, 0, 0)
//    wrefresh(menuBox);
    
    
    int jumlahopsi = sizeof(opsi) / sizeof(char *);
    int pilihanTerpilih = 0;
    int pilihan = -1; 
	//loading(5);
	//game();
	nodelay(stdscr, FALSE);
	//gameover();
    while (1) {
         // Menampilkan menu
		for (int i = 0; i < 4; i++) {
			if (pilihanTerpilih == i) attron(A_REVERSE);
			mvprintw(i+20,72, opsi[i]);
			refresh();
			if (pilihanTerpilih == i) attroff(A_REVERSE);
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
            input(20,88,userLog,99);
			pilihan = -1; // Keluar dari loop jika "Keluar" dipilih
        } else 
        if (pilihan == 1) { //pilih Register
			input(21,88,passLog,99); // masuk ke fungsi register
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
    
    delwin(menuB);
    endwin();
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
	box(menu,0,0);
	wrefresh(menu);
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
#endif
