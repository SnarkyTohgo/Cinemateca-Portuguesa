#include "Aderente.h"


/*
 * CONSTRUCTORS
 */

Aderente::Aderente(string nome, u_int nif, Date dataNasc, u_int anoAdesao)
    : Utilizador(nif){

    this->nome = nome;
    this->dataNasc = dataNasc;
    this->anoAdesao = anoAdesao;
}


/*
 * MEMBER FUNCTIONS
 */

string
Aderente::getNome() const {
    return this->nome;
}

Date
Aderente::getDataNasc() const {
    return this->dataNasc;
}

u_int
Aderente::getAnoAdesao() const {
    return this->anoAdesao;
}


/*
 * OPERATOR OVERLOADS
 */

ostream&
operator <<(ostream &out, Aderente& aderente) {
    out << toUpper(aderente.getNome())
        << "\nNIF: " << aderente.getNif()
        << "\nData de Nascimento: " << aderente.getDataNasc()
        << "Ano de Adesao: " << aderente.getAnoAdesao()
        << endl << endl;

    return out;
}

void
Aderente::operator =(const Aderente& aderente) {
    this->anoAdesao = aderente.anoAdesao;
}

bool
Aderente::operator <(const Aderente& aderente) {
    return this->nome < aderente.getNome();
}



