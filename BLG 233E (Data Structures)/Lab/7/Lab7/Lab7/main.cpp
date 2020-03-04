#include <iostream>
#include <cstdlib>

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

using namespace std;

struct posType
{
    int x;
    int y;
    int up;
    int right;
    int down;
    int left;
    int origin;
};

struct myStack
{
    posType element[100];
    posType pop();
    void push(posType);
    bool isEmpty();
    int top;
};

void myStack::push(posType newElement)
{
    element[top++] = newElement;
}

posType myStack::pop()
{
    return element[--top];
}

bool myStack::isEmpty()
{
    return (top == 0);
}

void printm(char l[][22]) //Haritay� yazd�r
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 21; j++)
        {
            cout << l[i][j];
        }
        cout << endl;
    }
    cout << endl << endl;
}

char map[14][22]={"# ###################",  //Verilen harita
                  "#     #      #    # #",
                  "# ### # ###### ## # #",
                  "# # #        # #  # #",
                  "# # ### #### # # ## #",
                  "#     # # ##   #    #",
                  "### # # # ## # # ####",
                  "# # # # #    #      #",
                  "# # # # # ######### #",
                  "# # # # # #       # #",
                  "# # #   # # #####   #",
                  "# # ##### # #   #####",
                  "#         #   #     #",
                  "###################E#"};

int main(){

    myStack sTemp, sEnd;
    sTemp.top = 0;
    sEnd.top = 0;
    posType pos = {1,0,0,0,0,0,0}; //Ba�lang�� koordinatlar�
    posType exit = {20,14,0,0,0,0,0}; //Biti� koordinatlar�
    pos.origin = UP;
    printm(map);
    bool goback = false;
    posType lastPoint;
    int step = 0;

    while (pos.x != exit.x || pos.y != exit.y)
    {
        system("cls||clear"); //Her iki OS'da da ekran� sil
        map[pos.y][pos.x]='o';

        printm(map);

        //�lk ba�ta ka� y�ne gidebilece�imizi bul
        if (!goback) //�lk hesaplamay� yap
        {
            pos.right = 0;
            pos.left = 0;
            pos.down = 0;
            pos.up = 0;

            if (pos.x<20 && map[pos.y][pos.x+1]!='#' && map[pos.y][pos.x+1]!='o')
                pos.right=1;//sa�

            if (pos.x>0 && map[pos.y][pos.x-1]!='#' && map[pos.y][pos.x-1]!='o')
                pos.left=1;//sol

            if (pos.y<14 && map[pos.y+1][pos.x]!='#' && map[pos.y+1][pos.x]!='o')
                pos.down=1;//a�a��

            if (pos.y>0 && map[pos.y-1][pos.x]!='#' && map[pos.y-1][pos.x]!='o')
                pos.up=1;//yukar�

        }
        else
        {
            goback = false;
        }

        bool canMove = true;
        posType past = pos;
        sEnd.push(past);
        step++;

        if (pos.down && pos.origin != DOWN)
        {
            pos.y++;
            pos.origin = UP;
            past.down = 0;

        }
        else if (pos.up && pos.origin != UP)
        {
            pos.y--;
            pos.origin = DOWN;
            past.up = 0;

        }
         else if (pos.left && pos.origin != LEFT)
        {
            pos.x--;
            pos.origin = RIGHT;
            past.left = 0;

        }
        else if (pos.right && pos.origin != RIGHT)
        {
            pos.x++;
            pos.origin = LEFT;
            past.right = 0;

        }
        else
        {
            canMove = false;
        }

        if (pos.x == exit.x || pos.y == exit.y)
        {
            break;
        }

        if (pos.x != exit.x || pos.y != exit.y)
        {
            if ( (pos.down + pos.up + pos.right + pos.left) >= 2) //Se�enekler 2 veya daha fazlaysa
            {
                sTemp.push(past);
            }

            if (!canMove) { //Geri d�nmek zorunda
                if ( !sTemp.isEmpty() ) { //E�er bo� de�ilse
                    lastPoint = sTemp.pop();

                    if (pos.origin == UP)
                    {
                        map[pos.y][pos.x] = ' ';
                        pos.y--;
                    }
                    else if (pos.origin == RIGHT)
                    {
                        map[pos.y][pos.x] = ' ';
                        pos.x++;
                    }
                    else if (pos.origin == DOWN)
                    {
                        map[pos.y][pos.x] = ' ';
                        pos.y++;
                    }
                    else if (pos.origin == LEFT)
                    {
                        map[pos.y][pos.x] = ' ';
                        pos.x--;
                    }
                    printm(map);

                    while (pos.x != lastPoint.x || pos.y != lastPoint.y)
                    {
                        system("cls||clear"); //Her iki OS'da da ekran� sil
                        sEnd.pop();
                        step--;
                        map[pos.y][pos.x] = ' ';

                        if (map[pos.y-1][pos.x] == 'o')
                        {
                            pos.y--;//Yukar�
                        }
                        else if (map[pos.y][pos.x+1] == 'o' )
                        {
                             pos.x++;//Sa�
                        }
                        else if (map[pos.y+1][pos.x] == 'o')
                        {
                            pos.y++;//A�a��
                        }
                        else if (map[pos.y][pos.x-1] == 'o')
                        {
                            pos.x--;//Sol
                        }

                        printm(map);
                        for(int i=0; i<100000000; i++){} //OS'dan ba��ms�z bekle
                    }
                    pos = lastPoint;
                    goback = true;
                }
            }
        }
        for(int i=0; i<100000000; i++){} //OS'dan ba��ms�z bekle
    }
    cout << "Path is found!" << endl;
    cout << "Points:" << endl;
    for (int i=0; i < step; i++)
    {
        cout << "x=" << sEnd.element[i].x << " " << "y=" << sEnd.element[i].y << endl; //Koordinatlar� yazd�r
    }
    cout << endl << "Needs " << step << " steps to finish the maze." << endl;
    return EXIT_SUCCESS;
}
