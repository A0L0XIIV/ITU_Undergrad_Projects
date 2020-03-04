#include <stdio.h>

int main(){
    int i, dizi[10];  // dizi tanýmlama ve kaç elemanlý olduðu
    
    printf("Array without initialization:\n");
    for (i = 0; i < 10; i++)
        printf("\tdizi [%d] = %d\n", i, dizi[i]);
        
    printf("\nArray with initialization:\n");
    for (i = 0; i < 10; i++) dizi[i] = 0;
    for (i = 0; i < 10; i++)
        printf("\tdizi [%d] = %d\n", i, dizi[i]);
        
    system("pause");
    return 0;
}
