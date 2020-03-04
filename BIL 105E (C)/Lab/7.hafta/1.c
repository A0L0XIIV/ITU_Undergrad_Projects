#include <stdio.h>

void reference (int *);
int value      ( int );

int main(){
    int n = 5;
    
    printf("n'nin ilk degeri: %d\n", n);
    
    value(n);
    printf("n'nin value fonksiyonu sonraki degeri: %d\n", n);
    
    reference(&n);
    printf("n'nin reference fonsiyonu sonrasi degeri: %d\n", n);
    return 0;
    
};

void reference(int *n) {
     *n = *n * *n;
};
int value(int n) {
    system ("pause");
    return n*n;
    
};
