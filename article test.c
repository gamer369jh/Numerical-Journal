#include <stdio.h>
#include <stdlib.h>
#include "article test.h"
#include <time.h>
#include <string.h>
#include <windows.h>

int read_number()
{
    int num;
    char term;
    do
    {
        if(scanf("%d%c", &num, &term) != 2 || term != '\n')
        {
            couleur(1);
            printf("PLEASE ENTER AN INTEGER");
            couleur(0);
            printf("\n");
            scanf("%d%c", &num, &term);
            fflush(stdin);
        }

        else
        {
             return num;
        }
    }while(term!='\n');
    return 0;

}

void delay(int x)
{
    clock_t st=clock();
    while (clock()<x+st);
}

char* espace(char *ch)
{
    int i;
    for(i=0;i<strlen(ch);i++)
    {
        if(ch[i]=='-')
            ch[i]=' ';
    }
    return(ch);
}

char* tiree(char *ch)
{
    int i;
    for(i=0;i<strlen(ch);i++)
    {
        if(ch[i]==' ')
            ch[i]='-';
    }
    return(ch);

}
void inserer_fin(article x,liste *l)
{
    noeud *n,*parc;
    n=(noeud*) malloc(sizeof(noeud));
    n->art.id=x.id;
    n->art.date_et_heure.tm_hour=x.date_et_heure.tm_hour;
    n->art.date_et_heure.tm_min=x.date_et_heure.tm_min;
    n->art.date_et_heure.tm_sec=x.date_et_heure.tm_sec;
    n->art.date_et_heure.tm_mday=x.date_et_heure.tm_mday;
    n->art.date_et_heure.tm_mon=x.date_et_heure.tm_mon;
    n->art.date_et_heure.tm_year=x.date_et_heure.tm_year;
    strcpy(n->art.categorie,x.categorie);
    strcpy(n->art.titre,x.titre);
    strcpy(n->art.texte,x.texte);
    strcpy(n->art.auteur.nom,x.auteur.nom);
    strcpy(n->art.auteur.prenom,x.auteur.prenom);
    n->suiv=NULL;
    if(l->tete==NULL)
        l->tete=n;
    else
    {
        parc=l->tete;
        while(parc->suiv != NULL)
        {
            parc=parc->suiv;
        }
        parc->suiv=n;
    }
}
auteur saisir_auteur()
{
    int i;
    auteur auteur;
    while (1)
    {
        printf("PLEASE GIVE THE NAME OF THE AUTHOR \n");
        fflush(stdin);
        gets(auteur.nom);
        i=0;
        while (i<=strlen(auteur.nom))
        {
            if (((auteur.nom[i]>='a')&&(auteur.nom[i]<='z'))||(auteur.nom[i]==' '))
            {
               i++;
            }                                               //saisi du nom et prenom de l'auteur
            else
                {
                     break;
                     couleur(1);
                    printf("!!!!!!!!!!!!  GIVE A REAL NAME PLEASE  !!!!!!!!!!!!");
                    couleur(0);
                    printf("\n");
                }
        }
        if (i==strlen(auteur.nom))
            break;
    }
       while (1)
    {
        printf("PLEASE GIVE THE SURNAME OF THE AUTHOR \n");
        fflush(stdin);
        gets(auteur.prenom);
        i=0;
        while (i<=strlen(auteur.prenom))
        {
            if (((auteur.prenom[i]>='a')&&(auteur.prenom[i]<='z'))||(auteur.prenom[i]==' '))
            {
               i++;
            }                                        //saisi du nom et prenom de l'auteur
            else
            {
                 break;
                 couleur(1);
                 printf("!!!!!!!!!!!!  GIVE A REAL NAME PLEASE  !!!!!!!!!!!!");
                 couleur(0);
                 printf("\n");
            }
        }
        if (i==strlen(auteur.prenom))
            break;
    }
    return auteur;
}



article saisir_article(int id)
{
    article a;
    fflush(stdin);
    printf("PLEASE GIVE THE ARTICAL'S TITLE \n");
    gets(a.titre);                          //saisi du titre
    a.auteur= saisir_auteur();         //saisir auteur
    fflush(stdin);
    printf("PLEASE GIVE THE ARTICAL'S CATEGORY \n");
    gets(a.categorie);                                 //saisi du categorie
    time_t rt;
    struct tm *tinfo;
    time(&rt);
    tinfo=localtime(&rt);
    fflush(stdin);
    printf("PLEASE GIVE THE TEXT WRITTEN IN THE ARTICAL \n");          //saisir texte
    gets(a.texte);
    a.id=id;
    a.date_et_heure=*tinfo;
    return(a);
}

void couleur(int x)
{
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    if(x==2)
    {
        SetConsoleTextAttribute ( h, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
        Beep(750,200);
    }
    if(x==1)
    {
        SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY );
        Beep(1000,500);
    }
    if(x==0)
    {
        SetConsoleTextAttribute ( h, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    }
}

//**********************************************  FCT DE LISTE CHAINEE  ************************************************

void liste_vide(liste *l)
{
    l->tete=NULL;
}

int nbrelem_liste(liste *l)
{
    int i=0;
    noeud *parc=l->tete;
    while(parc!=NULL)
    {
        i=i+1;
        parc=parc->suiv;
    }
    return(i);
}

noeud* rechecher_article(liste *l, int id)
{
    noeud *parc=l->tete,*res=NULL;
    while(parc!=NULL)
    {
        if (parc->art.id==id)
        {
            res=parc;
            break;
        }
        else
            parc=parc->suiv;
    }
    return(res);
}

int supprimer_article(liste *l,int n)
{
    int des=1,id;
    noeud* p=NULL;
    while(p==NULL)
    {
        printf("GIVE THE ID OF THE ARTICAL YOU WISH TO DELETE: \n");
        id=read_number();
        p=rechecher_article(l,id);
        if(p==NULL)
        {
            couleur(1);
            printf("!!!!!!!!!!!  THIS ID IS NOT FOUND  !!!!!!!!!!!");
            couleur(0);
            printf("\n");
            while(1)
            {
                printf("(1) TRY AGAIN\n");
                printf("(0) EXIT \n");
                scanf("%i",&des);
                Beep(600,300);
                if((des==0)||(des==1))
                    break;
                else
                {
                    couleur(1);
                    printf("PLEASE ENTER 0 OR 1");
                    couleur(0);
                    printf("\n");
                }
            }
        if(des==0)
            break;
        }
    }
    if(des==1)
    {
        noeud *m ,*parc=l->tete;
        while(parc->suiv!=p)
            parc=parc->suiv;
        //m=p;
        parc->suiv=p->suiv;
        free(p);
        n=n-1;
    }
    return (n);
}



void miseajour_article(liste *l)
{
    int id,y=1,x;
    noeud *p=NULL;
    while(p==NULL)
    {
        printf("PLEASE GIVE THE ID OF THE ARTICAL YOU WISH TO MODIFY: \n");
        //scanf("%i",&id);
        id=read_number();
        p=rechecher_article(l,id);
        if(p==NULL)
        {
            couleur(1);
            printf("THIS ID IS NOT FOUND");
            couleur(0);
            printf("\n");
            printf("(1) TRY AGAIN \n");
            printf("(0) EXIT \n");
            while(1)
            {
                //scanf("%i",&y);
                y=read_number();
                Beep(600,300);
                if((y==0)||(y==1))
                    break;
                else
                {
                    couleur(1);
                    printf("PLEASE TYPE 0 OR 1\n");
                    couleur(0);
                    printf("\n");
                }
            }

        }
        if(y==0)
            break;
    }
    if(y==1)
    {
        while(1)
        {
            printf("WHAT WOULD YOU LIKE TO MODIFY ?\n");
            printf("******************************* # MENU # **********************************\n");
            printf("************************* (1) UPDATE THE TITLE ****************************\n");
            printf("**************************(2) UPDATE THE TEXT  ****************************\n");
            printf("************************* (3) UPDATE THE AUTHOR ***************************\n");
            printf("************************* (4) UPDATE THE CATEGORY *************************\n");
            printf("************************* (0) SAVE AND EXIT *******************************\n");
            while(1)
            {
                //scanf("%i",&x);
                x=read_number();
                Beep(600,300);
                if((x<5)&&(x>-1))
                    break;
                couleur(1);
                printf("!!!!!!!!!!!  PLEASE TYPE 0 / 1 / 2 / 3 / 4 !!!!!!!!!!!");
                couleur(0);
                printf("\n");

            }
            system("cls");

            switch(x)
            {
                case 1:
                    {
                       printf("PLEASE ENTER THE NEW TITLE \n");
                       fflush(stdin);
                       gets(p->art.titre);
                       break;
                    }
                case 2:
                    {
                        printf("PLEASE ENTER THE NEW TEXT \n");
                        fflush(stdin);
                        gets(p->art.texte);
                       break;
                    }
                case 3:
                    {
                        printf("PLEASE ENTER THE NEW AUTHOR \n");
                        p->art.auteur= saisir_auteur();
                        break;
                    }

                case 4:
                    {
                        printf("PLEASE ENTER THE NEW CATEGORY \n");
                        fflush(stdin);
                        gets(p->art.categorie);
                        break;
                    }
                case 0:
                    {
                        time_t rt;
                        struct tm *tinfo;
                        time(&rt);
                        tinfo=localtime(&rt);
                        p->art.date_et_heure=*tinfo;
                        break;
                    }
            }
            if( x==0)
                break;
        }


    }
}

int verifier_id(liste *l)
{
    int id;
    while(1)
    {
        couleur(2);
        printf("PLEASE ENTER THE ID OF THE ARTICAL ");
        couleur(0);
        printf("\n");
        //scanf("%i",&id);
        id=read_number();
        noeud *parc=l->tete;
        while((parc!=NULL)&&(parc->art.id!=id))
        {
            parc=parc->suiv;
        }
        if(parc==NULL)
            break;
    }
    return(id);
}

void tri_article_down(liste *l)
{
    noeud *parc=l->tete,*s=parc->suiv;
    article c;
    int i;
    for(i=0;i<nbrelem_liste(l);i++)
    {
        while(s!=NULL)
        {
            if (difftime(mktime(&(parc->art.date_et_heure)),mktime(&(s->art.date_et_heure)))>0)
            {
                c=parc->art;
                parc->art=s->art;
                s->art=c;
            }
            parc=parc->suiv;
            s=s->suiv;
        }
    }
}

void tri_article_up(liste *l)
{
    noeud *parc=l->tete,*s=parc->suiv;
    article c;
    int i;
    for(i=0;i<nbrelem_liste(l);i++)
    {
        while(s!=NULL)
        {
            if (difftime(mktime(&(parc->art.date_et_heure)),mktime(&(s->art.date_et_heure)))<0)
            {
                c=parc->art;
                parc->art=s->art;
                s->art=c;
            }
            parc=parc->suiv;
            s=s->suiv;
        }
    }
}

void afficher_article(liste *l)
{
    char ch[2000],ch1[2000];
    int r,m,s=0,id;
    noeud *parc=l->tete;
    printf("WHAT DO YOU WANT TO SEARCH BY :\n");
    printf("******************************* # MENU # **********************************\n");
    printf("************************* (1) ID ******************************************\n");
    printf("**************************(2) CATEGORY ************************************\n");
    printf("************************* (3) AUTHOR **************************************\n");
    printf("************************* (4) YEAR ****************************************\n");
    while(1)
    {
        //scanf("%i",&m);
        m=read_number();
        Beep(600,300);
        if((m<5)&&(m>0))
            break;
        couleur(1);
        printf("PLEASE ENTER 1 / 2 / 3 / 4 ");
        couleur(0);
        printf("\n");

    }
    switch(m)
    {
    case 1:
    {
        printf("PLEASE GIVE THE ID OF THE ARTICAL YOU WISH TO SHOW \n");
        //scanf("%i",&id);
        id=read_number();
        int i=0;
        while(parc!=NULL)
        {
            if (id==parc->art.id)
            {
                s=1;
                printf("The article n° %i : \n",i+1);
                printf("The title : %s \n",parc->art.titre);
                printf("The category : %s \n",parc->art.categorie);
                printf("The text : %s \n",parc->art.texte);
                printf("written by: %s %s \n",parc->art.auteur.prenom,parc->art.auteur.nom);
                printf("written in: %i/%i/%i at %i:%i:%i",(parc->art.date_et_heure.tm_year)+1900,parc->art.date_et_heure.tm_mon,parc->art.date_et_heure.tm_mday,parc->art.date_et_heure.tm_hour,parc->art.date_et_heure.tm_min,parc->art.date_et_heure.tm_sec);
                printf("\n");
                printf("---------------------------------------------------\n");
                i++;
            }
            parc=parc->suiv;
        }
            if(s==0)
            {
                couleur(1);
                printf("THIS ID DOES NOT EXIST ");
                couleur(0);
                printf("\n");
            }

        break;
    }

    case 2:
    {
        printf("PLEASE GIVE THE CATEGORY OF THE ARTICALS YOU WISH TO SHOW\n");
        scanf("%s",ch);
        int i=0;
        while(parc!=NULL)
        {
            if (ch==parc->art.categorie)
            {
                s=1;
                printf("The article n° %i : \n",i+1);
                printf("The title : %s \n",parc->art.titre);
                printf("The category : %s \n",parc->art.categorie);
                printf("The text : %s \n",parc->art.texte);
                printf("written by: %s %s \n",parc->art.auteur.prenom,parc->art.auteur.nom);
                printf("written in: %i/%i/%i at %i:%i:%i",(parc->art.date_et_heure.tm_year)+1900,parc->art.date_et_heure.tm_mon,parc->art.date_et_heure.tm_mday,parc->art.date_et_heure.tm_hour,parc->art.date_et_heure.tm_min,parc->art.date_et_heure.tm_sec);
                printf("\n");
                printf("---------------------------------------------------\n");
                i++;
            }
            parc=parc->suiv;
        }
        if (s==0)
        {
            couleur(1);
            printf("THIS CATEGORY DOES NOT EXIST");
            couleur(0);
            printf("\n");
        }
        break;
    }
    case 3:
    {
        printf("PLEASE GIVE THE SURNAME OF THE AUTHOR OF THE ARTICALS YOU WISH TO SHOW\n");
        scanf("%s",ch);
        printf("PLEASE GIVE THE NAME OF THE AUTHOR OF THE ARTICALS YOU WISH TO SHOW\n");
        scanf("%s",ch1);
        int i=0;
        while(parc!=NULL)
        {
            if ((strcmp(parc->art.auteur.nom,ch1)==0)&&(strcmp(parc->art.auteur.prenom,ch)==0))
            {
                s=1;
                printf("The article n° %i : \n",i+1);
                printf("The title : %s \n",parc->art.titre);
                printf("The category : %s \n",parc->art.categorie);
                printf("The text : %s \n",parc->art.texte);
                printf("written by: %s %s \n",parc->art.auteur.prenom,parc->art.auteur.nom);
                printf("written in: %i/%i/%i at %i:%i:%i",(parc->art.date_et_heure.tm_year)+1900,parc->art.date_et_heure.tm_mon,parc->art.date_et_heure.tm_mday,parc->art.date_et_heure.tm_hour,parc->art.date_et_heure.tm_min,parc->art.date_et_heure.tm_sec);
                printf("\n");
                printf("---------------------------------------------------\n");
                i++;
            }
            parc=parc->suiv;
        }
        if (s==0)
        {
            couleur(1);
            printf("THIS AUTHOR DOES NOT EXIST");
            couleur(0);
            printf("\n");
        }
        break;
    }

    case 4:
    {
        printf("PLEASE ENTER THE YEAR OF THE ARTICALS YOU WISH TO SHOW\n");
        //scanf("%i",&r);
        r=read_number();
        r=r-1900;
        int i=0;
        while(parc!=NULL)
        {
            if (r==parc->art.date_et_heure.tm_year)
            {
                s=1;
                printf("The article n° %i : \n",i+1);
                printf("The title : %s \n",parc->art.titre);
                printf("The category : %s \n",parc->art.categorie);
                printf("The text : %s \n",parc->art.texte);
                printf("written by: %s %s \n",parc->art.auteur.prenom,parc->art.auteur.nom);
                printf("written in: %i/%i/%i at %i:%i:%i",(parc->art.date_et_heure.tm_year)+1900,parc->art.date_et_heure.tm_mon,parc->art.date_et_heure.tm_mday,parc->art.date_et_heure.tm_hour,parc->art.date_et_heure.tm_min,parc->art.date_et_heure.tm_sec);
                printf("\n");
                printf("---------------------------------------------------\n");
                i++;
            }
            parc=parc->suiv;
        }
        if (s==0)
        {
            couleur(1);
            printf("NO ARTICALS WERE WRITTEN ON THIS YEAR ");
            couleur(0);
            printf("\n");
        }
        break;
    }
    }
}





