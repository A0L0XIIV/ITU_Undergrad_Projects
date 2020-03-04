#include <stdio.h>

int main(){
    int dizi[2][3][4] = {0, 1},    //4x3 lük 2 tane tablo oluþturuyor...  4lük 3 taneden 2 adet oluþturuyor...
        i = 0, j = 0, k = 0;
    
    for (i = 0; i < 2;i++){
        for (j = 0; j < 3; j++){
            for (k = 0; k < 4; k++)
                printf("%3d", dizi[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }
    system("pause");
    return 0;
}
