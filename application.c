#include <ncurses.h>

int main() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if(has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
    }

    attron(COLOR_PAIR(1));
    printw("Press 'q' to quit");
    attroff(COLOR_PAIR(1));   
    refresh();

    int ch;
    while((ch = getch()) != 'q') {
        
    }

    endwin();
    return 0;
}