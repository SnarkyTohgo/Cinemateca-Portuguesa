#include "Aderente.h"


/*
 * CONSTRUCTORS
 */

Aderente::Aderente(string nome, u_int nif, Date dataNasc, u_int anoAdesao)
    : anoAdesao(anoAdesao), nif(nif), dataNasc(dataNasc), nome(nome){}


/*
 * MEMBER FUNCTIONS
 */

string
Aderente::getNome() const {
    return this->nome;
}

u_int
Aderente::getNif() const {
    return this->nif;
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
    this->nome = aderente.nome;
    this->nif = aderente.nif;
    this->dataNasc = aderente.dataNasc;
    this->anoAdesao = aderente.anoAdesao;
}

bool
Aderente::operator ==(const Aderente& aderente) {
    return this->nif == aderente.getNif();
}

bool
Aderente::operator<(const Aderente& aderente) {
    return this->nome < aderente.getNome();
}





