#include <stdio.h>

void yaz(int a){
     printf("Karenin cevresi = %d\n", a);
}

void hesapla(int a){
     yaz(4*a);
}

void devam(int a){
     hesapla(a);
}

int main(){
    int a;
    
    printf("Karenin kenarini giriniz: ");
    scanf("%d", &a);
    devam(a);
    
    system("pause");
    return 0;
}
