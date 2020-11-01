#include "Sala.h"

/*
 * CONSTRUCTORS
 */

Sala::Sala(string nome, u_int capacidade)
    : nome(nome){

    this->capacidade = capacidade;
}


/*
 * MEMBER FUNCTIONS
 */

string
Sala::getNome() const {
    return this->nome;
}

u_int
Sala::getCapacidade() const {
    return this->capacidade;
}

list<Evento>
Sala::getEventos() const {
    return this->eventos;
}

bool
Sala::checkDisponibilidade(const Evento evento){

    bool disponibilidade = false;

    // Ordenar eventos da sala por data (ASC)
    this->eventos.sort([](const Evento& e1, const Evento& e2){
        return e1.getData() < e2.getData();
    });

    for (auto eventoListado : this->eventos){
        if (evento.getData() == eventoListado.getData()){

            // calcular hora de termino do evento
            int duracaoEventoListado = eventoListado.getDuracao() / 60;             // duracao em horas
            int horaFim = eventoListado.getHora().getH() + duracaoEventoListado;

            Time fimEventoListado(horaFim, evento.getHora().getM(), evento.getHora().getS());

            if (evento.getHora() < fimEventoListado and evento.getHora() > eventoListado.getHora())
                continue;
            else {
                this->adicionarEvento(evento);
                disponibilidade = true;

                break;
            }
        } else {
            this->adicionarEvento(evento);
            disponibilidade = true;

            break;
        }
    }

    return disponibilidade;
}

void
Sala::adicionarEvento(const Evento evento){
    this->eventos.push_back(evento);
}


/*
 * OPERATOR OVERLOADS
 */

ostream&
operator <<(ostream &out, const Sala &sala) {
    out << toUpper(sala.getNome())
        << "\nCapacidade: " << sala.getCapacidade()
        <<  endl;

    return out;
}

void
Sala::operator =(const Sala& sala) {
    this->nome = sala.nome;
    this->capacidade = sala.capacidade;
}

bool
Sala::operator <(const Sala& sala){
    return this->nome < sala.getNome();
}


