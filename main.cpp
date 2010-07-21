/*****************************************************************************/
/* main.cpp                                                                  */
/* Auteur: Alexandre Proulx & Alexandre Gaudet                               */
/* fonction main qui gère l'entrée et la sortie des données et fait le lien  */
/* avec les autres fonctions                                                 */
/*...........................................................................*/

//#include "learning_network.h"
#include "mfc2input.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#define ITERATION 100
#define LEARNING_RATE 0.1

using namespace std;

int main(void)
{

    RESEAU net;
    COUCHE couche;
    NEURONE neurone;
    RESEAU *network;
    network = &net;
    network->couche = &couche;
    network->couche->neurone = &neurone;

    int nb_neurone_par_couche[3] = {2,2,1};
    double num[16] = {
    0.0,0.0,    1.0,0.0,    0.0,1.0,    1.0,1.0,    1.0,1.0,    1.0,1.0,    1.0,1.0,    1.0,1.0,    };
    double out[8] = {    0.0,    0.0,    0.0,    1.0,    1.0,    1.0,    1.0,    1.0,    };  

    create_txt_convert();
    create_network(network, nb_neurone_par_couche,sizeof(nb_neurone_par_couche)/sizeof(int), 2);
    learning_network(network, num, out,LEARNING_RATE, ITERATION);
   
}
