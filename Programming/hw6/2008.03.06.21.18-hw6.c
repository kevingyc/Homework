#include <stdio.h>
#include <stdlib.h>
#define DECK_SIZE 52
#define DATA_NAME "hw6_data.txt"


/*** Task #1: fill in the missing parts in the declarations for:
          struct card
          union card_and_unsigned
     Note that the size of struct card must be no more than one byte.
*/

struct card{
unsigned char face :4;
unsigned char spac :2;
unsigned char suit :2;
};


union card_and_unsigned {
struct card x;
unsigned y;
};


typedef struct card Card;

enum Suit {SPADE=0, HEART, DIAMOND, CLUB};


void loadDeckFromFile(char filename[], Card deck[])
{
     FILE *fp = fopen(filename, "r");
     int i, x;

     if (NULL==fp) {
         printf("Error! Can't open file %s.\n", filename);
     }

     for (i=0; i < DECK_SIZE; i++) {
         fscanf(fp, "%d", &x);
         deck[i].face = x % 13 + 1;  /* face = 1..13 */
         deck[i].suit = x / 13;
     }

     fclose( fp );
}


void displayBits( unsigned value )
{
     unsigned c; /* counter */

     /* define displayMask and left shift 15 bits */
	 unsigned displayMask = 1 << 15;

     printf( "%5u = ", value );

     /* loop through bits */
     for ( c = 1; c <= 16; c++ ) {
         putchar( value & displayMask ? '1' : '0' );
         value <<= 1; /* shift value left by 1 */

         if ( c % 8 == 0 ) { /* output space after 8 bits */
            putchar( ' ' );
         } /* end if */

     } /* end for */

	 putchar( '\n' );
} /* end function displayBits */


void displayCard(Card c)
{
     union card_and_unsigned dummy;
/*** Task #2: fill in the missing parts in displayCard()
          so it can produce output as described in the assignment.
*/
     enum Suit suits;
     const char *suit[] = {"Spade", "Heart", "Diamand", "Club"};

     printf("%-7s %2d",suit[c.suit],c.face);
	 c.spac = 0;
/*** Task #3: the following function call to displayBits() is incorrect.
          Fix it using the dummy variable (type of union card_and_unsigned).
*/   
     printf(", shown in bits as ");
     dummy.x = c;
     displayBits( dummy.y );
}


int main( void )
{
    Card deck[DECK_SIZE];
    int i;
    printf("The size of struct card is %d byte(s).\n", sizeof(Card));
    printf("The size of deck is %d bytes.\n\n", sizeof(deck));

    loadDeckFromFile(DATA_NAME, deck);

    for (i=0; i<DECK_SIZE; i++) {
        displayCard( deck[i] );
    } /* end for */

    system("PAUSE");
    return 0;
}
