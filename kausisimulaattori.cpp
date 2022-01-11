#include <iostream>
#include <string>
#include "kausisimulaattori.h"
#include <ctime>
#include <cstdlib>
using namespace std;


const int  alaraja = 1,			// sy�tteentarkistuksessa k�ytett�v� alaraja
		divisioonat = 4,		// divisioonat, jotka muodostavat NHL:n
		joukkueet = 8,			// joukkueet per divisioona
		pelit = 82 ;			// kaudella pelattavat pelit


int		valinta = 0,			// k�ytt�j�n valikkosy�te aliohjelmien puolella
		divisioona = 0,			// k�ytt�j�n valitsema divisioona
		joukkue = 0,			// k�ytt�j�n valitsema joukkue
		toisto,					// kerroin, joka m��ritt��, montako kertaa looppia py�ritet��n
		n = 0 ,					// toinen kerroin loopille
		j,						// kerroin vastustajien kirjaamiselle
		kotipelilaskuri = 0,	// pit�m��n kirjaa kotipeleist�
		vieraspelilaskuri = 0,	// pit�m��n kirjaa vieraspeleist�
		kertoimet = 1;			// k�ytt�j�n valinta, pidet��nk� kertoimet k�yt�ss�


// joukkueet divisioonittain kaksiulotteisessa taulukossa
string Joukkueet[divisioonat][joukkueet] = { 
	{ "Boston Bruins        ", "Buffalo Sabres       ", "Detroit Red Wings    ", "Florida Panthers     ", 
	"Montreal Canadiens   ", "Ottawa Senators      ", "Tampa Bay Lightning  ", "Toronto Maple Leaves " },
	{ "Carolina Hurricanes  ", "Columbus Blue Jackets", "New Jersey Devils    ", "New York Islanders   ", 
	"New York Rangers     ", "Philadelphia Flyers  ", "Pittsburgh Penguins  ", "Washington Capitals  " },
	{ "Anaheim Ducks        ", "Arizona Coyotes      ", "Calgary Flames       ", "Edmonton Oilers      ", 
	"Los Angeles Kings    ", "San Jose Sharks      ", "Vancouver Canucks    ", "Vegas Golden Knights " },
	{ "Chicago Blackhawks   ", "Colorado Avalanche   ", "Dallas Stars         ", "Minnesota Wild       ", 
	"Nashville Predators  ", "St. Louis Blues      ", "Winnipeg Jets        "} };


//  joukkueiden viralliset lyhenteet samassa j�rjestyksess� kuin taulukossa Joukkueet
string Lyhenteet[divisioonat][joukkueet] = { 
	{ "BOS", "BUF", "DET", "FLA", "MTL", "OTT", "TBL", "TOR" },
	{ "CAR", "CBJ", "NJD", "NYI", "NYR", "PHI", "PIT", "WSH" },
	{ "ANA", "ARI", "CGY", "EDM", "LAK", "SJS", "VAN", "VGK" },
	{ "CHI", "COL", "DAL", "MIN", "NSH", "STL", "WPG" } };

// kertoimeksi tehtyihin maaleihin
int Hyokkays[divisioonat][joukkueet] = { 
	{90, 88, 85, 89, 87, 81, 92, 90 },
	{89, 87, 83, 88, 86, 89, 90, 92 },
	{85, 90, 86, 88, 81, 84, 88, 88 },
	{89, 89, 88, 84, 89, 90, 91 } };

// jakajaksi tehtyihin maaleihin
int Puolustus[divisioonat][joukkueet] = {
	{89, 85, 83, 85, 89, 79, 90, 88},
	{86, 88, 84, 86, 85, 86, 86, 89},
	{89, 88, 86, 86, 84, 87, 88, 89},
	{85, 86, 90, 86, 87, 87, 87 } };


// taulukko divisioonille
string Divisioonat[divisioonat] = 
	{ "Atlantin divisioona", "Metropolin divisioona", 	
	"Tyynenmeren divisioona", "Keskinen divisioona" };


// alusta vastustajien koonnille
string Vastustajat[pelit];


// Vastustavien joukkueiden hy�kk�ys ja puolustus pelij�rjestyksen mukaan
int Hyokkaysjarjestys[pelit];
int Puolustusjarjestys[pelit];

void tervehdys() {

	cout << "\n Tervetuloa NHL-joukkueen runkosarjasimulaattoriin! \n "
		<< "Ohjelma simuloi valitsemasi joukkueen runkosarjan NHL:ss�\n"
		<< "kauden 2020-2021 joukkuekokonaisuuksilla ja arpaonnella. \n";

}


// ohjelman p��valikko, josta edet��n muihin ohjelman osiin k�ytt�j�n
// sy�tteen perusteella
int valikko() {

	cout << " Aloita valitsemalla toiminto: \n 1. N�yt� simulaattorin ohjeet "
		<< "\n 2. Aloita simulointi \n 3. Poistu simulaattorista \n\n";
	cin >> valinta;
	valinta = tarkistus(valinta, 3);														// tsekataan laittomuudet
	return valinta;

}


// tarkistukseen otetaan aina arvoiksi k�ytt�j�n sy�te ja sy�tteen yl�raja, 
// n�in tarkistus toimii (t�ss� ohjelmassa) universaalisti jokaiselle sy�tteelle
int tarkistus(int syote, int ylaraja) {

	do {
		try {
			if (syote >= alaraja && syote  <= ylaraja) {
				break;

			}
			else {
				if (cin.fail()) 															// v��r� muuttujatyyppi
					cout << "Ei muuten n�ytt�nyt numerolta. \n";


				else if (syote < alaraja)													// liian pieni numero
					cout << "Nyt tuli v�h�n liian pieni numero. \n";

				else if (syote > ylaraja)													// liian suuri numero
					cout << "Huhhuh, nyt oli kyll� aivan liian suuri numero. \n";
				throw (syote);
			}
		}
		catch (int a) {
			cin.clear();
			cin.ignore(10000, '\n');
		cout << "Yrit�h�n seuraavaksi v�h�n enemm�n.\n";
			cin >> syote;
		}
	} while (cin.fail() || syote > ylaraja || syote < alaraja);

	return syote;

}


// infossa selitet��n runkosarjan sek� ohjelman toimintaperiaate
// sek� esitell��n NHL-konferenssit, divisioonat sek� joukkueet
void info() {

	cout << " NHL eli National Hockey League koostuu 31 j��kiekkojoukkueesta. \n"
		<< " NHL-joukkueet on jaettu kahteen konferenssiin, jotka molemmat \n"
		<< " on jaettu kahteen divisioonaan. \n\n"
		<< " Jokainen joukkue pelaa yhden kauden runkosarjan aikana yhteens� 82 peli�, \n"
		<< " joista suurin osa pelataan oman konferenssin joukkueita vastaan. \n\n";

	cout << " Jako tapahtuu seuraavasti: \n";
	cout << "\n\t\t\t It�inen konferenssi: \n";
	cout << "\n " << Divisioonat[0] << ": \t\t\t\t " << Divisioonat[1] << ":\n\n";

	for (int i = 0; i < 8; i++) {
		cout << Joukkueet[0][i] << " (" << Lyhenteet[0][i] << ") " << "\t\t\t"		// tulostetaan joukkueiden
			<< Joukkueet[1][i] << " (" << Lyhenteet[1][i] << ") " << endl;			// nimet ja lyhenteet
	}																				// n�ttin� taulukkona
																					// konferensseittain ja
	cout << "\n\t\t\t L�ntinen konferenssi: \n";									//divisioonittain
	cout << "\n " << Divisioonat[2] << ": \t\t\t " << Divisioonat[3] << ":\n\n";	

	for (int i = 0; i < 8; i++) {
		cout << Joukkueet[2][i] << " (" << Lyhenteet[2][i] << ") " << "\t\t\t";
		if (i == 7) break;															// t�m� l�nnen 7-joukkueisen
		cout << Joukkueet[3][i] << "(" << Lyhenteet[3][i] << ") " << endl;			// "tynk�divisioonan" vuoksi	
	}
	cout << "\n\n Simulaattori ottaa huomioon kunkin joukkueen hy�kk�ys-, puolustus- \n"
		<< " sek� maalivahtikokonaisuudet ja kertoo, miten valitsemasi joukkue \n"
		<< " olisi voinut pelata, jos pandemian sijaan oltaisiin voitu pelata j��kiekkoa. \n\n";

	cout << "\n\n Haluatko aloittaa joukkueen valinnan vai sulkea ohjelman?"
		<< "\n 1. Aloita valinta \n 2. Sulje ohjelma \n\n";

}


// k�ytt�j� valitsee divisioonan
int divisioonanvalinta() {

	cout << " Aloita valitsemalla divisioona, josta haluat valita joukkueen: \n";
	for(int i = 0; i < 4; i ++)
		cout << i + 1 << ". " << Divisioonat[i] << endl;

	cin >> divisioona;
	divisioona = tarkistus(divisioona, 4);											// tsekataan laittomuudet
	divisioona = divisioona - 1;
	cout << "\n Valintasi on " << Divisioonat[divisioona] << ". \n" ;

	return divisioona;
}

// k�ytt�j� valitsee joukkueen
int joukkueenvalinta() {

	cout << "\n Valitse seuraavaksi joukkue, jonka kauden haluat simuloida: \n";
	toisto = toistonmuokkaus(toisto, divisioona);									// oikea m��r� toistoja divisioonan
																					// perusteella
	for (int i = 0; i < toisto; i++)												
		cout << i + 1 << ". " << Joukkueet[divisioona][i] << "\t" << Lyhenteet[divisioona][i] << endl;
	cin >> joukkue;
		joukkue = tarkistus(joukkue, toisto);										// tsekataan laittomuudet
	joukkue = joukkue - 1;

	cout << " Valitsit joukkueen " << Joukkueet[divisioona][joukkue] 
		<< "(" << Lyhenteet[divisioona][joukkue] << ") " << endl;

	cout << " Haluatko k�ytt�� simulaatiossa joukkuekohtaisia kertoimia, \n"		// mahdollisuus poistaa kertoimet k�yt�st�
		<< " vai haluatko simulaation olevan t�ysin sattumanvarainen? \n"
		<< "1. Kertoimet heti t�nne nyt! \n"
		<< "2. Ehkei t�ll� kertaa, kannatan tilastollisesti huonoa joukkuetta. \n";
	cin >> kertoimet;
	kertoimet = tarkistus(kertoimet, 2);
	return joukkue;
}


// pit�� ottaa huomioon, ett� yhdess� divisioonassa on v�hemm�n joukkueita
int toistonmuokkaus(int toisto, int divisioona) {

	if (divisioona < 3)
		toisto = 8;
	else if (divisioona == 3)
		toisto = 7;

	return toisto;
}


// ker�t��n talteen joukkueet, joita vastaan kauden aikana pelataan
void joukkueidenmaaritys(int divisioona, int joukkue) {

	 j = 0;
	for (int ylaraja = 4; ylaraja > 0; ylaraja--) {								// k�yd��n kaikki divisioonat l�pi
																				// divisioonaa vaihtaessa toistojen 
		while (n < ylaraja) {													// m��r� v�henee, koska pelataan
			if (ylaraja < 4) {
				toisto = toistonmuokkaus(toisto, divisioona);					// oikea m��r� toistoja divisioonan
			}
			
			for (int i = 0; i < toisto && j < pelit; i++) {						// kirjataan vastustajien lyhenteet taulukkoon
				if (i == joukkue && ylaraja == 4) {								// poistetaan valittu joukkue listasta
					if (joukkue == 6 && divisioona == 3 || joukkue == 7 && divisioona != 3)
						goto skippaa;											// ei laiteta vahingossa tyhj�� sis�lt�� jakajaan
					i++;														// se olisi hyvin laitonta
				}
				Vastustajat[j] = Lyhenteet[divisioona][i];
				Hyokkaysjarjestys[j] = Hyokkays[divisioona][i];
				Puolustusjarjestys[j] = Puolustus[divisioona][i];
				j++;
			}
			skippaa:
			n++;
		}

		n = 0;																	// palautetaan kerroin
		if (ylaraja == 1 && j < pelit) {										// kahta divisioonaa vastaan pelataan kahdesti
			ylaraja++;															
			if (j > 78 && divisioona < 2)										// huomioidaan tynk�divisioonan vaikutus
				divisioona = konferenssinvaihto(divisioona);					// l�nnen pelim��r��n ja t�ytet��n oikeilla
		}																		// joukkueilla

		else if (ylaraja == 4 || ylaraja == 2)									// divisioonan vaihto
			divisioona = divisioonanmaaritys(divisioona);
		else if (ylaraja == 3 || ylaraja == 1)									// konferenssin vaihto
			divisioona = konferenssinvaihto(divisioona);
	}

}


// varsinainen kauden simulointi
int runkosarja(int divisioona, int joukkue, int pistelaskuri) {


	for (int i = 0; i < pelit; i++) {
		int index = rand() % pelit;												// laitetaan vastustajat
		string joukkuetemp = Vastustajat[i];									// satunnaiseen j�rjestykseen
		int hyokkaystemp = Hyokkaysjarjestys[i];								// (mukaanlukien joukkueen hy�kk�ys-
		int puolustustemp = Puolustusjarjestys[i];								// ja puolustuskertoimet)
		Vastustajat[i] = Vastustajat[index];
		Hyokkaysjarjestys[i] = Hyokkaysjarjestys[index];
		Puolustusjarjestys[i] = Puolustusjarjestys[index];
		Vastustajat[index] = joukkuetemp;
		Hyokkaysjarjestys[index] = hyokkaystemp;
		Puolustusjarjestys[index] = puolustustemp;
	}

	cout << " Koti\t\t\t\t Vieras" << endl;
	for (int i = 0; i < pelit; i++) {
		int oma = rand() % 6;													// arvotaan molemmille joukkueille
		int vieras = rand() % 6;												// maalit sopivalta v�lilt�
		int koti = rand() % 2 + 1; ;											// arvotaan kotijoukkue
		if (kertoimet == 1) {													// jos k�ytet��n kertoimia, muokataan maaleja
			oma = oma * (Hyokkays[divisioona][joukkue] / (Puolustusjarjestys[i]));
			vieras = vieras * (Hyokkaysjarjestys[i] / (Puolustus[divisioona][joukkue]));
		}
		if (oma != vieras) {													//jos peli ratkeaa varsinaisella peliajalla


			if (koti == 1 && kotipelilaskuri < 42) {							// laskureilla varmistetaan, ettei koti- tai vieraspelej�
				cout << Lyhenteet[divisioona][joukkue] << "\t\t" << oma << " - "// tule liikaa
					<< vieras << "\t\t" << Vastustajat[i];						// kotipelin tulosten n�ytt�

			}
			else if (vieraspelilaskuri < 42 || kotipelilaskuri >= 42) {
				cout << Vastustajat[i] << "\t\t" << vieras << " - " 			// vieraspelin tulosten n�ytt�
					<< oma << "\t\t" << Lyhenteet[divisioona][joukkue];
						
			}
			

			if (oma > vieras)
				cout << "\tV\n";												// voitto
			else cout << "\tH\n";												// h�vi�

			if (oma > vieras)
				pistelaskuri = pistelaskuri + 2;								// voiton pisteiden kirjaaminen
		}

		if (oma == vieras) {		
			int jatkoaika = rand() % 2 + 1;										// arvotaan jatkoajan voittaja								

			if (jatkoaika == 1) {
				oma = oma + 1;
				pistelaskuri = pistelaskuri + 2;								// jatkoaikavoiton pisteiden kirjaaminen
			}

			else if (jatkoaika == 2) {
				vieras = vieras + 1;
				pistelaskuri = pistelaskuri + 1;								// jatkoaikah�vi�n pisteiden kirjaaminen
			}

	

			if (koti == 1) {
				cout << Lyhenteet[divisioona][joukkue] << "\t\t" << oma << " - "
					<< vieras << "\t\t" << Vastustajat[i];

			}

			else {
				cout << Vastustajat[i] << "\t\t" << vieras << " - " 			// tulosten n�ytt� k�ytt�j�lle
					<< oma << "\t\t" << Lyhenteet[divisioona][joukkue];
			}
			if (oma > vieras)
				cout << "\tJAV\n";												// jatkoaikavoitto
			else cout << "\tJAH\n";												// jatkoaikah�vi�
		}
		
	}
	kotipelilaskuri = 0;
	vieraspelilaskuri = 0;
	return pistelaskuri;														// pistesaldon palautus mainiin
}





int divisioonanmaaritys(int divisioona) {
	if (divisioona == 0 || divisioona == 2)										// vaihdetaan divisioonaa 
		divisioona = divisioona + 1;											// konferenssin sis�ll�

	else if (divisioona == 1 || divisioona == 3)
		divisioona = divisioona - 1;

	return divisioona;
}

int konferenssinvaihto(int divisioona) {
	if (divisioona == 0 || divisioona == 1)										// vaihdetaan divisioonaa
		divisioona = divisioona + 2;											// toiseeen konferenssiin

	else if (divisioona == 2 || divisioona == 3)
		divisioona = divisioona - 2;

	return divisioona;
}


// t��ll� kootaan n�yt�lle kauden tulos ja ilmoitetaan k�ytt�j�lle, p��sisik� joukkue
// keskivertokaudella playoffeihin
void koonti(int pistelaskuri) {

	cout << "\n Joukkue sai kaudella " << pistelaskuri << " pistett�. \n";
	if (pistelaskuri >= 95)
		cout << "Joukkue p��see suoraan playoffeihin! \n\n";
	else if (pistelaskuri >= 80)
		cout << "Joukkue voi p��st� villikorttina playoffeihin! \n\n";
	else if (pistelaskuri < 80)
		cout << "Joukkue j�� playoffien ulkopuolelle.\n\n";
	cout << "Haluatko palata divisioonan valintaan vai poistua? "
		<< "\n 1. Palataan divisioonan valintaan! \n 2. Lopetetaan t�lt� er��." << endl;

}
