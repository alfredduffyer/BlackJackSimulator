

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

// Number of cards burned at the begining
#define CARDS_BURNED 5

// Number of times the deck is shuffled
#define TIMES_SHUFFLED 100

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

// Actions of Splitting, Doubling Down, Drawing and Standing
#define SPLIT 400
#define DOUBLE 300
#define DOUBLEDOWN 300
#define DRAW 200
#define STAND 100

// Percentage of the shoe that won't be player
#define WASTE_PROPORTION 30

// Percentqge of time on whitch a player plays on two boxes
#define PLAYING_ON_TWO_BOXES 20

// Percentage of how much people play (100 : all the time, 0 : none)
#define GAME_PLAYING 70

// Playing x hand(s) index
#define PLAYING_1 100
#define PLAYING_2 50
#define PLAYING_3 25
#define PLAYING_4 10
#define PLAYING_5 0
#define PLAYING_6 0
#define PLAYING_7 0
#define PLAYING_8 0
#define PLAYING_9 0
#define PLAYING_10 0

// Activate the bet variation for counting methods
#define ACTIVATE_BET_VARIATION 1






















