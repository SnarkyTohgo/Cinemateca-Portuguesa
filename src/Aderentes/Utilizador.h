#ifndef CINEMATECAPORTUGUESA_UTILIZADOR_H
#define CINEMATECAPORTUGUESA_UTILIZADOR_H

/** @defgroup Classe Utilizador
 * Atributos e métodos para a classe Utilizador
 *
 * @{
 */

#include "../Utils/utils.h"
#include "../DateTime/Date.h"

class Utilizador {
private:
    u_int nif;      /**NIF do aderente*/

public:
    /**
     * @brief Construtor default da classe Utilizador
     */
    Utilizador(){};

    /**
     * @brief Construtor da classe Aderente
     * @param nome - nome do aderente
     * @param nif - NIF do aderente
     * @param dataNasc - data de nascimento do aderente
     */
    Utilizador(u_int nif);


    /**
     * @brief Permite obter o NIF do aderente
     * @return Retorna o NIF do aderente
     */
    u_int getNif() const;


    /**
     * @brief Permite mostrar um certo aderente no ecrã
     * @param out - outstream onde queremos mostrar o aderente
     * @param aderente - aderente que queremos mostrar no ecrã
     * @return retorna a outstream
     */
    friend ostream& operator <<(ostream& out, Utilizador& utilizador);

    /**
     * @brief Permite igualar um aderente a outro - iguala todos os seus atributos
     * @param aderente - aderente ao qual estamos a igualar o outro aderente
     */
    virtual void operator =(const Utilizador& utilizador);

    /**
     * @brief Permite comparar o NIF de dois aderentes para determinar se são iguais
     * @param aderente - aderente cujo NIF queremos comparar
     * @return Retorna true caso a igualdade se verifique e false caso não se verifique
     */
    bool operator ==(const Utilizador& utilizador);

    /**
     * @brief Permite ordenar os utilizadores por ordem alfabetica
     * @param utilizador Utilizador que queremos comparar
     * @return Retorna true caso o utilzador passado como argumento tenha um nif maior
     */
    virtual bool operator <(const Utilizador& utilizador);
};


class InvalidNif : public exception {
public:
    InvalidNif(){};
    virtual const char* what() const throw() {
        return "Nif Invalido";
    }
};

/** @} */ // end of Classe Aderentes

#endif //CINEMATECAPORTUGUESA_UTILIZADOR_H
