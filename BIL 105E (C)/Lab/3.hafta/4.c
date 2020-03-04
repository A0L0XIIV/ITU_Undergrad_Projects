#include <stdio.h>
int main()
{
    int x, y, z;
    
    z = 1;
    x = y = z;
    printf("x = %d \t y = %d \t z = %d \n", x, y, z);
    
    x = y++ + ++z;
    printf("x = %d \t y = %d \t z = %d \n", x, y, z);
    
    x = y == z;   //doðruysa 1 yanlýþsa 0
    printf("x = %d \t y = %d \t z = %d \n", x, y, z);
    
    x = y == --z;
    printf("x = %d \t y = %d \t z = %d \n", x, y, z);
 
    getchar ();   
    return 0;
}
