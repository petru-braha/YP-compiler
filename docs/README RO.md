# Compilatorul YP

Puteți găsi versiunea în limba engleză a acestui document [aici](/README.md).
În acest proiect au fost luate în considerare principiile test-driven development.

## Utilizare

- pentru îmbunătățirea redabilității, recomandăm VS Code și extensia „Better Comments”
- să fie trecute în terminalul rădăcină al proiectului:

0. „./setup.sh” - verifică instalarea bison și flex și construiește compilatorul nostru
0. „./build.sh” - construiește compilatorul personalizat
0. „./src/discard.sh” - șterge fișierele suplimentare
0. „./run.out <file_path>” - compilează și rulează codul sursă

## Tehnologii

0. C++
0. Flex
0. Yacc/Bison

## Caracteristici

- Toate variabilele/parametrii/obiectele au:
    - valoare(e) explicită(e)
    - valoare(uri) implicită(e) dacă nu există o definiție dată
        - de exemplu 0, 0.0, '0', „”, true
    - niciun container nu va fi niciodată „nedefinit”

- array-uri x-dimensionale, unde x poate fi orice valoare naturală, nu NULL. același lucru este asigurat pentru dimensiunea fiecărei dimensiuni.

- Recunoașteți atât int[1][3] nume_valoare, cât și int nume_valoare[14][5151][62];

- Fiecare fișier din [directorul de exemple](/exs/) este responsabil de o regulă gramaticală.

- Consultați [detalii de implementare](/docs/brainstorm.md) pentru mai multe detalii.

## Limitări

- Nu există calificative de tip
- Fără pointeri sau referințe
- Fără union, struct
- Fără caste
- Fără moștenire a claselor (fără specificator de acces protejat)
- Fără supraîncărcarea metodelor

Translated with DeepL.com (free version)
