#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "powloka.h"

#define MAX_ROZM_KOM 18

int main ( void ) {
    const char *pomoc = "pomoc\n";
    const char *pomocdod = "pomoc dodaj_plik\n";
    const char *pomocusun = "pomoc usun_plik\n";
    const char *polacz = "polacz\n";
    const char *dodajplik = "dodaj_plik\n";
    const char *usunplik = "usun_plik\n";
    const char *pokazprzed = "pokaz_przed\n";
    const char *pokazpo = "pokaz_po\n";
    const char *wyslij = "wyslij\n";
    const char *wyj = "wyjscie\n";

    Drzewo Drz;
    Drz.korzen = NULL;
    Drz.rozmiar = 0;

    Lista Lst;
    Lst.glowa = NULL;
    Lst.rozm = 0;

    Powitanie();

    bool polaczono = false;

    char odpowiedz[MAX_ROZM_KOM+1];

    while ( strcmp ( fgets( odpowiedz , MAX_ROZM_KOM , stdin ) , wyj ) != 0){
        if ( odpowiedz == NULL ){
            puts("Blad wczytywania danych!");
            exit ( EXIT_FAILURE );
        }
        if ( strcmp ( odpowiedz , pomoc ) == 0 )
            DrukujPomoc();
        else if ( strcmp ( odpowiedz , pomocdod ) == 0 )
                PomocDodajPlik();
        else if ( strcmp ( odpowiedz , pomocusun ) == 0 )
                PomocUsunPlik();
        else if ( strcmp ( odpowiedz , polacz ) == 0 )
                Polacz( &polaczono );
        else if ( strcmp ( odpowiedz , dodajplik ) == 0 )
                Dodaj( &Drz );
        else if ( strcmp ( odpowiedz , usunplik ) == 0 )
                Usun( &Drz );
        else if ( strcmp ( odpowiedz , pokazprzed ) == 0 )
                PokazPrzed( &Drz );
        else if ( strcmp ( odpowiedz , pokazpo ) == 0 ){
                if ( polaczono == true )
                    PokazPo( &Lst );
                else
                    puts("Aby wyswietlic wyslane pliki musisz najpierw nawiazac polaczenie.");
        }
        else if ( strcmp ( odpowiedz , wyslij ) == 0 ){
                if ( polaczono == true )
                    Wyslij( &Drz, &Lst );
                else
                    puts("Aby wyslac pliki musisz najpierw nawiazac polaczenie.");
        }
        else{
            puts("Nie znam twojej komendy. Wpisz pomoc, aby uzyskac informacje na temat dostepnych operacji.");
        }
    }
    Wyjscie( &Drz , &Lst );

return 0;
}
