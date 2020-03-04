#include <stdio.h>

int main(){
    int *ptr = (int *)malloc(sizeof(int));  //free gibigibi...
    void *vPtr = NULL;
    
    printf("ptr pointerinin gosterdigi: %d\ticerigi: %x\tadresi: %x\n",
            *ptr, ptr, &ptr);
            
    vPtr = ptr;
    printf("vPtr pointerinin gosterdigi: %d\ticerigi: %x\tadresi: %x\n",
            *(int *)vPtr, vPtr, &vPtr);
            
    system("pause");
    return 0;
}
