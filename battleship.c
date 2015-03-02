/* BATTLESHIP
 * 
 * Battleship game that I made for an AI course.
 * The computer reads coordinates from a file 
 * and then it starts to attack :)
 *
 * Marvin Contessi
 * Contact:
 * kontez@autistici.org
 */

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
    char *filename = argv[1]; /* getting the filename from argv */
    FILE *coordinates;        /* file */
    int board[10][10];        /* this will be the board */
    int x = 0;                /* coordinates */
    int y = 0;
    int i = 0;
    int j = 0;
    int shots = 0;

    /* Initializing the board */
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            board[i][j] = 0;
        }
    } 
    printf("board cleared\n");

    /* loading the file */
    coordinates = fopen(filename,"r");
    if ( coordinates == NULL )
    {
        printf("Cannot load file.\n");
        return(-1);
    }

    /* I get the ASCII value of e.g. 'A' and then i substract 64 to get 0
     * so that I can match it in the matrix
     */
    x = (int) getc(coordinates) - 65;
    y = (int) getc(coordinates) - 48;
    while(!feof(coordinates))
    {
        printf("x = %d; y = %d\n",x,y);
        board[x][y] = 1;
        x = (int) getc(coordinates) - 65;
        y = (int) getc(coordinates) - 48;
        
    } 
    printf("board loaded!\n");


    /* Print the board */
    for (i = 0; i < 10; i++)
    {
        printf("\n");
        for (j = 0; j < 10; j++)
        {
            printf("%d ",board[i][j]);
        }
    }

    printf("\n");

    /* attack with parity method */

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if ( (i + j)%2 == 0 ) /* if the box is even */
            {
                if ( board[i][j] == 1) /* ship */
                {
                    board[i][j] = -2; /* hit */
                    shots++;

                    if ( (board[i][j+1] == 1) && (j < 10) ) /* right */
                    {
                        board[i][j+1] = -2;
                        shots++;
                    }                             
                    
                    if ( (board[i][j-1] == 1) && (j > 0) ) /* left */
                    {
                        board[i][j-1] = -2;
                        shots++;
                    }

                    if ( (board[i+1][j] == 1) && (i < 10) ) /* down */
                    {
                        board[i+1][j] = -2;
                        shots++;
                    }

                    if ( (board[i-1][j] == 1) && (i > 0) ) /* up */
                    {
                        board[i-1][j] = -2;
                        shots++;
                    }
                }

                /* ok, that works, now I need only to clear the fields nearby
                 * will do that tomorrow in class :)
                 */

                else if ( board[i][j] == 0 ) /* water */
                {
                    board[i][j] = -1; /* miss */
                    shots++;
                }
            }
        }
    }


    /* reprint the board for debugging */
    for (i = 0; i < 10; i++)
    {
        printf("\n");
        for (j = 0; j < 10; j++)
        {
            printf("%d\t",board[i][j]);
        }
    }

    printf("\nshots: %d\n",shots);
}
