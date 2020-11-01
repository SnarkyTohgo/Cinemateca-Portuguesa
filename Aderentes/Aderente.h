#ifndef SRC_ADERENTE_H
#define SRC_ADERENTE_H

#include "../Utils/utils.h"
#include "../DateTime/Date.h"


class Aderente {
private:
    string nome;
    u_int nif;
    Date dataNasc;
    u_int anoAdesao;

public:
    Aderente(){};
    Aderente(string nome, u_int nif, Date dataNasc, u_int anoAdesao);

    string getNome() const;
    u_int getNif() const;
    Date getDataNasc() const;
    u_int getAnoAdesao() const;

    friend ostream& operator <<(ostream& out, Aderente& aderente);
    void operator =(const Aderente& aderente);
    bool operator ==(const Aderente& aderente);
    bool operator <(const Aderente& aderente);
};


#endif //SRC_ADERENTE_H
