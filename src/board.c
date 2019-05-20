#include "board.h"
#include "board_print_plain.h"
#include <stdio.h>
#include <stdlib.h>

extern char init_desk[8][8];
extern char desk[8][8];

//--------------------------
// Очистка экрана

void clear()
{
    printf("\033[2J");
    printf("\033[0;0f");
}
//--------------------------

//------------------------
// Функция, преобразующая числовые значения из чаровского массива p

void metamorphosis(int* b)
{
    b[0] = b[0] - 65; // X1
    b[1] = b[1] - 49; // Y1
    b[3] = b[3] - 65; // X2
    b[4] = b[4] - 49; // Y2
}
//------------------------

//---------------------------------------------------
// Движение фигуры по шахматной доске
int move(int* b) //формат движения е2-е4
{
    /*cout << "\n\n\n"
         << "b[3] = " << b[3] << "\nb[4] = " << b[4];
    cout << "\n\n\n"
         << "b[0] = " << b[0] << "\nb[1] = " << b[1];
    cout << "\n\n\n";*/

    desk[b[4]][b[3]] = desk[b[1]][b[0]];
    desk[b[1]][b[0]] = ' ';

    return 0;
}

//---------------------------------------------------

//-----------------------------------------------------------------
// Функция, проверяющая на правильность введённый ход

int check_input(int* b, char* p)
{
    if ((p[2] == '-') && (b[0] <= 72) && (b[3] <= 72) && (b[1] < 57)
        && (b[4] < 57) && (b[0] >= 65) && (b[3] >= 65) && (b[1] >= 49)
        && (b[4] >= 49))
        return 1;
    return 0;
}
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Функция повторного ввода при НЕ(check_input(b,p))

int input(char* p, int* b)
{
    //   clear();
    /*   cout << "\n\n\n"
            << "b[3] = " << b[3] << "\nb[4] = " << b[4];
       cout << "\n\n\n"
            << "b[0] = " << b[0] << "\nb[1] = " << b[1];
       cout << "\n\n\n"; */
    //    print_desk();
    printf("\nInput coordinates (X1Y1-X2Y2)\n");
    for (int i = 0; i < 5; i++) {
        scanf(" %c", &p[i]);
        b[i] = p[i];
    }
    for (int i = 0; i < 5; i++) {
        printf("p[");
        printf("%d", i);
        printf("] = ");
        printf("%c", p[i]);

        printf("\n");

        printf("b[");
        printf("%d", i);
        printf("] = ");
        printf("%d", b[i]);

        printf("\n");
    }
    //   clear();
    return 0;
}
//-----------------------------------------------------------------

//---------------------------------------
// Проверка очерёдности ходов

int Player(int* b, int s)
{
    if ((s % 2) == 0) {
        if (desk[b[1]][b[0]] < 97) {
            printf("Black (lil)\n\n");
            return 1;
        }
    } else if (desk[b[1]][b[0]] > 96) {
        printf("White (big)\n\n");
        return 1;
    }
    return 0;
}
//---------------------------------------

//------------------------------------------------------------------
// Функции для проверки движения шахматных фигур
//------------------------------------------------------------------

//---------------------------------------------------------
// Общее + частное движение фигур

int check_figure_move(int* b)
{
    metamorphosis(b);

    if (desk[b[4]][b[3]] == ' ') {
        if ((desk[b[1]][b[0]] == 'p') && (check_peshka(b))) // Чёрная пешка
            return 1;

        if ((desk[b[1]][b[0]] == 'P') && (check_peshka(b))) // Белая пешка
            return 1;

        if ((desk[b[1]][b[0]] == 'R') && (check_ladya(b))) // Белая ладья
            return 1;

        if ((desk[b[1]][b[0]] == 'r') && (check_ladya(b))) // Чёрная ладья
            return 1;

        if ((desk[b[1]][b[0]] == 'n') && (check_horse(b))) // Чёрный конь
            return 1;

        if ((desk[b[1]][b[0]] == 'N') && (check_horse(b))) // Белый конь
            return 1;

        if ((desk[b[1]][b[0]] == 'B') && (check_elephant(b))) // Белый слон
            return 1;

        if ((desk[b[1]][b[0]] == 'b') && (check_elephant(b))) // Чёрный слон
            return 1;

        if ((desk[b[1]][b[0]] == 'q') && (God_Save_The_Queen(b)))
            return 1; // Чёрная королева

        if ((desk[b[1]][b[0]] == 'Q') && (God_Save_The_Queen(b)))
            return 1; // Белая королева

        if ((desk[b[1]][b[0]] == 'K') && (check_king(b))) // Белый король
            return 1;

        if ((desk[b[1]][b[0]] == 'k') && (check_king(b))) // Чёрный король
            return 1;

    } else {
        if ((desk[b[1]][b[0]] == 'p') && (check_peshka(b))) // Чёрная пешка
            return 1;

        if ((desk[b[1]][b[0]] == 'P') && (check_peshka(b))) // Белая пешка
            return 1;

        if ((desk[b[1]][b[0]] == 'R') && (check_ladya(b)) // Белая ладья
            && ((int)desk[b[4]][b[3]] > 96))
            return 1;

        if ((desk[b[1]][b[0]] == 'r') && (check_ladya(b)) // Чёрная ладья
            && ((int)desk[b[4]][b[3]] < 97))
            return 1;

        if ((desk[b[1]][b[0]] == 'n') && (check_horse(b)) // Чёрный конь
            && ((int)desk[b[4]][b[3]] < 97))
            return 1;

        if ((desk[b[1]][b[0]] == 'N') && (check_horse(b)) // Белый конь
            && ((int)desk[b[4]][b[3]] > 96))
            return 1;

        if ((desk[b[1]][b[0]] == 'B') && (check_elephant(b)) // Белый слон
            && ((int)desk[b[4]][b[3]] > 96))
            return 1;

        if ((desk[b[1]][b[0]] == 'b') && (check_elephant(b)) // Чёрный слон
            && ((int)desk[b[4]][b[3]] < 97))
            return 1;

        if ((desk[b[1]][b[0]] == 'q') && (God_Save_The_Queen(b))
            && ((int)desk[b[4]][b[3]] < 97)) // Чёрная королева
            return 1;

        if ((desk[b[1]][b[0]] == 'Q') && (God_Save_The_Queen(b))
            && ((int)desk[b[4]][b[3]] > 96)) // Белая королева
            return 1;

        if ((desk[b[1]][b[0]] == 'K') && (check_king(b))
            && ((int)desk[b[4]][b[3]] > 96)) // Белый король
            return 1;

        if ((desk[b[1]][b[0]] == 'k') && (check_king(b))
            && ((int)desk[b[4]][b[3]] < 97)) // Чёрный король
            return 1;
    }

    return 0;
}
//---------------------------------------------------------

//---------------------------------------------------------
//Проверка движения пешки

int check_peshka(int* b)
{
    if (desk[b[4]][b[3]] == ' ') { // Если пешка идёт на пустое место
        if (desk[b[1]][b[0]] == 'p') { // Чёрная пешка
            if ((desk[b[1]][b[0]] == init_desk[b[1]][b[0]])
                && ((b[4] - b[1]) <= 2) && ((b[0] - b[3]) == 0)
                && (desk[b[1] + 1][b[0]] == ' '))
                return 1;

            if (((b[4] - b[1]) == 1)
                && ((b[0] - b[3]) == 0)) // Если не на начальной позиции
                return 1;
        }

        if (desk[b[1]][b[0]] == 'P') { // Белая пешка
            if ((desk[b[1]][b[0]] == init_desk[b[1]][b[0]])
                && ((b[1] - b[4]) <= 2) && ((b[0] - b[3]) == 0)
                && (desk[b[4] + 1][b[0]] == ' '))
                return 1;

            if (((b[1] - b[4]) == 1)
                && ((b[0] - b[3]) == 0)) // Если не на начальной позиции
                return 1;
        }
    } else { // Если пешка идёт не на пустое место
        if ((desk[b[1]][b[0]] == 'p')) {
            if ((abs(b[0] - b[3]) == 1) && (abs(b[1] - b[4]) == 1)
                && ((b[4] - b[1]) == 1) && ((int)desk[b[4]][b[3]] < 97))
                return 1;
        }

        if ((desk[b[1]][b[0]] == 'P')) {
            if ((abs(b[0] - b[3]) == 1) && (abs(b[1] - b[4]) == 1)
                && ((b[1] - b[4]) == 1) && ((int)desk[b[4]][b[3]] > 96))
                return 1;
        }
    }
    return 0;
}
//---------------------------------------------------------

//---------------------------------------------------
// Проверка движения ладьи

int check_ladya(int* b)
{
    // Случаи с ходом на одну клетку

    if (((b[1] - b[4]) == 1) && ((b[0] - b[3]) == 0))
        return 1;

    if (((b[4] - b[1]) == 1) && ((b[0] - b[3]) == 0))
        return 1;

    if (((b[3] - b[0]) == 1) && ((b[1] - b[4]) == 0))
        return 1;

    if (((b[0] - b[3]) == 1) && ((b[1] - b[4]) == 0))
        return 1;
    //-----------------------------------------------

    // Если двигаемся на пустое место
    if (((b[1] - b[4]) > 0) && ((b[0] - b[3]) == 0)) // По вертикали вверх
        for (int i = 1; i < (b[1] - b[4]); i++) {
            if (desk[b[1] - i][b[0]] != ' ')
                return 0;

            if (i == (b[1] - b[4] - 1))
                return 1;
        }

    if (((b[1] - b[4]) < 0) && ((b[0] - b[3]) == 0)) // По вертикали вниз
        for (int i = 1; i < (b[4] - b[1]); i++) {
            if (desk[b[1] + i][b[0]] != ' ')
                return 0;

            if (i == (b[4] - b[1] - 1))
                return 1;
        }

    if (((b[0] - b[3]) < 0) && ((b[1] - b[4]) == 0))
        for (int i = 1; i < (b[3] - b[0]); i++) { // По горизонтали вправо
            if (desk[b[1]][b[0] + i] != ' ')
                return 0;

            if (i == (b[3] - b[0] - 1))
                return 1;
        }

    if (((b[0] - b[3]) > 0) && ((b[1] - b[4]) == 0)) // По горизонтали влево
        for (int i = 1; i < (b[0] - b[3]); i++) {
            if (desk[b[1]][b[0] - i] != ' ')
                return 0;

            if (i == (b[0] - b[3] - 1))
                return 1;
        }

    return 0;
}
//---------------------------------------------------

//---------------------------------------------------
// Проверка движения коня

int check_horse(int* b)
{
    if ((abs(b[0] - b[3]) + abs(b[1] - b[4])) == 3 && (abs(b[0] - b[3]) <= 2)
        && (abs(b[1] - b[4]) <= 2))
        return 1;

    return 0;
}
//---------------------------------------------------

//---------------------------------------------------------
// Проверка движения слона

int check_elephant(int* b)
{
    if ((abs(b[1] - b[4]) == 1)
        && (abs(b[0] - b[3]) == 1)) // Ход на одну клетку
        return 1;

    if ((abs(b[0] - b[3])) == (abs(b[1] - b[4]))) {
        if ((b[0] > b[3]) && (b[1] > b[4])) // Влево вверх
            for (int i = 1; i < (b[0] - b[3]); i++) {
                if (desk[b[1] - i][b[0] - i] != ' ')
                    return 0;

                if (i == (b[0] - b[3] - 1))
                    return 1;
            }

        if ((b[0] < b[3]) && (b[1] < b[4])) // Вправо вниз
            for (int i = 1; i < (b[3] - b[0]); i++) {
                if (desk[b[1] + i][b[0] + i] != ' ')
                    return 0;

                if (i == (b[3] - b[0] - 1))
                    return 1;
            }

        if ((b[0] > b[3]) && (b[1] < b[4])) // Влево вниз
            for (int i = 1; i < (b[0] - b[3]); i++) {
                if (desk[b[1] + i][b[0] - i] != ' ')
                    return 0;

                if (i == (b[0] - b[3] - 1))

                    return 1;
            }

        if ((b[0] < b[3]) && (b[1] > b[4])) // Вправо вверх
            for (int i = 1; i < (b[3] - b[0]); i++) {
                if (desk[b[1] - i][b[0] + i] != ' ')
                    return 0;

                if (i == (b[3] - b[0] - 1))
                    return 1;
            }
    }

    return 0;
}
//---------------------------------------------------------

//----------------------------------------------------
// Проверка движения королевы

int God_Save_The_Queen(int* b)
{
    if (check_ladya(b) || check_elephant(b))
        return 1;

    return 0;
}
//-------------------------------------------------------

//---------------------------------------------------
// Проверка движения короля

int check_king(int* b)
{
    if (((b[1] - b[4]) == 1) && ((b[0] - b[3]) == 0))
        return 1;

    if (((b[4] - b[1]) == 1) && ((b[0] - b[3]) == 0))
        return 1;

    if (((b[3] - b[0]) == 1) && ((b[1] - b[4]) == 0))
        return 1;

    if (((b[0] - b[3]) == 1) && ((b[1] - b[4]) == 0))
        return 1;

    if ((abs(b[1] - b[4]) == 1) && (abs(b[0] - b[3]) == 1))
        return 1;

    return 0;
}
//---------------------------------------------------