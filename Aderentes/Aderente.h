#ifndef SRC_ADERENTE_H
#define SRC_ADERENTE_H

/** @defgroup Classe Aderente
 * Atributos e métodos para a classe Aderente
 *
 * @{
 */

#include "../Utils/utils.h"
#include "../DateTime/Date.h"

class Aderente {
private:
    string nome;    /**Nome do aderente*/
    u_int nif;      /**NIF do aderente*/
    Date dataNasc;  /**Data de nascimento do aderente*/
    u_int anoAdesao;/**Ano de adesao do aderente*/

public:
    /**
     * @brief Construtor default da classe Aderente
     */
    Aderente(){};

    /**
     * @brief Construtor da classe Aderente
     * @param nome - nome do aderente
     * @param nif - NIF do aderente
     * @param dataNasc - data de nascimento do aderente
     * @param anoAdesao - ano de adesao do aderente
     */
    Aderente(string nome, u_int nif, Date dataNasc, u_int anoAdesao);

    /**
     * @brief Permite obter o nome do aderente
     * @return Retorna o nome do aderente
     */
    string getNome() const;

    /**
     * @brief Permite obter o NIF do aderente
     * @return Retorna o NIF do aderente
     */
    u_int getNif() const;

    /**
     * @brief Permite obter a data de nascimento do aderente
     * @return Retorna a data de nascimento do aderente
     */
    Date getDataNasc() const;

    /**
     * @brief Permite obter o ano de adesao do aderente
     * @return Retorna o ano de adesao do aderente
     */
    u_int getAnoAdesao() const;

    /**
     * @brief Permite mostrar um certo aderente no ecrã
     * @param out - outstream onde queremos mostrar o aderente
     * @param aderente - aderente que queremos mostrar no ecrã
     * @return retorna a outstream
     */
    friend ostream& operator <<(ostream& out, Aderente& aderente);

    /**
     * @brief Permite igualar um aderente a outro - iguala todos os seus atributos
     * @param aderente - aderente ao qual estamos a igualar o outro aderente
     */
    void operator =(const Aderente& aderente);

    /**
     * @brief Permite comparar o NIF de dois aderentes para determinar se são iguais
     * @param aderente - aderente cujo NIF queremos comparar
     * @return Retorna true caso a igualdade se verifique e false caso não se verifique
     */
    bool operator ==(const Aderente& aderente);

    /**
     * @brief Permite ordenar os aderentes por ordem alfabetica
     * @param aderente - aderente que queremos comparar
     * @return Retorna true caso o aderente passado como argumento tenha um nome maior por ordem alfabetica
     */
    bool operator <(const Aderente& aderente);
};

/** @} */ // end of Classe Aderentes

#endif //SRC_ADERENTE_H
