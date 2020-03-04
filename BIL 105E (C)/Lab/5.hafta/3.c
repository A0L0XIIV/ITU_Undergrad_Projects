#include <stdio.h>

int main(){
    int sayi;
    
    printf("Sayiyi giriniz:");
    scanf("%d", &sayi);
    
    int i = sayi, j;
    
    for (i = sayi; i > 0; i /= 10){
           j = i % 10;
          printf("%d", j);
          
    }
    
    printf("\n");

    system("pause");
    return 0;
}
