#ifndef SRC_EVENTO_H
#define SRC_EVENTO_H

/** @defgroup Classe Evento
 * Atributos e métodos para a classe Evento
 *
 * @{
 */

#include "../Utils/utils.h"
#include "../DateTime/Date.h"
#include "../DateTime/Time.h"
#include "../Aderentes/Aderente.h"


class Evento {
private:

    string nome;                 /**Nome do evento*/
    Date data;                   /**Data do evento*/
    Time hora;                   /**Hora do evento*/
    u_int duracao;               /**Duracao do evento*/
    u_int lotMax;                /**Lotacao maxima do evento*/
    float preco;                 /**Preco do evento*/
    float totalVendas;           /**Valor total das vendas do evento*/
    u_int sala;                  /**Sala do evento*/
    u_int bilhetesComprados;     /**Total de bilhetes comprados*/

    list<Aderente> participantesAderentes;        /** Aderentes participantes do evento*/
    list<Utilizador> participantesNaoAderentes;   /** Utilizadores participantes do evento*/

public:
    /**
     * @brief Construtor por default da classe Evento
     */
    Evento(){};

    /**
     * @brief Construtor da classe Evento
     * @param nome - nome do evento
     * @param data - data do evento
     * @param hora - hora de inicio do evento
     * @param duracao - duracao do evento
     * @param lotMax - lotacao maxima do evento
     * @param preco - preco do evento
     */
    Evento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco);

    /**
     * @brief Construtor da classe Evento
     * @param nome - nome do evento
     * @param data - data do evento
     * @param hora - hora de inicio do evento
     * @param duracao - duracao do evento
     * @param lotMax - lotacao maxima do evento
     * @param preco - preco do evento
     * @param sala - sala em que decorre o evento
     */
    Evento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco, u_int sala, u_int bilhetesComprados);

    /**
     * @brief Permite obter o nome do evento
     * @return Retorna o nome do evento
     */
    string getNome() const;

    /**
     * @brief Permite obter a data do evento
     * @return Retorna a data do evento
     */
    Date getData() const;

    /**
     * @brief Permite obter a hora do evento
     * @return Retorna a hora do evento
     */
    Time getHora() const;

    /**
     * @brief Permite obter a duracao do evento
     * @return Retorna a duracao do evento
     */
    u_int getDuracao() const;

    /**
     * @brief Permite obter a lotacao maxima do evento
     * @return Retorna a lotacao maxima do evento
     */
    u_int getLotMax() const;

    /**
     * @brief Permite obter o preco do evento
     * @return Retorna o preco do evento
     */
    float getPreco() const;

    /**
     * @brief Permite obter a sala do evento
     * @return Retorna a sala do evento
     */
    u_int getSala() const;

    /**
     * @brief Permite obter o numero de bilhetes comprados do evento
     * @return Retorna o numero de bilhetes comprados do evento
     */
    u_int getBilhetesComprados() const;

    /**
     * @brief Permite obter o total de vendas (lucro) do evento
     * @return Retorna o total de vendas (lucro) do evento
     */
    float getTotalVendas() const;

    /**
     * @brief Permite obter os participantes no evento
     * @return Retorna a lista de participantes no evento
     */
    list<Utilizador> getParticipantes() const;

    /**
     * @brief Permite definir a sala associada ao evento
     * @param sala - sala associada ao evento
     */
    void setSala(const u_int sala);

    /**
    * @brief Atualiza o valor total das vendas de bilheteira para um dado evento
    */
    void updateTotalVendas(float valor);

    /**
     * @brief Incrementa o valor de bilhetes comprados para este evento
     */
    void updateBilhetesComprados();

    /**
     * @brief Permite determinar se a lotacao maxima de um evento ja foi atingida
     */
    bool isLotado() const;

    /**
     * @brief Permite adicionar um participante à lista de participantes aderentes do evento
     * @param aderente Aderente que participa num evento
     */
    void alocarParticipante(Aderente aderente);

    /**
     * @brief Permite adicionar um participante à lista de participantes utilizadores do evento
     * @param utilizador Utilizador que participa num evento
     */
    void alocarParticipante(Utilizador naoAderente);

    /**
     * @brief Permite mostrar o evento no ecrã
     * @param out - outstream onde queremos mostrar o evento
     * @param evento - evento que queremos mostrar
     * @return retorna a outstream
     */
    friend ostream& operator <<(ostream& out, const Evento& evento);

    /**
     * @brief Permite ordenar os eventos por ordem alfabetica
     * @param evento - evento que estamos a comparar
     * @return Retorna true caso o evento passado como argumento tenha um nome maior por ordem alfabetica
     */
    bool operator <(const Evento& evento);

    /**
     * @brief Permite igualar um evento a outro - iguala todos os seus atributos
     * @param evento - evento ao qual estamos a igualar o outro evento
     */
    void operator =(const Evento& evento);

    /**
     * @brief Permite comparar se os nomes de dois eventos sao iguais
     * @param evento - evento que estamos a comparar
     * @return Retorna true caso a igualdade se verifique e false caso não se verifique
     */
    bool operator ==(const Evento& evento);
};

/** @} */ // end of Classe Evento


class ItemHistoricoEventos {
private:
    Evento* itemEvento;
public:
    /**
     * @brief Construtor por default da classe ItemPosterEventos
     */
    ItemHistoricoEventos(Evento* itemEvento);

    /**
     * @brief Construtor da classe ItemPosterEventos
     * @param nome - nome do evento
     * @param data - data do evento
     * @param hora - hora de inicio do evento
     * @param duracao - duracao do evento
     * @param lotMax - lotacao maxima do evento
     * @param preco - preco do evento
     * @param sala - sala em que decorre o evento
     */
    ItemHistoricoEventos(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco, u_int sala, u_int bilhetesComprados);

    /**
     * @brief Permite obter o evento associado a este item do poster de eventos
     * @return Retorna o evento associado a este item
     */
    Evento* getEvento();

    /**
     * @brief Permite obter o nome do evento
     * @return Retorna o nome do evento
     */
    string getNome() const;

    /**
     * @brief Permite obter a data do evento
     * @return Retorna a data do evento
     */
    Date getData() const;

    /**
     * @brief Permite obter a hora do evento
     * @return Retorna a hora do evento
     */
    Time getHora() const;

    /**
     * @brief Permite obter a duracao do evento
     * @return Retorna a duracao do evento
     */
    u_int getDuracao() const;

    /**
     * @brief Permite obter a lotacao maxima do evento
     * @return Retorna a lotacao maxima do evento
     */
    u_int getLotMax() const;

    /**
     * @brief Permite obter o preco do evento
     * @return Retorna o preco do evento
     */
    float getPreco() const;

    /**
     * @brief Permite obter a sala do evento
     * @return Retorna a sala do evento
     */
    u_int getSala() const;

    /**
     * @brief Permite obter o numero de bilhetes comprados do evento
     * @return Retorna o numero de bilhetes comprados do evento
     */
    u_int getBilhetesComprados() const;

    /**
     * @brief Permite obter o total de vendas (lucro) do evento
     * @return Retorna o total de vendas (lucro) do evento
     */
    float getTotalVendas() const;

    /**
     * @brief Permite obter os participantes no evento
     * @return Retorna a lista de participantes no evento
     */
    list<Utilizador> getParticipantes() const;

    /**
     * @brief Permite ordenar os items do poster ordenados pelo número de aderentes que participaram no evento e, em caso de empate, por ordem alfabética da localização
     * @param ipe - evento que estamos a comparar
     * @return Retorna true caso o item seja menor
     */
    bool operator <(const ItemHistoricoEventos& ihe) const;

    /**
     * @brief Permite comparar se dois eventos do poster são iguais
     * @param evento - evento que estamos a comparar
     * @return Retorna true caso a igualdade se verifique e false caso não se verifique
     */
    bool operator ==(const ItemHistoricoEventos& ihe) const;
};

class ItemEvento {
private:
    Evento* evento;
    float satizfacao;
    vector<u_int>todosRatings;
public:
    ItemEvento(Evento* evento);
    ItemEvento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco, u_int sala, u_int bilhetesComprados);

    Evento* getEvento() const;
    float getSatizfacao() const;
    void adicionarRating(const u_int rating);
    void setSatizfacao(const float satizfacao);
    void setTodosRatings(const vector<u_int> todosRatings);
    vector<u_int> getTodosRatings() const;
    void updateSatizfacao(const float satizfacao);

    bool operator <(const ItemEvento& ie) const;
    bool operator ==(const ItemEvento& ie) const;

    friend ostream& operator <<(ostream& out, const ItemEvento& ie);

};

#endif //SRC_EVENTO_H
