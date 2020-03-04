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

void printm(char l[][22]) //Haritayý yazdýr
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
    posType pos = {1,0,0,0,0,0,0}; //Baþlangýç koordinatlarý
    posType exit = {20,14,0,0,0,0,0}; //Bitiþ koordinatlarý
    pos.origin = UP;
    printm(map);
    bool goback = false;
    posType lastPoint;
    int step = 0;

    while (pos.x != exit.x || pos.y != exit.y)
    {
        system("cls||clear"); //Her iki OS'da da ekraný sil
        map[pos.y][pos.x]='o';

        printm(map);

        //Ýlk baþta kaç yöne gidebileceðimizi bul
        if (!goback) //Ýlk hesaplamayý yap
        {
            pos.right = 0;
            pos.left = 0;
            pos.down = 0;
            pos.up = 0;

            if (pos.x<20 && map[pos.y][pos.x+1]!='#' && map[pos.y][pos.x+1]!='o')
                pos.right=1;//sað

            if (pos.x>0 && map[pos.y][pos.x-1]!='#' && map[pos.y][pos.x-1]!='o')
                pos.left=1;//sol

            if (pos.y<14 && map[pos.y+1][pos.x]!='#' && map[pos.y+1][pos.x]!='o')
                pos.down=1;//aþaðý

            if (pos.y>0 && map[pos.y-1][pos.x]!='#' && map[pos.y-1][pos.x]!='o')
                pos.up=1;//yukarý

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
            if ( (pos.down + pos.up + pos.right + pos.left) >= 2) //Seçenekler 2 veya daha fazlaysa
            {
                sTemp.push(past);
            }

            if (!canMove) { //Geri dönmek zorunda
                if ( !sTemp.isEmpty() ) { //Eðer boþ deðilse
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
                        system("cls||clear"); //Her iki OS'da da ekraný sil
                        sEnd.pop();
                        step--;
                        map[pos.y][pos.x] = ' ';

                        if (map[pos.y-1][pos.x] == 'o')
                        {
                            pos.y--;//Yukarý
                        }
                        else if (map[pos.y][pos.x+1] == 'o' )
                        {
                             pos.x++;//Sað
                        }
                        else if (map[pos.y+1][pos.x] == 'o')
                        {
                            pos.y++;//Aþaðý
                        }
                        else if (map[pos.y][pos.x-1] == 'o')
                        {
                            pos.x--;//Sol
                        }

                        printm(map);
                        for(int i=0; i<100000000; i++){} //OS'dan baðýmsýz bekle
                    }
                    pos = lastPoint;
                    goback = true;
                }
            }
        }
        for(int i=0; i<100000000; i++){} //OS'dan baðýmsýz bekle
    }
    cout << "Path is found!" << endl;
    cout << "Points:" << endl;
    for (int i=0; i < step; i++)
    {
        cout << "x=" << sEnd.element[i].x << " " << "y=" << sEnd.element[i].y << endl; //Koordinatlarý yazdýr
    }
    cout << endl << "Needs " << step << " steps to finish the maze." << endl;
    return EXIT_SUCCESS;
}
