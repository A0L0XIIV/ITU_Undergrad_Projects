#include <stdio.h>
int main(){
	int x, y, z;
	char i;
	
	puts("Toplama icin (+), c�karma icin (-), bolum icin (/), carpma icin (*) giriniz.");
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
			printf("B�l�m = %d\n", z);
		}
		else if(i == '*'){
			puts("Enter 2 integers:");
			scanf("%d%d",&x,&y);
			
			z = x * y;
			printf("�arp�m = %d\n", z);
		}
		else
			puts("Hatal� giri�!");
	}
	
	return 0;
}	
