#include <stdlib.h>
#include <sys/types.h>
#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/sem.h> 
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include "style.h"
#include "interfaceSite.h"
#include "interfaceIPC.h"

using namespace std;

#define nSites 4 // 1 : Lyon, 2 : Montpellier, 3 : Rennes, 4 : Toulouse

int main(int argc, char* argv[]){

    clearScreen();
    cout << "Serveur id : " << ANSI_COLOR_GREEN << ANSI_BLINK << getpid() << ANSI_RESET << endl;

    // Création clé
    key_t cle1 = creationCle("fichier.txt", 'x');
    key_t cle2 = creationCle("fichier.txt", 'y');

    // Création segment
    int shmid = creationSegmentSys(&cle1, nSites);
    int shm2id = creationSegmentNotif(&cle2);

    // Attachement au segment
    struct etat_sys* ptr = segmentSysAt(shmid);
    char* ptr2 = segmentNotifAt(shm2id);

    // On initialise les sites de réservation
    initialisationSites(ptr, nSites);

    // Création tableau de sémaphore
    int semid = creationTabSem(&cle1, tailleSem); //(0 à 3 : CPU, 4 à 8 : Stockage)
    int sem2id = creationTabSem(&cle2, 3); // Verrou shm client et shm notif, sem point de rdv


    // Initialisation valeur des sémaphores
    initialiserTabSem(semid, tailleSem, ptr); // Valeur sem sur CPU du site
    initialiserSem(sem2id, 3); // Initialisation du sem jouant le rôle de verrou sur le shm site et sur le shm notif

    // Création thread pour mise en écoute du shm
    pthread_t idThread;
    struct paramNotif p;
    
    // Verrou pour empêcher l'affichage saccadé
    pthread_mutex_t verrouAffichage; 
    mutex_init(&verrouAffichage);
    creationThread(&idThread, sem2id, ptr2, &verrouAffichage, &p);

    // Gestion de la déconnexion impromptue du serveur
    struct sigHandlerS sigH;
    sigH.s = ptr;
    sigH.notif = ptr2;
    sigH.idShm1 = shmid;
    sigH.idShm2 = shm2id;
    sigH.semid = semid;
    sigH.sem2id= sem2id;
    sigH.idThread = idThread;
    sigH.verrou = &verrouAffichage;

    // Fonction appelé en cas d'interruption
    signal(SIGINT, (void (*)(int))sighandlerServeur);
    sighandlerServeur(3, &sigH);

    int x = 0;

    do{
        printInfosSite(ptr);
        printClientSiteAll(ptr);

        cout << "1. Actualiser les infos du système" << endl;
        cout << "0. Quitter le serveur" << endl;
        cout << ">";

        cin >> x;

    }while(x);

    // Détachement du segment
    segmentDt(ptr);
    segmentDt(ptr2);

    // Suppression segment
    destructionSegment(shmid);
    destructionSegment(shm2id);

    // On tue le thread d'affichage
    pthread_cancel(idThread);

    // Suppresion tabSem
    destructionTabSem(semid);
    destructionTabSem(sem2id);

    // Destruction du mutex
    mutex_destroy(&verrouAffichage);

    cout << "fin serveur" << endl;
    
    return 0;
}