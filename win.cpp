#include <ncurses/curses.h>

void print_menu(WINDOW *menu_win, int pilihanTerpilih, const char *opsi[], int jumlahopsi);

int main() {
    initscr();
    clear();
    noecho();
    cbreak();

    int awalx = 0, awaly = 0; // Inisialisasi posisi awal
    int lebar = 20, tinggi = 10;

    // Membuat window menu
    WINDOW *menu_win = newwin(tinggi, lebar, awaly, awalx);

    keypad(menu_win, TRUE);
	box(menu_win,0,0);
	box(stdscr,0,0);
	refresh();
    // Daftar pilihan menu
    const char *opsi[] = {
        "Pilihan 1",
        "Pilihan 2",
        "Pilihan 3",
        "Keluar"
    };

    int jumlahopsi = sizeof(opsi) / sizeof(char *);
    int pilihanTerpilih = 0; // Indeks pilihan pertama
    int pilihan = -1; // Pilihan default -1

    while (1) {
        print_menu(menu_win, pilihanTerpilih, opsi, jumlahopsi); // Menampilkan menu

        int tombol = wgetch(menu_win); // Membaca input dari keyboard

        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih == 0) {
                    pilihanTerpilih = jumlahopsi - 1; // Kembali ke pilihan terakhir
                } else {
                    --pilihanTerpilih; // Pindah ke pilihan sebelumnya
                }
                break;

            case KEY_DOWN:
                if (pilihanTerpilih == jumlahopsi - 1) {
                    pilihanTerpilih = 0; // Kembali ke pilihan pertama
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

        if (pilihan == 3) { // Pilih "Keluar"
            break; // Keluar dari loop jika "Keluar" dipilih
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

