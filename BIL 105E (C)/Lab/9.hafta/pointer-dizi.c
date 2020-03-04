#include <stdio.h>

int main(){
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
        *ptr, *ptr2, i;
        
    ptr = A;                                       //dizinin ilk elemaný
    ptr2 = &A[sizeof(A) / sizeof(int) - 1];        //dizinin son elemaný
    
    printf("ptr ile dizinin son elemani: %d\n", *(ptr + 8));
    printf("ptr 2 ile dizinin ilk elemani: %d\n", *(ptr2 - 8));
    
    for (i = 0; i < 9; i++, ptr++, ptr2--){
        if(ptr == ptr2) break;
        printf("%d\t%d\n", *ptr, *ptr2);
    }
    
    system("pause");
    return 0;
}
