#include <stdio.h>
#include <math.h>

int main()
{
    int a, b;
    
    /*for(initilazition;
          condition;    
           post-loop)*/
           
           // for da(;;) noktalý virgüller boþ olsa bile olacak!!
           // powdaki 0.5 karekök
           
    for (;;){
        printf("iki kenarý giriniz:");
        scanf("%d %d", &a, &b);
        
        if (a > 0 && b > 0){
              printf("sonuc: %.2f\n", pow(a*a+b*b, 0.5));
              break;
              }
        else
            printf("farkli degerler giriniz...\n");
    }
    
    system("pause");
    return 0;
}
