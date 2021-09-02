/********************************************************/
/** CRÉATION ET MANIPULATION DES DIFFÉRENTS OBJETS IPC **/
/********************************************************/

#ifndef INTERFACE_IPC
#define INTERFACE_IPC

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/sem.h> 
#include <errno.h>
#include "interfaceSite.h"
#include "style.h"

using namespace std;

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct semingo *__buf;
};

struct paramNotif{
    char* adrShmNotif;
    int idSem; 
    pthread_mutex_t* mutex;
};

key_t creationCle(const char *s, char c);
int creationSegmentSys(const key_t *cle, unsigned int tailleSegment);
int creationSegmentNotif(const key_t *cle);
int getSegmentSysId(const key_t *cle, unsigned int tailleSegment);
int getSegmentNotifId(const key_t *cle);
struct etat_sys* segmentSysAt(int idSegment);
char* segmentNotifAt(int idSegment);
void segmentDt(const void* adrAt);
void destructionSegment(int idSegment);
int creationTabSem(const key_t *cle, unsigned int tailleTab);
int getTabSemId(const key_t *cle, unsigned int tailleTab);
void printValSem(int idTabSem, unsigned int nbElementSem);
void initialiserTabSem(int idTabSem, unsigned int tailleTab, const struct etat_sys* shm);
void initialiserSem(int idSem, unsigned int taille);
void sem_lock(int idSem, int num);
void sem_unlock(int idSem, int num);
void setValSem(int idSem, int numSem, unsigned int val);
void demandeRessource(struct sembuf *tabSemBuf, int idTabSem, unsigned int nbOp);
void creationThread(pthread_t *idThread, int sem2id, char *notif, pthread_mutex_t* mutex, void* param);
void mutex_init(pthread_mutex_t *mutex);
void mutex_lock(pthread_mutex_t *mutex);
void mutex_unlock(pthread_mutex_t *mutex);
void mutex_destroy(pthread_mutex_t *mutex);
void destructionTabSem(int idTabSem);

#endif