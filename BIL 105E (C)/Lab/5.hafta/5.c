	#include <stdio.h>

main(){
       int i, yuk, bosluk, yildiz=0;
       
       printf("Ucgenin yuksekligi:");
       scanf("%d", &yuk);
       
       for(i = 1; i <= yuk; ++i){
             for(bosluk = 1; bosluk <= yuk-i; ++bosluk){
                        printf(" ");
             }
             for( ; yildiz!= 2*i-1; ++yildiz){
                        printf("x");  
             }
             yildiz = 0;
             printf("\n");
       }
             
                        
system("pause");                       
return 0;
}
                        
