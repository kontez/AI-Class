/* BATTLESHIP
 * 
 * Battleship game that I made for an AI course.
 * The computer reads coordinates from a file 
 * and then it starts to attack :)
 *
 * Marvin Contessi
 * Contact:
 * kontez@autistici.org
 *   
 * USAGE:
 * The program wants to be fed with a file 
 * that contains 14 coordinates with no spaces
 * (e.g. B5B6B7B8B9C3D3E3F3F7G7H7J7J8 
 * 
 * then you can compile it with:
 * gcc battleship.c -o battleship
 *
 * and execute it with:
 * ./battleship filename
 *
 * have fun :)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char *argv[] )
{
    char *filename = argv[1]; /* getting the filename from argv */
    FILE *coordinates;        /* file */
    int board[10][10];        /* this will be the board */
    int x = 0;                /* coordinates */
    int y = 0;
    int i = 0;                /* counters */
    int j = 0;
    int k = 0;
    int c = 0;       
    int ships = 0;            /* total fields to hit */
    int shots = 0;            /* shots fired */
    int dir = 0;              /* direction
                               * 0 - horizontal
                               * 1 - vertical
                               */
    srand((unsigned)time(0));

    /* Initializing the board */
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            board[i][j] = 0;
        }
    }

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
        board[x][y] = 1;
        x = (int) getc(coordinates) - 65;
        y = (int) getc(coordinates) - 48;
        
    } 
    printf("\n[board loaded!]\n");
    printf("board layout: \n");


    /* Print the board */
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            printf("%d ",board[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    /* attack with parity method */

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if ( ((i + j)%2 == 0) && (ships < 14 )) /* if the box is even 
                                                     * and the number of ships that I hit
                                                     * is below 14
                                                     * where 14 is the total number of 
                                                     * fields that contain ships
                                                    */
            {
                if ( board[i][j] == 1) /* ship */
                {
                    board[i][j] = -2; /* hit */
                    ships++;
                    shots++;

                    dir = rand()%2; /* select direction */

                    /* save pos */
                    x = i;
                    y = j;

                    for(c = 0; c < 2; c++) /* do it 2 times */
                    {
                        if(dir == 1) /* vertical */
                        {
                            if ( (board[x-1][y] == 1) && ((x-1) >= 0)) /* up hit */
                            {
                                
                                board[x-1][y] = -2; /* hit */
                                ships++;
                                shots++;
                                k = x - 2;
                                do /* attack up until there's water */
                                {
                                    if ((board[k][y] == 1) && (k >= 0)) /* if ship */
                                    {
                                        board[k][y] = -2;
                                        shots++;
                                        ships++;
                                    }
                                    else if ((board[k][y] == 0) && (k >= 0)) /* if water */
                                    {
                                        board[k][y] = -1;
                                        board[k][y+1] = -3;
                                        board[k][y-1] = -3;
                                        shots++;
                                    }
                                    k--;
                                } while ((board[k][y] == 1) && (k >= 0));
                            }
                            else if ( (board[x-1][y] == 0) && ((x-1) >= 0)) /* up miss */
                            {
                                /* miss and attack down */
                                board[x-1][y] = -1;
                                board[x-1][y-1] = -3;
                                board[x-1][y+1] = -3;
                                shots++;
                                if ( (board[x+1][y] == 1) && ((x+1) < 10)) /* if ship */
                                {
                                    /* attack down */
                                    board[x+1][y] = -2;
                                    ships++;
                                    k = x + 2;   
                                    do /* attack down until there's water */
                                    {
                                        if ((board[k][y] == 1) && (k < 10)) /* if ship */
                                        {
                                            board[k][y] = -2;
                                            shots++;
                                            ships++;
                                        }
                                        else if ((board[k][y] == 0) && (k < 10)) /* if water */
                                        {
                                            board[k][y] = -1;
                                            board[k][y+1] = -3;
                                            board[k][y-1] = -3;
                                            shots++;
                                        }
                                        k++;
                                    } while ((board[k][y] == 1) && (k < 10));                                 
                                }
                                else /*if ( (board[x+1][y] == 0) && ((x+1) < 10))/* if miss, change direction */
                                {
                                    /* miss */
                                    board[x+1][y] = -1;
                                    shots++;
                                    dir = 0;
                                }
                            }
                        }

                        else if (dir == 0) /* horizontal */
                        {
                            if ( (board[x][y-1] == 1) && ((y-1) >= 0)) /* left attack */
                            {
                                board[x][y-1] = -2;
                                shots++;
                                ships++;
                                k = y - 2;
                                do /* attack left until there's water */
                                {
                                    if ((board[x][k] == 1) && (k >= 0)) /* if ship */
                                    {
                                        board[x][k] = -2;
                                        shots++;
                                        ships++;
                                    }
                                    else if ((board[x][k] == 0) && (k >= 0)) /* if water */
                                    {
                                        board[x][k] = -1;
                                        board[x-1][k] = -3;
                                        board[x+1][k] = -3;
                                        shots++;
                                    }
                                    k--;
                                } while ((board[x][k] == 1) && (k >= 0));
                            }
                            else if ( (board[x][y-1] == 0) && ((y-1) >= 0)) /* if left miss */
                            {
                                /* miss and attack right */
                                board[x][y-1] = -1;
                                board[x+1][y-1] = -3;
                                board[x+1][y-1] = -3;
                                shots++;

                                if ( (board[x][y+1] == 1) && ((y+1) < 10)) /* attack right */
                                {
                                    board[x][y+1] = -2;
                                    ships++;
                                    k = y + 2;   
                                    do /* attack right until there's water */
                                    {
                                        if ((board[x][k] == 1) && (k < 10)) /* if ship */
                                        {
                                            board[x][k] = -2;
                                            shots++;
                                            ships++;
                                        }
                                        else if ((board[x][k] == 0) && (k < 10)) /* if water */
                                        {
                                            board[x][k] = -1;
                                            shots++;
                                        }
                                        k++;
                                    } while ((board[x][k] == 1) && (k < 10));                                 
                                }
                                else /*if ( (board[x][y+1] == 0) && ((y+1) < 10))*/
                                {
                                    /* miss */
                                    board[x][y+1] = -1;
                                    shots++;
                                    dir = 1;
                                }
                            }
                        }
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
    printf("board after attack: \n");
    printf("[ 0 -> water | -1 -> miss | -2 -> hit | -3 -> ignored ]\n");
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
