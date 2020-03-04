#include <stdio.h>

int main(){
    
    int count, n, fact = 1;
    
    printf("Enter number: ");
    scanf("%d", &n);

    
    count = 1;
    while (count <= n){
    fact = fact * count;
    count++;
}
    
printf("Factorial of %d = %d\n", n, fact);

system("pause");
return 0;
}
/*#include <stdio.h>


int main(){
    
    int count, n, fact = 1;
    
    printf("Enter number: ");
    scanf("%d", &n);

    
for(count = 1; count <= n; count++);
          fact = fact * count
}
    

printf("Factorial of %d = %d\n", n, fact);

system("pause");
return 0;
}*/
    
