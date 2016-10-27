#ifndef HAND_H
#define HAND_H

class Hand
{
	private:
		int value;		// Hard value of the hand (under 21 if possible)
		int softValue;		// Soft value of the hand (same as hard value in case of a hard hand)
		int size;		// Number of cards composing the hand
		bool pair;		// True when the hand is a pair, false otherwise
		bool isSplitted;	// True if the hand is the result of a split, false otherwise
	
	public:
		Hand();					// Calls reset()
		void reset();				// Resets the hand
		int add(int value);			// Adds a card to the hand
		int getValue();				// Gives the final value of the hand (Hard value if <= 21, soft value otherwise)
		int getSoftValue();			// Gives the soft value
		int getSize();				// Gives the hand'ssize
		bool isSoft();				// True if the hand is soft, false otherwise
		bool isNatural();			// True if the hand is a natural (BlackJack), false otherwise
		bool isPair();				// True if the hand is a pair, false otherwise
		bool isBusted();			// True if the hand is busted, false otherwise
		void setSplitted(bool isSplitted);	// Sets the attribute isSplited
		int beats(Hand* hand);			// Tests if the hand beats the hand given (-1: loses, 0: tie, 1: wins)
};

#endif
