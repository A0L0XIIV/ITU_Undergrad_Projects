#include <stdio.h>

int main(){
    char sekil;
    int yukseklik, i, j;
    
    printf("Sekili olusturacak karakter ve sekili giriniz: ");
    scanf("%c %d", &sekil, &yukseklik);
    
    for (i = 1; i <= yukseklik; i++){
        for (j = 0; j < yukseklik - i; j++) printf(" ");
        for (j = 0; j < (2*i) - 1; j++) printf ("%c", sekil);
        printf("\n");
    }
    system("pause");
    return 0;
}
