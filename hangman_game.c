#include <stdio.h>
#include <stdbool.h>//원래 c에서는 bool 타입이 없음
#include <string.h>//strlen() 쓰려고 갖고옴, 없어도 되긴 하는데 경고 보기 싫어서..
#include <time.h> // 값을 랜덤으로 가져올 때 씀 
#include <Windows.h> 
#include <stdlib.h>

#define UP 0
#define DOWN 1
#define SUBMIT 4
#define QUIT 5

int KeyControl(); //알파벳 입력시에 방향 return
int menu(); //초기 메뉴함수
void titleDraw(); //Hangman Game
void how(); //게임방법
void game();
void gotoxy(int x, int y); //이동
void init(); //콘솔창 등장 및 크기 조절
void finish(); //게임 종료 시 Q입력 받아서 끝내기


char word[10][15] = { "apple","banana","orange","pineapple","source","queen","company","korea","chair","computer" }; //인덱스 1 기준(원래 랜덤으로 설정해주기)
char save[10];
bool mcw(char a, int random);////
int life = 10;
int count = 0;
char text[15]; //출력하는 정답단어

int main() {
    init();
    for (int i = 0; i < 2; i++) {
        titleDraw();
        int menuCode = menu();
        if (menuCode == 20) {
            game();
        }
        else if (menuCode == 21) {
            how();
        }
        else if (menuCode == 22) {
            break;
        }
        system("cls");
    }

    return 0;
}

int keyControl() { //방향키, submit 
    char temp = _getch();
    if (temp == 'w' || temp == 'W') {
        return UP;
    }
    else if (temp == 's' || temp == 'S') {
        return DOWN;
    }
    else if (temp == ' ') {
        return SUBMIT;
    }
    else if (temp == 'q' || temp == 'Q') {
        return QUIT;
    }
}

void init() {
    system("mode con cols=94 lines=25 | title Hangman Game");//콘솔창 크기 조절
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int menu() {
    int x = 43;
    int y = 20;
    gotoxy(x , y);
    printf("> 게임시작");
    gotoxy(x, y+1);
    printf("> 게임방법");
    gotoxy(x, y + 2);
    printf("> 끝내기");

    while (1) {
        int n = keyControl();
        switch (n) {
            case UP: {
                if (y > 20) {
                    gotoxy(x - 2, y);
                    printf(" ");
                    gotoxy(x - 2, --y);
                    printf(">");
                }
                break;
            }
            case DOWN: {
                if (y < 22) {
                    gotoxy(x - 2, y);
                    printf(" ");
                    gotoxy(x - 2, ++y);
                    printf(">");
                }
                break;
            }
            case SUBMIT: {
                return y;
            }
        }
    }
}

void how() {
    system("cls");
    printf("\n\n");
    printf("<게임 방법>\n\n");
    printf("설명1");
    printf("설명2");
    while (1) {
        if (keyControl() == QUIT) {
            break;
        }
    }
}


void titleDraw() {
    printf("\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | FOREGROUND_INTENSITY); //색깔 넣기 (노란색)
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
    printf("□■□□□□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
    printf("□■□□□□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
    printf("□■□□□□■□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
    printf("□■□□□□■□□□■■■□□■□■■□□□■■■■□■■■□■■□□□■■■□□■□■■□□\n");
    printf("□■■■■■■□□□□□□■□■■□□■□■□□□■□■□□■□□■□□□□□■□■■□□■□\n");
    printf("□■□□□□■□□□■■■■□■□□□■□■□□□■□■□□■□□■□□■■■■□■□□□■□\n");
    printf("□■□□□□■□□■□□□■□■□□□■□■□□□■□■□□■□□■□■□□□■□■□□□■□\n");
    printf("□■□□□□■□□■□□□■□■□□□■□■□□□■□■□□■□□■□■□□□■□■□□□■□\n");
    printf("□■□□□□■□□□■■■■□■□□□■□□■■■■□■□□■□□■□□■■■■□■□□□■□\n");
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□■□□□□□□□□□□□□□□□□□□□□□\n");
    printf("□□□□□□□□□□□□□□□□□□□□□■■■■□□□□□□□□□□□□□□□□□□□□□□\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//원상복귀

}

void game() {
    system("cls");
    srand(time(NULL));//rand값 매번 초기화
    int random = rand() % 10; //->  0 ~ 9  
    for (int i = 0; i < strlen(word[random]); i++) {
        text[i] = '_'; //저장
    }


    while (1) {
        
        printf("입력한 알파벳들: ");
        for (int i = 0; i < 10; i++) {
            printf("%c ", save[i]); //%s => string printf("%s",save);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | FOREGROUND_INTENSITY);
        printf("\nlife:");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//원상복귀
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2 | FOREGROUND_INTENSITY);
        printf(" %d\n ", life);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//원상복귀

        for (int i = 0; i < strlen(word[random]); i++) {
            printf("--");

        }
        printf("\n");
        printf("|");
        for (int i = 0; i < strlen(word[random]); i++) {
            printf("%c ", text[i]); //출력 _
        }
        printf("|\n ");
        for (int i = 0; i < strlen(word[random]); i++) {
            printf("--");

        }

        int ret = strcmp(text, word[random]);//인자1, 인자2 비교해서 같으면 0출력 다르면 1반환
        if (ret == 0) //비교했는데 같다! 정답이다!
        {
            printf("\n정답입니다!\n\n");
            finish();
        }

        char a;

        if (life == 0) {
            printf("life 전부 소진");
            printf("시도 횟수 초과, 게임 종료");
            finish();
        }

        printf("\n\n알파벳을 입력하세요 :");
        scanf("%c", &a);
        save[count] = a;
        count++;
        
        int result = mcw(a, random);
        getchar();
        if (result == 1) {
            printf("corret\n");
        }
        else {
            printf("wrong\n");
            life--;
        }

    }
}

bool mcw(char a, int random) {
    bool check = 0;
    for (int i = 0; i < strlen(word[random]); i++) {
        if (word[random][i] == a) {
            text[i] = a; // 내가 입력한 알파벳이 "_ _ _ _"에 있을 때 맞는 자리에 넣어줌 
            check = 1;//같은 알파벳이 두개 이상 들어갈 때 고려 bool check 변수 하나 만들기
        }
    }
    if (check == 1) return true;
    else return false;
}

void finish() {
    printf("Q를 누르면 종료됩니다.\n");
    while (1) {
        if (keyControl() == QUIT) {
            exit(1);
        }
    }
}