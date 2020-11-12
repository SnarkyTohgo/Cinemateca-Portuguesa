#ifndef CINEMATECAPORTUGUESA_DATE_H
#define CINEMATECAPORTUGUESA_DATE_H

#include "../Utils/utils.h"
/**
 * Classe Date
 */
class Date {
private:
    u_int d; /**Dia*/
    u_int m; /**Mes*/
    u_int a; /**Ano*/

public:
    /**
     * @brief Construtor default da classe Date
     */
    Date(){}

    /**
     * @brief Construtor da classe Date
     * @param d - dia
     * @param m - mes
     * @param a - ano
     */
    Date(u_int d, u_int m, u_int a);

    /**
     * @brief Permite obter o dia
     * @return Retorna o dia
     */
    u_int getD() const;

    /**
     * @brief Permite obter o mes
     * @return Retorna o mes
     */
    u_int getM() const;

    /**
     * @brief Permite obter o ano
     * @return Retorna o ano
     */
    u_int getA() const;

    /**
     * @brief Permite comparar se uma data é igual a outra
     * @param date - data com a qual queremos comparar
     * @return Retorna true caso a comparacao se verifique e false caso isso nao aconteca
     */
    bool operator ==(const Date date);

    /**
     * @brief Permite determinar se uma data é anterior a outra
     * @param date - data que queremos comparar
     * @return Retorna true caso a data passada como argumento seja posterior à data com a qual estamos a comparar
     */
    bool operator <(const Date date);

    /**
     * @brief Permite mostrar uma data no ecrã
     * @param out - outstream onde queremos mostrar a data
     * @param date - data que queremos mostrar
     * @return Retorna a outstream
     */
    friend ostream& operator <<(ostream& out, const Date& date);
};


#endif //CINEMATECAPORTUGUESA_DATE_H
