#include "interfaceIPC.h"

/********************/
/** GÉNÉRATION CLÉ **/
/********************/
key_t creationCle(const char s[], char c){

    key_t cle = ftok(s, c);

    if(cle == -1){
        cerr << "erreur ftok" << endl;
        exit(1);
    }

    //hide cout << "ftok ok" << endl;

    return cle;
}

/********************************/
/** SEGMENT DE MÉMOIRE PARTAGÉ **/
/********************************/
int creationSegmentSys(const key_t *cle, unsigned int tailleSegment){
    int shmid = shmget(*cle, sizeof(struct etat_sys)*tailleSegment, IPC_CREAT|IPC_EXCL|0666);

    if(shmid == -1){
        cerr << "erreur shmget" << endl;
        exit(1);
    }

    cout << "create shm ok [id : " << shmid << "]" << endl;

    return shmid;
}

int creationSegmentNotif(const key_t *cle){
    int shmid = shmget(*cle, sizeof(char[1000]), IPC_CREAT|IPC_EXCL|0666);

    if(shmid == -1){
        
        cerr << "erreur shmget" << endl;
        exit(1);
    }

    cout << "create shm ok [id : " << shmid << "]" << endl;

    return shmid;
}

int getSegmentSysId(const key_t *cle, unsigned int tailleSegment){
    int shmid = shmget(*cle, sizeof(struct etat_sys)*tailleSegment, 0666);

    if(shmid == -1){
        if(errno == ENOENT){
            cerr << "Le serveur doit être lancé avant le client" << endl;
        }
        else{
            cerr << "erreur shmget" << endl;
        }
        exit(1);
    }

    //hide cout << "get id shm ok [id : " << shmid << "]" << endl;

    return shmid;
}

int getSegmentNotifId(const key_t *cle){
    int shmid = shmget(*cle, sizeof(char[1000]), 0666);

    if(shmid == -1){
        if(errno == ENOENT){
            cerr << "Le serveur doit être lancé avant le client" << endl;
        }
        else{
            cerr << "erreur shmget" << endl;
        }
        exit(1);
    }

    //hide cout << "get id shm ok [id : " << shmid << "]" << endl;

    return shmid;
}

struct etat_sys* segmentSysAt(int idSegment){
    void* adr = NULL;

    if((adr = shmat(idSegment, NULL, 0666)) == (int*)-1){
        cerr << "erreur shmat" << endl;
        exit(1);
    }

    //hide cout << "shmat (sys) ok" << endl;

    return (struct etat_sys*)adr;
}

char* segmentNotifAt(int idSegment){
    void* adr = NULL;

    if((adr = shmat(idSegment, NULL, 0666)) == (int*)-1){
        cerr << "erreur shmat" << endl;
        exit(1);
    }

    //hide cout << "shmat (notif) ok" << endl;

    return (char*)adr;
}

void segmentDt(const void* adrAt){
    if(shmdt(adrAt) == -1){
        cerr << "erreur shmdt" << endl;
        exit(1);
    }

    //hide cout << "shdt ok" << endl;
}

void destructionSegment(int idSegment){
    if(shmctl(idSegment, IPC_RMID, NULL) == -1){
        cerr << "erreur shmtcl" << endl;
        exit(1);
    }

    cout << "suppr shm ok [id : " << idSegment << "]" << endl;
}

/**************************/
/** TABLEAU DE SÉMAPHORE **/
/**************************/
int creationTabSem(const key_t *cle, unsigned int tailleTab){
    int semid = semget(*cle, tailleTab, IPC_CREAT|IPC_EXCL|0666);

    if(semid == -1){
        cerr << "erreur semget" << endl;
        exit(1);
    }

    cout << "create sem ok [id : " << semid << "]" << endl;

    return semid;
}

int getTabSemId(const key_t *cle, unsigned int tailleTab){
    int semid = semget(*cle, tailleTab, 0666);

    if(semid == -1){
        cerr << "erreur semget" << endl;
        exit(1);
    }

    //hide cout << "get id sem ok [id : " << semid << "]" << endl;

    return semid;
}

// Affiche les valeurs d'un ensemble de sémaphore
void printValSem(int idTabSem, unsigned int nbElementSem){
    for(unsigned int i=0; i<nbElementSem; i++){
        cout << "sem[" << i << "] = " << semctl(idTabSem, i, GETVAL) << endl;
    }
}

// On initialise les val de sémaphores avec le nb de ressources qui leurs sont respectivement attribuées
void initialiserTabSem(int idTabSem, unsigned int tailleTab, const struct etat_sys* shm){

    union semun sem;
        
    for(unsigned int i=0; i<tailleTab/2; i++){ // CPU

        sem.val = shm[i].etat_courant.libre.CPU;
        
        if(semctl(idTabSem, i, SETVAL, sem) == -1){
            cout << "semctl erreur" << endl;
            exit(1);
        }

        cout << "sem[" << i << "] = " << semctl(idTabSem, i, GETVAL) << " (CPU)" << endl;
        
    }

    unsigned int j=0;

    for(unsigned int i=4; i<tailleTab; i++){ // Stockage

        sem.val = shm[j].etat_courant.libre.stockage;
        
        if(semctl(idTabSem, i, SETVAL, sem) == -1){
            cout << "semctl erreur" << endl;
            exit(1);
        }

        j++;

        cout << "sem[" << i << "] = " << semctl(idTabSem, i, GETVAL) << " (Stockage)" << endl;

    }

}

// On initialise la valeur du semaphore qui joue le rôle de verrou sur le shm
void initialiserSem(int idSem, unsigned int taille){

    union semun sem;
    sem.val = 1;

    for(unsigned int i=0; i<taille; i++){

        if(semctl(idSem, i, SETVAL, sem) == -1){
            cout << "semctl erreur" << endl;
            exit(1);
        }

        cout << "sem = " << semctl(idSem, i, GETVAL) << " (verrou shm) [id : " << idSem << "]" << endl;
    }

}

// Lock sur le segment
void sem_lock(int idSem, int num){

    struct sembuf sem;
    sem.sem_num = num;
    sem.sem_op = -1;
    sem.sem_flg = SEM_UNDO;

    if(semop(idSem, &sem, 1) == -1){
        cerr << "erreur semop" << endl;
        exit(1);
    }

    //hide cout << "semop : ok (lock shm)" << endl;
}

// Unlock sur le segment
void sem_unlock(int idSem, int num){

    struct sembuf sem;
    sem.sem_num = num;
    sem.sem_op = +1;
    sem.sem_flg = SEM_UNDO;

    if(semop(idSem, &sem, 1) == -1){
        cerr << "erreur semop" << endl;
        exit(1);
    }

    //hide cout << "semop : ok (unlock shm)" << endl;
}

// Affecter une valeur à un sémaphore
void setValSem(int idSem, int numSem, unsigned int val){

    if(semctl(idSem, numSem, SETVAL, val) == -1){
        cerr << "erreur semctl (setval)" << endl;
        exit(1);
    }

    //hide cout << "semctl (setval) ok" << endl;
}

// Obtention des ressources + modification du segment
// Blocage du processus s'il n'obtient pas TOUTES les ressources en une seule fois
// Ca peut aussi etre une opération V (et donc non bloquante)
void demandeRessource(struct sembuf *tabSemBuf, int idTabSem, unsigned int nbOp){

    if(nbOp != 0 && semop(idTabSem, tabSemBuf, nbOp) == -1){

        if(errno == EIDRM){
            cerr << endl << endl << ANSI_COLOR_GREEN_H << "Le serveur vient de se déconnecter, cela entraine une déconnexion du client." << ANSI_RESET << endl;
        }
        else{
            cerr << "erreur semop : demande de ressource" << endl;
        }
        exit(1);
    }

    //hide cout << "semop : demande ressource effectuée" << endl;
}

void destructionTabSem(int idTabSem){
    
    if(semctl(idTabSem, 0, IPC_RMID) == -1){
        cerr << "erreur shmtcl" << endl;
        exit(1);
    }

    cout << "suppr sem ok [id : " << idTabSem << "]" << endl;
}

/*****************************/
/** CRÉATION THREAD & MUTEX **/
/*****************************/

// Création du thread
void creationThread(pthread_t *idThread, int sem2id, char *notif, pthread_mutex_t* mutex, void* param){
    struct paramNotif *p = (struct paramNotif*)param;
    p->adrShmNotif = notif;
    p->idSem = sem2id;
    p->mutex = mutex;

    if(pthread_create(idThread, NULL, getNotification, p)){
        cerr << "erreur pthread_create" << endl;
        exit(1);
    }

   //hide cout << "pthread_create : ok" << endl;
}

// Initialisation mutex
void mutex_init(pthread_mutex_t *mutex){
    if(pthread_mutex_init(mutex, NULL) != 0){
       cerr << "erreur pthread_mutex_init" << endl;
        exit(1);
    }

    //hide cout << "pthread_mutex_init ok" << endl;
}

// Mutex lock
void mutex_lock(pthread_mutex_t *mutex){
    if(pthread_mutex_lock(mutex) != 0){
       //hide cerr << "erreur pthread_mutex_lock" << endl;
        exit(1);
    }

    //hide cout << "pthread_mutex_lock ok" << endl;
}

// Mutex unlock
void mutex_unlock(pthread_mutex_t *mutex){
    if(pthread_mutex_unlock(mutex) != 0){
       //hide cerr << "erreur pthread_mutex_unlock" << endl;
        exit(1);
    }

    //hide cout << "pthread_mutex_unlock ok" << endl;
}

// Mutex destroy
void mutex_destroy(pthread_mutex_t *mutex){
    if(pthread_mutex_destroy(mutex) != 0){
       //hide cerr << "erreur pthread_mutex_destroy" << endl;
        exit(1);
    }

    //hide cout << "pthread_mutex_destroy ok" << endl;
}