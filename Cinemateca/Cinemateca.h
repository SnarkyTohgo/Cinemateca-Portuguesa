#ifndef SRC_CINEMATECA_H
#define SRC_CINEMATECA_H

/** @defgroup Classe Cinemateca
 * Atributos e métodos para a classe Cinemateca
 *
 * @{
 */

#include "../Utils/utils.h"

#include "../Aderentes/Aderente.h"
#include "../Evento/Evento.h"
#include "../Sala/Sala.h"


class Cinemateca {
private:
    static u_int anoAtual;             /**Ano atual*/

    const string localizacao;          /**Localizacao da Cinemateca*/
    const string morada;               /**Morada da Cinemateca*/

    list<Utilizador> naoAderentes;     /**Utilizadores não aderentes da Cinemateca */
    list<Aderente> aderentes;          /**Aderentes (amigos) da Cinemateca*/
    list<Sala> salas;                  /**Salas da Cinemateca*/

    u_int bilhetesComprados;           /**Total de bilhetes comprados na Cinemateca*/
    double totalVendas;                /**Total de vendas da Cinemateca*/

public:
    list<Evento> eventos;              /**Eventos da Cinemateca*/

    /**
     * @brief Construtor default da classe Cinemateca
     */
    Cinemateca(){};

    /**
     * @brief Contrutor da classe Cinemateca
     * @param localizacao - localizacao da Cinemateca
     * @param morada - morada da Cinemateca
     */
    Cinemateca(string localizacao, string morada);

    /**
     * @brief Permite obter o ano atual
     * @return Retorna o ano atual
     */
    u_int getAnoAtual() const;

    /**
     * @brief Permite obter a localizacao da Cinemateca
     * @return Retorna a localizacao da Cinemateca
     */
    string getLocalizacao() const;

    /**
     * @brief Permite obter a morada da Cinemateca
     * @return Retorna a morada da Cinemateca
     */
    string getMorada() const;

    /**
     * @brief Permite obter os aderentes (amigos) da Cinemateca
     * @return Retorna a lista de aderentes (amigos) da Cinemateca
     */
    list<Aderente> getAderentes() const;

    /**
     * @brief Permite obter os utilizadores não aderentes Cinemateca
     * @return Retorna a lista de utilizadores não aderentes da Cinemateca
     */
    list<Utilizador> getNaoAderentes() const;

    /**
     * @brief Permite obter as salas da Cinemateca
     * @return Retorna a lista de salas da Cinemateca
     */
    list<Sala> getSalas() const;

    /**
     * @brief Permite obter um evento especifico que se encontra numa certa posicao da lista de eventos
     * @param pos - posicao na lista do evento que queremos obter
     * @return Retorna o evento especifico que queremos obter
     */
    Evento getEvento(int pos) const;

    /**
     * @brief Permite obter o numero de bilhetes comprados na Cinemateca
     * @return Retorna o numero de bilhetes comprados na Cinemateca
     */
    u_int getBilhetesComprados() const;

    /**
     * @brief Permite obter o total de vendas (lucro) da Cinemateca
     * @return Retorna o total de vendas (lucro) da Cinemateca
     */
    double getTotalVendas() const;

    /**
     * @brief Permite definir as salas da Cinemateca
     * @param salas - salas da Cinemateca
     */
    void setSalas(list<Sala> salas);

    /**
     * @brief Permite definir os eventos da Cinemateca
     * @param eventos - eventos da Cinemateca
     */
    void setEventos(list<Evento> eventos);

    /**
     * @brief Permite definir os aderentes da Cinemateca
     * @param aderentes - aderentes/amigos da Cinemateca
     */
    void setAderentes(list<Aderente> aderentes);

    /**
     * @brief Permite definir os aderentes da Cinemateca
     * @param aderentes - aderentes/amigos da Cinemateca
     */
    void setNaoAderentes(list<Utilizador> naoAderentes);

    /**
     * @brief Permite criar um novo aderente e adiciona-lo à lista de aderentes da Cinemateca
     * @param nome - nome do novo aderente
     * @param nif - nif do novo aderente
     * @param dataNasc - data de nascimento do novo aderente
     * @param anoAtual - ano em que o novo aderente está a aderir à Cinemateca
     */
    void registarAderente(string nome, u_int nif, Date dataNasc, u_int anoAtual);

    /**
     * @brief Permite criar um novo utilizador e adiciona-lo à lista de utilizadores não-aderentes da Cinemateca
     * @param nif - nif do novo aderente
     */
    void registarUtilizadorNaoAderente(u_int nif);

    /**
     * @brief Permite criar um novo evento e adicioná-lo à lista de eventos da Cinemateca
     * @param nome - nome do novo evento
     * @param data - data em que decorrerá o novo evento
     * @param hora - hora do novo evento
     * @param duracao - duracao do novo evento
     * @param lotMax - lotacao maxima do novo evento
     * @param preco - preco do novo evento
     */
    void adicionarEvento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco);

    /**
     * @brief Permite alocar uma sala a um certo evento
     * @param evento - evento ao qual queremos alocar a sala
     */
    void alocarSala(Evento* evento);

    /**
     * @brief Permite a um certo aderente comprar bilhete para um certo evento
     * @param aderente - aderente que quer comprar o bilhete
     * @param evento - evento para o qual o aderente quer comprar o bilhete
     * @return Retorna 0 em caso de sucesso na compra, e 1 em caso de erro
     */
    int comprarBilhete(Aderente aderente, Evento* evento);

    /**
     * @brief Permite a um certo utilizador comprar bilhete para um certo evento
     * @param utilizador - utilizador que quer comprar o bilhete
     * @param evento - evento para o qual o aderente quer comprar o bilhete
     * @return Retorna 0 em caso de sucesso na compra, e 1 em caso de erro
     */
    int comprarBilhete(Utilizador utilizador, Evento* evento);

    /**
     * @brief Permite fazer parse das salas que estao guardadas no ficheiro de salas
     */
    void parseSalas();

    /**
     * @brief Permite fazer parse dos eventos que estao guardados no ficheiro de eventos
     */
    void parseEventos();

    /**
     * @brief Permite fazer parse dos aderentes que estao guardados no ficheiro de aderentes
     */
    void parseAderentes();

    /**
     * @brief Permite fazer parse dos utilizadores não-aderentes que estao guardados no ficheiro de não-aderentes
     */
    void parseNaoAderentes();

    /**
     * @brief Permite guardar um aderente no ficheiro de aderentes
     * @param aderente - aderente que queremos guardar
     */
    void updateAderentes(Aderente aderente) const;

    /**
     * @brief Permite guardar um não-aderente no ficheiro de aderentes
     * @param aderente - aderente que queremos guardar
     */
    void updateNaoAderentes(Utilizador naoAderente) const;

    /**
     * @brief Permite guardar um evento no ficheiro de eventos
     * @param evento - evento que queremos guardar
     */
    void updateEventos(Evento evento) const;

    /**
     * @brief Atualiza o numero de bilhetes comprados
     */
    void updateBilhetesComprados();

    /**
     * @brief Atualiza o valor total de vendas
     * @param valor - valor a adicionar ao total de vendas
     */
    void updateTotalVendas(const float valor);

    /**
     * @brief Permite ordenar as salas por nome
     */
    void ordenarSalasNome();

    /**
     * @brief Permite ordenar as salas por capacidade
     */
    void ordenarSalasCapacidade();

    /**
     * @brief Permite ordenar os eventos por nome
     */
    void ordenarEventosNome();

    /**
     * @brief Permite ordenar os eventos por data
     */
    void ordenarEventosData();

    /**
     * @brief Permite ordenar os eventos por preco
     */
    void ordenarEventosPreco();

    /**
     * @brief Permite ordenar os eventos pela lotacao maxima
     */
    void ordenarEventosLotMax();

    /**
     * @brief Permite ordenar os aderentes por nome
     */
    void ordenarAderentesNome();

    /**
     * @brief Permite ordenar os aderentes por data de nascimento
     */
    void ordenarAderentesDataNasc();

    /**
     * @brief permite ordenar os aderentes por ano de adesao
     */
    void ordenarAderentesAnoAdesao();
};

/** @} */ // end of Classe Cinemateca

#endif //SRC_CINEMATECA_H
