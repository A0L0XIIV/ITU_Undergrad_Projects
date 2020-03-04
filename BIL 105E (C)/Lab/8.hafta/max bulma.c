#include <stdio.h>

#define ROW 3
#define COL 4
  
int main()
{
  int array[ROW][COL] = {
                         {1,     23, 21, 77},
                         {245,   43, 44, 12},
                         {2567, 675, 98, 9}
                        };
  int  max[ROW];                       
  int  i, j;
 
  for (i = 0; i < ROW; i++) {
     max[i] = array[i][0];
     
     for(j=1;j<COL;j++){
       if (max[i] < array[i][j] ) max[i] = array[i][j];                  
     }
  }
  
  
  for (i = 0; i < ROW; i++) printf("%d. max = %d\n", i, max[i]);
  
  getchar();
  getchar();
 
  return 0;
}
