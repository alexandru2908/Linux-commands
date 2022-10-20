Predescu Ioan-Alexandru 313CB
Functia SRD_fis parcurge un abrobe de tip fisier in ordinea stanga radacina dreapta
si afiseaza numele acestuia.
Functia SRD_dir parcurge un abrobe de tip fisier in ordinea stanga radacina dreapta
si afiseaza numele acestuia.
Functia free_fis elibereaza memoria pentru celulele de tip fisier.
Functia free_tot elbereaza celulele de tip director apoi pe cele de tip fisier,
prin apelarea functiei free_fis.
Functia LS parcurge cu ajutorul functiilor SRD_fis si SRD_dir pentru a afisa 
fisierele si directoarele din directorul curent.
Functia Fr_dir aloca memorie pentru o celula de tip director initializata cu NULL,
in care se copiaza doar numele directorului.
Functia Fr_fis aloca memorie pentru o celula de tip fisier initializata cu NULL,
in care se copiaza doar numele fisierului.
Functia exista_fis verifica in sistemul de fisiere daca exista un fisier dat ca
parametru si intoarce 1 daca DA, 0 daca NU.
Functia exista_dir verifica in sistemul de directoare daca exista un director dat ca
parametru si intoarce 1 daca DA, 0 daca NU.
Functia Inserare_touch are ca parametri directorul curent, fisierul ce trebuie inserat 
si parintele, apeland functia Fr_fis pt a aloca o celula dupa care se gaseste
locul corespuzator in functie de pozitia lexicografica si se insereaza.
Functia Inserare_mkdir are ca parametri directorul curent, directorul ce trebuie inserat 
si parintele, apeland functia Fr_dir pt a aloca o celula dupa care se gaseste
locul corespuzator in functie de pozitia lexicografica si se insereaza.
Functia RM copiaza intr-un arbore auxiliar toate celulele fara cele ce trebuie sterse,
apoi sunt inserate in arborele curent.
Functia RMDIR copiaza intr-un arbore auxiliar toate celulele fara cele ce trebuie sterse,
apoi sunt inserate in arborele curent.
Functia CD cauta fisierul dat in sistem si modifica parintele directorului curent.
Functia PWD parcurge fiecare parinte pana la root si il afiseaza.
Functia exista_fis_in_tot verifica prima data data exista fisierul dat ca parametru 
in directorul curent si afiseaza prin PWD calea acestuia daca exista. Se parcurge 
sistemul si se verifica fiecare element.
Functia exista_dir_in_tot verifica prima data data exista directorul dat ca parametru 
in directorul curent si afiseaza prin PWD calea acestuia daca exista. Se parcurge 
sistemul si se verifica fiecare element.
In main se initializeaza pentru prima data root-ul cu valorile date iar pentru
inceput directorul curent va fi root. Apoi se citeste de la tastatura linie cu linie
pana la introducerea lui "quit" si se executa comenzile date. Pentru touch si mkdir 
se verifica inainte si daca mai exista un fisier sau un director in sistem. Daca 
da se va afisa un mesaj corespunzator.
Se verifica la fel si pentru rmdir, rm si cd daca exista fisierul/directorul citit.
Pentru find se verifica daca se aplica pentru un fisier sau director apoi se apleaza functia 
exista_fis_in_tot/exista_dir_in_tot si daca nu exista ce cautam in sistem afisam un mesaj.
