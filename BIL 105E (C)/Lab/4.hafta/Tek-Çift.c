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
    
    //(sayi % 2 == 0 ? printf("Sayi �ifttir\n") : printf("Sayi tektir\n");
    
    //(cond) ? true: false   --->  if gibi
    // ba��nda ! var ��nk� kalan 0 onu 1 yap�yoruz ---> true saymas� i�in
    printf(!(sayi % 2) ? "Sayi cifttir\n": "Sayi tektir\n");
    system("pause");
    return 0;
}
