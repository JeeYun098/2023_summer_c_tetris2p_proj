#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define LEFT 75 //좌로 이동    //키보드값들 
#define RIGHT 77 //우로 이동 
#define UP 72 //회전 
#define DOWN 80 //soft drop

#define A 97 //좌로 이동    //키보드값들 
#define D 100 //우로 이동 
#define W 119 //회전 
#define S 115 //soft drop

#define SPACE 32 //hard drop
#define G 103 //hard drop

#define one 49 //delete_item
//#define two 50 //slow_item

#define K 107 //delete_item
//#define L 108 //slow_item

#define p 112 //일시정지 
#define P 80 //일시정지
#define ESC 27 //게임종료 

#define false 0
#define true 1

#define ACTIVE_BLOCK -2 // 게임판배열에 저장될 블록의 상태들 
#define CEILLING -1     // 블록이 이동할 수 있는 공간은 0 또는 음의 정수로 표현 
#define EMPTY 0         // 블록이 이동할 수 없는 공간은 양수로 표현 
#define WALL 1
#define INACTIVE_BLOCK 2 // 이동이 완료된 블록값 

#define MAIN_X 11 //게임판 가로크기 
#define MAIN_Y 23 //게임판 세로크기 
#define MAIN_X_ADJ 3 //게임판 위치조정 
#define MAIN_Y_ADJ 1 //게임판 위치조정 

#define STATUS_X_ADJ MAIN_X_ADJ+MAIN_X+2 //게임정보표시 위치조정 
#define STATUS_XX_ADJ STATUS_X_ADJ+9 //게임정보표시 위치조정 

#define MAIN_XX STATUS_XX_ADJ+2 //게임판 가로크기 
#define MAIN_YY 23 //게임판 세로크기 
#define MAIN_XX_ADJ MAIN_XX-8 //게임판 위치조정 
#define MAIN_YY_ADJ 1 //게임판 위치조정 



int STATUS_Y_GOAL; //GOAL 정보표시위치Y 좌표 저장 
int STATUS_Y_LEVEL; //LEVEL 정보표시위치Y 좌표 저장
int STATUS_Y_SCORE; //SCORE 정보표시위치Y 좌표 저장

int STATUS_YY_GOAL; //GOAL 정보표시위치Y 좌표 저장 
int STATUS_YY_LEVEL; //LEVEL 정보표시위치Y 좌표 저장
int STATUS_YY_SCORE; //SCORE 정보표시위치Y 좌표 저장

int blocks[7][4][4][4] = {
{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
 {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},
{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},
{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},
 {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},
{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}}
}; //블록모양 저장 4*4공간에 블록을 표현 blcoks[b_type][b_rotation][i][j]로 사용 

int b_type; //블록 종류를 저장 
int b_rotation; //블록 회전값 저장 
int b_type_next; //다음 블록값 저장 

int b_type2; //블록 종류를 저장 
int b_rotation2; //블록 회전값 저장 
int b_type_next2; //다음 블록값 저장 

int main_org[MAIN_Y][MAIN_X]; //게임판의 정보를 저장하는 배열 모니터에 표시후에 main_cpy로 복사됨 
int main_cpy[MAIN_Y][MAIN_X]; //즉 maincpy는 게임판이 모니터에 표시되기 전의 정보를 가지고 있음 
//main의 전체를 계속 모니터에 표시하지 않고(이렇게 하면 모니터가 깜빡거림) 
//main_cpy와 배열을 비교해서 값이 달라진 곳만 모니터에 고침 

int main_org2[MAIN_YY][MAIN_XX];
int main_cpy2[MAIN_YY][MAIN_XX];

int key; //키보드로 입력받은 키값을 저장 

int bx, by; //이동중인 블록의 게임판상의 x,y좌표를 저장

int speed; //게임진행속도 
int level; //현재 level 
int level_goal; //다음레벨로 넘어가기 위한 목표점수 
int cnt; //현재 레벨에서 제거한 줄 수를 저장 
int score; //현재 점수 
int last_score = 0; //마지막게임점수 
int best_score = 0; //최고게임점수 
int game_over = 0; //게임오버여부


int bx2, by2; //이동중인 블록의 게임판상의 x,y좌표를 저장 

int speed2; //게임진행속도 
int level2; //현재 level 
int level_goal2; //다음레벨로 넘어가기 위한 목표점수 
int cnt2; //현재 레벨에서 제거한 줄 수를 저장 
int score2; //현재 점수 
int last_score2 = 0; //마지막게임점수 
int best_score2 = 0; //최고게임점수 
int game_over2 = 0; //게임오버여부


int new_block_on = 0; //새로운 블럭이 필요함을 알리는 flag 
int crush_on = 0; //현재 이동중인 블록이 충돌상태인지 알려주는 flag 
int level_up_on = 0; //다음레벨로 진행(현재 레벨목표가 완료되었음을) 알리는 flag 
int space_key_on = 0; //hard drop상태임을 알려주는 flag 

int new_block_on2 = 0; //새로운 블럭이 필요함을 알리는 flag 
int crush_on2 = 0; //현재 이동중인 블록이 충돌상태인지 알려주는 flag 
int level_up_on2 = 0; //다음레벨로 진행(현재 레벨목표가 완료되었음을) 알리는 flag 
int space_key_on2 = 0; //hard drop상태임을 알려주는 flag 

int delete_item = 0;
//int slow_item = 0;
int drop = 0;

int delete_item2 = 0;
//int slow_item2 = 0;
int drop2 = 0;


void title(void); //게임시작화면 
void reset(void); //게임판 초기화 
void reset_main(void); //메인 게임판(main_org[][]를 초기화)
void reset_main_cpy(void); //copy 게임판(main_cpy[][]를 초기화)
void reset_main_cpy2(void); //copy 게임판(main_cpy2[][]를 초기화)
void draw_map(void); //게임 전체 인터페이스를 표시 
void draw_main(void); //게임판을 그림 
void draw_main2(void); //게임판을 그림 
void new_block(void); //새로운 블록을 하나 만듦 
void check_key(void); //키보드로 키를 입력받음 
void drop_block(void); //블록을 아래로 떨어트림 
int check_crush(int bx, int by, int rotation); //bx, by위치에 rotation회전값을 같는 경우 충돌 판단 
void move_block(int dir); //dir방향으로 블록을 움직임 
void check_line(void); //줄이 가득찼는지를 판단하고 지움 
void check_level_up(void); //레벨목표가 달성되었는지를 판단하고 levelup시킴 

void new_block2(void); //새로운 블록을 하나 만듦 
void drop_block2(void); //블록을 아래로 떨어트림
int check_crush2(int bx2, int by2, int rotation2); //bx, by위치에 rotation회전값을 같는 경우 충돌 판단 
void check_line2(void); //줄이 가득찼는지를 판단하고 지움 
void check_level_up2(void); //레벨목표가 달성되었는지를 판단하고 levelup시킴 


void check_game_over(void); //게임오버인지 판단하고 게임오버를 진행 
void check_game_over2(void); //게임오버인지 판단하고 게임오버를 진행 
void check_winner(void); //승자표시하고 게임 재시작 
void pause(void);//게임을 일시정지시킴 

void gotoxy(int x, int y) { //gotoxy함수 
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //커서숨기는 함수에 사용되는 열거형 
void setcursortype(CURSOR_TYPE c) { //커서숨기는 함수 
    CONSOLE_CURSOR_INFO CurInfo;

    switch (c) {
    case NOCURSOR:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

int main() {
    int i;

    srand((unsigned)time(NULL)); //난수표생성 
    setcursortype(NOCURSOR); //커서 없앰 
    title(); //메인타이틀 호출 
    reset(); //게임판 리셋 

    while (1) {
        for (i = 0; i < 5; i++) { //블록이 한칸떨어지는동안 5번 키입력받을 수 있음 
            check_key(); //키입력확인 
            draw_main(); //화면을 그림 
            draw_main2(); //화면을 그림 
            Sleep(speed); //게임속도조절 
            Sleep(speed2); //게임속도조절 
            if (crush_on && check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
            if (crush_on2 && check_crush2(bx2, by2 + 1, b_rotation2) == false) Sleep(100);
            //블록이 충돌중인경우 추가로 이동및 회전할 시간을 갖음 
            if (space_key_on == 1) { //스페이스바를 누른경우(hard drop) 추가로 이동및 회전할수 없음 break; 
                space_key_on = 0;
                break;
            }
            if (space_key_on2 == 1) { //G를 누른경우(hard drop) 추가로 이동및 회전할수 없음 break; 
                space_key_on2 = 0;
                break;
            }
        }
        drop_block(); // 블록을 한칸 내림 
        drop_block2();

        check_level_up(); // 레벨업을 체크
        check_level_up2();

        check_game_over(); //1p 게임오버를 체크
        check_game_over2(); //2p 게임오버를 체크

        if ((game_over == 1) && (game_over2 == 1)) check_winner(); //둘다게임오버되면 승자를 체크 

        if (new_block_on == 1) {
            drop++; //블록 떨어질때마다 drop증가
            if (drop % 10 == 0) {
                delete_item++; //10번 떨어지면 delete_item증가
            }
            new_block(); // 뉴 블럭 flag가 있는 경우 새로운 블럭 생성
        }
        if (new_block_on2 == 1) {
            drop2++;
            if (drop2 % 10 == 0) {
                delete_item2++;
            }
            new_block2();
        }
    }
}

void title(void) {
    int x = 5; //타이틀화면이 표시되는 x좌표 
    int y = 4; //타이틀화면이 표시되는 y좌표 
    int cnt; //타이틀 프레임을 세는 변수  

    gotoxy(x + 10, y + 0); printf("■□□□■■■□□■■□□■■"); Sleep(100);
    gotoxy(x + 10, y + 1); printf("■■■□  ■□□    ■■□□■"); Sleep(100);
    gotoxy(x + 10, y + 2); printf("□□□■              □■  ■"); Sleep(100);
    gotoxy(x + 10, y + 3); printf("■■□■■  □  ■  □□■□□"); Sleep(100);
    gotoxy(x + 10, y + 4); printf("■■  ■□□□■■■□■■□□"); Sleep(100);
    gotoxy(x + 10 + 5, y + 2); printf("T E T R I S"); Sleep(100);
    gotoxy(x + 10, y + 7); printf("Please Enter Any Key to Start..");
    gotoxy(x, y + 9); printf("             <1P>             ");
    gotoxy(x, y + 10); printf("   W   : Shift");
    gotoxy(x, y + 11); printf(" A   D : Left / Right");
    gotoxy(x, y + 12); printf("   S   : Soft Drop");
    gotoxy(x, y + 13); printf("   G   : Hard Drop");
    gotoxy(x, y + 14); printf("   1   : Delete Item");
    gotoxy(x, y + 15); printf("   P   : Pause");
    gotoxy(x, y + 16); printf("  ESC  : Quit");
    gotoxy(x, y + 18); printf("BONUS FOR HARD DROPS / COMBOS");
    gotoxy(x + 20, y + 9); printf("             <2P>             ");
    gotoxy(x + 20, y + 10); printf("  △   : Shift");
    gotoxy(x + 20, y + 11); printf("◁  ▷ : Left / Right");
    gotoxy(x + 20, y + 12); printf("  ▽   : Soft Drop");
    gotoxy(x + 20, y + 13); printf(" SPACE : Hard Drop");
    gotoxy(x + 20, y + 14); printf("   K   : Delete Item");
    gotoxy(x + 20, y + 15); printf("   P   : Pause");
    gotoxy(x + 20, y + 17); printf("  ESC  : Quit");
    gotoxy(x + 20, y + 18); printf("BONUS FOR HARD DROPS / COMBOS");

    for (cnt = 0;; cnt++) { //cnt를 1씩 증가시키면서 계속 반복    //하나도 안중요한 별 반짝이는 애니메이션효과 
        if (_kbhit()) break; //키입력이 있으면 무한루프 종료 
        if (cnt % 200 == 0) { gotoxy(x + 10 + 4, y + 1); printf("★"); }       //cnt가 200으로 나누어 떨어질때 별을 표시 
        if ((cnt % 200 - 100) == 0) { gotoxy(x + 10 + 4, y + 1); printf("  "); } //위 카운트에서 100카운트 간격으로 별을 지움 
        if ((cnt % 350) == 0) { gotoxy(x + 10 + 13, y + 2); printf("☆"); } //윗별과 같지만 시간차를 뒀음 
        if ((cnt % 350 - 100) == 0) { gotoxy(x + 10 + 13, y + 2); printf("  "); }
        Sleep(10); // 00.1초 딜레이  
    }

    while (_kbhit()) _getch(); //버퍼에 기록된 키값을 버림 

}

void reset(void) {

    FILE* file = fopen("score.dat", "rt"); // score.dat파일을 연결 
    if (file == 0) { best_score = 0; } //파일이 없으면 걍 최고점수에 0을 넣음 
    else {
        fscanf(file, "%d", &best_score); // 파일이 열리면 최고점수를 불러옴 
        fclose(file); //파일 닫음 
    }

    FILE* file2 = fopen("score2.dat", "rt"); // score.dat파일을 연결 
    if (file2 == 0) { best_score2 = 0; } //파일이 없으면 걍 최고점수에 0을 넣음 
    else {
        fscanf(file2, "%d", &best_score2); // 파일이 열리면 최고점수를 불러옴 
        fclose(file2); //파일 닫음 
    }

    key = 0;
    game_over = 0;
    game_over2 = 0;

    level = 1; //각종변수 초기화 
    score = 0;
    level_goal = 1000;
    crush_on = 0;
    cnt = 0;
    speed = 100;


    level2 = 1; //각종변수 초기화 
    score2 = 0;
    level_goal2 = 1000;
    crush_on2 = 0;
    cnt2 = 0;
    speed2 = 100;

    delete_item = 0;
    //slow_item = 0;
    drop = 0;

    delete_item2 = 0;
    //slow_item2 = 0;
    drop2 = 0;

    system("cls"); //화면지움 
    reset_main(); // main_org를 초기화 
    draw_map(); // 게임화면을 그림
    draw_main(); // 게임판을 그림 
    draw_main2(); // 게임판을 그림 

    b_type_next = rand() % 7; //다음번에 나올 블록 종류를 랜덤하게 생성 
    b_type_next2 = rand() % 7; //다음번에 나올 블록 종류를 랜덤하게 생성 
    new_block(); //새로운 블록을 하나 만듦 
    new_block2(); //새로운 블록을 하나 만듦
}

void reset_main(void) { //게임판을 초기화  
    int i, j;

    for (i = 0; i < MAIN_Y; i++) { // 게임판을 0으로 초기화  
        for (j = 0; j < MAIN_X; j++) {
            main_org[i][j] = 0;
            main_cpy[i][j] = 100;
        }
    }
    for (j = 1; j < MAIN_X; j++) { //y값이 3인 위치에 천장을 만듦 
        main_org[3][j] = CEILLING;
    }
    for (i = 1; i < MAIN_Y - 1; i++) { //좌우 벽을 만듦  
        main_org[i][0] = WALL;
        main_org[i][MAIN_X - 1] = WALL;
    }
    for (j = 0; j < MAIN_X; j++) { //바닥벽을 만듦 
        main_org[MAIN_Y - 1][j] = WALL;
    }

    for (i = 0; i < MAIN_YY; i++) { // 게임판을 0으로 초기화  
        for (j = MAIN_XX - 11; j < MAIN_XX; j++) {
            main_org2[i][j] = 0;
            main_cpy2[i][j] = 100;
        }
    }
    for (j = MAIN_XX - 10; j < MAIN_XX; j++) { //y값이 3인 위치에 천장을 만듦 
        main_org2[3][j] = CEILLING;
    }
    for (i = 1; i < MAIN_YY - 1; i++) { //좌우 벽을 만듦  
        main_org2[i][MAIN_XX - 11] = WALL;
        main_org2[i][MAIN_XX - 1] = WALL;
    }
    for (j = MAIN_XX - 11; j < MAIN_XX; j++) { //바닥벽을 만듦 
        main_org2[MAIN_YY - 1][j] = WALL;
    }
}

void reset_main_cpy(void) { //main_cpy를 초기화 
    int i, j;

    for (i = 0; i < MAIN_Y; i++) {         //게임판에 게임에 사용되지 않는 숫자를 넣음 
        for (j = 0; j < MAIN_X; j++) {  //이는 main_org와 같은 숫자가 없게 하기 위함 
            main_cpy[i][j] = 100;
        }
    }
}

void reset_main_cpy2(void) { //main_cpy를 초기화 
    int i, j;

    for (i = 0; i < MAIN_YY; i++) {         //게임판에 게임에 사용되지 않는 숫자를 넣음 
        for (j = MAIN_XX - 11; j < MAIN_XX; j++) {  //이는 main_org와 같은 숫자가 없게 하기 위함 
            main_cpy2[i][j] = 100;
        }
    }
}

void draw_map(void) { //게임 상태 표시를 나타내는 함수  
    int y = 3;             // level, goal, score만 게임중에 값이 바뀔수 도 있음 그 y값을 따로 저장해둠 
    // 그래서 혹시 게임 상태 표시 위치가 바뀌어도 그 함수에서 안바꿔도 되게.. 
    gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL = y); printf(" LEVEL : %5d", level);
    gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", 10 - cnt);
    gotoxy(STATUS_X_ADJ, y + 2); printf("+-  N E X T  -+ ");
    gotoxy(STATUS_X_ADJ, y + 3); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 4); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 5); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 6); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 7); printf("+-- -  -  - --+ ");
    gotoxy(STATUS_X_ADJ, y + 8); printf(" YOUR SCORE :");
    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE = y + 9); printf("        %6d", score);
    gotoxy(STATUS_X_ADJ, y + 10); printf(" LAST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 11); printf("        %6d", last_score);
    gotoxy(STATUS_X_ADJ, y + 12); printf(" BEST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 13); printf("        %6d", best_score);

    gotoxy(STATUS_XX_ADJ, STATUS_YY_LEVEL = y); printf(" LEVEL : %5d", level2);
    gotoxy(STATUS_XX_ADJ, STATUS_YY_GOAL = y + 1); printf(" GOAL  : %5d", 10 - cnt2);
    gotoxy(STATUS_XX_ADJ, y + 2); printf("+-  N E X T  -+ ");
    gotoxy(STATUS_XX_ADJ, y + 3); printf("|             | ");
    gotoxy(STATUS_XX_ADJ, y + 4); printf("|             | ");
    gotoxy(STATUS_XX_ADJ, y + 5); printf("|             | ");
    gotoxy(STATUS_XX_ADJ, y + 6); printf("|             | ");
    gotoxy(STATUS_XX_ADJ, y + 7); printf("+-- -  -  - --+ ");
    gotoxy(STATUS_XX_ADJ, y + 8); printf(" YOUR SCORE :");
    gotoxy(STATUS_XX_ADJ, STATUS_YY_SCORE = y + 9); printf("        %6d", score2);
    gotoxy(STATUS_XX_ADJ, y + 10); printf(" LAST SCORE :");
    gotoxy(STATUS_XX_ADJ, y + 11); printf("        %6d", last_score2);
    gotoxy(STATUS_XX_ADJ, y + 12); printf(" BEST SCORE :");
    gotoxy(STATUS_XX_ADJ, y + 13); printf("        %6d", best_score2);
}

void draw_main(void) { //게임판 그리는 함수 
    int i, j;

    for (j = 1; j < MAIN_X - 1; j++) { //천장은 계속 새로운블럭이 지나가서 지워지면 새로 그려줌 
        if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
    }
    for (i = 0; i < MAIN_Y; i++) {
        for (j = 0; j < MAIN_X; j++) {
            if (main_cpy[i][j] != main_org[i][j]) { //cpy랑 비교해서 값이 달라진 부분만 새로 그려줌.
                //이게 없으면 게임판전체를 계속 그려서 느려지고 반짝거림
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                switch (main_org[i][j]) {
                case EMPTY: //빈칸모양 
                    printf("  ");
                    break;
                case CEILLING: //천장모양 
                    printf(". ");
                    break;
                case WALL: //벽모양 
                    printf("▩");
                    break;
                case INACTIVE_BLOCK: //굳은 블럭 모양  
                    printf("□");
                    break;
                case ACTIVE_BLOCK: //움직이고있는 블럭 모양  
                    printf("■");
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAIN_Y; i++) { //게임판을 그린 후 main_cpy에 복사  
        for (j = 0; j < MAIN_X; j++) {
            main_cpy[i][j] = main_org[i][j];
        }
    }
}

void draw_main2(void) { //게임판 그리는 함수 
    int i, j;

    for (j = MAIN_XX - 10; j < MAIN_XX - 1; j++) { //천장은 계속 새로운블럭이 지나가서 지워지면 새로 그려줌 
        if (main_org2[3][j] == EMPTY) main_org2[3][j] = CEILLING;
    }
    for (i = 0; i < MAIN_YY; i++) {
        for (j = MAIN_XX - 11; j < MAIN_XX; j++) {
            if (main_cpy2[i][j] != main_org2[i][j]) { //cpy랑 비교해서 값이 달라진 부분만 새로 그려줌.
                //이게 없으면 게임판전체를 계속 그려서 느려지고 반짝거림
                gotoxy(MAIN_XX_ADJ + j, MAIN_YY_ADJ + i);
                switch (main_org2[i][j]) {
                case EMPTY: //빈칸모양 
                    printf("  ");
                    break;
                case CEILLING: //천장모양 
                    printf(". ");
                    break;
                case WALL: //벽모양 
                    printf("▩");
                    break;
                case INACTIVE_BLOCK: //굳은 블럭 모양  
                    printf("□");
                    break;
                case ACTIVE_BLOCK: //움직이고있는 블럭 모양  
                    printf("■");
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAIN_YY; i++) { //게임판을 그린 후 main_cpy에 복사  
        for (j = MAIN_XX - 11; j < MAIN_XX; j++) {
            main_cpy2[i][j] = main_org2[i][j];
        }
    }
}

void new_block(void) { //새로운 블록 생성  
    int i, j;

    bx = (MAIN_X / 2) - 1; //블록 생성 위치x좌표(게임판의 가운데) 
    by = 0;  //블록 생성위치 y좌표(제일 위) 
    b_type = b_type_next; //다음블럭값을 가져옴 
    b_type_next = rand() % 7; //다음 블럭을 만듦 
    b_rotation = 0;  //회전은 0번으로 가져옴 

    new_block_on = 0; //new_block flag를 끔  


    for (i = 0; i < 4; i++) { //게임판 bx, by위치에 블럭생성  
        for (j = 0; j < 4; j++) {
            if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
        }
    }
    for (i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("■");
            }
            else {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}

void new_block2(void) { //새로운 블록 생성
    int i, j;

    bx2 = (MAIN_XX / 2) - 6; //블록 생성 위치x좌표(게임판의 가운데)
    by2 = 0;  //블록 생성위치 y좌표(제일 위)
    b_type2 = b_type_next2; //다음블럭값을 가져옴
    b_type_next2 = rand() % 7; //다음 블럭을 만듦
    b_rotation2 = 0;  //회전은 0번으로 가져옴

    new_block_on2 = 0; //new_block flag를 끔

    for (i = 0; i < 4; i++) { //게임판 bx, by위치에 블럭생성
        for (j = 0; j < 4; j++) {
            if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = ACTIVE_BLOCK;
        }
    }
    for (i = 1; i < 3; i++) { //게임상태표시에 다음에 나올블럭을 그림
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next2][0][i][j] == 1) {
                gotoxy(STATUS_XX_ADJ + 2 + j, i + 6);
                printf("■");
            }
            else {
                gotoxy(STATUS_XX_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}


void check_key(void) {
    key = 0; //키값 초기화  
    int i;

    if (_kbhit()) { //키입력이 있는 경우  
        key = _getch(); //키값을 받음
        if (key == 224) { //방향키인경우 
            do { key = _getch(); } while (key == 224);//방향키지시값을 버림 
            switch (key) {
            case LEFT: //왼쪽키 눌렀을때  
                if (check_crush2(bx2 - 1, by2, b_rotation2) == true) move_block(LEFT);
                break;                            //왼쪽으로 갈 수 있는지 체크 후 가능하면 이동
            case RIGHT: //오른쪽 방향키 눌렀을때- 위와 동일하게 처리됨 
                if (check_crush2(bx2 + 1, by2, b_rotation2) == true) move_block(RIGHT);
                break;
            case DOWN: //아래쪽 방향키 눌렀을때-위와 동일하게 처리됨 
                if (check_crush2(bx2, by2 + 1, b_rotation2) == true) move_block(DOWN);
                break;
            case UP: //위쪽 방향키 눌렀을때 
                if (check_crush2(bx2, by2, (b_rotation2 + 1) % 4) == true) move_block(UP);
                //회전할 수 있는지 체크 후 가능하면 회전
                else if (crush_on2 == 1 && check_crush2(bx2, by2 - 1, (b_rotation2 + 1) % 4) == true) move_block(10);
                break;
            }                    //바닥에 닿은 경우 위쪽으로 한칸띄워서 회전이 가능하면 그렇게 함(특수동작)
        }
        else { //방향키가 아닌경우 
            switch (key) {
            case A: //왼쪽키 눌렀을때
                if (check_crush(bx - 1, by, b_rotation) == true) move_block(A);
                break;                            //왼쪽으로 갈 수 있는지 체크 후 가능하면 이동
            case D: //오른쪽 방향키 눌렀을때- 위와 동일하게 처리됨
                if (check_crush(bx + 1, by, b_rotation) == true) move_block(D);
                break;
            case S: //아래쪽 방향키 눌렀을때-위와 동일하게 처리됨
                if (check_crush(bx, by + 1, b_rotation) == true) move_block(S);
                break;
            case W: //위쪽 방향키 눌렀을때
                if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(W);
                //회전할 수 있는지 체크 후 가능하면 회전
                else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(20);
                //바닥에 닿은 경우 위쪽으로 한칸띄워서 회전이 가능하면 그렇게 함(특수동작)
                break;
            case G: //G키 눌렀을때
                space_key_on = 1; //스페이스키 flag를 띄움
                while (crush_on == 0) { //바닥에 닿을때까지 이동시킴
                    drop_block();
                    score += level; // hard drop 보너스
                    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score); //점수 표시
                }
                break;
            case SPACE: //스페이스키 눌렀을때 
                space_key_on2 = 1; //스페이스키 flag를 띄움 
                while (crush_on2 == 0) { //바닥에 닿을때까지 이동시킴 
                    drop_block2();
                    score2 += level2; // hard drop 보너스
                    gotoxy(STATUS_XX_ADJ, STATUS_YY_SCORE); printf("        %6d", score2); //점수 표시  
                }
                break;
            case one:
                if (delete_item > 0) {
                    for (i = 0; i < 4; i++) {
                        gotoxy(MAIN_X_ADJ + 3, MAIN_Y_ADJ + 4);
                        printf("DELETE ITEM!");
                        Sleep(200);

                        gotoxy(MAIN_X_ADJ + 3, MAIN_Y_ADJ + 4);
                        printf("            ");
                        Sleep(200);
                    }
                    reset_main_cpy(); //텍스트를 지우기 위해 main_cpy을 초기화.
                    for (i = 1; i < MAIN_X - 1; i++) {
                        main_org[MAIN_Y - 2][i] = INACTIVE_BLOCK; // 하단 1줄을 블록으로 모두 채우고 
                        Sleep(20);
                    }
                    check_line();
                    //블록으로 모두 채운 1줄 지우기
                    delete_item--; //아이템 하나 삭제
                }
                break;
            case K:
                if (delete_item2 > 0) {
                    for (i = 0; i < 4; i++) {
                        gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 7, MAIN_YY_ADJ + 4);
                        printf("DELETE ITEM!");
                        Sleep(200);

                        gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 7, MAIN_YY_ADJ + 4);
                        printf("            ");
                        Sleep(200);
                    }
                    reset_main_cpy2(); //텍스트를 지우기 위해 main_cpy을 초기화.
                    for (i = MAIN_XX - 10; i < MAIN_XX - 1; i++) {
                        main_org2[MAIN_YY - 2][i] = INACTIVE_BLOCK; // 하단 1줄을 블록으로 모두 채우고 
                        Sleep(20);
                    }
                    check_line2();
                    //블록으로 모두 채운 1줄 지우기
                    delete_item2--;
                }
                break;
            case P: //P(대문자) 눌렀을때 
            case p: //p(소문자) 눌렀을때
                pause(); //일시정지
                break;
            case ESC: //ESC눌렀을때 
                system("cls"); //화면을 지우고 
                exit(0); //게임종료 
            }
        }
    }
    while (_kbhit()) _getch(); //키버퍼를 비움 
}

/*
void check_key2(void) {
    key2 = 0; //키값 초기화

    if (_kbhit()) { //키입력이 있는 경우
        key2 = _getch(); //키값을 받음
        switch (key2) {
        case A: //왼쪽키 눌렀을때
            if (check_crush2(bx2 - 1, by2, b_rotation2) == true) move_block2(A);
            break;                            //왼쪽으로 갈 수 있는지 체크 후 가능하면 이동
        case D: //오른쪽 방향키 눌렀을때- 위와 동일하게 처리됨
            if (check_crush2(bx2 + 1, by2, b_rotation2) == true) move_block2(D);
            break;
        case S: //아래쪽 방향키 눌렀을때-위와 동일하게 처리됨
            if (check_crush2(bx2, by2 + 1, b_rotation2) == true) move_block2(S);
            break;
        case W: //위쪽 방향키 눌렀을때
            if (check_crush2(bx2, by2, (b_rotation2 + 1) % 4) == true) move_block2(W);
            //회전할 수 있는지 체크 후 가능하면 회전
            else if (crush_on2 == 1 && check_crush2(bx2, by2 - 1, (b_rotation2 + 1) % 4) == true) move_block2(200);
            //바닥에 닿은 경우 위쪽으로 한칸띄워서 회전이 가능하면 그렇게 함(특수동작)
        case G: //G키 눌렀을때
            space_key_on2 = 1; //스페이스키 flag를 띄움
            while (crush_on2 == 0) { //바닥에 닿을때까지 이동시킴
                drop_block2();
                score2 += level2; // hard drop 보너스
                gotoxy(STATUS_XX_ADJ, STATUS_YY_SCORE); printf("        %6d", score2); //점수 표시
            }
            break;
        case P: //P(대문자) 눌렀을때
        case p: //p(소문자) 눌렀을때
            pause(); //일시정지
            break;
        case ESC: //ESC눌렀을때
            system("cls"); //화면을 지우고
            exit(0); //게임종료
        }
    }
    while (_kbhit()) _getch(); //키버퍼를 비움
}
*/

void drop_block(void) {
    int i, j;

    if (crush_on && check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //밑이 비어있으면 crush flag 끔
    if (crush_on && check_crush(bx, by + 1, b_rotation) == false) { //밑이 비어있지않고 crush flag가 켜저있으면 
        for (i = 0; i < MAIN_Y; i++) { //현재 조작중인 블럭을 굳힘 
            for (j = 0; j < MAIN_X; j++) {
                if (main_org[i][j] == ACTIVE_BLOCK) main_org[i][j] = INACTIVE_BLOCK;
            }
        }
        crush_on = 0; //flag를 끔 
        check_line(); //라인체크를 함 
        new_block_on = 1; //새로운 블럭생성 flag를 켬    
        return; //함수 종료 
    }
    if (check_crush(bx, by + 1, b_rotation) == true) move_block(S); //밑이 비어있으면 밑으로 한칸 이동 
    if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; //밑으로 이동이 안되면  crush flag를 켬
}

void drop_block2(void) {
    int i, j;

    if (crush_on2 && check_crush2(bx2, by2 + 1, b_rotation2) == true) crush_on2 = 0; //밑이 비어있으면 crush flag 끔
    if (crush_on2 && check_crush2(bx2, by2 + 1, b_rotation2) == false) { //밑이 비어있지않고 crush flag가 켜저있으면
        for (i = 0; i < MAIN_YY; i++) { //현재 조작중인 블럭을 굳힘
            for (j = MAIN_XX - 11; j < MAIN_XX; j++) {
                if (main_org2[i][j] == ACTIVE_BLOCK) main_org2[i][j] = INACTIVE_BLOCK;
            }
        }
        crush_on2 = 0; //flag를 끔
        check_line2(); //라인체크를 함
        new_block_on2 = 1; //새로운 블럭생성 flag를 켬
        return; //함수 종료
    }
    if (check_crush2(bx2, by2 + 1, b_rotation2) == true) move_block(DOWN); //밑이 비어있으면 밑으로 한칸 이동
    if (check_crush2(bx2, by2 + 1, b_rotation2) == false) crush_on2++; //밑으로 이동이 안되면  crush flag를 켬
}


int check_crush(int bx, int by, int b_rotation) { //지정된 좌표와 회전값으로 충돌이 있는지 검사 
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { //지정된 위치의 게임판과 블럭모양을 비교해서 겹치면 false를 리턴 
            if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
        }
    }
    return true; //하나도 안겹치면 true리턴 
};


int check_crush2(int bx2, int by2, int b_rotation2) { //지정된 좌표와 회전값으로 충돌이 있는지 검사 
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { //지정된 위치의 게임판과 블럭모양을 비교해서 겹치면 false를 리턴 
            if (blocks[b_type2][b_rotation2][i][j] == 1 && main_org2[by2 + i][bx2 + j] > 0) return false;
        }
    }
    return true; //하나도 안겹치면 true리턴 
};



void move_block(int dir) { //블록을 이동시킴 
    int i, j;

    switch (dir) {
    case LEFT: //왼쪽방향 
        for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //왼쪽으로 한칸가서 active block을 찍음 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx2--; //좌표값 이동 
        break;

    case RIGHT:    //오른쪽 방향. 왼쪽방향이랑 같은 원리로 동작 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j + 1] = ACTIVE_BLOCK;
            }
        }
        bx2++;
        break;

    case DOWN:    //아래쪽 방향. 왼쪽방향이랑 같은 원리로 동작
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i + 1][bx2 + j] = ACTIVE_BLOCK;
            }
        }
        by2++;
        break;

    case UP: //키보드 위쪽 눌렀을때 회전시킴. 
        for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움  
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        b_rotation2 = (b_rotation2 + 1) % 4; //회전값을 1증가시킴(3에서 4가 되는 경우는 0으로 되돌림) 
        for (i = 0; i < 4; i++) { //회전된 블록을 찍음 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 10: //블록이 바닥, 혹은 다른 블록과 닿은 상태에서 한칸위로 올려 회전이 가능한 경우 
        //이를 동작시키는 특수동작 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        b_rotation2 = (b_rotation2 + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i - 1][bx2 + j] = ACTIVE_BLOCK;
            }
        }
        by2--;
        break;

    case A: //왼쪽방향 
        for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //왼쪽으로 한칸가서 active block을 찍음 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx--; //좌표값 이동 
        break;

    case D:    //오른쪽 방향. 왼쪽방향이랑 같은 원리로 동작 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j + 1] = ACTIVE_BLOCK;
            }
        }
        bx++;
        break;

    case S:    //아래쪽 방향. 왼쪽방향이랑 같은 원리로 동작
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i + 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by++;
        break;

    case W: //키보드 위쪽 눌렀을때 회전시킴. 
        for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움  
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4; //회전값을 1증가시킴(3에서 4가 되는 경우는 0으로 되돌림) 
        for (i = 0; i < 4; i++) { //회전된 블록을 찍음 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 20: //블록이 바닥, 혹은 다른 블록과 닿은 상태에서 한칸위로 올려 회전이 가능한 경우 
        //이를 동작시키는 특수동작 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i - 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by--;
        break;
    }
}

/*
void move_block2(int dir) { //블록을 이동시킴
    int i, j;

    switch (dir) {
    case A: //왼쪽방향
        for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //왼쪽으로 한칸가서 active block을 찍음
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx2--; //좌표값 이동
        break;

    case D:    //오른쪽 방향. 왼쪽방향이랑 같은 원리로 동작
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j + 1] = ACTIVE_BLOCK;
            }
        }
        bx2++;
        break;

    case S:    //아래쪽 방향. 왼쪽방향이랑 같은 원리로 동작
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i + 1][bx2 + j] = ACTIVE_BLOCK;
            }
        }
        by2++;
        break;

    case W: //키보드 위쪽 눌렀을때 회전시킴.
        for (i = 0; i < 4; i++) { //현재좌표의 블럭을 지움
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        b_rotation2 = (b_rotation2 + 1) % 4; //회전값을 1증가시킴(3에서 4가 되는 경우는 0으로 되돌림)
        for (i = 0; i < 4; i++) { //회전된 블록을 찍음
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 200: //블록이 바닥, 혹은 다른 블록과 닿은 상태에서 한칸위로 올려 회전이 가능한 경우
        //이를 동작시키는 특수동작
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i - 1][bx2 + j] = ACTIVE_BLOCK;
            }
        }
        by2--;
        break;
    }
}
*/

void check_line(void) {
    int i, j, k, l;

    int block_amount; //한줄의 블록갯수를 저장하는 변수 
    int combo = 0; //콤보갯수 저장하는 변수 지정및 초기화 

    for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : 밑쪽벽의 윗칸부터,  i>3 : 천장(3)아래까지 검사 
        block_amount = 0; //블록갯수 저장 변수 초기화 
        for (j = 1; j < MAIN_X - 1; j++) { //벽과 벽사이의 블록갯루를 셈 
            if (main_org[i][j] > 0) block_amount++;
        }
        if (block_amount == MAIN_X - 2) { //블록이 가득 찬 경우 
            if (level_up_on == 0) { //레벨업상태가 아닌 경우에(레벨업이 되면 자동 줄삭제가 있음) 
                score += 100 * level; //점수추가 
                cnt++; //지운 줄 갯수 카운트 증가 
                combo++; //콤보수 증가  
            }
            for (k = i; k > 1; k--) { //윗줄을 한칸씩 모두 내림(윗줄이 천장이 아닌 경우에만) 
                for (l = 1; l < MAIN_X - 1; l++) {
                    if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
                    if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;
                    //윗줄이 천장인 경우에는 천장을 한칸 내리면 안되니까 빈칸을 넣음 
                }
            }
        }
        else i--;
    }
    if (combo) { //줄 삭제가 있는 경우 점수와 레벨 목표를 새로 표시함  
        if (combo > 1) { //2콤보이상인 경우 경우 보너스및 메세지를 게임판에 띄웠다가 지움 
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 4); printf("%d COMBO!", combo);
            Sleep(500);
            score += (combo * level * 100);
            reset_main_cpy(); //텍스트를 지우기 위해 main_cpy을 초기화.
            //(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 
        }
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= 10) ? 10 - cnt : 0);
        gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
    }
}
void check_line2(void) {
    int i, j, k, l;

    int block_amount; //한줄의 블록갯수를 저장하는 변수 
    int combo = 0; //콤보갯수 저장하는 변수 지정및 초기화 

    for (i = MAIN_YY - 2; i > 3;) { //i=MAIN_YY-2 : 밑쪽벽의 윗칸부터,  i>3 : 천장(3)아래까지 검사 
        block_amount = 0; //블록갯수 저장 변수 초기화 
        for (j = MAIN_XX - 10; j < MAIN_XX - 1; j++) { //벽과 벽사이의 블록갯루를 셈 
            if (main_org2[i][j] > 0) block_amount++;
        }
        if (block_amount == MAIN_X - 2) { //블록이 가득 찬 경우 
            if (level_up_on2 == 0) { //레벨업상태가 아닌 경우에(레벨업이 되면 자동 줄삭제가 있음) 
                score2 += 100 * level2; //점수추가 
                cnt2++; //지운 줄 갯수 카운트 증가 
                combo++; //콤보수 증가  
            }
            for (k = i; k > 1; k--) { //윗줄을 한칸씩 모두 내림(윗줄이 천장이 아닌 경우에만) 
                for (l = MAIN_XX - 10; l < MAIN_XX - 1; l++) {
                    if (main_org2[k - 1][l] != CEILLING) main_org2[k][l] = main_org2[k - 1][l];
                    if (main_org2[k - 1][l] == CEILLING) main_org2[k][l] = EMPTY;
                    //윗줄이 천장인 경우에는 천장을 한칸 내리면 안되니까 빈칸을 넣음 
                }
            }
        }
        else i--;
    }
    if (combo) { //줄 삭제가 있는 경우 점수와 레벨 목표를 새로 표시함  
        if (combo > 1) { //2콤보이상인 경우 경우 보너스및 메세지를 게임판에 띄웠다가 지움 
            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 7, MAIN_YY_ADJ + 4); printf("%d COMBO!", combo);
            Sleep(500);
            score2 += (combo * level2 * 100);
            reset_main_cpy2(); //텍스트를 지우기 위해 main_cpy을 초기화.
            //(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 
        }
        gotoxy(STATUS_XX_ADJ, STATUS_YY_GOAL); printf(" GOAL  : %5d", (cnt2 <= 10) ? 10 - cnt2 : 0);
        gotoxy(STATUS_XX_ADJ, STATUS_YY_SCORE); printf("        %6d", score2);
    }
}

void check_level_up(void) {
    int i, j;

    if (cnt >= 10) { //레벨별로 10줄씩 없애야함. 10줄이상 없앤 경우 
        draw_main();
        level_up_on = 1; //레벨업 flag를 띄움 
        level += 1; //레벨을 1 올림 
        cnt = 0; //지운 줄수 초기화   

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("☆LEVEL UP!☆");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 6);
            printf("☆SPEED UP!☆");
            Sleep(200);

            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 6);
            printf("             ");
            Sleep(200);
        }
        reset_main_cpy(); //텍스트를 지우기 위해 main_cpy을 초기화.
        //(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 

        for (i = MAIN_Y - 2; i > MAIN_Y - 2 - (level - 1); i--) { //레벨업보상으로 각 레벨-1의 수만큼 아랫쪽 줄을 지워줌 
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[i][j] = INACTIVE_BLOCK; // 줄을 블록으로 모두 채우고 
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); // 별을 찍어줌.. 이뻐보이게 
                printf("★");
                Sleep(20);
            }
        }
        Sleep(100); //별찍은거 보여주기 위해 delay 
        check_line(); //블록으로 모두 채운것 지우기
        //.check_line()함수 내부에서 level up flag가 켜져있는 경우 점수는 없음.         
        switch (level) { //레벨별로 속도를 조절해줌. 
        case 2:
            speed = 50;
            break;
        case 3:
            speed = 25;
            break;
        case 4:
            speed = 10;
            break;
        case 5:
            speed = 5;
            break;
        case 6:
            speed = 4;
            break;
        case 7:
            speed = 3;
            break;
        case 8:
            speed = 2;
            break;
        case 9:
            speed = 1;
            break;
        case 10:
            speed = 0;
            break;
        }
        level_up_on = 0; //레벨업 flag꺼줌

        gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //레벨표시 
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - cnt); // 레벨목표 표시 

    }
}
void check_level_up2(void) {
    int i, j;

    if (cnt2 >= 10) { //레벨별로 10줄씩 없애야함. 10줄이상 없앤 경우 
        draw_main2();
        level_up_on2 = 1; //레벨업 flag를 띄움 
        level2 += 1; //레벨을 1 올림 
        cnt2 = 0; //지운 줄수 초기화   

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 8, MAIN_YY_ADJ + 4);
            printf("☆LEVEL UP!☆");
            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 8, MAIN_YY_ADJ + 6);
            printf("☆SPEED UP!☆");
            Sleep(200);

            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 8, MAIN_YY_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 8, MAIN_YY_ADJ + 6);
            printf("             ");
            Sleep(200);
        }
        reset_main_cpy2(); //텍스트를 지우기 위해 main_cpy을 초기화.
        //(main_cpy와 main_org가 전부 다르므로 다음번 draw()호출시 게임판 전체를 새로 그리게 됨) 

        for (i = MAIN_YY - 2; i > MAIN_YY - 2 - (level2 - 1); i--) { //레벨업보상으로 각 레벨-1의 수만큼 아랫쪽 줄을 지워줌 
            for (j = MAIN_XX - 10; j < MAIN_XX - 1; j++) {
                main_org2[i][j] = INACTIVE_BLOCK; // 줄을 블록으로 모두 채우고 
                gotoxy(MAIN_XX_ADJ + j, MAIN_YY_ADJ + i); // 별을 찍어줌.. 이뻐보이게 
                printf("★");
                Sleep(20);
            }
        }
        Sleep(100); //별찍은거 보여주기 위해 delay 
        check_line2(); //블록으로 모두 채운것 지우기
        //.check_line()함수 내부에서 level up flag가 켜져있는 경우 점수는 없음.         
        switch (level2) { //레벨별로 속도를 조절해줌. 
        case 2:
            speed2 = 50;
            break;
        case 3:
            speed2 = 25;
            break;
        case 4:
            speed2 = 10;
            break;
        case 5:
            speed2 = 5;
            break;
        case 6:
            speed2 = 4;
            break;
        case 7:
            speed2 = 3;
            break;
        case 8:
            speed2 = 2;
            break;
        case 9:
            speed2 = 1;
            break;
        case 10:
            speed2 = 0;
            break;
        }
        level_up_on2 = 0; //레벨업 flag꺼줌

        gotoxy(STATUS_XX_ADJ, STATUS_YY_LEVEL); printf(" LEVEL : %5d", level2); //레벨표시 
        gotoxy(STATUS_XX_ADJ, STATUS_YY_GOAL); printf(" GOAL  : %5d", 10 - cnt2); // 레벨목표 표시 

    }
}

void check_game_over(void) {
    int i;

    int x = 5;
    int y = 8;

    for (i = 1; i < MAIN_X - 2; i++) {
        if (main_org[3][i] > 0) { //천장(위에서 세번째 줄)에 inactive가 생성되면 게임 오버
            new_block_on = -1; //더이상 새로운 블럭생성x, 게임중단
            game_over = 1;

            gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤"); //게임오버 메세지 
            gotoxy(x, y + 1); printf("▤                              ▤");
            gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 3); printf("▤  | 1 P  G A M E  O V E R |   ▤");
            gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 5); printf("▤  YOUR SCORE: %6d          ▤", score);
            gotoxy(x, y + 6); printf("▤                              ▤");
            gotoxy(x, y + 7); printf("▤  Please wait for 2P..        ▤");
            gotoxy(x, y + 8); printf("▤                              ▤");
            gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");

            last_score = score; //게임점수를 옮김 

            if (score > best_score) { //최고기록 갱신시 
                FILE* file = fopen("score.dat", "wt"); //score.dat에 점수 저장                

                gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");

                if (file == 0) { //파일 에러메세지  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
                }
                else {
                    fprintf(file, "%d", score);
                    fclose(file);
                }
            }
        }
    }
}

void check_game_over2(void) {
    int i;

    int x = 27;
    int y = 8;

    for (i = MAIN_XX - 10; i < MAIN_XX - 2; i++) {
        if (main_org2[3][i] > 0) { //천장(위에서 세번째 줄)에 inactive가 생성되면 게임 오버 
            new_block_on2 = -1; //더이상 새로운 블럭생성x, 게임중단
            game_over2 = 1;

            gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤"); //게임오버 메세지 
            gotoxy(x, y + 1); printf("▤                              ▤");
            gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 3); printf("▤  | 2 P  G A M E  O V E R |   ▤");
            gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
            gotoxy(x, y + 5); printf("▤  YOUR SCORE: %6d          ▤", score2);
            gotoxy(x, y + 6); printf("▤                              ▤");
            gotoxy(x, y + 7); printf("▤  Please wait for 1P..        ▤");
            gotoxy(x, y + 8); printf("▤                              ▤");
            gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");

            last_score2 = score2; //게임점수를 옮김 

            if (score2 > best_score2) { //최고기록 갱신시 
                FILE* file2 = fopen("score2.dat", "wt"); //score.dat에 점수 저장                

                gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");

                if (file2 == 0) { //파일 에러메세지  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE2.DAT\"");
                }
                else {
                    fprintf(file2, "%d", score2);
                    fclose(file2);
                }
            }
        }
    }
}


void check_winner(void) {
    int x = 5;
    int y = 8;

    if (score > score2) { //1p점수가 높으면
        gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤"); //승자표시 메세지
        gotoxy(x, y + 1); printf("▤                              ▤");
        gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 3); printf("▤  |★ W I N N E R : 1 P ★|   ▤");
        gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 5); printf("▤  YOUR SCORE: %6d          ▤", score);
        gotoxy(x, y + 6); printf("▤                              ▤");
        gotoxy(x, y + 7); printf("▤  Press any key to restart..  ▤");
        gotoxy(x, y + 8); printf("▤                              ▤");
        gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
        last_score = score; //게임점수를 옮김

        if (score > best_score) { //최고기록 갱신시
            FILE* file = fopen("score.dat", "wt"); //score.dat에 점수 저장

            gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");

            if (file == 0) { //파일 에러메세지
                gotoxy(0, 0);
                printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
            }
            else {
                fprintf(file, "%d", score);
                fclose(file);
            }
        }
        Sleep(1000);
        while (_kbhit()) _getch();
        key = _getch();
        reset();
    }

    if (score2 > score) { //2p점수가 높으면
        gotoxy(x + 22, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤"); //승자표시 메세지
        gotoxy(x + 22, y + 1); printf("▤                              ▤");
        gotoxy(x + 22, y + 2); printf("▤  +-----------------------+   ▤");
        gotoxy(x + 22, y + 3); printf("▤  |★ W I N N E R : 2 P ★|   ▤");
        gotoxy(x + 22, y + 4); printf("▤  +-----------------------+   ▤");
        gotoxy(x + 22, y + 5); printf("▤  YOUR SCORE: %6d          ▤", score2);
        gotoxy(x + 22, y + 6); printf("▤                              ▤");
        gotoxy(x + 22, y + 7); printf("▤  Press any key to restart..  ▤");
        gotoxy(x + 22, y + 8); printf("▤                              ▤");
        gotoxy(x + 22, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
        last_score2 = score2; //게임점수를 옮김

        if (score2 > best_score2) { //최고기록 갱신시
            FILE* file2 = fopen("score2.dat", "wt"); //score2.dat에 점수 저장

            gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");

            if (file2 == 0) { //파일 에러메세지
                gotoxy(0, 0);
                printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE2.DAT\"");
            }
            else {
                fprintf(file2, "%d", score2);
                fclose(file2);
            }
        }
        Sleep(1000);
        while (_kbhit()) _getch();
        key = _getch();
        reset();
    }

    if ((game_over == 1) && (game_over2 == 1) && (score == score2)) { //점수가 같으면
        gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤"); //승자표시 메세지
        gotoxy(x, y + 1); printf("▤                              ▤");
        gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 3); printf("▤  |      ★ T I E ★      |   ▤");
        gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 5); printf("▤  YOUR SCORE: %6d          ▤", score);
        gotoxy(x, y + 6); printf("▤                              ▤");
        gotoxy(x, y + 7); printf("▤  Press any key to restart..  ▤");
        gotoxy(x, y + 8); printf("▤                              ▤");
        gotoxy(x, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
        last_score = score; //게임점수를 옮김
        if (score > best_score) { //최고기록 갱신시
            FILE* file = fopen("score.dat", "wt"); //score.dat에 점수 저장

            gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");

            if (file == 0) { //파일 에러메세지
                gotoxy(0, 0);
                printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
            }
            else {
                fprintf(file, "%d", score);
                fclose(file);
            }
        }

        gotoxy(x + 22, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤"); //승자표시 메세지
        gotoxy(x + 22, y + 1); printf("▤                              ▤");
        gotoxy(x + 22, y + 2); printf("▤  +-----------------------+   ▤");
        gotoxy(x + 22, y + 3); printf("▤  |      ★ T I E ★      |   ▤");
        gotoxy(x + 22, y + 4); printf("▤  +-----------------------+   ▤");
        gotoxy(x + 22, y + 5); printf("▤  YOUR SCORE: %6d          ▤", score2);
        gotoxy(x + 22, y + 6); printf("▤                              ▤");
        gotoxy(x + 22, y + 7); printf("▤  Press any key to restart..  ▤");
        gotoxy(x + 22, y + 8); printf("▤                              ▤");
        gotoxy(x + 22, y + 9); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
        last_score2 = score2; //게임점수를 옮김
        if (score2 > best_score2) { //최고기록 갱신시
            FILE* file2 = fopen("score2.dat", "wt"); //score2.dat에 점수 저장

            gotoxy(x, y + 6); printf("▤  ★★★ BEST SCORE! ★★★   ▤  ");

            if (file2 == 0) { //파일 에러메세지
                gotoxy(0, 0);
                printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE2.DAT\"");
            }
            else {
                fprintf(file2, "%d", score2);
                fclose(file2);
            }
        }

        Sleep(1000);
        while (_kbhit()) _getch();
        key = _getch();
        reset();
    }
}

void pause(void) { //게임 일시정지 함수 
    int i, j;

    int x = 16;
    int y = 9;

    for (i = 1; i < MAIN_X - 2; i++) { //게임 일시정지 메세지 
        gotoxy(x, y + 0); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
        gotoxy(x, y + 1); printf("▤                              ▤");
        gotoxy(x, y + 2); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 3); printf("▤  |       P A U S E       |   ▤");
        gotoxy(x, y + 4); printf("▤  +-----------------------+   ▤");
        gotoxy(x, y + 5); printf("▤  Press any key to resume..   ▤");
        gotoxy(x, y + 6); printf("▤                              ▤");
        gotoxy(x, y + 7); printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
    }
    _getch(); //키입력시까지 대기 

    system("cls"); //화면 지우고 새로 그림 
    reset_main_cpy();
    reset_main_cpy2();
    draw_main();
    draw_main2();
    draw_map();

    for (i = 1; i < 3; i++) { // 다음블록 그림 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(MAIN_X + MAIN_X_ADJ + 4 + j, i + 6);
                printf("■");
            }
            else {
                gotoxy(MAIN_X + MAIN_X_ADJ + 4 + j, i + 6);
                printf("  ");
            }
        }
    }
    for (i = 1; i < 3; i++) { // 다음블록 그림 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next2][0][i][j] == 1) {
                gotoxy(STATUS_XX_ADJ + 2 + j, i + 6);
                printf("■");
            }
            else {
                gotoxy(STATUS_XX_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
} //끝!