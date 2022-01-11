	/*
	NHL-joukkueen kausisimulaattorissa valitaan NHL-joukkue, jonka runkosarja simuloidaan.
	Alun valikosta p��see inforuutuun tai suoraan simulointiin sek� halutessaan pois ohjelmasta.
	Ohjelma simuloi kaikki 82 runkosarjan peli� satunnaisessa j�rjestyksess� ja lopuksi ilmoittaa, 
	p��sisik� joukkue playoffeihin vertaamalla kauden tulosta keskim��r�isiin alarajoihin.
	Kaikki k�ytt�j�n sy�tteet k�ytet��n tarkistus-aliohjelman kautta, ettei ohjelma kaadu virheelliseen sy�tteeseen.
	Kommentointi l�ytyy p��s��nt�isesti kausisimulaattori.cpp:st�. 
	*/

#include <iostream>
#include "kausisimulaattori.h"
#include <string>
using namespace std;


int main() {

	// aloitetaan lis��m�ll� ��kk�set, koska ohjelma on suomenkielinen
	setlocale(LC_ALL, "");


	
	int valinta = 0,				// k�ytt�j�n valikkosy�te
		divisioona,					// k�ytt�j�n valitsema divisioona
		joukkue,					// k�ytt�j�n valitsema joukkue
		pistelaskuri = 0;			// kirjaa joukkueen kauden aikana saamat pisteet
	//string tarkistamatonvalinta;

	// alkuun tervetulotoivotus
	tervehdys();


	// siirryt��n ohjelman p��valikkoon
	valikko:
	valinta = valikko();


	// inforuutu ohjelman toiminnasta ja runkosarjarakenteesta
	if (valinta == 1) {

		info();
		cin >> valinta;
		valinta = tarkistus(valinta, 3);
		valinta = valinta + 1;
	}


	// varsinainen simulaattori py�rii t�ss�
	while (valinta == 2) {

		divisioona = divisioonanvalinta();
		joukkue = joukkueenvalinta();
		joukkueidenmaaritys(divisioona, joukkue);
		pistelaskuri = runkosarja(divisioona, joukkue, pistelaskuri);
		koonti(pistelaskuri);
		cin >> valinta;
		valinta = tarkistus(valinta, 2);
		valinta = valinta + 1;
		pistelaskuri = 0;

	}


	if (valinta == 3) {
		cout << "Kiitos ajastasi! Toivottavasti pidit simulaattorista. \n";
		system("pause");
		return EXIT_SUCCESS;

	}
	cout << "Jotain tapahtui, palataanpa p��valikkoon. \n";
	goto valikko;
}