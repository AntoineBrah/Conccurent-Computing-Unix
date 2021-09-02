#include "interfaceSite.h"

// [0] Lyon : 64 CPU & 2000 Go 
// [1] Montpellier : 92 CPU & 700 Go 
// [2] Rennes : 25 CPU & 400 Go 
// [3] Toulouse : 120 CPU & 3500 Go 

void initialisationSites(struct etat_sys *s, unsigned int nbSites){

    for(unsigned int i=0; i<nbSites; i++){

        switch(i){
            case 0:
                sprintf(s[i].nom, "Lyon");
                s[i].nbClient = 0;
                s[i].etat_init.CPU = 64;
                s[i].etat_init.stockage = 2000;
                s[i].etat_courant.libre.CPU = 64;
                s[i].etat_courant.libre.stockage = 2000;
                s[i].etat_courant.exclusif.CPU = 0;
                s[i].etat_courant.exclusif.stockage = 0;
                s[i].etat_courant.partage.CPU = 0;
                s[i].etat_courant.partage.stockage = 0;
                for(int j=0; j<nbMaxClient; j++){
                    initialiserClient(&s[i].client[j], nSites);
                }
                break;
            case 1:
                sprintf(s[i].nom, "Montpellier");
                s[i].nbClient = 0;
                s[i].etat_init.CPU = 92;
                s[i].etat_init.stockage = 700;
                s[i].etat_courant.libre.CPU = 92;
                s[i].etat_courant.libre.stockage = 700;
                s[i].etat_courant.exclusif.CPU = 0;
                s[i].etat_courant.exclusif.stockage = 0;
                s[i].etat_courant.partage.CPU = 0;
                s[i].etat_courant.partage.stockage = 0;
                for(int j=0; j<nbMaxClient; j++){
                    initialiserClient(&s[i].client[j], nSites);
                }
                break;
            case 2:
                sprintf(s[i].nom, "Rennes");
                s[i].nbClient = 0;
                s[i].etat_init.CPU = 25;
                s[i].etat_init.stockage = 400;
                s[i].etat_courant.libre.CPU = 25;
                s[i].etat_courant.libre.stockage = 400;
                s[i].etat_courant.exclusif.CPU = 0;
                s[i].etat_courant.exclusif.stockage = 0;
                s[i].etat_courant.partage.CPU = 0;
                s[i].etat_courant.partage.stockage = 0;
                for(int j=0; j<nbMaxClient; j++){
                    initialiserClient(&s[i].client[j], nSites);
                }
                break;
            case 3:
                sprintf(s[i].nom, "Toulouse");
                s[i].nbClient = 0;
                s[i].etat_init.CPU = 120;
                s[i].etat_init.stockage = 3500;
                s[i].etat_courant.libre.CPU = 120;
                s[i].etat_courant.libre.stockage = 3500;
                s[i].etat_courant.exclusif.CPU = 0;
                s[i].etat_courant.exclusif.stockage = 0;
                s[i].etat_courant.partage.CPU = 0;
                s[i].etat_courant.partage.stockage = 0;
                for(int j=0; j<nbMaxClient; j++){
                    initialiserClient(&s[i].client[j], nSites);
                }
                break;
            default:
                printf("Erreur, le nombre de site est trop grand\n");
                break;
        }
    }
}

/************************************************/
/** COPIE EN PROFONDEUR DE SITES ET DE CLIENTS **/
/************************************************/

// On copie la structure de s1 (source) dans la structure de s2 (destination);
void copySite(const struct etat_sys *s1, struct etat_sys *s2, unsigned int nbSites, unsigned int index){
    strcpy(s2[index].nom, s1[index].nom);
    s2[index].nbClient = s1[index].nbClient;
    s2[index].etat_init.CPU = s1[index].etat_init.CPU;
    s2[index].etat_init.stockage = s1[index].etat_init.stockage;
    s2[index].etat_courant.libre.CPU = s1[index].etat_courant.libre.CPU;
    s2[index].etat_courant.libre.stockage = s1[index].etat_courant.libre.stockage;
    s2[index].etat_courant.exclusif.CPU = s1[index].etat_courant.exclusif.CPU;
    s2[index].etat_courant.exclusif.stockage = s1[index].etat_courant.exclusif.stockage;
    s2[index].etat_courant.partage.CPU = s1[index].etat_courant.partage.CPU;
    s2[index].etat_courant.partage.stockage = s1[index].etat_courant.partage.stockage;
}

void copyInfosClient(const struct client *c1, struct client *c2){
    c2->id = c1->id;
    c2->exclusif.CPU = c1->exclusif.CPU;
    c2->exclusif.stockage = c1->exclusif.stockage;
    c2->partage.CPU = c1->partage.CPU;
    c2->partage.stockage = c1->partage.stockage; 
}

void ajoutInfosClient(const struct client *c1, struct client *c2){

    c2->id = c1->id;

    if(possedeRessourceDansSite(c1, "exclusif")){
        c2->exclusif.CPU += c1->exclusif.CPU;
        c2->exclusif.stockage += c1->exclusif.stockage;
    }
    else if(possedeRessourceDansSite(c1, "partage")){
        if(c1->partage.CPU > c2->partage.CPU){
            c2->partage.CPU = c1->partage.CPU;
        }
        if(c1->partage.stockage > c2->partage.stockage){
            c2->partage.stockage = c1->partage.stockage;
        }
    }

}

/******************************************************/
/** AFFICHAGE DE L'ÉTAT DU SYSTEME D'UN OU DES SITES **/
/******************************************************/

void printSys(const struct etat_sys *s){
    cout << "######################################" << endl;
    cout << "# ► " << ANSI_BOLD <<"Site : " << ANSI_RESET << ANSI_COLOR_GREEN << s->nom << ANSI_RESET << endl;
    cout << "# ► " << ANSI_BOLD << "État actuel système" << ANSI_RESET << " : " << endl;
    cout << "#   - CPU : " << ANSI_COLOR_GREEN << s->etat_courant.libre.CPU << ANSI_RESET << endl;
    cout << "#   - Stockage : " << ANSI_COLOR_GREEN << s->etat_courant.libre.stockage << ANSI_RESET << endl;
    cout << "######################################" << endl;
}

void printSysAll(const struct etat_sys *s, unsigned int nbSites){
    cout << endl;
    for(int i=0; i<nbSites; i++){
        cout << "######################################" << endl;
        cout << "# ► " << ANSI_BOLD <<"Site : " << ANSI_RESET << ANSI_COLOR_GREEN << s[i].nom << ANSI_RESET << endl;
        cout << "# ► " << ANSI_BOLD << "État actuel système" << ANSI_RESET << " : " << endl;
        cout << "#   - CPU : " << ANSI_COLOR_GREEN << s[i].etat_courant.libre.CPU << ANSI_RESET << endl;
        cout << "#   - Stockage : " << ANSI_COLOR_GREEN << s[i].etat_courant.libre.stockage << ANSI_RESET << endl;
        cout << "######################################" << endl;
    }
}

/**********************/
/** FONCTIONS CLIENT **/
/**********************/

const char* getSiteById(unsigned int id){

    switch(id){
        case 0:
            return "Lyon";
            break;
        case 1:
            return "Montpellier";
            break;
        case 2:
            return "Rennes";
            break;
        case 3:
            return "Toulouse";
            break;
        default:
            cout << "erreur getSiteById, id non reconnu" << endl;
            break;
    }

    return "";
}

unsigned int possedeRessourceDansSite(const struct client *c, const char mode[]){

    if(strcmp(mode, "exclusif") == 0 && (c->exclusif.CPU != 0 || c->exclusif.stockage != 0)){
        return (c->exclusif.CPU != 0 && c->exclusif.stockage != 0)? 2:1;

    }
    else if(strcmp(mode, "partage") == 0 && (c->partage.CPU != 0 || c->partage.stockage != 0)){
        return (c->partage.CPU != 0 && c->partage.stockage != 0)? 2:1;
    }

    return 0;
}

// Initialiser client
void initialiserClient(struct client *c, unsigned int nbSite){
    c->id = 0;
    c->exclusif.CPU = 0;
    c->exclusif.stockage = 0;
    c->partage.CPU = 0;
    c->partage.stockage = 0;
}

// Efface un client d'un site s'il ne possède plus de ressource dans ce site
void nettoyerClient(struct etat_sys* s){

    for(unsigned int i=0; i<nSites; i++){
        for(unsigned int j=0; j<nbMaxClient; j++){
            if(s[i].client[j].id != 0 && s[i].client[j].exclusif.CPU == 0 && s[i].client[j].exclusif.stockage == 0 && s[i].client[j].partage.CPU == 0 && s[i].client[j].partage.stockage == 0){
                initialiserClient(&s[i].client[j], nSites);
                s[i].nbClient--;
            }
        }
    }

}

// Affichage infos du client sur les différents sites
void printInfosClient(const struct client *c, unsigned int nbSite){
    
    cout << "id client : " << ANSI_BLINK << ANSI_COLOR_GREEN << c->id << ANSI_RESET << endl;

    for(int i=0; i<nbSite; i++){
        if(possedeRessourceDansSite(&c[i], "exclusif")){
            cout << "Exclusif :" << endl;
            if(c[i].exclusif.CPU != 0){
                cout << "CPU : " << ANSI_COLOR_GREEN << c[i].exclusif.CPU << ANSI_RESET << " à " << ANSI_COLOR_GREEN << getSiteById(i) << ANSI_RESET << endl;
            }
            if(c[i].exclusif.stockage != 0){
                cout << "Stockage : " ANSI_COLOR_GREEN << c[i].exclusif.stockage << " go " << ANSI_RESET << " à " << ANSI_COLOR_GREEN << getSiteById(i) << ANSI_RESET << endl;
            }
        }
        else if(possedeRessourceDansSite(&c[i], "partage")){
            cout << "Partage :" << endl;
            if(c[i].partage.CPU != 0){
                cout << "CPU : " << ANSI_COLOR_GREEN << c[i].partage.CPU << ANSI_RESET << " à " << ANSI_COLOR_GREEN << getSiteById(i) << ANSI_RESET << endl;
            }
            if(c[i].partage.stockage != 0){
                cout << "Stockage : " << ANSI_COLOR_GREEN << c[i].partage.stockage << " go " << ANSI_RESET << " à " << ANSI_COLOR_GREEN << getSiteById(i) << ANSI_RESET << endl;
            }
        }
    }

}

void printClientSiteAll(const struct etat_sys *s){

    for(unsigned int i=0; i<nSites; i++){

        unsigned int n_e = 0;
        unsigned int n_p = 0;

        unsigned int nbClientExclusif = 0;
        unsigned int nbClientPartage = 0;

        cout << "• " << s[i].nom << " : { " << "Réservation exclusive : ";
        for(unsigned int j=0; j<nbMaxClient; j++){

            if(possedeRessourceDansSite(&s[i].client[j], "exclusif") == 1){
                nbClientExclusif++;

                if(nbClientExclusif == 1)
                    cout << ANSI_COLOR_GREEN << "client" << ANSI_RESET << " n°" << ANSI_COLOR_GREEN << s[i].client[j].id << ANSI_RESET << " : ";
                else if(nbClientExclusif >= 2)
                    cout << ", " << ANSI_COLOR_GREEN << "client" << ANSI_RESET << " n°" << ANSI_COLOR_GREEN << s[i].client[j].id << ANSI_RESET << " : ";

                if(s[i].client[j].exclusif.CPU != 0){
                    cout << ANSI_COLOR_GREEN << s[i].client[j].exclusif.CPU << ANSI_RESET << " CPU";
                }
                else if(s[i].client[j].exclusif.stockage != 0){
                    cout << ANSI_COLOR_GREEN << s[i].client[j].exclusif.stockage << ANSI_RESET << " Go de stockage";
                }

                n_e++;
            }
            else if(possedeRessourceDansSite(&s[i].client[j], "exclusif") == 2){
                nbClientExclusif++;

                if(nbClientExclusif == 1)
                    cout << ANSI_COLOR_GREEN << "client" << ANSI_RESET << " n°" << ANSI_COLOR_GREEN << s[i].client[j].id << ANSI_RESET << " : ";
                else if(nbClientExclusif >= 2)
                    cout << ", " << ANSI_COLOR_GREEN << "client" << ANSI_RESET << " n°" << ANSI_COLOR_GREEN << s[i].client[j].id << ANSI_RESET << " : ";

                cout << ANSI_COLOR_GREEN << s[i].client[j].exclusif.CPU << ANSI_RESET << " CPU et " << ANSI_COLOR_GREEN << s[i].client[j].exclusif.stockage << ANSI_RESET << " Go de stockage";

                n_e++;
            }
        }

        if(n_e == 0)
            cout << ANSI_COLOR_GREEN << " Aucune" << ANSI_RESET;

        cout << " | " << "Réservation partagée : ";
        for(unsigned int j=0; j<nbMaxClient; j++){

            if(possedeRessourceDansSite(&s[i].client[j], "partage") == 1){
                nbClientPartage++;

                if(nbClientPartage == 1)
                    cout << ANSI_COLOR_GREEN << "client" << ANSI_RESET << " n°" << ANSI_COLOR_GREEN << s[i].client[j].id << ANSI_RESET << " : ";
                else if(nbClientPartage >= 2)
                    cout << ", " << ANSI_COLOR_GREEN << "client" << ANSI_RESET << " n°" << ANSI_COLOR_GREEN << s[i].client[j].id << ANSI_RESET << " : ";

                if(s[i].client[j].partage.CPU != 0){
                    cout << ANSI_COLOR_GREEN << s[i].client[j].partage.CPU << ANSI_RESET << " CPU";
                    n_p++;
                }
                else if(s[i].client[j].partage.stockage != 0){
                    cout << ANSI_COLOR_GREEN << s[i].client[j].partage.stockage << ANSI_RESET << " Go de stockage";
                    n_p++;
                }
            }
            else if(possedeRessourceDansSite(&s[i].client[j], "partage") == 2){
                nbClientPartage++;

                if(nbClientPartage == 1)
                    cout << ANSI_COLOR_GREEN << "client" << ANSI_RESET << " n°" << ANSI_COLOR_GREEN << s[i].client[j].id << ANSI_RESET << " : ";
                else if(nbClientPartage >= 2)
                    cout << ", " << ANSI_COLOR_GREEN << "client" << ANSI_RESET << " n°" << ANSI_COLOR_GREEN << s[i].client[j].id << ANSI_RESET << " : ";

                cout << ANSI_COLOR_GREEN << s[i].client[j].partage.CPU << ANSI_RESET << " CPU et " << ANSI_COLOR_GREEN << s[i].client[j].partage.stockage << ANSI_RESET << " Go de stockage";
                n_p++;
            }
        }

        if(n_p == 0)
            cout << ANSI_COLOR_GREEN << " Aucune" << ANSI_RESET;

        cout << " }" << endl;
    }

    cout << endl;
}

void printInfosSite(const struct etat_sys* s){
    cout << endl;

    TablePrinter tp(&std::cout);

    tp.AddColumn(s[0].nom, 25);
    tp.AddColumn(s[1].nom, 25);
    tp.AddColumn(s[2].nom, 25);
    tp.AddColumn(s[3].nom, 25);
    tp.PrintHeader();

    // Lyon : libre
    char cpu_str0_l[50];
    sprintf(cpu_str0_l, "   - CPU :   %d", s[0].etat_courant.libre.CPU);
    char stock_str0_l[50];
    sprintf(stock_str0_l, "   - Stockage : %d", s[0].etat_courant.libre.stockage);

    // Lyon : exclusif
    char cpu_str0_e[50];
    sprintf(cpu_str0_e, "   - CPU :   %d", s[0].etat_courant.exclusif.CPU);
    char stock_str0_e[50];
    sprintf(stock_str0_e, "   - Stockage : %d", s[0].etat_courant.exclusif.stockage);

    // Lyon : partagé
    char cpu_str0_p[50];
    sprintf(cpu_str0_p, "   - CPU :   %d", s[0].etat_courant.partage.CPU);
    char stock_str0_p[50];
    sprintf(stock_str0_p, "   - Stockage : %d", s[0].etat_courant.partage.stockage);

    // Montpellier : libre
    char cpu_str1_l[50];
    sprintf(cpu_str1_l, "   - CPU :   %d", s[1].etat_courant.libre.CPU);
    char stock_str1_l[50];
    sprintf(stock_str1_l, "   - Stockage : %d", s[1].etat_courant.libre.stockage);

    // Montpellier : excusif
    char cpu_str1_e[50];
    sprintf(cpu_str1_e, "   - CPU :   %d", s[1].etat_courant.exclusif.CPU);
    char stock_str1_e[50];
    sprintf(stock_str1_e, "   - Stockage : %d", s[1].etat_courant.exclusif.stockage);

    // Montpellier : partagé
    char cpu_str1_p[50];
    sprintf(cpu_str1_p, "   - CPU :   %d", s[1].etat_courant.partage.CPU);
    char stock_str1_p[50];
    sprintf(stock_str1_p, "   - Stockage : %d", s[1].etat_courant.partage.stockage);

    // Rennes : libre
    char cpu_str2_l[50];
    sprintf(cpu_str2_l, "   - CPU :   %d", s[2].etat_courant.libre.CPU);
    char stock_str2_l[50];
    sprintf(stock_str2_l, "   - Stockage : %d", s[2].etat_courant.libre.stockage);

    // Rennes : exclusif
    char cpu_str2_e[50];
    sprintf(cpu_str2_e, "   - CPU :   %d", s[2].etat_courant.exclusif.CPU);
    char stock_str2_e[50];
    sprintf(stock_str2_e, "   - Stockage : %d", s[2].etat_courant.exclusif.stockage);

    // Rennes : partagé
    char cpu_str2_p[50];
    sprintf(cpu_str2_p, "   - CPU :   %d", s[2].etat_courant.partage.CPU);
    char stock_str2_p[50];
    sprintf(stock_str2_p, "   - Stockage : %d", s[2].etat_courant.partage.stockage);

    // Toulouse : libre
    char cpu_str3_l[50];
    sprintf(cpu_str3_l, "   - CPU :   %d", s[3].etat_courant.libre.CPU);
    char stock_str3_l[50];
    sprintf(stock_str3_l, "   - Stockage : %d", s[3].etat_courant.libre.stockage);

    // Toulouse : exclusif
    char cpu_str3_e[50];
    sprintf(cpu_str3_e, "   - CPU :   %d", s[3].etat_courant.exclusif.CPU);
    char stock_str3_e[50];
    sprintf(stock_str3_e, "   - Stockage : %d", s[3].etat_courant.exclusif.stockage);

    // Toulouse : partagé
    char cpu_str3_p[50];
    sprintf(cpu_str3_p, "   - CPU :   %d", s[3].etat_courant.partage.CPU);
    char stock_str3_p[50];
    sprintf(stock_str3_p, "   - Stockage : %d", s[3].etat_courant.partage.stockage);

    tp << " ► État actuel système   " << " ► État actuel système   " << " ► État actuel système   " << " ► État actuel système   ";
    tp << cpu_str0_l << cpu_str1_l << cpu_str2_l << cpu_str3_l;
    tp << stock_str0_l << stock_str1_l << stock_str2_l << stock_str3_l;
    tp << " " << bprinter::endl();
    tp << " ► Réservation exclusive " << " ► Réservation exclusive " << " ► Réservation exclusive " << " ► Réservation exclusive ";
    tp << cpu_str0_e << cpu_str1_e << cpu_str2_e << cpu_str3_e;
    tp << stock_str0_e << stock_str1_e << stock_str2_e << stock_str3_e;
    tp << " " << bprinter::endl();
    tp << " ► Réservation partagée  " << " ► Réservation partagée  " << " ► Réservation partagée  " << " ► Réservation partagée  ";
    tp << cpu_str0_p << cpu_str1_p << cpu_str2_p << cpu_str3_p;
    tp << stock_str0_p << stock_str1_p << stock_str2_p << stock_str3_p;



    tp.PrintFooter();

    cout << endl;
}

// Demande de saisie ressource pour chaque site
void saisieRessourceAll(struct client *c, const struct etat_sys* s, int sem2id, int nbSite){

    struct client bufferClient[nSites];
    for(unsigned int i=0; i<nSites; i++){
        initialiserClient(&bufferClient[i], nSites);
    }

    sem_lock(sem2id, 0);
    // On intiialise le buffer (pour vérifier les valeurs saisies)
    for(unsigned int i=0; i<nSites; i++){
       for(unsigned int j=0; j<nbMaxClient; j++){
           if(s[i].client[j].id == getpid()){
               copyInfosClient(&s[i].client[j], &bufferClient[i]);
               break;
           }
       }
    }
    sem_unlock(sem2id, 0);

    for(int i=0; i<nbSite; i++){

        sem_lock(sem2id, 0);
        unsigned int nbCpuInitial = s[i].etat_init.CPU;
        unsigned int nbStockageInitial = s[i].etat_init.stockage;
        unsigned int nbCpuLibre = s[i].etat_courant.libre.CPU;
        unsigned int nbStockageLibre = s[i].etat_courant.libre.stockage;
        sem_unlock(sem2id, 0);

        c[i].id = getpid(); // On associe un id au client lors de la saisie

        //cout << ANSI_COLOR_WHITE_H << "                       " << ANSI_RESET << endl;
        cout << endl;
 
        int CPU = -1;
        int stockage = -1;
        cout << "► " << ANSI_BOLD <<"Site : " << ANSI_RESET << ANSI_COLOR_GREEN << s[i].nom << ANSI_RESET << endl;
        cout << "► " << ANSI_BOLD << "État initial système : " << ANSI_RESET << endl;
        cout << "   - CPU : " << ANSI_COLOR_GREEN << s[i].etat_init.CPU << ANSI_RESET << endl;
        cout << "   - Stockage : " << ANSI_COLOR_GREEN << s[i].etat_init.stockage << ANSI_RESET << endl;
        cout << "► " << ANSI_BOLD << "État actuel système" << ANSI_RESET << " : " << endl;
        cout << "   - CPU : " << ANSI_COLOR_GREEN << s[i].etat_courant.libre.CPU << ANSI_RESET << endl;
        cout << "   - Stockage : " << ANSI_COLOR_GREEN << s[i].etat_courant.libre.stockage << ANSI_RESET << endl;

        char resv_mode_s[1000] = "";
        int resv_mode_i = 0;


        do{ // Mode de réservation (exclusif ou partagé)
            cout << ANSI_UNDERLINE << "# Choisissez un mode de réservation :" << ANSI_RESET << endl;
            cout << "1. Je ne souhaite pas réserver de ressource à " << ANSI_COLOR_GREEN << s[i].nom << ANSI_RESET << endl;
            cout << "2. Exclusif" << endl;
            cout << "3. Partage" << endl;
            cout << "> ";

            cin.getline(resv_mode_s, 1000);
            resv_mode_i = atoi(resv_mode_s);
            
            if(resv_mode_i!=1 && resv_mode_i !=2 && resv_mode_i !=3)
                cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl;

            cout << endl;

        }while(resv_mode_i!=1 && resv_mode_i!=2 && resv_mode_i!=3);

        if(resv_mode_i == 2 || resv_mode_i == 3){

            char resv_CPU_s[1000] = "";
            int resv_CPU_i = 0;

            do{ // Réservation CPU 
                cout << ANSI_UNDERLINE << "# Choisissez le nombre de CPU à réserver " << ANSI_COLOR_RED << "(/!\\ MAX = " << s[i].etat_init.CPU << ")" << ANSI_RESET << " :" << endl;
                cout << "> ";

                cin.getline(resv_CPU_s, 1000);
                resv_CPU_i = atoi(resv_CPU_s);
                
                if(resv_CPU_i > s[i].etat_init.CPU || resv_CPU_i < 0)
                    cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl;
                else if(resv_mode_i == 2 && (bufferClient[i].exclusif.CPU+bufferClient[i].partage.CPU+resv_CPU_i) > s[i].etat_init.CPU){
                    cout << endl << ANSI_COLOR_RED << "✖ Erreur, situation d'autoblocage évitée" << ANSI_RESET << endl;
                }
                else if(resv_mode_i == 3 && (resv_CPU_i+bufferClient[i].exclusif.CPU) > s[i].etat_init.CPU){
                    cout << endl << ANSI_COLOR_RED << "✖ Erreur, situation d'autoblocage évitée" << ANSI_RESET << endl;
                }

                cout << endl;

            }while(resv_CPU_i > s[i].etat_init.CPU || resv_CPU_i < 0 || 
            resv_mode_i == 2 && (bufferClient[i].exclusif.CPU+bufferClient[i].partage.CPU+resv_CPU_i) > s[i].etat_init.CPU ||
            resv_mode_i == 3 && (resv_CPU_i+bufferClient[i].exclusif.CPU) > s[i].etat_init.CPU);

            char resv_stockage_s[1000] = "";
            int resv_stockage_i = 0;

            do{ // Réservation stockage 
                cout << ANSI_UNDERLINE << "# Choisissez le nombre de Go de stockage à réserver " << ANSI_COLOR_RED << "(/!\\ MAX = " << s[i].etat_init.stockage << " Go)" << ANSI_RESET << " :" << endl;
                cout << "> ";

                cin.getline(resv_stockage_s, 1000);
                resv_stockage_i = atoi(resv_stockage_s);
                
                if(resv_stockage_i > s[i].etat_init.stockage || resv_stockage_i < 0)
                    cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl;
                else if(resv_mode_i == 2 && (bufferClient[i].exclusif.stockage+bufferClient[i].partage.stockage+resv_stockage_i) > s[i].etat_init.stockage){
                    cout << endl << ANSI_COLOR_RED << "✖ Erreur, situation d'autoblocage évitée" << ANSI_RESET << endl;
                }
                else if(resv_mode_i == 3 && (resv_stockage_i+bufferClient[i].exclusif.stockage) > s[i].etat_init.stockage){
                    cout << endl << ANSI_COLOR_RED << "✖ Erreur, situation d'autoblocage évitée" << ANSI_RESET << endl;
                }
                
                cout << endl;

            }while(resv_stockage_i > s[i].etat_init.stockage || resv_stockage_i < 0 || 
            resv_mode_i == 2 && (bufferClient[i].exclusif.stockage+bufferClient[i].partage.stockage+resv_stockage_i) > s[i].etat_init.stockage ||
            resv_mode_i == 3 && (resv_stockage_i+bufferClient[i].exclusif.stockage) > s[i].etat_init.stockage);

            if(resv_mode_i == 2 && (resv_CPU_i != 0 || resv_stockage_i != 0)){ // Mode exclusif
                c[i].exclusif.CPU = resv_CPU_i;
                c[i].exclusif.stockage = resv_stockage_i;
            }
            else if(resv_mode_i == 3 && (resv_CPU_i != 0 || resv_stockage_i != 0)){ // Mode stockage
                c[i].partage.CPU = resv_CPU_i;
                c[i].partage.stockage = resv_stockage_i;
            }
            else{
                if(resv_mode_i == 2){ // Cas ou le client saisie les valeurs 0 CPU & 0 Stockage
                    c[i].exclusif.CPU = 0;
                    c[i].exclusif.stockage = 0;
                }
                else if(resv_mode_i == 3){
                    c[i].partage.CPU = 0;
                    c[i].partage.stockage = 0;
                }
            }
        }
        else{
            // Le client n'a rien réservé sur ce site
            c[i].exclusif.CPU = 0;
            c[i].exclusif.stockage = 0;
            c[i].partage.CPU = 0;
            c[i].partage.stockage = 0;
        }
    }
}

// Demande de saisie pour rendre des ressources sur chaque site
void rendreRessourceAll(const struct etat_sys* s, struct client *c, int sem2id,  int nbSite){

    unsigned int possedeRessource = 0;

    struct client bufferClient[nSites];
    for(unsigned int i=0; i<nSites; i++){
        initialiserClient(&bufferClient[i], nSites);
    }

    sem_lock(sem2id, 0);
    // On intiialise le buffer (pour vérifier les valeurs saisies)
    for(unsigned int i=0; i<nSites; i++){
       for(unsigned int j=0; j<nbMaxClient; j++){
           if(s[i].client[j].id == getpid()){
               copyInfosClient(&s[i].client[j], &bufferClient[i]);
               break;
           }
       }
    }
    sem_unlock(sem2id, 0);

    for(unsigned int i=0; i<nbSite; i++){

        c[i].id = getpid();

        // Si le client en possède aucune ressource dans un site donné, alors on ne lui propose pas d'en rendre
        if(possedeRessourceDansSite(&bufferClient[i], "exclusif") == 0 && possedeRessourceDansSite(&bufferClient[i], "partage") == 0){
            possedeRessource++;
            continue;
        }

        cout << endl << "► " << ANSI_BOLD <<"Site : " << ANSI_RESET << ANSI_COLOR_GREEN << getSiteById(i) << ANSI_RESET << endl;
        if(possedeRessourceDansSite(&bufferClient[i], "exclusif")){

            if(bufferClient[i].exclusif.CPU != 0 && bufferClient[i].exclusif.stockage != 0){
                cout << ANSI_BOLD <<"► " << ANSI_RESET << "Vous disposez de : " << ANSI_COLOR_GREEN << bufferClient[i].exclusif.CPU << ANSI_RESET << " CPU et " << ANSI_COLOR_GREEN << bufferClient[i].exclusif.stockage << ANSI_RESET << " go de stockage, en " << ANSI_COLOR_GREEN << "mode exclusif" << ANSI_RESET << endl;
            }
            else if(bufferClient[i].exclusif.CPU != 0){
                cout << ANSI_BOLD <<"► " << ANSI_RESET << "Vous disposez de : " << ANSI_COLOR_GREEN << bufferClient[i].exclusif.CPU << ANSI_RESET << " CPU, en " << ANSI_COLOR_GREEN << "mode exclusif" << ANSI_RESET << endl;
            }
            else if(bufferClient[i].exclusif.stockage != 0){
                cout << ANSI_BOLD <<"► " << ANSI_RESET << "Vous disposez de : " << ANSI_COLOR_GREEN << bufferClient[i].exclusif.stockage << ANSI_RESET << " go de stockage, en " << ANSI_COLOR_GREEN << "mode exclusif" << ANSI_RESET << endl;
            }
        }

        if(possedeRessourceDansSite(&bufferClient[i], "partage")){

            if(bufferClient[i].partage.CPU != 0 && bufferClient[i].partage.stockage != 0){
                cout << ANSI_BOLD <<"► " << ANSI_RESET << "Vous disposez de : " << ANSI_COLOR_GREEN << bufferClient[i].partage.CPU << ANSI_RESET << " CPU et " << ANSI_COLOR_GREEN << bufferClient[i].partage.stockage << ANSI_RESET << " go de stockage, en " << ANSI_COLOR_GREEN << "mode partagé" << ANSI_RESET << endl;
            }
            else if(bufferClient[i].partage.CPU != 0){
                cout << ANSI_BOLD <<"► " << ANSI_RESET << "Vous disposez de : " << ANSI_COLOR_GREEN << bufferClient[i].partage.CPU << ANSI_RESET << " CPU, en " << ANSI_COLOR_GREEN << "mode partagé" << ANSI_RESET << endl;
            }
            else if(bufferClient[i].partage.stockage != 0){
                cout << ANSI_BOLD <<"► " << ANSI_RESET << "Vous disposez de : " << ANSI_COLOR_GREEN << bufferClient[i].partage.stockage << ANSI_RESET << " go de stockage, en " << ANSI_COLOR_GREEN << "mode partagé" << ANSI_RESET << endl;
            }
        }

        cout << endl;

        char resv_mode_s[1000] = "";
        int resv_mode_i = 0;

        do{ // Mode de réservation (exclusif ou partagé)
            cout << ANSI_UNDERLINE << "# Choisissez le type de ressource que vous souhaitez rendre :" << ANSI_RESET << endl;
            cout << "1. Je ne souhaite pas rendre de ressource sur le site de " << ANSI_COLOR_GREEN << getSiteById(i) << ANSI_RESET << endl;
            cout << "2. Exclusive" << endl;
            cout << "3. Partagée" << endl;
            cout << "> ";

            cin.getline(resv_mode_s, 1000);
            resv_mode_i = atoi(resv_mode_s);
            
            if(resv_mode_i!=1 && resv_mode_i !=2 && resv_mode_i !=3)
                cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl << endl;;

            cout << endl;

        }while(resv_mode_i!=1 && resv_mode_i!=2 && resv_mode_i!=3);

        char resv_CPU_s[1000] = "";
        int resv_CPU_i = 0;
        char resv_stockage_s[1000] = "";
        int resv_stockage_i = 0;

        if(resv_mode_i == 2){
            
            if(possedeRessourceDansSite(&bufferClient[i], "exclusif")){

                if(bufferClient[i].exclusif.CPU != 0 && bufferClient[i].exclusif.stockage != 0){
                    do{ // Réservation CPU 
                        cout << ANSI_UNDERLINE << "# Choisissez le nombre de CPU à rendre " << ANSI_COLOR_RED << "(/!\\ MAX = " << bufferClient[i].exclusif.CPU << ")" << ANSI_RESET << endl;
                        cout << "> ";

                        cin.getline(resv_CPU_s, 1000);
                        resv_CPU_i = atoi(resv_CPU_s);
                        
                        if(resv_CPU_i > bufferClient[i].exclusif.CPU || resv_CPU_i < 0)
                            cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl << endl;;

                        cout << endl;

                    }while(resv_CPU_i > bufferClient[i].exclusif.CPU || resv_CPU_i < 0);

                    do{ // Réservation stockage 
                        cout << ANSI_UNDERLINE << "# Choisissez le nombre de Go de stockage à rendre " << ANSI_COLOR_RED << "(/!\\ MAX = " << bufferClient[i].exclusif.stockage << " Go)" << ANSI_RESET << endl;
                        cout << "> ";

                        cin.getline(resv_stockage_s, 1000);
                        resv_stockage_i = atoi(resv_stockage_s);
                        
                        if(resv_stockage_i > bufferClient[i].exclusif.stockage || resv_stockage_i < 0)
                            cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl << endl;;
                        
                        cout << endl;

                    }while(resv_stockage_i > bufferClient[i].exclusif.stockage || resv_stockage_i < 0);
                }
                else if(bufferClient[i].exclusif.CPU != 0){
                    do{ // Réservation CPU 
                        cout << ANSI_UNDERLINE << "# Choisissez le nombre de CPU à rendre " << ANSI_COLOR_RED << "(/!\\ MAX = " << bufferClient[i].exclusif.CPU << ")" << ANSI_RESET << endl;
                        cout << "> ";

                        cin.getline(resv_CPU_s, 1000);
                        resv_CPU_i = atoi(resv_CPU_s);
                        
                        if(resv_CPU_i > bufferClient[i].exclusif.CPU || resv_CPU_i < 0)
                            cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl << endl;;

                        cout << endl;

                    }while(resv_CPU_i > bufferClient[i].exclusif.CPU || resv_CPU_i < 0);
                }
                else if(bufferClient[i].exclusif.stockage != 0){
                    do{ // Réservation stockage 
                        cout << ANSI_UNDERLINE << "# Choisissez le nombre de Go de stockage à rendre " << ANSI_COLOR_RED << "(/!\\ MAX = " << bufferClient[i].exclusif.stockage << " Go)" << ANSI_RESET << endl;
                        cout << "> ";

                        cin.getline(resv_stockage_s, 1000);
                        resv_stockage_i = atoi(resv_stockage_s);
                        
                        if(resv_stockage_i > bufferClient[i].exclusif.stockage || resv_stockage_i < 0)
                            cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl << endl;;
                        
                        cout << endl;

                    }while(resv_stockage_i > bufferClient[i].exclusif.stockage || resv_stockage_i < 0);
                }
                else{
                    cout << endl << ANSI_COLOR_RED << "✖ Erreur, vous ne disposez d'aucune ressource exclusive sur ce site" << ANSI_RESET << endl << endl;;
                }

                // En construit la demande de rendre des ressources du client
                if(resv_CPU_i != 0 || resv_stockage_i != 0){ 
                    c[i].exclusif.CPU = resv_CPU_i;
                    c[i].exclusif.stockage = resv_stockage_i;
                }
            }
            else{
                cout << ANSI_COLOR_RED << "✖ Vous ne disposez d'aucune ressource en mode exclusive sur ce site" << ANSI_RESET << endl << endl;
            }
        }
        else if(resv_mode_i == 3){

            if(possedeRessourceDansSite(&bufferClient[i], "partage")){
                if(bufferClient[i].partage.CPU != 0 && bufferClient[i].partage.stockage != 0){
                    do{ // Réservation CPU 
                        cout << ANSI_UNDERLINE << "# Choisissez le nombre de CPU à rendre " << ANSI_COLOR_RED << "(/!\\ MAX = " << bufferClient[i].partage.CPU << ")" << ANSI_RESET << endl;
                        cout << "> ";

                        cin.getline(resv_CPU_s, 1000);
                        resv_CPU_i = atoi(resv_CPU_s);
                        
                        if(resv_CPU_i > bufferClient[i].partage.CPU || resv_CPU_i < 0)
                            cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl << endl;;

                        cout << endl;

                    }while(resv_CPU_i > bufferClient[i].partage.CPU || resv_CPU_i < 0);

                    do{ // Réservation stockage 
                        cout << ANSI_UNDERLINE << "# Choisissez le nombre de Go de stockage à rendre " << ANSI_COLOR_RED << "(/!\\ MAX = " << bufferClient[i].partage.stockage << " Go)" << ANSI_RESET << endl;
                        cout << "> ";

                        cin.getline(resv_stockage_s, 1000);
                        resv_stockage_i = atoi(resv_stockage_s);
                        
                        if(resv_stockage_i > bufferClient[i].partage.stockage || resv_stockage_i < 0)
                            cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl << endl;;
                        
                        cout << endl;

                    }while(resv_stockage_i > bufferClient[i].partage.stockage || resv_stockage_i < 0);
                }
                else if(bufferClient[i].partage.CPU != 0){
                    do{ // Réservation CPU 
                        cout << ANSI_UNDERLINE << "# Choisissez le nombre de CPU à rendre " << ANSI_COLOR_RED << "(/!\\ MAX = " << bufferClient[i].partage.CPU << ")" << ANSI_RESET << endl;
                        cout << "> ";

                        cin.getline(resv_CPU_s, 1000);
                        resv_CPU_i = atoi(resv_CPU_s);
                        
                        if(resv_CPU_i > bufferClient[i].partage.CPU || resv_CPU_i < 0)
                            cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl << endl;;

                        cout << endl;

                    }while(resv_CPU_i > bufferClient[i].partage.CPU || resv_CPU_i < 0);
                }
                else if(bufferClient[i].partage.stockage != 0){
                    do{ // Réservation stockage 
                        cout << ANSI_UNDERLINE << "# Choisissez le nombre de Go de stockage à rendre " << ANSI_COLOR_RED << "(/!\\ MAX = " << bufferClient[i].partage.stockage << " Go)" << ANSI_RESET << endl;
                        cout << "> ";

                        cin.getline(resv_stockage_s, 1000);
                        resv_stockage_i = atoi(resv_stockage_s);
                        
                        if(resv_stockage_i > bufferClient[i].partage.stockage || resv_stockage_i < 0)
                            cout << endl << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl << endl;
                        
                        cout << endl;

                    }while(resv_stockage_i > bufferClient[i].partage.stockage || resv_stockage_i < 0);
                }
                else{
                    cout << endl << ANSI_COLOR_RED << "✖ Erreur, vous ne disposez d'aucune ressource partagée sur ce site" << ANSI_RESET << endl << endl;
                }

                // En construit la demande de rendre des ressources du client
                if(resv_CPU_i != 0 || resv_stockage_i != 0){ 
                    c[i].partage.CPU = resv_CPU_i;
                    c[i].partage.stockage = resv_stockage_i;
                }
            }
            else{
                cout << ANSI_COLOR_RED << "✖ Vous ne disposez d'aucune ressource en mode partagé sur ce site" << ANSI_RESET << endl << endl;
            }

        }

    }

    if(possedeRessource == nbSite){
        cout << endl << ANSI_COLOR_RED << "✖ Erreur, vous ne possedez aucune ressource donc vous ne pouvez pas en rendre" << ANSI_RESET << endl << endl;
    }
}

// On obtient le nombre d'opération a réalisé d'un client
unsigned int getNbOp(struct client *c, unsigned int nbSite){
    unsigned int nbOp = 0;

    for(unsigned int i=0; i<nbSite; i++){
        nbOp += possedeRessourceDansSite(&c[i], "exclusif") + possedeRessourceDansSite(&c[i], "partage");
    }

    return nbOp;
}

// Opération avant demande de ressource sur le segment (après saisie)
void initialisationOpRessourceP(struct client *c, struct etat_sys *s, struct sembuf *tabSemBufP, int idTabSem, int sem2id, unsigned int *nbOp){

    sem_lock(sem2id, 0); // On verrouille le segment

    unsigned int nOp = 0;

    for(unsigned int i=0; i<tailleSem/2; i++){ // CPU

        if(possedeRessourceDansSite(&c[i], "exclusif")){ // CPU exclusif
            if(c[i].exclusif.CPU != 0){
                // P : demande de ressource
                tabSemBufP[nOp].sem_num = i;
                tabSemBufP[nOp].sem_op = -c[i].exclusif.CPU;
                tabSemBufP[nOp].sem_flg = 0;

                //hide cout << "(exclusif/cpu) tabSemBufP[" << nOp << "] = " << tabSemBufP[nOp].sem_op << " (P) | Appliqué sur le sem n°" << tabSemBufP[nOp].sem_num << endl;

                nOp++;
            }

        }
        else if(possedeRessourceDansSite(&c[i], "partage")){ // CPU partage
            if(c[i].partage.CPU != 0){
                // P : demande de ressource
                if(s[i].etat_courant.partage.CPU == 0){ // Cas ou il n'y a aucun CPU en partagé
                    tabSemBufP[nOp].sem_num = i;
                    tabSemBufP[nOp].sem_op = -c[i].partage.CPU;
                    tabSemBufP[nOp].sem_flg = 0;
                    
                    //hide cout << "(partage/cpu) tabSemBufP[" << nOp << "] = " << tabSemBufP[nOp].sem_op << " (P) | Appliqué sur le sem n°" << tabSemBufP[nOp].sem_num << endl;

                    nOp++;
                }
                else if(c[i].partage.CPU > s[i].etat_courant.partage.CPU){ // Cas ou il y a du CPU en partagé
                    tabSemBufP[nOp].sem_num = i;
                    tabSemBufP[nOp].sem_op = -(c[i].partage.CPU-s[i].etat_courant.partage.CPU);
                    tabSemBufP[nOp].sem_flg = 0;
            
                    //hide cout << "(partage/cpu) tabSemBufP[" << nOp << "] = " << tabSemBufP[nOp].sem_op << " (P) | Appliqué sur le sem n°" << tabSemBufP[nOp].sem_num << endl;

                    nOp++;
                }
            }

        }
        
    }

    unsigned int j=0;

    for(unsigned int i=4; i<tailleSem; i++){ // Stockage

        if(possedeRessourceDansSite(&c[j], "exclusif")){ // Stockage exclusif
            if(c[j].exclusif.stockage != 0){
                // P : demande de ressource
                tabSemBufP[nOp].sem_num = i;
                tabSemBufP[nOp].sem_op = -c[j].exclusif.stockage;
                tabSemBufP[nOp].sem_flg = 0;
                
                //hide cout << "(exclusif/stockage) tabSemBufP[" << nOp << "] = " << tabSemBufP[nOp].sem_op << " (P) | Appliqué sur le sem n°" << tabSemBufP[nOp].sem_num << endl;

                nOp++;
            }

        }
        else if(possedeRessourceDansSite(&c[j], "partage")){ // Stockage partage
            if(c[j].partage.stockage != 0){
                // P : demande de ressource
                if(s[j].etat_courant.partage.stockage == 0){ // Cas ou il n'y a aucun Stcokage en partagé
                    tabSemBufP[nOp].sem_num = i;
                    tabSemBufP[nOp].sem_op = -c[j].partage.stockage;
                    tabSemBufP[nOp].sem_flg = 0;
                    
                    //hide cout << "(partage/stockage) tabSemBufP[" << nOp << "] = " << tabSemBufP[nOp].sem_op << " (P) | Appliqué sur le sem n°" << tabSemBufP[nOp].sem_num << endl;

                    nOp++;
                }
                else if(c[j].partage.stockage > s[j].etat_courant.partage.stockage){ // Cas ou il y a du Stockage en partagé
                    tabSemBufP[nOp].sem_num = i;
                    tabSemBufP[nOp].sem_op = -(c[j].partage.CPU-s[j].etat_courant.partage.stockage);
                    tabSemBufP[nOp].sem_flg = 0;
            
                    //hide cout << "(partage/stockage) tabSemBufP[" << nOp << "] = " << tabSemBufP[nOp].sem_op << " (P) | Appliqué sur le sem n°" << tabSemBufP[nOp].sem_num << endl;

                    nOp++;
                }
            }

        }

        j++;

    }

    //cout << "nOp = " << nOp << endl; 
    *nbOp = nOp;

    sem_unlock(sem2id, 0); // On déverouille le segment
}

// Opération avant rendu de ressource sur le segment (après saisie)
void initialisationOpRessourceV(struct client *c, struct etat_sys *s, struct sembuf *tabSemBufV, int idTabSem, int sem2id, unsigned int *nbOp){

    struct client clientBuffer[nSites]; // On récupère les possessions du client
    for(unsigned int i=0; i<nSites; i++){
        initialiserClient(&clientBuffer[i], nSites);
    }

    for(unsigned int i=0; i<nSites; i++){
        for(unsigned int j=0; j<nbMaxClient; j++){
            if(s[i].client[j].id == getpid()){
                copyInfosClient(&s[i].client[j], &clientBuffer[i]);
                break;
            }
        }
    }

    unsigned int nOp = 0;

    for(unsigned int i=0; i<tailleSem/2; i++){ // CPU

        if(possedeRessourceDansSite(&c[i], "exclusif")){ // CPU exclusif
            if(c[i].exclusif.CPU != 0){
                // V : rendu de ressource
                tabSemBufV[nOp].sem_num = i;
                tabSemBufV[nOp].sem_op = +c[i].exclusif.CPU;
                tabSemBufV[nOp].sem_flg = 0;

                //hide cout << "(exclusif/cpu) tabSemBufV[" << nOp << "] = " << tabSemBufV[nOp].sem_op << " (V) | Appliqué sur le sem n°" << tabSemBufV[nOp].sem_num << endl;

                nOp++;
            }

        }
        
        if(possedeRessourceDansSite(&c[i], "partage")){ // CPU partage
            if(c[i].partage.CPU != 0){
                // V : rendu de ressource
                if((clientBuffer[i].partage.CPU-c[i].partage.CPU) > pgvCpuPartage(&s[i], nSites)){ // Cas ou il y a du CPU en partagé

                    tabSemBufV[nOp].sem_num = i;
                    tabSemBufV[nOp].sem_op = +c[i].partage.CPU;
                    tabSemBufV[nOp].sem_flg = 0;
            
                    //hide cout << "(partage/cpu) tabSemBufV[" << nOp << "] = " << tabSemBufV[nOp].sem_op << " (V) | Appliqué sur le sem n°" << tabSemBufV[nOp].sem_num << endl;

                    nOp++;
                }
                else if((clientBuffer[i].partage.CPU > pgvCpuPartage(&s[i], nSites)) && ((clientBuffer[i].partage.CPU-c[i].partage.CPU) <= pgvCpuPartage(&s[i], nSites))){

                    tabSemBufV[nOp].sem_num = i;
                    tabSemBufV[nOp].sem_op = +(clientBuffer[i].partage.CPU-pgvCpuPartage(&s[i], nSites));
                    tabSemBufV[nOp].sem_flg = 0;
            
                    //hide cout << "(partage/cpu) tabSemBufV[" << nOp << "] = " << tabSemBufV[nOp].sem_op << " (V) | Appliqué sur le sem n°" << tabSemBufV[nOp].sem_num << endl;

                    nOp++;
                }
            }

        }
        
    }

    unsigned int j=0;

    for(unsigned int i=4; i<tailleSem; i++){ // Stockage

        if(possedeRessourceDansSite(&c[j], "exclusif")){ // Stockage exclusif
            if(c[j].exclusif.stockage != 0){
                // V : rendu de ressource
                tabSemBufV[nOp].sem_num = i;
                tabSemBufV[nOp].sem_op = +c[j].exclusif.stockage;
                tabSemBufV[nOp].sem_flg = 0;
                
                //hide cout << "(exclusif/stockage) tabSemBufV[" << nOp << "] = " << tabSemBufV[nOp].sem_op << " (V) | Appliqué sur le sem n°" << tabSemBufV[nOp].sem_num << endl;

                nOp++;
            }

        }
        
        if(possedeRessourceDansSite(&c[j], "partage")){ // Stockage partage
            if(c[j].partage.stockage != 0){
                // V : rendu de ressource
                if((clientBuffer[j].partage.stockage-c[j].partage.stockage) > pgvStockagePartage(&s[j], nSites)){ // Cas ou il y a du Stockage en partagé
                    
                    tabSemBufV[nOp].sem_num = i;
                    tabSemBufV[nOp].sem_op = +c[j].partage.stockage;
                    tabSemBufV[nOp].sem_flg = 0;
            
                    //hide cout << "(partage/stockage) tabSemBufV[" << nOp << "] = " << tabSemBufV[nOp].sem_op << " (V) | Appliqué sur le sem n°" << tabSemBufV[nOp].sem_num << endl;

                    nOp++;
                }
                else if((clientBuffer[j].partage.stockage > pgvStockagePartage(&s[j], nSites)) && ((clientBuffer[j].partage.stockage-c[j].partage.stockage) <= pgvStockagePartage(&s[j], nSites))){

                    tabSemBufV[nOp].sem_num = i;
                    tabSemBufV[nOp].sem_op = +(clientBuffer[j].partage.stockage-pgvStockagePartage(&s[j], nSites));
                    tabSemBufV[nOp].sem_flg = 0;
            
                    //hide cout << "(partage/stockage) tabSemBufV[" << nOp << "] = " << tabSemBufV[nOp].sem_op << " (V) | Appliqué sur le sem n°" << tabSemBufV[nOp].sem_num << endl;

                    nOp++;
                }
            }

        }

        j++;
    }

    //cout << "nOp = " << nOp << endl; 
    *nbOp = nOp;
}

// Prend l'id d'un sémpahore en entrée et renvoi l'id du site associé
int donneIdSiteAssocie(unsigned int idDuSemaphore){
    if(idDuSemaphore < tailleSem/2){
        return idDuSemaphore; // CPU
    }
    else if(idDuSemaphore >= tailleSem/2 && idDuSemaphore < tailleSem){
        return idDuSemaphore-(tailleSem/2); // Stockage
    }

    return -1; // erreur
}

// Vérifie si le client existe dans un site donné
unsigned int clientExisteDansSite(unsigned int idClient, const struct etat_sys *s){

    unsigned int boolean = 0;

    for(unsigned int i=0; i<nbMaxClient; i++){
        if(s->client[i].id == idClient){
            boolean = 1;
            break;
        }
    }

    return boolean;
}

// Inscrit le client dans le tableau de client sur segment de mémoire partagé
void abonneClient(const struct client *c, struct etat_sys *s, int nbSites){

    for(unsigned int i=0; i<nbSites; i++){
        for(unsigned int j=0; j<nbMaxClient; j++){

            if(clientExisteDansSite(getpid(), &s[i]) == 1 && s[i].client[j].id == getpid()){ // Il appartient déjà au site
                ajoutInfosClient(&c[i], &s[i].client[j]);
                break;
            }
            else{ // Il n'appartient pas au site
                if(clientExisteDansSite(getpid(), &s[i]) == 0 && s[i].client[j].id == 0 && (possedeRessourceDansSite(&c[i], "exclusif") || possedeRessourceDansSite(&c[i], "partage"))){
                    copyInfosClient(&c[i], &s[i].client[j]);
                    break;
                }
            }
        }
    }

    //hide cout << "Le client : " << c->id << " vient de s'abonner au segment" << endl;
}

// On modifie le shm
void modificationSite(const struct client *c, struct etat_sys *s, char *notif, int sem2id, int nbSites){

    char notification[1000] = "";
    
    sem_lock(sem2id, 0); // On verrouille le segment
    for(unsigned int i=0; i<nbSites; i++){

        char buffer[250] = "";

        if(possedeRessourceDansSite(&c[i], "exclusif")){
            s[i].etat_courant.libre.CPU -= c[i].exclusif.CPU;
            s[i].etat_courant.exclusif.CPU += c[i].exclusif.CPU;
            s[i].etat_courant.libre.stockage -= c[i].exclusif.stockage;
            s[i].etat_courant.exclusif.stockage += c[i].exclusif.stockage;

            

            if(c[i].exclusif.CPU != 0 && c[i].exclusif.stockage !=0)
                sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient d'effectuer une réservation de \x1b[32m%d\x1b[0m CPU et de \x1b[32m%d\x1b[0m go de stockage en \x1b[32mmode exclusif\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].exclusif.CPU, c[i].exclusif.stockage, getSiteById(i));
            else if(c[i].exclusif.CPU != 0)
                sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient d'effectuer une réservation de \x1b[32m%d\x1b[0m CPU  en \x1b[32mmode exclusif\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].exclusif.CPU, getSiteById(i));
            else if(c[i].exclusif.stockage != 0)
                sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient d'effectuer une réservation de \x1b[32m%d\x1b[0m go de stockage en \x1b[32mmode exclusif\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].exclusif.stockage, getSiteById(i));

            if(clientExisteDansSite(getpid(), &s[i]) == 0)
                s[i].nbClient++; // On ajoute un client
        }
        else if(possedeRessourceDansSite(&c[i], "partage")){
            // CPU
            if(s[i].etat_courant.partage.CPU == 0){
                s[i].etat_courant.libre.CPU -= c[i].partage.CPU;
                s[i].etat_courant.partage.CPU += c[i].partage.CPU;
            }
            else if(c[i].partage.CPU > s[i].etat_courant.partage.CPU){
                s[i].etat_courant.libre.CPU -= (c[i].partage.CPU-s[i].etat_courant.partage.CPU);
                s[i].etat_courant.partage.CPU += (c[i].partage.CPU-s[i].etat_courant.partage.CPU);
            }

            // Stockage
            if(s[i].etat_courant.partage.stockage == 0){
                s[i].etat_courant.libre.stockage -= c[i].partage.stockage;
                s[i].etat_courant.partage.stockage += c[i].partage.stockage;
            }
            else if(c[i].partage.stockage > s[i].etat_courant.partage.stockage){
                s[i].etat_courant.libre.stockage -= (c[i].partage.stockage-s[i].etat_courant.partage.stockage);
                s[i].etat_courant.partage.stockage += (c[i].partage.stockage-s[i].etat_courant.partage.stockage);
            }

            if(c[i].partage.CPU != 0 && c[i].partage.stockage !=0)
                sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient d'effectuer une réservation de \x1b[32m%d\x1b[0m CPU et de \x1b[32m%d\x1b[0m go de stockage en \x1b[32mmode partagé\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].partage.CPU, c[i].partage.stockage, getSiteById(i));
            else if(c[i].partage.CPU != 0)
                sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient d'effectuer une réservation de \x1b[32m%d\x1b[0m CPU  en \x1b[32mmode partagé\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].partage.CPU, getSiteById(i));
            else if(c[i].partage.stockage != 0)
                sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient d'effectuer une réservation de \x1b[32m%d\x1b[0m go de stockage en \x1b[32mmode partagé\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].partage.stockage, getSiteById(i));

            if(clientExisteDansSite(getpid(), &s[i]) == 0)
                s[i].nbClient++; // On ajoute un client
        }

        strcat(notification, buffer);
    }

    sem_lock(sem2id, 1); // On verrouille le segment notif

    memset(notif, 0, strlen(notif)); // On vide la string
    strcpy(notif, notification); // On écrit dans la string
    setValSem(sem2id, 2, 0); // On affecte la valeur 0 au sémaphore pour provoquer le réveil

    sem_unlock(sem2id, 1); // On déverouille le segment notif

    abonneClient(c, s, nSites);
    sem_unlock(sem2id, 0); // On déverouille le segment
}

unsigned int pgvCpuPartage(const struct etat_sys *s, unsigned int nbSite){

    unsigned int pid = 0;
    unsigned int valCPUpartage = 0;


    for(unsigned int j=0; j<nbMaxClient; j++){
        if(s->client[j].id != getpid() && s->client[j].partage.CPU > valCPUpartage){
            valCPUpartage = s->client[j].partage.CPU;
            pid = s->client[j].id;
        }
    }

    return valCPUpartage;  
}

unsigned int pgvCpuPartageInclus(const struct etat_sys *s, unsigned int nbSite){

    unsigned int pid = 0;
    unsigned int valCPUpartage = 0;


    for(unsigned int j=0; j<nbMaxClient; j++){
        if(s->client[j].partage.CPU > valCPUpartage){
            valCPUpartage = s->client[j].partage.CPU;
            pid = s->client[j].id;
        }
    }

    return valCPUpartage;  
}

unsigned int pgvStockagePartage(const struct etat_sys *s, unsigned int nbSite){

    unsigned int pid = 0;
    unsigned int valStockagePartage = 0;


    for(unsigned int j=0; j<nbMaxClient; j++){
        if(s->client[j].id != getpid() && s->client[j].partage.stockage > valStockagePartage){
            valStockagePartage = s->client[j].partage.stockage;
            pid = s->client[j].id;
        }
    }

    return valStockagePartage;  
}

unsigned int pgvStockagePartageInclus(const struct etat_sys *s, unsigned int nbSite){

    unsigned int pid = 0;
    unsigned int valStockagePartage = 0;


    for(unsigned int j=0; j<nbMaxClient; j++){
        if(s->client[j].partage.stockage > valStockagePartage){
            valStockagePartage = s->client[j].partage.stockage;
            pid = s->client[j].id;
        }
    }

    return valStockagePartage;  
}

void* getNotification(void* param){

    struct paramNotif *p = (struct paramNotif*)param;

    struct sembuf semZ;
    semZ.sem_num = 2;
    semZ.sem_op = 0;
    semZ.sem_flg = SEM_UNDO;

    struct sembuf semV;
    semV.sem_num = 2;
    semV.sem_op = +1;
    semV.sem_flg = SEM_UNDO;

    do{
        demandeRessource(&semZ, p->idSem, 1);
        sem_lock(p->idSem, 1); // On verrouille le segment notif
        mutex_lock(p->mutex); // verrou affichage lock
        cout << endl << p->adrShmNotif << endl;
        mutex_unlock(p->mutex); // verrou affichage unlock
        sem_unlock(p->idSem, 1); // On déverrouille le segment notif
        demandeRessource(&semV, p->idSem, 1);
    }while(1);
}

// le client rend des ressources sur un ou plusieurs sites
void clientRendRessourceSurSite(const struct client *c, struct etat_sys *s, char *notif, int sem2id, int nbSite){

    char notification[1000] = "";

    for(unsigned int i=0; i<nbSite; i++){ // CPU

        char buffer[250] = "";

        for(unsigned int j=0; j<nbMaxClient; j++){

            if(s[i].client[j].id == getpid()){

                if(possedeRessourceDansSite(&c[i], "exclusif")){ 
                    if(c[i].exclusif.CPU != 0){ // CPU exclusif
                        // on rend la ressource
                        s[i].etat_courant.exclusif.CPU -= c[i].exclusif.CPU;
                        s[i].etat_courant.libre.CPU += c[i].exclusif.CPU;

                        s[i].client[j].exclusif.CPU -= c[i].exclusif.CPU;
                    }
                    
                    if(c[i].exclusif.stockage != 0){ // Stockage en exclusif
                        // on rend la ressource
                        s[i].etat_courant.exclusif.stockage -= c[i].exclusif.stockage;
                        s[i].etat_courant.libre.stockage += c[i].exclusif.stockage;

                        s[i].client[j].exclusif.stockage -= c[i].exclusif.stockage;
                    }

                    if(c[i].exclusif.CPU != 0 && c[i].exclusif.stockage !=0)
                        sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient de rendre \x1b[32m%d\x1b[0m CPU et \x1b[32m%d\x1b[0m go de stockage en \x1b[32mmode exclusif\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].exclusif.CPU, c[i].exclusif.stockage, getSiteById(i));
                    else if(c[i].exclusif.CPU != 0)
                        sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient de rendre \x1b[32m%d\x1b[0m CPU  en \x1b[32mmode exclusif\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].exclusif.CPU, getSiteById(i));
                    else if(c[i].exclusif.stockage != 0)
                        sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient de rendre \x1b[32m%d\x1b[0m go de stockage en \x1b[32mmode exclusif\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].exclusif.stockage, getSiteById(i));
                }
                
                if(possedeRessourceDansSite(&c[i], "partage")){ 

                    if(c[i].partage.CPU != 0){ // CPU partage
                        
                        if((s[i].client[j].partage.CPU-c[i].partage.CPU) > pgvCpuPartage(&s[i], nSites)){ // Cas ou la difference entre ce que j'ai et ce que je souhaite rendre reste > aux cpu partagées de tous les clients
                            s[i].etat_courant.partage.CPU = (s[i].client[j].partage.CPU-c[i].partage.CPU);
                            s[i].etat_courant.libre.CPU += c[i].partage.CPU;
                        }
                        else if(((s[i].client[j].partage.CPU > pgvCpuPartage(&s[i], nSites))  && ((s[i].client[j].partage.CPU-c[i].partage.CPU) <= pgvCpuPartage(&s[i], nSites)))){
                            s[i].etat_courant.partage.CPU = pgvCpuPartage(&s[i], nSites);
                            s[i].etat_courant.libre.CPU += (s[i].client[j].partage.CPU-pgvCpuPartage(&s[i], nSites));
                        }

                        s[i].client[j].partage.CPU -= c[i].partage.CPU;
                    }
                    
                    if(c[i].partage.stockage != 0){ // Stockage en partagé

                        if((s[i].client[j].partage.stockage-c[i].partage.stockage) > pgvStockagePartage(&s[i], nSites)){ // Cas ou la difference entre ce que j'ai et ce que je souhaite rendre reste > au stockage partagé de tous les clients
                            s[i].etat_courant.partage.stockage = (s[i].client[j].partage.stockage-c[i].partage.stockage);
                            s[i].etat_courant.libre.stockage += c[i].partage.stockage;
                        }
                        else if(((s[i].client[j].partage.stockage > pgvStockagePartage(&s[i], nSites)) && ((s[i].client[j].partage.stockage-c[i].partage.stockage) <= pgvStockagePartage(&s[i], nSites)))){
                            s[i].etat_courant.partage.stockage = pgvStockagePartage(&s[i], nSites);
                            s[i].etat_courant.libre.stockage += (s[i].client[j].partage.stockage-pgvStockagePartage(&s[i], nSites));
                        }

                        s[i].client[j].partage.stockage -= c[i].partage.stockage;
                    }

                    if(c[i].partage.CPU != 0 && c[i].partage.stockage !=0)
                        sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient de rendre \x1b[32m%d\x1b[0m CPU et \x1b[32m%d\x1b[0m go de stockage en \x1b[32mmode partagé\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].partage.CPU, c[i].partage.stockage, getSiteById(i));
                    else if(c[i].partage.CPU != 0)
                        sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient de rendre \x1b[32m%d\x1b[0m CPU  en \x1b[32mmode partagé\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].partage.CPU, getSiteById(i));
                    else if(c[i].partage.stockage != 0)
                        sprintf(buffer, "\x1b[32m\033[5m⮕\x1b[0m Le client n°\x1b[32m%d\x1b[0m vient de rendre \x1b[32m%d\x1b[0m go de stockage en \x1b[32mmode partagé\x1b[0m sur le site de \x1b[32m%s\x1b[0m\n", c[i].id, c[i].partage.stockage, getSiteById(i));   
                }

                break;
            }
        }

        strcat(notification, buffer);
    }

    sem_lock(sem2id, 1); // On verrouille le segment notif

    memset(notif, 0, strlen(notif)); // On vide la string
    strcpy(notif, notification); // On écrit dans la string

    if(strlen(notif) != 0) 
        setValSem(sem2id, 2, 0); // On affecte la valeur 0 au sémaphore pour provoquer le réveil

    sem_unlock(sem2id, 1); // On déverouille le segment notif

    nettoyerClient(s); // Si le client a tout rendu, on l'efface
}

// Suppresion client shm
// le client rend des ressources sur un ou plusieurs sites
void suppressionClientSite(struct etat_sys *s, char *notif, int semid,  int sem2id, int nbSite){


    struct client clientBuffer[nSites]; // On récupère les possessions du client
    for(unsigned int i=0; i<nSites; i++){
        initialiserClient(&clientBuffer[i], nSites);
    }

    for(unsigned int i=0; i<nSites; i++){
        for(unsigned int j=0; j<nbMaxClient; j++){
            if(s[i].client[j].id == getpid()){
                copyInfosClient(&s[i].client[j], &clientBuffer[i]);
                break;
            }
        }
    }
    
    unsigned int nbOpV = getNbOp(clientBuffer, nSites);
    struct sembuf tabSemBufV[nbOpV];

    initialisationOpRessourceV(clientBuffer, s, tabSemBufV, semid, sem2id, &nbOpV);

    clientRendRessourceSurSite(clientBuffer, s, notif, sem2id, nSites);

    demandeRessource(tabSemBufV, semid, nbOpV);

    cout << "fin du client : les ressources ont été libéré (s'il en avait)" << endl;
}

// Menu de navigation
int menuNavigation(struct etat_sys* ptr, char* ptr2, int semid, int sem2id, pthread_t idThread, pthread_mutex_t *verrouAffichage){
    char action_s[1000] = "";
    int action_i = 0;

    do{
        mutex_lock(verrouAffichage);
        TablePrinter tp(&std::cout);
        tp.AddColumn("                  MENU", 40);
        tp.PrintHeader();
        tp << "  1. Afficher l'etat du systeme";
        tp << "  2. Effectuer une reservation";
        tp << "  3. Rendre des ressources";
        tp << "  4. Quitter le programme";
        tp.PrintFooter();

        cout << endl << ANSI_UNDERLINE << "# Je souhaite" << ANSI_RESET << " :" << endl;
        cout << "> ";
        mutex_unlock(verrouAffichage);

        cin.getline(action_s, 1000);
        action_i = atoi(action_s);
            
        if(action_i!=1 && action_i !=2 && action_i !=3 && action_i!=4)
            cout << ANSI_COLOR_RED << "✖ Erreur, veuillez entrer une valeur valide" << ANSI_RESET << endl;

    }while(action_i!=1 && action_i!=2 && action_i!=3 && action_i!=4);


    if(action_i == 1){
        cout << endl << "► Client n°" << ANSI_COLOR_GREEN << ANSI_BLINK << getpid() << ANSI_RESET<< endl;
        printInfosSite(ptr);
        printClientSiteAll(ptr);
    }
    else if(action_i == 2){
        // Structure de demande du client pour chacun des sites
        struct client demandeClient[nSites]; 
        for(int i=0; i<nSites; i++){
            initialiserClient(&demandeClient[i], nSites);
        }

        // On demande au client de saisir sa réservation
        saisieRessourceAll(demandeClient, ptr, sem2id, nSites);

        // On affiche les infos du client
        //hide printInfosClient(demandeClient, nSites);
        
        // Implémentation des opérations P
        unsigned int nbOpP = getNbOp(demandeClient, nSites);
        unsigned int nbOpPApresInit = 0;
        struct sembuf tabSemBufP[nbOpP];

        // On construit la demande du client (sembuf)
        initialisationOpRessourceP(demandeClient, ptr, tabSemBufP, semid, sem2id, &nbOpPApresInit);

        // On effectue la demande du client (semop)
        demandeRessource(tabSemBufP, semid, nbOpPApresInit);

        // On modifie le segment en fonction de la demande du client
        modificationSite(demandeClient, ptr, ptr2, sem2id, nSites);
    }
    else if(action_i == 3){
        struct client rendreClient[nSites]; 
        for(int i=0; i<nSites; i++){
            initialiserClient(&rendreClient[i], nSites);
        }

        // On demande au client de saisir ce qu'il souhaite rendre
        rendreRessourceAll(ptr, rendreClient, sem2id, nSites);

        // Implémentation des opérations V
        unsigned int nbOpV = getNbOp(rendreClient, nSites);
        unsigned int nbOpVApresInit = 0;
        struct sembuf tabSemBufV[nbOpV];

        sem_lock(sem2id, 0); // On verrouille le segment site

        // On construit la demande du client (sembuf)
        initialisationOpRessourceV(rendreClient, ptr, tabSemBufV, semid, sem2id, &nbOpVApresInit);

        // On modifie le segment en fonction de la demande du client
        clientRendRessourceSurSite(rendreClient, ptr, ptr2, sem2id, nSites);

        // On effectue la demande du client (semop)
        demandeRessource(tabSemBufV, semid, nbOpVApresInit);

        sem_unlock(sem2id, 0); // On deverrouille le segment site
    }
    else if(action_i == 4){
        // On supprime le client du segment
        sem_lock(sem2id, 0); // On verrouille le segment site
        suppressionClientSite(ptr, ptr2, semid, sem2id, nSites);
        sem_unlock(sem2id, 0); // On deverrouille le segment site

        // Destruction du mutex
        mutex_destroy(verrouAffichage);
        pthread_cancel(idThread);
    
        // Détachement du segment
        segmentDt(ptr);
        segmentDt(ptr2);

        return 0;
    }

    return 1;
}

// En cas d'arrêt impromptu du client, il quitte proprement (rend les ressources et se détache...)
int sighandlerClient(const int signal, void *ptr){

    static struct sigHandlerC *saved = NULL;

    if(saved == NULL){
        saved = (struct sigHandlerC*)ptr;
    }

    if(signal == 2){
        cout << endl << endl << ANSI_COLOR_GREEN_H << "C'est vraiment pas sympa d'essayer de quitter comme ça..." << ANSI_RESET << endl;
        sleep(2);
        cout << ANSI_COLOR_GREEN_H << "Bon ça passe pour cette fois, je rends les ressources à ta place." << ANSI_RESET << endl << endl;;
        sleep(2);

        sem_lock(saved->sem2id, 0);
        suppressionClientSite(saved->s, saved->notif, saved->semid, saved->sem2id, nSites);
        sem_unlock(saved->sem2id, 0);


        mutex_destroy(saved->verrou);
        pthread_cancel(saved->idThread);

        segmentDt(saved->s);
        segmentDt(saved->notif);

        exit(0);
    }


    return 1;
}

// En cas d'arrêt impromptu du serveur, le serveur quitte proprement (détruit les objets IPC)
int sighandlerServeur(const int signal, void *ptr){

    static struct sigHandlerS *saved = NULL;

    if(saved == NULL){
        saved = (struct sigHandlerS*)ptr;
    }

    if(signal == 2){
        cout << endl << endl << ANSI_COLOR_GREEN_H << "Extinction prématurée du serveur..." << ANSI_RESET << endl;
        sleep(2);
        cout << ANSI_COLOR_GREEN_H << "Destruction des objets IPC en cours..." << ANSI_RESET << endl << endl;;
        sleep(2);


        mutex_destroy(saved->verrou);
        pthread_cancel(saved->idThread);

        segmentDt(saved->s);
        segmentDt(saved->notif);

        destructionSegment(saved->idShm1);
        destructionSegment(saved->idShm2);

        destructionTabSem(saved->semid);
        destructionTabSem(saved->sem2id);

        cout << endl << "fin serveur" << endl;

        exit(0);
    }


    return 1;
}