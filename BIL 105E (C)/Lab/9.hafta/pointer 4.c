#include <stdio.h>

int main(){
    int count = 0, *temp, sum = 0;
    
    temp = &count;
    *temp = 20;
    temp = &sum;
    *temp = count;
    
    printf("count: %d, temp: %d, sum: %d\n",
            count, *temp, sum);
            
    system("pause");
    return 0;
}
