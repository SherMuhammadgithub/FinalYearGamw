#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;
string setcolor(unsigned short color);
// int blue = 1, green = 2, cyan = 3, red = 4, brown = 6, lightwhite = 7, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, yellow = 14, white = 15;
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
void gotoxy(int, int);
char getCharAtxy(short int x, short int y);
void printBanner();
void loading();
void eraseLoading();
void moveLoading();
void printMaze();
void printPlayer();
void erasePlayer();
void movePlayerLeft();
void movePlayerRight();
void movePlayerup();
void movePlayerDown();
void printEnemyOne();
void eraseEnemyOne();
string enemyOneDirectionControl(string direction);
void moveEnemyOne(string direction);
void printEnemyTwo();
void eraseEnemyTwo();
string enemyTwoDirectionControl(string direction);
void moveEnemyTwo(string direction);
void printEnemyThree();
void eraseEnemyThree();
string enemyThreeDirectionControl(string direction);
void moveEnemyThree(string direction);
void printFire();
int moveFireX1 = 50, moveFireY1 = 1;
int loadingX = 64, loadingY = 29;
int PlayerX = 6, playerY = 29;          // varaibles for player position
int EnemyOneX = 4, EnemyOneY = 1;       // varaibles for EnemyOne position
int EnemyTwoX = 64, EnemyTwoY = 3;      // varaibles for EnemyTwo position
int EnemyThreeX = 16, EnemyThreeY = 14; // varaibles for EnemyThree position
int incraesePower = 3;
//@@@@@@@@@@@
// Player Firing vars
int fireX = 0, fireY = 0;
bool isFire = false;
string fireDirection = "HR";
// player sfiring functions
void printFire();
void moveFire();
// enemy Firing
void enemy1Fire();
void moveEnemy1Fire();
bool enemyOneFire = false;
int enemyOneFireX = 0, enemyOneFireY = 0;
//@@@@@@@@@@@
// enemyTwo firing
void enemy2Fire();
void moveEnemy2Fire();
bool enemyTwoFire = false;
int enemyTwoFireX = 0, enemyTwoFireY = 0;
//@@@@@@@@@@@
// Pump Fire
void pumpFire();
void movePumpFire();
bool pumpFirevar = false;
int pumpFireX = 0, pumpFireY = 0;
void firingPump();
//@@@@@@@@@@@
// printing scoreBoard
void printScoreBoard();
void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

//@@@@@@@@@@@
int enemyOneHealth = 1;
int enemyTwoHealth = 1;
int enemyThreeHealth = 1;
//@@@@@@@@@@@@@
// printing obstacles in the game
void printObstacles()
{
    // abstacle no 1
    setcolor(14);
    gotoxy(17, 5);
    cout << "&&&&&&&&&&                %%%%%%%%%%";
    gotoxy(17, 6);
    cout << "&&&&&&&&&&                %%%%%%%%%%";
    gotoxy(17, 7);
    cout << "&&&&&&&&&&                %%%%%%%%%%";
    setcolor(7);
    setcolor(1);
    gotoxy(17, 11);
    cout << "&&&&&&&&&&                ::::::::::";
    gotoxy(17, 12);
    cout << "&&&&&&&&&&                ::::::::::";
    gotoxy(17, 13);
    cout << "&&&&&&&&&&                ::::::::::";
    setcolor(7);
    // obstacle no 2
    setcolor(10);
    gotoxy(17, 17);
    cout << "&&&&&&&&&&                %%%%%%%%%%";
    gotoxy(17, 18);
    cout << "&&&&&&&&&&                %%%%%%%%%%";
    gotoxy(17, 19);
    cout << "&&&&&&&&&&                %%%%%%%%%%";
    setcolor(7);
    setcolor(6);
    gotoxy(17, 23);
    cout << "&&&&&&&&&&                ::::::::::";
    gotoxy(17, 24);
    cout << "&&&&&&&&&&                ::::::::::";
    gotoxy(17, 25);
    cout << "&&&&&&&&&&                ::::::::::";
    setcolor(7);
}
//@@@@@@@@@@@@@
// dangerous enemy
int dangerousEnemyHealth = 10;
bool isDangerousEnemy = false; // for printing dangerous enemy at certain time
int dangerousEnemyX = 2, dangerousEnemyY = 4;
string dangerousEnemyDirectionControl(string direction)
{
    if (direction == "right" && dangerousEnemyX + 8 == 64)
    {
        direction = "left";
    }
    else if (direction == "left" && dangerousEnemyX == 4)
    {
        direction = "right";
    }
    return direction;
}
void drawDangerousEnemy()
{
    gotoxy(dangerousEnemyX, dangerousEnemyY);
    cout << "  _____  " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 1);
    cout << " /     \\ " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 2);
    cout << "0 >   < 0" << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 3);
    cout << "(   ^   )" << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 4);
    cout << " \\vvvvv/" << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 5);
    cout << "  /   \\  " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 6);
    cout << " /     \\ " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 7);
    cout << "/       \\" << endl;
}
void eraseDangerousEnemy()
{
    gotoxy(dangerousEnemyX, dangerousEnemyY);
    cout << "         " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 1);
    cout << "         " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 2);
    cout << "         " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 3);
    cout << "         " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 4);
    cout << "         " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 5);
    cout << "         " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 6);
    cout << "         " << endl;
    gotoxy(dangerousEnemyX, dangerousEnemyY + 7);
    cout << "         " << endl;
}
void moveDangerousEnemy(string direction)
{
    eraseDangerousEnemy();
    if (direction == "left" && getCharAtxy(dangerousEnemyX - 1, dangerousEnemyY) == ' ' && getCharAtxy(dangerousEnemyX - 1, dangerousEnemyY + 1) && getCharAtxy(dangerousEnemyX - 1, dangerousEnemyY + 2) == ' ' && getCharAtxy(dangerousEnemyX - 1, dangerousEnemyY + 3) && getCharAtxy(dangerousEnemyX - 1, dangerousEnemyY + 4) == ' ' && getCharAtxy(dangerousEnemyX - 1, dangerousEnemyY + 5) && getCharAtxy(dangerousEnemyX - 1, dangerousEnemyY + 6) == ' ' && getCharAtxy(dangerousEnemyX - 1, dangerousEnemyY + 7) == ' ')
    {
        dangerousEnemyX -= 1;
    }
    else if (direction == "right" && getCharAtxy(dangerousEnemyX + 10, dangerousEnemyY) == ' ' && getCharAtxy(dangerousEnemyX + 10, dangerousEnemyY + 10) && getCharAtxy(dangerousEnemyX + 10, dangerousEnemyY + 2) == ' ' && getCharAtxy(dangerousEnemyX + 10, dangerousEnemyY + 3) && getCharAtxy(dangerousEnemyX + 10, dangerousEnemyY + 4) == ' ' && getCharAtxy(dangerousEnemyX + 10, dangerousEnemyY + 5) && getCharAtxy(dangerousEnemyX + 10, dangerousEnemyY + 6) == ' ' && getCharAtxy(dangerousEnemyX + 10, dangerousEnemyY + 7) == ' ')
    {
        dangerousEnemyX += 1;
    }
    drawDangerousEnemy();
}
//@@@@@@@@@@@@@
// dangerouly enemy frirng
void dangerousEnemyFire();
void moveDangerousEnemyFire();
bool dangerousEnemyFireVar = false;
int dangerousEnemyFireX = 0, dangerousEnemyFireY = 0;
void dangerousEnemyFire()
{
    dangerousEnemyFireX = dangerousEnemyX + 4;
    dangerousEnemyFireY = dangerousEnemyY + 5;
    gotoxy(dangerousEnemyFireX, dangerousEnemyFireY);
    setcolor(4);
    cout << "vvv";
    setcolor(7);
}
void moveDangerousEnemyFire()
{
    gotoxy(dangerousEnemyFireX, dangerousEnemyFireY);
    cout << "   ";
    if (getCharAtxy(dangerousEnemyFireX, dangerousEnemyFireY + 2) == ' ')
    {
        dangerousEnemyFireY += 1;
        gotoxy(dangerousEnemyFireX, dangerousEnemyFireY);
        setcolor(4);
        cout << "vvv";
        setcolor(7);
    }
    else if (getCharAtxy(dangerousEnemyFireX, dangerousEnemyFireY + 2) == '(' || getCharAtxy(dangerousEnemyFireX, dangerousEnemyFireY + 2) == '/' || getCharAtxy(dangerousEnemyFireX, dangerousEnemyFireY + 2) == '\\' || getCharAtxy(dangerousEnemyFireX, dangerousEnemyFireY + 2) == 'p' || getCharAtxy(dangerousEnemyFireX, dangerousEnemyFireY + 2) == ')' || getCharAtxy(dangerousEnemyFireX, dangerousEnemyFireY + 2) == '|')
    {
        gotoxy(dangerousEnemyFireX, dangerousEnemyFireY + 1);
        incraesePower -= 5;
        dangerousEnemyHealth += 5;
        gotoxy(92, 3);
        cout << incraesePower << " ";
        gotoxy(92, 15);
        cout << dangerousEnemyHealth << " ";
        cout << "   ";
        dangerousEnemyFireVar = false;
    }
    else
    {
        gotoxy(dangerousEnemyFireX, dangerousEnemyFireY + 1);
        cout << "   ";
        dangerousEnemyFireVar = false;
    }
}
main()
{

    string choices;
    // printBanner();
    // loading();
    // int i = 1;
    // while (i <= 40)
    // {
    //     moveLoading();
    //     Sleep(100);
    //     if (i == 40)
    //     {
    //         cout << setw(10) << "Loading Completed";
    //     }
    //     i++;
    // }

    // sleep_for(seconds(3));
    Sleep(700);
    system("cls");
    string dangerEnemyDirection = "right";
    string enemyOneIntialDirection = "right";
    string enemyTwoIntialDirection = "down";
    string enemyThreeIntialDirection = "right";
    // drawDangerousEnemy();
start:
    printMaze();
    if (!isDangerousEnemy)
    {
        printObstacles();
        printEnemyOne();
        printEnemyTwo();
        printEnemyThree();
    }
    else
    {
        drawDangerousEnemy();
    }
    printPlayer();
    firingPump();
    printScoreBoard();
    hideCursor();
    while (true)
    {
        if (!isDangerousEnemy) // printing smaller enemies intially and then printing dangerous enemy
        {

            if (enemyOneHealth > 0)
            {
                enemyOneIntialDirection = enemyOneDirectionControl(enemyOneIntialDirection);
                moveEnemyOne(enemyOneIntialDirection);
            }
            if (enemyTwoHealth > 0)
            {

                enemyTwoIntialDirection = enemyTwoDirectionControl(enemyTwoIntialDirection);
                moveEnemyTwo(enemyTwoIntialDirection);
            }
            if (enemyThreeHealth > 0)
            {
                enemyThreeIntialDirection = enemyThreeDirectionControl(enemyThreeIntialDirection);
                moveEnemyThree(enemyThreeIntialDirection);
            }
        }
        else
        {
            dangerEnemyDirection = dangerousEnemyDirectionControl(dangerEnemyDirection);
            moveDangerousEnemy(dangerEnemyDirection);
        }

        if (GetAsyncKeyState(VK_LEFT))
        {
            movePlayerLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            movePlayerRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            movePlayerup();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            movePlayerDown();
        }
        if (GetAsyncKeyState('A'))
        {
            if (isFire == false)
            {
                fireDirection = "HL"; // horizontal Left
                printPlayer();
            }
        }
        if (GetAsyncKeyState('D'))
        {
            if (isFire == false)
            {
                fireDirection = "HR"; // horizontal right
                printPlayer();
            }
        }
        if (GetAsyncKeyState('W'))
        {
            if (isFire == false)
            {
                fireDirection = "UP";
                printPlayer();
            }
        }

        if (GetAsyncKeyState(VK_SPACE))
        {
            if (isFire == false) // stopping for overhitting the fire
            {
                printFire();
                isFire = true;
            }
        }
        if (isFire)
        {
            moveFire();
        }
        // fire Through Enemies
        if (!enemyOneFire && enemyOneHealth > 0)
        {
            enemy1Fire();
            enemyOneFire = true;
        }
        if (enemyOneFire)
        {
            moveEnemy1Fire();
        }
        if (!enemyTwoFire && enemyTwoHealth > 0)
        {
            enemy2Fire();
            enemyTwoFire = true;
        }
        if (enemyTwoFire)
        {
            moveEnemy2Fire();
        }
        // fire Through Pump
        if (!pumpFirevar)
        {
            pumpFire();
            pumpFirevar = true;
        }
        if (pumpFirevar)
        {
            movePumpFire();
        }

        // check for enemy died
        if (enemyOneHealth == 0)
        {
            eraseEnemyOne();
        }
        if (enemyTwoHealth == 0)
        {
            eraseEnemyTwo();
        }
        if (enemyThreeHealth == 0)
        {
            eraseEnemyThree();
        }
        // checking for win or lose
        if (incraesePower <= 0)
        {
            system("cls");
            cout << "You lose" << endl;
            break;
        }
        if (enemyOneHealth == 0 && enemyTwoHealth == 0 && enemyThreeHealth == 0 && isDangerousEnemy == false)
        {
            gotoxy(50, 20);
            cout << "Monster has come!!!" << endl;
            Sleep(1000);
            system("cls");
            isDangerousEnemy = true;
            goto start;
            // break;
        }
        // fire through dangerous enemy
        if (!dangerousEnemyFireVar && isDangerousEnemy)
        {
            dangerousEnemyFire();
            dangerousEnemyFireVar = true;
        }
        if (dangerousEnemyFireVar)
        {
            moveDangerousEnemyFire();
        }
        // declaring a winner
        if (dangerousEnemyHealth <= 0)
        {
            system("cls");
            cout << "You Win" << endl;
            break;
        }
        Sleep(100);
    }
}
void printBanner()
{
    system("cls");
    string choice;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(100) << "  __  __ _____ _____  _    _          ____  _    _   _  ____" << endl;
    cout << setw(100) << "|  \\/  | ____|_   _|/ \\  | |        / ___|| |  | | | |/ ___|" << endl;
    cout << setw(100) << "| |\\/| |  _|   | | / _ \\ | |        \\___ \\| |  | | | | |  _ " << endl;
    cout << setw(100) << "| |  | | |___  | |/ ___ \\| |___      ___) | |__| |_| | |_| |" << endl;
    cout << setw(100) << "|_|  |_|_____| |_/_/   \\_\\_____|    |____/|_____\\___/ \\____|" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(100) << "                                                          #    " << endl;
    cout << setw(100) << "  @########(((((((((((((((((#(((#((((((#((((((#######(#(##     " << endl;
    cout << setw(100) << " %@(###%@(###((##&(##(#######(##(((((((((#######%#########     " << endl;
    cout << setw(100) << "  @####################%@@@@(##((#######(######%&####%###%     " << endl;
    cout << setw(100) << "  %&%######(#(#&%#%#%%#%%##@%&%##%#%#%#&&&#&#######%%&&&&&&    " << endl;
    cout << setw(100) << "   %%%&&&&&&&&%&%%%%%%%%%%%#(%%%%%%%%#####%%%%%%%#%&&&%        " << endl;
    cout << setw(100) << "                    %#@        &&@@&%&%##########%%&@&         " << endl;
    cout << setw(100) << "                     %%       &##@@ %@&%%%%####%%##&@&         " << endl;
    cout << setw(100) << "                    /##     #&##   #%%@@&&%%%#(#%%%&&@%        " << endl;
    cout << setw(100) << "                    %&&&&&&&%&%%%%#   %&&&&%##%%(%%#&&&%       " << endl;
    cout << setw(100) << "                                       %%&%&(#%%%%&(&&%%##     " << endl;
    cout << setw(100) << "                                       %&%&%&#%%%%%%%%%&#%&/   " << endl;
    cout << setw(100) << "                                         %&&%&&&%#%&&&&&(%&%%  " << endl;
    cout << setw(100) << "                                          @&%%%%&%(&#%%%%#%&%% " << endl;
    cout << setw(100) << "                                           &%%%%&#&%&%%%%%&%@@(" << endl;
    cout << setw(100) << "                                            %&%#%%#%%%&%&@,    " << endl;
    cout << setw(100) << "                                             (%&%%%%&&%%#/" << endl;
}
void loading()
{
    gotoxy(loadingX, loadingY);
    cout << "__ __";
}
void eraseLoading()
{
    gotoxy(loadingX, loadingY);
    cout << "";
}
void moveLoading()
{
    // loading();
    eraseLoading();
    loadingX += 1;
    if (loadingX == 80)
    {
        loadingY == 64;
    }
    loading();
}

void printMaze()
{

    cout << "#######################################################################" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                         .                                           #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "##############################################################        #" << endl;
    cout << "                                                                .     #" << endl;
    cout << "                                      .                               #" << endl;
    cout << "                                                                      #" << endl;
    cout << "#######################################################################" << endl;
}
void printPlayer()
{
    if (fireDirection == "HR")
    {
        setcolor(10);
        gotoxy(PlayerX, playerY);
        cout << "(p)" << endl;
        gotoxy(PlayerX, playerY + 1);
        cout << "/|>" << endl;
        gotoxy(PlayerX, playerY + 2);
        cout << "/ \\" << endl;
        setcolor(7);
    }
    else if (fireDirection == "HL")
    {
        setcolor(14);
        gotoxy(PlayerX, playerY);
        cout << "(p)" << endl;
        gotoxy(PlayerX, playerY + 1);
        cout << "<|\\" << endl;
        gotoxy(PlayerX, playerY + 2);
        cout << "/ \\" << endl;
        setcolor(7);
    }
    else if (fireDirection == "UP")
    {
        setcolor(6);
        gotoxy(PlayerX, playerY);
        cout << "|p|" << endl;
        gotoxy(PlayerX, playerY + 1);
        cout << "/|\\" << endl;
        gotoxy(PlayerX, playerY + 2);
        cout << "/ \\" << endl;
        setcolor(7);
    }
}
void erasePlayer()
{
    gotoxy(PlayerX, playerY);
    cout << "   ";
    gotoxy(PlayerX, playerY + 1);
    cout << "   ";
    gotoxy(PlayerX, playerY + 2);
    cout << "   ";
}

void movePlayerLeft()
{

    if (getCharAtxy(PlayerX - 1, playerY) == ' ' && getCharAtxy(PlayerX - 1, playerY + 1) == ' ' && getCharAtxy(PlayerX - 1, playerY + 2) == ' ')
    {
        erasePlayer();
        PlayerX = PlayerX - 1;
        printPlayer();
    }
    if (getCharAtxy(PlayerX - 1, playerY) == '.' || getCharAtxy(PlayerX - 1, playerY + 1) == '.' || getCharAtxy(PlayerX - 1, playerY + 2) == '.')
    {
        erasePlayer();
        PlayerX = PlayerX - 1;
        incraesePower++;
        gotoxy(92, 3);
        cout << incraesePower;
        printPlayer();
    }
}
void movePlayerRight()
{

    if (getCharAtxy(PlayerX + 3, playerY) == ' ' && getCharAtxy(PlayerX + 3, playerY + 1) == ' ' && getCharAtxy(PlayerX + 3, playerY + 2) == ' ')
    {
        erasePlayer();
        PlayerX = PlayerX + 1;

        printPlayer();
    }
    else if (getCharAtxy(PlayerX + 3, playerY) == '.' || getCharAtxy(PlayerX + 3, playerY + 1) == '.' || getCharAtxy(PlayerX + 3, playerY + 2) == '.')
    {
        erasePlayer();
        PlayerX = PlayerX + 1;
        incraesePower++;
        gotoxy(92, 3);
        cout << incraesePower;
        printPlayer();
    }
}

void movePlayerup()
{
    if (getCharAtxy(PlayerX, playerY - 1) == ' ' && getCharAtxy(PlayerX + 1, playerY - 1) == ' ' && getCharAtxy(PlayerX + 2, playerY - 1) == ' ')
    {
        erasePlayer();
        playerY = playerY - 1;
        printPlayer();
    }
    if (getCharAtxy(PlayerX, playerY - 1) == '.' || getCharAtxy(PlayerX + 1, playerY - 1) == '.' || getCharAtxy(PlayerX + 2, playerY - 1) == '.')
    {
        erasePlayer();
        playerY = playerY - 1;
        incraesePower++;
        printPlayer();
    }
}
void movePlayerDown()
{
    if (getCharAtxy(PlayerX, playerY + 3) == ' ' && getCharAtxy(PlayerX + 1, playerY + 3) == ' ' && getCharAtxy(PlayerX + 2, playerY + 3) == ' ')
    {
        erasePlayer();
        playerY = playerY + 1;
        printPlayer();
    }
    if (getCharAtxy(PlayerX, playerY + 3) == '.' || getCharAtxy(PlayerX + 1, playerY + 3) == '.' || getCharAtxy(PlayerX + 2, playerY + 3) == '.')
    {
        erasePlayer();
        playerY = playerY;
        incraesePower++;
        gotoxy(92, 3);
        cout << incraesePower;
        printPlayer();
    }
}
void printEnemyOne()
{
    setcolor(4);
    gotoxy(EnemyOneX, EnemyOneY);
    cout << "   _   " << endl;
    gotoxy(EnemyOneX, EnemyOneY + 1);
    cout << "  + +  " << endl;
    gotoxy(EnemyOneX, EnemyOneY + 2);
    cout << "++_v_++" << endl;
    setcolor(7);
}
void eraseEnemyOne()
{
    gotoxy(EnemyOneX, EnemyOneY);
    cout << "       ";
    gotoxy(EnemyOneX, EnemyOneY + 1);
    cout << "       ";
    gotoxy(EnemyOneX, EnemyOneY + 2);
    cout << "       ";
}
string enemyOneDirectionControl(string direction)
{
    if (EnemyOneX + 3 == 64 && direction == "right")
    {

        direction = "left";
    }
    else if (EnemyOneX == 4 && direction == "left")
    {
        direction = "right";
    }
    return direction;
}
void moveEnemyOne(string direction)
{
    eraseEnemyOne();
    if (direction == "left" && getCharAtxy(EnemyOneX - 1, EnemyOneY) == ' ' && getCharAtxy(EnemyOneX - 1, EnemyOneY + 1) == ' ' && getCharAtxy(EnemyOneX - 1, EnemyOneY + 2) == ' ')
    {
        EnemyOneX -= 1;
    }
    else if (direction == "right" && getCharAtxy(EnemyOneX + 8, EnemyOneY) == ' ' && getCharAtxy(EnemyOneX + 8, EnemyOneY + 1) == ' ' && getCharAtxy(EnemyOneX + 8, EnemyOneY + 2) == ' ')
    {
        EnemyOneX += 1;
    }
    printEnemyOne();
}
void enemy1Fire()
{
    enemyOneFireX = EnemyOneX + 3;
    enemyOneFireY = EnemyOneY + 2;
    gotoxy(enemyOneFireX, enemyOneFireY);
    setcolor(4);
    cout << "v";
    setcolor(7);
}
void moveEnemy1Fire()
{
    gotoxy(enemyOneFireX, enemyOneFireY);
    cout << " ";
    if (getCharAtxy(enemyOneFireX, enemyOneFireY + 2) == ' ')
    {
        enemyOneFireY += 1;
        gotoxy(enemyOneFireX, enemyOneFireY);
        setcolor(4);
        cout << "v";
        setcolor(7);
    }
    else if (getCharAtxy(enemyOneFireX, enemyOneFireY + 2) == '(' || getCharAtxy(enemyOneFireX, enemyOneFireY + 2) == '/' || getCharAtxy(enemyOneFireX, enemyOneFireY + 2) == '\\' || getCharAtxy(enemyOneFireX, enemyOneFireY + 2) == 'p' || getCharAtxy(enemyOneFireX, enemyOneFireY + 2) == ')' || getCharAtxy(enemyOneFireX, enemyOneFireY + 2) == '|')
    {
        gotoxy(enemyOneFireX, enemyOneFireY + 1);
        incraesePower--;
        gotoxy(92, 3);
        cout << incraesePower;
        cout << " ";
        enemyOneFire = false;
    }
    else
    {
        gotoxy(enemyOneFireX, enemyOneFireY + 1);
        cout << " ";
        enemyOneFire = false;
    }
}
void printEnemyTwo()
{
    setcolor(1);
    gotoxy(EnemyTwoX, EnemyTwoY);
    cout << "<E>" << endl;
    gotoxy(EnemyTwoX, EnemyTwoY + 1);
    cout << "(|)" << endl;
    gotoxy(EnemyTwoX, EnemyTwoY + 2);
    cout << "?v?" << endl;
    setcolor(7);
}
void eraseEnemyTwo()
{
    gotoxy(EnemyTwoX, EnemyTwoY);
    cout << "   ";
    gotoxy(EnemyTwoX, EnemyTwoY + 1);
    cout << "   ";
    gotoxy(EnemyTwoX, EnemyTwoY + 2);
    cout << "   ";
}
string enemyTwoDirectionControl(string direction)
{
    if (EnemyTwoY + 3 == 29 && direction == "down")
    {
        direction = "up";
    }
    else if (EnemyTwoY == 3 && direction == "up")
    {
        direction = "down";
    }
    return direction;
}
void moveEnemyTwo(string direction)
{
    eraseEnemyTwo();
    if (direction == "up" && getCharAtxy(EnemyTwoX, EnemyTwoY - 1) == ' ' && getCharAtxy(EnemyTwoX + 1, EnemyTwoY - 1) == ' ' && getCharAtxy(EnemyTwoX + 2, EnemyTwoY - 1) == ' ')
    {
        EnemyTwoY -= 1;
    }
    else if (direction == "down" && getCharAtxy(EnemyTwoX, EnemyTwoY + 3) == ' ' && getCharAtxy(EnemyTwoX + 1, EnemyTwoY + 3) == ' ' && getCharAtxy(EnemyTwoX + 2, EnemyTwoY + 3) == ' ')
    {
        EnemyTwoY += 1;
    }
    printEnemyTwo();
}
void enemy2Fire()
{
    enemyTwoFireX = EnemyTwoX + 1;
    enemyTwoFireY = EnemyTwoY - 2;
    gotoxy(enemyTwoFireX, enemyTwoFireY);
    setcolor(8);
    cout << "<";
    setcolor(7);
}
void moveEnemy2Fire()
{
    gotoxy(enemyTwoFireX, enemyTwoFireY);
    cout << " ";
    if (getCharAtxy(enemyTwoFireX - 2, enemyTwoFireY) == ' ')
    {
        enemyTwoFireX -= 1;
        gotoxy(enemyTwoFireX, enemyTwoFireY);
        setcolor(1);
        cout << "<";
        setcolor(7);
    }
    else if (getCharAtxy(enemyTwoFireX - 2, enemyTwoFireY) == '(' || getCharAtxy(enemyTwoFireX - 2, enemyTwoFireY) == '/' || getCharAtxy(enemyTwoFireX - 2, enemyTwoFireY) == '\\' || getCharAtxy(enemyTwoFireX - 2, enemyTwoFireY) == 'p' || getCharAtxy(enemyTwoFireX - 2, enemyTwoFireY) == ')' || getCharAtxy(enemyTwoFireX - 2, enemyTwoFireY) == '|')
    {
        gotoxy(enemyTwoFireX - 1, enemyTwoFireY);
        incraesePower--;
        gotoxy(92, 3);
        cout << incraesePower;
        cout << " ";
        enemyTwoFire = false;
    }
    else
    {
        gotoxy(enemyTwoFireX - 1, enemyTwoFireY);
        cout << " ";
        enemyTwoFire = false;
    }
}
void printEnemyThree()
{
    gotoxy(EnemyThreeX, EnemyThreeY);
    cout << "0E0" << endl;
    gotoxy(EnemyThreeX, EnemyThreeY + 1);
    cout << "{|}" << endl;
    gotoxy(EnemyThreeX, EnemyThreeY + 2);
    cout << "I^I" << endl;
}

void eraseEnemyThree()
{
    gotoxy(EnemyThreeX, EnemyThreeY);
    cout << "   ";
    gotoxy(EnemyThreeX, EnemyThreeY + 1);
    cout << "   ";
    gotoxy(EnemyThreeX, EnemyThreeY + 2);
    cout << "   ";
}
string enemyThreeDirectionControl(string direction)
{

    if (EnemyThreeX + 3 == 64 && direction == "right")
    {
        direction = "left";
    }
    else if (EnemyThreeX == 4 && direction == "left")
    {
        direction = "right";
    }
    return direction;
}
void moveEnemyThree(string direction)
{
    eraseEnemyThree();
    if (direction == "left" && getCharAtxy(EnemyThreeX - 1, EnemyThreeY) == ' ' && getCharAtxy(EnemyThreeX - 1, EnemyThreeY + 1) == ' ' && getCharAtxy(EnemyThreeX - 1, EnemyThreeY + 2) == ' ')
    {
        EnemyThreeX -= 1;
    }
    else if (direction == "right" && getCharAtxy(EnemyThreeX + 3, EnemyThreeY) == ' ' && getCharAtxy(EnemyThreeX + 3, EnemyThreeY + 1) == ' ' && getCharAtxy(EnemyThreeX + 3, EnemyThreeY + 2) == ' ')
    {
        EnemyThreeX += 1;
    }
    printEnemyThree();
}
void pumpFire()
{
    pumpFireX = 8;
    pumpFireY = 20;
    gotoxy(pumpFireX, pumpFireY);
    setcolor(10);
    cout << ">";
    setcolor(7);
}
void movePumpFire()
{
    gotoxy(pumpFireX, pumpFireY);
    cout << " ";
    if (getCharAtxy(pumpFireX + 2, pumpFireY) == ' ')
    {
        pumpFireX += 1;
        gotoxy(pumpFireX, pumpFireY);
        setcolor(10);
        cout << ">";
        setcolor(7);
    }
    else if (getCharAtxy(pumpFireX + 2, pumpFireY) == '(' || getCharAtxy(pumpFireX + 2, pumpFireY) == '/' || getCharAtxy(pumpFireX + 2, pumpFireY) == '\\' || getCharAtxy(pumpFireX + 2, pumpFireY) == 'p' || getCharAtxy(pumpFireX + 2, pumpFireY) == ')' || getCharAtxy(pumpFireX + 2, pumpFireY) == '|')
    {
        gotoxy(pumpFireX + 1, pumpFireY);
        incraesePower--;
        gotoxy(92, 3);
        cout << incraesePower;
        cout << " ";
        pumpFirevar = false;
    }
    else
    {
        gotoxy(pumpFireX + 1, pumpFireY);
        cout << " ";
        pumpFirevar = false;
    }
}
void firingPump()
{
    setcolor(1);
    gotoxy(2, 19);
    cout << "###__";
    gotoxy(2, 20);
    cout << "###__";
    gotoxy(2, 21);
    cout << "###";
    setcolor(7);
}
void printPower()
{
    gotoxy(92, 2);
    cout << ":Power:" << endl;
}
void printFire()
{
    if (fireDirection == "HR")
    {
        fireX = PlayerX + 2;
        fireY = playerY + 1;
        gotoxy(fireX, fireY);
        cout << "*";
    }
    else if (fireDirection == "HL")
    {
        fireX = PlayerX - 2;
        fireY = playerY + 1;
        gotoxy(fireX, fireY);
        cout << "*";
    }
    else if (fireDirection == "UP")
    {
        fireX = PlayerX + 2;
        fireY = playerY - 1;
        gotoxy(fireX, fireY);
        cout << "*";
    }
}

void moveFire()
{
    if (fireDirection == "HL")
    {
        gotoxy(fireX, fireY);
        cout << " ";
        if (getCharAtxy(fireX - 2, fireY) == ' ')
        {
            fireX -= 1;
            gotoxy(fireX, fireY);
            cout << "*";
        }
        else if (getCharAtxy(fireX - 2, fireY) == '+')
        {
            incraesePower++;
            enemyOneHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 6);
            cout << enemyOneHealth;
            gotoxy(fireX - 1, fireY);
            cout << " ";
            isFire = false;
        }
        else if (getCharAtxy(fireX - 2, fireY) == '}' || getCharAtxy(fireX - 2, fireY) == 'I' || getCharAtxy(fireX - 2, fireY) == '|')
        {
            incraesePower++;
            enemyThreeHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 12);
            cout << enemyThreeHealth;
            gotoxy(fireX - 1, fireY);
            cout << " ";
            isFire = false;
        }
        else if (getCharAtxy(fireX - 2, fireY) == '>' || getCharAtxy(fireX - 2, fireY) == ')' || getCharAtxy(fireX - 2, fireY) == '?')
        {
            incraesePower++;
            enemyTwoHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 9);
            cout << enemyTwoHealth;
            gotoxy(fireX - 1, fireY);
            cout << " ";
            isFire = false;
        }
        else if (getCharAtxy(fireX - 2, fireY) == '/' || getCharAtxy(fireX - 2, fireY) == '\\' || getCharAtxy(fireX - 2, fireY) == ')' || getCharAtxy(fireX - 2, fireY) == '0')
        {
            incraesePower++;
            dangerousEnemyHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 15);
            cout << dangerousEnemyHealth;
            gotoxy(fireX - 2, fireY);
            cout << " ";
            dangerousEnemyFireVar = false;
        }
        else
        {
            gotoxy(fireX - 1, fireY);
            cout << " ";
            isFire = false;
        }
    }
    else if (fireDirection == "HR")
    {
        gotoxy(fireX, fireY);
        cout << " ";

        if (getCharAtxy(fireX + 2, fireY) == ' ')
        {
            fireX += 1;
            gotoxy(fireX, fireY);
            cout << "*";
        }
        else if (getCharAtxy(fireX + 2, fireY) == '+')
        {
            incraesePower++;
            enemyOneHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 6);
            cout << enemyOneHealth;
            gotoxy(fireX + 1, fireY);
            cout << " ";
            isFire = false;
        }
        else if (getCharAtxy(fireX + 2, fireY) == '0' || getCharAtxy(fireX + 2, fireY) == '{' || getCharAtxy(fireX + 2, fireY) == 'I')
        {
            incraesePower++;
            enemyThreeHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 12);
            cout << enemyThreeHealth;
            gotoxy(fireX + 1, fireY);
            cout << " ";
            isFire = false;
        }
        else if (getCharAtxy(fireX + 2, fireY) == '<' || getCharAtxy(fireX + 2, fireY) == '(' || getCharAtxy(fireX + 2, fireY) == '?')
        {
            incraesePower++;
            enemyTwoHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 9);
            cout << enemyTwoHealth;
            gotoxy(fireX + 1, fireY);
            cout << " ";
            isFire = false;
        }
        else if (getCharAtxy(fireX - 2, fireY) == '/' || getCharAtxy(fireX - 2, fireY) == '\\' || getCharAtxy(fireX - 2, fireY) == '(' || getCharAtxy(fireX - 2, fireY) == '0')
        {
            incraesePower++;
            dangerousEnemyHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 15);
            cout << dangerousEnemyHealth;
            gotoxy(fireX - 1, fireY);
            cout << " ";
            dangerousEnemyFireVar = false;
        }
        else
        {
            gotoxy(fireX + 1, fireY);
            cout << " ";
            isFire = false;
        }
    }
    else if (fireDirection == "UP")
    {
        gotoxy(fireX, fireY);
        cout << " ";
        if (getCharAtxy(fireX, fireY - 2) == ' ')
        {
            fireY -= 1;
            gotoxy(fireX, fireY);
            cout << "*";
        }
        else if (getCharAtxy(fireX - 2, fireY) == '_' || getCharAtxy(fireX, fireY - 2) == '+')
        {
            incraesePower++;
            enemyOneHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 6);
            cout << enemyOneHealth;
            gotoxy(fireX, fireY - 1);
            cout << " ";
            isFire = false;
        }
        else if (getCharAtxy(fireX, fireY - 2) == '^')
        {
            incraesePower++;
            enemyThreeHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 12);
            cout << enemyThreeHealth;
            gotoxy(fireX, fireY - 1);
            cout << " ";
            isFire = false;
        }
        else if (getCharAtxy(fireX, fireY - 2) == 'v' || getCharAtxy(fireX - 2, fireY) == '.')
        {
            incraesePower++;
            enemyTwoHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 9);
            cout << enemyTwoHealth;
            gotoxy(fireX, fireY - 1);
            cout << " ";
            isFire = false;
        }
        else if (getCharAtxy(fireX - 2, fireY) == '/' || getCharAtxy(fireX - 2, fireY) == '\\' || getCharAtxy(fireX - 2, fireY) == 'v')
        {
            incraesePower++;
            dangerousEnemyHealth--;
            gotoxy(92, 3);
            cout << incraesePower;
            gotoxy(92, 15);
            cout << dangerousEnemyHealth;
            gotoxy(fireX - 1, fireY);
            cout << " ";
            dangerousEnemyFireVar = false;
        }
        else
        {
            gotoxy(fireX, fireY - 1);
            cout << " ";
            isFire = false;
        }
    }
    else if (fireDirection == "DOWN")
    {
        gotoxy(fireX, fireY);
        cout << " ";
        gotoxy(fireX + 1, fireY);
        cout << "*";
        fireY += 1;
    }
}
void printScoreBoard()
{
    setcolor(4);
    gotoxy(92, 2);
    cout << ":Power:" << endl;
    gotoxy(92, 3);
    cout << incraesePower << endl;
    gotoxy(92, 5);
    cout << ":Enemy One:" << endl;
    gotoxy(92, 6);
    cout << enemyOneHealth << endl;
    gotoxy(92, 8);
    cout << ":Enemy Two:" << endl;
    gotoxy(92, 9);
    cout << enemyTwoHealth << endl;
    gotoxy(92, 11);
    cout << ":Enemy Three:" << endl;
    gotoxy(92, 12);
    cout << enemyThreeHealth << endl;
    gotoxy(92, 14);
    cout << ":Enemy Three:" << endl;
    gotoxy(92, 15);
    cout << dangerousEnemyHealth << endl;
    setcolor(7);
}
// built in funtionality
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
// built in funtionality for moving plyer with arrow keys
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}