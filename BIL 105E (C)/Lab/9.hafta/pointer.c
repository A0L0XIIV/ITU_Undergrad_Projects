#include <stdio.h>

int main(){
    int n = 44;
    
    printf("n = %d \t &n = %x\n", n, &n);  //%x hexadecimal
    
    int* pn = &n;
    
    printf("*pn = %d \t pn = %x \t pnp = %p \t &pn = %x\n",   //%p pointer
            *pn, pn, pn, &pn);
        
    system("pause");        
    return 0;
}
