#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "getpage.h"

int pageNumber = 100;

void display_page(int pageNumber) {
    clear();

    char* content = get_page_by_number(pageNumber);

    if(content) {
        mvprintw(0, 0, "Page number: %d", pageNumber);
        mvprintw(1, 0, "%s", content);
        free(content);
    } else {
        mvprintw(0,0, "Failed to load page %d", pageNumber);
    }
    
    refresh();
}


int main() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if(has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
    }

    display_page(100);

    char input[10];
    int input_pos = 0;
    memset(input, 0, sizeof(input));

    int ch;
    while((ch = getch()) != 'q') {
        if(ch >= '0' && ch <= '9') {
            if(input_pos < (int)sizeof(input) - 1) {
                input[input_pos++] = (char) ch;
                input[input_pos] = '\0';
                mvprintw(LINES - 1, 0, "PAGE NUMBER: %s", input);
                refresh();
            }
        }

        if(ch == KEY_RIGHT) {
            pageNumber += 1;
            display_page(pageNumber);
        }

        if(ch == KEY_LEFT) {
            pageNumber -= 1;
            display_page(pageNumber);
        }

        if(ch == '\n' || ch == KEY_ENTER) {
            if(input_pos > 0) {
                pageNumber = atoi(input);

                display_page(pageNumber);

                memset(input, 0, sizeof(input));
                input_pos = 0;
            }
        }
    }

    endwin();
    return 0;
}