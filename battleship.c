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

int attack();
int hunt();

int main( int argc, char *argv[] )
{
    char *filename = argv[1]; /* getting the filename from argv */
    FILE *coordinates;        /* file */
    int board[9][9];          /* this will be the board */
    int x = 0;                /* coordinates */
    int y = 0;


    /* loading the file */
    coordinates = fopen(filename,"r");
    if ( coordinates == NULL )
    {
        printf("Cannot load file.\n");
        return(-1);
    }
    while(!feof(coordinates))
    {
        /* will finish this in class 8D */
    } 
}