#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <utility>

class Etudiant {
public:

    Etudiant(const std::string &p_nom, int p_points) : m_nom(p_nom), m_points(p_points) {};

    // Ici l'opérateur de comparaison est membre d'Étudiant.  Il n'a pas besoin d'être "friendzoné".
    bool operator<(const Etudiant &rhs) const;

    // Ces déclarations sont obligatoires pour 2 et 3 si on veut garder les attributs private

    friend bool operator<(const Etudiant &lhs, const Etudiant &rhs);

    friend class Comparateur;

//private:
    std::string m_nom;
    int m_points;
};

/**
 * Opérateur de comparaison surchargé:  notez qu'il doit d'abord être déclaré friend dans la classe Étudiant
 * puisqu'il utilise des attributs qui sont donc privés.
 * @param lhs Opérande
 * @param rhs Opérande
 * @return true si lhs a moins de points que rhs
 */
bool operator<(const Etudiant &lhs, const Etudiant &rhs) {
    return lhs.m_points < rhs.m_points;
}

/**
 * Objet-fonction comparateur: un objet fonction est une classe qui surcharge l'opérateur () qui est l'opérateur "appel
 * de fonction".  On peut donc créer une instance de cette classe, et appeler une instance exactement comme si c'était
 * une fonction.
 *
 * Notez que pour accéder aux attributs d'Étudiant, cette classe aussi doit être déclarée friend dans Étudiant.
 */
class Comparateur {
public:

    /**
     * Surcharge de l'opérateur appel de fonction.
     * @param lhs Opérande
     * @param rhs Opérande
     * @return true si lhs a moins de points que rhs
     */
    bool operator()(const Etudiant &lhs, const Etudiant &rhs) {
        return lhs.m_points < rhs.m_points;
    }
};

bool Etudiant::operator<(const Etudiant &rhs) const {
    return m_points < rhs.m_points;
}

int
main() {
    std::array<Etudiant, 8> resultats{
            {
                    {"Albert", 3},
                    {"Ben", 5},
                    {"Christine", 2},
                    {"Dan", 8},
                    {"Enchilada", 4},
                    {"Francis", 1},
                    {"Greg", 3},
                    {"Hagrid", 5}
            }};

    /*****************************************************
     * Solution 1: lambda expression
     * Qu'arrive-t-il si on remet les attributs private???
     *****************************************************/

    const auto theBest{
            std::max_element(resultats.begin(), resultats.end(),
                             [](const Etudiant &lhs, const Etudiant &rhs) { return lhs.m_points < rhs.m_points; })
    };

    std::cout << theBest->m_nom
              << " est le meilleur étudiant par la solution 1\n"; // on doit déréférencer l'itarateur pour avoir accès à l'élément

    /******************************************************
     * Solution 2: Objet fonction
     * est-il utilisable si les attributs sont private?
     * À quelle condition?
     ******************************************************/

    Comparateur monComparateur;

    const auto meilleur{
            std::max_element(resultats.begin(), resultats.end(), monComparateur)
    };

    std::cout << meilleur->m_nom << " est le meilleur étudiant par la solution 2\n";

    /*****************************************************************
     * Solution 3: Surcharge de l'opérateur < en fonction libre
     * Cette solution fonctionne-t-elle si les attributs sont privés?
     *****************************************************************/

    const auto u_r_a_star{
            std::max_element(resultats.begin(), resultats.end(), operator<)
    };

    std::cout << u_r_a_star->m_nom << " est le meilleur étudiant par la solution 3\n";

    /******************************************************************************
     * Solution 4: Utiliser la surcharge de l'opérateur < comme méthode d'Étudiant.
     * Cette solution fonctionne-t-elle si les attributs sont privés?
     * Est-ce qu'elle nécessite une déclaration friend?
     *******************************************************************************/

    const auto da_man{
            std::max_element(resultats.begin(), resultats.end(), std::mem_fn(&Etudiant::operator<))
    };

    std::cout << da_man->m_nom << " est le meilleur étudiant par la solution 4\n";

    return 0;
}