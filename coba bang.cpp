#include <ncurses/curses.h>
#include <unistd.h> // Untuk fungsi usleep

int main() {
    // Inisialisasi ncurses
    initscr();
    noecho();
    curs_set(0); // Sembunyikan kursor

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); // Mendapatkan ukuran layar terminal

    int x = 0, y = max_y / 2; // Posisi awal karakter
    int dx = 1; // Kecepatan gerakan horizontal

    while (true) {
        clear(); // Bersihkan layar
        mvprintw(y, x, "O"); // Tampilkan karakter 'O' di posisi saat ini
        refresh(); // Perbarui layar

        // Perbarui posisi
        x += dx;

        // Pantulkan jika menyentuh tepi layar
        if (x >= max_x - 1 || x <= 0) {
            dx = -dx; // Balik arah
        }

        usleep(50000); // Tunggu 50 milidetik
    }

    endwin(); // Akhiri mode ncurses
    return 0;
}

