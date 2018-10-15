#include<stdio.h>
#include<windows.h>

 int player_x;
 int player_y;
 int move;
 int back=0;

 int winx_left=0;
 int winx_right=0;
 int winy_up=0;
 int winy_down=0;

 int wind_left=0;
 int wind_right=0;

char name_A[30];
char name_B[30];
 
 int p=0;
 int score_A=0;
 int score_B=0;
 int sc=0;
 int answer=0;


extern int player_x;
extern int player_y;
char array[19][19][3]={
	{"¦£","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦§","¦¦"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦¶","¦«","¦«","¦«","¦«","¦«","¦¶","¦«","¦«","¦«","¦«","¦«","¦¶","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦¶","¦«","¦«","¦«","¦«","¦«","¦¶","¦«","¦«","¦«","¦«","¦«","¦¶","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦¶","¦«","¦«","¦«","¦«","¦«","¦¶","¦«","¦«","¦«","¦«","¦«","¦¶","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¨","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦«","¦ª"},
	{"¦¤","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦©","¦¥"}
 };

//¦£¦¨¦¨¦¤
//¦§¦«¦«¦©
//¦§¦«¦«¦©
//¦¦¦ª¦ª¦¥

int check[19][19]={0};


/* È­¸éÀÇ Ä¿¼­¸¦ º¸ÀÌ°Å³ª ¼û±â±â */
void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

/* x, y ÁÂÇ¥·Î Ä¿¼­¸¦ ¿òÁ÷ÀÌ´Â ÇÔ¼ö */
void gotoxy(int x, int y) /*Ä¿¼­ÀÌµ¿ ÇÔ¼ö ºÎºÐ*/
{
    COORD XY = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}



void PlayerErase(void)
{
    gotoxy(player_x, player_y);
    printf("%s",array[player_x/2-4][player_y-5]);

}



void PlayerDraw(void)
{
    gotoxy(player_x, player_y);
    printf("¡à");
}


void move_check(void)
{
	if(check[player_x/2-4][player_y-5]==1 ){
		gotoxy(10,3);
		printf("ÀÌ¹Ì µÐ ÀÚ¸® ÀÔ´Ï´Ù.");
		Sleep(1000);
		gotoxy(10,3);
		printf("                    ");
		gotoxy(player_x,player_y);
		back=1;
	}
	else if(check[player_x/2-4][player_y-5]==2){
		gotoxy(10,3);
		printf("ÀÌ¹Ì µÐ ÀÚ¸® ÀÔ´Ï´Ù.");
		Sleep(1000);
		gotoxy(10,3);
		printf("                    ");
		gotoxy(player_x,player_y);
		back=1;
	}
}

void game_restart(void)
{
    for(int i=0;i<19;i++)
		for(int j=0;j<19;j++)
			check[i][j]=0;

	for(i=0;i<19;i++)
		for(int j=0;j<19;j++)
			strcpy(array[i][j],"¦«");

	for(int j=1;j<18;j++)
		strcpy(array[0][j],"¦§");

	for(j=1;j<18;j++)
		strcpy(array[18][j],"¦©");
	
	for(i=1;i<18;i++)
		strcpy(array[i][0],"¦¨");

	for(i=0;i<18;i++)
		strcpy(array[i][18],"¦ª");

	strcpy(array[0][0],"¦£");
	strcpy(array[18][0],"¦¤");
	strcpy(array[0][18],"¦¦");
	strcpy(array[18][18],"¦¥");

    for(i=3;i<19;i+=6)
		for(j=3;j<19;j+=6)
			strcpy(array[i][j],"¦¶");

		gotoxy(8,5);
	for(i=0;i<19;i++){
		for(j=0;j<19;j++){
			printf("%s",array[j][i]);
		}
		printf("\n        ");
	}

	gotoxy(50,8);
    printf("    ¦¢   %2dã­    %2dø¨   ¦¢",score_A,score_B);


	gotoxy(50,12);
    printf("    ¦¢   %2dã­    %2dø¨   ¦¢",score_B,score_A);

	if(move==1){
		gotoxy(52,7);
		printf("¡á");
		gotoxy(52,8);
		printf("¡á");
	}
	else if(move==2){
		gotoxy(52,11);
		printf("¡á");
		gotoxy(52,12);
		printf("¡á");
	}


}

void game_end(void)
{


		if(sc==1)
			score_A++;
		else
			score_B++;

    		gotoxy(14,12);
		printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤");
        gotoxy(14,13);
    	printf("¦¢   ÇöÀç ±îÁöÀÇ ½ºÄÚ¾î   ¦¢");
    	gotoxy(14,14);
     	printf("¦¢   %5s   vs  %5s    ¦¢",name_A,name_B);
        gotoxy(14,15);
    	printf("¦¢   %5d   :   %5d    ¦¢",score_A,score_B);
    	gotoxy(14,16);
    	printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
		Sleep(5000);
	

	gotoxy(14,12);
	printf("¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤");
	gotoxy(14,13);
	printf("¦¢        ÇÑÆÇ ´õ?        ¦¢");
	gotoxy(14,14);
	printf("¦¢                        ¦¢");
	gotoxy(14,15);
	printf("¦¢   y=Space bar, n=Esc   ¦¢");
	gotoxy(14,16);
	printf("¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");

}

void winner(void)
{
    winx_left=0;
	winx_right=0;
	winy_up=0;
	winy_down=0;
    wind_left=0;
    wind_right=0;

	//UP
	for(int i=1; check[player_x/2-4][player_y-5-i]==p ;i++)
		winy_up++;
	//DOWN
	for(i=1; check[player_x/2-4][player_y-5+i]==p ;i++)
		winy_down++;

	if(winy_up + winy_down == 4){
		gotoxy(10,3);
        if(p==1){
			printf("%s´Ô ã­!", name_A);
			sc=1;
			Sleep(3000);
			gotoxy(10,3);
			printf("                        ");
			game_end();}
		else{
			printf("%s´Ô ã­!", name_B);
			sc=2;
		    Sleep(3000);
			gotoxy(10,3);
			printf("                        ");
			game_end();}
	}

	//LEFT
	for(i=1; check[player_x/2-4-i][player_y-5]==p ;i++)
		winx_left++;
	//RIGHT
	for(i=1; check[player_x/2-4+i][player_y-5]==p ;i++)
		winx_right++;

	if(winx_left + winx_right == 4){
		gotoxy(10,3);
        if(p==1){
			printf("%s´Ô ã­!", name_A);
			sc=1;
			Sleep(3000);
			game_end();}
		else{
			printf("%s´Ô ã­!", name_B);
			sc=2;
			Sleep(3000);
			game_end();
		}
	}

	//DOWN_DIAGONAL-LEFT (ex)\n, ÇÏÇâ´ë°¢¼±)  
	for(i=1; check[player_x/2-4-i][player_y-5-i]==p ;i++)
		wind_left++;
	//DOWN_DIAGONAL-RIGHT
	for(i=1; check[player_x/2-4+i][player_y-5+i]==p ;i++)
		wind_right++;

	if(wind_left + wind_right == 4){
		gotoxy(10,3);
        if(p==1){
			printf("%s´Ô ã­!", name_A);
			sc=1;
			Sleep(3000);
			game_end();
		}
		else{
			printf("%s´Ô ã­!", name_B);
			sc=2;
			Sleep(3000);
			game_end();
		}
	}

	wind_left=0;
	wind_right=0;

	//UP_DIAGONAL-LEFT (ex)/, »óÇâ´ë°¢¼±)  
	for(i=1; check[player_x/2-4-i][player_y-5+i]==p ;i++)
		wind_left++;
	//UP_DIAGONAL-RIGHT
	for(i=1; check[player_x/2-4+i][player_y-5-i]==p ;i++)
		wind_right++;

	if(wind_left + wind_right == 4){
		gotoxy(10,3);
        if(p==1){
			printf("%s´Ô ã­!", name_A);
			sc=1;
			Sleep(3000);
			game_end();
		}
		else{
			printf("%s´Ô ã­!", name_B);
			sc=2;
			Sleep(3000);
			game_end();
		}
	}
		
}


void PlayerMove(void)
{
    
    int dx = 0;
    int dy = 0;
    int move_flag = 0;
	back=0;

    if ((GetAsyncKeyState(VK_UP) < 0) && (player_y > 5))        {move_flag = 1; dy = -1;}
    if ((GetAsyncKeyState(VK_DOWN) < 0) && (player_y < 23))     {move_flag = 1; dy =  1;}
    if ((GetAsyncKeyState(VK_LEFT) < 0) && (player_x > 8))      {move_flag = 1; dx = -2;}
    if ((GetAsyncKeyState(VK_RIGHT) < 0) && (player_x < 44))    {move_flag = 1; dx = +2;}
    if (GetAsyncKeyState(VK_RETURN)  <0){ 
		if(move==1){
            move_check();

			if(back==0)
			{
				 strcpy(array[player_x/2-4][player_y-5],"¡Ü");
	             move=2;
		         check[player_x/2-4][player_y-5]=1;
				 p=1;


				 gotoxy(52,11);
				 printf("¡á");
				 gotoxy(52,12);
				 printf("¡á");


				 gotoxy(52,7);
                 printf("  ");
				 gotoxy(52,8);
				 printf("  ");




				 winner();
			}
		}
		else if(move==2){
			move_check();

			if(back==0)
			{
				 strcpy(array[player_x/2-4][player_y-5],"¡Û");
	    	     move=1;
			     check[player_x/2-4][player_y-5]=2;
				 p=2;

				 gotoxy(52,11);
				 printf("  ");
				 gotoxy(52,12);
				 printf("  ");

				 gotoxy(52,7);
                 printf("¡á");
				 gotoxy(52,8);
				 printf("¡á");

				 winner();
			}
		}
	}


    if (move_flag != 0) {
        PlayerErase();
        player_x += dx;
        player_y += dy;
        PlayerDraw();
    }

}


void PlayerInit(void)
{
    player_x = 26;
    player_y = 14;

    PlayerDraw();
}
