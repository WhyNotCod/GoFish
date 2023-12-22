#include <stdlib.h>
#include <stdio.h>
#include <string.h>   
#include "player.h"

struct player user;
struct player computer;


/*
 * Function: add_card
 * -------------------
 *  Add a new card to the player's hand. 
 *
 *  target: the target player
 *  new_card: pointer to the new card to add
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int add_card(struct player* target, struct card* new_card) {
  struct hand* temp;
  //struct hand* cur_hand = target->card_list;

  temp = (struct hand*)malloc(sizeof(struct hand)); //allocate space for new element for linked list

  if (temp == NULL)  { return -1; } 

  temp->top = *new_card; //keep new card unsigned int
  temp->next = target->card_list;  //initialize next pointer
// Append the new hand to the end of the player's hand
  target->card_list = temp;
    
  return 0;
}

/*
 * Function: remove_card
 * ---------------------
 *  Remove a card from the player's hand. 
 *
 *  target: the target player
 *  old_card: pointer to the old card to remove
 *
 *  returns: return 0 if no error, non-zero otherwise
 */
int remove_card(struct player* target, struct card* old_card) {
    struct hand* iterator = target->card_list;
    struct hand* previous = NULL;
    if (iterator == NULL) { return 0; } //list is empty

    while ((iterator->top.suit != old_card->suit) || (iterator->top.rank[0] != old_card->rank[0])) {
        
        previous = iterator;
        iterator = iterator->next;
        
        if (iterator == NULL) {
            //printf("\n\n%s%c\n\n", previous->top.rank, previous->top.suit);
            return 1;
        }
            
    }

    //check suit and rank of the card, no match while loop
    if (previous != NULL) {  //old_card dereferenced
        previous->next = iterator->next;        //store current card as previous' next
    } else {
        target->card_list = iterator->next;
    }
    free(iterator);
    return 0;
}


char check_add_book(struct player* target) {
    int count = 0;      //counter
    struct hand* cur_card = target->card_list;      //var pointer for current card in list
    //printf("being looked at");
    //struct hand* previous = NULL;
    char ranks[] = "123456789JQKA";
    //iterate through card_list to check for same rank
    for (int j=0; j<13;j++) {
        count = 0;      //reset count for each rank
        cur_card = target->card_list;
        while (cur_card) {
            //printf(" %c ",cur_card->top.rank[0]);
            if (cur_card->top.rank[0] == ranks[j]) {        //if string match, it returns 0
                
                count++;
                //printf("Being looked at too -%d- ",count);

                if (count >= 4) {
                    //printf("enter");
                    for (int c=0;c<13;c++) {
                        if (ranks[j] == cur_card->top.rank[0]) {
                            //remove 4 cards from hand that have val of rank j
                            //printf("removed!!");
                            struct card card1;
                            card1.suit = 'H';
                            strcpy(card1.rank, cur_card->top.rank);
                            //printf("\n\n%s%c\n\n", card1.rank, card1.suit);
                            remove_card(target, &card1);
                            card1.suit = 'S';
                            remove_card(target, &card1); 
                            card1.suit = 'C';
                            remove_card(target, &card1); 
                            card1.suit = 'D';
                            remove_card(target, &card1);   
                            break;
                        }
                    }
                    //add cards to book
                    for (size_t i = 0; i < 7; i++) {
                        //printf("will add");
                        if (target->book[i] == '\0') {

                            //printf("added book");
                            target->book[i] = ranks[j];      //fixed warning of assinging pointer to a char
                            return 'Y';  // A book was added
                        }
                    }
  
                }
            }
            cur_card = cur_card->next;
        }
    }
    return 'N';
}


int search(struct player* target, char rank) {
    struct hand* current_card = target->card_list;
    //2 cases: other player has rank, other player doesn't have rank
    //printf("%c",rank); works
    while (current_card != NULL) {
        
        if (rank == current_card->top.rank[0]) {   //if rank in card list, return 1
            //printf("yes");
            return 1;
        }
        current_card = current_card->next;      //increment the linked list
    }
    return 0;       //return False if rank in card list
}

  
int transfer_cards(struct player* src, struct player* dest, char rank) {
    //check all cards in list that share chosen rank (should be 4)
    struct hand* cur_card = src->card_list;   
    struct card crd;
    //struct hand* previous = NULL;
    int counts = 0;
    while (cur_card != NULL) {
        if (rank == *cur_card->top.rank) {
            // Remove the card from the source player and add it to the destination player
            crd = cur_card->top;
            cur_card = cur_card->next;
            if (remove_card(src, &crd) == 0) {
                
                if (add_card(dest, &crd) == 0) {
                    
                    counts++;
                } else {
                    printf("add failed...\n");
                    // If adding to destination fails, you may want to handle this error
                }
            } else {
                printf("remove failed...\n");
                // If removing from source fails, you may want to handle this error
            }
        }
        else cur_card = cur_card->next;     //look at next card
    }
    return counts;
}

int game_over(struct player* target) {
  int card;
  for (card=0; card<7;card++) { //iterate over card
    if (target->book[card] == '\0') { //reset all of book
      return 0; //return 0 if success
    } 
  }
  return 1;
}

/* 
 * Function: reset_player
 * ----------------------
 *
 *   Reset player by free'ing any memory of cards remaining in hand,
 *   and re-initializes the book. Used when playing a new game.
 * 
 *   target: player to reset
 * 
 *   Return: 0 if no error, and non-zero on error.
 */

int reset_player(struct player* target) {
    struct hand* cur_card = target->card_list;
    struct hand* next_card;

    // Free cards in memory
    while (cur_card != NULL) {
        next_card = cur_card->next;  // Store the next card
        free(cur_card);             // Free the current card
        cur_card = next_card;       // Move to the next card
    }

    // Clear book elements
    for (int i = 0; i < 7; i++) {
        target->book[i] = '\0';
    }

    // Set hand size to 0
    target->hand_size = 0;

    // Set card_list to NULL to indicate an empty hand
    target->card_list = NULL;

    return 0;
}

/* 
 * Function: computer_play
 * -----------------------
 *
 *   Select a rank randomly to play this turn. The player must have at least
 *   one card of the selected rank in their hand.
 *
 *   target: the player's hand to select from
 *
 *   Rank: return a valid selected rank
 */
char computer_play(struct player* target) {
    char ranks[13];
    int num_ranks = 0;
    int random_index;
    struct hand* cur_card = target->card_list;
    //printf("\t\t\t\tgoes here %s%c\n",cur_card->top.rank, cur_card->top.suit);
    //char chosen_rank;
    while (cur_card != NULL) {
        //need to check for duplicates -- fix later
        int isDouble = 0;
        for (int i=0; i <13;i++) {
            //printf("%d",i);
            if (ranks[i] == cur_card->top.rank[0]) {
                isDouble =1;
                break;
            }
        }
        if (!isDouble) {
            ranks[num_ranks] = cur_card->top.rank[0];
            num_ranks++;        //increment index
        }
        cur_card = cur_card->next;      //goes to next card in linked list
    }
    //use mod of rand()
    if (num_ranks > 0) {
        random_index = rand() % num_ranks;
    }
    return ranks[random_index];        //dereference pointer
}

/* 
 * Function: user_play
 * -------------------
 *
 *   Read standard input to get rank user wishes to play.  Must perform error
 *   checking to make sure at least one card in the player's hand is of the 
 *   requested rank. If not, print out "Error - must have at least one card from rank to play"
 *   and then re-prompt the user.
 *
 *   target: the player's hand to check
 * 
 *   returns: return a valid selected rank
 */
char user_play(struct player* target) {
    char rank;
    int valid_rank = 0;
    //struct card* new_card = next_card();
    
    while (!valid_rank) {
        //if (target->hand_size == 0) { add_card(target,&new_card);}
        printf("Player 1's turn, enter a Rank: ");
        
        scanf("%1s", &rank);
        
        if (search(target, rank) == 1) {
            valid_rank = 1;
        } else {
            printf("Error - must have at least one card from rank to play\n");
        }
    }

    return rank;
}
