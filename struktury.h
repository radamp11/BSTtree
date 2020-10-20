#ifndef _STRUKTURY_H
#define _STRUKTURY_H

#define MAX_ROZM 50

typedef struct Plik {
    char nazwa[MAX_ROZM];
    double rozmiar;
    int prio;
}Plik;

//struktury dla drzewa

typedef struct Wezel {
    Plik P;
    struct Wezel *lewy;
    struct Wezel *prawy;
}Wezel;

typedef struct Drzewo {
    Wezel *korzen;
    int rozmiar;
}Drzewo;

/*struktura potrzebna do funkcji sprawdzajacej, czy istnieje juz plik o zadanym priorytecie
rezygnacja z trzeciego wskaznika (na ojca) w strukturze wezla skutkuje tym, ze w przeszukianiu drzewa jest potrzebna taka struktura pomocnicza*/

typedef struct Para{
    Wezel *ojciec;
    Wezel *syn;
}Para;

//struktury dla listy dwukierunkowej

typedef struct Element {
    Plik F;
    struct Element *nast;
    struct Element *poprz;
}Element;

typedef struct Lista {
    Element *glowa;
    int rozm;
}Lista;

#endif // _STRUKTURY_H
