/******************************************************************************/
/*moyenne.cpp                                                                 */
/* Auteur: Alexandre Proulx & Alexandre Gaudet                              */
/*fonction réduisant la grosseur du tableau pour obtenir la grosseur voulue   */
/*............................................................................*/
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <fstream>
#include "mfc2input.h"
#include <stdlib.h>// for MAX_PATH
#include <direct.h> // for getcwd

#define NBCOLONNES 26
#define POURCENTAGE_BRUIT 0.1
#define NBCOLONNES 26

std::string GetCurrentPath(void);
std::string CreateHandle(std::string fullSearchPath,HANDLE hFind, WIN32_FIND_DATA FindData);


int create_txt_convert(void)
{
	//Déclarations des variables
	FILE *fp;
	
    int i = 0;
    int j = 0;
    int nb_lignes_voulu = 60;
    int nb_lignes = 0;
    int nb_lignes_dlt = 0;
	int cpt_ligne_wave = 0;
	int cpt_lignes_dlt = 0;
	int ligne_to_dlt = 0;
	int bonne_donnee = 0;
	float valeur_min = 0;
	float valeur_max = 0;
	float valeur_bruit = 0;
    float wave[300][26];
    float wave_crap[300][26];
    HANDLE hFind;       
    WIN32_FIND_DATA FindData;	
    std::string subFolder = "test";    
    std::string searchPattern = "*.txt";
    std::string str_new_fichier = "_convert.txt";
    /**************************************************************************/
	/*Fait une recherche dans le dossier sécifié pour les fichier .txt        */
	/*........................................................................*/
	std::string current_path = GetCurrentPath();
   	std::cout<< "current path is -> " << current_path << "\n";
    std::string full_search_path = current_path + "\\" + subFolder + "\\" + searchPattern;  	
    hFind = FindFirstFile(full_search_path.c_str(), &FindData );
    if( hFind == INVALID_HANDLE_VALUE )
    {
     std::cout << "Default forder <test/> is not found\n";
     full_search_path = AskUser(current_path, hFind, &FindData);
    }
    std::cout << "\nle dossier de test est ->" << full_search_path << "\n";
    std::cout << "\nEntrez le nombre de lignes desire: ";
    std::cin >> nb_lignes_voulu;
    /**************************************************************************/
	/*Pour chaque fichier trouvé, on lit les données                          */
	/*........................................................................*/ 
    do
    {
        std::string filePath = full_search_path + "\\" + FindData.cFileName;
            std::cout << "\nle dossier de test est ->" << filePath << "\n";
        /*Ouvre un fichier de test*/
            fp = fopen (filePath.c_str(),"r" );
            //Message d'erreur pour le cas où le fichier ne peut être ouvert
            if( (fp = fopen (filePath.c_str(),"r" )) == NULL )
            {
                printf ("Le fichier ne peut etre ouvert\n");
                system("PAUSE");
                return -1; 
            }
        

        /**********************************************************************/
	    /*on scan le fichier .txt afin de créer un tableau  ..................*/
	    /*....................................................................*/
	    valeur_max = 0;
	    valeur_min = 0;
	    //On vérifie les valeurs max et min pour les puissances de chaque ligne
	    while(fscanf(fp, "%f", &wave_crap[i][j])==1)
	    {
                if(wave_crap[i][12]<valeur_min)
                {
                    valeur_min = wave_crap[i][12];
                }
                if(wave_crap[i][12]>valeur_max)
                {
                    valeur_max = wave_crap[i][12];
                }
                j++;
                if(j>NBCOLONNES-1)
    		    {
                    i++;
                    j = 0;
                }
         }
         fseek ( fp , 0 , SEEK_SET );
         
         //Avec les valeurs min et max, on trouve un seuil de bruit et donc
         //une valeur minimum considérée comme du bruit
         valeur_bruit = valeur_min+((valeur_max-valeur_min)*POURCENTAGE_BRUIT);
    
	    i = j = 0;
	    
    	while(fscanf(fp, "%f", &wave[i][j])==1)
    	{
    		j++;
    		if(j>NBCOLONNES-1)
    		{
    			//On vérifie si les données sont considérées comme un silence 
    			//jusqu'à ce qu'on trouve une bonne donnée
                if((wave[i][12] < valeur_bruit) && (bonne_donnee == 0))
    			{
                     //Si c'est un silence, on écrasera les données avec la 
                     //ligne suivante...
                     i = i;
                     j = 0;
                     printf ("Silence\n");
                }
                else
                {
                    //...sinon on change de ligne pour les nouvelles données
                    i++;
        			j = 0;
        			bonne_donnee = 1;
                }
    		}
    	}
    	//On vérifie les dernières données dans le tableau et on élimine les 
    	//lignes de silence
        while(wave[i][12] < valeur_bruit)
    	{
             i--;
             printf ("Silence\n");              
        }
    	//Fermeture du fichier
    	fclose(fp);
    	
    	nb_lignes = i;
    	printf ("%i",nb_lignes);
    	i = j = 0;
    	
        //Vérifie le nombre de ligne à deleter
    	nb_lignes_dlt = nb_lignes - nb_lignes_voulu;
        /**********************************************************************/
        /*On crée 1 tableau dynamique de grosseur désirée ....................*/
        /*....................................................................*/
        float **final;
        final = (float **)malloc(nb_lignes_voulu*sizeof(float*));
        
        for(i = 0; i < nb_lignes_voulu; i++)
        {
            final[i] = (float *)malloc(NBCOLONNES*sizeof(float));
        }
    	
    	//Vérifie le cas où il n'y aurait pas assez de données
        if(nb_lignes_dlt<0)
    	{
              printf ("Le fichier ne contient pas assez de donnees\n");
              system("PAUSE");
              return -1;
        }
        if(nb_lignes_voulu != nb_lignes)
        {
            //Fonction qui traite le tableau et renvoie un tableau tronqué
            final = moyenne_tableau(nb_lignes_voulu, nb_lignes, wave);
        }
        else
        {
            for(i=0;i<nb_lignes_voulu;i++)
            {
                  for(j=0;j<26;j++)
        	      {
        		      final[i][j] = wave[i][j];
       	          }
            }      
        }	
        /**********************************************************************/
    	/*Création du nouveau fichier pour enregistrer les données voulues ...*/
    	/*....................................................................*/
        std::string nom_new_fichier = filePath + str_new_fichier;
        
        std::ofstream fichier(nom_new_fichier.c_str(), std::ios::trunc);
        
        if ( !fichier ){
             std::cerr << "Erreur de creation du fichier" << std::endl;
             system("PAUSE");
             return -1;
        }
        //Écriture des données à partir du tableau final, cellule par cellule
        for(i=0; i<nb_lignes_voulu; i++)
        {
            for(j=0;j<26;j++)
            {
                 fichier << final[i][j] << " ";
            }
            fichier << std::endl;
        }
        fichier.close();
        /**********************************************************************/
    	/*Libération de la mémoire vive.......................................*/
    	/*....................................................................*/
        for(i = 0; i < nb_lignes_voulu; i++)
        {
            free(final[i]);
        }
        free(final);
        //Ré-initialisation des variables pour la prochaine boucle
        i = 0;
        j = 0;
        nb_lignes = 0;
        nb_lignes_dlt = 0;
    	cpt_ligne_wave = 0;
    	cpt_lignes_dlt = 0;
    	ligne_to_dlt = 0;
    	bonne_donnee = 0;
    }
    //Retour dans la boucle tant qu'un fichier est trouvé
    while( FindNextFile(hFind, &FindData) > 0 );
}
/******************************************************************************/
/*On déplace les données pour les lignes "normales" et on calcul la moyenne   */
/*une fois par "bloc de données" pour pouvoir éliminer une ligne              */
/*............................................................................*/
float ** moyenne_tableau(int nb_lignes_voulu, int nb_lignes, float tableau[][26])
{
    //Déclaration des variables
    int cpt_ligne = 0;
    int i = 0;
    int j = 0;
    //Création d'un tableau de données de la grosseur voulue au final
    float **final;
    final = (float **)malloc(nb_lignes_voulu*sizeof(float*));
    for(i = 0; i < nb_lignes_voulu; i++)
    {
        final[i] = (float *)malloc(NBCOLONNES*sizeof(float));
    }  
    //S'il faut ajouter des lignes...
    if(nb_lignes_voulu > nb_lignes)
    {
       //Déclaration des variables locales
       int nb_lignes_add = nb_lignes_voulu - nb_lignes;
       int ligne_to_add = 0;
       int cpt_lignes_add = 0;
       int nb_par_bloc = nb_lignes/nb_lignes_add;
       //Pour chaque ligne du tableau final...
       for(i=0;i<(nb_lignes_voulu-cpt_lignes_add);i++)
       {
            //...on fait la moyenne de 2 lignes du tableau original et on insert
            //le résultat à la ligne suivante (on crée une nouvelle ligne)
            if((i == ligne_to_add)&&(cpt_lignes_add<nb_lignes_add))
            {
        	     for(j=0;j<26;j++)
        	     {
        		      final[i+cpt_lignes_add][j] = tableau[i][j];
                      final[i+cpt_lignes_add+1][j] = (tableau[i][j] + tableau[i+1][j])/2;
        	     }
        	ligne_to_add = ligne_to_add + nb_par_bloc;
        	cpt_lignes_add++;
            }
            //ou on copie la ligne originale si ce n'est pas une ligne "à ajouter"
            else
            {
        	    for(j=0;j<26;j++)
        	    {
        		      final[i+cpt_lignes_add][j] = tableau[i][j];
        	    }
            }		
        }
    }
    //s'il ne faut pas ajouter de ligne, on efface les lignes pour réduire la taille du tableau
    else
    {
        //Variables locales
        int nb_lignes_dlt = nb_lignes - nb_lignes_voulu;
        int nb_par_bloc = nb_lignes/nb_lignes_dlt;
        int cpt_lignes_dlt = 0;
        int ligne_to_dlt = 0;

        //Pour chaque ligne du tableau final...
        for(i=0;i<nb_lignes_voulu;i++)
        {
             //...on fait la moyenne de 2 lignes du tableau original et on insert
             //le résultat dans le fichier final si c'est une ligne "à effacer"
             if((cpt_ligne == ligne_to_dlt)&&(cpt_lignes_dlt<nb_lignes_dlt))
             {
        	      for(j=0;j<26;j++)
        	      {
        		       final[i][j] = (tableau[cpt_ligne][j] + tableau[cpt_ligne+1][j])/2;
      	          }
        	
        	      cpt_ligne = cpt_ligne + 2;
        	      ligne_to_dlt = ligne_to_dlt + nb_par_bloc;
        	      cpt_lignes_dlt++;
             }
             //ou on copie la ligne originale si ce n'est pas une ligne "à effacer"
             else
             {
        	     for(j=0;j<26;j++)
                 {
     		           final[i][j] = tableau[cpt_ligne][j];
        	     }
        	     cpt_ligne++;
             }
         }		
    }
    //On retourne le tableau final
    return final;
} 


std::string GetCurrentPath(void)
     {
      char buf_path[_MAX_PATH];
      std::string currentpath = getcwd(buf_path, _MAX_PATH);
      return currentpath;
     }

std::string AskUser(std::string current_path, HANDLE hFind, WIN32_FIND_DATA *FindData)
    {
            std::string searchPattern = "*.txt";
            std::string SubFolder = " ";
            std::cout << "Entrez le nom du dossier contenant les fichiers a traiter: ";
            std::cin >> SubFolder;
            std::string fullSearchPath = current_path + "\\" + SubFolder + "\\" + searchPattern;
                hFind = FindFirstFile( fullSearchPath.c_str(), FindData );
                if( hFind == INVALID_HANDLE_VALUE )
                {
                std::cout << "Une erreur est survenue en cherchant le dossier\n";       
                system("PAUSE");
                return "ERREUR_CREATE_HANDLE";       
                }
            return current_path + "\\" + SubFolder + "\\";
    }
    
    
     // Specify the directory you want to manipulate.


converted?(std::string path)
{
      if ( Directory::Exists( path ) )
      {
         Console::WriteLine( "That path exists already." );
         return 0;
      }
}

create_dir(std::string path)
{
 try
 {
      // Try to create the directory.
      DirectoryInfo^ di = Directory::CreateDirectory( path );
      Console::WriteLine( "The directory was created successfully at {0}.", Directory::GetCreationTime( path ) );
 }
 catch ( Exception^ e ) 
   {
      Console::WriteLine( "The process failed: {0}", e );
   }
}

delete_dir(std::string path)
{
      // Delete the directory.
      di->Delete();
      Console::WriteLine( "The directory was deleted successfully." );
   }
   catch ( Exception^ e ) 
   {
      Console::WriteLine( "The process failed: {0}", e );
   }
}
    
    
    
    
    
    
    
    
