#ifndef _HEADER_H_
#define _HEADER_H_
 
enum {HIDDEN, SHOW};

extern char name_A[30];
extern char name_B[30];

extern int player_x;
extern int player_y;
extern char array[19][19][3];
extern int check;
extern int move;
extern char name_B[30];
extern char name_A[30];
extern int score_A;
extern int score_B;


void CursorView(char show);
void gotoxy(int x, int y);
void PlayerErase(void);
void PlayerDraw(void);
void PlayerMove(void);
void PlayerInit(void);
void game_restart(void);

#endif