// Demineur.hpp
// Lang: "fr"

#include <iostream>
#include <string>
#include <time.h>
#include "libs/termkit/termkit.cpp"
#include "libs/termkit/termkit.hpp"

using namespace std;

const char bombe = '&';       // Variable globale des bombes
int k, m;               // Variable globale : remplace les valeurs x et y, i et j...
int bombCounter = 1;    // Variable globale du compteur de bombes : initialisée à 1 autre que 0 (conflit avec le main sinon)

void graff() {  

    cout << termkit::center_text_block(R"(
oooooooooo.                                o8o                  By Axel MAS              
888     `Y8b                               `"'                                           
888      888  .ooooo.  ooo. .oo.  .oo.   oooo  ooo. .oo.    .ooooo.  oooo  oooo  oooo d8b
888      888 d88   88b  888P  Y88bP Y88b  888   888P  Y88b d88' `88b  888   888   888""8P
888      888 888ooo888  888   888   888   888   888   888  888ooo888  888   888   888    
888     d88' 888    .o  888   888   888   888   888   888  888    .o  888   888   888    
o888bood8P'  `Y8bod8P' o888o o888o o888o o888o o888o o888o `Y8bod8P' `V88V"V8P' d888b  
    )", 90)<<endl;
}

void regles() { 
// Règles & astuces
    termkit::clear();
    graff();

    cout << R"(+------## REGLES ##------+

    Le joueur selectionne une case sur la grille, et cette case revele un nombre qui indique le nombre de mines se trouvant dans les cases adjacentes.
    En utilisant ces informations, vous devez deduire l'emplacement des mines et les marquer avec des drapeaux pour les eviter.
    La strategie et la logique sont essentielles pour reussir au Demineur. vous devez faire preuve de prudence et de reflexion pour eviter les cases piegees
    tout en decouvrant les cases sures.
    Chaque decision compte, car une erreur peut conduire a une explosion et a la fin de la partie.
    En fonction de la taille de la grille et du nombre de mines, le niveaux de difficulte sera evolutif. Ce jeu captivant et stimulant met a l'epreuve les
    competences analytiques et la prise de decision du joueur.

    +-----## ASTUCES ##-----+

    -> Commencez par les cases sures : Avant de prendre des risques, commencez par reveler les cases qui sont entourees par un grand nombre de cases deja
    revelees. Cela reduit les possibilites d'explosion et vous donne plus d'infos pour prendre des decisions.
    -> Analysez les chiffres : Les chiffres indiquent le nombre de mines adjacentes a une case. Utilisez ces informations pour deduire les emplacements
    possibles des mines. Si une case a un chiffre eleve, cela signifie qu'il y a plusieurs mines a proximite, alors que si elle a un chiffre bas, cela indique
    moins de mines autour.
    -> Marquez les mines potentielles : Si vous suspectez la presence d'une mine, marquez-la avec un drapeau ou un symbole approprie. Cela vous aide a eviter
    de cliquer accidentellement sur cette case et a garder une trace des emplacements probables des mines.
    -> Utilisez les indices : Parfois, vous atteindrez une situation ou toutes les cases environnantes d'un chiffre donne ont ete revelees. Cela signifie que
    les mines restantes doivent se trouver ailleurs. Profitez de cette information pour explorer de nouvelles zones et reduire les possibilites.
    -> Soyez attentif aux modeles : Au fur et a mesure que vous jouez, vous remarquerez peut-etre des motifs recurrents dans la disposition des mines. Apprendre
    a reconnaitre ces modeles peut vous aider a anticiper les emplacements des mines et a prendre des decisions plus eclairees.

    Avec de la pratique et de l'experience, vous deviendrez de plus en plus habile a anticiper les emplacements des mines et a eviter les explosions. Bonne chance ! )" << endl;
}

void grille(char Tab[16][30], int &max_c, int &max_l) {

    max_c = 9;                          // max_c = Colonne
    max_l = 9;                          // max_l = Ligne
}


// Séquence de début du jeu

void debut() {

    termkit::clear();
    graff();

    cout << endl;
    cout << termkit::center_line("Bienvenue dans le jeu du Demineur !") << endl;
    cout << endl;

    char x;
    cout << "Voulez-vous connaitre les regles du jeu : Oui = Y, Non = N" << endl;

    cout << "</> : ";
    cin >> x;

    if (x == 'y' || x == 'Y') {
        
        regles();
        cout << endl;

        cout << "Commencer ? : faites Y" << endl;
        cout << "</> : ";
        cin >> x;

        if (x == 'y' || x == 'Y') {
            termkit::clear();
        }
        else {
            cout << "La valeur rentree n'est pas bonne, merci de rentrer Y." << endl;
            cout << "Veuillez reessayer !!" << endl;
            cout << endl;
            sleep(1);
            debut();
        }
    }

    else if (x == 'n' || x == 'N') {
        termkit::clear();
    }
    else {
        cout << "La valeur rentree n'est pas bonne, merci de rentrer Y ou N." << endl;
        cout << "Veuillez reessayer !!" << endl;
        cout << endl;
        sleep(1);
        debut();
    }
}


// Cette fonction sert à initialiser le tableau. Dans le "main", elle reset puis recrée un tableau basique

string init(char Tab[16][30], int &max_c, int &max_l) {

    string s = "";                          // Chaîne de caractère
    for (int i = 0; i < 16; i++) {

        for (int j = 0; j < 30; j++) {
            
            Tab[i][j] = '-';                // Initialisation visuelle dans le terminal, elle est sous forme :
            s += "  ";                      // ..-..-..-..-..-  (. pour espace)  
        }
        s += '\n';                          // \n = Retour à la ligne
    }
    return s;
}

// Cette procédure sert à afficher ou ré-afficher le tableau

void affGrille(char Tab[16][30], int &max_c, int &max_l) {

    sleep(5);
    termkit::clear();
    graff();

    int l = 64;                     // Dans la table ASCII : la valeur avant A vaut 64 en décimal // A = 65
    string s = "";                  
    string bar = "  |";             // Sert a donner une meilleure esthetique au tableau (A"  |"  -)


    cout << "#  #  1  2  3  4  5  6  7  8  9  #" << endl;       // Repérage chiffres pour Facile
    cout << "#  +-----------------------------+" << endl;       // Haut du tableau

    
    for (int i = 0; i < max_c; i++) {
        l += 1;                          // La valeur est incrémentée de 1 lors d'un saut de ligne
        s += l ;                         // Partie milieu-gauche du tableau
        s += bar;                        // On ajoute "bar" pour l'esthetique => (A"  |"  -)

        for (int j = 0; j < max_l; j++) {
            s += "  "; 

            if (Tab[i][j] == bombe) {
                s += "-";
            }
            else {
                s += Tab[i][j];
            }
        }
        
        s += bar;
        s += '\n';
    }

    cout << s;
    cout << "#  +-----------------------------+" << endl;       // Bas du tableau pour Facile

}

// On remplace aléatoirement le nombre de bombes en fonction de la difficulté désirée sur le tableau

void bombes(char Tab[16][30], int &max_c, int &max_l) {

    srand((unsigned int)time(NULL));

    int i, j;
    int b = 10;                                     // Nombre de bombes total sur le jeu
    for (int m = 0; m < b; m++) {
        i = rand() % max_c;                         // Ligne
        j = rand() % max_l;                         // Colonne

        if (Tab[i][j] == '-') {                     // On vérifie que la case est libre
            Tab[i][j] = bombe;                      // On remplace la bombe                                                        
        }

        else {                                      // Si jamais déjà occupé par une bombe ou non libre pour quelconque raison :
            b++;                                    // On ajoute un emplacement pour eviter une superposition de bombes au même endroit
        }
    }
}


// Cherche si autour de l'emplacement selectionné validé (si tiret) d'autres tirets sont placés pour les valider à la suite

void tiretAutour(char mask[16][30], char Tab[16][30], int max_c, int max_l, int k, int m)
{
    if (k - 1 >= 0 && m + 1 <= max_c) {
        if (mask[k - 1][m + 1] == '-' && Tab[k - 1][m + 1] == '-') {                        //  -1 / +1
                                                                                           
            Tab[k - 1][m + 1] = ' ';                                                        // | x - - |
            mask[k - 1][m + 1] = ' ';                                                       // | - o - |
            tiretAutour(mask, Tab, max_c, max_l, k - 1, m + 1);                             // | - - - |
        }
        else {
            Tab[k - 1][m + 1] = mask[k - 1][m + 1];
        }
    }

    if (k - 1 >= 0) {
        if (mask[k - 1][m] == '-' && Tab[k - 1][m] == '-') {                                //  -1 / 0

            Tab[k - 1][m] = ' ';                                                            // | - - - |
            mask[k - 1][m] = ' ';                                                           // | x o - |
            tiretAutour(mask, Tab, max_c, max_l, k - 1, m);                                 // | - - - |
        }
        else {
            Tab[k - 1][m] = mask[k - 1][m];
        }
    }

    if (k - 1 >= 0 && m - 1 >= 0) {
        if (mask[k - 1][m - 1] == '-' && Tab[k - 1][m - 1] == '-') {                        //  -1 / -1

            Tab[k - 1][m - 1] = ' ';                                                        // | - - - |
            mask[k - 1][m - 1] = ' ';                                                       // | - o - |
            tiretAutour(mask, Tab, max_c, max_l, k - 1, m - 1);                             // | x - - |
        }
        else {
            Tab[k - 1][m - 1] = mask[k - 1][m - 1];
        }
    }

    if (m - 1 >= 0) {
        if (mask[k][m - 1] == '-' && Tab[k][m - 1] == '-') {                                //  0 / -1

            Tab[k][m - 1] = ' ';                                                            // | - - - |
            mask[k][m - 1] = ' ';                                                           // | - o - |
            tiretAutour(mask, Tab, max_c, max_l, k, m - 1);                                 // | - x - |
        }
        else {
            Tab[k][m - 1] = mask[k][m - 1];
        }
    }

    if (k + 1 <= max_l && m - 1 >= 0) {
        if (mask[k + 1][m - 1] == '-' && Tab[k + 1][m - 1] == '-') {                        //  +1 / -1

            Tab[k + 1][m - 1] = ' ';                                                        // | - - - |
            mask[k + 1][m - 1] = ' ';                                                       // | - o - |
            tiretAutour(mask, Tab, max_c, max_l, k + 1, m - 1);                             // | - - x |
        }
        else {
            Tab[k + 1][m - 1] = mask[k + 1][m - 1];
        }
    }

    if (k + 1 <= max_l) {
        if (mask[k + 1][m] == '-' && Tab[k + 1][m] == '-') {                                //  +1 / 0

            Tab[k + 1][m] = ' ';                                                            // | - - - |
            mask[k + 1][m] = ' ';                                                           // | - o x |
            tiretAutour(mask, Tab, max_c, max_l, k + 1, m);                                 // | - - - |
        }
        else {
            Tab[k + 1][m] = mask[k + 1][m];
        }
    }

    if (k + 1 <= max_l && m + 1 <= max_c) {
        if (mask[k + 1][m + 1] == '-' && Tab[k + 1][m + 1] == '-') {                        //  +1 / +1

            Tab[k + 1][m + 1] = ' ';                                                        // | - - x |
            mask[k + 1][m + 1] = ' ';                                                       // | - o - |
            tiretAutour(mask, Tab, max_c, max_l, k + 1, m + 1);                             // | - - - |
        }
        else {
            Tab[k + 1][m + 1] = mask[k + 1][m + 1];
        }
    }

    if (m + 1 <= max_c) {
        if (mask[k][m + 1] == '-' && Tab[k][m + 1] == '-') {                                //  0 / +1

            Tab[k][m + 1] = ' ';                                                            // | - x - |
            mask[k][m + 1] = ' ';                                                           // | - o - |
            tiretAutour(mask, Tab, max_c, max_l, k, m + 1);                                 // | - - - |
        }
        else {
            Tab[k][m + 1] = mask[k][m + 1];
        }
    }
}


// Lorsque bombCounter == 0 (cf. nbBombesRestantes.hpp), ce sous-programme vérifie si :
// L'emplacement des bombes est correct : Dans ce cas, l'utilisateur gagne la partie.
// L'emplacement des bombes est incorrect : Dans ce cas, l'utilisateur perd la partie, et comprend ou il aurait pu les poser.

void finPartie(char Tab[16][30], char mask[16][30], int &max_c, int &max_l) {

    int bombCounter;
    short perdu = 0;                                                 // Initialisé de base sur false (Bah oui, l'utilisateur ne perd pas directement en lançant le jeu !!)

    for (int i = 0; i < max_c; i++) {

        for (int j = 0; j < max_l; j++) {

            if (Tab[i][j] == bombe) {                                   // Si l'utilisateur ne pose pas de drapeau sur un emplacement qui contient une bombe :
                perdu += 1;                                             // Il perd
                Tab[i][j] = 'B';                                        // On affiche le contenu de la case avec le paramètre correspondant (ci-dessous)
            }

            else if (mask[i][j] != bombe && Tab[i][j] == 'X') {         // Si l'utilisateur pose un drapeau sur un emplacement qui ne contient pas de bombe :
                perdu += 1;                                             // Il perd
                Tab[i][j] = '/';                                        // On affiche le contenu de la case avec le paramètre correspondant (ci-dessous)
            }

            else if (mask[i][j] == bombe && Tab[i][j] == 'X') {         // Si l'utilisateur pose un drapeau sur un emplacement qui contient une bombe :
                Tab[i][j] = 'O';                                        // L'issue du jeu n'est pas déterminable (il n'a ni gagné, ni perdu)
            }                                                           // On affiche le contenu de la case avec le paramètre correspondant (ci-dessous)
        }
    }
    
    if (perdu > 0) {    // Séquence quand l'utilisateur a perdu                                                    
        affGrille(Tab, max_c, max_l);
        cout << endl;
        cout << "Dommage, vous avez perdu !" << endl;
        bombCounter = -1;

        cout << endl;  // Paramètres de fin de jeu :
        // On affiche les bombes et drapeaux de différentes manières en fonction des actions du joueur
        cout << "-> B = Bombes sans drapeau" << endl;               
        cout << "-> O = Drapeau valide" << endl;                    
        cout << "-> / = Drapeau invalide" << endl;                  
        cout << endl;

        sleep(5);                                                                        // Cool down de 5s.
        abort();                                                                            // Fin du jeu
    }
    else if (perdu == 0) {

        affGrille(Tab, max_c, max_l); // Séquence quand l'utilisateur a gagné  
        cout << endl;
        cout << "Bravo !" << endl;
        cout << "Merci d'avoir joue au demineur ! \n";
        
        sleep(5);                                                                        // Cool down de 5s.
        abort();                                                                            // Fin du jeu
    }
}


// Ce sous-programme va compter le nombre de bombes que le tableau à généré. Puis il va aussi se charger de les soustraire

void nbBombesRestantes(char mask[16][30], char Tab[16][30], int max_c, int max_l) {

    bombCounter = 0;                                                            // On donne 0 dans la fonction cette fois-ci

    for (int k = 0; k < max_l; k++) {

        for (int m = 0; m < max_c; m++) {

            if (Tab[k][m] == bombe) {                                           // Si l'emplacement contient une bombe :
                bombCounter++;                                                  // +1
            }

            else if (Tab[k][m] == 'X' && mask[k][m] == bombe) {                 // Si l'emplacement du tableau contient un drapeau et que l'emplacement du masque contient une bombe :
                continue;                                                       // Ne rien faire
            }

            else if (Tab[k][m] == 'X') {                                        // Si l'emplacement contient un drapeau :
                bombCounter--;                                                  // -1
            }
        }
    }
    cout << endl; // Affichage du nombre de bombes restantes
    cout << "Il reste " << bombCounter << " bombes restantes" << endl;          
    cout << endl; 

    if (bombCounter == 0) {                                                     // Dès que le nombre de bombes passe à 0 :
        finPartie(Tab, mask, max_c, max_l);                                     // On vérifie les drapeaux et annonce le résultat final de la partie
    }
}


// La partie intéraction est la partie la plus importante (avec le main...). Sans elle, pas de communication avec le tableau, donc inutilisable par un utilisateur.
// C'est ce sous-programme qui donne la possibilité de modifier des données du tableau pour déterminer une issue

void interaction(char mask[16][30], char Tab[16][30], int &max_c, int &max_l) {

    char x, y;                                                          // x / y = Valeurs entrées | (de 1 à 30) && (de A à P)
    char t, drap;                                                       //
    string s = "";                                                      // t = variable temporaire pour interchanger les valeurs de x et y
//                                                                      // drap = Variable du drapeau                                                    
    cout << "Chiffre / Lettre : ";
    cin >> x; 
    cin >> y;                                                                       
//                                                                      
    cout << "Drapeau ? (y/n) : ";
    cin >> drap;                                                           

    cout << endl;

        // Section "Chiffre / Lettre"
        if ((x >= 49 && x <= 57) && (y >= 65 && y <= 73)) {                               // Limite et disposition des valeurs             
            y = y - 65;                                                                   //
            x = x - 49;                                                                   // 1er if : 1A = # (1 - 9) & (A - I) #               
        }                                                                                 // 2e if : 1a = # (1 - 9) & (a - i) #
        //                                                                                // 3e if : 1A = # (A - I) & (1 - 9) #
        else if ((x >= 49 && x <= 57) && (y >= 97 && y <= 105)) {                         // 4e if : 1A = # (a - i) & (1 - 9) #                                                    
            y = y - 97;                                                                   //
            x = x - 49;                                                                   // else : "Erreur !"
        } 

        else if ((x >= 65 && x <= 73) && (y >= 49 && y <= 57)) {                                            
            y = y - 49;                                                                 // Les soustractions ici sont utlisées pour se placer par défaut :                   
            x = x - 65;                                                                 // Sur (0,0) si : x = Vmin & y = Vmin   
            t = y;
            y = x;                                                                      // On interchange les valeurs avec la variable t
            x = t;  
        }  

        else if ((x >= 97 && x <= 105) && (y >= 49 && y <= 57)) {                                                                               
            y = y - 49;                                                                 
            x = x - 97; 
            t = y;
            y = x;                                                                      // On interchange les valeurs avec la variable t
            x = t;                                                                  
        }                                                                                

        else {
            cout << "Merci de respecter l'ordre Chiffre / Lettre !" << endl;
            cout << "Veuillez reessayer !" << endl;
            cout << endl;
            sleep(10);
            termkit::clear();
            graff();
            interaction(mask, Tab, max_c, max_l);                                // Ré-éffectue interaction()
        }
    
    if (drap == 'y' || drap == 'Y') {

        // Section "Drapeau"                                                    // Ces sous-sections sont pré-faites
        if (Tab[y][x] == '-' || Tab[y][x] == bombe) {                           // 
            Tab[y][x] = 'X';                                                    // En fonction de ce l'emplacement a déjà :
        }                                                                       // Les conditions remplacent simplement le caractère attribué par le nouveau
        else if (mask[y][x] == bombe && Tab[y][x] == 'X') {                     // En fonction de ce l'utilsateur demande dans le drapeau (y / n)
            Tab[y][x] = bombe;                                                  //
        }                                                                       // Exemple : ('-' => 'X')
        else if (Tab[y][x] == 'X') {
            Tab[y][x] = '-';
        }
    }

    else if (mask[y][x] == bombe) {
        finPartie(Tab, mask, max_c, max_l);
    }

    else if (mask[y][x] == '-') {
        Tab[y][x] = ' ';
        tiretAutour(mask, Tab, max_c, max_l, y, x);
    }

    else {
        Tab[y][x] = mask[y][x];
    }
    affGrille(Tab, max_c, max_l);
}


void numBombes(char mask[16][30], int max_c, int max_l)
{
    for (int k = 0; k < max_l; k++)
    {
        for (int m = 0; m < max_c; m++)
        {

            if (mask[k][m] == bombe)                                                // Exemple du fonctionnement :
            {
                if (k - 1 >= 0 && m + 1 <= max_c)                                   // | - - - - - - - |
                {                                                                   // | - 1 1 1 - - - |
                    if (mask[k - 1][m + 1] == '-')                                  // | - 1 & 2 1 1 - |
                    {                                                               // | - 1 2 3 & 1 - |
                        mask[k - 1][m + 1] = '1';                                   // | - - 1 & 2 1 - |
                    }                                                               // | - - 1 1 1 - - |
                    else if (mask[k - 1][m + 1] != bombe)                           // | - - - - - - - |
                    {
                        mask[k - 1][m + 1] += 1;
                    }
                }

                if (k - 1 >= 0)                                                     // Comme dans tiretAutour, chaque partie
                {                                                                   // de fonction s'occupe d'une coordonée
                    if (mask[k - 1][m] == '-')                                      // autour de l'emplacement choisi par 
                    {                                                               // l'utilisateur
                        mask[k - 1][m] = '1';
                    }
                    else if (mask[k - 1][m] != bombe)
                    {
                        mask[k - 1][m] += 1;
                    }
                }

                if (k - 1 >= 0 && m - 1 >= 0)
                {
                    if (mask[k - 1][m - 1] == '-')
                    {
                        mask[k - 1][m - 1] = '1';
                    }
                    else if (mask[k - 1][m - 1] != bombe)
                    {
                        mask[k - 1][m - 1] += 1;
                    }
                }

                if (m - 1 >= 0)
                {
                    if (mask[k][m - 1] == '-')
                    {
                        mask[k][m - 1] = '1';
                    }
                    else if (mask[k][m - 1] != bombe)
                    {
                        mask[k][m - 1] += 1;
                    }
                }

                if (k + 1 <= max_l && m - 1 >= 0)
                {
                    if (mask[k + 1][m - 1] == '-')
                    {
                        mask[k + 1][m - 1] = '1';
                    }
                    else if (mask[k + 1][m - 1] != bombe)
                    {
                        mask[k + 1][m - 1] += 1;
                    }
                }

                if (k + 1 <= max_l)
                {
                    if (mask[k + 1][m] == '-')
                    {
                        mask[k + 1][m] = '1';
                    }
                    else if (mask[k + 1][m] != bombe)
                    {
                        mask[k + 1][m] += 1;
                    }
                }

                if (k + 1 <= max_l && m + 1 <= max_c)
                {
                    if (mask[k + 1][m + 1] == '-')
                    {
                        mask[k + 1][m + 1] = '1';
                    }
                    else if (mask[k + 1][m + 1] != bombe)
                    {
                        mask[k + 1][m + 1] += 1;
                    }
                }

                if (m + 1 <= max_c)
                {
                    if (mask[k][m + 1] == '-')
                    {
                        mask[k][m + 1] = '1';
                    }
                    else if (mask[k][m + 1] != bombe)
                    {
                        mask[k][m + 1] += 1;
                    }
                }
            }
        }
    }
}

int main()
{

    char Tab[16][30];
    char mask[16][30];
    int max_c, max_l;

    debut();
    graff();
    grille(Tab, max_c, max_l);
    init(Tab, max_c, max_l);

    affGrille(Tab, max_c, max_l);
    cout << endl;
    
    bombes(Tab, max_c, max_l);

    // ------- //

    for (int k = 0; k < max_l; k++) {

        for (int m = 0; m < max_c; m++) {

            mask[k][m] = Tab[k][m];
        }
    }

    numBombes(mask, max_c, max_l);
    //                                                          // DEBUG:
    //    for (int k = 0; k < max_l; k++)                       // Sert pour visionner les bombes, et le nombre de bombes
    //    {                                                     // autour des bombes correspondantes
    //        for (int m = 0; m < max_c; m++)
    //        {
    //            cout << mask[k][m] << " ";                    // Affichage du tableau masqué (mask[][])
    //        }                                                 //
    //        cout << endl;                                     // Saut de ligne lors du changement de lettre
    //    }
    //    cout << endl;
    //

    cout << termkit::center_line("Il reste 10 bombes restantes") << endl; 
    cout << endl;
    while (bombCounter != 0) {
        interaction(mask, Tab, max_c, max_l);
        if (bombCounter == 0) {
            break;
        }
        nbBombesRestantes(mask, Tab, max_c, max_l);
    }
}
