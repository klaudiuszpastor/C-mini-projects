#include <curses.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} vec2;

int score = 0;
vec2 segments[256];

int main()
{
    int screen_width = 40;
    int screen_heigth = 20;

    // initialiaze screen
    WINDOW * win = initscr(); 

    // take player input
    keypad(win,true); // controls keypad translation, true - keypad translation is turned on
    nodelay(win,true); // if true the screen is set to no delay mode
    curs_set(0); // hide the cursor

    //snake
    vec2 head = {0,0};
    vec2 dir = {1,0};

    // food
    vec2 food = {rand()%screen_width,rand()%screen_heigth};

    while (true)
    {
        int pressed = wgetch(win); // if keypad is enabled functions respond to the pressing of a function 
        if (pressed == KEY_LEFT) { // key by returning the corresponding KEY_value 
            if (dir.x == 1) continue; 
            dir.x = -1;
            dir.y = 0;
        }
        if (pressed == KEY_RIGHT) {
            if (dir.x == -1) continue;
            dir.x = 1;
            dir.y = 0;
        }
        if (pressed == KEY_DOWN) {
            if (dir.y == -1) continue;
            dir.x = 0;
            dir.y = 1;
        }       
        if (pressed == KEY_UP) {
            if (dir.y == 1) continue;
            dir.x = 0;
            dir.y = -1;
        }
        if (pressed == '\e') {
            break;
        }

        // update
        // update segments
        for (int i = score; i > 0; i--) {
            segments[i] = segments[i-1];
        }
        segments[0] = head;

        head.x += dir.x;
        head.y += dir.y;

        // check collision with food
        if (head.x == food.x && head.y == food.y) {
            score += 1;
            food.x = rand() % screen_width;
            food.y = rand() % screen_heigth;
        }

        // draw
        erase(); // clear a window - clear every position in the current or specified window
        mvaddch(food.y, food.x * 2, 'S');

        // draw snake
        for (int i =0; i < score; i++) {
            mvaddch(segments[i].y,segments[i].x *2, 'o');
        }
        mvaddch(head.y, head.x * 2, 'O'); // place char into the current or specified window at the current or specified position
        
        refresh(); // refresh the screen to show the changes
        usleep(125000); // sleep for a short time

    }

    endwin(); // restores the terminal after Curses activity by at lease restoring the saved shell terminal mode

    return 0;
}