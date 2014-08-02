/*
	
	This file contains the configuration for the game that you can edit as you please (before compiling !).
	
	Warning : it can have hazardous effects if not set properly !
	
*/

#ifndef CONFIG
#define CONFIG

/*
 * Console's width, in characters (for display)
 */
#define TERMINAL_SIZE_X 80

/*
 * (De)Activates the bet variation for counting methods (0,1)
 * 
 * 1 activates the bet variation
 * 0 deactivates it
 */
#define ACTIVATE_BET_VARIATION 1

/*
 * Percentage of how much other players play [0-100]
 * 
 * 100 : all the time
 * 0 : never
 */
#define GAME_PLAYING 70

/*
 * Percentage of the shoe that won't be played [0-100]
 * 
 * 100 : shuffles after every hand
 * 0 : play to the last card
 */
#define WASTE_PROPORTION 30

/*
 * Number of cards burned at the begining [0-(NB_DECKS*52)]
 */
#define CARDS_BURNED 5

/*
 * Number of times the player is allowed to split [0-100]
 * 
 * 0 : The player can never split
 */
#define MAX_SPLIT 2

/*
 * Number of decks that will be played with [1-10]
 */
#define NB_DECKS 4

/*
 * Maximum of the variation of the number of hands played [1-?]
 * 
 * 1 : The player will always play on one box
 * ? : The player will play on up to ? boxes
 */
#define MAX_HAND_VARIATION 4

/*
 * Maximum of the variation bet (in units) [1-?]
 * 
 * 1 : The player will never vary his bet
 * ? : The player will vary his bet up to ? times his minimum bet
 */
#define MAX_BET_VARIATION 3

#endif
