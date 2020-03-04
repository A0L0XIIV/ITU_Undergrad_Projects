#include <iostream>
#include "operations.h"




void labirent::olustur() {
    
    head = NULL;
    
    
    
}


void labirent::push(c_data a) {
    
    
    stck* news = new stck;
    news->data = a;
    news->next = head;
    head = news;
    
}

c_data labirent::pop() {
    
    c_data temp = head->data;
    stck* temps;
    temps = head;
    head = head->next;
    delete temps;
    return temp;
}


bool labirent::isempty() {
    
    if (head == NULL)
        return true;
    else
        return false;
}








