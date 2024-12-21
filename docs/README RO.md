# YP compiler

Puteti gasi versiunea in engleza a acestui document [aici](./../README.md).

## Utilizare (în rădăcina proiectului)

- pentru o vizualizare îmbunătățită, recomandăm VS Code și extensia „Better Comments”
0. „./setup.sh” - verifică instalarea bison și flex și construiește compilatorul nostru
0. „./compile.sh” - construiește compilatorul personalizat
0. „./src/discard.sh” - șterge fișierele suplimentare
0. „./run.out <file_path>” - compilează și rulează codul sursă

## Funcții

- Funcțiile principale ale lui C în programul nostru se numește master:
    - programul începe prin apelarea master
    - master() nu returnează nicio valoare

- array-uri x-dimensionale, unde x poate fi orice valoare naturală diferită de NULL. același lucru este asigurat și pentru dimensiunea fiecărei dimensiuni.

- inițializarea NULL a datelor la declarare dacă utilizatorul nu furnizează o atribuire
- Recunoaște atât int[1][3] nume_valoare, cât și int nume_valoare[14][5151][62];

## Limitări

- Fără pointeri sau referințe
- Nu există definiții union, struct
- Fără funcție de casting
- Fără moștenire a claselor (fără specificator de acces protejat)
- Fără supraîncărcarea metodelor

## Brainstorming

- Patru tipuri posibile de stocare a datelor:
    - class(tip)
    - funcție
    - variabilă
    - obiect
- Trei stări posibile ale unei stocări de date:
    - declarație
    - definiție
    - apel
- Există o diferență majoră între declarat și definit. Va trebui să stocăm atât declarații, cât și definiții și să le utilizăm în funcție de scenariul adecvat.