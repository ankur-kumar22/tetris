#include<stdio.h>

#define row 20
#define col 10

int board[row][col]= {0};

void drawboard() {
    for (int i = 0; i < row; i++)
    {
        printf("|");
        for (int j = 0; j < col; j++)
        {
            if (board[i][j]==1)
                printf("[]");
            else
                printf("..");
            
        }
        printf("|\n");
    }
    printf("+");
    for (int j = 0; j < col; j++) 
    printf("--");
    printf("+\n"); 
}
int main() {

    board[19][0] = 1;
    board[19][1] = 1;
    board[18][0] = 1;

    drawboard();
    return 0;
}