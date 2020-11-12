#ifndef CINEMATECAPORTUGUESA_TIME_H
#define CINEMATECAPORTUGUESA_TIME_H

#include "../Utils/utils.h"

/**
 * Classe Time
 */
class Time {
private:
    int h;  /**horas*/
    int m;  /**minutos*/
    int s;  /**segundos*/

public:
    /**
     * @brief Construtor default da classe Time
     */
    Time(){};

    /**
     * @brief Construtor da classe Time
     * @param h - horas
     * @param m - minutos
     * @param s - segundos
     */
    Time(int h, int m, int s);

    /**
     * @brief Permite obter as horas
     * @return Retorna as horas
     */
    int getH() const;

    /**
     * @brief Permite obter os minutos
     * @return Retorna os minutos
     */
    int getM() const;

    /**
     * @brief Permite obter os segundos
     * @return Retorna os segundos
     */
    int getS() const;

    /**
     * @brief Permite definir as horas
     * @param h - horas
     */
    void setH(int h);

    /**
     * @brief Permite definir os minutos
     * @param m - minutos
     */
    void setM(int m);

    /**
     * @brief Permite definir os segundos
     * @param s - segundos
     */
    void setS(int s);

    /**
     * @brief Permite comparar se uma hora é igual a outra
     * @param time - hora com a qual queremos comparar
     * @return Retorna true caso a comparacao se verifique e false caso isso nao aconteca
     */
    bool operator ==(const Time t);

    /**
     * @brief Permite saber se uma hora é posterior a outra
     * @param t - hora que queremos comparar
     * @return Retorna true caso a hora passada como argumento seja posterior à hora com a qual estamos a comparar
     */
    bool operator <(const Time t);

    /**
     * @brief Permite saber se uma hora é anterior a outra
     * @param t - hora que queremos comparar
     * @return Retorna true caso a hora passada como argumento seja anterior à hora com a qual estamos a comparar
     */
    bool operator >(const Time t);

    /**
     * @brief Permite mostrar uma hora no ecrã
     * @param out - outstream onde queremos mostrar a hora
     * @param time - hora que queremos mostrar
     * @return Retorna a outstream
     */
    friend ostream& operator <<(ostream& out, const Time& time);
};


#endif //CINEMATECAPORTUGUESA_TIME_H
