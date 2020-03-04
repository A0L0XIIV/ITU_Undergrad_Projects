#include <stdio.h>
#include <math.h>

main()
{   int pass = 0, fail = 0, student = 1, result = 0;
    while (student <= 10) 
    {     printf("Enter results (pass=1, fail=2)\n");
          scanf("%d", &result);
          
          if (result == 1){
          pass ++;
          }
          else {
          fail += 1;
          }
          
          student = student + 1;
    }
    printf("Passed: %d\n", pass);
    printf("Failed: %d\n", fail);

    if ( pass > 8 ){
            puts ("Bonus!\n");
    }
    system ("pause");
}
    
    
