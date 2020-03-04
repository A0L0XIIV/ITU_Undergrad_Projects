#include <stdio.h>

int main()
{
    int sayi;
    
    printf("Sayi giriniz:");
    scanf("%d", &sayi);
    
    if ((!(sayi % 5) && (sayi % 7)))
       printf("Sayi 5'e tam bolunur\n");
       
    else if (( !(sayi % 7) && (sayi % 5)))
         printf("Sayi 7'ye tam bolunur\n");
    
    else if (( !(sayi % 7) && !(sayi % 5)))
         printf("Sayi 5'e ve 7'ye tam bolunur\n");
         
    else
        printf("Sayi 5'e de 7'ye de tam bolunmez\n");
        
    system("pause");
    return 0;
    
}
