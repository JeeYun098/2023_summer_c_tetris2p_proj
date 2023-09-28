#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define LEFT 75 //�·� �̵�    //Ű���尪�� 
#define RIGHT 77 //��� �̵� 
#define UP 72 //ȸ�� 
#define DOWN 80 //soft drop

#define A 97 //�·� �̵�    //Ű���尪�� 
#define D 100 //��� �̵� 
#define W 119 //ȸ�� 
#define S 115 //soft drop

#define SPACE 32 //hard drop
#define G 103 //hard drop

#define one 49 //delete_item
//#define two 50 //slow_item

#define K 107 //delete_item
//#define L 108 //slow_item

#define p 112 //�Ͻ����� 
#define P 80 //�Ͻ�����
#define ESC 27 //�������� 

#define false 0
#define true 1

#define ACTIVE_BLOCK -2 // �����ǹ迭�� ����� ����� ���µ� 
#define CEILLING -1     // ����� �̵��� �� �ִ� ������ 0 �Ǵ� ���� ������ ǥ�� 
#define EMPTY 0         // ����� �̵��� �� ���� ������ ����� ǥ�� 
#define WALL 1
#define INACTIVE_BLOCK 2 // �̵��� �Ϸ�� ��ϰ� 

#define MAIN_X 11 //������ ����ũ�� 
#define MAIN_Y 23 //������ ����ũ�� 
#define MAIN_X_ADJ 3 //������ ��ġ���� 
#define MAIN_Y_ADJ 1 //������ ��ġ���� 

#define STATUS_X_ADJ MAIN_X_ADJ+MAIN_X+2 //��������ǥ�� ��ġ���� 
#define STATUS_XX_ADJ STATUS_X_ADJ+9 //��������ǥ�� ��ġ���� 

#define MAIN_XX STATUS_XX_ADJ+2 //������ ����ũ�� 
#define MAIN_YY 23 //������ ����ũ�� 
#define MAIN_XX_ADJ MAIN_XX-8 //������ ��ġ���� 
#define MAIN_YY_ADJ 1 //������ ��ġ���� 



int STATUS_Y_GOAL; //GOAL ����ǥ����ġY ��ǥ ���� 
int STATUS_Y_LEVEL; //LEVEL ����ǥ����ġY ��ǥ ����
int STATUS_Y_SCORE; //SCORE ����ǥ����ġY ��ǥ ����

int STATUS_YY_GOAL; //GOAL ����ǥ����ġY ��ǥ ���� 
int STATUS_YY_LEVEL; //LEVEL ����ǥ����ġY ��ǥ ����
int STATUS_YY_SCORE; //SCORE ����ǥ����ġY ��ǥ ����

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
}; //��ϸ�� ���� 4*4������ ����� ǥ�� blcoks[b_type][b_rotation][i][j]�� ��� 

int b_type; //��� ������ ���� 
int b_rotation; //��� ȸ���� ���� 
int b_type_next; //���� ��ϰ� ���� 

int b_type2; //��� ������ ���� 
int b_rotation2; //��� ȸ���� ���� 
int b_type_next2; //���� ��ϰ� ���� 

int main_org[MAIN_Y][MAIN_X]; //�������� ������ �����ϴ� �迭 ����Ϳ� ǥ���Ŀ� main_cpy�� ����� 
int main_cpy[MAIN_Y][MAIN_X]; //�� maincpy�� �������� ����Ϳ� ǥ�õǱ� ���� ������ ������ ���� 
//main�� ��ü�� ��� ����Ϳ� ǥ������ �ʰ�(�̷��� �ϸ� ����Ͱ� �����Ÿ�) 
//main_cpy�� �迭�� ���ؼ� ���� �޶��� ���� ����Ϳ� ��ħ 

int main_org2[MAIN_YY][MAIN_XX];
int main_cpy2[MAIN_YY][MAIN_XX];

int key; //Ű����� �Է¹��� Ű���� ���� 

int bx, by; //�̵����� ����� �����ǻ��� x,y��ǥ�� ����

int speed; //��������ӵ� 
int level; //���� level 
int level_goal; //���������� �Ѿ�� ���� ��ǥ���� 
int cnt; //���� �������� ������ �� ���� ���� 
int score; //���� ���� 
int last_score = 0; //�������������� 
int best_score = 0; //�ְ�������� 
int game_over = 0; //���ӿ�������


int bx2, by2; //�̵����� ����� �����ǻ��� x,y��ǥ�� ���� 

int speed2; //��������ӵ� 
int level2; //���� level 
int level_goal2; //���������� �Ѿ�� ���� ��ǥ���� 
int cnt2; //���� �������� ������ �� ���� ���� 
int score2; //���� ���� 
int last_score2 = 0; //�������������� 
int best_score2 = 0; //�ְ�������� 
int game_over2 = 0; //���ӿ�������


int new_block_on = 0; //���ο� ���� �ʿ����� �˸��� flag 
int crush_on = 0; //���� �̵����� ����� �浹�������� �˷��ִ� flag 
int level_up_on = 0; //���������� ����(���� ������ǥ�� �Ϸ�Ǿ�����) �˸��� flag 
int space_key_on = 0; //hard drop�������� �˷��ִ� flag 

int new_block_on2 = 0; //���ο� ���� �ʿ����� �˸��� flag 
int crush_on2 = 0; //���� �̵����� ����� �浹�������� �˷��ִ� flag 
int level_up_on2 = 0; //���������� ����(���� ������ǥ�� �Ϸ�Ǿ�����) �˸��� flag 
int space_key_on2 = 0; //hard drop�������� �˷��ִ� flag 

int delete_item = 0;
//int slow_item = 0;
int drop = 0;

int delete_item2 = 0;
//int slow_item2 = 0;
int drop2 = 0;


void title(void); //���ӽ���ȭ�� 
void reset(void); //������ �ʱ�ȭ 
void reset_main(void); //���� ������(main_org[][]�� �ʱ�ȭ)
void reset_main_cpy(void); //copy ������(main_cpy[][]�� �ʱ�ȭ)
void reset_main_cpy2(void); //copy ������(main_cpy2[][]�� �ʱ�ȭ)
void draw_map(void); //���� ��ü �������̽��� ǥ�� 
void draw_main(void); //�������� �׸� 
void draw_main2(void); //�������� �׸� 
void new_block(void); //���ο� ����� �ϳ� ���� 
void check_key(void); //Ű����� Ű�� �Է¹��� 
void drop_block(void); //����� �Ʒ��� ����Ʈ�� 
int check_crush(int bx, int by, int rotation); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ� 
void move_block(int dir); //dir�������� ����� ������ 
void check_line(void); //���� ����á������ �Ǵ��ϰ� ���� 
void check_level_up(void); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 

void new_block2(void); //���ο� ����� �ϳ� ���� 
void drop_block2(void); //����� �Ʒ��� ����Ʈ��
int check_crush2(int bx2, int by2, int rotation2); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ� 
void check_line2(void); //���� ����á������ �Ǵ��ϰ� ���� 
void check_level_up2(void); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 


void check_game_over(void); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void check_game_over2(void); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void check_winner(void); //����ǥ���ϰ� ���� ����� 
void pause(void);//������ �Ͻ�������Ŵ 

void gotoxy(int x, int y) { //gotoxy�Լ� 
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //Ŀ������� �Լ��� ���Ǵ� ������ 
void setcursortype(CURSOR_TYPE c) { //Ŀ������� �Լ� 
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

    srand((unsigned)time(NULL)); //����ǥ���� 
    setcursortype(NOCURSOR); //Ŀ�� ���� 
    title(); //����Ÿ��Ʋ ȣ�� 
    reset(); //������ ���� 

    while (1) {
        for (i = 0; i < 5; i++) { //����� ��ĭ�������µ��� 5�� Ű�Է¹��� �� ���� 
            check_key(); //Ű�Է�Ȯ�� 
            draw_main(); //ȭ���� �׸� 
            draw_main2(); //ȭ���� �׸� 
            Sleep(speed); //���Ӽӵ����� 
            Sleep(speed2); //���Ӽӵ����� 
            if (crush_on && check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
            if (crush_on2 && check_crush2(bx2, by2 + 1, b_rotation2) == false) Sleep(100);
            //����� �浹���ΰ�� �߰��� �̵��� ȸ���� �ð��� ���� 
            if (space_key_on == 1) { //�����̽��ٸ� �������(hard drop) �߰��� �̵��� ȸ���Ҽ� ���� break; 
                space_key_on = 0;
                break;
            }
            if (space_key_on2 == 1) { //G�� �������(hard drop) �߰��� �̵��� ȸ���Ҽ� ���� break; 
                space_key_on2 = 0;
                break;
            }
        }
        drop_block(); // ����� ��ĭ ���� 
        drop_block2();

        check_level_up(); // �������� üũ
        check_level_up2();

        check_game_over(); //1p ���ӿ����� üũ
        check_game_over2(); //2p ���ӿ����� üũ

        if ((game_over == 1) && (game_over2 == 1)) check_winner(); //�Ѵٰ��ӿ����Ǹ� ���ڸ� üũ 

        if (new_block_on == 1) {
            drop++; //��� ������������ drop����
            if (drop % 10 == 0) {
                delete_item++; //10�� �������� delete_item����
            }
            new_block(); // �� �� flag�� �ִ� ��� ���ο� �� ����
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
    int x = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
    int y = 4; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
    int cnt; //Ÿ��Ʋ �������� ���� ����  

    gotoxy(x + 10, y + 0); printf("����������������"); Sleep(100);
    gotoxy(x + 10, y + 1); printf("�����  ����    ������"); Sleep(100);
    gotoxy(x + 10, y + 2); printf("�����              ���  ��"); Sleep(100);
    gotoxy(x + 10, y + 3); printf("������  ��  ��  ������"); Sleep(100);
    gotoxy(x + 10, y + 4); printf("���  �������������"); Sleep(100);
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
    gotoxy(x + 20, y + 10); printf("  ��   : Shift");
    gotoxy(x + 20, y + 11); printf("��  �� : Left / Right");
    gotoxy(x + 20, y + 12); printf("  ��   : Soft Drop");
    gotoxy(x + 20, y + 13); printf(" SPACE : Hard Drop");
    gotoxy(x + 20, y + 14); printf("   K   : Delete Item");
    gotoxy(x + 20, y + 15); printf("   P   : Pause");
    gotoxy(x + 20, y + 17); printf("  ESC  : Quit");
    gotoxy(x + 20, y + 18); printf("BONUS FOR HARD DROPS / COMBOS");

    for (cnt = 0;; cnt++) { //cnt�� 1�� ������Ű�鼭 ��� �ݺ�    //�ϳ��� ���߿��� �� ��¦�̴� �ִϸ��̼�ȿ�� 
        if (_kbhit()) break; //Ű�Է��� ������ ���ѷ��� ���� 
        if (cnt % 200 == 0) { gotoxy(x + 10 + 4, y + 1); printf("��"); }       //cnt�� 200���� ������ �������� ���� ǥ�� 
        if ((cnt % 200 - 100) == 0) { gotoxy(x + 10 + 4, y + 1); printf("  "); } //�� ī��Ʈ���� 100ī��Ʈ �������� ���� ���� 
        if ((cnt % 350) == 0) { gotoxy(x + 10 + 13, y + 2); printf("��"); } //������ ������ �ð����� ���� 
        if ((cnt % 350 - 100) == 0) { gotoxy(x + 10 + 13, y + 2); printf("  "); }
        Sleep(10); // 00.1�� ������  
    }

    while (_kbhit()) _getch(); //���ۿ� ��ϵ� Ű���� ���� 

}

void reset(void) {

    FILE* file = fopen("score.dat", "rt"); // score.dat������ ���� 
    if (file == 0) { best_score = 0; } //������ ������ �� �ְ������� 0�� ���� 
    else {
        fscanf(file, "%d", &best_score); // ������ ������ �ְ������� �ҷ��� 
        fclose(file); //���� ���� 
    }

    FILE* file2 = fopen("score2.dat", "rt"); // score.dat������ ���� 
    if (file2 == 0) { best_score2 = 0; } //������ ������ �� �ְ������� 0�� ���� 
    else {
        fscanf(file2, "%d", &best_score2); // ������ ������ �ְ������� �ҷ��� 
        fclose(file2); //���� ���� 
    }

    key = 0;
    game_over = 0;
    game_over2 = 0;

    level = 1; //�������� �ʱ�ȭ 
    score = 0;
    level_goal = 1000;
    crush_on = 0;
    cnt = 0;
    speed = 100;


    level2 = 1; //�������� �ʱ�ȭ 
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

    system("cls"); //ȭ������ 
    reset_main(); // main_org�� �ʱ�ȭ 
    draw_map(); // ����ȭ���� �׸�
    draw_main(); // �������� �׸� 
    draw_main2(); // �������� �׸� 

    b_type_next = rand() % 7; //�������� ���� ��� ������ �����ϰ� ���� 
    b_type_next2 = rand() % 7; //�������� ���� ��� ������ �����ϰ� ���� 
    new_block(); //���ο� ����� �ϳ� ���� 
    new_block2(); //���ο� ����� �ϳ� ����
}

void reset_main(void) { //�������� �ʱ�ȭ  
    int i, j;

    for (i = 0; i < MAIN_Y; i++) { // �������� 0���� �ʱ�ȭ  
        for (j = 0; j < MAIN_X; j++) {
            main_org[i][j] = 0;
            main_cpy[i][j] = 100;
        }
    }
    for (j = 1; j < MAIN_X; j++) { //y���� 3�� ��ġ�� õ���� ���� 
        main_org[3][j] = CEILLING;
    }
    for (i = 1; i < MAIN_Y - 1; i++) { //�¿� ���� ����  
        main_org[i][0] = WALL;
        main_org[i][MAIN_X - 1] = WALL;
    }
    for (j = 0; j < MAIN_X; j++) { //�ٴں��� ���� 
        main_org[MAIN_Y - 1][j] = WALL;
    }

    for (i = 0; i < MAIN_YY; i++) { // �������� 0���� �ʱ�ȭ  
        for (j = MAIN_XX - 11; j < MAIN_XX; j++) {
            main_org2[i][j] = 0;
            main_cpy2[i][j] = 100;
        }
    }
    for (j = MAIN_XX - 10; j < MAIN_XX; j++) { //y���� 3�� ��ġ�� õ���� ���� 
        main_org2[3][j] = CEILLING;
    }
    for (i = 1; i < MAIN_YY - 1; i++) { //�¿� ���� ����  
        main_org2[i][MAIN_XX - 11] = WALL;
        main_org2[i][MAIN_XX - 1] = WALL;
    }
    for (j = MAIN_XX - 11; j < MAIN_XX; j++) { //�ٴں��� ���� 
        main_org2[MAIN_YY - 1][j] = WALL;
    }
}

void reset_main_cpy(void) { //main_cpy�� �ʱ�ȭ 
    int i, j;

    for (i = 0; i < MAIN_Y; i++) {         //�����ǿ� ���ӿ� ������ �ʴ� ���ڸ� ���� 
        for (j = 0; j < MAIN_X; j++) {  //�̴� main_org�� ���� ���ڰ� ���� �ϱ� ���� 
            main_cpy[i][j] = 100;
        }
    }
}

void reset_main_cpy2(void) { //main_cpy�� �ʱ�ȭ 
    int i, j;

    for (i = 0; i < MAIN_YY; i++) {         //�����ǿ� ���ӿ� ������ �ʴ� ���ڸ� ���� 
        for (j = MAIN_XX - 11; j < MAIN_XX; j++) {  //�̴� main_org�� ���� ���ڰ� ���� �ϱ� ���� 
            main_cpy2[i][j] = 100;
        }
    }
}

void draw_map(void) { //���� ���� ǥ�ø� ��Ÿ���� �Լ�  
    int y = 3;             // level, goal, score�� �����߿� ���� �ٲ�� �� ���� �� y���� ���� �����ص� 
    // �׷��� Ȥ�� ���� ���� ǥ�� ��ġ�� �ٲ� �� �Լ����� �ȹٲ㵵 �ǰ�.. 
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

void draw_main(void) { //������ �׸��� �Լ� 
    int i, j;

    for (j = 1; j < MAIN_X - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
        if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
    }
    for (i = 0; i < MAIN_Y; i++) {
        for (j = 0; j < MAIN_X; j++) {
            if (main_cpy[i][j] != main_org[i][j]) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���.
                //�̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ�
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                switch (main_org[i][j]) {
                case EMPTY: //��ĭ��� 
                    printf("  ");
                    break;
                case CEILLING: //õ���� 
                    printf(". ");
                    break;
                case WALL: //����� 
                    printf("��");
                    break;
                case INACTIVE_BLOCK: //���� �� ���  
                    printf("��");
                    break;
                case ACTIVE_BLOCK: //�����̰��ִ� �� ���  
                    printf("��");
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAIN_Y; i++) { //�������� �׸� �� main_cpy�� ����  
        for (j = 0; j < MAIN_X; j++) {
            main_cpy[i][j] = main_org[i][j];
        }
    }
}

void draw_main2(void) { //������ �׸��� �Լ� 
    int i, j;

    for (j = MAIN_XX - 10; j < MAIN_XX - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
        if (main_org2[3][j] == EMPTY) main_org2[3][j] = CEILLING;
    }
    for (i = 0; i < MAIN_YY; i++) {
        for (j = MAIN_XX - 11; j < MAIN_XX; j++) {
            if (main_cpy2[i][j] != main_org2[i][j]) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���.
                //�̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ�
                gotoxy(MAIN_XX_ADJ + j, MAIN_YY_ADJ + i);
                switch (main_org2[i][j]) {
                case EMPTY: //��ĭ��� 
                    printf("  ");
                    break;
                case CEILLING: //õ���� 
                    printf(". ");
                    break;
                case WALL: //����� 
                    printf("��");
                    break;
                case INACTIVE_BLOCK: //���� �� ���  
                    printf("��");
                    break;
                case ACTIVE_BLOCK: //�����̰��ִ� �� ���  
                    printf("��");
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAIN_YY; i++) { //�������� �׸� �� main_cpy�� ����  
        for (j = MAIN_XX - 11; j < MAIN_XX; j++) {
            main_cpy2[i][j] = main_org2[i][j];
        }
    }
}

void new_block(void) { //���ο� ��� ����  
    int i, j;

    bx = (MAIN_X / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
    by = 0;  //��� ������ġ y��ǥ(���� ��) 
    b_type = b_type_next; //���������� ������ 
    b_type_next = rand() % 7; //���� ���� ���� 
    b_rotation = 0;  //ȸ���� 0������ ������ 

    new_block_on = 0; //new_block flag�� ��  


    for (i = 0; i < 4; i++) { //������ bx, by��ġ�� ������  
        for (j = 0; j < 4; j++) {
            if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
        }
    }
    for (i = 1; i < 3; i++) { //���ӻ���ǥ�ÿ� ������ ���ú��� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}

void new_block2(void) { //���ο� ��� ����
    int i, j;

    bx2 = (MAIN_XX / 2) - 6; //��� ���� ��ġx��ǥ(�������� ���)
    by2 = 0;  //��� ������ġ y��ǥ(���� ��)
    b_type2 = b_type_next2; //���������� ������
    b_type_next2 = rand() % 7; //���� ���� ����
    b_rotation2 = 0;  //ȸ���� 0������ ������

    new_block_on2 = 0; //new_block flag�� ��

    for (i = 0; i < 4; i++) { //������ bx, by��ġ�� ������
        for (j = 0; j < 4; j++) {
            if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = ACTIVE_BLOCK;
        }
    }
    for (i = 1; i < 3; i++) { //���ӻ���ǥ�ÿ� ������ ���ú��� �׸�
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next2][0][i][j] == 1) {
                gotoxy(STATUS_XX_ADJ + 2 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(STATUS_XX_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}


void check_key(void) {
    key = 0; //Ű�� �ʱ�ȭ  
    int i;

    if (_kbhit()) { //Ű�Է��� �ִ� ���  
        key = _getch(); //Ű���� ����
        if (key == 224) { //����Ű�ΰ�� 
            do { key = _getch(); } while (key == 224);//����Ű���ð��� ���� 
            switch (key) {
            case LEFT: //����Ű ��������  
                if (check_crush2(bx2 - 1, by2, b_rotation2) == true) move_block(LEFT);
                break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
            case RIGHT: //������ ����Ű ��������- ���� �����ϰ� ó���� 
                if (check_crush2(bx2 + 1, by2, b_rotation2) == true) move_block(RIGHT);
                break;
            case DOWN: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó���� 
                if (check_crush2(bx2, by2 + 1, b_rotation2) == true) move_block(DOWN);
                break;
            case UP: //���� ����Ű �������� 
                if (check_crush2(bx2, by2, (b_rotation2 + 1) % 4) == true) move_block(UP);
                //ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
                else if (crush_on2 == 1 && check_crush2(bx2, by2 - 1, (b_rotation2 + 1) % 4) == true) move_block(10);
                break;
            }                    //�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
        }
        else { //����Ű�� �ƴѰ�� 
            switch (key) {
            case A: //����Ű ��������
                if (check_crush(bx - 1, by, b_rotation) == true) move_block(A);
                break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
            case D: //������ ����Ű ��������- ���� �����ϰ� ó����
                if (check_crush(bx + 1, by, b_rotation) == true) move_block(D);
                break;
            case S: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó����
                if (check_crush(bx, by + 1, b_rotation) == true) move_block(S);
                break;
            case W: //���� ����Ű ��������
                if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(W);
                //ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
                else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(20);
                //�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
                break;
            case G: //GŰ ��������
                space_key_on = 1; //�����̽�Ű flag�� ���
                while (crush_on == 0) { //�ٴڿ� ���������� �̵���Ŵ
                    drop_block();
                    score += level; // hard drop ���ʽ�
                    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score); //���� ǥ��
                }
                break;
            case SPACE: //�����̽�Ű �������� 
                space_key_on2 = 1; //�����̽�Ű flag�� ��� 
                while (crush_on2 == 0) { //�ٴڿ� ���������� �̵���Ŵ 
                    drop_block2();
                    score2 += level2; // hard drop ���ʽ�
                    gotoxy(STATUS_XX_ADJ, STATUS_YY_SCORE); printf("        %6d", score2); //���� ǥ��  
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
                    reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
                    for (i = 1; i < MAIN_X - 1; i++) {
                        main_org[MAIN_Y - 2][i] = INACTIVE_BLOCK; // �ϴ� 1���� ������� ��� ä��� 
                        Sleep(20);
                    }
                    check_line();
                    //������� ��� ä�� 1�� �����
                    delete_item--; //������ �ϳ� ����
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
                    reset_main_cpy2(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
                    for (i = MAIN_XX - 10; i < MAIN_XX - 1; i++) {
                        main_org2[MAIN_YY - 2][i] = INACTIVE_BLOCK; // �ϴ� 1���� ������� ��� ä��� 
                        Sleep(20);
                    }
                    check_line2();
                    //������� ��� ä�� 1�� �����
                    delete_item2--;
                }
                break;
            case P: //P(�빮��) �������� 
            case p: //p(�ҹ���) ��������
                pause(); //�Ͻ�����
                break;
            case ESC: //ESC�������� 
                system("cls"); //ȭ���� ����� 
                exit(0); //�������� 
            }
        }
    }
    while (_kbhit()) _getch(); //Ű���۸� ��� 
}

/*
void check_key2(void) {
    key2 = 0; //Ű�� �ʱ�ȭ

    if (_kbhit()) { //Ű�Է��� �ִ� ���
        key2 = _getch(); //Ű���� ����
        switch (key2) {
        case A: //����Ű ��������
            if (check_crush2(bx2 - 1, by2, b_rotation2) == true) move_block2(A);
            break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
        case D: //������ ����Ű ��������- ���� �����ϰ� ó����
            if (check_crush2(bx2 + 1, by2, b_rotation2) == true) move_block2(D);
            break;
        case S: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó����
            if (check_crush2(bx2, by2 + 1, b_rotation2) == true) move_block2(S);
            break;
        case W: //���� ����Ű ��������
            if (check_crush2(bx2, by2, (b_rotation2 + 1) % 4) == true) move_block2(W);
            //ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
            else if (crush_on2 == 1 && check_crush2(bx2, by2 - 1, (b_rotation2 + 1) % 4) == true) move_block2(200);
            //�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
        case G: //GŰ ��������
            space_key_on2 = 1; //�����̽�Ű flag�� ���
            while (crush_on2 == 0) { //�ٴڿ� ���������� �̵���Ŵ
                drop_block2();
                score2 += level2; // hard drop ���ʽ�
                gotoxy(STATUS_XX_ADJ, STATUS_YY_SCORE); printf("        %6d", score2); //���� ǥ��
            }
            break;
        case P: //P(�빮��) ��������
        case p: //p(�ҹ���) ��������
            pause(); //�Ͻ�����
            break;
        case ESC: //ESC��������
            system("cls"); //ȭ���� �����
            exit(0); //��������
        }
    }
    while (_kbhit()) _getch(); //Ű���۸� ���
}
*/

void drop_block(void) {
    int i, j;

    if (crush_on && check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //���� ��������� crush flag ��
    if (crush_on && check_crush(bx, by + 1, b_rotation) == false) { //���� ��������ʰ� crush flag�� ���������� 
        for (i = 0; i < MAIN_Y; i++) { //���� �������� ���� ���� 
            for (j = 0; j < MAIN_X; j++) {
                if (main_org[i][j] == ACTIVE_BLOCK) main_org[i][j] = INACTIVE_BLOCK;
            }
        }
        crush_on = 0; //flag�� �� 
        check_line(); //����üũ�� �� 
        new_block_on = 1; //���ο� ������ flag�� ��    
        return; //�Լ� ���� 
    }
    if (check_crush(bx, by + 1, b_rotation) == true) move_block(S); //���� ��������� ������ ��ĭ �̵� 
    if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; //������ �̵��� �ȵǸ�  crush flag�� ��
}

void drop_block2(void) {
    int i, j;

    if (crush_on2 && check_crush2(bx2, by2 + 1, b_rotation2) == true) crush_on2 = 0; //���� ��������� crush flag ��
    if (crush_on2 && check_crush2(bx2, by2 + 1, b_rotation2) == false) { //���� ��������ʰ� crush flag�� ����������
        for (i = 0; i < MAIN_YY; i++) { //���� �������� ���� ����
            for (j = MAIN_XX - 11; j < MAIN_XX; j++) {
                if (main_org2[i][j] == ACTIVE_BLOCK) main_org2[i][j] = INACTIVE_BLOCK;
            }
        }
        crush_on2 = 0; //flag�� ��
        check_line2(); //����üũ�� ��
        new_block_on2 = 1; //���ο� ������ flag�� ��
        return; //�Լ� ����
    }
    if (check_crush2(bx2, by2 + 1, b_rotation2) == true) move_block(DOWN); //���� ��������� ������ ��ĭ �̵�
    if (check_crush2(bx2, by2 + 1, b_rotation2) == false) crush_on2++; //������ �̵��� �ȵǸ�  crush flag�� ��
}


int check_crush(int bx, int by, int b_rotation) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
            if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
        }
    }
    return true; //�ϳ��� �Ȱ�ġ�� true���� 
};


int check_crush2(int bx2, int by2, int b_rotation2) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
            if (blocks[b_type2][b_rotation2][i][j] == 1 && main_org2[by2 + i][bx2 + j] > 0) return false;
        }
    }
    return true; //�ϳ��� �Ȱ�ġ�� true���� 
};



void move_block(int dir) { //����� �̵���Ŵ 
    int i, j;

    switch (dir) {
    case LEFT: //���ʹ��� 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx2--; //��ǥ�� �̵� 
        break;

    case RIGHT:    //������ ����. ���ʹ����̶� ���� ������ ���� 
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

    case DOWN:    //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
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

    case UP: //Ű���� ���� �������� ȸ����Ŵ. 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ����  
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        b_rotation2 = (b_rotation2 + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
        for (i = 0; i < 4; i++) { //ȸ���� ����� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 10: //����� �ٴ�, Ȥ�� �ٸ� ��ϰ� ���� ���¿��� ��ĭ���� �÷� ȸ���� ������ ��� 
        //�̸� ���۽�Ű�� Ư������ 
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

    case A: //���ʹ��� 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx--; //��ǥ�� �̵� 
        break;

    case D:    //������ ����. ���ʹ����̶� ���� ������ ���� 
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

    case S:    //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
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

    case W: //Ű���� ���� �������� ȸ����Ŵ. 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ����  
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
        for (i = 0; i < 4; i++) { //ȸ���� ����� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 20: //����� �ٴ�, Ȥ�� �ٸ� ��ϰ� ���� ���¿��� ��ĭ���� �÷� ȸ���� ������ ��� 
        //�̸� ���۽�Ű�� Ư������ 
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
void move_block2(int dir) { //����� �̵���Ŵ
    int i, j;

    switch (dir) {
    case A: //���ʹ���
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ����
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ����
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx2--; //��ǥ�� �̵�
        break;

    case D:    //������ ����. ���ʹ����̶� ���� ������ ����
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

    case S:    //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
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

    case W: //Ű���� ���� �������� ȸ����Ŵ.
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ����
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = EMPTY;
            }
        }
        b_rotation2 = (b_rotation2 + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���)
        for (i = 0; i < 4; i++) { //ȸ���� ����� ����
            for (j = 0; j < 4; j++) {
                if (blocks[b_type2][b_rotation2][i][j] == 1) main_org2[by2 + i][bx2 + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 200: //����� �ٴ�, Ȥ�� �ٸ� ��ϰ� ���� ���¿��� ��ĭ���� �÷� ȸ���� ������ ���
        //�̸� ���۽�Ű�� Ư������
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

    int block_amount; //������ ��ϰ����� �����ϴ� ���� 
    int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

    for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
        block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
        for (j = 1; j < MAIN_X - 1; j++) { //���� �������� ��ϰ��縦 �� 
            if (main_org[i][j] > 0) block_amount++;
        }
        if (block_amount == MAIN_X - 2) { //����� ���� �� ��� 
            if (level_up_on == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����) 
                score += 100 * level; //�����߰� 
                cnt++; //���� �� ���� ī��Ʈ ���� 
                combo++; //�޺��� ����  
            }
            for (k = i; k > 1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��) 
                for (l = 1; l < MAIN_X - 1; l++) {
                    if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
                    if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;
                    //������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
                }
            }
        }
        else i--;
    }
    if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ����  
        if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ���� 
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 4); printf("%d COMBO!", combo);
            Sleep(500);
            score += (combo * level * 100);
            reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
            //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 
        }
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= 10) ? 10 - cnt : 0);
        gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
    }
}
void check_line2(void) {
    int i, j, k, l;

    int block_amount; //������ ��ϰ����� �����ϴ� ���� 
    int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

    for (i = MAIN_YY - 2; i > 3;) { //i=MAIN_YY-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
        block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
        for (j = MAIN_XX - 10; j < MAIN_XX - 1; j++) { //���� �������� ��ϰ��縦 �� 
            if (main_org2[i][j] > 0) block_amount++;
        }
        if (block_amount == MAIN_X - 2) { //����� ���� �� ��� 
            if (level_up_on2 == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����) 
                score2 += 100 * level2; //�����߰� 
                cnt2++; //���� �� ���� ī��Ʈ ���� 
                combo++; //�޺��� ����  
            }
            for (k = i; k > 1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��) 
                for (l = MAIN_XX - 10; l < MAIN_XX - 1; l++) {
                    if (main_org2[k - 1][l] != CEILLING) main_org2[k][l] = main_org2[k - 1][l];
                    if (main_org2[k - 1][l] == CEILLING) main_org2[k][l] = EMPTY;
                    //������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
                }
            }
        }
        else i--;
    }
    if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ����  
        if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ���� 
            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 7, MAIN_YY_ADJ + 4); printf("%d COMBO!", combo);
            Sleep(500);
            score2 += (combo * level2 * 100);
            reset_main_cpy2(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
            //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 
        }
        gotoxy(STATUS_XX_ADJ, STATUS_YY_GOAL); printf(" GOAL  : %5d", (cnt2 <= 10) ? 10 - cnt2 : 0);
        gotoxy(STATUS_XX_ADJ, STATUS_YY_SCORE); printf("        %6d", score2);
    }
}

void check_level_up(void) {
    int i, j;

    if (cnt >= 10) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
        draw_main();
        level_up_on = 1; //������ flag�� ��� 
        level += 1; //������ 1 �ø� 
        cnt = 0; //���� �ټ� �ʱ�ȭ   

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("��LEVEL UP!��");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 6);
            printf("��SPEED UP!��");
            Sleep(200);

            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 6);
            printf("             ");
            Sleep(200);
        }
        reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
        //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

        for (i = MAIN_Y - 2; i > MAIN_Y - 2 - (level - 1); i--) { //�������������� �� ����-1�� ����ŭ �Ʒ��� ���� ������ 
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[i][j] = INACTIVE_BLOCK; // ���� ������� ��� ä��� 
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); // ���� �����.. �̻����̰� 
                printf("��");
                Sleep(20);
            }
        }
        Sleep(100); //�������� �����ֱ� ���� delay 
        check_line(); //������� ��� ä��� �����
        //.check_line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.         
        switch (level) { //�������� �ӵ��� ��������. 
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
        level_up_on = 0; //������ flag����

        gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //����ǥ�� 
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - cnt); // ������ǥ ǥ�� 

    }
}
void check_level_up2(void) {
    int i, j;

    if (cnt2 >= 10) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
        draw_main2();
        level_up_on2 = 1; //������ flag�� ��� 
        level2 += 1; //������ 1 �ø� 
        cnt2 = 0; //���� �ټ� �ʱ�ȭ   

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 8, MAIN_YY_ADJ + 4);
            printf("��LEVEL UP!��");
            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 8, MAIN_YY_ADJ + 6);
            printf("��SPEED UP!��");
            Sleep(200);

            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 8, MAIN_YY_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_XX_ADJ + (MAIN_XX / 2) - 8, MAIN_YY_ADJ + 6);
            printf("             ");
            Sleep(200);
        }
        reset_main_cpy2(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
        //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

        for (i = MAIN_YY - 2; i > MAIN_YY - 2 - (level2 - 1); i--) { //�������������� �� ����-1�� ����ŭ �Ʒ��� ���� ������ 
            for (j = MAIN_XX - 10; j < MAIN_XX - 1; j++) {
                main_org2[i][j] = INACTIVE_BLOCK; // ���� ������� ��� ä��� 
                gotoxy(MAIN_XX_ADJ + j, MAIN_YY_ADJ + i); // ���� �����.. �̻����̰� 
                printf("��");
                Sleep(20);
            }
        }
        Sleep(100); //�������� �����ֱ� ���� delay 
        check_line2(); //������� ��� ä��� �����
        //.check_line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.         
        switch (level2) { //�������� �ӵ��� ��������. 
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
        level_up_on2 = 0; //������ flag����

        gotoxy(STATUS_XX_ADJ, STATUS_YY_LEVEL); printf(" LEVEL : %5d", level2); //����ǥ�� 
        gotoxy(STATUS_XX_ADJ, STATUS_YY_GOAL); printf(" GOAL  : %5d", 10 - cnt2); // ������ǥ ǥ�� 

    }
}

void check_game_over(void) {
    int i;

    int x = 5;
    int y = 8;

    for (i = 1; i < MAIN_X - 2; i++) {
        if (main_org[3][i] > 0) { //õ��(������ ����° ��)�� inactive�� �����Ǹ� ���� ����
            new_block_on = -1; //���̻� ���ο� ������x, �����ߴ�
            game_over = 1;

            gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //���ӿ��� �޼��� 
            gotoxy(x, y + 1); printf("��                              ��");
            gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 3); printf("��  | 1 P  G A M E  O V E R |   ��");
            gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 5); printf("��  YOUR SCORE: %6d          ��", score);
            gotoxy(x, y + 6); printf("��                              ��");
            gotoxy(x, y + 7); printf("��  Please wait for 2P..        ��");
            gotoxy(x, y + 8); printf("��                              ��");
            gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");

            last_score = score; //���������� �ű� 

            if (score > best_score) { //�ְ��� ���Ž� 
                FILE* file = fopen("score.dat", "wt"); //score.dat�� ���� ����                

                gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

                if (file == 0) { //���� �����޼���  
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
        if (main_org2[3][i] > 0) { //õ��(������ ����° ��)�� inactive�� �����Ǹ� ���� ���� 
            new_block_on2 = -1; //���̻� ���ο� ������x, �����ߴ�
            game_over2 = 1;

            gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //���ӿ��� �޼��� 
            gotoxy(x, y + 1); printf("��                              ��");
            gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 3); printf("��  | 2 P  G A M E  O V E R |   ��");
            gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 5); printf("��  YOUR SCORE: %6d          ��", score2);
            gotoxy(x, y + 6); printf("��                              ��");
            gotoxy(x, y + 7); printf("��  Please wait for 1P..        ��");
            gotoxy(x, y + 8); printf("��                              ��");
            gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");

            last_score2 = score2; //���������� �ű� 

            if (score2 > best_score2) { //�ְ��� ���Ž� 
                FILE* file2 = fopen("score2.dat", "wt"); //score.dat�� ���� ����                

                gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

                if (file2 == 0) { //���� �����޼���  
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

    if (score > score2) { //1p������ ������
        gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //����ǥ�� �޼���
        gotoxy(x, y + 1); printf("��                              ��");
        gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 3); printf("��  |�� W I N N E R : 1 P ��|   ��");
        gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 5); printf("��  YOUR SCORE: %6d          ��", score);
        gotoxy(x, y + 6); printf("��                              ��");
        gotoxy(x, y + 7); printf("��  Press any key to restart..  ��");
        gotoxy(x, y + 8); printf("��                              ��");
        gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
        last_score = score; //���������� �ű�

        if (score > best_score) { //�ְ��� ���Ž�
            FILE* file = fopen("score.dat", "wt"); //score.dat�� ���� ����

            gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

            if (file == 0) { //���� �����޼���
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

    if (score2 > score) { //2p������ ������
        gotoxy(x + 22, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //����ǥ�� �޼���
        gotoxy(x + 22, y + 1); printf("��                              ��");
        gotoxy(x + 22, y + 2); printf("��  +-----------------------+   ��");
        gotoxy(x + 22, y + 3); printf("��  |�� W I N N E R : 2 P ��|   ��");
        gotoxy(x + 22, y + 4); printf("��  +-----------------------+   ��");
        gotoxy(x + 22, y + 5); printf("��  YOUR SCORE: %6d          ��", score2);
        gotoxy(x + 22, y + 6); printf("��                              ��");
        gotoxy(x + 22, y + 7); printf("��  Press any key to restart..  ��");
        gotoxy(x + 22, y + 8); printf("��                              ��");
        gotoxy(x + 22, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
        last_score2 = score2; //���������� �ű�

        if (score2 > best_score2) { //�ְ��� ���Ž�
            FILE* file2 = fopen("score2.dat", "wt"); //score2.dat�� ���� ����

            gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

            if (file2 == 0) { //���� �����޼���
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

    if ((game_over == 1) && (game_over2 == 1) && (score == score2)) { //������ ������
        gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //����ǥ�� �޼���
        gotoxy(x, y + 1); printf("��                              ��");
        gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 3); printf("��  |      �� T I E ��      |   ��");
        gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 5); printf("��  YOUR SCORE: %6d          ��", score);
        gotoxy(x, y + 6); printf("��                              ��");
        gotoxy(x, y + 7); printf("��  Press any key to restart..  ��");
        gotoxy(x, y + 8); printf("��                              ��");
        gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
        last_score = score; //���������� �ű�
        if (score > best_score) { //�ְ��� ���Ž�
            FILE* file = fopen("score.dat", "wt"); //score.dat�� ���� ����

            gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

            if (file == 0) { //���� �����޼���
                gotoxy(0, 0);
                printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
            }
            else {
                fprintf(file, "%d", score);
                fclose(file);
            }
        }

        gotoxy(x + 22, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //����ǥ�� �޼���
        gotoxy(x + 22, y + 1); printf("��                              ��");
        gotoxy(x + 22, y + 2); printf("��  +-----------------------+   ��");
        gotoxy(x + 22, y + 3); printf("��  |      �� T I E ��      |   ��");
        gotoxy(x + 22, y + 4); printf("��  +-----------------------+   ��");
        gotoxy(x + 22, y + 5); printf("��  YOUR SCORE: %6d          ��", score2);
        gotoxy(x + 22, y + 6); printf("��                              ��");
        gotoxy(x + 22, y + 7); printf("��  Press any key to restart..  ��");
        gotoxy(x + 22, y + 8); printf("��                              ��");
        gotoxy(x + 22, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
        last_score2 = score2; //���������� �ű�
        if (score2 > best_score2) { //�ְ��� ���Ž�
            FILE* file2 = fopen("score2.dat", "wt"); //score2.dat�� ���� ����

            gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

            if (file2 == 0) { //���� �����޼���
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

void pause(void) { //���� �Ͻ����� �Լ� 
    int i, j;

    int x = 16;
    int y = 9;

    for (i = 1; i < MAIN_X - 2; i++) { //���� �Ͻ����� �޼��� 
        gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
        gotoxy(x, y + 1); printf("��                              ��");
        gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 3); printf("��  |       P A U S E       |   ��");
        gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 5); printf("��  Press any key to resume..   ��");
        gotoxy(x, y + 6); printf("��                              ��");
        gotoxy(x, y + 7); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
    }
    _getch(); //Ű�Է½ñ��� ��� 

    system("cls"); //ȭ�� ����� ���� �׸� 
    reset_main_cpy();
    reset_main_cpy2();
    draw_main();
    draw_main2();
    draw_map();

    for (i = 1; i < 3; i++) { // ������� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(MAIN_X + MAIN_X_ADJ + 4 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(MAIN_X + MAIN_X_ADJ + 4 + j, i + 6);
                printf("  ");
            }
        }
    }
    for (i = 1; i < 3; i++) { // ������� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next2][0][i][j] == 1) {
                gotoxy(STATUS_XX_ADJ + 2 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(STATUS_XX_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
} //��!