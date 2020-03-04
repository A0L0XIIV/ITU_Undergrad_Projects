#include <stdio.h>
#define BOYUT 4

void yazdir(int matris[BOYUT][BOYUT]);

int main(){
    int matris[BOYUT][BOYUT];
    int i, j;
    
    printf("%dx%d Matrisin Elemanlari giriniz:\n\n", BOYUT, BOYUT);
    for(i = 0; i < BOYUT; i++) {
          printf( "Satir %d: ", i+1 );
          for ( j = 0; j < BOYUT; j++ ) {
              scanf("%d", &matris[i][j]);
          }    
    }
    
    printf("\n\nMatris:\n");
    yazdir(matris);
    
    int transpoz[BOYUT][BOYUT];
    for (i = 0; i < BOYUT; i++)
        for (j = 0; j < BOYUT; j++)
            transpoz[j][i] = matris[i][j];
            
    printf("\n\nTranspoz:\n");
    yazdir(transpoz);
    return 0;
}

void yazdir(int matris[BOYUT][BOYUT]){
     int i, j;
     
     for (i = 0; i < BOYUT; i++) {
         printf("Satir %d: ", i+1);
         for (j = 0; j < BOYUT; j++)
             printf("%4d" , matris[i][j]);
         printf("\n");
     }
     printf("\n");
     return 0;
}
