#include <stdio.h>
#include "player.h"
#include "card.h"
#include "deck.h"
#include "gofish.h"
#include <string.h>
#include <windows.h>

// ---------------------------if value is 10, use 1------------------------------

int book_count_user=0;
int book_count_comp=0;

void disp_book(struct player* p1, struct player* p2) {
  //printf("Player 1's Book - %s \n", p1->book);
  //printf("Player 2's Book - %s \n", p2->book);
  printf("Player 1's Book - ");
  for (int i = 0; p1->book[i] != '\0'; i++) {
    printf("%c ", p1->book[i]);
    Sleep(50);
  }
  printf("\n");

  printf("Player 2's Book - ");
  for (int i = 0; p2->book[i] != '\0'; i++) {
    printf("%c ", p2->book[i]);
    Sleep(50);
  }
  printf("\n");
}

int isBookFull(int book_count) {
  //int count=0;
        if (book_count == 7) {
            return 0; // Not full, as a placeholder value (null terminator) was found
          }
    return 1; // Full, as no placeholder value was found
}

void start_rd(struct player* p1, struct player* p2) {
  // deal_player_cards(p1); // deal Player 1's cards
  // deal_player_cards(p2);
  struct hand* current_pcard = p1->card_list;
  //struct hand* current_pcards = p2->card_list;

  printf("Player 1's Hand - ");
  while (current_pcard != NULL) {
    // Assuming that the card struct has suit and rank members
    printf("%s%c ", current_pcard->top.rank, current_pcard->top.suit);
    Sleep(100);
    current_pcard = current_pcard->next;
  }
  printf("\n");

  disp_book(&user,&computer);
 
  //return p1->card_list;
}

void user_turn(struct player* p1, struct player* p2);

void user_turn(struct player* p1, struct player* p2);

/*-----------------------Main Func-----------------------------*/
int main(int args, char* argv[]) {

  char aws;

  char string1[] = "You are losing to my computer";
  char string2[] = "Be better!";
  char string3[] = "Pick you cards better";
  char string4[] = "You better not lose";
  char string5[] = "Next time yo will win...right?";
  

  while(1) {
    //start over------------------
    book_count_user = 0;
    book_count_comp = 0;
    shuffle();

    reset_player(&user);
    reset_player(&computer);
    //---------------

    deal_player_cards(&user); // deal Player 1's cards
    deal_player_cards(&computer);
    while (isBookFull(book_count_user) != 0 && isBookFull(book_count_comp) != 0) {
    
      start_rd(&user,&computer);
      //first turn belongs to the user
      //printf("3333");
      user_turn(&user,&computer);

      if (book_count_user == 7) { //check if book is 7, exit
        break;
      }

      start_rd(&user,&computer); 

      if (book_count_user == 7) { //check if book is 7, exit
        break;
      }
      comp_turn(&user,&computer);
      

    } //end of second while
    
    if (isBookFull(book_count_comp) != 0) {
      printf("Player 1 Wins! %d - %d\n",book_count_user,book_count_comp);
    }
    else {
      printf("Player 2 Wins! %d - %d\n",book_count_comp,book_count_user);
    }
  
    printf("Do you want to play again [Y/N]:");
    scanf(" %c",&aws);
    if (aws == 'N' || aws == 'n') {
      break;
    }
  }
  return 0;
}
/*-----------------------Main Func End-----------------------------*/

void user_turn(struct player* p1, struct player* p2) {
  
  struct hand* temp1 = p1->card_list;
  struct hand* temp2 = p2->card_list;
  //char num[3];
  //printf("in user_turn");
  char result = user_play(p1); // Assuming user_play returns a character
  //char draw_ranks;
  // ---------------------------if value is 10, use 1------------------------------

  if (search(p2, result) == 0) {
    struct card* new_card = next_card();
    printf("\t-Player2 has no %c\n",result);
    Sleep(80);
    add_card(p1,new_card);
    printf("\t-Go Fish, Player 1 draws %s%c\n",new_card->rank,new_card->suit);
    Sleep(80);
    if (new_card->rank[0] == result) { //if player draws card they asked for, gets another turn

      if (check_add_book(p1) == 'Y') { //prints if player1 gets a book
        book_count_user++;
        result = new_card->rank[0];
        printf("\t-Player 1 books %c\n",result);
        Sleep(80);
        if (book_count_user == 7) { //check if book is 7, exit
          return;
        }

    }
      printf("\t-Player 1 gets another turn\n\n");    //have line space
      Sleep(50);
      start_rd(p1,p2);
      user_turn(p1,p2);
      return;//don't continue with the rest of the function, avoid repeat
    }
  
  if (check_add_book(p1) == 'Y') { //prints if player1 gets a book
    book_count_user++;
    result = new_card->rank[0];
    printf("\t-Player 1 books %c\n",result);
    Sleep(80);
    if (book_count_user == 7) { //check if book is 7, exit
      return;
    }
        //check_add_book(p1);                     //adds the 4 cards to player's book
    printf("\t-Player 1 gets another turn\n\n");    //have line space
    Sleep(80);
    start_rd(p1,p2);
    user_turn(p1,p2);
    return;//don't continue with the rest of the function, avoid repeat
    }
    printf("\t-Player 2's turn\n\n");
    Sleep(80);
  } else {
    printf("\t-Player2 has ");
    Sleep(80);
    while (temp2 != NULL) {
      if (result == temp2->top.rank[0]) {
        printf("%s%c ",temp2->top.rank,temp2->top.suit);  //prints out card player2 has for transfer
      }
      temp2 = temp2->next;
    }
    printf("\n");   //print new line
    printf("\t-Player1 has ");
    Sleep(80);
     while (temp1 != NULL) {
      if (result == temp1->top.rank[0]) {
        printf("%s%c ",temp1->top.rank,temp1->top.suit);  //prints out card player1 has for transfer
        Sleep(50);
      }
      temp1 = temp1->next;
    }
    printf("\n");   //print new line

    transfer_cards(p2,p1,result);

    if (check_add_book(p1) == 'Y') { //prints if player1 gets a book
      book_count_user++;
      printf("\t-Player 1 books %c\n",result);
      Sleep(80);
      if (book_count_user == 7) { //check if book is 7, exit
        return;
      }
      printf("\t-Player 1 gets another turn\n\n");    //have line space
      Sleep(80);
      start_rd(p1,p2);
      user_turn(p1,p2);    //recursive call
      return; //don't repeat two funcs
    }

    printf("\t-Player 2's turn\n\n");
    Sleep(50);
  }
}

/*--------------------------Computer Inst-------------------------------------------*/
// ---------------------------if value is 10, it uses 1------------------------------

void comp_turn(struct player* p1, struct player* p2) {
  
  struct hand* temp1 = p1->card_list;
  struct hand* temp2 = p2->card_list;


  char c_rank = computer_play(p2);
  //char draw_rank; //resets rank to drawn card for books

  printf("Player 2's turn, enter a Rank: %c\n",c_rank);
  Sleep(80);

  if (search(p1, c_rank) == 0) {
    struct card* new_cardd = next_card();
    printf("\t-Player1 has no %c\n",c_rank);
    Sleep(80);
    add_card(p2,new_cardd);
    printf("\t-Go Fish, Player 2 draws %s%c\n",new_cardd->rank,new_cardd->suit);
    Sleep(80);
    
    if (new_cardd->rank[0] == c_rank) { //if player draws card they asked for, gets another turn
      
      if (check_add_book(p2) == 'Y') { //prints if player1 gets a book
        book_count_comp++;
        c_rank = new_cardd->rank[0]; //prints the card comp books, not draws
        printf("\t-Player 2 books %c\n",c_rank);
        Sleep(80);
        if (book_count_user == 7) { //check if book is 7, exit
          return;
        }
    }
      printf("\t-Player 2 gets another turn\n\n");    //have line space
      Sleep(80);
      start_rd(p1,p2);
      comp_turn(p1,p2);   //call back function
      return;//don't continue with the rest of the function, avoid repeat
    }
  
    if (check_add_book(p2) == 'Y') { //prints if player1 gets a book
      book_count_comp++;
      c_rank = new_cardd->rank[0]; //prints the card comp books, not draws
      printf("\t-Player 2 books %c\n",c_rank);
      Sleep(80);
      if (book_count_user == 7) { //check if book is 7, exit
        return;
      }

      printf("\t-Player 2 gets another turn\n\n");    //have line space
      Sleep(80);
      start_rd(p1,p2);
      comp_turn(p1,p2);   //call back function
      return;//don't continue with the rest of the function, avoid repeat
    }
    printf("\t-Player 1's turn\n\n");
    Sleep(50);
  } else {
    printf("\t-Player2 has ");
    Sleep(80);
    while (temp2 != NULL) {
      if (c_rank == temp2->top.rank[0]) {
        printf("%s%c ",temp2->top.rank,temp2->top.suit);  //prints out card player2 has for transfer
      }
      temp2 = temp2->next;
    }
    printf("\n");
    printf("\t-Player1 has ");
    Sleep(80);
    while (temp1 != NULL) {
      if (c_rank == temp1->top.rank[0]) {
        printf("%s%c ",temp1->top.rank,temp1->top.suit);  //prints out card player2 has for transfer
        Sleep(80);
      }
      temp1 = temp1->next;
    }
    printf("\n");

    transfer_cards(p1,p2,c_rank);
    if (check_add_book(p2) == 'Y') { //prints if player1 gets a book
      book_count_comp++;
      printf("\t-Player 2 books %c\n",c_rank);
      Sleep(50);
      if (book_count_user == 7) { //check if book is 7, exit
        return;
      }
      //adds the 4 cards to player's book
      printf("\t-Player 2 gets another turn\n\n");    //have 2 line space
      Sleep(80);
      start_rd(p1,p2);
      comp_turn(p1,p2);
      return; //don't repeat two funcs
    }

    printf("\t-Player 1's turn\n\n");
    Sleep(50);

  }
}
