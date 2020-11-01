#include "Evento.h"

/*
 * CONSTRUCTORS
 */

Evento::Evento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco)
    : nome(nome){

    this->data = data;
    this->hora = hora;
    this->duracao = duracao;
    this->lotMax = lotMax;
    this->preco = preco;
}

Evento::Evento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco, u_int sala)
        : nome(nome){

    this->data = data;
    this->hora = hora;
    this->duracao = duracao;
    this->lotMax = lotMax;
    this->preco = preco;
    this->sala = sala;
}


/*
 * MEMBER FUNCTIONS
 */

string
Evento::getNome() const {
    return this->nome;
}

Date
Evento::getData() const {
    return this->data;
}

Time
Evento::getHora() const {
    return this->hora;
}

u_int
Evento::getDuracao() const {
    return this->duracao;
}

u_int
Evento::getLotMax() const {
    return this->lotMax;
}

float
Evento::getPreco() const {
    return this->preco;
}

u_int
Evento::getSala() const {
    return this->sala;
}

list<Aderente>
Evento::getParticipantes() const {
    return this->participantes;
}

u_int
Evento::getBilhetesComprados() const {
    return this->participantes.size();
}

double
Evento::getTotalVendas() const {
    double total = 0;

    for (auto bilhete : this->participantes)
        total += (double) this->preco;

    return total;
}

void
Evento::setSala(const u_int sala){
    this->sala = sala;
}

bool
Evento::isLotado() const {
    return this->participantes.size() == this->lotMax;
}

void
Evento::alocarParticipante(Aderente aderente){
    this->participantes.push_back(aderente);
}


/*
 * OPERATOR OVERLOADS
 */

ostream&
operator <<(ostream& out, const Evento& evento){
    out << toUpper(evento.getNome())
        << "\nData: " << evento.getData()
        << "Inicio: " << evento.getHora()
        << "Duracao: " << evento.getDuracao()
        << "\nLotacao Maxima: " << evento.getLotMax()
        << "\nPreco: " << evento.getPreco()
        <<  endl << endl;

    return out;
}

bool
Evento::operator <(const Evento& evento) {
    return this->nome < evento.getNome();
}

void
Evento::operator=(const Evento& evento) {
    this->nome = evento.nome;
    this->data = evento.data;
    this->hora = evento.hora;
    this->duracao = evento.duracao;
    this->lotMax = evento.lotMax;
    this->preco = evento.preco;
}

bool
Evento::operator==(const Evento& evento) {
    return this->nome == evento.getNome();
}













