/****************************************************/
/** CRÉATION & INITIALISATION DES DIFFÉRENTS SITES **/
/****************************************************/

#ifndef INTERFACE_SITE
#define INTERFACE_SITE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "style.h"
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/sem.h>
#include <pthread.h>
#include <errno.h>
#include "table_printer.h"
#include "interfaceIPC.h"

using bprinter::TablePrinter;
using namespace std;

#define nSites 4 // Nombre de site
#define tailleSem nSites*2 // Taille de l'ensemble de sémaphore
#define nbMaxClient 100 // Nombre max de client sur un site

struct client{
    unsigned int id;
    struct exclusif{
        unsigned int CPU;
        unsigned int stockage;
    }exclusif;
    struct partage{
        unsigned int CPU;
        unsigned int stockage;
    }partage;
};

// Structure de données descriptive de l'état du système de réservation d'un site donné
struct etat_sys{
    char nom[50];
    unsigned int nbClient;
    struct etat_init{
        unsigned int CPU;
        unsigned int stockage;
    }etat_init;
    struct etat_courant{
        struct libre{
            unsigned int CPU;
            unsigned int stockage;
        }libre;
        struct exclusif{
            unsigned int CPU;
            unsigned int stockage;
        }exclusif;
        struct partage{
            unsigned int CPU;
            unsigned int stockage;
        }partage;
    }etat_courant;
    struct client client[nbMaxClient];
};

// En cas d'arrêt impromptu du client, il quitte proprement (rend les ressources et se détache...)
struct sigHandlerC{
    struct etat_sys *s;
    char *notif;
    int semid;
    int sem2id;
    pthread_t idThread;
    pthread_mutex_t *verrou;
};

// En cas d'arrêt impromptu du serveur, il quitte proprement (détruit les objets IPC)
struct sigHandlerS{
    struct etat_sys *s;
    int idShm1;
    char *notif;
    int idShm2;
    int semid;
    int sem2id;
    pthread_t idThread;
    pthread_mutex_t *verrou;
};

void initialisationSites(struct etat_sys *s, unsigned int nbSites);
void copySite(const struct etat_sys *s1, struct etat_sys *s2, unsigned int nbSites, unsigned int index);
void copyInfosClient(const struct client *c1, struct client *c2);
void ajoutInfosClient(const struct client *c1, struct client *c2);
void printSys(const struct etat_sys *s);
void printSysAll(const struct etat_sys *s, unsigned int nbSites);
void saisieRessourceAll(struct client *c, const struct etat_sys* s, int sem2id, int nbSite);
void rendreRessourceAll(const struct etat_sys* s, struct client *c, int sem2id,  int nbSite);
const char* getSiteById(unsigned int id);
unsigned int possedeRessourceDansSite(const struct client *c, const char mode[]);
void initialiserClient(struct client *c, unsigned int nbSite);
void printInfosClient(const struct client *c, unsigned int nbSite);
void printClientSiteAll(const struct etat_sys *s);
void printInfosSite(const struct etat_sys* s);
unsigned int getNbOp(struct client *c, unsigned int nbSite);
void initialisationOpRessourceP(struct client *c, struct etat_sys *s, struct sembuf *tabSemBufP, int idTabSem, int sem2id, unsigned int *nbOp);
void initialisationOpRessourceV(struct client *c, struct etat_sys *s, struct sembuf *tabSemBufP, int idTabSem, int sem2id, unsigned int *nbOp);
int donneIdSiteAssocie(unsigned int idDuSemaphore);
unsigned int clientExisteDansSite(unsigned int idClient, const struct etat_sys *s);
void abonneClient(const struct client *c, struct etat_sys *s, int nbSites);
void modificationSite(const struct client *c, struct etat_sys *s, char *notif, int sem2id, int nbSites);
unsigned int pgvCpuPartage(const struct etat_sys *s, unsigned int nbSite);
unsigned int pgvCpuPartageInclus(const struct etat_sys *s, unsigned int nbSite);
unsigned int pgvStockagePartage(const struct etat_sys *s, unsigned int nbSite);
unsigned int pgvStockagePartageInclus(const struct etat_sys *s, unsigned int nbSite);
void* getNotification(void *param);
void clientRendRessourceSurSite(const struct client *c, struct etat_sys *s, char *notif, int sem2id, int nbSite);
void suppressionClientSite(struct etat_sys *s, char *notif, int semid,  int sem2id, int nbSite);
int menuNavigation(struct etat_sys* ptr, char* ptr2, int semid, int sem2id, pthread_t idThread, pthread_mutex_t *verrouAffichage);
int sighandlerClient(const int signal, void *ptr);
int sighandlerServeur(const int signal, void *ptr);

#endif