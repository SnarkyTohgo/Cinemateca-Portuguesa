#include "Utilizador.h"

/*
 * CONSTRUCTORS
 */

Utilizador::Utilizador(u_int nif): nif(nif){
    if (to_string(this->nif).length() != 9)
        throw InvalidNif();
}

/*
 * MEMBER FUNCTIONS
 */

u_int
Utilizador::getNif() const {
    return this->nif;
}



/*
 * OPERATOR OVERLOADS
 */

ostream&
operator <<(ostream &out, Utilizador& utilizador) {
    out << "\nNIF: " << utilizador.getNif()
        << endl << endl;

    return out;
}

void
Utilizador::operator =(const Utilizador& utilizador) {
    this->nif = utilizador.nif;
}

bool
Utilizador::operator ==(const Utilizador& utilizador) {
    return this->nif == utilizador.getNif();
}

bool
Utilizador::operator<(const Utilizador& utilizador) {
    return this->nif < utilizador.getNif();
}