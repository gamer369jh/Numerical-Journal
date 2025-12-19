#ifndef ARTICLE_TEST_H_INCLUDED
#define ARTICLE_TEST_H_INCLUDED
#include <time.h>



typedef struct auteur
{
  char prenom[200];
  char nom [200];
}auteur;

typedef struct article
{
    char titre[2000];
    struct tm date_et_heure;
    auteur auteur;
    char categorie[2000];
    char texte[399999];
    int id;
}article;

struct noeud
{
    article art;
    struct noeud* suiv;
};typedef struct noeud noeud;

typedef struct liste
{
    noeud *tete;
}liste;
int read_number();
auteur saisir_auteur();
article saisir_article(int id);
void delay(int x);
void couleur(int x);
char* espace(char* ch);
char* tiree(char* ch);

//********************************************  FCT DE LISTE CHAINEE  ************************************
void inserer_fin(article x,liste *l);
int nbrelem_liste(liste *l);
void liste_vide(liste *l);
noeud *rechecher_article(liste *l, int id);
int supprimer_article(liste *l,int n);
void miseajour_article(liste *l);
int verifier_id(liste *l);
void tri_article_down(liste *l);
void tri_article_up(liste *l);
void afficher_article(liste *l);

#endif


