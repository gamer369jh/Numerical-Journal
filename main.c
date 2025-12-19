#include <stdio.h>
#include <stdlib.h>
#include "article test.h"
#include <string.h>
#include <windows.h>



int main()
{
   int n,id,i;
   FILE *fichier;
   noeud *parc,*m;
   liste *l=NULL;
   char s[20000],pass[9],ch[9];
   couleur(0);
   printf("WELCOME TO OUR DIGITAL JOURNAL \n");
   printf("TO START WE WOULD LIKE TO KNOW IF YOU ALREADY HAVE A SAVED JOURNAL \n");
   printf("(1)  YES OPEN IT \n");
   printf("(0)  NO CREATE A NEW ONE \n");
   int c;
   while (1)
   {
        //scanf("%i",&c);
        c=read_number();
        Beep(600,300);
        if((c != 0)&&(c != 1))
        {
            couleur(1);
            printf("PLEASE ENTER 0 OR 1\n");
            couleur(0);
            printf("\n");
        }
        else
        {
            break;
        }
   }
   system("cls");
   if(c==1)
   {
       do{
        printf("WHAT IS YOUR JOURNAL'S NAME(add .txt at the end please) \n");
        scanf("%s",s);
        fichier=fopen(s,"rt");
        if(fichier==NULL)
           {
               couleur(1);
               printf("THIS FILE DOES NOT EXISIT");
               couleur(0);
               printf("\n");
               printf("WOULD YOU LIKE TO UPDATE ANOTHER ARTICAL \n");
                printf("*************** (1) ENTER A NEW JOURNAL'S NAME ****************\n ");
                printf("*****************  (0) CREATE A NEW JOURNAL *******************\n");
                m=read_number();
                Beep(600,300);
                while((m<0)||(m>1))
                {
                    couleur(1);
                    printf("!!!!!!!!!!!  PLEASE ENTER 1 OR 0  !!!!!!!!!!!!!!");
                    couleur(0);
                    m=read_number();
                    Beep(600,300);
                }
           }
            if(m==0)
           {
               c=0;
               break;
           }
           else
            system("cls");

       }while(fichier==NULL);
       int tries=0 ,a=0;
       while((tries<3)&&(a==0)&&(fichier!=NULL))
       {
           printf("WHAT'S THE 8 CHARACTER PASSWORD TO ACCESS THIS JOURNAL\n");
           for(i=0;i<8;i++)
           {
              ch[i]=getch();
              printf("*");
           }
           printf("\n");
           n=4000;
           l=(liste*)malloc(sizeof(noeud));
           liste_vide(l);
           fichier=fopen(s,"rt");
           fgets(pass,9,fichier);
           if(strcmp(ch,pass)==0)
           {
               a=1;
               article art;
               while (!feof(fichier))
               {
                   parc=(noeud*)malloc(sizeof(noeud));
                   fscanf(fichier,"%i %i/%i/%i %i:%i:%i %s %s %s %s %s\n",&art.id,&art.date_et_heure.tm_mday,&art.date_et_heure.tm_mon,&art.date_et_heure.tm_year,&art.date_et_heure.tm_hour,&art.date_et_heure.tm_min,&art.date_et_heure.tm_sec,art.titre,art.auteur.prenom,art.auteur.nom,art.categorie,art.texte);
                   art.date_et_heure.tm_mon= art.date_et_heure.tm_mon-1;
                   art.date_et_heure.tm_year=art.date_et_heure.tm_year-1900;
                   inserer_fin(art,l);
               }
               n=nbrelem_liste(l);
               fclose(fichier);
               parc = l->tete;
               while(parc != NULL)
               {
                    strcpy(parc->art.categorie,espace(parc->art.categorie));
                    strcpy(parc->art.auteur.nom,espace(parc->art.auteur.nom));
                    strcpy(parc->art.auteur.prenom,espace(parc->art.auteur.prenom));
                    strcpy(parc->art.titre,espace(parc->art.titre));
                    strcpy(parc->art.texte,espace(parc->art.texte));
                    parc=parc->suiv;
               }
           }
           else
           {
               tries=tries+1;
               couleur(1);
               printf("WRONG PASSWORD TRY AGAIN");
               couleur(0);
               printf("\n");

           }
       }
       if(tries>=3)
       {
           system("cls");
           couleur(1);
           printf("!!!!!!!!!!!!!!!!!!!!!!!  ACCESS DENIED !!!!!!!!!!!!!!!!!!!!!!!!\n");
           return(0);
       }
       system("cls");

    }
   if(c==0)
   {
    printf("WHAT DO YOU INTEND TO NAME YOUR JOURNAL(add .txt at the end please) \n");
    scanf("%s",s);
    printf("PLEASE ENTER THE NUMBER OF THE ARTICALS \n");
    //scanf("%i",&n);
     do
    {
        n=read_number();
        if(n<0)
        {
            couleur(1);
            printf("YOU MUST ENTER A POSITIVE NUMBER");
            couleur(0);
            printf("\n");
        }
    }while(n<0);
    article x;
    if(n!=0)
    {

        noeud*m;
        m=(noeud*)malloc(sizeof(noeud));
        l=(liste*)malloc(sizeof(noeud));
        liste_vide(l);
        l->tete=m;
        system("cls");
        couleur(2);
        printf("ENTER THE ARTICAL N° 1\n");
        printf("PLEASE GIVE THE ID OF THE ARTICAL\n ");
        couleur(0);
        printf("\n");
        //scanf("%i",&id);
        id=read_number();
        x=saisir_article(id);
        m->art.id=x.id;
        m->art.date_et_heure.tm_hour=x.date_et_heure.tm_hour;
        m->art.date_et_heure.tm_min=x.date_et_heure.tm_min;
        m->art.date_et_heure.tm_sec=x.date_et_heure.tm_sec;
        m->art.date_et_heure.tm_mday=x.date_et_heure.tm_mday;
        m->art.date_et_heure.tm_mon=x.date_et_heure.tm_mon;
        m->art.date_et_heure.tm_year=x.date_et_heure.tm_year;
        strcpy(m->art.categorie,x.categorie);
        strcpy(m->art.titre,x.titre);
        strcpy(m->art.texte,x.texte);
        strcpy(m->art.auteur.nom,x.auteur.nom);
        strcpy(m->art.auteur.prenom,x.auteur.prenom);
    }
    for(i=1;i<n;i++)
    {
        couleur(2);
        printf("ENTER THE ARTICAL n° %i : ",i+1);
        couleur(0);
        printf("\n");
        id= verifier_id(l);
        x=saisir_article(id);
        inserer_fin(x,l);

    }
    system("cls");
   }
   Beep(500,500);
   Beep(700,500);
   Beep(900,500);
    int choice=7;
    printf("%i",n);
    while(choice!=0)
    {
        printf("******************************* # MENU # **********************************\n");
        printf("************************* (1) UPDATE AN ARTICAL ***************************\n");
        printf("**************************(2) DISPLAY AN ARTICAL **************************\n");
        printf("************************* (3) DELETE AN ARTICAL ***************************\n");
        printf("************************* (4) SEARCH FOR AN ARTICAL ***********************\n");
        printf("************************* (5) ADD AN ARTICAL ******************************\n");
        printf("************************* (6) SORT THE ARTICALS BY DATE *******************\n");
        printf("************************* (0) SAVE AND EXIT *******************************\n");
        //scanf("%i",&choice);
        choice=read_number();
        Beep(600,300);
        while((choice<0)&&(choice>6))
        {
            couleur(1);
            printf("PLEASE CHOOSE 0 OR 1 OR 2 OR 3 OR 4 OR 5 OR 6 ");
            couleur(0);
            printf("\n");
            //scanf("%i",&choice);
            choice=read_number();
            Beep(600,300);
        }
        system("cls");
        switch(choice)
        {
        case 1:
            {
                if(n!=0)
                {
                    int m;
                    do
                    {
                        miseajour_article(l);
                        printf("WOULD YOU LIKE TO UPDATE ANOTHER ARTICAL \n");
                        printf("*****************  (1) UPDATE ANOTHER ARTICAL  ******************\n ");
                        printf("*****************  (0) BACK TO THE MAIN MENU  *******************\n");
                        //scanf("%i",&m);
                        m=read_number();
                        Beep(600,300);
                        while((m<0)||(m>1))
                        {
                            couleur(1);
                            printf("!!!!!!!!!!!  PLEASE ENTER 1 OR 0  !!!!!!!!!!!!!!");
                            couleur(0);
                            //scanf("%i",&m);
                            m=read_number();
                            Beep(600,300);
                        }
                        system("cls");

                    }while(m==1);
                }
                else
                {
                    couleur(1);
                    printf("YOU HAVE NO ARTICL IN THIS FILE");
                    couleur(0);
                    delay(500);
                    system("cls");
                }
                break;
            }
        case 2:
            {
                if(n!=0)
                {
                    int m;
                    do
                    {
                        afficher_article(l);
                        printf("WOULD YOU LIKE TO DISPLAY ANOTHER ARTICAL \n");
                        printf("*****************  (1) DISPLAY ANOTHER ARTICAL  *****************\n ");
                        printf("*****************  (0) BACK TO THE MAIN MENU  *******************\n");
                        //scanf("%i",&m);
                        m=read_number();
                        Beep(600,300);
                        while((m<0)||(m>1))
                        {
                            couleur(1);
                            printf("!!!!!!!!!!!  PLEASE ENTER 1 OR 0  !!!!!!!!!!!!!!");
                            couleur(0);
                            printf("\n");
                            //scanf("%i",&m);
                            m=read_number();
                            Beep(600,300);
                        }
                        system("cls");

                    }while(m==1);
                }
                else
                {
                    couleur(1);
                    printf("YOU HAVE NO ARTICL IN THIS FILE");
                    couleur(0);
                    delay(500);
                    system("cls");
                }
                break;
            }
        case 3:
            {
                if(n!=0)
                {
                    int m=1;
                    while((m==1)&&(n!=0))
                    {
                        n=supprimer_article(l,n);
                        printf("WOULD YOU LIKE TO DELETE ANOTHER ARTICAL \n");
                        printf("*****************  (1) DELETE ANOTHER ARTICAL  ******************\n ");
                        printf("*****************  (0) BACK TO THE MAIN MENU  *******************\n");
                        //scanf("%i",&m);
                        m=read_number();
                        Beep(600,300);
                        while((m<0)||(m>1))
                        {
                            couleur(1);
                            printf("!!!!!!!!!!!  PLEASE ENTER 1 OR 0  !!!!!!!!!!!!!!");
                            couleur(0);
                            printf("\n");
                            //scanf("%i",&m);
                            m=read_number();
                            Beep(600,300);
                        }
                        system("cls");

                    }
                }
                else
                {
                    couleur(1);
                    printf("YOU HAVE NO ARTICL IN THIS FILE");
                    couleur(0);
                    delay(500);
                    system("cls");
                }

                break;
            }
        case 4:
            {
                if(n!=0)
                {
                    int m;
                    do{
                        printf("PLEASE ENTER THE ID OF THE ARTICAL YOU ARE LOOKING FOR \n");
                        //scanf("%i",&id);
                        id=read_number();
                        noeud *d=rechecher_article(l,id);
                        if(d==NULL)
                        {
                            couleur(1);
                            printf("ARTICAL NOT FOUND PLEASE VERIFY THE ID");
                            couleur(0);
                            printf("\n");
                        }
                        else
                        {
                            printf("ARTICAL IS FOUND\n");
                        }
                        printf("WOULD YOU LIKE TO SEARCH FOR ANOTHER ARTICAL \n");
                        printf("****************   (1) SEARCH FOR ANOTHER ARTICAL  **************\n ");
                        printf("*****************  (0) BACK TO THE MAIN MENU  *******************\n");
                        //scanf("%i",&m);
                        m=read_number();
                        Beep(600,300);
                        while((m<0)||(m>1))
                        {
                            couleur(1);
                            printf("!!!!!!!!!!!  PLEASE ENTER 1 OR 0  !!!!!!!!!!!!!!");
                            couleur(0);
                            printf("\n");
                            //scanf("%i",&m);
                            m=read_number();
                            Beep(600,300);
                        }

                        system("cls");
                    }while(m==1);
                }
                else
                {
                    couleur(1);
                    printf("YOU HAVE NO ARTICL IN THIS FILE");
                    couleur(0);
                    delay(500);
                    system("cls");
                }
                break;
            }
        case 5:
            {
                int m;
                do
                {
                    if(n!=0)
                    {
                        article x;
                        id= verifier_id(l);
                        x=saisir_article(id);
                        inserer_fin(x,l);
                        n=n+1;
                    }
                    else
                    {
                        article x;
                        noeud*m;
                        m=(noeud*)malloc(sizeof(noeud));
                        l=(liste*)malloc(sizeof(noeud));
                        liste_vide(l);
                        l->tete=m;
                        system("cls");
                        couleur(2);
                        printf("ENTER THE ARTICAL N° 1\n");
                        printf("PLEASE GIVE THE ID OF THE ARTICAL\n ");
                        couleur(0);
                        printf("\n");
                        //scanf("%i",&id);
                        id=read_number();
                        x=saisir_article(id);
                        m->art.id=x.id;
                        m->art.date_et_heure.tm_hour=x.date_et_heure.tm_hour;
                        m->art.date_et_heure.tm_min=x.date_et_heure.tm_min;
                        m->art.date_et_heure.tm_sec=x.date_et_heure.tm_sec;
                        m->art.date_et_heure.tm_mday=x.date_et_heure.tm_mday;
                        m->art.date_et_heure.tm_mon=x.date_et_heure.tm_mon;
                        m->art.date_et_heure.tm_year=x.date_et_heure.tm_year;
                        strcpy(m->art.categorie,x.categorie);
                        strcpy(m->art.titre,x.titre);
                        strcpy(m->art.texte,x.texte);
                        strcpy(m->art.auteur.nom,x.auteur.nom);
                        strcpy(m->art.auteur.prenom,x.auteur.prenom);
                        n++;
                    }
                    printf("WOULD YOU LIKE TO ADD ANOTHER ARTICAL \n");
                    printf("*****************  (1) ADD ANOTHER ARTICAL  *********************\n ");
                    printf("*****************  (0) BACK TO THE MAIN MENU  *******************\n");
                    //scanf("%i",&m);
                    m=read_number();
                    Beep(600,300);
                    while((m<0)||(m>1))
                    {
                        couleur(1);
                        printf("!!!!!!!!!!!  PLEASE ENTER 1 OR 0  !!!!!!!!!!!!!!");
                        couleur(0);
                        printf("\n");
                        //scanf("%i",&m);
                        m=read_number();
                        Beep(600,300);
                    }
                    system("cls");

                }while(m==1);
                break;

            }
         case 6:
            {
                int m;
                printf("WOULD YOU LIKE TO SORT YOUR ARTICALS \n");
                printf("*****************  (1) FROM THE LATEST TO THE OLDEST  *********************\n ");
                printf("*****************  (0) FROM THE OLDEST TO THE LATEST *******************\n");
                m=read_number();
                Beep(600,300);
                while((m<0)||(m>1))
                {
                    couleur(1);
                    printf("!!!!!!!!!!!  PLEASE ENTER 1 OR 0  !!!!!!!!!!!!!!");
                    couleur(0);
                    printf("\n");
                    m=read_number();
                    Beep(600,300);
                }
                if(m==1)
                    tri_article_up(l);
                else
                    tri_article_down(l);
                delay(2000);
                couleur(2);
                printf("SORTING IS DONE SUCCESSFULLY ");
                couleur(0);
                printf("\n");
                delay(2000);
                system("cls");
                break;
            }
         case 0:
            {
                break;
            }
        }

    }
    if(c==0)
    {

        while(1)
        {
            couleur(2);
            printf("GIVE THE PASSWORD TO YOUR JOURNAL");
            couleur(0);
            printf("\n");
            scanf("%s",pass);
            if(strlen(pass)==8)
                break;
            else
            {
                couleur(1);
                printf("PASSWORD MUST HAVE 8 CHARACTERS ");
                couleur(0);
                printf("\n");
            }
        }
    }
    Beep(900,500);
    Beep(700,500);
    Beep(500,500);
    fichier= fopen(s,"w");
    fprintf(fichier,"%s\n",pass);
    noeud *parc1=l->tete;
    while(parc1!=NULL)
    {
        strcpy(parc1->art.categorie,tiree(parc1->art.categorie));
        strcpy(parc1->art.auteur.nom,tiree(parc1->art.auteur.nom));
        strcpy(parc1->art.auteur.prenom,tiree(parc1->art.auteur.prenom));
        strcpy(parc1->art.titre,tiree(parc1->art.titre));
        strcpy(parc1->art.texte,tiree(parc1->art.texte));
        fprintf(fichier,"%i %i/%i/%i %i:%i:%i %s %s %s %s %s\n",parc1->art.id,parc1->art.date_et_heure.tm_mday,(parc1->art.date_et_heure.tm_mon+1),(parc1->art.date_et_heure.tm_year+1900),parc1->art.date_et_heure.tm_hour,parc1->art.date_et_heure.tm_min,parc1->art.date_et_heure.tm_sec,parc1->art.titre,parc1->art.auteur.prenom,parc1->art.auteur.nom,parc1->art.categorie,parc1->art.texte);
        parc1=parc1->suiv;
    }
    fclose(fichier);
    couleur(2);
    printf("The program works successfully");
    return 0;

}
