#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

// 함수 선언
void Draw(int x, int y, const char* word);
void Draw_boader(int stx, int sty, int width, int length);
void ClearScreenWithBorder(int stx, int sty, int width, int length);
void GotoXY(int x, int y);
void display();
void drawTitle();

char startgame();
void mobset();
void makec();
void start_give_status();
void status();

void ready_to_fight();
void fight();
void onetickturn();
int dice(int x, int y);




// 캐릭터 생성 시 캐릭터 정보 구조체
struct maincharcter {
    char mcname[10];
    char subname[10];
    char weapon[20];
    char armor[20];
    char underarmor[20];
    char shoes[20];
    char map[20];

    int level;
    double hp;
    double maxhp;
    double userdef;
    double power;
    double speed;
    double luck;

    double next_turn;
};

struct monster {
    char mobname[10];
    char buff[10];
    char weapon[20];
    char mobarmor[10];

    int level;
    double mobdef;
    double mobhp;
    double mobmaxhp;
    double mobpower;
    double speed;
    double luck;

    double next_turn;
};

struct maincharcter mc1;

struct monster mob1;

int main() {
    srand((unsigned int)time(NULL));
    char choice = startgame();

    //setting
    if (choice = '1')
    {
        strcpy_s(mc1.subname, sizeof(mc1.subname), "인간");
        mc1.level = 1;
        mc1.power = 5;
        mc1.speed = 2;
        mc1.maxhp = 10;
        mc1.luck = 5;

        makec();
        mc1.hp = mc1.maxhp;
        
    }

    
    //mobsetting
    mobset();

    ready_to_fight();

    fight();
    


    return 0;
}

char startgame() {
    // 테두리와 초기 메시지 출력
    Draw_boader(0,0,85, 25);

    drawTitle();

    Draw(25, 12, "게임에 오신것을 환영합니다.");
    Draw(30, 14, "1 : 새게임");
    Draw(30, 15, "2 : 불러오기");
    Draw(30, 17, "X : 게임 종료");

    Draw(32, 20, "[     ]");

    
    // 입력 받기
    GotoXY(35, 20);
    char choice = getchar();

    // 결과 출력
    GotoXY(29, 22);
    printf("입력된 값: %c\n", choice);

    return choice;
}

void GotoXY(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Draw(int x, int y, const char* word) {
    GotoXY(x, y);
    printf("%s", word);
}

// 화면 테두리 그리기
void Draw_boader(int stx, int sty, int width, int length) {
    // 상단 및 하단 테두리 그리기
    for (int i = 0; i < width; i++) {
        GotoXY(stx + i, sty);                 // 상단 테두리
        printf("*");
        GotoXY(stx + i, sty + length - 1);     // 하단 테두리
        printf("*");
    }

    // 좌측 및 우측 테두리 그리기
    for (int i = 0; i < length; i++) {
        GotoXY(stx, sty + i);                 // 좌측 테두리
        printf("*");
        GotoXY(stx + width - 1, sty + i);     // 우측 테두리
        printf("*");
    }
}

void display() {
    printf("\n");
}

//시작화면 타이틀
void drawTitle() {
    GotoXY(1, 2);
    printf("                #                               #                                ");
    GotoXY(1, 3);
    printf("                #                               #                                ");
    GotoXY(1, 4);
    printf("                #                               #                                ");
    GotoXY(1, 5);
    printf("  ######   ######  ##   ##   #####   # ####   ######   #     #   # ###    #####  ");
    GotoXY(1, 6);
    printf(" #     #  #     #   #   #   #     #  ##    #    #      #     #   ##      #     # ");
    GotoXY(1, 7);
    printf(" #     #  #     #    # #    #######  #     #    #      #     #   #       ####### ");
    GotoXY(1, 8);
    printf(" #    ##  #     #    # #    #        #     #    #      #    ##   #       #       ");
    GotoXY(1, 9);
    printf("  #### #   ######     #      #####   #     #     ###    #### #   #        #####  ");
                                                            
}


void makec()
{
    ClearScreenWithBorder(0,0,85,25);


    GotoXY(10, 10);
    printf("캐릭터 이름을 입력하세요 : [           ]");
    GotoXY(13, 11);
    printf("( 최대 9자의 영어이름 )");
    GotoXY(38, 10);
    (void)scanf_s("%s", mc1.mcname, (unsigned)_countof(mc1.mcname));
    // 입력 버퍼에 남아있는 줄바꿈 제거
    while (getchar() != '\n');

    status();
    start_give_status();
}

void ClearScreenWithBorder(int stx, int sty, int width, int length) {
    // 화면 지우기
    system("cls");

    // 테두리 그리기
    Draw_boader(stx,sty,width, length);
}

void status()
{
    ClearScreenWithBorder(0,0,85,25);
    GotoXY(35, 2);
    printf("name : %s", mc1.mcname);
    GotoXY(60, 5);
    printf("power : %lf",mc1.power);
    GotoXY(60, 9);
    printf("speed : %lf",mc1.speed);
    GotoXY(60, 13);
    printf("max health : %lf",mc1.maxhp);
    GotoXY(60, 17);
    printf("luck : %lf",mc1.luck);
}

int dice(int x, int y) {
    int dice_num = rand() % 6 + 1;

    GotoXY(x, y);
    printf("┌───────┐");
    GotoXY(x, y + 1);
    printf("│       │");
    GotoXY(x, y + 2);
    printf("│       │");
    GotoXY(x, y + 3);
    printf("│       │");
    GotoXY(x, y + 4);
    printf("└───────┘");

    // 주사위 숫자에 따른 점 출력
    switch (dice_num) {
    case 1:
        GotoXY(x + 4, y + 2);
        printf("●");
        break;
    case 2:
        GotoXY(x + 2, y + 1);
        printf("●");
        GotoXY(x + 6, y + 3);
        printf("●");
        break;
    case 3:
        GotoXY(x + 2, y + 1);
        printf("●");
        GotoXY(x + 4, y + 2);
        printf("●");
        GotoXY(x + 6, y + 3);
        printf("●");
        break;
    case 4:
        GotoXY(x + 2, y + 1);
        printf("●");
        GotoXY(x + 6, y + 1);
        printf("●");
        GotoXY(x + 2, y + 3);
        printf("●");
        GotoXY(x + 6, y + 3);
        printf("●");
        break;
    case 5:
        GotoXY(x + 2, y + 1);
        printf("●");
        GotoXY(x + 6, y + 1);
        printf("●");
        GotoXY(x + 4, y + 2);
        printf("●");
        GotoXY(x + 2, y + 3);
        printf("●");
        GotoXY(x + 6, y + 3);
        printf("●");
        break;
    case 6:
        GotoXY(x + 2, y + 1);
        printf("●");
        GotoXY(x + 6, y + 1);
        printf("●");
        GotoXY(x + 2, y + 2);
        printf("●");
        GotoXY(x + 6, y + 2);
        printf("●");
        GotoXY(x + 2, y + 3);
        printf("●");
        GotoXY(x + 6, y + 3);
        printf("●");
        break;
    }
    return(dice_num);
}

void start_give_status()
{
    int roll_num = 6;
    int tstatus = 0;
    GotoXY(10, 7);
    printf("start stat = ");
    GotoXY(10, 8);
    printf("시작 스탯 결정 = 주사위 여섯번의 합");
    Draw_boader(10, 12, 30, 10);
    GotoXY(10, 10);
    printf("아무키 입력시 주사위 굴림");
    for (int i = 0; i < 6; i++) 
    {
        GotoXY(10, 9);
        printf("남은 주사위 굴림 기회 : %d",roll_num-i);
        (void)_getch();
        tstatus += dice(13, 15);
        GotoXY(10, 7);
        printf("start stat = %d",tstatus);
        
    }
    GotoXY(10, 9);
    printf("남은 주사위 굴림 기회 : 0");
    (void)_getch();
    
    ClearScreenWithBorder(0, 0, 85, 25);
    status();
    Draw_boader(10, 12, 35, 10);
    GotoXY(12, 14);
    printf("힘(a) : power + 2, maxhp + 1");
    GotoXY(12, 15);
    printf("속도(s) : speed + 1");
    GotoXY(12, 16);
    printf("맷집(d) : maxhp + 3");
    GotoXY(12, 17);
    printf("운(f) : luck + 1");
    GotoXY(12, 18);
    printf("기본 제공");
    GotoXY(12, 19);
    printf("power+5,speed+2,maxhp+10,luck+1");
    
    for (int i = 0; i < tstatus; i++)
    {
        
        GotoXY(10, 9);

        if (tstatus - i < 10)
            GotoXY(13, 9);
        printf("start stat = %d", tstatus - i);
        char take_stat = getch();
        switch (take_stat) {
        case 'a': 
            mc1.power += 2;
            mc1.maxhp++;
            break;
        case 's':
            mc1.speed++;
            break;
        case 'd':
            mc1.maxhp += 3;
            break;
        case 'f':
            mc1.luck++;
            break;
        default:
            i--; // 잘못된 입력일 경우 루프를 반복
            continue;
        }
        

        GotoXY(35, 2);
        printf("name : %s", mc1.mcname);
        GotoXY(60, 5);
        printf("power : %lf", mc1.power);
        GotoXY(60, 9);
        printf("speed : %lf", mc1.speed);
        GotoXY(60, 13);
        printf("max health : %lf", mc1.maxhp);
        GotoXY(60, 17);
        printf("luck : %lf", mc1.luck);
    
    }
    

}

void mobset() {
    mob1.level = mc1.level;
    int randmoblevel = rand() % 3;
    mob1.level = mob1.level + randmoblevel;
    mob1.mobpower = 10 + (mob1.level * 2);
    mob1.speed = 3;
    mob1.luck = 10;

    //종에 따른 기본체력 및 방어력 분배....
    char mobnames[][10] = { "고블린", "red슬라임", "오크", "스켈레톤" };

    int plushp = rand() % 4;
    strcpy_s(mob1.mobname, sizeof(mob1.mobname), mobnames[plushp]);
    mob1.mobmaxhp = 50 + (mob1.level * (rand() % 10 + 1)) + (plushp * 10);
    mob1.mobhp = mob1.mobmaxhp;
    mob1.mobdef = 5 + (plushp * 5);

    int randomValue = rand() % 100;

    int weaponpower = 0;

    
    if (randomValue < 50) {
        weaponpower = 0; // 50% 확률
    }
    else if (randomValue < 80) {
        weaponpower = 1; // 30% 확률
    }
    else if (randomValue < 90) {
        weaponpower = 2; // 10% 확률
    }
    else if (randomValue < 96) {
        weaponpower = 3; // 6% 확률
    }
    else if (randomValue < 99) {
        weaponpower = 4; // 3% 확률
    }
    else {
        weaponpower = 5; // 1% 확률
    }

    if (weaponpower == 0) {
        char weapon[][10] = { "X","목검","낡은 철검","한손 방패","양손방패" };
        weaponpower = rand() % 4;
        strcpy_s(mob1.weapon, sizeof(mob1.weapon), weapon[weaponpower]);
    }
    else
        strcpy_s(mob1.weapon, sizeof(mob1.weapon), "X");

    randomValue = rand() % 100;

    int armorpower = 0;


    if (randomValue < 50) {
        armorpower = 0; // 50% 확률
    }
    else if (randomValue < 80) {
        armorpower = 1; // 30% 확률
    }
    else if (randomValue < 90) {
        armorpower = 2; // 10% 확률
    }
    else if (randomValue < 96) {
        armorpower = 3; // 6% 확률
    }
    else if (randomValue < 99) {
        armorpower = 4; // 3% 확률
    }
    else {
        armorpower = 5; // 1% 확률
    }

    if (armorpower == 0) {
        char armors[][10] = { "X","누더기","가죽갑옷","청바지","팔보호대" };
        armorpower = rand() % 4;
        strcpy_s(mob1.mobarmor, sizeof(mob1.mobarmor), armors[armorpower]);
    }
    else
        strcpy_s(mob1.mobarmor, sizeof(mob1.mobarmor), "X");


    //buff
    randomValue = rand() % 100;

    int buffpower = 0;
    if (randomValue < 50) {
        buffpower = 0;
    }
    else if (randomValue < 80) {
        buffpower = 1; 
    }
    else if (randomValue < 90) {
        buffpower = 2; 
    }
    else if (randomValue < 96) {
        buffpower = 3; 
    }
    else if (randomValue < 99) {
        buffpower = 4; 
    }
    else {
        buffpower = 5;
    }
    //buff
    if (buffpower == 0) {
        char buffs[][10] = { "난폭한","차분한","재빠른","둔한" };
        int buffpower = rand() % 4;
        strcpy_s(mob1.buff, sizeof(mob1.buff), buffs[buffpower]);
        switch (buffpower) {
        case 1:
            mob1.mobpower *= 1.2;
            break;
        case 2:
            mob1.mobdef *= 1.1;
            mob1.mobpower *= 1.1;
            break;
        case 3:
            mob1.speed *= 1.2;
            break;
        case 4:
            mob1.mobdef *= 1.2;
            mob1.mobmaxhp *= 1.2;
            mob1.mobhp = mob1.mobmaxhp;
            mob1.speed *= 0.7;
            break;
        }
    }
    else
        strcpy_s(mob1.buff, sizeof(mob1.buff), " ");

}

void ready_to_fight() {
    //monster set
    ClearScreenWithBorder(0, 0, 85, 25);
    GotoXY(2, 3);
    printf("[Lv%d] %s %s",mob1.level, mob1.buff,mob1.mobname);
    GotoXY(2, 4);
    printf("%lf / %lf",mob1.mobhp, mob1.mobmaxhp);
    GotoXY(50, 2);
    printf("무기 : %s, 방어구 : %s", mob1.weapon, mob1.mobarmor);
    GotoXY(50, 3);
    printf("power : %lf", mob1.mobpower);
    GotoXY(50, 4);
    printf("def : %lf", mob1.mobdef);
    GotoXY(50, 5);
    printf("speed : %lf", mob1.speed);
    GotoXY(50, 6);
    printf("luck : %lf", mob1.luck);

    //user
    GotoXY(2, 20);
    printf("[Lv%d] %s %s",mc1.level,mc1.subname ,mc1.mcname);
    GotoXY(2, 21);
    printf("%lf / %lf",mc1.hp, mc1.maxhp);
    GotoXY(55, 19);
    printf("무기 : %s, 방어구 : %s", mc1.weapon, mc1.armor);
    GotoXY(55, 20);
    printf("power : %lf", mc1.power);
    GotoXY(55, 21);
    printf("def : %lf", mc1.userdef);
    GotoXY(55, 22);
    printf("speed : %lf", mc1.speed);
    GotoXY(55, 23);
    printf("luck : %lf", mc1.luck);
}

void fight() {
    Draw_boader(2, 7, 50, 10);
    mc1.next_turn = 100;
    mob1.next_turn = 100;
    GotoXY(2, 5);
    printf("%lf", mob1.next_turn);
    GotoXY(2, 22);
    printf("%lf", mc1.next_turn);
    while (mc1.hp > 0 && mob1.mobhp > 0) {
        onetickturn();
        GotoXY(2, 5);
        printf("%lf", mob1.next_turn);
        GotoXY(2, 22);
        printf("%lf", mc1.next_turn);
        if (mc1.next_turn <= 0 || mob1.next_turn <= 0)
        {
            if (mc1.next_turn < mob1.next_turn)
            {
        
            }
        }
    }
}

void onetickturn() {
    Sleep(1000);
    mc1.next_turn -= mc1.speed;
    mob1.next_turn -= mob1.speed;
}