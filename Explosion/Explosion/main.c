#include <stdio.h>
#include <math.h>
#include <Windows.h>
#define PI 3.14159226535897

void moveCursor(int x, int y) {
    printf("\x1b[%d;%dH", y, x);
}

//매개변수 isExpploded
//0: 폭발전 폭탄
//1: 폭발함
void printBomb(int isExpploded) {
    //폭탄은 항상 7칸
    if (isExpploded) {
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!");
        printf("\x1b[B\x1b[7D^^^^^^^");
    }

    else
    {
        printf("(  b  )");
    }
}

int main() {
    printBomb(0);
    // 0: 하, 1: 우, 2: 상, 3: 좌
    int direction = 0;// 방향(?)
    int posX = 14, posY = 7; // 좌표지정
    moveCursor(posX, posY); // 커서 움직임
    printf("*");

    // # 그리기
    for (int i = 2; i <= 12; i += 2)  // 턴마다 제거할 # 개수
    {
        for (int j = 0; j < 2; j++)  // 두 턴 소비
        {
            for (int k = 0; k < i; k++) // 해당 턴에 제거할 #의 개수만큼 반복
            {
                switch (direction) {
                case 0: // 하
                    posY++;
                    moveCursor(posX, posY);
                    break;
                case 1: // 우
                    posX++;
                    moveCursor(posX, posY);
                    break;
                case 2: // 상
                    posY--;
                    moveCursor(posX, posY);
                    break;
                case 3: // 좌
                    posX--;
                    moveCursor(posX, posY);
                    break;
                }
                printf("#");// #그리는거 반복
            }
            direction = (direction + 1) % 4; // 방향 바꾸기
        }
    }

    posX = 14, posY = 7; // 그리기 시작할 좌표
    direction = 0;//다시 아래로 방향조절
    for (int i = 2; i <= 12; i += 2)  // 턴마다 제거할 # 개수
    {
        for (int j = 0; j < 2; j++)  // 두 턴 소비
        {
            for (int k = 0; k < i; k++) // 해당 턴에 제거할 #의 개수만큼 반복
            {
                moveCursor(posX, posY);// 커서 움직임
                printf(" ");
                switch (direction) {
                case 0: // 하
                    posY++;
                    moveCursor(posX, posY);
                    break;
                case 1: // 우
                    posX++;
                    moveCursor(posX, posY);
                    break;
                case 2: // 상
                    posY--;
                    moveCursor(posX, posY);
                    break;
                case 3: // 좌
                    posX--;
                    moveCursor(posX, posY);
                    break;
                }
                printf("*");// #자리에 *을 그리기 위함
                moveCursor(posX, posY);
                Sleep(200);//200ms마다 진행(?)
            }
            direction = (direction + 1) % 4; // 방향 바꾸기
        }
        printf(" ");// 마지막에 남은 *없애기 위한 공백
    }

    moveCursor(posX, posY);// 커서를 지정 좌표로 움직임
    moveCursor(0, 0);// 좌표에 커서 움직임
    printf(" ");
    printBomb(1);
    moveCursor(0, 0);// 좌표에 커서 움직임
    moveCursor(10, 20);// 좌표에 커서 움직임

    return 0;
}// 문제점 출력 다끝낸 후 b가 사라져야 하는데 안사라짐, 프린트 한번씩만 써야하는데 조건 에 부합하지 못함