#include <stdio.h>
#include <unistd.h>     //for sleep / falling animation
#include <stdlib.h>     //for clear terminal
#include <termios.h>    //for fast keyboard inupt and raw mode
#include <sys/select.h> // to detect keyboard input without blocking
#include <time.h>      // for randomness in shapes

#define ROW 20
#define COL 10

void enable_raw_mode()
{
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &t);
}

struct Tetromino // shape
{
    int shape[4][4];
    int row;
    int col;
};

struct Tetromino shapes[7] = {
    {
        // shape O
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}},
        0, // row
        3  // col
    },
    {
        // shape T
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}},
        0, // row
        3  // col
    },
    {
        // shape S
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}},
        0, // row
        3  // col
    },
    {
        // shape Z
        {
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}},
        0, // row
        3  // col
    },
    {
        // shape J
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}},
        0, // row
        3  // col
    },
    {
        // shape L
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}},
        0, // row
        3  // col
    },
    {
        // shape I
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}},
        0, // row
        3  // col
    },
};

int board[ROW][COL] = {0};

void drawboard() // empty board
{
    for (int i = 0; i < ROW; i++)
    {
        printf("|");
        for (int j = 0; j < COL; j++)
        {
            if (board[i][j] == 1)
                printf("[]");
            else
                //printf("░░");
                printf("::");
        }
        printf("|\n");
    }
    printf("+");
    for (int j = 0; j < COL; j++)
        printf("__");
    printf("+\n");
}

void draw_tetromino(struct Tetromino t) // printing shape
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (t.shape[i][j] == 1)
            {
                board[i + t.row][j + t.col] = 1;
            }
        }
    }
}

int kbhit()
{
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void erase_tetromino(struct Tetromino t)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (t.shape[i][j] == 1)
            {
                board[i + t.row][j + t.col] = 0;
            }
        }
    }
}

int can_move_down(struct Tetromino t) // collision detection for bottom wall
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (t.shape[i][j] == 1)
            {
                if (t.row + i + 1 >= ROW || board[t.row + i + 1][t.col + j] == 1)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}


int main()
{
    enable_raw_mode();
    srand(time(NULL)); // seed random number
    struct Tetromino current = shapes[rand() % 7];

    draw_tetromino(current);
    drawboard();
    while (1) // game control loop
    {
        erase_tetromino(current); //  ghost block prevention by erase before any movement (keyboard or falling)
        if (kbhit())              // keyboard inputs
        {
            {
                char key = getchar();
                if (key == 'a' || key == 'A')
                {
                    if (current.col > 0)
                        current.col--;
                }
                else if (key == 'd' || key == 'D')
                {
                    if (current.col < COL - 4)
                        current.col++;
                }
                else if (key == 's' || key == 'S')
                {
                    current.row++;
                }
                else if (key == 'q' || key == 'Q')
                {
                    break;
                }
            }
        }
        if (can_move_down(current))
        {
            current.row++;
        }
        else
        {
            draw_tetromino(current);
            current = shapes[rand() % 7];
            current.row = 0;
            current.col = 3;

            system("clear");
            drawboard();
        }
        draw_tetromino(current);
        system("clear");
        drawboard();
        usleep(500000);
    }
    return 0;
}
