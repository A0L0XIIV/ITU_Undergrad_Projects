#include <stdio.h>

int karenin_cevresi(int);
int karenin_alani(int);

int main(){
    int a;
    
    printf("Karenin kenarini giriniz: ");
    scanf("%i", &a);
    
    printf("Karenin alani: %d\n",karenin_alani(a));
    printf("Karenin cevresi: %d\n",karenin_cevresi(a));
    
    system("pause");
    return 0;
    
}

int karenin_alani(int a){
    return a*a;
}
int karenin_cevresi(int a){
    return 4*a;
}
    
