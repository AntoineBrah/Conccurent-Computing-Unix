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


#define nSites 4 // Nombre de site


int main(int argc, char* argv[]){

    clearScreen();
    cout << "► Client n°" << ANSI_COLOR_GREEN << ANSI_BLINK << getpid() << ANSI_RESET << " connecté" << endl;

    // Création clé
    key_t cle1 = creationCle("fichier.txt", 'x');
    key_t cle2 = creationCle("fichier.txt", 'y');

    // Obtention id segment
    int shmid = getSegmentSysId(&cle1, nSites);
    int shm2id = getSegmentNotifId(&cle2);

    // Attachement au segment
    struct etat_sys* ptr = segmentSysAt(shmid);
    char* ptr2 = segmentNotifAt(shm2id);


    // Obtention id tableau de sémaphore
    int semid = getTabSemId(&cle1, tailleSem);  // Tab Sem 
    int sem2id = getTabSemId(&cle2, 3); // Verrou

    // On affiche l'état du système
    printInfosSite(ptr);
    printClientSiteAll(ptr);


    // Création thread pour mise en écoute du shm
    pthread_t idThread;
    struct paramNotif p;

    // Verrou pour empêcher l'affichage saccadé
    pthread_mutex_t verrouAffichage; 
    mutex_init(&verrouAffichage);
    creationThread(&idThread, sem2id, ptr2, &verrouAffichage, &p);
    
    // Gestion de la déconnexion impromptue
    struct sigHandlerC sigH;
    sigH.s = ptr;
    sigH.notif = ptr2;
    sigH.semid = semid;
    sigH.sem2id = sem2id;
    sigH.idThread = idThread;
    sigH.verrou = &verrouAffichage;

    // Fonction appelé en cas d'interruption
    signal(SIGINT, (void (*)(int))sighandlerClient);
    sighandlerClient(3, &sigH);


    // On boucle sur le menu de navigation
    while(menuNavigation(ptr, ptr2, semid, sem2id, idThread, &verrouAffichage));

    return 0;
}