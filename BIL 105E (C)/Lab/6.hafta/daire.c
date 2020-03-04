#include <stdio.h>

#define PI 3.14

float cemberin_cevresi(float r, float pi) {
      return 2*r*PI;
}
float dairenin_alani(float r) {
      return r*r*PI;
}


int main(){
    float r;
    
    printf("Yaricapi giriniz: ");
    scanf("%f", &r);
    
    printf("Cemberin cevresi = %.2f\n",cemberin_cevresi(r, PI));
    printf("Cemberin alani %.2f\n", dairenin_alani(r));
    
    system("pause");
    return 0;
    
}
