#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struktury.h"

//------------------funkcje drzewa----------------------
//------------------------------------------------------
//1. funkcje odpowiedzialne za dodawanie plikow do drzewa

//tworzenie nowego wêzla

static Wezel *NowyWezel ( Plik *Pl ){
    Wezel *nowy;
    nowy = ( Wezel *) malloc( sizeof(Wezel) );
    if ( nowy != NULL ){
        nowy->P = *Pl;
        nowy->lewy = NULL;
        nowy->prawy = NULL;
        }
    return nowy;
}

//dodawanie wezla. przechodzenie drzewa rekurencyjnie

static void DodajWezel ( Wezel *nowy, Wezel *korzen){
    if ( nowy->P.prio < korzen->P.prio ){
        if ( korzen->lewy == NULL )
            korzen->lewy = nowy;
        else
            DodajWezel( nowy, korzen->lewy );
    }
    else if ( nowy->P.prio > korzen->P.prio ){
        if ( korzen->prawy == NULL )
            korzen->prawy = nowy;
        else
            DodajWezel( nowy, korzen->prawy );
    }
    else{
        fprintf ( stderr, "Nie udalo sie dodac wezla. Sprawdz funkcje DodajWezel\n");
        exit( 1 );
    }
}

//sprawdzanie, czy juz zostal dodany plik o danym priorytecie

static bool CzyJuzJestPrio ( Plik *Pl, Drzewo *drz ){
    Para szukaj;
    szukaj.ojciec = NULL;
    szukaj.syn = drz->korzen;
    if ( szukaj.syn == NULL ){
        return false;
    }
    while ( szukaj.syn != NULL ){
        if ( Pl->prio > szukaj.syn->P.prio ){
            szukaj.ojciec = szukaj.syn;
            szukaj.syn = szukaj.syn->prawy;
        }
        else if( Pl->prio < szukaj.syn->P.prio ){
            szukaj.ojciec = szukaj.syn;
            szukaj.syn = szukaj.syn->lewy;
        }
        else if( Pl->prio == szukaj.syn->P.prio ){
            return true;
        }
    }
    return false;
}

//dodawanie pliku do drzewa (kolejki)

bool DodajPlik ( Plik *Pl, Drzewo *drz ){
    if ( CzyJuzJestPrio( Pl, drz ) == true ){
        fprintf( stderr, "Nie mozesz dodac pliku o zadanym priorytecie, poniewaz inny plik juz ma taki priorytet przesylania.\n");
        return false;
    }
    Wezel *nowy;
    nowy = NowyWezel( Pl );
    if ( nowy == NULL){
        fprintf( stderr, "Nie udalo sie utworzyc nowego miejsca w kolejce przeslylania.\n");
        return false;
    }
    drz->rozmiar++;
    if ( drz->korzen == NULL )
        drz->korzen = nowy;
    else
        DodajWezel( nowy, drz->korzen );
    return true;
    //zwraca prawde, gdy pomyslnie dodano nowy plik
}

//2. funkcje odpowiedzialne za usuwanie danego pliku

//zwraca adres pary, w ktorej syn przechowuje poszukiwany plik

static Para Znajdz ( Plik *Pl, Drzewo *drz ){
    Para szukaj;
    szukaj.ojciec = NULL;
    szukaj.syn = drz->korzen;
    if ( szukaj.syn == NULL ){
        return szukaj;
    }
    while ( szukaj.syn != NULL ){
        if ( Pl->prio > szukaj.syn->P.prio ){
            szukaj.ojciec = szukaj.syn;
            szukaj.syn = szukaj.syn->prawy;
        }
        else if( Pl->prio < szukaj.syn->P.prio ){
            szukaj.ojciec = szukaj.syn;
            szukaj.syn = szukaj.syn->lewy;
        }
        else break;
    }
    return szukaj;
}

//funkcja usuwajaca wezel z drzewa. rozbita jest na 3 przypadki

static void UsunWezel ( Wezel **wsk ){
    Wezel *pom;
    if ( (*wsk)->lewy == NULL ){
        pom = *wsk;
        *wsk = (*wsk)->prawy;
        free(pom);
    }
    else if ( (*wsk)->prawy == NULL ){
        pom = *wsk;
        *wsk = (*wsk)->lewy;
        free(pom);
    }
    else {           //wezel ma dwoje dzieci
        for ( pom = (*wsk)->lewy ; pom->prawy != NULL ; pom = pom->prawy ); //szukam najwiekszego elementu w lewym poddrzewie, aby tam dolaczyc prawe poddrzewo
        pom->prawy = (*wsk)->prawy;
        pom = *wsk;
        *wsk = (*wsk)->lewy;
        free(pom);
    }
}

//usuwa zadany plik z drzewa (korzysta z dwoch poprzednich funkcji)

bool UsunPlik ( Plik *pl, Drzewo *drz ){
    Para szukaj;
    szukaj = Znajdz( pl, drz );
    if ( szukaj.syn == NULL )
        return false;
    if ( szukaj.ojciec == NULL )
        UsunWezel( &drz->korzen );
    else if ( szukaj.ojciec->lewy == szukaj.syn )
        UsunWezel( &szukaj.ojciec->lewy );
    else
        UsunWezel( &szukaj.ojciec->prawy );
    drz->rozmiar--;
    return true;
}

//3. funkcje odpowiedzialne za wydruk drzewa

void DrukujPlik ( Plik pl ){
    printf("%s      | %0.2lf kb   | %d \n", pl.nazwa , pl.rozmiar, pl.prio );
}

//przechodzi drzewo rekurencyjnie do wezla z plikiem o najwiekszym priorytecie oraz drukuje plik

static void PoKolei ( Wezel *korzen ){
    if ( korzen != NULL ){
        PoKolei ( korzen->prawy );
        DrukujPlik( korzen->P );
        PoKolei ( korzen->lewy );
    }
}

//wyykonuje poprzednia funkcje dla kazdego wezla

void Przejdz ( Drzewo *drzewko ){
    if ( drzewko != NULL )
        PoKolei ( drzewko->korzen );
}

//4. Usuwanie calego drzewa
//potrzebne do zwalniania pamieci na zakonczenie programu

static void TylkoUsun ( Wezel *usuwany ){
    Wezel *wlewy;
    if ( usuwany != NULL ){
        wlewy = usuwany->lewy;
        TylkoUsun( usuwany->prawy );
        free(usuwany);
        TylkoUsun( wlewy );
    }
}

void UsunDrzewko ( Drzewo *drz ){
    if ( drz != NULL )
        TylkoUsun( drz->korzen );
    drz->korzen = NULL;
    drz->rozmiar = 0;
}

//-----------------funkcje listy---------------------------
//---------------------------------------------------------
//funkcja tworzaca nowy element w liscie zawierajacy zadany plik

static Element *NowyElementListy ( Plik *pli ){
    Element *nowy;
    nowy = ( Element *) malloc( sizeof(Element) );
    if( nowy != NULL ){
        nowy->F = *pli;
        nowy->poprz = NULL;
        nowy->nast = NULL;
    }
    return nowy;
}

//funkcja dodajaca plik we wlasciwe miejsce do listy przeslanych plikow

void DodajPlikDoListy ( Plik *Pl, Lista *listaa ){
    Element *nowy;
    nowy = NowyElementListy( Pl );
    if ( nowy == NULL){
        fprintf( stderr, "Brak pamieci na urzadzeniu, do ktorego chcesz przeslac plik.\n");
        exit( 1 );
    }
    Element *tymcz;
    Element *tymcz1;
    if ( listaa->glowa == NULL ){ //gdy lista jest pusta, sprawa jest prosta
        listaa->glowa = nowy;
        listaa->rozm++;
    }
    else if ( nowy->F.rozmiar <= listaa->glowa->F.rozmiar ){ //dodawanie elementu na poczatek listy
        listaa->glowa->poprz = nowy;
        tymcz = listaa->glowa;
        nowy->nast = tymcz;
        listaa->glowa = nowy;
        listaa->rozm++;
    }
    else if ( nowy->F.rozmiar > listaa->glowa->F.rozmiar ){
        while( (nowy->F.rozmiar > listaa->glowa->F.rozmiar) && listaa->glowa->nast != NULL ){// przesuwanie wskaznika
            listaa->glowa = listaa->glowa->nast;
        }
        if ( listaa->glowa->nast == NULL && (nowy->F.rozmiar > listaa->glowa->F.rozmiar) ){//dodawanie elementu na koniec listy
            listaa->glowa->nast = nowy;
            tymcz = listaa->glowa;
            nowy->poprz = tymcz;
            listaa->rozm++;
            while ( listaa->glowa->poprz != NULL ) //cofanie wskaznika na pierwotna glowe
                listaa->glowa = listaa->glowa->poprz;
        }
        else { //dodawanie elementu w srodek listy
            tymcz = listaa->glowa->poprz;
            tymcz1 = listaa->glowa;
            tymcz->nast = nowy;
            tymcz1->poprz = nowy;
            nowy->poprz = tymcz;
            nowy->nast = tymcz1;
            listaa->rozm++;
            while ( listaa->glowa->poprz != NULL ) //cofanie wskaznika na pierwotna glowe
                listaa->glowa = listaa->glowa->poprz;
        }
    }
}
//---------drukowanie-------------

static void DrukujWyslanyElement ( Element *elem ){
    if ( elem != NULL)
        DrukujPlik( elem->F );
    if( elem->nast != NULL )
        DrukujWyslanyElement( elem->nast );
}

void DrukujListe ( Lista *listaa ){
    if( listaa->glowa != NULL )
        DrukujWyslanyElement( listaa->glowa);
}

//---------usuwanie------------

static void UsunElement ( Element *elem ){
    Element *tymczasowy = NULL;
    if ( elem != NULL ){
        if ( elem->nast != NULL )
            tymczasowy = elem->nast;
        free(elem);
    }
    if ( tymczasowy != NULL )
        UsunElement( tymczasowy );
    //else
        //exit ( EXIT_SUCCESS );
}

void UsunListe ( Lista *listaa ){
    if ( listaa->rozm != 0)
        UsunElement( listaa->glowa );
    listaa->glowa = NULL;
    listaa->rozm = 0;
}

//------------------funkcje wspolne-------------------

//przesyla plik z odpowiedniego wezla do listy a nastepnie usuwa ten wezel

static void UsunIWyslij ( Wezel *usuwany , Lista *listaa ){
    Wezel *wlewy;
    if ( usuwany != NULL ){
        wlewy = usuwany->lewy;
        UsunIWyslij( usuwany->prawy , listaa );
        DodajPlikDoListy( &(usuwany->P) , listaa );
        free(usuwany);
        UsunIWyslij( wlewy, listaa );
    }
}

//wykonuje poprzednia funkcje dla calego drzewa

void WyslijPliki ( Drzewo *drz , Lista *listaa ){
    if ( drz != NULL )
        UsunIWyslij( drz->korzen , listaa );
    drz->korzen = NULL;
    drz->rozmiar = 0;
}
