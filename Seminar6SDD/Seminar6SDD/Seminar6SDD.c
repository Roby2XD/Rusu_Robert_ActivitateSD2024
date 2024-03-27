#include<stdio.h>
#include<malloc.h>

typedef struct CafeneaMea Cafenea;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct CafeneaMea {
    char* nume;
    int nrLocuri;
    float suprafata;
};

struct Nod {
    Cafenea cafenea;
    Nod* anterior;
    Nod* urmator;
};

struct ListaDubla {
    Nod* cap;
    Nod* coada;
};

void inserareInceput(ListaDubla* listaDubla, Cafenea cafenea) {
    Nod* nou = malloc(sizeof(Nod));
    nou->anterior = NULL;
    nou->cafenea = cafenea;
    nou->urmator = listaDubla->cap;
    if (listaDubla->cap != NULL) {
        listaDubla->cap->anterior = nou;
    }
    else {
        listaDubla->coada = nou;
    }
    listaDubla->cap = nou;
}


Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
    Cafenea cafenea;
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;
    cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(cafenea.nume, nume);

    return cafenea;
}


void afisareCafenea(Cafenea c) {
    printf("\nDenumire: %s Nr scaune: %i Suprafata %.2f\n", c.nume, c.nrLocuri, c.suprafata);
}

void afisareLista(ListaDubla listaDubla) {
    Nod* nod = listaDubla.cap;
    while (nod) {
        afisareCafenea(nod->cafenea);
        nod = nod->urmator;
    }
    printf("\n\n");
}

ListaDubla stergeCafeneaDupaNume(ListaDubla listaDubla, const char* nume) {
    if (nume == NULL) {
        return listaDubla;
    }
    Nod* nod = listaDubla.cap;
    while (nod && strcmp(nod->cafenea.nume,nume) != 0) {
        
        nod = nod->urmator;
    }
    if (nod != NULL) {
        if (nod->urmator == NULL && nod->anterior == NULL) {
            listaDubla.cap = NULL;
            listaDubla.coada = NULL;
        }
        else {
            if (nod->anterior == NULL) {
                listaDubla.cap = nod->urmator;
                listaDubla.cap->anterior = NULL;
            }
            else if (nod->urmator == NULL) {
                listaDubla.coada = nod->anterior;
                listaDubla.coada->urmator = NULL;
            }
            else {
                nod->anterior->urmator = nod->urmator;
                nod->urmator->anterior = nod->anterior;
            }
        }
        free(nod->cafenea.nume);
        free(nod);
    }
    return(listaDubla);
}

ListaDubla stergereLista(ListaDubla listaDubla) {
    while (listaDubla.cap != NULL) {
        free(listaDubla.cap->cafenea.nume);
        Nod* temp = listaDubla.cap;
        listaDubla.cap = listaDubla.cap->urmator;
        free(temp);
    }
    listaDubla.cap = NULL;
    listaDubla.coada = NULL;
    return listaDubla;
}

int NrTotalLocuri(ListaDubla lista) {
    if (lista.cap == NULL) {
        return 0;
    }

    int nrLocuri = 0;
    Nod* nod = lista.coada;
    while (nod != NULL) {
        nrLocuri += nod->cafenea.nrLocuri;
        nod = nod->anterior;
    }

    return nrLocuri;
}


void main() {
    Cafenea cafenea = initializareCafenea("Tucano", 12, 20);
    Cafenea cafenea2 = initializareCafenea("Caf2", 17, 17.3);
    Cafenea cafenea3 = initializareCafenea("Caf3", 19, 33);
    Cafenea cafenea4 = initializareCafenea("Caf4", 22, 35);


    ListaDubla listaDubla;
    listaDubla.cap = NULL;
    listaDubla.coada = NULL;

    inserareInceput(&listaDubla, cafenea);
    inserareInceput(&listaDubla, cafenea2);
    inserareInceput(&listaDubla, cafenea3);
    inserareInceput(&listaDubla, cafenea4);

    afisareLista(listaDubla);

    /*listaDubla = stergeCafeneaDupaNume(listaDubla,"Caf2");
    afisareLista(listaDubla);

    listaDubla = stergeCafeneaDupaNume(listaDubla,"Tucano");
    afisareLista(listaDubla);

    listaDubla = stergeCafeneaDupaNume(listaDubla,"Caf3");
    afisareLista(listaDubla);

    listaDubla = stergeCafeneaDupaNume(listaDubla,"Caf4");
    afisareLista(listaDubla);*/

    printf("Nr locuri totale: %d", NrTotalLocuri(listaDubla));

    listaDubla = stergereLista(listaDubla);
    afisareLista(listaDubla);

    

    






  

}

