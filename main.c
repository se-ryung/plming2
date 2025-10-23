#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 scanf 등의 보안 경고를 무시하도록 설정
// (이건 개발 및 학습용으로 유용하지만, 실제 제품에서는 더 안전한 함수를 사용하는 것이 좋아!)

#include <stdio.h>    // 표준 입출력 함수 (printf, scanf, fopen, fclose 등)
#include <stdlib.h>   // rand, srand 함수 (랜덤 물고기 선택), system 함수 (콘솔 지우기)
#include <conio.h>    // _getch 함수 (키 입력) - Visual Studio의 Windows 환경에서 사용 가능
#include <windows.h>  // Sleep 함수 (시간 지연), SetConsoleTextAttribute 함수 (콘솔 색상) - Windows 환경 특화
#include <time.h>     // time 함수 (srand 시드 설정)
#include <string.h>   // strcmp 함수 (문자열 비교), strcspn 함수 (문자열 검색)

// 콘솔 텍스트 색상을 설정하는 함수
void SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 콘솔 텍스트 색상을 기본값(흰색)으로 초기화하는 함수
void ResetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // 기본 흰색 (빨강, 초록, 파랑 모두 활성화)
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// 물고기 구조체
struct Fish
{
    char* name;     // 물고기 이름
    char* talk;     // 물고기가 내는 퀴즈 (문제 + 보기)
    int answer;     // 퀴즈의 정답 번호

    char* talk_O;   // 퀴즈를 맞췄을 때 물고기의 대사
    char* talk_X;   // 퀴즈를 틀렸을 때 물고기의 대사
};

// 메인 함수
int main()
{
    // 랜덤 시드 초기화 (프로그램을 실행할 때마다 다른 랜덤 결과를 얻기 위함)
    srand((unsigned int)time(NULL));

    // 물고기 5마리 정보 초기화
    struct Fish fishes[5] = {
        {"니모", "세상에서 가장 큰 물고기는? (1. 상어 2. 고래 3. 고래상어)", 3, "정답이야! 짝짝짝!", "아쉽지만 틀렸어!"},
        {"도리", "물고기인데 물고기가 아닌 것은? (1. 해마 2. 물개 3. 오리)", 3, "딩동댕! 정말 똑똑하구나!", "에잇, 다음엔 맞춰봐!"},
        {"세자르", "물속에서 사는 새는? (1. 갈매기 2. 펭귄 3. 오리)", 2, "후후, 잘 맞추는걸?", "하하, 생각보다 어렵지?"},
        {"골디", "물고기가 좋아하는 음악은? (1. 팝송 2. 힙합 3. 물고기 댄스)", 3, "센스 만점! 딱 걸렸어!", "너무 어렵게 냈나?"},
        {"블루", "어부가 가장 싫어하는 물고기는? (1. 상어 2. 망둥어 3. 고등어)", 2, "정답! 어휴 다행이다!", "어부가 슬퍼할 거야..."}
    };

    FILE* fp; // 파일 포인터
    char log_name[256]; // 물고기 이름 임시 저장
    char log_result_str[10]; // O 또는 X 결과 임시 저장
    int total_games = 0; // 총 게임 횟수
    int correct_answers = 0; // 맞춘 퀴즈 횟수

    // 게임 시작 시 플레이 기록 불러오기 (log.txt에서)
    fp = fopen("log.txt", "r"); // log.txt 파일을 읽기 모드로 연다
    if (fp != NULL) { // 파일이 존재하면
        while (fgets(log_name, sizeof(log_name), fp) != NULL) { // 물고기 이름을 읽고
            log_name[strcspn(log_name, "\n")] = 0; // 개행 문자 제거

            if (fgets(log_result_str, sizeof(log_result_str), fp) != NULL) { // 이어서 결과를 읽는다
                if (log_result_str[0] == 'O') {
                    correct_answers++; // 'O'면 정답 횟수 증가
                }
                total_games++; // 총 게임 횟수 증가
            }
        }
        fclose(fp); // 파일 닫기
    }

    printf("***** 물고기 퀴즈 게임 *****\n");
    printf("현재까지 %d번째 게임입니다!\n", total_games + 1); // 현재 시작하는 게임이 n+1번째 게임
    if (total_games > 0) {
        printf("누적 정답률: %.2f%%\n", (double)correct_answers / total_games * 100.0);
    }
    else {
        printf("아직 플레이 기록이 없습니다.\n");
    }
    printf("*****************************\n\n");
    Sleep(2000); // 2초 대기
    system("cls"); // 콘솔 화면 지우기 (Windows에서 작동)


    char yn;
    while (1) { // "찌를 던진다 (Y/N) >" 출력 및 예외 처리
        printf("찌를 던진다 (Y/N) > ");
        yn = _getch(); // 키 입력을 받는다. Enter를 누르지 않아도 바로 입력됨.
        printf("%c\n", yn); // 입력받은 키를 화면에 표시

        if (yn == 'Y' || yn == 'y') {
            break; // Y나 y를 입력했으면 루프를 빠져나와 게임 진행
        }
        else if (yn == 'N' || yn == 'n') {
            printf("다음에 다시 놀러 와!\n");
            return 0; // N이나 n을 입력했으면 프로그램 종료
        }
        else {
            printf("앗, Y나 N만 입력해줘! 다시 선택해줘.\n"); // 그 외의 키 입력 시 다시 입력 요청
        }
    }

    // 500ms마다 .을 찍어서 총 5개의 점이 찍힌 후에 "입질이 왔다!!!!" 녹색으로 출력
    for (int i = 0; i < 5; i++) {
        printf(".");
        Sleep(500); // 0.5초 대기 (Windows.h)
    }
    SetColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // 글자색을 초록색 (밝게)으로 설정
    printf(" 입질이 왔다!!!!\n");
    ResetColor(); // 글자색을 기본값(흰색)으로 되돌림
    printf("\n");

    // 랜덤하게 5개의 물고기 중 하나가 튀어나와서 말을 건다.
    int random_fish_index = rand() % 5; // 0부터 4까지의 랜덤 숫자 생성
    struct Fish current_fish = fishes[random_fish_index]; // 선택된 물고기

    printf("%s : %s\n", current_fish.name, current_fish.talk);

    int user_answer;
    printf("당신의 정답은? > ");
    scanf("%d", &user_answer); // 사용자에게 정답 번호를 입력받음

    // 입력 버퍼 비우기 (다음 _getch()나 다른 입력 함수에 영향을 주지 않도록)
    while (getchar() != '\n');

    char quiz_result_char; // 로그 파일에 저장할 'O' 또는 'X'

    if (user_answer == current_fish.answer) {
        printf("%s : %s\n", current_fish.name, current_fish.talk_O);
        SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY); // 밝은 파란색
        printf(">> 와! 정답이야! 대단하다!\n");
        ResetColor();
        quiz_result_char = 'O'; // 정답이면 'O'
    }
    else {
        printf("%s : %s\n", current_fish.name, current_fish.talk_X);
        SetColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // 밝은 빨간색
        printf(">> 흐음... 다음 기회에... 정답은 %d번이었어.\n", current_fish.answer);
        ResetColor();
        quiz_result_char = 'X'; // 오답이면 'X'
    }
    printf("\n");
    Sleep(2000); // 2초 대기

    // 로그 파일을 log.txt라고 만들고 물고기 이름과, 퀴즈 맞췄는지 여부를 저장
    fp = fopen("log.txt", "a");
    if (fp == NULL) {
        printf("로그 파일을 열 수 없습니다! 관리자 권한을 확인해주세요.\n");
        return 1;
    }

    fprintf(fp, "%s\n", current_fish.name); // 물고기 이름 저장
    fprintf(fp, "%c\n", quiz_result_char);  // 퀴즈 결과 (O 또는 X) 저장
    fclose(fp); // 파일 닫기

    printf("오늘의 기록이 log.txt에 저장되었습니다!\n");
    printf("게임을 종료합니다.\n");

    return 0; // 프로그램 정상 종료
}