#include <stdio.h>

#define DUR 2

int main(){
    int i, j, k;
    
    for (i = 0; i < DUR; i++){
        for (j = 0; j < DUR; j++){
            for (k = 0; k < DUR; k++){
                if (k == 0) continue;
                printf("k : %d\n", k);
                }
                if (j == 0) break;
                printf("j : %d\n", j);
            }
            
            printf("i : %d\n", i);
        }
        
        system ("pause");
        return 0;
    }
