#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <iterator>

// un magnifique fichier source

using namespace std;

// Foncteur qui effectue un chiffrement par decalage
class ChiffrementSubst{

public:

  // Constructeur prenant le nom fichier contenant les substitutions a utiliser
  ChiffrementSubst(const string& nomFichier)
  {
    ifstream fichier(nomFichier.c_str());
    string ligne;

    if(fichier)
    {
      while(getline(fichier,ligne))
      {
        m_tabSub[ligne[0]] = ligne[2];
      }

    }
    else
    {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
  }

  // L'operateur() qui effectue le chiffrement
  char operator()(char lettre)
  {
    // On transforme uniquement les caracteres majuscules
    if(isupper(lettre))
    {
      // On applique la substitution
      lettre = m_tabSub[lettre];
    }
    return lettre;
  }

private:

  // table de substitution
  map<char, char> m_tabSub;
};


int main()
{

  // Le message a crypter
  string texte("BIENVENUE SUR LE MOOC C++ D'OCR !!");

  // Demande de la cle a l'utilisateur
  cout << "Quel fichier contenant la cle voulez-vous utiliser ? ";
  string nomFichier;
  cin >> nomFichier;

  // Creation du foncteur
  ChiffrementSubst foncteur(nomFichier);

  // Chaine de caracteres pour le message crypter
  string texte_crypte;

    // Un iterateur permettant l'insertion a la fin
  back_insert_iterator<string> it(texte_crypte);

  // On applique le foncteur sur le vector pour crypter le message en utilisant 'transform'
  transform(texte.begin(), texte.end(), it, foncteur);

  // On copie le message dans cout en utilisant l'algorithme 'copy'
  copy(texte_crypte.begin(), texte_crypte.end(), ostream_iterator<char>(cout, ", "));
  cout << endl;

  return 0;
}

