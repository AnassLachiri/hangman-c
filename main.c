#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char lireCaractere();
bool isFound(char* word);
void manipulate(char c, char* word, char* found, int* coups);
int numWords(FILE* dict);
static void rmnl(char* text);

/************************************ Main Function ************************************/

int main(int argc, char* argv[]){
    srand(time(NULL));

    FILE* dict;
    dict = fopen("dict.txt", "r");
    if(dict==NULL){
        printf("Error occured while opening the dict file!!\n");
        exit(0);
    }

    char line[20];
    int check = fgets(line, 20, dict);

    int counter = 0;
    while(check != NULL){
        counter++;
        check = fgets(line, 20, dict);
    }

    if(counter == 0){
        printf("No words in the dict file!!\n");
        exit(0);
    }

    char word[20];
    rewind(dict);

    int nb_line = rand()%counter;
    int count = 0;
    fgets(word, 20, dict);
    while(count<nb_line){
        count++;
        fgets(word, 20, dict);
    }
    rmnl(word);

    char *found = malloc(strlen(word)*sizeof(char));
    for(int i = 0; i<strlen(word); i++){
        found[i] = '*';
    }

    int coups = 10;
    char c;

    
    printf("Bienvenue dans le Pendu !!\n");

    do{
        printf("Il vous reste %d coups a jouer \nQuel est le mot secret ? %s \nProposez une lettre : ", coups, found);
        c = lireCaractere();
        manipulate(c, word, found, &coups);
        printf("\n");

    }while(coups>0 && !isFound(found));

    if(coups==0){
        printf("Tu as perdu!! le mot est %s\n", word);
    }else{
        printf("Gagne!! le mot est %s\n", found);
    }

    free(found);

    return 0;
}


/***************************** Functions *****************************/

int numChars(char * name, int size){
    
}

char lireCaractere() { 
    char caractere = 0;
 
    caractere = getchar(); // On lit le premier caractère
    caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà
 
    // On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer) 
    while (getchar() != '\n') ;
 
    return caractere; // On retourne le premier caractère qu'on a lu 
}

bool isFound(char* word){
    for(int i = 0; i<strlen(word); i++){
        if(word[i]=='*') return false;
    }
    return true;
}

void manipulate(char c, char* word, char* found, int* coups){
    int oc = 0;
    for(int i = 0; i<strlen(word); i++){
        if(word[i]==c){
            found[i]=c;
            oc++;
        }
    }
    if(oc==0) *coups-=1;
}

static void rmnl(char* text){
    for(int i = 0; i<strlen(text); i++){
        if(text[i]=='\n') text[i]='\0';
    }
}

