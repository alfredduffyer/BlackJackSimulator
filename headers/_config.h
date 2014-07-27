

// Don't touch the following lines :
#if __linux__
#ifndef LINUX
#define LINUX 1
#endif
#else
#ifndef LINUX
#define LINUX 0
#endif
#endif

// Taille du terminal d'affichage en caractères
#define TERMINAL_SIZE_X 80

// Minimum size of the shoe, in decks
#define MIN_SHOE_SIZE 1

// Maximum size of the shoe, in decks
#define MAX_SHOE_SIZE 10

// Number of times the deck is shuffled
#define TIMES_SHUFFLED 1

// Shift of Hard Standing Table
#define SHIFT_HS 12

// Shift of Soft Standing Table
#define SHIFT_SS 17

// Shift of Hard Doubling Down Table
#define SHIFT_HDD 2

// Shift of Soft Doubling Down Talbe
#define SHIFT_SDD 2

// Shift of Splitting Pairs
#define SHIFT_SP 2

// Activate the bet variation for counting methods
#define ACTIVATE_BET_VARIATION 1

// Actions of Splitting, Doubling Down, Drawing and Standing
#define SPLIT 400
#define DOUBLE 300
#define DOUBLEDOWN 300
#define DRAW 200
#define STAND 100

// Playing x hand(s) index
/*#define PLAYING_1 10
#define PLAYING_2 0
#define PLAYING_3 0
#define PLAYING_4 0
#define PLAYING_5 0
#define PLAYING_6 0
#define PLAYING_7 0
#define PLAYING_8 0
#define PLAYING_9 0
#define PLAYING_10 0*/

// Shell Colors
#define C_BLACK 30
#define C_RED 31
#define C_GREEN 32
#define C_YELLOW 33
#define C_BLUE 34
#define C_MAGENTA 35
#define C_CYAN 36
#define C_WHITE 37

// Percentage of how much other players play (100 : all the time, 0 : none)
#define GAME_PLAYING 100

// Percentage of the shoe that won't be player
#define WASTE_PROPORTION 2

// Number of cards burned at the begining
#define CARDS_BURNED 1

// Activate the bet variation for counting methods
#define MAX_SPLIT 1

// Number of decks played with
#define NB_DECKS 1

// Maximum of the variation bet (in units)
#define MAX_BET_VARIATION 5

#define STATUS 1
#define DEBUG 1
#define PAUSE 1
#define SLEEP 0
#define DEBUG_COLOR 1








