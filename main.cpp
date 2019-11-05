#include <ncurses.h>
#include <iostream>
#include <locale.h>
#include <string>
#include <clocale> 
#include <algorithm>
static int stage = 1;
static int map3copy[11][9] = {
    {4,4,4,4,4,4,4,4,4},
    {1,1,1,1,1,1,1,1,4},
    {1,1,0,1,0,1,1,1,4},
    {1,0,0,0,0,0,1,1,4},
    {1,0,2,1,0,0,0,1,1},
    {1,0,0,2,0,0,2,0,1},
    {1,1,1,0,0,0,0,0,1},
    {1,1,1,0,0,0,0,1,1},
    {4,1,1,1,1,1,1,1,1},
    {4,1,1,1,1,1,1,1,1},
    {4,4,4,4,4,4,4,4,4}
};
static int map2copy[11][9] = {
    {4,4,4,4,4,4,4,4,4},
    {1,1,1,1,1,4,4,4,4},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,0,0,1,1,1},
    {4,1,1,1,0,0,0,0,1},
    {1,1,0,2,0,0,2,0,1},
    {1,1,0,0,0,0,2,0,1},
    {1,1,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1},
    {4,4,4,4,4,4,4,4,4}
};

static int map1copy[11][9] = {
    {4, 4, 4, 4, 4, 4, 4, 4, 4},
    {4, 1, 1, 1, 1, 1, 1, 4, 4},
	{4, 1, 0, 0, 0, 0, 1, 4, 4},
	{4, 1, 0, 0, 0, 0, 1, 4, 4},
	{4, 1, 0, 0, 2, 0, 1, 4, 4},
	{4, 1, 1, 2, 0, 0, 1, 1, 4},
	{4, 4, 1, 0, 2, 0, 0, 1, 4},
	{4, 4, 1, 0, 0, 0, 0, 1, 4},
	{4, 4, 1, 0, 0, 1, 1, 1, 4},
	{4, 4, 1, 1, 1, 1, 4, 4, 4},
    {4, 4, 4, 4, 4, 4, 4, 4, 4},
	};

void clear1(int maps);
static int map1[11][9]={
    {4, 4, 4, 4, 4, 4, 4, 4, 4},
    {4, 1, 1, 1, 1, 1, 1, 4, 4},
	{4, 1, 0, 0, 0, 0, 1, 4, 4},
	{4, 1, 0, 0, 0, 0, 1, 4, 4},
	{4, 1, 0, 0, 2, 0, 1, 4, 4},
	{4, 1, 1, 2, 0, 0, 1, 1, 4},
	{4, 4, 1, 0, 2, 0, 0, 1, 4},
	{4, 4, 1, 0, 0, 0, 0, 1, 4},
	{4, 4, 1, 0, 0, 1, 1, 1, 4},
	{4, 4, 1, 1, 1, 1, 4, 4, 4},
    {4, 4, 4, 4, 4, 4, 4, 4, 4},
	};

static int map1solve[3][2] = {{2,2}, {3,2}, {4,2}} ;
static int map2solve[3][2] = {{3,4}, {3,5}, {4,7}} ;
static int map3solve[3][2] = {{4,5}, {4,6}, {7,6}} ;
int check1();
int pr= 3, pc=2;
void moveon(int s);
void print(WINDOW * win1);
static int step;

int main() {
    initscr(); // ncurses 초기화/ 가장 먼저 수행
    setlocale(LC_ALL, ""); // 유니코드를 사용하기 위해 하는 행위.
    start_color(); // 색깔을 사용하기 위해 하는 행위임
    keypad(stdscr, TRUE); // 키 입력을 받기 위해 하는 행위임.
    curs_set(0); // 커서를 감춤
    noecho(); // 콘솔 출력을 보이지 않게 함.

    int key; // key를 받기 위한 셋임

    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_GREEN);

    resize_term(999,999); // 스크린 크기 조절
    mvprintw(10,0,"This is Push-Box1"); // 스크린에 보일 내용임.
    mvprintw(11,0,"All right is on 20181685");

    key = getch();
    clear();
    printw("%d\n",key);
    refresh();
    getch();
    clear();
    WINDOW *win1;
    WINDOW *win2;
        while(true){
        if(key == 27){break;}
        if(check1()==3){
            clear();
            if(stage==3){break;}
            printw("clear");
            refresh();
            clear1(++stage);
            getch();
        }
        clear();
        win1 = newwin(11, 9, 2, 3);
        print(win1);
        wrefresh(win1);
        
        win2 = newwin(9,15,5,20);
        mvwprintw(win2,0,1,"%s\n   ","Stage");
        mvwprintw(win2,1,1,"%d\n   ",stage);
        mvwprintw(win2,3,1,"%s\n   ","Step");
        mvwprintw(win2,4,1,"%d\n",step);
        mvwprintw(win2,5,1,"%s\n   ","Push");
        mvwprintw(win2,6,1,"%d\n   ",check1());
        mvwprintw(win2,8,1,"Restart : R");
        //s 258 // 259 w // 261 d // 260 a // 
        wrefresh(win2);
        refresh();
        key = getch();
        

        moveon(key);
    }
            printw("ALL STAGE CLEAR!!");
            refresh();
            
            getch();
    return 0;
}

void moveon(int s){
    
	int r, c;
	if(s == 259){r = -1; c = 0;}
	else if (s == 258){ r= 1; c= 0;}
	else if (s == 260){ r= 0; c= -1;}
	else if(s == 261){ r= 0; c= 1;}
    else if(s==114){
        clear1(stage);

    return;}
    
	if (map1[pr + r][pc + c] == 1) {
		
		return;
	}
    else if (map1[pr + r][pc + c] == 0) {
		pr += r; pc += c;
        step ++;
		return;
	}
	else if(map1[pr + r][pc + c] == 2 && map1[pr + r*2][pc + c*2] == 2){

		return;
	}
    else if(map1[pr + r][pc + c] == 2 && map1[pr + r*2][pc + c*2] == 0){
		pr += r; pc += c;
		map1[pr][pc] = 0;
		map1[pr + r][pc + c] = 2;
        step ++;

	}
}

int check1(){
    int k= 0;
    if(map1[map1solve[0][0]][map1solve[0][1]] == 2 &&map1[map1solve[1][0]][map1solve[1][1]] == 2&&map1[map1solve[2][0]][map1solve[2][1]] == 2)
    {return 3;}
    if(map1[map1solve[0][0]][map1solve[0][1]] == 2){
        k++;
    }
    if(map1[map1solve[1][0]][map1solve[1][1]] == 2){k++;}
    if(map1[map1solve[2][0]][map1solve[2][1]] == 2){k++;} 
    return k;
}

void clear1(int maps){
    for(int i = 0 ; i< 11; i++){
        for(int j = 0;  j < 9 ; j++){
            if(maps == 1)
                map1[i][j] = map1copy[i][j];
            else if(maps == 2)
                map1[i][j] = map2copy[i][j];
            else if(maps == 3)
                map1[i][j] = map3copy[i][j];
        }
    }
    if(maps == 2){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j< 2; j++){
                map1solve[i][j] = map2solve[i][j];
            }
        }
    }
    else if(maps == 3){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j< 2; j++){
                map1solve[i][j] = map3solve[i][j];
            }
        }
    }
    if(maps ==1 ){
        pr = 3; pc = 3;}
    else if(maps == 2){
        pr =7; pc = 3 ;}
    else if(maps == 3){
        pr =3; pc = 2 ;}

    step = 0;
}

void print(WINDOW * win1){
    
    map1[pr][pc] = 7;
        
    for(int i = 0; i < 11; i ++){
        for(int j = 0; j < 9; j++){
            if(map1[i][j]==1){
                wattron(win1,COLOR_PAIR(1));
                mvwprintw(win1,i,j,"%s\n", "0");
                wattroff(win1,COLOR_PAIR(1));}
            else if(map1[i][j]==2){
                wattron(win1,COLOR_PAIR(2));
                mvwprintw(win1,i,j,"%s\n", "0");
                wattroff(win1,COLOR_PAIR(2));}
            else if(map1[i][j]==7){
                wattron(win1,COLOR_PAIR(3));
                mvwprintw(win1,i,j,"%s\n", "*");
                wattroff(win1,COLOR_PAIR(3));}
            else if(map1[i][j]==4){
                wattron(win1,COLOR_PAIR(4));
                mvwprintw(win1,i,j,"%s\n", "0");
                wattroff(win1,COLOR_PAIR(4));}
            else{
                mvwprintw(win1,i,j,"%s\n", " ");
                if(i == map1solve[0][0] && j == map1solve[0][1]){
                    wattron(win1,COLOR_PAIR(5));
                    mvwprintw(win1,i,j,"%s\n", " ");
                    wattroff(win1,COLOR_PAIR(5));}
                else if(i == map1solve[1][0] && j == map1solve[1][1]){
                    wattron(win1,COLOR_PAIR(5));
                    mvwprintw(win1,i,j,"%s\n", " ");
                    wattroff(win1,COLOR_PAIR(5));}
                    else if(i == map1solve[2][0] && j == map1solve[2][1]){
                    wattron(win1,COLOR_PAIR(5));
                    mvwprintw(win1,i,j,"%s\n", " ");
                    wattroff(win1,COLOR_PAIR(5));}
                    
                    }
                
                }
                            
            }

    refresh();
    map1[pr][pc] = 0;

}