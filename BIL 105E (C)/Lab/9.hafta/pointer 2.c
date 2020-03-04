#include <stdio.h>

int main(){
    int n = 44;
    
    printf("n = %d \t &n = %x\n", n, &n);  //%x hexadecimal
    
    int* pn = &n;
    
    printf("*pn = %d \t pn = %x \t pnp = %p \t &pn = %x\n",   //%p pointer
            *pn, pn, pn, &pn);
            
    int** ppn = &pn;
    printf("**ppn = %d \t *ppn = %x \t ppn = %x \t &ppn = %x\n",
            **ppn, *ppn, ppn, &ppn);
    
    system("pause");
    return 0;
}
