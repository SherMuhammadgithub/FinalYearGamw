#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;
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
void printPower();
void eraseFire();
string fireOneDirectionControl(string direction);
int moveFireX1 = 50, moveFireY1 = 1;
int loadingX = 64, loadingY = 29;
int PlayerX = 6, playerY = 29;          // varaibles for player position
int EnemyOneX = 4, EnemyOneY = 1;       // varaibles for EnemyOne position
int EnemyTwoX = 64, EnemyTwoY = 3;      // varaibles for EnemyTwo position
int EnemyThreeX = 16, EnemyThreeY = 13; // varaibles for EnemyThree position
int incraesePower = 0;
//@@@@@@@@@@@
// Player Firing vars
int fireX = 0, fireY = 0;
bool isFire = false;
string fireDirection = "HR";
// player sfiring functions
void printFire();
void moveFire();
// enemy Firing

main()
{
    string choices;
    printBanner();
    loading();
    int i = 1;
    while (i <= 40)
    {
        moveLoading();
        Sleep(100);
        if (i == 40)
        {
            cout << setw(10) << "Loading Completed";
        }
        i++;
    }

    // sleep_for(seconds(3));
    Sleep(700);
    system("cls");
    string enemyOneIntialDirection = "right";
    string enemyTwoIntialDirection = "down";
    string enemyThreeIntialDirection = "right";
    // system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
    printMaze();
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    printEnemyOne();
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
    printEnemyTwo();
    printEnemyThree();
    printPlayer();
    printPower();

    while (true)
    {

        enemyOneIntialDirection = enemyOneDirectionControl(enemyOneIntialDirection);
        moveEnemyOne(enemyOneIntialDirection);
        enemyTwoIntialDirection = enemyTwoDirectionControl(enemyTwoIntialDirection);
        moveEnemyTwo(enemyTwoIntialDirection);
        enemyThreeIntialDirection = enemyThreeDirectionControl(enemyThreeIntialDirection);
        moveEnemyThree(enemyThreeIntialDirection);
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
                fireDirection = "HL";
                printPlayer();
            }
        }
        if (GetAsyncKeyState('D'))
        {
            if (isFire == false)
            {
                fireDirection = "HR";
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
    cout << "#          ##################################################         #" << endl;
    cout << "#          #         #########         ########             #         #" << endl;
    cout << "#          #         #$$$$$$$#         #$$$$$$#             #         #" << endl;
    cout << "#                                                           #         #" << endl;
    cout << "#                                                           #         #" << endl;
    cout << "#                                                           #         #" << endl;
    cout << "#          #         &&&&&&&&          &&&&&&&&             #         #" << endl;
    cout << "#          #         %%%%%%%%          %%%%%%%%             #         #" << endl;
    cout << "#          ##################################################         #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#                                                                     #" << endl;
    cout << "#          ##################################################         #" << endl;
    cout << "#          #        ##########         ########             #         #" << endl;
    cout << "#          #        #$$$$$$$$#         #$$$$$$#             #         #" << endl;
    cout << "#                                                           #         #" << endl;
    cout << "#                                                           #         #" << endl;
    cout << "#                                                           #         #" << endl;
    cout << "#          #         $$$$$$$$$         $$$$$$$$             #         #" << endl;
    cout << "#          #         %%%%%%%%%         %%%%%%%%             #         #" << endl;
    cout << "#          ##################################################         #" << endl;
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
        gotoxy(PlayerX, playerY);
        cout << "(p)" << endl;
        gotoxy(PlayerX, playerY + 1);
        cout << "/|>" << endl;
        gotoxy(PlayerX, playerY + 2);
        cout << "/ \\" << endl;
    }
    else if (fireDirection == "HL")
    {
        gotoxy(PlayerX, playerY);
        cout << "(p)" << endl;
        gotoxy(PlayerX, playerY + 1);
        cout << "<|\\" << endl;
        gotoxy(PlayerX, playerY + 2);
        cout << "/ \\" << endl;
    }
    else if (fireDirection == "UP")
    {
        gotoxy(PlayerX, playerY);
        cout << "|p|" << endl;
        gotoxy(PlayerX, playerY + 1);
        cout << "/|\\" << endl;
        gotoxy(PlayerX, playerY + 2);
        cout << "/ \\" << endl;
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
        printPlayer();
    }
}
void printEnemyOne()
{
    gotoxy(EnemyOneX, EnemyOneY);
    cout << "(E)" << endl;
    gotoxy(EnemyOneX, EnemyOneY + 1);
    cout << "/|\\" << endl;
    gotoxy(EnemyOneX, EnemyOneY + 2);
    cout << "/ \\" << endl;
}
void eraseEnemyOne()
{
    gotoxy(EnemyOneX, EnemyOneY);
    cout << "   ";
    gotoxy(EnemyOneX, EnemyOneY + 1);
    cout << "   ";
    gotoxy(EnemyOneX, EnemyOneY + 2);
    cout << "   ";
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
    else if (direction == "right" && getCharAtxy(EnemyOneX + 3, EnemyOneY) == ' ' && getCharAtxy(EnemyOneX + 3, EnemyOneY + 1) == ' ' && getCharAtxy(EnemyOneX + 3, EnemyOneY + 2) == ' ')
    {
            EnemyOneX += 1;
            
    }
    printEnemyOne();
}
void printEnemyTwo()
{
    gotoxy(EnemyTwoX, EnemyTwoY);
    cout << "(E)" << endl;
    gotoxy(EnemyTwoX, EnemyTwoY + 1);
    cout << "/|\\" << endl;
    gotoxy(EnemyTwoX, EnemyTwoY + 2);
    cout << "/ \\" << endl;
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

void printEnemyThree()
{
    gotoxy(EnemyThreeX, EnemyThreeY);
    cout << "(E)" << endl;
    gotoxy(EnemyThreeX, EnemyThreeY + 1);
    cout << "/|\\" << endl;
    gotoxy(EnemyThreeX, EnemyThreeY + 2);
    cout << "/ \\" << endl;
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
        else if (getCharAtxy(fireX - 2, fireY) == ')' || getCharAtxy(fireX - 2, fireY) == '\\')
        {
            incraesePower++;
            gotoxy(92, 4);
            cout << incraesePower;
            gotoxy(fireX - 1, fireY);
            cout << " ";
            isFire = false;
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
        else if (getCharAtxy(fireX + 2, fireY) == '(' || getCharAtxy(fireX + 2, fireY) == '/')
        {
            incraesePower++;
            gotoxy(92, 4);
            cout << incraesePower;
            gotoxy(fireX + 1, fireY);
            cout << " ";
            isFire = false;
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
        else if (getCharAtxy(fireX - 2, fireY) == '/' || getCharAtxy(fireX, fireY - 2) == '\\' || getCharAtxy(fireX, fireY - 2) == '|')
        {
            incraesePower++;
            gotoxy(92, 4);
            cout << incraesePower;
            gotoxy(fireX, fireY - 1);
            cout << " ";
            isFire = false;
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