/******************************************************************************/
/* mfc2input.h                                                                  */
/* Auteur: Alexandre Proulx & Alexandre Gaudet                                */
/* Prototype de la fonction qui reduit la grosseur du tableau                 */
/* nb_lignes_voulu : nombre de lignes du tableau final                        */
/* nb_lignes : nombre de ligne du tableau initial                             */
/* tableau[][26] : tableau original ayant X lignes de 26 cellules             */
/* renvoi un pointeur double pour le tableau final                            */
/*............................................................................*/

#ifndef MFC2INPUT_H
#define MFC2INPUT_H
#include <string>
#include <iostream>
#include <string.h>   // Required by strcpy()
#include <stdlib.h>   // Required by malloc()

using namespace std;

float ** moyenne_tableau(int nb_lignes_voulu, int nb_lignes, float tableau[][26]);
int create_txt_convert(void);

//string AskUser(string current_path, HANDLE hFind, WIN32_FIND_DATA *FindData);

string GetCurrentPath(void);
//converted(string path);
//create_dir(string path);
//delete_dir(string path);


#endif
