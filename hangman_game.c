#include <stdio.h>
#include <stdbool.h>//���� c������ bool Ÿ���� ����
#include <string.h>//strlen() ������ �����, ��� �Ǳ� �ϴµ� ��� ���� �Ⱦ..
#include <time.h> // ���� �������� ������ �� �� 
#include <Windows.h> 
#include <stdlib.h>

#define UP 0
#define DOWN 1
#define SUBMIT 4
#define QUIT 5

int KeyControl(); //���ĺ� �Է½ÿ� ���� return
int menu(); //�ʱ� �޴��Լ�
void titleDraw(); //Hangman Game
void how(); //���ӹ��
void game();
void gotoxy(int x, int y); //�̵�
void init(); //�ܼ�â ���� �� ũ�� ����
void finish(); //���� ���� �� Q�Է� �޾Ƽ� ������


char word[10][15] = { "apple","banana","orange","pineapple","source","queen","company","korea","chair","computer" }; //�ε��� 1 ����(���� �������� �������ֱ�)
char save[10];
bool mcw(char a, int random);////
int life = 10;
int count = 0;
char text[15]; //����ϴ� ����ܾ�

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

int keyControl() { //����Ű, submit 
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
    system("mode con cols=94 lines=25 | title Hangman Game");//�ܼ�â ũ�� ����
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
    printf("> ���ӽ���");
    gotoxy(x, y+1);
    printf("> ���ӹ��");
    gotoxy(x, y + 2);
    printf("> ������");

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
    printf("<���� ���>\n\n");
    printf("����1");
    printf("����2");
    while (1) {
        if (keyControl() == QUIT) {
            break;
        }
    }
}


void titleDraw() {
    printf("\n\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | FOREGROUND_INTENSITY); //���� �ֱ� (�����)
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    printf("������������������������������������������������\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//���󺹱�

}

void game() {
    system("cls");
    srand(time(NULL));//rand�� �Ź� �ʱ�ȭ
    int random = rand() % 10; //->  0 ~ 9  
    for (int i = 0; i < strlen(word[random]); i++) {
        text[i] = '_'; //����
    }


    while (1) {
        
        printf("�Է��� ���ĺ���: ");
        for (int i = 0; i < 10; i++) {
            printf("%c ", save[i]); //%s => string printf("%s",save);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 | FOREGROUND_INTENSITY);
        printf("\nlife:");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//���󺹱�
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2 | FOREGROUND_INTENSITY);
        printf(" %d\n ", life);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//���󺹱�

        for (int i = 0; i < strlen(word[random]); i++) {
            printf("--");

        }
        printf("\n");
        printf("|");
        for (int i = 0; i < strlen(word[random]); i++) {
            printf("%c ", text[i]); //��� _
        }
        printf("|\n ");
        for (int i = 0; i < strlen(word[random]); i++) {
            printf("--");

        }

        int ret = strcmp(text, word[random]);//����1, ����2 ���ؼ� ������ 0��� �ٸ��� 1��ȯ
        if (ret == 0) //���ߴµ� ����! �����̴�!
        {
            printf("\n�����Դϴ�!\n\n");
            finish();
        }

        char a;

        if (life == 0) {
            printf("life ���� ����");
            printf("�õ� Ƚ�� �ʰ�, ���� ����");
            finish();
        }

        printf("\n\n���ĺ��� �Է��ϼ��� :");
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
            text[i] = a; // ���� �Է��� ���ĺ��� "_ _ _ _"�� ���� �� �´� �ڸ��� �־��� 
            check = 1;//���� ���ĺ��� �ΰ� �̻� �� �� ��� bool check ���� �ϳ� �����
        }
    }
    if (check == 1) return true;
    else return false;
}

void finish() {
    printf("Q�� ������ ����˴ϴ�.\n");
    while (1) {
        if (keyControl() == QUIT) {
            exit(1);
        }
    }
}