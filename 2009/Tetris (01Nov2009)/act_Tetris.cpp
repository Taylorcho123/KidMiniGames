#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
/////////////////////
#define UP      72    //블록 회전
#define DOWN    80    //블록 1칸 강제개행
#define LEFT    75    //블록 왼쪽이동
#define RIGHT   77    //블록 오른쪽이동
#define SPACE   32    //블록 강제개행
#define ENTER   13    //게임 시작과 멈춤기능

#define randomize() srand((unsigned)time(NULL))
#define random(n) (rand() % (n))

#define START_X 12    //블록이 처음 내려올시 x위치
#define START_Y  1    //블록이 처음 내려올시 y위치
/////////////////////
void rotate();        //블럭을 시계방향으로 회전.
void move();          //블럭 이동.
int  bump();          //충돌 체크. (return값 有)

void copy_imap();     //떨어진 블록을 imap에 저장 한후 블록 재생
void erase_x();       //(if) X축에 빈 공간이 없을때 지운후 블록들을 한칸 아래로
int  game_over();     //게임 오버 체크! (return값 有)

void set_block();
void print_block();
void erase_block();

void shift_down();
void shift_left();
void shift_right();
void shift_space();
void pause_enter();   //게임 시작과 멈춤기능

void cursorhide();
void gotoxy(int x,int y);
void setcolor(int color, int bgcolor);

void main_draw();
void main_help();

void easy_view();    //게임편의기능.떨어질곳 미리보기.
void erase_view();   //떨어질곳 지우기.. (비실용적)
/////////////////////
int block[4][4]={0};
int tblock[4][4]={0};
int block7[7][4][4]={
{{0,0,0,0},
{0,0,0,0},
{8,8,8,8},
{0,0,0,0}}
,
{{0,0,0,0},
{0,9,9,0},
{0,9,9,0},
{0,0,0,0}}
,
{{0,0,0,0},
{10,10,0,0},
{0,10,10,0},
{0,0,0,0}}
,
{{0,0,0,0},
{0,0,11,11},
{0,11,11,0},
{0,0,0,0}}
,
{{0,12,0,0},
{0,12,0,0},
{0,12,12,0},
{0,0,0,0}}
,
{{0,0,13,0},
{0,0,13,0},
{0,13,13,0},
{0,0,0,0}}
,
{{0,0,0,0},
{0,14,0,0},
{14,14,14,0},
{0,0,0,0}}
};

char map[25][35]={
	{"15555555555555555552001555555552"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006003555555554"},
	{"60000000000000000006001555555552"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006003555555554"},
	{"60000000000000000006001555555552"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006003555555554"},
	{"60000000000000000006000000000000"},
	{"60000000000000000006000000000000"},
	{"60000000000000000006000000000000"},
	{"60000000000000000006000000000000"},
	{"60000000000000000006000000000000"},
    {"60000000000000000006001555555552"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006006000000006"},
	{"60000000000000000006006000000006"},
	{"35555555555555555554003555555554"}
};
int  imap[25][20]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int x=12;
int y=2;

int score=0;
int c;               //block color.
int n;
/////////////////////
void cursorhide(){
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}
/**/
void gotoxy(int x, int y) /*커서이동 함수 부분*/
{
    COORD XY = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}
/**/
void setcolor(int color, int bgcolor) {
    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
/**********************************************/
void rotate()
{
	int block2[4][4];
	int i,j,k=0;

	for(i=0;i<4;i++){
		k=0;
		for(j=3;j>=0;j--){
			block2[i][k]=block[j][i];
			k++;
		}
	}
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			block[i][j]=block2[i][j];
		}
	}
}

void move()
{
    int check=0;
    int timer=0;
    int t=0;
    int g=0;

	while(1){

		timer=(int) clock()/(CLK_TCK/2);     //중력!
		if((timer%2==0) && (t==0)){
			shift_down();
			t=1;
		}
		else if((timer%2!=0) && (t=1)){t=0;}

		g=game_over();
		if(g==1)                            //게임 오버가 되면 프로그램을 종료시킨다.
			break;

		if(kbhit()){
		 
			char ch=getch();
               
    		   switch(ch){
  
    		   case UP:
				       erase_view();
	    			   erase_block();
		    		   rotate();

					   check=bump();
					   if(check==-1){
						   rotate();
						   rotate();
						   rotate();
					   }
					   easy_view();
			    	   print_block();
				       break;

    		   case DOWN:
	    				shift_down();
		    			break;

    		   case LEFT:
	    				shift_left();
		    			break;

    		   case RIGHT:
	    				shift_right();
		    		    break;

			   case ' ':
				        shift_space();
						break;

			   case ENTER:
				        pause_enter();
						break;

			   }
			
		}

	}
}
/**/
int  bump()
{
   int ix;
   int iy;
   int i,j;

   iy=y;

	for(i=0;i<4;i++){
		ix=x/2;
		for(j=0;j<4;j++){

		    if(block[i][j]>0 && imap[iy][ix]>0){
				return -1;
			}
			ix++;
		}
		iy++;
	}
	return 0;
}
/*******************************************/
void set_block()
{
	int i,j;
	
	c=n;
	setcolor(c+8,15);
    srand((unsigned)time(NULL));
    n=rand()%7;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			block[i][j]=tblock[i][j];
	}}

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			tblock[i][j]=block7[n][i][j];
	}}
	setcolor(n+8,15);
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(tblock[i][j]==0){
				gotoxy(50+j*2,3+i);
				printf("  ");
			}
			else if(tblock[i][j]>0){
				gotoxy(50+j*2,3+i);
				printf("■");
			}
	}}

			
}
/**/
void print_block()
{
	int i,j;
	setcolor(c+8,15);

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){

			if(block[i][j]>0) {
               gotoxy(x+j*2,y+i);
			   printf("■");
			}
		}
	}
}		
/**/
void erase_block()
{
   int i,j;

	for(i=0;i<4;i++){	
		for(j=0;j<4;j++){

			if(block[i][j]>0){
				gotoxy(x+j*2,y+i);
               printf("  ");
			}
		}
	}
}
/*******************************************/
void copy_imap()
{
    int ix;
    int iy;
    int i,j;

       iy=y;

		for(i=0;i<4;i++){
    		ix=x/2;
    		for(j=0;j<4;j++){
    
				if(block[i][j]>0){    
    			imap[iy][ix]=c+8;
				}
    			ix++;
			}
    		iy++;
		}

}
/**/
void erase_x()
{
	int i=0,j=0,temp=0;
	int k=0,l=1;//l=1!

	for(i=23;i>0;i--){
		for(j=1;j<19 && imap[i][j]!=0;j++);
	
	    if(j==19){
			score+=20;
            
        	for(k=i;k>START_Y;k--){
		    	memcpy(imap[k],imap[k-1],20*sizeof(int));

				for(l=1;l<19;l++){

    				if(imap[k][l]>0){
	        			gotoxy(l*2,k);
						setcolor(imap[k][l],15);
		    			printf("■");
					}
    		 	    else if(imap[k][l]==0){
	    				gotoxy(l*2,k);
		    			printf("  ");
					}
			}}

			i++;    //imap[k]는 imap[k-1]이 되었다. -> imap[k]에 또다시 j==19일 가능성이 있기 때문에 i++를 한다.
		}//if문 끝
	}






}
/**/
int  game_over()
{
	int g_check=0;

	g_check=bump();
	if(g_check==-1){
		gotoxy(2,1);
		
		setcolor(7,15);
		for(int i=1;i<24;i++){
			gotoxy(2,i);
			for(int j=1;j<19;j++){
				printf("■");
			}
			Sleep(200);
		}
		setcolor(12,15);
		gotoxy(15,11);
		printf("GAME OVER");
		Sleep(2000);
		getch();

		return 1;
	}
	return 0;
}
/*******************************************/
void shift_down()
{
	int d_check;

	erase_view();
	erase_block();
	gotoxy(x,y++);

	d_check=bump();
	if(d_check==-1){
		gotoxy(x,y--);
    	print_block();

        copy_imap();
		erase_x();

		gotoxy(x=START_X , y=START_Y);
		set_block();

		score+=1;             //스코어!!
		gotoxy(55,10);
		printf("%d",score);
	}
	easy_view();
	print_block();
}
/**/
void shift_left()
{
	int l_check;
	
	erase_view();
	erase_block();
	gotoxy(x-=2,y);

	l_check=bump();
	if(l_check==-1)
		gotoxy(x+=2,y);

	easy_view();
	print_block();
}
/**/
void shift_right()
{
	int r_check;
	
	erase_view();
	erase_block();
	gotoxy(x+=2,y);

	r_check=bump();
	if(r_check==-1)
		gotoxy(x-=2,y);

	easy_view();
	print_block();
}
/**/
void shift_space()
{
	int s_check;
	
	while(s_check!=-1)
	{
    	erase_block();
    	gotoxy(x,y++);

    	s_check=bump();
		if(s_check==-1){
	    	gotoxy(x,y--);
        	print_block();

			copy_imap();
			erase_x();

    		gotoxy(x=START_X , y=START_Y);
	    	set_block();

			score+=1;     //스코어!!
		    gotoxy(55,10);
    		printf("%d",score);
		}

    	print_block();
	}
}
/**/
void pause_enter()
{
	int ch;
	ch=getch();

	if(ch!=ENTER)
		pause_enter();
}
/*******************************************/
int main(void)
{	
	main_draw();
	set_block();
    set_block();

	print_block();

    cursorhide();
	move();

	return 0;
}
/*******************************************/
void main_draw()
{
    int m;
	int x,y;

	system("mode con:cols=65");
	system("mode con:lines=25");
	system("color F0");
//Tetris
	printf("■■■■■■■■■■-by.란탄\n");
	printf("      ■\n");
	printf("      ■\n");
	printf("      ■\n");
	printf("      ■\n");
	printf("      ■                  ■                    ■\n");
	printf("      ■    ■■■    ■■■■■                        ■■■\n");
	printf("      ■  ■      ■      ■      ■    ■■  ■■    ■      ■\n");
	printf("      ■  ■      ■      ■      ■  ■        ■    ■\n");
	printf("      ■  ■■■■■      ■      ■■          ■      ■■\n");
	printf("      ■  ■              ■      ■            ■          ■\n");
	printf("      ■  ■              ■      ■            ■            ■\n");
	printf("      ■  ■      ■      ■      ■            ■    ■      ■\n");
	printf("      ■    ■■■          ■■  ■          ■■■    ■■■\n");
    printf("\n\n\n\n");
	printf("                    ┌──────────┐\n");
	printf("                    │     1.게임시작     │\n");
	printf("                    │     2.게임방법     │\n");
	printf("                    ├──────────┤\n");
	printf("                    │     입력:          │\n");
	printf("                    └──────────┘\n");
	gotoxy(33,22);
	scanf("%d",&m);

	if(m==1)
	{
		system("cls");


		     for(y=0; y<25; y++){
                for(x=0; x<35; x++){
                    if(map[y][x] == '0')    printf("　");
                    if(map[y][x] == '1')    printf("┏");
                    if(map[y][x] == '2')    printf("┓");
                    if(map[y][x] == '3')    printf("┗");
                    if(map[y][x] == '4')    printf("┛");
                    if(map[y][x] == '5')    printf("━");
                    if(map[y][x] == '6')    printf("┃");
				}
			}
			 gotoxy(46,10);
			 printf("score:");
			 gotoxy(51,1);
			 printf("-next-");
			 gotoxy(46,21);
			 printf("PAUSE: ENTER");
	}

	else if(m==2){
		main_help();
		main_draw();
	}
}
/**/
void main_help()
{
	system("cls");

	printf("-혹시 모르시는 분들을 위한 테트리스 게임설명! -\n\n\n");
	printf("움직일때는 방향키,\n\n");
	printf("빠르게 떨어지게 하고 싶을땐 스페이스 바\n\n");
	printf("그리고, 잠시 쉬고 싶을땐 엔터를 누르시면 됩니다.\n\n\n");
	printf("아무키나 누르시면 메인으로 이동합니다.");

	getch();
	system("cls");
}
/*******************************************/
void easy_view()
{
	int ey=y;
	int e_check=0;
	int i=0,j=0;

	ey=y;

	while(e_check!=-1){
		y++;

		e_check=bump();
		if(e_check==-1){
			gotoxy(x,y--);

			//erase_block();

			for(i=0;i<4;i++){       //그린다.
				for(j=0;j<4;j++){ 

					if(block[i][j]>0) {
						gotoxy(x+j*2,y+i);
            			printf("□");
			}}}
	}}

	y=ey;
}
/**/
void erase_view()
{
	int ey=y;
	int e_check=0;
	int i=0,j=0;

	ey=y;

	while(e_check!=-1){
		y++;

		e_check=bump();
		if(e_check==-1){
			gotoxy(x,y--);

			erase_block();
	}}
	y=ey;
}
