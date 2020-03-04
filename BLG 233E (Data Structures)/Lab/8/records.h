

typedef struct cell
{
    bool left, right, up, down; // right = false when a wall does not exist otherwise, right = true means there is a wall
    char val; // initially this is empty (' '), when the cell is used to reach the exit, this becomes 'o'
    bool visited; // this variable will be used while generating maze randomly (look the pseudo code for further information)
}konum;



typedef struct d {
    int i, j;
}c_data,entrance,exitx;



struct stck {
    
    stck* next;
    c_data data;
    
    
};


