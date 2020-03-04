#include <iostream>
#include "operations.h"
#include <time.h>
#include <stdlib.h>
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define MAZESIZE 25


using namespace std;

void labirent::olustur() {
    
    head = NULL;
    
    
    
}


void labirent::push(c_data a) {
    
    
    stck* news = new stck;
    news->data = a;
    news->next = head;
    head = news;
    
}

c_data labirent::pop() {
    
    c_data temp = head->data;
    stck* temps;
    temps = head;
    head = head->next;
    delete temps;
    return temp;
}


bool labirent::isempty() {
    
    if (head == NULL)
        return true;
    else
        return false;
}

bool find_path(cell m[MAZESIZE][MAZESIZE], int, int, c_data c);
void temizle();
void print(cell m[][MAZESIZE]);
bool isvisited();
void olust();


cell m[MAZESIZE][MAZESIZE];

int main() {
    
    labirent lab;
    
    lab.olustur();
    
    olust();
    //print(m);
    getchar();
    srand((int)time(NULL));
    
    //m[0][0] is the initial cell
    int x = 0;
    int y = 0;
    
    m[x][y].visited = true;
    
    
    while (isvisited()){
        

        bool komsu = false;
        int array[4]={0,0,0,0};
        int temp = 0;
        
     
        if (x != 0 && !m[x - 1][y].visited) {
            
            array[temp] = UP;
            temp++;
        }
        if (x != MAZESIZE - 1 && !m[x + 1][y].visited) {
            
            array[temp] = DOWN;
            temp++;
        }
        if (y != MAZESIZE - 1 && !m[x][y + 1].visited) {
            
            array[temp] = RIGHT;
            temp++;
        }
        if (y != 0 && !m[x][y - 1].visited) {
            
            array[temp] = LEFT;
            temp++;
        }
        
        
        for (int a = 0; a < 4; a++) {
            if ( array[a] != 0){
                komsu = true;
                break;
            }
        }

        
        if (komsu) {
            
            c_data tem;
            tem.i = x;
            tem.j = y;
            
            lab.push(tem);
            
            
            int rnd = rand() % 4;
            
            while (array[rnd] == 0) {
                rnd = rand() % 4;
            }
            
            
            
            if (array[rnd] == UP) {
                
                m[x][y].up = false;
                x--;
                m[x][y].down = false;
                m[x][y].visited = true;
                
            }
            else if (array[rnd] == DOWN) {
                
                m[x][y].down = false;
                x++;
                m[x][y].up = false;
                m[x][y].visited = true;
                
            }
            else if (array[rnd] == RIGHT) {
                
                m[x][y].right = false;
                y++;
                m[x][y].left = false;
                m[x][y].visited = true;
                
            }
            else if (array[rnd] == LEFT) {
                
                m[x][y].left = false;
                y--;
                m[x][y].right = false;
                m[x][y].visited = true;
                
            }
            
            
            
        }
        else if (!lab.isempty()) {
            
            c_data temp = lab.pop();
            
            x = temp.i;
            y = temp.j;
            
        }
        
        else {
            bool cik = false;
            for (int i = 0; i < MAZESIZE && !cik; i++) {
                
                for (int j = 0; j < MAZESIZE && !cik; j++) {
                    
                    if (!m[i][j].visited) {
                        x = i;
                        y = j;
                        cik = true;
                    }
                }
            }
            
            
        }
    
    }
    
    print(m);
    
    // random maze created
    
    
    temizle();
    c_data giris, cikis;
    
    cout << "Enter entrance coordinates" << endl;
    cin >> giris.i >> giris.j;
    cout << "Enter exit coordinates" << endl;
    cin >> cikis.i >> cikis.j;
    
    if (find_path(m, giris.i, giris.j, cikis)) {
        cout << "Path Found" << endl;
    }
    
    print(m);
    
    getchar();
    getchar();
    return 0;
}


void olust() {
    
    for (int i = 0; i < MAZESIZE; i++) {
        
        for (int j = 0; j < MAZESIZE; j++) {
            
            m[i][j].down = true;
            m[i][j].up = true;
            m[i][j].right = true;
            m[i][j].left = true;
            m[i][j].val = ' ';
            m[i][j].visited = false;
            
        }
    }
    

    
}
void temizle() {
    
    for (int i = 0; i < MAZESIZE; i++) {
        
        for (int j = 0; j < MAZESIZE; j++) {
            
            m[i][j].visited = false;
            
            
        }
    }
}


bool isvisited() {
    
    for (int i = 0; i < MAZESIZE; i++) {
        
        for (int j = 0; j < MAZESIZE; j++) {
            
            if (!m[i][j].visited)
                return true;
        }
    }
    return false;
}




void print(cell m[][MAZESIZE])
{
	int h = 0;
    cout << "Maze:" << endl;
    for (int k = 0; k<MAZESIZE; k++)
    {
        m[0][k].up = true;
    }
    
    for (int i = 0; i < MAZESIZE; i++)
    {
        for (int j = 0; j < MAZESIZE; j++)
        {
            if (m[i][j].up)
                cout << " -";
            else
                cout << "  ";
        }
        
        cout << endl;
        cout << "|";
        for (int j = 0; j < MAZESIZE; j++)
        {
            if (m[i][j].right)
                cout << m[i][j].val << "|";
            else
                cout << m[i][j].val << " ";
        }
        cout << i << endl;h++;
    }
    
    for (int i = 0; i < MAZESIZE; i++)
    {
        if (m[MAZESIZE - 1][i].down)
            cout << " -";
    }
    cout << endl;
}


bool find_path(cell m[MAZESIZE][MAZESIZE], int x, int y, c_data c) {
    
    
    m[x][y].val = 'o';
    
    m[x][y].visited = true;
    
    if (x == c.i && y == c.j)
        return true;
    
    print(m);
    
    
    if (x > 0 && !m[x - 1][y].visited && !m[x][y].up ) {
        
        if (find_path(m, x - 1, y, c))
            return true;
    }
    if (x != MAZESIZE - 1 && !m[x + 1][y].visited && !m[x][y].down) {
        
        if (find_path(m, x + 1, y, c))
            return true;
        
    }
    
    if (y != MAZESIZE - 1 && !m[x][y + 1].visited && !m[x][y].right) {
        
        if (find_path(m, x, y + 1, c))
            return true;
        
    }
    if (y != 0 && !m[x][y - 1].visited && !m[x][y].left) {
        
        if (find_path(m, x, y - 1, c))
            return true;
    }
    
    m[x][y].val = ' ';
    print(m);
    
    return false;
    
}

