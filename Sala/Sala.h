#ifndef SRC_SALA_H
#define SRC_SALA_H

#include "../Utils/utils.h"
#include "../DateTime/Time.h"
#include "../DateTime/Date.h"

#include "../Evento/Evento.h"

class Sala {
private:
    string nome;
    u_int capacidade;
    list<Evento> eventos;

public:
    Sala(){};
    Sala(string nome, u_int capacidade);

    string getNome() const;
    u_int getCapacidade() const;
    list<Evento> getEventos() const;

    bool checkDisponibilidade(const Evento evento);
    void adicionarEvento(const Evento evento);

    friend ostream& operator <<(ostream& out, const Sala& sala);
    void operator =(const Sala& sala);
    bool operator <(const Sala& sala);
};


#endif //SRC_SALA_H
