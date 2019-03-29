#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int height, width, thickness, height_counter, width_counter, thickness_counter, max_thickness_width, max_thickness_height;                                      // Fonksiyonlar içerisindeki sayilari tanimlama
	char secim;                                                // Kullanicinin devam edip etmemesini belirlemede kullanilan karakter


	printf("Enter the height for your rectangle:\n ");
	scanf("%d", &height);                                           // Kullanicidan height alma
	printf("Enter the width for your rectangle:\n ");
	scanf("%d", &width);                                           // Kullanicidan width alma
	printf("Enter the thickness:\n ");
	scanf("%d", &thickness);                                           // Kullanicidan thickness alma
	
	
	//maximum thickness degerini hesaplar --Kalinligin 4 tarafta da kullanilamadigi durumda
	int find_max_thickness(int width){
	
		if(width % 2){  //width tek sayi ise
			return width / 2 ;
		} else{         // çift sayi ise
			return width / 2 - 1;
		}
	}



	
	if(height  <= (thickness * 2) && width <= (thickness * 2)){   // Thickness uygun degil ise
	
		printf("It is not possible to draw your rectangle with the specified thickness. The rectangle without the thickness option is drawn below:\n");

		
		for(height_counter = 1; height_counter <= height; height_counter++){
			for(width_counter = 1; width_counter <= width; width_counter++){
				printf("*");
			}
			printf("\n");
		}
	
	}	
		
	else if (width <= (thickness * 2)) {  //Thickness 4 taraf için uygun degil ise  ve dikeyde daha uzunsa ve yatay taraf thickness'i asarsa
		
		//Genislik kismindaki thickness degeri için kullanilacak
		max_thickness_width = find_max_thickness(width);

		for(height_counter = 1; height_counter <= height; height_counter++){
			//2. kismin yazildigi yer
			if(height_counter > thickness && height_counter <= (height - thickness) ){
				
				for(thickness_counter = 1; thickness_counter <= width ; thickness_counter++){
					//max_thickness thickness degeri yerine kullanilir (thickness ile olusturmak mümkün degil)
					if(thickness_counter > max_thickness_width && thickness_counter <= (width - max_thickness_width)){
						printf(" ");
					} else{
						printf("*");
					}			
				}
			} 
			else{ //1. ve 3. kismin yazildigi yer
				for(width_counter = 1; width_counter <= width ; width_counter++){
					printf("*");
				}
				
			}
			printf("\n");
		}
	}
			
	else if (height <= (thickness * 2)) {  //Thickness 4 taraf için uygun degil ise  ve yatayda daha uzunsa ve dikey taraf thickness'i asarsa
			
		max_thickness_height = find_max_thickness(height);
		
		for(height_counter = 1; height_counter <= height; height_counter++){
			//2. kismin yazildigi yer
			//max_thickness thickness degeri yerine kullanilir (thickness ile olusturmak mümkün degil)
			if(height_counter > max_thickness_height && height_counter <= (height - max_thickness_height) ){
				
				for(thickness_counter = 1; thickness_counter <= width ; thickness_counter++){
					
					if(thickness_counter > thickness && thickness_counter <= (width - thickness)){
						printf(" ");
					} else{
						printf("*");
					}			
				}
			} 
			else{ //1. ve 3. kismin yazildigi yer
				for(width_counter = 1; width_counter <= width ; width_counter++){
					printf("*");
				}
				
			}
			printf("\n");
		}
	}
	

	 
	else{ // Thickness 4 taraf için uygun ise
	
		for(height_counter = 1; height_counter <= height; height_counter++){
		//Dikey olarak thickness degerinden  (height - thickness) degerine  kadar 2. kisma denk gelir
			if(height_counter > thickness && height_counter <= (height - thickness) ){
				
				//2.kismin yazildigi döngü
				for(thickness_counter = 1; thickness_counter <= width ; thickness_counter++){
					//thickness degerinden ve (width - thickness) degerine kadar bosluk yazilacak
					if(thickness_counter > thickness && thickness_counter <= (width - thickness)){
						printf(" ");
					} else{ //Bastan thickness degerine kadar ve (width - thickness) degerinden width degerine kadar * yazilacak
						printf("*");
					}			
				}
			} 
			else{ //1. ve 3. kismin yazildigi yer
				for(width_counter = 1; width_counter <= width ; width_counter++){
					printf("*");
				}
			}
			printf("\n");
		}
	
	}
	

	printf("Do you want to continue? (1 for Yes, 0 for No):\n\n");  // Kullanicinin devam edip etmemesini belirleme
	secim = getch();
	if(secim == '1')
	return main();                                              	// Seçim 1 ise tekrar main'i çagir
	exit(0);														// Seçim 1 degil ise programi bitir
}   // Main bitis





	








