#include <stdio.h>

int main(){
    int sayi = 0, *ptr = &sayi;
    
    printf("sayi: %d, \t\tadresi: %p\n", sayi, &sayi);
    printf("*ptr: %d, \t\tptr: %p\t &ptr: %p\n", *ptr, ptr, &ptr);
    printf("*&ptr: %p\t&*ptr: %p\n", *&ptr, &*ptr);   // & ve * birbirinin etkilerini yok ediyorlar...
    
    system("pause");
    return 0;
}
