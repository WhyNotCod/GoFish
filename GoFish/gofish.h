#ifndef GOFISH_H
#define GOFISH_H


//start the round
void start_rd(struct player* p1, struct player* p2);

//display the books of the player, return a book (char)
void disp_book(struct player* p1, struct player* p2);

//function acts through actions of user
void user_turn(struct player* p1, struct player* p2);

//void redo_turn(struct player* p1, struct player* p2);

void comp_turn(struct player* p1, struct player* p2);

#endif
