#include <iostream>
#include "lista.h"

using namespace std;

enum kolor {
    brak,
    czerwony,
    niebieski
};

struct wierzcholek {
	int index;
    int color=brak;
	lista sasiedzi;
};

struct graf {
    int rzad;
    wierzcholek* wierzcholki;

    graf() : rzad(0), wierzcholki(nullptr) {}

    ~graf() {
        cleargraf(); 
    }

    void creategraf(int n) {
        int s, sasiad;

        rzad = n;
        wierzcholki = new wierzcholek[rzad];

        for (int k = 0; k < n; k++) {
            cin >> s;
            wierzcholki[k].index = k;
            for (int p = 0; p < s; p++) {
                cin >> sasiad;
                wierzcholki[k].sasiedzi.push(sasiad - 1);
            }
        }
    }

    void cleargraf() {
        for (int k = 0; k < rzad; k++) {
            wierzcholki[k].sasiedzi.deleteall();
        }
        delete[] wierzcholki;
        wierzcholki = nullptr;
        rzad = 0;
    }

    void clearKolory() {
        for (int k = 0; k < rzad; k++) {
            wierzcholki[k].color = -1;
        }
    }
};

void sortowanie(int* liczby, int size) {
    for (int i = 1; i < size; i++) {
        int ValueTmp = liczby[i];
        int z = i - 1;

        while (z >= 0 && liczby[z] < ValueTmp) {
            liczby[z + 1] = liczby[z];
            z = z - 1;
        }
        liczby[z + 1] = ValueTmp;
    }
}

int CiagStopniowy(graf* graf) {
    int* liczby = new int[graf->rzad];
    int MaxIloscSasiadow = 0;
    for (int k = 0; k < graf->rzad; k++) {
        liczby[k] = graf->wierzcholki[k].sasiedzi.size;
    }
    sortowanie(liczby, graf->rzad);
    for (int k = 0; k < graf->rzad; k++) {
        cout << liczby[k] << " " ;
    }
    cout << endl;
    MaxIloscSasiadow = liczby[0];
    delete[] liczby;
    return MaxIloscSasiadow;
}

void dopelnienie(graf* Graf) {
    long long int liczbaKrawedzi = 0;

    long long int iloscWierzcholkow = Graf->rzad;
    for (int k = 0; k < iloscWierzcholkow; k++) {
        long long int p = Graf->wierzcholki[k].sasiedzi.size;
        liczbaKrawedzi += p;
        
    }
    cout<< ((iloscWierzcholkow * (iloscWierzcholkow - 1)) / 2) - liczbaKrawedzi/2<<endl;
}

void PrzeszukujWGlab(graf* Graf,bool* odwiedzone,int Wierzcholek) {
    wierzcholek tmp = Graf->wierzcholki[Wierzcholek];
    element* ElementTmp = tmp.sasiedzi.first;
    int index=-1;
    for (int k = 0; k < tmp.sasiedzi.size; k++) {
        index = ElementTmp->liczba;
        if (!odwiedzone[index]) {
            odwiedzone[index] = true;
            PrzeszukujWGlab(Graf, odwiedzone, index);
        }
        ElementTmp = ElementTmp->next;
    }
    ElementTmp = nullptr;
    delete(ElementTmp);
}

int SkladoweSpojnosci(graf* Graf) {
    int liczbaSkladowychSpojnosci = 0;
    bool* odwiedzone = new bool[Graf->rzad];
    for (int k = 0; k < Graf->rzad; k++) {
        odwiedzone[k] = false;
    }
    for (int k = 0; k < Graf->rzad; k++) {
        if (!odwiedzone[k]) {
            PrzeszukujWGlab(Graf, odwiedzone, k);
            liczbaSkladowychSpojnosci++;
        }
    }
    delete[] odwiedzone;
    return liczbaSkladowychSpojnosci;
}

bool Dwudzielny(graf* Graf) {
    lista kolejka;
    kolor kolortmp;
    int indextmp = 0;
    wierzcholek wierzcholektmp;
    int indexsasiadatmp = 0;
    element* ElementTmp=nullptr;
    for (int k = 0; k < Graf->rzad; k++) {
        if (Graf->wierzcholki[k].color == brak) {
            kolejka.push(k);
            Graf->wierzcholki[k].color = czerwony;
        }
        while (kolejka.size != 0) {
            indextmp = kolejka.pop();
            wierzcholektmp = Graf->wierzcholki[indextmp];

            if (wierzcholektmp.color == czerwony) kolortmp = niebieski;
            else kolortmp = czerwony;

            ElementTmp = wierzcholektmp.sasiedzi.first;
            for (int p = 0; p < wierzcholektmp.sasiedzi.size; p++) {
                indexsasiadatmp = ElementTmp->liczba;
                if (wierzcholektmp.color == Graf->wierzcholki[indexsasiadatmp].color) {
                    ElementTmp = nullptr;
                    delete(ElementTmp);
                    return false;
                }
                else if(Graf->wierzcholki[indexsasiadatmp].color==brak) {
                    Graf->wierzcholki[indexsasiadatmp].color = kolortmp;
                    kolejka.push(indexsasiadatmp);
                }
                ElementTmp = ElementTmp->next;
            }
        }
    }
    ElementTmp = nullptr;
    delete(ElementTmp);
    return true;
}

void KolorujZachlannie(graf* Graf, int MaxIloscSasiadow) {
    int iloscWierzcholkow = Graf->rzad;
    int kolor = 0;
    int indextmp = 0;
    element* ElementTmp = nullptr;

    Graf->wierzcholki[0].color = 0;
    bool* CzySasiadMaKolor = new bool[MaxIloscSasiadow + 1];

    for (int i = 0; i < iloscWierzcholkow; i++) {

        for (int j = 0; j <= MaxIloscSasiadow; j++) {
            CzySasiadMaKolor[j] = false;
        }

        ElementTmp = Graf->wierzcholki[i].sasiedzi.first;
        for (int j = 0; j < Graf->wierzcholki[i].sasiedzi.size; j++) {
            indextmp = ElementTmp->liczba;
            kolor = Graf->wierzcholki[indextmp].color;
            if (kolor!= -1) {
                CzySasiadMaKolor[kolor] = true;
            }
            ElementTmp = ElementTmp->next;
        }

        int KolorDoPrzypisania = 1;
        while (CzySasiadMaKolor[KolorDoPrzypisania]) {
            KolorDoPrzypisania++;
        }
        Graf->wierzcholki[i].color = KolorDoPrzypisania;
    }

    for (int k = 0; k < iloscWierzcholkow; k++) {
        cout << Graf->wierzcholki[k].color << " ";
    }
    cout << endl;

    delete[] CzySasiadMaKolor;
}

int main()
{
    graf graf;
    int liczbaGrafow, liczbaWierzcholkow;
    int MaxIloscSasiadow;
    cin >> liczbaGrafow;
    for (int k = 0; k < liczbaGrafow; k++) {

        cin >> liczbaWierzcholkow;
        graf.creategraf(liczbaWierzcholkow);

        MaxIloscSasiadow = CiagStopniowy(&graf);
        cout << SkladoweSpojnosci(&graf) << endl;
        if (Dwudzielny(&graf)) {
            cout << "T" << endl;
        }
        else {
            cout << "F" << endl;
        }
        cout << "?" << endl;
        cout << "?" << endl;


        graf.clearKolory();
        KolorujZachlannie(&graf,MaxIloscSasiadow);
        graf.clearKolory();
        cout << "?" << endl;
        cout << "?" << endl;
        cout << "?" << endl;
        dopelnienie(&graf);
        cout << endl;
        graf.cleargraf();
    }
    return 0;
}
