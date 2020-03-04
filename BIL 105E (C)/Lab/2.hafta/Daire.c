#include <stdio.h>

#define PI 3.1415

int main()
{
          float yaricap, cevre, alan;
          
          printf("Yaricapi giriniz: ");
          scanf("%f", &yaricap);
          
          cevre = (2 * yaricap) * PI;
          alan = PI * yaricap * yaricap;
          
          printf("Cemberin cevresi =%7.2f\n", cevre);  //%7 kaç birim yer kaplayacaðý
          printf("Dairenin alani   =%7.2f\n", alan);   //.2 .'dan sonra kaç birim olduðu
          
          system("pause");
          return 0;
}

