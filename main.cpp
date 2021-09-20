#include <iostream>
#include <string.h>
using namespace std;

char* process(const char* input);

int main() {
	const char* input    = NULL;
	const char* expected = 0;

	for (int i = 0; i < 10; i++) {
		switch (i) {
            case 0 :
                input    = "Word";
                expected = "Word";
                break;
            case 1 :
                input    = "proCESsors";
                expected = "pro-CES-sors";
                break;
            case 2 :
                input    = "Lorem ipsum dolor sit amet";
                expected = "Lo-rem ip-sum do-lor sit a-met";
                break;
            case 3 :
                input    = "using hyphenation and requiring estro estre bistro syllables";
                expected = "u-sing hy-phe-na-tion and re-qui-ring e-stro estre bi-stro syl-la-bles";
                break;
            case 4 :
                input    = "In a village of La Mancha, the name of which I have no desire to call to mind...";
                expected = "In a vil-lage of La Man-cha, the name of which I have no de-sire to call to mind...";
                break;
            case 5 :
                input    = "We are programmed to receive. You can check-out any time you like, But you can never leave!";
                expected = "We are prog-ram-med to re-cei-ve. You can check-out a-ny time you li-ke, But you can ne-ver lea-ve!";
                break;
            case 6 :
                input    = "counterclockwise counterintelligence disproportionate incomprehensible multimillionaire characteristically";
                expected = "coun-terclockwise coun-te-rin-tel-li-gen-ce dispro-por-tio-nate in-compre-hen-sible mul-ti-mil-lio-naire cha-rac-te-ri-sti-cal-ly";
                break;
            case 7 :
                input    = "chlorofluorocarbons conceptualizations electroencephalograms oversimplification";
                expected = "chlo-rof-luo-ro-car-bons con-cep-tua-li-za-tions e-lec-troen-ce-pha-log-rams o-ver-simpli-fi-ca-tion";
                break;
            case 8 :
                input    = "abbe eddi iggo axqua axtra axbra quza trza brza";
                expected = "ab-be ed-di ig-go ax-qua ax-tra ax-bra quza trza brza";
                break;
            case 9 :
                input    = "Star Wars: The Force Awakens (also known as Star Wars Episode VII: The Force Awakens) is an upcoming American epic space opera film directed by J. J. Abrams. The seventh installment in the main Star Wars film series, it stars John Boyega, Daisy Ridley, Adam Driver, Oscar Isaac, Andy Serkis, Domhnall Gleeson, and Max von Sydow, with Harrison Ford, Carrie Fisher, Mark Hamill, Anthony Daniels, Peter Mayhew, and Kenny Baker reprising their roles from previous Star Wars films. The story is set approximately 30 years after the events of Return of the Jedi (1983).";
                expected = "Star Wars: The For-ce A-wa-kens (al-so known as Star Wars E-pi-sode VII: The For-ce A-wa-kens) is an up-co-ming A-me-ri-can e-pic space o-pe-ra film di-rec-ted by J. J. A-brams. The se-venth in-stallment in the main Star Wars film se-ries, it stars John Boye-ga, Dai-sy Rid-ley, A-dam Dri-ver, Os-car I-saac, An-dy Ser-kis, Domhnall Glee-son, and Max von Sy-dow, with Har-ri-son Ford, Car-rie Fis-her, Mark Ha-mill, Antho-ny Da-niels, Pe-ter May-hew, and Ken-ny Ba-ker rep-ri-sing their ro-les from pre-vious Star Wars films. The sto-ry is set appro-xi-ma-te-ly 30 years af-ter the e-vents of Re-turn of the Je-di (1983).";
                break;
			default:
				cout << "we should never get here" << endl;
				return -1;
		}
		char* actual = process( input );
		bool  equal  = false;
		if (actual != NULL) {
		    equal  = strcmp( expected, actual ) == 0;
		}
		cout << "test " << i << ": " << (equal ? "ok" : "failed");
        if (!equal) {
            cout << " expected [" << expected
                 << "] but was [" << (actual == NULL ? "NULL" : actual) << "]";
        }
        cout << endl;

		delete actual;
	}
	return EXIT_SUCCESS;
}
