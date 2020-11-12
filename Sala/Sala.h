#ifndef SRC_SALA_H
#define SRC_SALA_H

#include "../Utils/utils.h"
#include "../DateTime/Time.h"
#include "../DateTime/Date.h"

#include "../Evento/Evento.h"
/**
 * Classe Sala
 */
class Sala {
private:
    string nome;            /**nome da sala*/
    u_int capacidade;       /**capacidade da sala*/
    list<Evento> eventos;   /**eventos da sala*/

public:
    /**
     * @brief Construtor default da classe Sala
     */
    Sala(){};

    /**
     * @brief Construtor da classe Sala
     * @param nome - nome da sala
     * @param capacidade - capacidade da sala
     */
    Sala(string nome, u_int capacidade);

    /**
     * @brief Permite obter o nome da sala
     * @return Retorna o nome da sala
     */
    string getNome() const;

    /**
     * @brief Permite obter a capacidade da sala
     * @return Retorna a capacidade da sala
     */
    u_int getCapacidade() const;

    /**
     * @brief Permite obter os eventos associados à sala
     * @return Retorna a lista de eventos associados à sala
     */
    list<Evento> getEventos() const;

    /**
     * @brief Permite confirmar a disponibilidade da sala para um certo evento
     * @param evento - evento para o qual queremos confirmar a disponibilidade
     * @return Retorna true caso a sala tenha disponibilidade para aquele evento, e false caso não tenha
     */
    bool checkDisponibilidade(const Evento evento);

    /**
     * @brief Permite adicionar um evento à lista de eventos daquela sala
     * @param evento - evento que queremos adicionar
     */
    void adicionarEvento(const Evento evento);

    /**
     * @brief Permite mostrar uma certa sala no ecrã
     * @param out - outstream onde queremos mostrar a sala
     * @param sala - sala que queremos mostrar
     * @return Retorna a outstream
     */
    friend ostream& operator <<(ostream& out, const Sala& sala);

    /**
     * @brief Permite igualar uma sala a outra - iguala todos os seus atributos
     * @param sala - sala à qual estamos a igualar a outra sala
     */
    void operator =(const Sala& sala);

    /**
     * @brief Permite ordenar as salas por ordem alfabetica
     * @param sala - sala que queremos comparar
     * @return Retorna true caso a sala passada como argumento tenha um nome maior por ordem alfabetica
     */
    bool operator <(const Sala& sala);
};


#endif //SRC_SALA_H
