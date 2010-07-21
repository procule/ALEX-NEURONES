/******************************************************************************/
/* learning_network.h                                                         */
/* Auteur: Alexandre Proulx & Alexandre Gaudet                                */
/* Prototype des fonctions nécessaire à l'apprentissage du réseau MLP         */
/* "in_out" pour le calcul des activations                                    */ 
/* calc_delta pour le calcul des Deltas pour la rétropropagation de l'erreur  */
/* maj_poids pour mettre à jour les poids                                     */
/* learning_network est la fonction MASTER qui appel les autres               */
/*............................................................................*/

#ifndef LEARNING_NETWORK_H
#define LEARNING_NETWORK_H

typedef struct NEURONE {
        double input;
        double activation;
        double seuil_activation;
        double delta;
        double *momentum;
        double *poids;
        }NEURONE;
typedef struct COUCHE {
        int nmb_input;
        int nmb_neurones;
        NEURONE *neurone;
        }COUCHE;
typedef struct RESEAU {
        int nmb_couche;
        double tau;
        COUCHE *couche;
        }RESEAU;


int in_out(RESEAU *network, double *entrees);
int calc_delta(RESEAU *network, double *sorties);
int maj_poids(RESEAU *network, double *entrees);
int create_network(RESEAU *network, const int nb_neurone_par_couche[], const int nb_couche, const int nb_entrees);
int learning_network(RESEAU *network, const double *num , const double *out,const double learning_rate, int iteration);

#endif
