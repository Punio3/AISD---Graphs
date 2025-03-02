#ifndef LISTA_H
#define LISTA_H

struct element {
    int liczba;
    element* next;
};

struct lista {

    element* first;
    element* last;
    int size;

    lista();

    void push(int liczba);
    int pop();
    void deleteall();
};

#endif 