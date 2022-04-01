#include<iostream>
using namespace std;
int index1;
char board[9] = { '1','2','3','4','5','6','7','8','9'};
int isFull()
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] != 'X')
        {
            if (board[i] != 'O')
            {
                return 0;
            }
        }
    }
    return 1;
}
int user_won()
{
    for (int i = 0; i < 9; i += 3)
    {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == 'O'))
            return 1;
    }
    for (int i = 0; i < 3; i++)
    {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == 'O'))
            return 1;
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 'O'))
    {
        return 1;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == 'O'))
    {
        return 1;
    }
    return 0;
}
int cpu_won()
{
    for (int i = 0; i < 9; i += 3)
    {
        if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]) && (board[i] == 'X'))
            return 1;
    }
    for (int i = 0; i < 3; i++)
    {
        if ((board[i] == board[i + 3]) && (board[i + 3] == board[i + 6]) && (board[i] == 'X'))
            return 1;
    }
    if ((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 'X'))
    {
        return 1;
    }
    if ((board[2] == board[4]) && (board[4] == board[6]) && (board[2] == 'X'))
    {
        return 1;
    }
    return 0;
}
void draw_board()
{
    cout << board[0] << "|" << board[1] << "|" << board[2] << endl;
    cout << board[3] << "|" << board[4] << "|" << board[5] << endl;
    cout << board[6] << "|" << board[7] << "|" << board[8] << endl;
}
int minimax(bool flag)
{
    int max_val = -1000, min_val = 1000;
    int i, j, value = 1;
    char sim;
    if (cpu_won() == 1)
    {
        return 10;
    }
    else if (user_won() == 1)
    {
        return -10;
    }
    else if (isFull() == 1)
    {
        return 0;
    }
    int score[9] = { 1,1,1,1,1,1,1,1,1 };

    for (i = 0; i < 9; i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
        {
            if (min_val > max_val)
            {
                sim = board[i];
                if (flag == true)
                {
                    board[i] = 'X';
                    value = minimax(false);
                }
                else
                {
                    board[i] = 'O';
                    value = minimax(true);
                }
                board[i] = sim;
                score[i] = value;
            }
        }
    }

    if (flag == true)
    {
        max_val = -1000;
        for (j = 0; j < 9; j++)
        {
            if (score[j] > max_val && score[j] != 1)
            {
                max_val = score[j];
                index1 = j;
            }
        }
        return max_val;
    }
    if (flag == false)
    {
        min_val = 1000;
        for (j = 0; j < 9; j++)
        {
            if (score[j] < min_val && score[j] != 1)
            {
                min_val = score[j];
                index1 = j;
            }
        }
        return min_val;
    }
}
int main()
{
    int move, choice;
    setlocale(LC_ALL, "rus");
    cout << "Добро пожаловать в крестики нолики\n";
    draw_board();
    cout << "Выберите, кто ходит первым:" << endl;
    cout << "1) Игрок первый \n2) Компьютер первый: ";
    cin >> choice;
    if (choice == 1)
    {
        system("cls");
        draw_board();
        bool ho = false;
        while (ho != true) {
            cout << "Ваш ход: ";
            cin >> move;
            if (board[move - 1] != 'X' && board[move - 1] != 'O')
            {
                board[move - 1] = 'O';
                system("cls");
                ho = true;
            }
            else
            {
                cout << "Неверный ход. Выберите другой ход: " << endl;
            }
        }
    }

    while (true)
    {
        system("cls");
        minimax(true);
        board[index1] = 'X';
        draw_board();
        if (cpu_won() == 1)
        {
            cout << "Выигрыш компьютера!" << endl;
            break;
        }
        if (isFull() == 1)
        {
            cout << "Ничья!" << endl;
            break;
        }
        bool ha = false;
        while (ha == false) {
            cout << "Ваш ход: ";
            cin >> move;
            if (board[move - 1] != 'X' && board[move - 1] != 'Y')
            {
                board[move - 1] = 'O';

                draw_board();
                ha = true;
            }
            else
            {
                cout << "Неверный ход. Выберите другой ход: " << endl;
                
            }
        }
        if (user_won() == 1)
        {
            cout << "Вы выиграли. Поздравления!" << endl;
            break;
        }
        if (isFull() == 1)
        {
            cout << "Ничья!" << endl;
            break;
        }
    }
}