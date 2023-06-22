#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void clear(){
    system("clear");
}

char *filestring(char* argv)
{ // Initialise les fichiers de texte fournis, n étant le fichier donné comme argument au terminal
  char c;
  int cpt = 0;

  /*Calcule la taille du fichier*/
  FILE *f = fopen(argv, "r");
  while (fscanf(f, "%c", &c) != EOF)
  {
    cpt = cpt + 1;
  }
  fclose(f);
  /* Stocke le texte du fichier dans un string*/
  char *texte = malloc((cpt + 1) * sizeof(char));
  texte[cpt] = '\0';
  f = fopen(argv, "r");
  cpt = 0;

  while (fscanf(f, "%c", &c) != EOF)
  {
    texte[cpt] = c;
    cpt = cpt + 1;
  }
  return texte;
}

void remove_spaces(char* s) { /* Mon code pour résoudre les expressions n'accepte pas des espaces.*/
    char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

int tempvaluate(char* string){ // For a given expression, return answer. Expression CAN include spaces.
    char todo[strlen(string) + 200];
    char strung[strlen(string)];
    
    strcpy(strung, string);

    remove_spaces(strung);

    strcpy(todo, "cd infixpostfix && echo \"");
    strcat(todo, strung); 
    strcat(todo,"\" | ./InfixPostfix | ocaml InfixPostfix.ml");
    strcat(todo,"> ../temp.txt"); // (saves to temp.txt)
    system(todo);

    return atoi(filestring("temp.txt"));  
}

void evaluate_expression(char* string){ // string has to be spaceless. 
    char todo[strlen(string) + 200];

    strcpy(todo, "cd infixpostfix && echo \"");
    strcat(todo, string); 
    strcat(todo,"\" | ./InfixPostfix | ocaml InfixPostfix.ml");
    strcat(todo,">> ../expanswers.txt"); // (also saves result to expanswers.txt)
    system(todo);
}

char* expression(int n, int d, int lvl){ // n = number of numbers per expression, max digits of numbers
    char* expression = malloc((n*d) * 50 * sizeof(char));
    int n2 = n;
    int o = 0; // Is a parentheses open?
    int l = 9 + 9 * pow(10, d-1);
    int m;
    int x = -1;
    n = n2;
    while (n > 0){
        
        int r = rand() % 4;

        if (r == 0){// add sum
            int s1 = 1 +(rand() % l);
            int s2 = 1 +(rand() % l);

            char sum[d*2 + 20];

            snprintf(sum, d*2+20, "%d + %d", s1, s2);

            strcat(expression, sum);

            n--;} 
        if (r == 1){// add sub
            int s1 = 0;
            int s2 = 1;
            if(lvl == 0){
                while(s1 - s2 < 0){
                    s1 = 1 +(rand() % l); s2 = 1 +(rand() % l);}}
            else{
            s1 = 1 +(rand() % l); 
            s2 = 1 +(rand() % l);}
            char sum[d*2 + 20];

            snprintf(sum, d*2 + 20, "%d - %d", s1, s2);
            strcat(expression, sum);

            n--;} 
        if (r == 2){// add mult
            int s1 = 1 +(rand() % l);
            int s2 = 1 +(rand() % l);


            char sum[d*2+20];

            snprintf(sum, d*2+20, "%d * %d", s1, s2);

            strcat(expression, sum);

            n--;} 
        if (r == 3){// add divide
            int s1 = 1 +(rand() % l);
            int s2 = 1 +(rand() % l);

            while (s1 % s2 != 0 || s1 == s2 || s2 == 1){ // s2 ne peut pas être 1, s2 ne peut pas être s1 (trop faciles).
            s1 = 1 +(rand() % l);
            s2 = 1 +(rand() % l);
            }

            char sum[d*2+20];

            snprintf(sum, d*2+20, "(%d / %d)", s1, s2);

            strcat(expression, sum);

            n--;} 
        r = rand() % 3;

        int p = rand() % 2;
        if (o == 1 && p == 1){strcat(expression, ")"); o--;}


        if(r == 0 && n != 0) { strcat(expression, " + ");}
        if(r == 1 && n != 0) { strcat(expression, " * ");}
        if(r == 2 && n != 0) { strcat(expression, " - ");}

        p = rand() % 2;
        if (p == 1 && n != 0){strcat(expression, "("); o++;}
    }

    while(o != 0){strcat(expression, ")"); o--;} 

    return expression;
}

void savefile(int n, int d, int k, int lvl){ // number of numbers per expresion, max digits of numbers, number of expressions to save. lvl= negative results allowed
    char* string = malloc(k * n * 30 * sizeof(char));
    char* solutions = malloc (d * 20 * sizeof(char));
    char* tempxpression = malloc (n * 30 *  sizeof(char));
    system("truncate -s 0 expanswers.txt");
    strcpy(string, "");
    
    for(int i = 0; i < k; i++){
        clear();
        printf("Saving... (%d/%d)\n", i+1, k);
        tempxpression = expression(n,d,lvl);
        int x = tempvaluate(tempxpression);

        if (lvl == 0){
        while(x < 0){
            tempxpression = expression(n,d,lvl);
            x = tempvaluate(tempxpression);
        }
        }

        strcat(string, tempxpression);
        strcat(string,"\n");        

        remove_spaces(tempxpression);
        evaluate_expression(tempxpression);
    }

    FILE *filexp;
    filexp = fopen("expressions.txt", "w+");
    fprintf(filexp, "%s", string);
    fclose(filexp);
    printf("Fichier 'expressions.txt' sauvegardé avec succes avec %d problèmes à résoudre\n", k );
    free(string);
    free(tempxpression);
    free(solutions);
}

bool isperfsquare(int d){
    float f = sqrt((double)d);
    int i = f;

    return (i == f);
}

int* polynomial(int d){ //d = max digits per coefficient. all equations will have only real solutions
    int* polynome = malloc( 5 * sizeof(int));
    int a,b,c,delta, s;
    int l = (10 * pow(10, d-1));
    
    a = rand() % l;
    b = rand() % l;
    c = rand() % l;
    delta = (b*b - 4*a*c);


    while( a == 0 || (b % a != 0) || (c % a != 0) || ( delta < 0 ) || !(isperfsquare(delta))){ 
        a = rand() % l;
        b = rand() % l;
        c = rand() % l;
        
        s = rand() % 2;
        if(s == 1){a = -a;}
        
        s = rand() % 2;
        if(s == 1){b = -b;}

        s = rand() % 2;
        if(s == 1){c = -c;}

        delta = (b*b - 4*a*c);
    }

    polynome[0] = a; 
    polynome[1] = b; 
    polynome[2] = c;

    return polynome;
} 

char* stringpol(int p[3], int d){

    char* str = malloc((d*6 + 10)*sizeof(char));
    // There has to be a better way to do this. Didn't find it.
    if(p[1] >= 0 && p[2]>= 0){ 
        sprintf(str, "%dX^2 + %dX + %d\n",p[0],p[1],p[2]);
    }
    else if (p[1] < 0 && p[2] >= 0){
        sprintf(str, "%dX^2 %dX + %d\n",p[0],p[1],p[2]);
    }
    else{
        sprintf(str, "%dX^2 %dX %d\n",p[0],p[1],p[2]);
    }

    return str;
}

int* roots(int p[3]){
    int* roots = malloc(10 * sizeof(int));
    int d = (p[1]*p[1]) - (4*p[0]*p[2]);

    roots[0] = ( (-1*p[1] + sqrt(d))/(2*p[0]));
    roots[1] = ( (-1*p[1] - sqrt(d))/(2*p[0]));
    return roots;
}

char* stringsol(int p[3], int d){
    char* solstring = malloc(d * 5 * sizeof(char));
    int* root = roots(p);

    if(root[0] == root[1]){
        sprintf(solstring, "%d\n", root[0]);
    }
    else {sprintf(solstring, "%d , %d\n", root[0], root[1]);}

    return solstring;
}

void polynomials(int d, int n){ //d = max digits per coefficient. n number of expressions to create.
    char* fullstring = malloc(n *(d*6 + 10)*sizeof(char));
    char* solutions = malloc(n * d * 5 * sizeof(char));

    for(int i = 0; i<n;i++){
        clear();
        printf("Saving... (%d/%d)\n", i+1, n);

        int* p = malloc(5*sizeof(int));
        p = polynomial(d);
        strcat(fullstring, stringpol(p, d));
        strcat(solutions, stringsol(p, d));
        
        free(p);
    }
    
    FILE *poly;
    poly = fopen("expressions.txt", "w+");
    fprintf(poly, "%s", fullstring);
    fclose(poly);

    FILE *solfile;
    solfile = fopen("expanswers.txt", "w+");
    fprintf(solfile, "%s", solutions);
    fclose(solfile);

    printf("Fichier 'expressions.txt' sauvegardé avec succes avec %d problèmes à résoudre\n", n);
}

void arith_interac(){   
    char opt[10];
    int n, d, k, lvl;
    clear();
    printf("-GÉNERATION DE PROBLÈMES D'ARITHMETIQUE:-\n");

    printf("\nQuantité de calculs à faire par problème:\n");
    scanf("%s", opt);
    n = atoi(opt);

    strcpy(opt,"");
    printf("\nQuantité maximale de chiffres par nombre:\n");
    scanf("%s", opt);
    d = atoi(opt);

    strcpy(opt,"");
    printf("\nQuantité d'expressions à génerer:\n");
    scanf("%s", opt);
    k = atoi(opt);

    strcpy(opt,"");
    printf("\nChoisir niveau. \n0: Le Résultat de l'expression et les sous-expressions sont positifs.\n1: Expression peut avoir des nombres négatifs\nVotre choix:\n");
    scanf("%s", opt);
    lvl = atoi(opt);

    savefile(n,d,k, lvl);
    return;
    }

void poly_interac(){
    char opt[10];
    int d, n;
    clear();
    printf("-GÉNERATION D'ÉQUATIONS DE SECOND DEGRÉ:-\n");
    printf("\nChiffres maximales par coefficient:\n");
    scanf("%s", opt);
    d = atoi(opt);

    strcpy(opt,"");
    printf("\nQuantité de polynômes à génerer:\n");
    scanf("%s", opt);
    n = atoi(opt);

    polynomials(d,n);
}

void interactive(){
    clear();
    bool t = true;
    char opt[10];

    while (t){
        printf("Que voulez vous faire?\n1: Arithmétique (Generation de Problèmes)\n2: Géneration Équations Quadratiques\n3: Afficher dernières expressions crées.\n4: Afficher réponses.\n5: Fermer.");
        printf("\nVotre choix:\n");
        scanf("%s", opt);
        if(atoi(opt) == 1){
        arith_interac();
        }
        if(atoi(opt) == 2){
            poly_interac();
        }
        if(atoi(opt) == 3){
            clear();
            system("cat expressions.txt");
            printf("\n");
        }
        if(atoi(opt) == 4){
            clear();
            system("cat expanswers.txt");
            printf("\n");
        }
        if(atoi(opt) == 5){
            clear();
            return;
        }
        else{};
        strcpy(opt,"");
        }
}

int main(int argc, char *argv[]) {
    interactive();
    return 0;
}
