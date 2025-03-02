#include "lista.h"
#include <iostream>

lista::lista() : first(nullptr), last(nullptr), size(0) {}

void lista::push(int liczba) {
    element* new_liczba = new element;
    new_liczba->liczba = liczba;
    new_liczba->next = nullptr;

    if (first == nullptr) {
        first = new_liczba;
        last = new_liczba;
    }
    else {
        last->next = new_liczba;
        last = new_liczba;
    }

    size++;
}

int lista::pop() {
    if (first == nullptr) {
        return 0;
    }
    int out = first->liczba;
    element* tmp = first;
    first = first->next;
    delete tmp;
    size--;

    if (first == nullptr) {
        last = nullptr;
    }

    return out;
}

void lista::deleteall() {
    while (first != nullptr) {
        element* tmp = first;
        first = first->next;
        delete tmp;
    }
    last = nullptr;
    first = nullptr;
    size = 0;
}