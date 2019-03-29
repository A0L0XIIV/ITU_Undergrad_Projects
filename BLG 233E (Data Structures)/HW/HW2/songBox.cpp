/* @Author
* Student Name: Baran Kaya
* Student ID : 150130032
* Date:
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <time.h>
#include "songList.h"

using namespace std;

/*typedef list musicBox;
musicBox Liste;

typedef playlist playLists;
playLists pList;*/

list Liste;

playlist pList;



const char *filename;
FILE *recordfile;

void show_menu();
bool process_selection(char);
void read_file();


int main()
{
	//List.recordNumber = 0;
	Liste.create();
	Liste.createPlayLists();
	bool finish = false;
	char selection;
	while (!finish) {
		show_menu();
		cin >> selection;
		finish = process_selection(selection);
	}
	Liste.close();
	return EXIT_SUCCESS;
}

void show_menu()
{
	system("clear || cls");
	cout << endl << endl;
	cout << "SONG BOX APPLICATION (USING DOUBLY, CIRCULAR MULTI LINKED LIST)" << endl;
	cout << "Choose an operation" << endl;
	cout << "P: Play" << endl;
	cout << "L: Show all playlists" << endl;
	cout << "A: Add songs to a playlist" << endl;
	cout << "R: Remove songs to a playlist" << endl;
	cout << "C: Create a new playlist" << endl;
	cout << "D: Delete a playlist" << endl;
	cout << "W: Write to a file (SAVE)" << endl;
	cout << "E: Exit" << endl;
	cout << "Your selection is:" << endl;
}

bool process_selection(char selection)
{
	bool end = false;

	switch (selection) {
	case 'P': case 'p':
		Liste.play();
		break;
	case 'L': case 'l':
		Liste.printList();
		break;
	case 'A': case 'a':
		Liste.addSong();
		break;
	case 'R': case 'r':
		Liste.removeSong();
		break;
	case 'C': case 'c':
		Liste.createList();
		break;
	case 'D': case 'd':
		Liste.deleteList();
		break;
	case 'W': case 'w':
		Liste.writeToFile();
		break;
	case 'E': case 'e':
		cout << "Are you sure that you want to terminate the program? (Y/N):";
		cin >> selection;
		if (selection == 'Y' || selection == 'y')
			end = true;
		break;
	default:
		cout << "Error: You have made an invalid choice" << endl << endl;
		show_menu();
		cin >> selection;
		end = process_selection(selection);
		break;
	}
	return end;
}

void list::create(){
	Liste.head = NULL;
	Liste.playlist_count = 0;
	read_file();															//Listenin içini dosyadan okuyup dolduruyor
}


void list::close(){
	list::writeToFile();													//Listeyi dosyaya yazdýrýyor
	list::makeEmpty();														//Liste dosyaya yazdýrýlýdýktan sonra memoryden silmek için
}


void list::createPlayLists(){												//SIRALAMASI BELLÝ 3 PLAYLÝST'Ý OLUÞTURAN FONKSÝTON

	Liste.head = NULL;
	playlist *chronological, *sorted, *randoml;			
	chronological = new playlist;
	chronological->name = "chronologicalPlayList";
	sorted = new playlist;
	sorted->name = "sortedPlayList";
	randoml = new playlist;
	randoml->name = "randomPlayList";
	chronological->next = sorted;
	chronological->prev = randoml;
	sorted->next = randoml;
	sorted->prev = chronological;
	randoml->next = chronological;
	randoml->prev = sorted;

	Liste.head = randoml;													//Circular olduðu için tail yerine head, head yerine head->next kullandým

	Liste.playlist_count = 3;												//playlist sayýsýný 3 yaptým

}






void list::sortByYear(song * Temp){

	song_node *newSong, *head, *traverse;

	newSong = new song_node;
	newSong->data = Temp;
	newSong->next = NULL;
	newSong->prev = NULL;

	playlist *chronological;
	chronological = Liste.head->next;

	head = chronological->head;

	traverse = head->next;								//head son eleman iken head->next ilk eleman çünkü circular list

	chronological->songnumber++;		

	if(head->next == NULL){
		head->next = newSong;
		head = newSong;
		head->prev = newSong;
		return;

	}
	

	if( newSong->data->year < head->next->data->year ){	//Listenin baþýna eklemek (gelen yeni þarkýnýn yýlý liste baþýndaki elemanýn yýlýndan küçükse)

		newSong->next = head->next;						//newSong'un next kýsmýna þu anki ilk elemaný (head->next) attým
		(newSong->next)->prev = newSong;				//Kaydýrdýðým 2. elemanýn prev kýsmýný yeni eklediðim newSong'a eþitledim
		newSong->prev = head;							//Yeni eklediðim ilk elemanýn prev kýsýmýna son eleman olan head'in adresini atadým
		head->next = newSong;							//Ýlk elemaný newSong'a eþitledim
		return;

	}


	if( newSong->data->year >= head->data->year ){		//Yeni gelen þarký dizinin sonuna eklenecek ise (gelen þarkýný yýlý son elemanýn yýlýndan büyük veya eþitse)

		newSong->next = head->next;						//newSong'un next kýsmýna ilk elemanýn adresini yazdým
		(head->next)->prev = newSong;					//Ýlk elemanýn prev kýsmýna newSong'un adresini yazdým
		newSong->prev = head;							//Yeni þarkýnýn prev kýsmýna head'in adresini yazdým
		head = newSong;									//Son elemana yeni þarkýnýn adresini yazdým
		return;

	}


	while( head->data->year > newSong->data->year && traverse->data->year < newSong->data->year ){ //Yeni gelen þarký dizinin orta bir yerlerine eklenecek ise traverse ekleneceði yerden bir öncekini gösterir
		traverse = traverse->next;				
	}
	if(traverse->data->year >= newSong->data->year){	//Traverse yeni gelecek þarkýdan bir öncekini gösteriyor ise (traverse yýlý eþit veya daha büyük)

		newSong->next = traverse->next;
		(traverse->next)->prev = newSong;
		traverse->next = newSong;
		newSong->prev = traverse;
		return;

	}

}






void list::sortBySinger(song * Temp){		//ADD SONG FONKSÝYONUNDAN DA BURAYA ÝÇÝNDE TEMP ÝLE GÖNDERMEM VE BUNALRI ÇAÐIRMAM LAIZM
											//ÖNCE SANATÇI SONRA ÞARKI ADINA GÖRE SIRALANCAK
	song_node *newSong, *head, *traverse;

	newSong = new song_node;
	newSong->data = Temp;
	newSong->next = NULL;
	newSong->prev = NULL;

	playlist *sorted;
	sorted = Liste.head->next->next;

	head = sorted->head;
	
	traverse = head->next;								//head son eleman iken head->next ilk eleman çünkü circular list

	sorted->songnumber++;		

	if(head->next == NULL){
		head->next = newSong;
		head = newSong;
		head->prev = newSong;
		return;

	}

//YENÝ ÞARKI LÝSTENÝN BAÞINA EKLENECEK VEYA ÝLK ÞARKICI ÝLE ÞARKICI ÝSÝMLERÝ AYNI ÝSE BAÞLARDA BÝR YERLERE EKLENECEK ÝSE

	int singerCompareWithFirstNode = strcmp( newSong->data->singer, head->next->data->singer );	//Yeni þarkýnýn þarkýcýsý ile ÝLK elemanýnkini karþýlarþtýrma 
	int songNameCompareWithFirstNode = strcmp( newSong->data->name, head->next->data->name );	//Yeni þarkýnýn adý ile ÝLK elemanýnkini karþýlarþtýrma 

	//ÞARKICI ÝSMÝ KARÞILAÞTIRMASINDA NEWSONG ÞARKICISI LÝSTENÝN ÝLK ELEMANINDAN KÜÇÜKSE
	if( singerCompareWithFirstNode < 0 ){				//Listenin baþýna eklemek (Gelen yeni þarkýnýn sanatçý ismi liste baþýndaki elemanýn sanatçý isiminden küçükse)

		newSong->next = head->next;						//newSong'un next kýsmýna þu anki ilk elemanýn (head->next) next kýsmýna attým
		head->next = newSong;							//Ýlk elemaný newSong'a eþitledim
		(newSong->next)->prev = newSong;				//Kaydýrdýðým 2. elemanýn prev kýsmýný yeni eklediðim newSong'a eþitledim
		newSong->prev = head;							//Yeni eklediðim ilk elemanýn prev kýsýmýna son eleman olan head'in adresini atadým
		return;

	}

	//ÞARKICI ÝSMÝ KARÞILAÞTIRMADA NEWSONG ÞARKICISI LÝSTENÝN ÝLK ELEMANININ ÞARKICISI ÝLE AYNI ÝSE
	if( singerCompareWithFirstNode == 0 ){
		
		if( songNameCompareWithFirstNode < 0 ){				//Þarkýcý adý liste baþýndaki ile ayný fakat þarký ismi önce geliyor (1. eleman olacak)
			newSong->next = head->next->next;				//newSong'un next kýsmýna þu anki ilk elemanýn (head->next) next kýsmýna attým
			head->next = newSong;							//Ýlk elemaný newSong'a eþitledim
			(newSong->next)->prev = newSong;				//Kaydýrdýðým 2. elemanýn prev kýsmýný yeni eklediðim newSong'a eþitledim
			newSong->prev = head;							//Yeni eklediðim ilk elemanýn prev kýsýmýna son eleman olan head'in adresini atadým
			return;
		}
		
		
		
	//ÞARKICI ÝSMÝ AYNI VE ÞARKI ADI ÝLK ELEMANDAN BÜYÜK OLABÝLÝR AMA YA SONRAKÝ AYNI ÞARKICININ ÞARKILARINDAN KÜÇÜK KALIRSA (AYMI ÞARKICININ 5 ÞARKISI VARSA DA HEP 2. ELEMAN OLUR)(TRAVERSE LAZIM SANIRIM)
		if( songNameCompareWithFirstNode > 0 ){				//Þarkýcý adý liste baþýndaki ile ayný fakat þarký ismi sonra geliyor (2. eleman olacak)
			newSong->next = head->next->next->next;			//newSong'un next kýsmýna þu anki ikinci elemanýn (head->next->next) next kýsmýna attým
			head->next->next = newSong;						//Ýkinici elemaný newSong'a eþitledim
			(newSong->next)->prev = newSong;				//Kaydýrdýðým 3. elemanýn prev kýsmýný yeni eklediðim newSong'a eþitledim
			newSong->prev = head->next;						//Yeni eklediðim ikinci elemanýn prev kýsýmýna ilk eleman olan head->next'in adresini atadým
			return;
		}

	}


//YENÝ ÞARKI LÝSTENÝN BAÞINA EKLENECEK VEYA ÝLK ÞARKICI ÝLE ÞARKICI ÝSÝMLERÝ AYNI ÝSE BAÞLARDA BÝR YERLERE EKLENECEK ÝSE

	int singerCompareWithLastNode = strcmp( newSong->data->singer, head->data->singer ); //Yeni þarkýnýn þarkýcýsý ile SON elemanýnkini karþýlarþtýrma
	int songNameCompareWithLastNode = strcmp( newSong->data->name, head->data->name );	 //Yeni þarkýnýn adý ile SON elemanýnkini karþýlarþtýrma

	//ÞARKICI ÝSMÝ KARÞILAÞTIRMASINDA NEWSONG ÞARKICISI LÝSTENÝN SON ELEMANINDAN BÜYÜKSE
	if( singerCompareWithLastNode > 0 ){				//Listenin sonuna eklemek (Gelen yeni þarkýnýn sanatçý ismi liste sonundaki elemanýn sanatçý isiminden büyükse)

		newSong->next = head->next;						//newSong'un next kýsmýna ilk elemanýn adresini yazdým
		(head->next)->prev = newSong;					//Ýlk elemanýn prev kýsmýna newSong'un adresini yazdým
		newSong->prev = head;							//Yeni þarkýnýn prev kýsmýna head'in adresini yazdým
		head = newSong;									//Son elemana yeni þarkýnýn adresini yazdým
		return;

	}


//YENÝ ÞARKI LÝSTENÝN ORTALARINA EKLENECEK ÝSE
	while( head->data->year > newSong->data->year && traverse->data->year < newSong->data->year ){ //Yeni gelen þarký dizinin orta bir yerlerine eklenecek ise traverse ekleneceði yerden bir öncekini gösterir
		traverse = traverse->next;				
	}
	if(traverse->data->year >= newSong->data->year){	//Traverse yeni gelecek þarkýdan bir öncekini gösteriyor ise (traverse yýlý eþit veya daha büyük)

		newSong->next = traverse->next;
		(traverse->next)->prev = newSong;
		traverse->next = newSong;
		newSong->prev = traverse;
		return;

	}

}






void list::randomSort(song * Temp){

	song_node *newSong, *head, *traverse, *tail;

	newSong = new song_node;
	newSong->data = Temp;
	newSong->next = NULL;
	newSong->prev = NULL;

	playlist *randoml;
	randoml = Liste.head;

	head = randoml->head;

	traverse = head->next;
	tail = traverse;

	randoml->songnumber++;

	int randomnumber;
	srand( time( NULL ) ); // initializes the pseudo-random number generator
	randomnumber = 5 + rand() % 20; // generating random numbers between 5 and 25


	if(head == NULL){
		head->next = newSong;
		head = newSong;
		head->prev = newSong;
		return;
	}
	
	//RANDOMNUMBER 15'TEN KÜÇÜKSE LÝSTENÝN BAÞINA, BÜYÜKSE SONUNA, 15'E EÞÝTSE ORTALARDA RASTGELE BÝR YERLERE EKLENECEK
	if( randomnumber < 15 ){
		newSong->next = head->next;
		newSong->prev = head;
		(newSong->next)->prev = newSong;
		head->next = newSong;
		return;

	}else if( randomnumber > 15 ){
		newSong->next = head->next;
		(newSong->next)->prev = newSong;
		newSong->prev = head;
		head = newSong;
		return;

	}else{		//randomnumber == 15

		while( traverse != head && (rand() % 2) != 0 ){		//Traverse son elemana eþit deðilse ve 1 veya 0 arasýndan 1 gelirse traverse bir sonraki node'a geçer
			tail = traverse;
			traverse = traverse->next;
		}
		if( traverse == head && traverse == head->next ){	//Listede sadece 1 eleman var ise yeni gelen elemaný 2. sýraya yerleþtirir (newSong head olur yani son eleman)
			newSong->prev = head;
			newSong->next = head;
			head->next = newSong;
			head->prev = newSong;
			head = newSong;
			return;
		}
		else{												//Listede tek eleman yoksa newSong tail ve traverse arasýna yerleþtirilir
			newSong->next = traverse;
			newSong->prev = tail;
			tail->next = newSong;
			traverse->prev = newSong;
			return;
		}
	}

}






void list::printList(){

	char select;
	playlist *traverse, *chronological;

	chronological = Liste.head->next;
	traverse = Liste.head->next;

	cout << "Playlist:" << chronological->name << endl;
	cout << "N (Next)" << "\t" << "P (Previous)" << "\t" << "S (Select)" << "\t" << "E (Exit)" << endl;
	select = getchar();

	while( select != 'E' || select != 'e' ){
		switch( select ){

		case 'N': case 'n':											//Sonraki listeye geçme
			traverse = traverse->next;
			cout << "Playlist:" << traverse->name << endl;
			break;
		case 'P': case 'p':											//Önceki listeye geçme
			traverse = traverse->prev;
			cout << "Playlist:" << traverse->name << endl;
			break;
		case 'S': case 's':											//Liste seçildi ve listeye iþlemler yapýlacak
			char selectInSelect;

			cout << "D (Delete List)" << "\t" << "A (Add Song)" << "\t" << "R (Remove Song)" << "\t" << "P (Play List)" << endl;
			selectInSelect = getchar();

			switch( selectInSelect ){
				case 'D': case 'd':									//Seçilen listeyi silme
					song_node *delSong;
					delSong = traverse->head->next;
					delSong->next = NULL;	
					while( delSong->next != delSong ){
						delSong = traverse->head->next;
						traverse->head->next = traverse->head->next->next;
						delete  delSong;
						traverse->songnumber--;
					}
					delete delSong;									//Son elemaný silme

					traverse->prev->next = traverse->next;
					traverse->next->prev = traverse->prev;
					delete traverse;

					break;
				case 'A': case 'a':									//Seçilen listeye þarký ekleme
					Liste.addSong();
					break;
				case 'R': case 'r':
					Liste.removeSong();
					break;
				case 'P': case 'p':
					Liste.play();
					break;
			}

			break;
		case 'E': case 'e':
			break;
		default:
			cout << "Invalid option, please try again." << endl;
			break;

		}
	}
	return;
}






void list::play(){

	char playSelection;

	system("clear || cls");
	cout << endl << endl;
	cout << "PLAY>" << endl;
	cout << "Choose an option" << endl;
	cout << "L: Play a playlist" << endl;
	cout << "S: Play a playlist starting from spesific song" << endl;
	cout << "P: Play a single song" << endl;
	cout << "E: Exit" << endl << endl;
	cout << "Enter a choice {L, S, P, E}:" << endl;

	cin >> playSelection;

	while( playSelection != 'E' || playSelection != 'e' ){
		switch(playSelection){
	
			case 'L': case 'l':

				int playListSelection;
				playListSelection = 0;

				int i, j;
				i = 1, j = 1;

				playlist *traverseList, *selectedList;
				traverseList = Liste.head->next;
				selectedList = Liste.head->next;
				
				cout << "Playlists:" << endl;
				while( traverseList != Liste.head ){							//Bütün playlistleri yazdýrma
					cout << i << "." << traverseList->name << endl;
					traverseList = traverseList->next;
					i++;
				}
				cout << i << "." << traverseList->name << endl << endl;			//Son eleman olan head'i yazdýrmak için
				cout << "Choose a playlist (Enter the number of the playlist):" << endl;
				cin >> playListSelection;

				if( 1 <= playListSelection <= Liste.playlist_count ){			//Kullanýcýnýn girdiði playListSelection sayýsýnýn 1 ile playlist sayýsý arasýnda olduðunu kontrol eder
					for(j = 1; j <= playListSelection ; j++){
						if( playListSelection != j )
							selectedList = selectedList->next;					//Kullanýcýnýn girdiði sayýnýn olduðu playlist'e kadar selectedList bir sonraki playlist'e atlar

						else if( playListSelection == j){						//Kullanýcýnýn istediði playlist bulundu ve þarkýlar çalýnacak
							
							cout << "playing..." << endl;
							cout << selectedList->head->next->data->name << "\t" << selectedList->head->next->data->singer << "\t" << selectedList->head->next->data->style << "\t" << selectedList->head->next->data->year << endl;
							cout << "NEXT (N) - PREVIOUS (P) - EXIT (E)" << endl;
							song_node *lTraverse;
							lTraverse = selectedList->head->next;

							char songSelection;									//Bir sonraki ya da bir önceki þarkýyý seçmek için gereken N veya P karakteri
							songSelection = getchar();

							while( songSelection != 'E' ||songSelection != 'e' ){//Seçim 'E' ise döngü biter
								if( songSelection == 'N' || songSelection == 'n' )
									lTraverse = lTraverse->next;
								if( songSelection == 'P' || songSelection == 'p' )
									lTraverse = lTraverse->prev;
								cout << "playing..." << endl;
								cout << lTraverse->data->name << "\t" << lTraverse->data->singer << "\t" << lTraverse->data->style << "\t" << lTraverse->data->year << endl;
								cout << "NEXT (N) - PREVIOUS (P) - EXIT (E)" << endl;
								songSelection = getchar();
							}
							break;												//Þarký deðiþtirme döngüsünden çýkýþ
						}
					}
				}

				break;
			case 'S': case 's':

				int playListSelection2;
				playListSelection2 = 0;

				int k, l, a, b;
				k = 1, l = 1, a = 1, b = 1;

				//playlist *traverseList, *selectedList;
				traverseList = Liste.head->next;
				selectedList = Liste.head->next;
				
				cout << "Playlists:" << endl;
				while( traverseList != Liste.head ){							//Bütün playlistleri yazdýrma
					cout << k << "." << traverseList->name << endl;
					traverseList = traverseList->next;
					k++;
				}
				cout << k << "." << traverseList->name << endl << endl;			//Son eleman olan head'i yazdýrmak için
				cout << "Choose a playlist (Enter the number of the playlist):" << endl;
				cin >> playListSelection2;

				if( 1 <= playListSelection2 <= Liste.playlist_count ){			//Kullanýcýnýn girdiði playListSelection sayýsýnýn 1 ile playlist sayýsý arasýnda olduðunu kontrol eder
					for(l = 1; l <= playListSelection2 ; l++){
						if( playListSelection2 != l )
							selectedList = selectedList->next;					//Kullanýcýnýn girdiði sayýnýn olduðu playlist'e kadar selectedList bir sonraki playlist'e atlar

						else if( playListSelection2 == l){						//Kullanýcýnýn istediði playlist bulundu ve þarkýlar çalýnacak
							
							int songSelection2;
							song_node *traverse, *stop;							//traverse seçilen þarkýyý bulacak ve çalan þarkýyý gösterecek, stop ise 1ç þarkýnýn yerini gösterecek
							traverse = selectedList->head->next;

							cout << "Songs:" << endl;
							while( traverse != selectedList->head ){			//Playlistteki bütün þarkýlarý yazdýrma
								cout << a << "." << traverse->data->name << "\t" << traverse->data->singer << "\t" << traverse->data->style << "\t" << traverse->data->year << endl;
								traverse = traverse->next;
								a++;
							}
							cout << a << "." << traverse->data->name << "\t" << traverse->data->singer << "\t" << traverse->data->style << "\t" << traverse->data->year << endl;//Son þarkýyý yazdýrmak için
							cout << "Choose a song to play first:" << endl;
							cin >> songSelection2;

							if( 1 <= songSelection2 <= selectedList->songnumber ){//Kullanýcýnýn girdiði songSelection sayýsýnýn 1 ile songNumber sayýsý arasýnda olduðunu kontrol eder
								for(b = 1; b <= songSelection2; b++){
									if( songSelection2 != b )
										traverse = traverse->next;

									else if( songSelection2 == b ){				//Kullanýcýnýn istediði þarký bulundu ve bu þarký ile baþlayýp þarkýlar çalýnacak
										stop = traverse;						//stop seçilip bulunan þarkýnýn yerini gösterecek

										cout << "playing..." << endl;			//Seçilen ilk þarký çalar...
										cout << a << "." << traverse->data->name << "\t" << traverse->data->singer << "\t" << traverse->data->style << "\t" << traverse->data->year << endl;
										cout << "NEXT (N) - PREVIOUS (P) - EXIT (E)" << endl;

										char NPE;
										NPE = getchar();						//Next-Previous kontrolü döngüsü

										while( NPE != 'E' ||NPE != 'e' ){//Seçim 'E' ise döngü biter
											if( NPE == 'N' || NPE == 'n' )
												traverse = traverse->next;
											if( NPE == 'P' || NPE == 'p' )
												traverse = traverse->prev;
											cout << "playing..." << endl;
											cout << traverse->data->name << "\t" << traverse->data->singer << "\t" << traverse->data->style << "\t" << traverse->data->year << endl;
											cout << "NEXT (N) - PREVIOUS (P) - EXIT (E)" << endl;
											NPE = getchar();
										}
										break;
									}
								}
							}
						}
					}
				}
				break;
			case 'P': case 'p':

				song_node *pTraverse, *pTraverse2;

				int songSelection3, m;
				m = 1;

				playlist *sorted;
				sorted = Liste.head->next->next;

				pTraverse = sorted->head->next;
				pTraverse2 = sorted->head->next;

				while( pTraverse != sorted->head ){
					cout << m << "." << pTraverse->data->name << "\t" << pTraverse->data->singer << "\t" << pTraverse->data->style << "\t" << pTraverse->data->year << endl;
					pTraverse = pTraverse->next;
					m++;
				}
				cout << m << "." << pTraverse->data->name << "\t" << pTraverse->data->singer << "\t" << pTraverse->data->style << "\t" << pTraverse->data->year << endl; //Son elemaný yazdýrma
				cout << "Choose a song:" << endl;
				cin >> songSelection3;
				for(int n = 1; n < songSelection3; n++){			
					pTraverse2 = pTraverse2->next;
				}
				cout << "playing..." << endl;
				cout << pTraverse2->data->name << "\t" << pTraverse2->data->singer << "\t" << pTraverse2->data->style << "\t" << pTraverse2->data->year << endl;

				break;
			case 'E': case 'e':
				break;
			default:
				cout << "Error: You have made an invalid choice" << endl << endl;
				break;
		}

		system("clear || cls");
		cout << endl << endl;
		cout << "PLAY>" << endl;
		cout << "Choose an option" << endl;
		cout << "L: Play a playlist" << endl;
		cout << "S: Play a playlist starting from spesific song" << endl;
		cout << "P: Play a single song" << endl;
		cout << "E: Exit" << endl << endl;
		cout << "Enter a choice {L, S, P, E}:" << endl;

		cin >> playSelection;
	}

	return;
}






void list::createList(){

	cout << "Creating a new playlist>" << endl;
	cout << "1: Songs of spesific style" << endl;
	cout << "2: Songs of spesific singer" << endl;
	cout << "3: Combination of existing playlist" << endl;
	cout << "4: Combination of existing songs" << endl;
	cout << "Choose your option:" << endl;

	int selection;
	cin >> selection;

	switch ( selection )
	{
		case 1:
			Liste.playlist_count++;
			playlist *speStyle;
			speStyle = new playlist;
			speStyle->name = "spesificStylePlaylist";

			speStyle->prev = Liste.head;
			speStyle->next = Liste.head->next;
			Liste.head->next->prev = speStyle;
			Liste.head = speStyle;

			song_node *traverse1, *traverse2;
			traverse1 = Liste.head->next->next->head->next;							//Ýkinci playlist'in ( sorted ) ilk elemanýna eþitleme
			traverse2 = Liste.head->next->next->head->next;

			int styleCounter;
			styleCounter = 0;

			cout << "Styles:" << endl;
			for( int i = 1; i <= Liste.head->next->next->songnumber ; i++ ){		//Sorted playlist'in þarký sayýsý kadar döner
				if ( strcmp( traverse1->data->style, traverse1->next->data->style) != 0 ) {		//traverse->next'in stili ile þu anki traverse stili ayný ise yazdýrmaz fakat farklý ise yazdýrýr ve farklý bütün stiller gözükür
					styleCounter++;
					cout << styleCounter << "." << traverse1->data->style << endl;
				}
				traverse1 = traverse1->next;
			}

			char *styleSelect;
			styleSelect = {};

			cout << "Please enter a style name that you want to create a new playlist:" << endl;
			cin >> styleSelect;
			for( int j = 0; j <= Liste.head->next->next->songnumber; j++ ){
				if (strcmp(traverse2->data->style, styleSelect) == 0) {				//Girilen þarkýcý adý ile ayný olan song_node'lar speStyle playlistine eklenir
					if (speStyle->head == NULL) {									//Liste boþsa
						traverse2 = speStyle->head;
						traverse2 = speStyle->head->next;
						traverse2 = speStyle->head->prev;
					}
					else {															//Listede baþka þarkýlar var ise sona ekler
						traverse2->next = speStyle->head->next;
						traverse2->prev = speStyle->head;
						speStyle->head->next->prev = traverse2;
						speStyle->head->next = traverse2;
						speStyle->head = traverse2;
					}
				}
				traverse2 = traverse2->next;
			}
			
			break;
		case 2:
			Liste.playlist_count++;
			playlist *speSinger;
			speSinger = new playlist;
			speSinger->name = "spesificSingerPlaylist";

			speSinger->prev = Liste.head;
			speSinger->next = Liste.head->next;
			Liste.head->next->prev = speSinger;
			Liste.head = speSinger;

			song_node *traverse3, *traverse4, *traverse5;
			traverse3 = Liste.head->next->next->head->next;							//Ýkinci playlist'in ( sorted ) ilk elemanýna eþitleme
			traverse4 = Liste.head->next->next->head->next;
			traverse5 = Liste.head->next->next->head->next;

			int singerCounter;
			singerCounter = 0;

			cout << "Singers:" << endl;
			for( int i = 1; i <= Liste.head->next->next->songnumber; i++) {			//Sorted playlist'in þarký sayýsý kadar döner
				if ( strcmp( traverse3->data->singer, traverse3->next->data->singer) != 0 ) {		//traverse->next'in þarkýcýsý ile þu anki traverse þarkýcýsý ayný ise yazdýrmaz fakat farklý ise yazdýrýr ve farklý bütün þarkýcýlar gözükür
					singerCounter++;
					cout << singerCounter << "." << traverse3->data->singer << endl;
				}
				traverse3 = traverse3->next;
			}

			int singerSelect;
			singerSelect = 0;
			int singerFound;
			singerFound = 0;
			char *selectedSinger;
			selectedSinger = {};

			cout << "Please enter a singer number that you want to create a new playlist:" << endl;
			cin >> singerSelect;
			for( int j = 0; j <= Liste.head->next->next->songnumber; j++) {			//Bu for döngüsü sadece girilen sayýnýn þarkýcý ismini bulup onu selectedSinger'a eþitler
				if (strcmp(traverse4->data->singer, traverse4->next->data->singer) != 0) {
					singerFound++;
				}
				if (singerFound == singerSelect)
					selectedSinger = traverse4->data->singer;

				traverse4 = traverse4->next;
			}
			for (int k = 0; k <= Liste.head->next->next->songnumber; k++ ){			
				if (strcmp(traverse5->data->style, selectedSinger) == 0) {			//selectedSinger ile þarkýcý adý ayný olan node'lar speSinger playlistine eklenir
					if (speSinger->head == NULL) {									//Liste boþsa
						traverse5 = speSinger->head;
						traverse5 = speSinger->head->next;
						traverse5 = speSinger->head->prev;
					}
					else {															//Listede baþka þarký varsa sona eklenir
						traverse5->next = speSinger->head->next;
						traverse5->prev = speSinger->head;
						speSinger->head->next->prev = traverse5;
						speSinger->head->next = traverse5;
						speSinger->head = traverse5;
					}
				}
				traverse5 = traverse5->next;
			}

			break;
		case 3:
			Liste.playlist_count++;
			playlist *combination;
			combination = new playlist;
			combination->name = "combinationOfExistingPlaylists";

			combination->prev = Liste.head;
			combination->next = Liste.head->next;
			Liste.head->next->prev = combination;
			Liste.head = combination;

			playlist *traverseList1, *traverseList2;
			traverseList1 = Liste.head->next;
			traverseList2 = Liste.head->next;

			for (int l = 1; l <= Liste.playlist_count; l++) {
				cout << l << "\t" << traverseList1->name << endl;
				traverseList1 = traverseList1->next;
			}

			int listSelect1, listSelect2;
			listSelect1 = 0, listSelect2 = 0;

			cout << "Please enter the numbers (2 lists) of playlists that you want to combine:" << endl;
			cin >> listSelect1;
			cin >> listSelect2;

			if (1 <= listSelect1 <= 3 && 1 <= listSelect2 <= 3) {					//Hazýr 3 liste seçildi ise þarkýlar zaten aynýdýr ve yeni þarký eklenmemiþtir
				cout << "These two playlists have the same songs, their combination is the same as these lists." << endl;
				return;
			}

			playlist *combine1, *combine2;
			combine1 = Liste.head->next;
			combine2 = Liste.head->next;

			for (int m = 1; m <= Liste.playlist_count; m++) {						//1. seçilen listeyi bulma
				if (m != listSelect1)
					combine1 = combine1->next;
				else
					break;
			}
			for (int n = 1; n <= Liste.playlist_count; n++) {						//2. seçilen listeyi bulma
				if (n != listSelect2)
					combine2 = combine2->next;
				else
					break;
			}
			song_node *combine1traverse1, *combine1traverse2, *combine2traverse;
			combine1traverse1 = combine1->head->next;
			combine1traverse2 = combine1->head->next;
			combine2traverse = combine2->head->next;

			for (int o = 1; o <= combine1->songnumber; o++) {						//1. listeyi direkt combination listesine ekledim
				if (combination->head == NULL) {									//Liste boþsa
					combination->head = combine1traverse1;
					combination->head->next = combine1traverse1;
					combination->head->prev = combine1traverse1;
				}
				else {																//Listede baþka þarký varsa
					combine1traverse1->prev = combination->head;
					combine1traverse1->next = combination->head->next;
					combination->head->next->prev = combine1traverse1;
					combination->head = combine1traverse1;
				}
				combine1traverse1 = combine1traverse1->next;
			}
			for (int p = 0; p <= combine2->songnumber; p++) {						//2. listeyi combination listesine ekleme
				for (int r = 0; r <= combine1->songnumber; r++) {					//combine2 listesindeki þarkýlar combine1 þarkýlarý ile kontrol edilir ve farklý ise combination listesine eklenir
					if (strcmp(combine1traverse2->data->name, combine2traverse->data->name) != 0) {
						combine2traverse->prev = combination->head;
						combine2traverse->next = combination->head->next;
						combination->head->next->prev = combine2traverse;
						combination->head = combine2traverse;
					}
					combine1traverse2 = combine1traverse2->next;
				}
				combine2traverse = combine2traverse->next;
			}


			break;
		case 4:
			Liste.playlist_count++;
			playlist *combinationSongs;
			combinationSongs = new playlist;
			combinationSongs->name = "combinationOfExistingSongs";

			combinationSongs->prev = Liste.head;
			combinationSongs->next = Liste.head->next;
			Liste.head->next->prev = combinationSongs;
			Liste.head = combinationSongs;

			break;
		default:
			cout << "Error: Invalid option." << endl;
			break;
	}

	return;
}






void list::addSong(){

	playlist *traverse;
	traverse = Liste.head->next;
	int i = 1;

	while( traverse != Liste.head ){								//Tüm playlistleri yazdýrma
		cout << i << "." << traverse->name << endl;
		traverse = traverse->next;
		i++;
	}
	cout << i << "." << traverse->name << endl;						//Son eleman olan Liste->head yazdýrmak için

	int playlistSelection;
	playlist *selectedList;
	selectedList = Liste.head->next;

	cout << "Enter the number of playlist that you want to add a song in that list (You cannot add a song in first 3 playlists!): " << endl;
	cin >> playlistSelection;

	if (playlistSelection >= 4) {									//Ýlk 3 playliste þarký eklenemez

		for (i = 1; i >= playlistSelection; i++) {					//Seçilen playlist'i bulma
			if (playlistSelection != i)
				selectedList = selectedList->next;

			if (playlistSelection == i) {							//playlist bulundu ve iþlemler yapýlacak

				int addSong;
				song *songAdd;
				songAdd = NULL;

				cout << "Song name: " << endl;
				cin >> songAdd->name;
				cout << "Singer name: " << endl;
				cin >> songAdd->singer;
				cout << "Song year: " << endl;
				cin >> songAdd->year;
				cout << "Song style: " << endl;
				cin >> songAdd->style;

				if (selectedList->name == "chronologicalPlayList")
					Liste.sortByYear(songAdd);
				else if (selectedList->name == "sortedPlayList")
					Liste.sortByYear(songAdd);
				else if (selectedList->name == "randomPlayList")
					Liste.randomSort(songAdd);
				else
					cout << "You cannot add any song that playlist in that function, please try to use create new list function." << endl;

			}
		}
	}
	else
		cout << "You cannot add any song to first 3 playlists!" << endl;

	return;
}






void list::removeSong(){

	playlist *traverse;
	traverse = Liste.head->next;
	int i = 1;

	while( traverse != Liste.head ){								//Tüm playlistleri yazdýrma
		cout << i << "." << traverse->name << endl;
		traverse = traverse->next;
		i++;
	}
	cout << i << "." << traverse->name << endl;						//Son eleman olan Liste->head yazdýrmak için

	int playlistSelection;
	playlist *selectedList;
	selectedList = Liste.head->next;

	cout << "Enter the number of playlist that you want to delete a song in that list (You cannot delete a song in first 3 playlists!): " << endl;
	cin >> playlistSelection;
	
	if (playlistSelection >= 4) {									//Ýlk 3 playlistten þarký silinemez

		for (i = 1; i >= playlistSelection; i++) {					//Seçilen playlist'i bulma
			if (playlistSelection != i)
				selectedList = selectedList->next;

			if (playlistSelection == i) {							//playlist bulundu ve iþlemler yapýlacak

				int deleteSong;
				song_node *songTraverse, *songDelete, *behind;
				songTraverse = selectedList->head->next;
				songDelete = selectedList->head->next;
				behind = songDelete;
				int j = 1;

				while (songTraverse != selectedList->head) {		//playlistteki bütün þarkýlarý yazdýrma
					cout << j << "." << songTraverse->data->name << "\t" << songTraverse->data->singer << "\t" << songTraverse->data->style << "\t" << songTraverse->data->year << endl;
					songTraverse = songTraverse->next;
					j++;
				}
				cout << j << "." << songTraverse->data->name << "\t" << songTraverse->data->singer << "\t" << songTraverse->data->style << "\t" << songTraverse->data->year << endl; //Son þarkýyý yazdýrma

				cout << "Enter the number of song that you want to delete: " << endl;
				cin >> deleteSong;

				for (j = 1; j >= deleteSong; j++) {					//Seçilen þarkýyý bulma
					if (deleteSong != j) {
						behind = songDelete;
						songDelete = songDelete->next;
					}
					if (deleteSong == j) {							//Seçilen þarký bulundu ve iþlem yapýlacak
						behind->next = songDelete->next;
						(songDelete->next)->prev = behind;
						delete songDelete;
						selectedList->songnumber--;
					}
				}
			}
		}
	}
	else
		cout << "You cannot delete any song that in first 3 playlists!" << endl;

	return;
}






void list::deleteList(){

	playlist *traverse;
	traverse = Liste.head->next;
	int i = 1;

	while( traverse != Liste.head ){								//Tüm playlistleri yazdýrma
		cout << i << "." << traverse->name << endl;
		traverse = traverse->next;
		i++;
	}
	cout << i << "." << traverse->name << endl;						//Son eleman olan Liste->head yazdýrmak için

	int deleteSelection = 0;
	playlist *selectedList, *behind;
	selectedList = Liste.head->next;
	behind = selectedList;

	cout << "Enter the number of list that you want to delete (You cannot delete first 3 playlists!): " << endl;
	cin >> deleteSelection;

	if (deleteSelection >= 4) {										//Ýlk 3 liste silinemez

		for (i = 1; i >= deleteSelection; i++) {					//Seçilen playlist'i bulma
			if (i != deleteSelection) {
				behind = selectedList;
				selectedList = selectedList->next;
			}
			if (i == deleteSelection) {								//Eðer seçilen playlist bulundu ise
				behind->next = selectedList->next;					//selectedList'in baðlantýlarý koparýlýr
				(selectedList->next)->prev = behind;

				song_node *deletePlaylistSongs;
				deletePlaylistSongs = selectedList->head->next;		//selectedList'in ilk elemanýna eþitledim

				while (deletePlaylistSongs != selectedList->head) { //Son elemana gelene kadar döner
					selectedList->head->next = deletePlaylistSongs->next;
					delete deletePlaylistSongs;
					deletePlaylistSongs = selectedList->head->next;
				}
				delete deletePlaylistSongs;							//Son eleman olan selectedList->head'i silmek için

				delete selectedList;								//Ýçindeki þarkýlar temizlenen selectedList'Ý de silip bitiriyoruz
			}
		}
		Liste.playlist_count--;
	}
	else
		cout << "You cannot delete first 3 playlists!" << endl;
	return;
}






void read_file(){

	song Temp;//Dosyadan okumak için geçici bir playlist structý kullanýp sonra her playlisti sýrakamak için ayrý fonksiyonlarý çaðýracaðým 
	//Temp = NULL;
	Temp.name = {};
	Temp.singer = {};
	Temp.style = {};
	Temp.year = 0;

	filename = "songbook.txt";
	recordfile = fopen(filename, "r+");

	if(recordfile == NULL){
		cerr << "File could not be opened" << endl;
		exit(1);
	}else{
		int i = 0;
		while(!feof(recordfile)){
			
			fscanf(recordfile, "%[^\t]\t%[^\t]\t%s\t%d\n", Temp.name, Temp.singer, Temp.style, Temp.year );
			i++;
			pList.songnumber++;
			Liste.sortByYear(&Temp);			//FUNC PROTOTYPE KISMINDA SONG * ÝSTEMELERÝNÝ YAZDIM, ONDAN ADRES GÖNDERTTÝM
			Liste.sortBySinger(&Temp);
			Liste.randomSort(&Temp);
			if(feof(recordfile))
				break;
			
		}
	}
	fclose(recordfile);
}






void list::writeToFile(){

	filename = "songbook.txt";
	recordfile = fopen(filename, "w+");

	if(recordfile == NULL){
		cerr << "File could not be opened" << endl;
		exit(1);
	}else{

		playlist *chronological;
		chronological = Liste.head->next;

		song_node *traverse;
		traverse = chronological->head->next;

		while( traverse->next != traverse ){
			fprintf(recordfile, "%s\t%s\t%d\t%s\n" ,traverse->data->name, traverse->data->singer, traverse->data->year, traverse->data->style);
			traverse = traverse->next;
		}
		fprintf(recordfile, "%s\t%s\t%d\t%s\n" ,traverse->data->name, traverse->data->singer, traverse->data->year, traverse->data->style);		//Son þarkýyý yazdýrma

		//3 ana playlist dýþýnda kullanýcýnýn eklediði baþka bir liste var ise
		if( Liste.playlist_count != 3 ){
			
			playlist *traverseList;
			traverseList = Liste.head->next->next->next->next;							//3. liste olan random listesinden sonra gelen yeni listeye atadým

			for( int i = 0; i < ( Liste.playlist_count - 3 ); i++ ){					//Toplam playlist sayýsý -3 kadar döner ve sonradan yazdýrýlan listelerin þarkýlarýný dosyaya yazar
				cout << "*****" << endl;
				traverse = traverseList->head->next;
				while ( traverse->next != traverse ){
					fprintf(recordfile, "%s\t%s\t%d\t%s\n" ,traverse->data->name, traverse->data->singer, traverse->data->year, traverse->data->style);
					traverse = traverse->next;
				}
				fprintf(recordfile, "%s\t%s\t%d\t%s\n" ,traverse->data->name, traverse->data->singer, traverse->data->year, traverse->data->style);		 //Son þarkýyý yazdýrma

				traverseList = traverseList->next;										//Bir sonraki playliste geçme
			}
		}

	}
	fclose(recordfile);
}






void list::makeEmpty(){
	
	playlist *traverseList;
	traverseList = Liste.head->next;

	song_node *traverseSong;
	traverseSong = NULL;
	traverseSong->next = NULL;

	while( traverseList->next != traverseList ){

		Liste.head->next = Liste.head->next->next;

		traverseSong = traverseList->head->next;
		while( traverseSong->next != traverseSong ){
			
			traverseList->head->next = traverseList->head->next->next;
			delete traverseSong;
			traverseSong = traverseList->head->next;

		}
		delete traverseSong;												//Sone þarkýyý silme

		traverseList->prev->next = traverseList->next;
		traverseList->next->prev = traverseList->prev;

		delete traverseList;

		traverseList = Liste.head->next;
	}
	delete traverseList;													//Son listeyi silme
	
	return;
}

