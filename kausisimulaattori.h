#pragma once
#include <iostream>
#include <string>

// tervetulotoivotus
void tervehdys();

// p‰‰valikko
int valikko();

// syˆtteentarkistus
int tarkistus(int, int);

// n‰ytet‰‰n info
void info();

// valitaan divisioona
int divisioonanvalinta();

// valitaan joukkue
int joukkueenvalinta();

// muokataan toistojen m‰‰r‰‰
int toistonmuokkaus(int, int);

//ker‰t‰‰n talteen joukkueet, joita vastaan kauden aikana pelataan
void joukkueidenmaaritys(int, int);

//vaihdetaan divisioonaa
int divisioonanmaaritys(int);

//vaihdetaan konferenssia
int konferenssinvaihto(int);

//t‰‰ll‰ tapahtuu varsinainen simulointi
int runkosarja(int, int, int);

//t‰‰ll‰ ilmoitetaan pisteet ja mahdollinen playoff-paikka
void koonti(int);
