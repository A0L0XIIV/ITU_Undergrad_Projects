#include <stdio.h>
int main(){
	int x, y, z;
	char i;
	
	puts("Toplama icin (+), cýkarma icin (-), bolum icin (/), carpma icin (*) giriniz.");
	scanf("%c",&i);
	for(; i != 'Q';){

		if(i == '+'){
			puts("Enter 2 integers:");
			scanf("%d%d",&x,&y);
			
			z = x + y;
			printf("Toplam = %d\n", z);
		}
		else if(i == '-'){
			puts("Enter 2 integers:");
			scanf("%d%d",&x,&y);
			
			z = x - y;
			printf("Fark = %d\n", z);
		}
		else if(i == '/'){
			puts("Enter 2 integers:");
			scanf("%d%d",&x,&y);
			
			z = x / y;
			printf("Bölüm = %d\n", z);
		}
		else if(i == '*'){
			puts("Enter 2 integers:");
			scanf("%d%d",&x,&y);
			
			z = x * y;
			printf("Çarpým = %d\n", z);
		}
		else
			puts("Hatalý giriþ!");
	}
	
	return 0;
}	
