#include <stdio.h>
#include <math.h>

int main()
{
    int a, b;
    
    /*for(initilazition;
          condition;    
           post-loop)*/
           
           // for da(;;) noktal� virg�ller bo� olsa bile olacak!!
           // powdaki 0.5 karek�k
           
    for (;;){
        printf("iki kenar� giriniz:");
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
