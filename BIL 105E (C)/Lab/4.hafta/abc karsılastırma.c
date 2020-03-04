#include <stdio.h>

int main()
{
    int a,b,c;
    
    printf("Karsilastirilacak 3 sayiyi giriniz: ");
    scanf("%d %d %d", &a, &b, &c);
    
    if ((a > b) && (a > c)){
       printf("En buyuk sayi a: %d\n", a);
       if (b > c){
             printf("Ikinci buyuk sayi b: %d\n", b);
             printf("En kucuk sayi c: %d\n", c);
       }
       else{
            printf("Ikinci buyuk sayi c: %d\n", c);
            printf("En kucuk sayi b: %d\n", b);
            }
    }
    else if ((b > a) && (b > c)){
       printf("En buyuk sayi b: %d\n", b);
       if (a > c){
             printf("Ikinci buyuk sayi a: %d\n", a);
             printf("En kucuk sayi c: %d\n", c);
       }
       else{
            printf("Ikinci buyuk sayi c: %d\n", c);
            printf("En kucuk sayi a: %d\n", a);
            }
    }
    else if ((c > a) && (c > b)){
       printf("En buyuk sayi c: %d\n", c);
       if (b > a){
             printf("Ikinci buyuk sayi b: %d\n", b);
             printf("En kucuk sayi a: %d\n", a);
       }
       else{
            printf("Ikinci buyuk sayi a: %d\n", a);
            printf("En kucuk sayi b: %d\n", b);
            }
    }
    system("pause");
    return 0;
}      
