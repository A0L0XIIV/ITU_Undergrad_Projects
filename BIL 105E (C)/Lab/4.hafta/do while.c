#include <stdio.h>

int main()
{
    int i=0;
    
    do{
        printf("i = %d\n", i),
        i += 2;
    } while (i <= 20);
    
    system("pause");
    return 0;
}
