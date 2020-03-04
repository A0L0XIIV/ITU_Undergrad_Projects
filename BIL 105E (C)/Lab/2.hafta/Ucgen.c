#include <stdio.h>
#include <math.h>

int main()
{
    float kenar1, kenar2, hipotenus;
    float hip_ceil, hip_floor;
    
    printf("Ucgenin kenarlarini giriniz: ");
    scanf("%f %f", &kenar1, &kenar2);
    
    hipotenus = sqrt((kenar1 * kenar1) +
                     (kenar2 * kenar2));
                     
    printf("Ucgenin hipotenusu = %f\n", hipotenus);
    
    hip_ceil = ceil(hipotenus);
    printf("Ucgenin hipotenusu = %f\n", hip_ceil);
    
    hip_floor = floor(hipotenus);
    printf("Ucgenin hipotenusu = %f\n", hip_floor);
    
                    
    return 0;
}
