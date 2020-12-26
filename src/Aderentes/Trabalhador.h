#ifndef CINEMATECAPORTUGUESA_TRABALHADOR_H
#define CINEMATECAPORTUGUESA_TRABALHADOR_H

/** @defgroup Classe Trabalhador
 * Atributos e métodos para a classe Trabalhador
 *
 * @{
 */

#include "Utilizador.h"
#include "../Utils/utils.h"
#include "../DateTime/Date.h"


class Trabalhador : public Utilizador {
private:
    string nome;
    string localizacao;
    u_int numContratacoes;
    bool atual;
    Date dataContratacao;
    Date dataDespedimento;
public:
    /**
     * @brief Construtor default da classe Trabalhador
     */
    Trabalhador(){};

    /**
     * @brief Construtor da classe Trabalhador
     * @param nome - nome do trabalhador
     */
    Trabalhador(string nome);

    /**
     * @brief Construtor da classe Trabalhador
     * @param nome - nome do trabalhador
     * @param localizacao - local de trabalho do trabalhador
     */
    Trabalhador(string nome, string localizacao);

    /**
     * @brief Construtor da classe Trabalhador
     * @param n - nome do trabalhador
     * @param l - localizacao
     * @param dataCont - data de contratação
     * @param dataDesp - data de despedimento
     * @param atual - estado atual do trabalhador
     * @param exTrabalhador - estado que verifica se o trabalhador já foi funcionário da Cinemateca
     */
    Trabalhador(string n, string l, Date dataCont, Date dataDesp, bool atual);

    /**
     * @brief Permite obter o nome do trabalhador
     * @return Retorna o nome do trabalhador
     */
    string getNome() const;

    /**
     * @brief Permite obter o local de trabalho do trabalhador
     * @return Retorna o local de trabalho do trabalhador
     */
    string getLocalizacao() const;

    /**
     * @brief Permite obter o estado atual de contratação do trabalhador
     * @return Retorna o estado atual de contratação do trabalhador
     */
    bool getAtual() const;

    /**
     * @brief Atualiza o estado do atributo `atual`, que verifica se este trabalhador é um funcionário atual da Cinamateca
     * @param valor - novo valor de `atual`
     */
    void setAtual(const bool valor);

    /**
     * @brief Permite obter a data de contratação do trabalhador
     * @return Retorna a data de contratação do trabalhador
     */
    Date getDataContatacao() const;

    /**
     * @brief Permite obter a data de despedimento do trabalhador
     * @return Retorna a data de despedimento do trabalhador
     */
    Date getDataDespedimento() const;

    /**
     * @brief Atualiza a data de despedimento deste trabalhador
     * @param dataDespedimento - nova data de despedimento
     */
    void setDataDespedimento(const Date dataDespedimento);
};


class RegistoTrabalhador {
private:
    string trabalhador;
    string localizacao;
    u_int numContratacoes;
    bool atual;
    Date dataContratacao;
    Date dataDespedimento;
public:
    RegistoTrabalhador(){};

    /**
     * @brief Construtor da classe RegistoTrabalhador - regista um novo trabalhador da cinemateca
     * @param trabalhador - nome do trabalhador
     */
    RegistoTrabalhador(string trabalhador);

    /**
     * @brief Construtor da classe RegistoTrabalhador - regista um novo trabalhador da cinemateca
     * @param trabalhador - nome do trabalhador
     * @param localizacao - local de trabalho do trabalhador
     */
    RegistoTrabalhador(string trabalhador, string localizacao);

    /**
     * @brief Construtor da classe RegistoTrabalhador - regista um ex funcionário da cinemateca
     * @param t - nome do trabalhador
     * @param l - local de trabalho do trabalhador
     * @param dataCont - data de contratação do trabalhador
     * @param dataDesp - data de despedimento do trabalhador
     */
    RegistoTrabalhador(string t, string l, Date dataCont, Date dataDesp);

    /**
     * @brief Construtor da classe RegistoTrabalhador - regista um funcionário da cinemateca
     * @param t - nome do trabalhador
     * @param l - local de trabalho do trabalhador
     * @param dataCont - data de contratação do trabalhador
     * @param dataDesp - data de despedimento do trabalhador
     */
    RegistoTrabalhador(string t, string l, Date dataCont, Date dataDesp, bool atual);

    /**
     * @brief Atualiza o estado do atributo `atual` e a data de contratação, assinando um novo contrado de trabalho
     */
    void assinarContrato();

    /**
     * @brief Atualiza o estado do atributo `atual` e a data de despedimento, assindando a rescisão do contrato de trabalho atual
     */
    void resignarContrato();

    /**
     * @brief Permite obter o nome do trabalhador
     * @return Retorna o nome do trabalhador
     */
    string getTrabalhador() const;

    /**
     * @brief Permite obter o número de vezes que este trabalhador foi contratado para trabalhar na Cinemateca
     * @return Retorna o número de contratações
     */
    u_int getNumContratacoes() const;

    /**
     * @brief Incrementa o número de vezes que este trabalhador foi contratado para trabalhar na Cinemateca
     */
    void incNumContratacoes();

    /**
     * @brief Permite obter o local de trabalho do trabalhador
     * @return Retorna o local de trabalho do trabalhador
     */
    string getLocalizacao() const;

    /**
     * @brief Atualiza o local de trabalho deste registo
     * @param localizacao - novo local de trabalho
     */
    void setLocalizacao(const string localizacao);

    /**
     * @brief Permite obter o estado atual de contratação do trabalhador
     * @return Retorna o estado atual de contratação do trabalhador
     */
    bool getAtual() const;

    /**
     * @brief Atualiza o estado do atributo `atual`, que verifica se este trabalhador é um funcionário atual da Cinamateca
     * @param valor - novo valor de `atual`
     */
    void setAtual(const bool valor);

    /**
     * @brief Permite obter a data de contratação do trabalhador
     * @return Retorna a data de contratação do trabalhador
     */
    Date getDataContatacao() const;

    /**
     * @brief Atualiza a data de contratação deste registo
     * @param dataDespedimento - nova data de contratação
     */
    void setDataContratacao(const Date dataContratacao);

    /**
     * @brief Permite obter a data de despedimento do trabalhador
     * @return Retorna a data de despedimento do trabalhador
     */
    Date getDataDespedimento() const;

    /**
     * @brief Atualiza a data de despedimento deste registo
     * @param dataDespedimento - nova data de despedimento
     */
    void setDataDespedimento(const Date dataDespedimento);

    /**
     * @brief Permite mostrar um certo trabalhador no ecrã
     * @param out - outstream onde queremos mostrar o aderente
     * @param trabalhador - trabalhador que queremos mostrar no ecrã
     * @return retorna a outstream
     */
    friend ostream& operator <<(ostream& out, RegistoTrabalhador& trabalhador);

    /**
     * @brief Permite igualar um trabalhador a outro - iguala todos os seus atributos
     * @param trabalhador - aderente ao qual estamos a igualar o outro aderente
     */
    void operator =(const RegistoTrabalhador& trabalhador);

};


struct RegistoTrabalhadorHash {
    int operator()(const RegistoTrabalhador& rt) const {
        return rt.getTrabalhador().size();
    }

    bool operator()(const RegistoTrabalhador& rt1, const RegistoTrabalhador& rt2) const {
        return rt1.getTrabalhador() == rt2.getTrabalhador();
    }
};

/** @} */ // end of Classe Trabalhador

#endif //CINEMATECAPORTUGUESA_TRABALHADOR_H
