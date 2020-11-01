#ifndef SRC_EVENTO_H
#define SRC_EVENTO_H

#include "../Utils/utils.h"
#include "../DateTime/Date.h"
#include "../DateTime/Time.h"
#include "../Aderentes/Aderente.h"


class Evento {
private:

    string nome;
    Date data;
    Time hora;
    u_int duracao;
    u_int lotMax;
    float preco;
    u_int sala;

    list<Aderente> participantes;

public:
    Evento(){};
    Evento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco);
    Evento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco, u_int sala);


    string getNome() const;
    Date getData() const;
    Time getHora() const;
    u_int getDuracao() const;
    u_int getLotMax() const;
    float getPreco() const;
    u_int getSala() const;
    u_int getBilhetesComprados() const;
    double getTotalVendas() const;
    list<Aderente> getParticipantes() const;

    void setSala(const u_int sala);

    bool isLotado() const;
    void alocarParticipante(Aderente aderente);

    friend ostream& operator <<(ostream& out, const Evento& evento);
    bool operator <(const Evento& evento);
    void operator =(const Evento& evento);
    bool operator ==(const Evento& evento);
};


#endif //SRC_EVENTO_H
