#include <stdio.h>

int main(){
    int sayi;
    
    printf("Sayiyi giriniz:");
    scanf("%d", &sayi);
    
    for (i = sayi, j;i > 0;j = i % 10){
          printf("%d", j);
          i /= 10;
    }
    
    printf("\n");

    system("pause");
    return 0;
}
