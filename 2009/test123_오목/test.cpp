#include<stdio.h>
#include<windows.h>
#include"header.h"


void main_draw(void)
{

    fputs("\n\n\n",stdout);

	printf("      ■■■      ■          ■      ■■■      ■        ■■            \n");
	printf("    ■      ■    ■■      ■■    ■      ■    ■      ■■              \n");
	printf("  ■          ■  ■■■  ■■■  ■          ■  ■    ■■                \n");
	printf("  ■          ■  ■  ■■■  ■  ■          ■  ■  ■■                  \n");
	printf("  ■          ■  ■    ■    ■  ■          ■  ■■■                    \n");
	printf("  ■          ■  ■          ■  ■          ■  ■■■                    \n");
	printf("  ■          ■  ■          ■  ■          ■  ■  ■■                  \n");
	printf("  ■          ■  ■          ■  ■          ■  ■    ■                  \n");
	printf("  ■          ■  ■          ■  ■          ■  ■    ■■                \n");
	printf("  ■          ■  ■          ■  ■          ■  ■      ■                \n");
	printf("    ■      ■    ■          ■    ■      ■    ■      ■■    -by. 란탄.\n");
	printf("      ■■■      ■          ■      ■■■      ■        ■■■■■■■■\n");


    fputs("\n\n\n\n\n                  ",stdout);
    system("pause");
	system("cls");
}
void game_draw(void)
{
	printf("첫번째 이름을 입력하세요:");
	scanf("%s",name_A);
	printf("두번째 이름을 입력하세요:");
	scanf("%s",name_B);

	for(int i=0;i<10;i++){
		fputs(".\n",stdout);
		Sleep(100);
	}
	printf("게임 시작!\n\n");
	Sleep(1000);
	system("cls");

	fputs("\n\n",stdout);
    printf("        ┌─────────────────┐\n");
	printf("        │                                  │\n");
	printf("        └─────────────────┘\n");

	printf("        ");
  
	for(int k=0;k<19;k++){
		for(int j=0;j<19;j++)
			printf("%s",array[j][k]);
		printf("\n        ");
	}

	gotoxy(50,6);
	printf("    ┌─────────┐");
	gotoxy(50,7);
	printf("    │ %5s님의 스코어 │",name_A);
	gotoxy(50,8);
    printf("    │   %2d勝    %2d敗   │",score_A,score_B);
	gotoxy(50,9);
	printf("    └─────────┘");

	gotoxy(50,10);
	printf("    ┌─────────┐");
	gotoxy(50,11);
	printf("    │ %5s님의 스코어 │",name_B);
	gotoxy(50,12);
    printf("    │   %2d勝    %2d敗   │",score_B,score_A);
	gotoxy(50,13);
	printf("    └─────────┘");

	gotoxy(50,19);
	printf("    ┌─────────┐");
	gotoxy(50,20);
	printf("    │  돌놓기 = ENTER  │");
	gotoxy(50,21);
    printf("    │  종료 = ESC      │");
	gotoxy(50,22);
	printf("    │  move = 방향키   │");
	gotoxy(50,23);
	printf("    └─────────┘");

    gotoxy(52,7);
    printf("■");
	gotoxy(52,8);
	printf("■");


}



void main() 
{ 
    system("mode con:lines=28");
	system("mode con:cols=80");
	system("color F0");
    
	main_draw();
	game_draw();

    CursorView(HIDDEN);

 
    PlayerInit();
    
	move=1;
    for (;;) {

        PlayerMove();
		Sleep(80);

   if (GetAsyncKeyState(VK_ESCAPE) < 0) break;
   if (GetAsyncKeyState(VK_SPACE)  <0) game_restart();

    }

    CursorView(SHOW);
}
