#include <stdio.h>

int main()
{
    int sayi;
    
    printf("Bir sayi giriniz:");
    scanf("%d", &sayi);
    /*
    if ((sayi % 2) == 0)
    printf("sayi cifttir\n");
    else
    printf("sayi tektir\n);
    */
    
    //(sayi % 2 == 0 ? printf("Sayi çifttir\n") : printf("Sayi tektir\n");
    
    //(cond) ? true: false   --->  if gibi
    // başında ! var çünkü kalan 0 onu 1 yapıyoruz ---> true sayması için
    printf(!(sayi % 2) ? "Sayi cifttir\n": "Sayi tektir\n");
    system("pause");
    return 0;
}
