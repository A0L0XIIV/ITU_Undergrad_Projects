#include <stdio.h>

int main(){
    int i, n, dizi[10] = {1,1};
    
    printf("Kaca kadar:\n");      // n'leri 10 yaparsan çalýþýr...
    scanf("%d, &n");
    
    for (i = 2; i < n; i++) 
        dizi[i] = dizi[i-1] + dizi[i-2];
        
    for (i = 0; i < n; i++)
        printf("dizi [%d] = %d\n", i, dizi[i]);
        
        
    system("pause");
    return 0;
}
