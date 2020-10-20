#ifndef _FUN_DRZEWA_H
#define _FUN_DRZEWA_H

#include "struktury.h"

//wszystkie deklaracje sa umieszczone w kolejnosci odpowiadajacej implementacji w ciele

bool DodajPlik ( Plik *Pl, Drzewo *drz );

bool UsunPlik ( Plik *pl, Drzewo *drz );

void DrukujPlik ( Plik pl );

void Przejdz ( Drzewo *drzewko );

void UsunDrzewko ( Drzewo *drz );
//--------------------------------------------

void DodajPlikDoListy ( Plik *Pl, Lista *lista );

void DrukujListe ( Lista *listaa );

void UsunListe ( Lista *listaa );
//--------------------------------------------

void WyslijPliki ( Drzewo *drz , Lista *listaa );

#endif // _FUN_DRZEWA_H
