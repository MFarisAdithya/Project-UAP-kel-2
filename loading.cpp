#include <curses.h>
#include <unistd.h> // Untuk usleep()

int main() {
    // Inisialisasi ncurses
    initscr();
    curs_set(0); // Menyembunyikan kursor

    // Menampilkan pesan loading
    mvprintw(10, 30, "Loading...");

    // Menampilkan bar pertama (gunakan karakter 'barl')
    for (int i = 0; i < 25; i++) {
        mvaddch(12, 30 + i, 186); // Menambahkan karakter 'barl'
        refresh();
        usleep(150000); // Delay 150ms
    }

    // Menampilkan bar kedua (gunakan karakter 'bar2')
    for (int i = 0; i < 25; i++) {
        mvaddch(12, 30 + i, 207); // Menambahkan karakter 'bar2'
        refresh();
        usleep(100000); // Delay 150ms
    }

    // Menampilkan karakter setelah loading selesai
    mvprintw(14, 30, "Done :p");
    refresh();

    // Menunggu input pengguna sebelum keluar
    getch();

    // Mengakhiri ncurses
    endwin();

    return 0; // EXIT_SUCCESS
}
