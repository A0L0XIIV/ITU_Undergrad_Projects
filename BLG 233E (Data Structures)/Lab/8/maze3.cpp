#include <iostream>
#include <time.h>
#include<stdlib.h>
#define MAZESIZE 10
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

using namespace std;

typedef struct cell
{
    bool left, right, up, down; // right = false when a wall does not exist otherwise, right = true means there is a wall
    int l,r,u,d;
    char val; // initially this is empty (' '), when the cell is used to reach the exit, this becomes 'o'
    bool visited; // this variable will be used while generating maze randomly (look the pseudo code for further information)
    int position_x;
    int position_y;
    int camefrom;
    cell *next;
};
struct Stack{
       cell *head;
       void create();
       void close();
       void push(cell,int,int);
       int *pop();
       bool isempty();
};
void Stack::create(){
     head = NULL;       
}
void Stack::close(){    //delete list
     cell *p;
     while (head){
           p = head;
           head = head->next;
           delete p;
     }
}
bool Stack::isempty(){
     return head == NULL;
}
void Stack::push(cell cellData, int x, int y){
     cell *newnode = new cell;
     newnode->left=cellData.left;
     newnode->right=cellData.right;
     newnode->up=cellData.up;
     newnode->down=cellData.down;
     newnode->visited=cellData.visited;
     newnode->val=cellData.val;
     newnode->position_x=x;
     newnode->position_y=y;
     newnode->camefrom=cellData.camefrom;
     newnode->next = NULL;
     if(isempty()){ 
             head = newnode;
     }
     else{  
         newnode->next = head;
         head = newnode;
     }
}
int *Stack::pop(){
              cell *topnode;
              int *poz=new int [2];
              topnode = head;
              poz[0]=topnode->position_x;
              poz[1]=topnode->position_y;
              head = head->next;
              return poz;
}

cell maze[MAZESIZE][MAZESIZE]; // this is the maze
int sayac = MAZESIZE*MAZESIZE-1; //this is unvisited number
Stack stack;
Stack decisionP;

void print()
{
    for(int i = 0; i < MAZESIZE; i++)
    {
        for(int j = 0; j < MAZESIZE; j++)
        {
            if(maze[i][j].up)
                          cout << " -";
            else 
                 cout << "  ";
        }
        cout << endl;
        cout << "|";
        for(int j = 0; j < MAZESIZE; j++)
        {
                if(maze[i][j].right)
                                 cout << maze[i][j].val << "|";
                else
                    cout << maze[i][j].val << " ";
        }
        cout << endl;
    }
    for(int i = 0; i < MAZESIZE; i++)
    {
            if(maze[MAZESIZE-1][i].down)
                                     cout << " -";
    }
    cout << endl;
}
int randomWay(int x, int y){
     int choosen[4], i=0;
     if(x>0 && !maze[x-1][y].visited){
            choosen[i++]=UP;
     }
     if(y>0 && !maze[x][y-1].visited){
            choosen[i++]=LEFT;
     }
     if(x<MAZESIZE-1 && !maze[x+1][y].visited){
                     choosen[i++]=DOWN;
     }
     if(y<MAZESIZE-1 && !maze[x][y+1].visited){
                     choosen[i++]=RIGHT;
     }
     if(i==0) return 0;

     else return choosen[rand() % i];
}
void buildMaze(int x, int y){
        if(!sayac){ return;}
        if(randomWay(x,y)){
                         int choosen=randomWay(x,y);
                         stack.push(maze[x][y],x,y);
                if(choosen==UP){
                              maze[x][y].up=false;
                              x--;
                              maze[x][y].down=false;
                }
                if(choosen==LEFT){
                                maze[x][y].left=false;
                                y--;
                                maze[x][y].right=false;
                }
                if(choosen==DOWN){
                                maze[x][y].down=false;
                                x++;
                                maze[x][y].up=false;
                }
                if(choosen==RIGHT){
                                 maze[x][y].right=false;
                                 y++;
                                 maze[x][y].left=false;
                }
                maze[x][y].visited=true;
                sayac--;
                buildMaze(x,y);
        }
        else if(!stack.isempty()){
             int *a=new int [2];
             a=stack.pop();
             x=a[0];
             y=a[1];
             buildMaze(x,y);
        }
        else {
             x=rand()%MAZESIZE;
             y=rand()%MAZESIZE;
             if(!maze[x][y].visited){
                                  maze[x][y].visited=true;
                                  sayac--;
             }
             buildMaze(x,y);
        }
}
void findWay(int x, int y, int xEnd, int yEnd){
     maze[x][y].val='o';
     while(x!=xEnd || y!=yEnd){
		if(maze[x][y].r + maze[x][y].d + maze[x][y].u + maze[x][y].l>1) decisionP.push(maze[x][y], x, y);
		if(y<MAZESIZE-1 && !maze[x][y].r){
            maze[x][y].r=1;
        	y++;
            maze[x][y].val='o';
            maze[x][y].l=1;
        	maze[x][y].camefrom=LEFT;
		}
		else if(x>0 && !maze[x][y].u){
		    maze[x][y].u=1;
            x--;
            maze[x][y].val='o';
            maze[x][y].d=1;
            maze[x][y].camefrom=DOWN;
		}
		else if(x<MAZESIZE-1 && !maze[x][y].d){
		    maze[x][y].d=1;
            x++;
            maze[x][y].val='o';
            maze[x][y].u=1;
            maze[x][y].camefrom=UP;
		}
		else if(y>0 && !maze[x][y].l){
		    maze[x][y].l=1;
            y--;
            maze[x][y].val='o';
            maze[x][y].r=1;
            maze[x][y].camefrom=RIGHT;
		}
		
		else {
		   //break; //kaldýr
		int *a=new int [2];
		a=decisionP.pop();
		x=a[0];
		y=a[1];
		} 
     }
}    

int main(){
    srand(time(NULL));
    for(int i = 0; i < MAZESIZE; i++){
            for(int j = 0; j < MAZESIZE; j++){
                    maze[i][j].left=true;
                    maze[i][j].right=true;
                    maze[i][j].up=true;
                    maze[i][j].down=true;
                    maze[i][j].l=1;
                    maze[i][j].u=1;
                    maze[i][j].d=1;
                    maze[i][j].r=1;
                    maze[i][j].visited=false;
                    maze[i][j].val=' ';
            }
    }
    int x, y, xStart, yStart, xEnd, yEnd;
    cout << "Enter the entrance point's x and y" << endl;
    cout << "x=";
    cin >> x;
    xStart = x;
    cout << "y=";
    cin >> y;
    yStart = y;
    cout << "Entrance point's x =" << x << " y=" << y << endl;
    /*int x=2; //start x
    int y=0; //start y
    int xEnd=2; //exit x
    int yEnd=4;  //exit y*/
    maze[x][y].visited=true;         //start point visited
    buildMaze(x,y);                   //build maze
    for(int i = 0; i < MAZESIZE; i++){
        for(int j = 0; j < MAZESIZE; j++){
                if(!maze[i][j].left) maze[i][j].l=0; else maze[i][j].l=1;  //false measn there is no wall, true means there is wall
                if(!maze[i][j].down) maze[i][j].d=0; else maze[i][j].d=1;
                if(!maze[i][j].up) maze[i][j].u=0; else maze[i][j].u=1;
                if(!maze[i][j].right) maze[i][j].r=0; else maze[i][j].r=1;
        }
    }
    print();
    cout << "Enter the exit point's x and y" << endl;
    cout << "x=";
    cin >> xEnd;
    cout << "y=";
    cin >> yEnd;
    findWay(xStart, yStart, xEnd, yEnd);
    print();
    system("pause");
}
    

