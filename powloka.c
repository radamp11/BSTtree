#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fun_drzewa.h"

#define MAX_ROZM_KOM 18

void CzyscBuf ( void ){
    int S;
    while( ( S = getchar() ) != '\n' && S != EOF );
}

//------------wczytywanie ze strumienia-------------

Plik WczytajPlik ( void ){
    Plik nowy;
    while ( 3 != scanf ( "%50s %lf %d", nowy.nazwa, &nowy.rozmiar, &nowy.prio ) || nowy.prio <= 0 ){
        puts ( "Podales bledne dane. Pamietaj, ze priorytet musi byc liczba calkowita dodatnia.\nPoprawna skladnia: nazwa_pliku, rozmiar_pliku, priorytet_pliku\nSprobuj ponownie: ");
        CzyscBuf();
    }
    return nowy;
}

//-------------drukowanie na standardowe wyjscie---------------------

void Powitanie ( void ){
puts("########################################################");
puts("########## BEZPOSREDNIE LACZE JEDNOKIERUNKOWE ##########");
puts("########################################################");
puts("\n***Witaj!***\n\nJezeli potrzebujesz pomocy, wpisz komende  pomoc , a otrzymasz informacje o dostepnych operacjach.\n");
puts("Powiedz mi, co mam zrobic:\n");
}

void DrukujPomoc ( void ){
    putchar('\n');
    puts("NAJWAZNIEJSZE: po wpisaniu kazdej komendy wcisnij klawisz Enter - w przeciwnym wypadku program moze wczytac nieprawilowe dane!\n");
    puts(" pomoc nazwa_polecenia - wyswietla skladnie danej instrukcji.");
    puts("                         Zauwaz, ze ta komende mozesz zastosowac tylko do polecen dodaj_plik oraz usun_plik");
    puts("                         Reszta polecen nie wymaga wpisania nic oprocz samego polecenia.");
    puts(" polacz - nawiazuje polaczenie bezprzewodowe z drugim uzytkownikiem.");
    puts(" dodaj_plik - plik wybrany przez uzytkownika zostaje dodany do kolejki wysylania.");
    puts(" usun_plik - plik wybrany przez uzytkownika zostaje usuniety z kolejki wysylania.");
    puts(" wyslij - komenda wysyla do drugiego uzytkownika wszystkie pliki w kolejce w kolejnosci okreslonej priorytetem.");
    puts(" pokaz_przed - wyswietla liste plikow oczekujacych na wyslanie.");
    puts(" pokaz_po - wyswietla liste poprawnie przeslanych plikow.");
    puts(" wyjscie - zamyka program.");
    putchar('\n');
}

void PomocDodajPlik ( void ){
    puts("\ndodaj_plik nazwa_pliku rozmiar_pliku priorytet_przesylania\n");
}

void PomocUsunPlik ( void ){
    puts("\nusun_plik nazwa_pliku rozmiar_pliku priorytet_przesylania\n");
}

void PokazPrzed ( Drzewo *drz ){
    putchar('\n');
    if ( drz->rozmiar == 0 )
        puts("Brak plikow w kolejce do wyslania.");
    else{
        puts("____________________________________");
        Przejdz( drz );
        puts("____________________________________");
    }
    putchar('\n');
}

void PokazPo ( Lista * lstaa ){
    putchar('\n');
    if ( lstaa->glowa == NULL )
        puts("Jeszcze zaden plik nie zostal przeslany!");
    else{
        puts("____________________________________");
        DrukujListe( lstaa );
        puts("____________________________________");
    }
    putchar('\n');
}

//-------------------------------------------------

void Polacz ( bool *zmienna ){
    putchar('\n');
    if ( *zmienna == true )
        puts("Juz nawiazano polaczenie z drugim uzytkownikiem.");
    else{
        *zmienna = true;
        puts("Poprawnie polaczono z drugim uzytkownikiem.");
    }
    putchar('\n');
}

void Dodaj ( Drzewo *drz ){
    Plik tymczasowy;
    tymczasowy = WczytajPlik();
    if ( DodajPlik( &tymczasowy, drz ) == true )
        puts("Poprawnie dodano nowy plik do kolejki.");
    CzyscBuf();
    putchar('\n');
}

void Usun ( Drzewo *drz ){
    Plik tymczasowy;
    if ( drz->rozmiar == 0 ){
        puts("Brak plikow w kolejce!");
        return;
    }
    tymczasowy = WczytajPlik();
    if ( UsunPlik( &tymczasowy, drz ))
        puts("Plik zostal poprawnie usuniety z kolejki.");
    else
        puts("Nie ma takiego pliku!");
    CzyscBuf();
    putchar('\n');
}

void Wyslij ( Drzewo *drz, Lista *lsta ){
    putchar('\n');
    if ( drz->rozmiar == 0 ){
        puts("Brak plikow w kolejce - nie mozesz wyslac pustego pakietu danych.");
    }
    else {
        WyslijPliki( drz, lsta );
        puts("Poprawnie przeslano wszystkie pliki.\n");
    }
    putchar('\n');
}

//--------zakonczenie--------------
//czysci drzewo, liste i konczy dzialanie programu.

void Wyjscie ( Drzewo *drz, Lista *lst ){
    if ( drz->korzen != NULL ){
        UsunDrzewko( drz );
    }
    if ( lst->glowa != NULL )
        UsunListe( lst );
    puts("\n***Do widzenia!***");
}
