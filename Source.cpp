	/*
	NHL-joukkueen kausisimulaattorissa valitaan NHL-joukkue, jonka runkosarja simuloidaan.
	Alun valikosta pääsee inforuutuun tai suoraan simulointiin sekä halutessaan pois ohjelmasta.
	Ohjelma simuloi kaikki 82 runkosarjan peliä satunnaisessa järjestyksessä ja lopuksi ilmoittaa, 
	pääsisikö joukkue playoffeihin vertaamalla kauden tulosta keskimääräisiin alarajoihin.
	Kaikki käyttäjän syötteet käytetään tarkistus-aliohjelman kautta, ettei ohjelma kaadu virheelliseen syötteeseen.
	Kommentointi löytyy pääsääntöisesti kausisimulaattori.cpp:stä. 
	*/

#include <iostream>
#include "kausisimulaattori.h"
#include <string>
using namespace std;


int main() {

	// aloitetaan lisäämällä ääkköset, koska ohjelma on suomenkielinen
	setlocale(LC_ALL, "");


	
	int valinta = 0,				// käyttäjän valikkosyöte
		divisioona,					// käyttäjän valitsema divisioona
		joukkue,					// käyttäjän valitsema joukkue
		pistelaskuri = 0;			// kirjaa joukkueen kauden aikana saamat pisteet
	//string tarkistamatonvalinta;

	// alkuun tervetulotoivotus
	tervehdys();


	// siirrytään ohjelman päävalikkoon
	valikko:
	valinta = valikko();


	// inforuutu ohjelman toiminnasta ja runkosarjarakenteesta
	if (valinta == 1) {

		info();
		cin >> valinta;
		valinta = tarkistus(valinta, 3);
		valinta = valinta + 1;
	}


	// varsinainen simulaattori pyörii tässä
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
	cout << "Jotain tapahtui, palataanpa päävalikkoon. \n";
	goto valikko;
}