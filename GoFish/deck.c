#include "deck.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct deck deck_instance;
/*
 * Function: shuffle
 * --------------------
 *  Initializes deck_instance and shuffles it.
 *  Resets the deck if a prior game has been played.
 * 
 *  returns: 0 if no error, and non-zero on error
 */ 
int shuffle() {
    char suits[] = {'C', 'D', 'H', 'S'};
    char ranks[][3] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"}; //account for null character

    // Initialize the deck_instance
    int count = 0;
    for (int suit_index = 0; suit_index < 4; suit_index++) {
        for (int rank_index = 0; rank_index < 13; rank_index++) {
            deck_instance.list[count].suit = suits[suit_index]; //initialize the suits
            strcpy(deck_instance.list[count].rank, ranks[rank_index]); //initialize the ranks
            count++; 
        }
    }

    // First card dealt is first in shuffled deck
    deck_instance.top_card = 0;

    int i;
    int j;
    struct card temp;

    printf("Shuffling...\n");
    for (i = 1; i < 52; i++) {
        
        j = rand() % (i);

        // Swap deck_instance.list[i] and deck_instance.list[j]
        temp = deck_instance.list[i];
        deck_instance.list[i] = deck_instance.list[j];
        deck_instance.list[j] = temp;
    }

    return 0; // Return 0 to indicate no error
}

/*
 * Function: deal_player_cards
 * ---------------------------
 *  Deal 7 random cards to the player specified in the function.
 *  Remove the dealt cards from the deck. 
 *
 *  target: pointer to the player to be dealt cards
 *
 *  returns: 0 if no error, and non-zero on error
 */
int deal_player_cards(struct player* target) {

    for (int i = 0; i<7; i++) {
        struct card* card = next_card();
        
        if (card == NULL) { return 1; }
        add_card(target,card);
        //if (add_card(target,card) == 0) { printf("working-ish") } //error in adding a card
    }
    return 0;
}
/*
 * Function: next_card
 * -------------------
 *  Return a pointer to the top card on the deck.
 *  Removes that card from the deck. 
 *
 *  returns: pointer to the top card on the deck.
 */
struct card* next_card() {
    // Check if the deck is empty
    if (deck_instance.top_card == 52) {
        // Handle the case where the deck is empty (no cards left)
        return NULL;
    }
    // Get a pointer to the top card

    struct card* top_ptr = &deck_instance.list[deck_instance.top_card];     //addr of deck instance, top card
    //printf("%c\n", top_ptr->rank[0]);
    deck_instance.top_card += 1;
    return top_ptr;
}

//not used
//unsinged int
size_t deck_size() {
    if (deck_instance.top_card>=52) {
        deck_instance.top_card = 52;
    }
    return (size_t) 52-deck_instance.top_card;
}