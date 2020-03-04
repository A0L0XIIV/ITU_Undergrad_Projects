#include <iostream>
#include <cstdlib>

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

using namespace std;

struct position
{
    int x;
    int y;
    int up;
    int right;
    int down;
    int left;
    int camefrom;
};

struct myStack
{
    position element[100];
	//element ele;
    position pop();
    void push(position);
    bool isEmpty();
    int top;
};

struct StackNode{
	position data;
	StackNode *next;
};

struct element{
	position ele;
	element *next;
};

struct list{
	element *head;
	void create();
};

void list::create(){
	head = NULL;
}

void myStack::push(position newElement)
{
    element[top++] = newElement;
}

position myStack::pop()
{
    return element[--top];
}

bool myStack::isEmpty()
{
    return (top == 0);
}

void printlab(char l[][22])
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

char Maze[14][22]={"#o###################",  
                  "#     #           # #",
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

    myStack stackPP, LastP;//stackPP for process, lastp for printing last way's coordinates
    stackPP.top = 0;
    LastP.top = 0;
    position pos = {1,0,0,0,0,0,0}; //Start
    position exit = {20,14,0,0,0,0,0}; //Finish
    pos.camefrom = UP;
    printlab(Maze);
    bool goback = false;
    position lastPoint;
    int step = 0;

    while (pos.x != exit.x || pos.y != exit.y)
    {
        system("cls");
        Maze[pos.y][pos.x]='o';

        printlab(Maze);

        if (!goback) 
        {
            pos.right = 0;
            pos.left = 0;
            pos.down = 0;
            pos.up = 0;
			//Check the all directions for # and o
			if (pos.y>0 && Maze[pos.y - 1][pos.x] != '#' && Maze[pos.y - 1][pos.x] != 'o')
				pos.up = 1;//up

            if (pos.x<20 && Maze[pos.y][pos.x+1]!='#' && Maze[pos.y][pos.x+1]!='o')
                pos.right=1;//right

			if (pos.y<14 && Maze[pos.y + 1][pos.x] != '#' && Maze[pos.y + 1][pos.x] != 'o')
				pos.down = 1;//down

            if (pos.x>0 && Maze[pos.y][pos.x-1]!='#' && Maze[pos.y][pos.x-1]!='o')
                pos.left=1;//left


        }
        else
        {
            goback = false;
        }

        bool canMove = true;
        position past = pos;
        LastP.push(past);
        step++;

        if (pos.down && pos.camefrom != DOWN)
        {
            pos.y++;
            pos.camefrom = UP;
            past.down = 0;

        }
        else if (pos.up && pos.camefrom != UP)
        {
            pos.y--;
            pos.camefrom = DOWN;
            past.up = 0;

        }
         else if (pos.left && pos.camefrom != LEFT)
        {
            pos.x--;
            pos.camefrom = RIGHT;
            past.left = 0;

        }
        else if (pos.right && pos.camefrom != RIGHT)
        {
            pos.x++;
            pos.camefrom = LEFT;
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
            if ( (pos.down + pos.up + pos.right + pos.left) >= 2)
            {
                stackPP.push(past);//Decision point push
            }

            if (!canMove) { //It has to go back (Geri döndüðü yollarý temizler ve geri döner)
                if ( !stackPP.isEmpty() ) { //If stack is not empty
                    lastPoint = stackPP.pop();//Pop last point

                    if (pos.camefrom == UP)
                    {
                        Maze[pos.y][pos.x] = ' ';
                        pos.y--;
                    }
                    else if (pos.camefrom == RIGHT)
                    {
                        Maze[pos.y][pos.x] = ' ';
                        pos.x++;
                    }
                    else if (pos.camefrom == DOWN)
                    {
                        Maze[pos.y][pos.x] = ' ';
                        pos.y++;
                    }
                    else if (pos.camefrom == LEFT)
                    {
                        Maze[pos.y][pos.x] = ' ';
                        pos.x--;
                    }
                    printlab(Maze);

                    while (pos.x != lastPoint.x || pos.y != lastPoint.y)//(O'yu bulup tekrar son karar noktasýna kadar o'yu silerek ilerler)
                    {													//lastpoint poplanan karar noktasý ve oraya ulaþana kadar döngü döner
                        system("cls");
                        LastP.pop();
                        step--;
                        Maze[pos.y][pos.x] = ' ';//Replace "o" to " "
						
                        if (Maze[pos.y-1][pos.x] == 'o')
                        {
                            pos.y--;//Up
                        }
                        else if (Maze[pos.y][pos.x+1] == 'o' )
                        {
                             pos.x++;//Right
                        }
                        else if (Maze[pos.y+1][pos.x] == 'o')
                        {
                            pos.y++;//Down
                        }
                        else if (Maze[pos.y][pos.x-1] == 'o')
                        {
                            pos.x--;//Left
                        }

                        printlab(Maze);
                        for(int i=0; i<50000000; i++){}//Delay
                    }
                    pos = lastPoint;//devam edeceði yolu son karar noktasýna eþitleme
                    goback = true;
                }
            }
        }
        for(int i=0; i<50000000; i++){}//Delay
    }
    cout << "There is a path that it can reach the exit!" << endl;
    cout << "Way points:" << endl;
    for (int i=0; i < step; i++)
    {
        cout << "x=" << LastP.element[i].x << " " << "y=" << LastP.element[i].y << endl; //Coordinates
    }
    cout << endl << "Step number: " << step << endl;
    return EXIT_SUCCESS;
}
