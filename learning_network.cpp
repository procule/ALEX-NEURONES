#include <cstdlib>
#include <iostream>
#include <string.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "learning_network.h"

FILE * learning_file;

double sigmoide(double donnee)
{
       return 1/(1+exp(-(donnee)));       
}


int create_network(RESEAU *network, const int nb_neurone_par_couche[], const int nb_couche, const int nb_entrees)
{
    int i,j,k;
    network->nmb_couche = nb_couche-1;
    network->tau = 0.1;

    //Alloue la mémoire nécessaire aux couches selon le nombre désiré
    network->couche = (COUCHE*)malloc((network->nmb_couche+2) * sizeof(COUCHE));
    //Crée le bon nombre de neurone (assigne la valeurs à nmb_couche)
       for(i=0;i<=network->nmb_couche;i++)
       {
           network->couche[i].nmb_neurones = nb_neurone_par_couche[i];
           //assigne le nombre d'entré au réseau
        if(i==0){
           network->couche[i].nmb_input = nb_neurone_par_couche[i];
           }
        else{
             network->couche[i].nmb_input = nb_entrees;           
        }
       }


    //Initialisation des poids et des momentums
    for(i=0;i<=network->nmb_couche;i++)
    {
    network->couche[i].neurone = (NEURONE*)malloc((network->couche[i].nmb_neurones) * sizeof(NEURONE));                                    
        for(j=0;j<network->couche[i].nmb_neurones;j++)
        {      
            network->couche[i].neurone[j].seuil_activation = (double)((rand() / (RAND_MAX + 1.0)) * 4.0) - 2.0;
                 network->couche[i].neurone[j].momentum = (double*)malloc(network->couche[i].nmb_input * sizeof(double));
                 network->couche[i].neurone[j].poids = (double*)malloc(network->couche[i].nmb_input * sizeof(double));                          
            for(k=0;k<network->couche[i].nmb_input;k++)
            {                                                                     
                network->couche[i].neurone[j].poids[k] = (double)((rand() / (RAND_MAX + 1.0)) * 4.0) - 2.0;
                network->couche[i].neurone[j].momentum[k] = 0.0;
            }
        }
    }
    return 1;
}

int learning_network(RESEAU *network, const double *num , const double *out, const double learning_rate, int iteration)
{
    int i,j,k,random;
    double entrees[2];
    double sorties[1];
     network->tau = learning_rate;
    
    srand(time(NULL));
   
    std::string nom_new_fichier = "test.txt";
    std::ofstream fichier(nom_new_fichier.c_str(), std::ios::trunc);
    if ( !fichier ){
        std::cerr << "Erreur de creation du fichier" << std::endl;
        system("PAUSE");
        return -1;
    } 
    learning_file = fopen("learning_file.txt","w");
   
/*****************************************************************************/

    for(i=0;i<iteration;i++)
    {   
        fprintf(learning_file,"\n/**********************************************************************/\n",i);
        fprintf(learning_file,"/**************************ITERATION %i**********************************/\n",i);
        fprintf(learning_file,"*************************************************************************/\n\n",i);
   
       
       
       
       
       
       
        random = rand()%4;        
 /****************************************************************************************************************/      
       
        for(j=0;j<2;j++)
        {
            entrees[j] = num[(random*2)+j];
        }
//        for(j=0;j<1;j++)
//        {
            sorties[0] = out[random];
//        }

/*****************************************************************************************************************/






    fprintf(learning_file,"Random = %i -->  %f AND %f = %f\n",random,entrees[0],entrees[1],sorties[0]);
    //Calcul l'entrée et la sortie des couches
    in_out(network, entrees);
    //Calcul les delta de chaque couche
    calc_delta(network, sorties); 
    //Calcul des delta_poids et des nouveaux poids
    maj_poids(network, entrees);
    fprintf(learning_file,"%f AND %f = %f\n",entrees[0],entrees[1],sorties[0]);
    fprintf(learning_file,"      L'activation:%f\n",network->couche[2].neurone[0].activation);
    fprintf(learning_file,"Seuil d'activation:%f\n",network->couche[2].neurone[0].seuil_activation);
    if(network->couche[2].neurone[0].activation>=network->couche[2].neurone[0].seuil_activation)
    {
        fprintf(learning_file,"Exité\n",network->couche[2].neurone[0].seuil_activation);
    }
    else
    {
        fprintf(learning_file,"OFF\n",network->couche[2].neurone[0].seuil_activation);    
    }
    fichier << entrees[0] << " ";
    fichier << (double)entrees[1] << " ";
    fichier << "-> " << sorties[0] << " ";   
/*  fichier << entrees[2] << " ";
    fichier << entrees[3] << " ";
    fichier << entrees[4] << " ";
    fichier << entrees[5] << " ";
    fichier << entrees[6] << " ";
*/    

//Itération pour afficher un nombre d'entré de taille différente
//Itération pour afficher un nombre de sortie de taille différente


      fichier << "|input :" << " ";
      fichier << network->couche[0].neurone[0].input << " ";
    fichier << network->couche[0].neurone[1].input << " ";
      fichier << "|input sous-couche :" << " ";    
    fichier << network->couche[1].neurone[0].input << " ";
    fichier << network->couche[1].neurone[1].input << " ";
      fichier << "|input sortie :" << " ";       
    fichier << network->couche[2].neurone[0].input << " ";
    fichier << "|delta :" << " ";
    fichier << network->couche[0].neurone[0].delta << " ";
    fichier << network->couche[0].neurone[1].delta << " ";
    fichier << network->couche[1].neurone[0].delta << " ";
    fichier << network->couche[1].neurone[1].delta << " ";
    fichier << network->couche[2].neurone[0].delta << " ";
    fichier << "|seuil_activation :" << " ";
    fichier << network->couche[0].neurone[0].seuil_activation << " ";
    fichier << network->couche[0].neurone[1].seuil_activation << " ";
    fichier << network->couche[1].neurone[0].seuil_activation << " ";
    fichier << network->couche[1].neurone[1].seuil_activation << " ";
    fichier << network->couche[2].neurone[0].seuil_activation << " ";
      fichier << "|poids :" << " ";
    fichier << network->couche[0].neurone[0].poids[0] << " ";
    fichier << network->couche[0].neurone[0].poids[1] << " ";
    fichier << network->couche[0].neurone[1].poids[0] << " ";
    fichier << network->couche[0].neurone[1].poids[1] << " ";
    fichier << network->couche[1].neurone[0].poids[0] << " ";
    fichier << network->couche[1].neurone[0].poids[1] << " ";
    fichier << network->couche[1].neurone[1].poids[0] << " ";
    fichier << network->couche[1].neurone[1].poids[1] << " ";
    fichier << network->couche[2].neurone[0].poids[0] << " ";
    fichier << network->couche[2].neurone[0].poids[1] << " ";
          fichier << "|activation :" << " ";
    fichier << network->couche[0].neurone[0].activation << " ";
    fichier << network->couche[0].neurone[1].activation << " ";
    fichier << network->couche[1].neurone[0].activation << " ";
    fichier << network->couche[1].neurone[1].activation << " ";
    fichier << network->couche[2].neurone[0].activation << " ";
    
    fichier << "| " << entrees[0] << " ";
    fichier << entrees[1] << " ";
    fichier << "-> " << sorties[0] << " ";
    fichier << "\n";
    }
    fichier << std::endl;
    fichier.close();
    printf("success!? %f",network->couche[2].neurone[0].activation);
    system("PAUSE");
    
    //Libère la mémoire allouée lors de la création du réseau
    for(i=0;i<network->nmb_couche+1;i++)
    {
       for(j=0;j<network->couche[i].nmb_neurones;j++)
       {
           free(network->couche[i].neurone[j].momentum);
           free(network->couche[i].neurone[j].poids);                              
       }
       free(network->couche[i].neurone);
    }
    
    free(network->couche); 

    return EXIT_SUCCESS;
}


//Fonction de calcul pour les entrées et sorties des neurones dans les couches secondaires du réseau
int in_out(RESEAU *network, double *entrees)
{
    int i,j,k;  
    fprintf(learning_file,"\n                    /*****CALCUL DE L'ACTIVATION*****/\n");
    for(k=0;k<=network->nmb_couche;k++)
    {
             //Calcul de l'activation pour la première couche avec la table des entrées
             if(k==0)
             {
                    for(i=0;i<network->couche[k].nmb_neurones;i++)
                    {
                       //Sommation de toutes les entrées*poids
                       network->couche[k].neurone[i].input = 0.0;
                       fprintf(learning_file,"Couche%i\n\tNeuronne %i,\n",k,i);
                       for(j=0;j<network->couche[k].nmb_input;j++)
                       {
                            network->couche[k].neurone[i].input = (network->couche[k].neurone[i].poids[j] * entrees[j]);
                            fprintf(learning_file,"\t\tsommation(du poid_%i*entree_%i) : %f\n",j,j,network->couche[k].neurone[i].input);
                       }                      
                       network->couche[k].neurone[i].input += network->couche[k].neurone[i].seuil_activation;
                       network->couche[k].neurone[i].activation = sigmoide(network->couche[k].neurone[i].input);
                       fprintf(learning_file,"      L'activation:%f\n",network->couche[k].neurone[i].activation);
                       fprintf(learning_file,"Seuil d'activation:%f\n",network->couche[k].neurone[i].seuil_activation);
                       if(network->couche[k].neurone[i].activation>=network->couche[k].neurone[i].seuil_activation)
                       {
                        fprintf(learning_file,"Exité\n",network->couche[k].neurone[i].seuil_activation);
                       }
                       else{
                        fprintf(learning_file,"OFF\n",network->couche[k].neurone[i].seuil_activation);    
                            }
                    }  
             }          
             //Calcul pour les couches suivantes
             else
             {
                    for(i=0;i<network->couche[k].nmb_neurones;i++)
                    {
                    //Sommation de toutes les entrées*poids
                    network->couche[k].neurone[i].input = 0.0;
                       fprintf(learning_file,"Couche%i\n\tNeuronne %i,\n",k,i);
                        for(j=0;j<network->couche[k].nmb_input;j++)
                        {
                            network->couche[k].neurone[i].input += (network->couche[k].neurone[i].poids[j] * network->couche[k-1].neurone[j].activation);
                            fprintf(learning_file,"\t\tsommation du poid_%i*entree_%i) : %f\n",k,i,j,j,network->couche[k].neurone[i].input);             
                        }
                        network->couche[k].neurone[i].input += network->couche[k].neurone[i].seuil_activation;
                        network->couche[k].neurone[i].activation = sigmoide(network->couche[k].neurone[i].input);
                       fprintf(learning_file,"L'activation:%f\n",network->couche[k].neurone[i].activation);
                    }
             }  
        }    
        return 1;
}
int calc_delta(RESEAU *network, double *sorties)
{
    int i,j,k;
    fprintf(learning_file,"\n                    /*****CALCUL DU DELTA*****/\n");    
    for(i=network->nmb_couche;i>-1;i--)
    {     
        //Calcul du delta pour la dernière couche avec la table de sorties
        if(i==network->nmb_couche)
        {                                                    
              for(j=0;j<network->couche[i].nmb_neurones;j++)
              {                                
                    network->couche[i].neurone[j].delta = (sorties[j] - network->couche[i].neurone[j].activation)*(network->couche[i].neurone[j].activation)*(1-network->couche[i].neurone[j].activation);
                    fprintf(learning_file,"Couche%i\n\tNeurone%i: delta=%f\n",i,j,network->couche[i].neurone[j].delta);
              }
        }
        //Calcul du delta pour les couches précédantes
        else
        {
              for(j=0;j<network->couche[i].nmb_neurones;j++)
              {    
                    network->couche[i].neurone[j].delta = 0.0;
                    for(k=0;k<network->couche[i+1].nmb_neurones;k++)
                    {
                          network->couche[i].neurone[j].delta = network->couche[i].neurone[j].delta + (network->couche[i+1].neurone[k].delta * network->couche[i+1].neurone[k].poids[j]);
                    fprintf(learning_file,"Couche%i\n\tNeurone%i: delta=%f\n",i,j,network->couche[i].neurone[j].delta);
                    }                  
                    network->couche[i].neurone[j].delta = (network->couche[i].neurone[j].delta) * (network->couche[i].neurone[j].activation)*(1-network->couche[i].neurone[j].activation);
                    fprintf(learning_file,"\t\tDELTA: %f\n",network->couche[i].neurone[j].delta); 
              }  
        }
    }
    return 1;
}

/***************Fonction qui met à jour les poids des connections**********************/

int maj_poids(RESEAU *network, double *entrees)
{
        int i,j,k;
        double delta_w;
        fprintf(learning_file,"\n                    /*****MISE A JOUR DES POIDS*****/\n");
        for(k=0;k<network->nmb_couche+1;k++)
        {                               
        fprintf(learning_file,"Couche%i\n",k);
             //Calcul pour la première couche avec la table des entrées
             if(k==0)
             {
                   for(i=0;i<network->couche[k].nmb_neurones;i++)
                   {
                       for(j=0;j<network->couche[k].nmb_input;j++)
                       {
                          delta_w = (network->tau * network->couche[k].neurone[i].delta * entrees[j]);
                          network->couche[k].neurone[i].momentum[j] = 0.5 * delta_w;    
                          fprintf(learning_file,"\tNeurone%i \n\t\tinput%i\n",i,j);
                          fprintf(learning_file,"\t\t\tdelta_w+w_old = w_new %f + %f = ", delta_w,network->couche[k].neurone[i].poids[j]);
                          network->couche[k].neurone[i].poids[j] = network->couche[k].neurone[i].poids[j] + delta_w; //+ network->couche[k].neurone[i].momentum[j];
                          fprintf(learning_file,"%f\n",network->couche[k].neurone[i].poids[j]);
                          fprintf(learning_file,"\t\t\tmomentum (0.5 * delta_w) = %f\n",network->couche[k].neurone[i].momentum[j]);

                       }              
                   }  
             }
             //Calcul pour les couches suivantes
             else
             {
                  for(i=0;i<network->couche[k].nmb_neurones;i++)
                  {
                       for(j=0;j<network->couche[k].nmb_input;j++)
                       {                          
                           delta_w = (network->tau * network->couche[k].neurone[i].delta) * network->couche[k].neurone[i].input;
                           network->couche[k].neurone[i].momentum[j] = 0.5 * delta_w;
                           fprintf(learning_file,"\tNeurone%i, \n\t\tinput%i\n",i,j);
                           fprintf(learning_file,"\t\t\tdelta_w+w_old = w_new%f + %f = ", delta_w, network->couche[k].neurone[i].poids[j]);
                           network->couche[k].neurone[i].poids[j] = network->couche[k].neurone[i].poids[j] + delta_w; //+ network->couche[k].neurone[i].momentum[j];
                           fprintf(learning_file,"%f\n",network->couche[k].neurone[i].poids[j]); 
                           fprintf(learning_file,"\t\t\tmomentum (0.5 * delta_w) = %f\n",network->couche[k].neurone[i].momentum[j]);                       
                       }
                  }
             }
       }
       return 1;
}


