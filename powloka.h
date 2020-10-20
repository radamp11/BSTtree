#ifndef _POWLOKA_H
#define _POWLOKA_H

#include "struktury.h"

void CzyscBuf ( void );

Plik WczytajPlik ( void );

void Powitanie ( void );

void DrukujPomoc ( void );

void PomocDodajPlik ( void );

void PomocUsunPlik ( void );

void PokazPrzed ( Drzewo *drz );

void PokazPo ( Lista * lstaa );

void Polacz ( bool *zmienna );

void Dodaj ( Drzewo *drz );

void Usun ( Drzewo *drz );

void Wyslij ( Drzewo *drz, Lista *lsta );

void Wyjscie ( Drzewo *drz, Lista *lst );

#endif // _POWLOKA_H
