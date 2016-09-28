#ifndef VARIABLES
#define VARIABLES

// Defines wheter the user is under LINUX or not (for system() calls)
#if __linux__
#define LINUX 1
#else
#define LINUX 0
#endif

// Decisions of Splitting, Doubling Down, Drawing and Standing
#define SPLIT 400
#define DOUBLE 300
#define DOUBLEDOWN 300
#define DRAW 200
#define STAND 100

// Minimum size of the shoe, in decks
#define MIN_SHOE_SIZE 1

// Maximum size of the shoe, in decks
#define MAX_SHOE_SIZE 10

// Shift of various counting numbers tables
#define SHIFT_HS 12		// Hard Standing Table
#define SHIFT_SS 17		// Soft Standing Table
#define SHIFT_HDD 2		// Hard Doubling Down Table
#define SHIFT_SDD 2		// Soft Doubling Down Table
#define SHIFT_SP 2		// Splitting Pairs

// Shell Colors
#define C_BLACK 30
#define C_RED 31
#define C_GREEN 32
#define C_YELLOW 33
#define C_BLUE 34
#define C_MAGENTA 35
#define C_CYAN 36
#define C_WHITE 37

// DEBUG options
#define NOSTATUSLIMIT 10000000
#define STATUS 0
#define DEBUG 0
#define FORCE_DEBUG 1
#define PRINT_TABLE 0
#define PAUSE 0
#define SLEEP 0
#define DEBUG_COLOR 0

#endif
