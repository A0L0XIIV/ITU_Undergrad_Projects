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

//#ifndef SONGLIST_H
#define SONGLIST_H

#define SNAME_LENGTH 50
#define LNAME_LENGTH 50
#define STYLE_LENGTH 30
#define SINGER_LENGTH 50

using namespace std;

struct playlist;

struct song {
	char* name = new char[SNAME_LENGTH];
	char* singer = new char[SINGER_LENGTH];
	char* style = new char[STYLE_LENGTH]; 
	int year;
};

struct song_node {
	song* data;
	song_node* next;
	song_node* prev;
	playlist* parent;
}; 

struct playlist {
	int songnumber;
	char* name = new char[LNAME_LENGTH];
	song_node* head;
	playlist* next;
	playlist* prev;
};

//add file definitions and functions as needed.
struct list {
	int playlist_count;
	playlist* head;
	void play();
	void printList();
	void createList();
	void addSong();
	void removeSong();
	void deleteList();
	void writeToFile();

	void create();
	void createPlayLists();
	void sortByYear(song *);
	void sortBySinger(song *);
	void randomSort(song *);
	void makeEmpty();
	void close();

};


