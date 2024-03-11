#include <iostream>
#include <chrono>
//#include <conio.h>
#include <thread>

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
bool gameOver;
const int height = 20;
const int width = 20;
int headX, headY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tail_len;

void setup();
void draw();
void input();
void logic();

int main()
{
    char start;
    cout << "\t -------------------------------------------------" << endl;
    cout << "\t  \t  : SNAKE KING " << endl;
    cout << "\t -------------------------------------------------" << endl;
    cout << "Press s to start: " << endl;
    cin >> start;
    if (start == 's')
    {
        setup();
        while (!gameOver)
        {
            draw();
            input();
            logic();
            std::this_thread::sleep_for(std::chrono::milliseconds(40));
            system("clear");
        }
    }
}

void setup()
{
    gameOver = false;
    dir = STOP;
    headX = width / 2;
    headY = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw()
{
    system("clear");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // walls
            if (i == headY && j == headX)
                cout << "O"; // snake head
            else if (i == fruitY && j == fruitX)
                cout << "*"; // fruit
            else
            {

                bool print = false;
                for (int k = 0; k < tail_len; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; print = true;
                    }
                }
                if (!print)
                    cout << " ";

            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void input()
{
    char c;
    cin >> c;
    switch (c)
    {
    case 'w':
        dir = UP;
        break;
    case 'a':
        dir = LEFT;
        break;
    case 's':
        dir = DOWN;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'x':
        gameOver = true;
        break;
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;

    for(int i = 1; i < tail_len ; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    default:
        break;
    }

    if (headX >= width)
        headX = 0;
    else if (headX < 0)
        headX = width - 1;
    if (headY >= height)
        headY = 0;
    else if (headY < 0)
        headY = height - 1;

    for (int i = 0; i < tail_len; i++)
        if (tailX[i] == headX && tailY[i] == headY)
            gameOver = true;

    if (headX == fruitX && headY == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tail_len++;
    }
}
