#include "Cinemateca.h"

/*
 * Globals
 */

ifstream salasDB;
ifstream ratingsDB;
ifstream eventosDB;
ifstream aderentesDB;
ifstream naoAderentesDB;
ifstream trabalhadoresDB;

vector<string> salasData;
vector<string> ratingsData;
vector<string> eventosData;
vector<string> aderentesData;
vector<string> naoAderentesData;
vector<string> trabalhadoresData;


/*
 * CONSTRUCTORS
 */

auto now = Clock::now();
std::time_t now_c = Clock::to_time_t(now);
struct tm *parts = std::localtime(&now_c);

u_int Cinemateca::anoAtual = 1900 + parts->tm_year;

Date dataAtual(parts->tm_mday, 1 + parts->tm_mon, 1900 + parts->tm_year);
Date ultimosDozeMeses(parts->tm_mday, 1 + parts->tm_mon, 1900 + parts->tm_year - 1);

Cinemateca::Cinemateca(string localizacao, string morada)
    : localizacao(localizacao), morada(morada), historico(ItemHistoricoEventos("", Date(), Time(), 0, 0, 0.00, 0, 0)) {

    this->parseEventos();
    this->parseSalas();
    this->parseAderentes();
    this->parseNaoAderentes();
    this->parseTrabalhadores();

    this->registarTrabalhadores();

    this->bilhetesComprados = 0;
    this->totalVendas = 0;

    for (auto evento : this->eventos)
        this->alocarSala(&evento);

    this->gerarHistorico();
    this->checkRatings();
}


/*
 * MEMBER FUNCTIONS
 */

// RATINGS

void
Cinemateca::adicionarRating(const Evento evento) {
    ItemEvento novoItem(evento.getNome(), evento.getData(), evento.getHora(), evento.getDuracao(), evento.getLotMax(), evento.getPreco(), evento.getSala(), evento.getBilhetesComprados());
    this->ratings.push(novoItem);
    this->updateRatings(novoItem);
}

priority_queue<ItemEvento>
Cinemateca::getRatings() const {
    return this->ratings;
}

void
Cinemateca::atribuirRating(const string evento, const u_int satizfacao) {
    if (satizfacao < 1 or satizfacao > 5)
        throw InvalidRating();

    priority_queue<ItemEvento> tmp;

    while (!this->ratings.empty()) {
        if (this->ratings.top().getEvento()->getNome() == evento) {
            ItemEvento novoItem(this->ratings.top().getEvento());
            novoItem.setSatizfacao(this->ratings.top().getSatizfacao());
            novoItem.setTodosRatings(this->ratings.top().getTodosRatings());
            novoItem.updateSatizfacao(satizfacao);
            tmp.push(novoItem);
        } else {
            tmp.push(this->ratings.top());
        }
        this->ratings.pop();
    }

    while (!tmp.empty()) {
        this->ratings.push(tmp.top());
        tmp.pop();
    }

    // update ficheiro satizfacao

    deleteFileData("../satizfacao.dat");

    priority_queue<ItemEvento> ratingsCpy = this->getRatings();
    while (!ratingsCpy.empty()) {
        this->updateRatings(ratingsCpy.top());
        ratingsCpy.pop();
    }
}

void
Cinemateca::checkRatings() {
    priority_queue<ItemEvento> tmp;

    while (!this->ratings.empty()) {
        // Se o evento occoreu nos ultimos 12 meses
        Evento* ev = this->ratings.top().getEvento();
        if (ev->getData() <  dataAtual and ev->getData() > ultimosDozeMeses) {
            tmp.push(this->ratings.top());
        }
        this->ratings.pop();
    }

    while(!tmp.empty()) {
        this->ratings.push(tmp.top());
        tmp.pop();
    }

    // update ficheiro satizfacao

    deleteFileData("../satizfacao.dat");

    priority_queue<ItemEvento> ratingsCpy = this->getRatings();
    while (!ratingsCpy.empty()) {
        this->updateRatings(ratingsCpy.top());
        ratingsCpy.pop();
    }
}

Evento
Cinemateca::pesquisarEvento(const Date dataChao, const Date dataTeto) const {
    priority_queue<ItemEvento> tmp = this->getRatings();
    Evento* found;

    while (!tmp.empty()) {
        Date dataEvento = tmp.top().getEvento()->getData();

        if (dataEvento > dataChao and dataEvento < dataTeto) {
            found = tmp.top().getEvento();
            break;
        }
        tmp.pop();
    }

    return *found;
}

// HISTORICO

void
Cinemateca::gerarHistorico() {
    this->historico.makeEmpty();

    list<Evento>::iterator it;
    for (it = this->eventos.begin(); it != this->eventos.end(); ++it) {
        if (it->getData() < dataAtual) {
            Evento* ptrEvento = new Evento(it->getNome(), it->getData(), it->getHora(), it->getDuracao(), it->getLotMax(), it->getPreco(), it->getSala(), it->getBilhetesComprados());
            historico.insert(ptrEvento);
        }
    }
}

BST<ItemHistoricoEventos>
Cinemateca::getHistoricoEventos() {
    return this->historico;
}

vector<ItemHistoricoEventos>
Cinemateca::getExitosBilheteira() {
    vector<ItemHistoricoEventos> tmp, exitos;
    BSTItrIn<ItemHistoricoEventos> it(this->historico);

    while (!it.isAtEnd()) {
        tmp.push_back(it.retrieve());
        it.advance();
    }

    sort(tmp.begin(), tmp.end(), [](ItemHistoricoEventos& i1, ItemHistoricoEventos& i2){
        return i1.getBilhetesComprados() > i2.getBilhetesComprados();
    });

    for (size_t i = 0; i < 10; i++) {
        exitos.push_back(tmp[i]);
    }

    return exitos;
}

vector<ItemHistoricoEventos>
Cinemateca::getEventosLotMax() {
    vector<ItemHistoricoEventos> res;
    BSTItrIn<ItemHistoricoEventos> it(this->historico);

    while (!it.isAtEnd()) {
        if (it.retrieve().getBilhetesComprados() == it.retrieve().getLotMax()) {
            res.push_back(it.retrieve());
        }
        it.advance();
    }

    sort(res.begin(), res.end(), [](ItemHistoricoEventos& i1, ItemHistoricoEventos& i2){
        return i1.getBilhetesComprados() > i2.getBilhetesComprados();
    });

    return res;
}


// GETTERS

u_int
Cinemateca::getAnoAtual() const {
    return this->anoAtual;
}

string
Cinemateca::getLocalizacao() const {
    return this->localizacao;
}

string
Cinemateca::getMorada() const {
    return this->morada;
}

list<Aderente>
Cinemateca::getAderentes() const {
    return this->aderentes;
}

list<Utilizador>
Cinemateca::getNaoAderentes() const {
    return this->naoAderentes;
}

list<Sala>
Cinemateca::getSalas() const {
    return this->salas;
}

Evento
Cinemateca::getEvento(int pos) const {

    int idx = 0;
    for (auto evento : this->eventos){
        if (idx == pos) return evento;
        idx++;
    }

    return Evento();
}

u_int
Cinemateca::getBilhetesComprados() const {
    return this->bilhetesComprados;
}

double
Cinemateca::getTotalVendas() const {
    return this->totalVendas;
}

// SETTERS

void
Cinemateca::setSalas(list<Sala> salas){
    this->salas = salas;
}

void
Cinemateca::setEventos(list<Evento> eventos){
    this->eventos = eventos;
}

void
Cinemateca::setAderentes(list<Aderente> aderentes){
    this->aderentes = aderentes;
}

void
Cinemateca::setNaoAderentes(list<Utilizador> naoAderentes){
    this->naoAderentes = naoAderentes;
}

// ADERENTES E EVENTOS

void
Cinemateca::registarAderente(string nome, u_int nif, Date dataNasc, u_int anoAtual) {
    Aderente novoAderente(nome, nif, dataNasc, anoAtual);

    this->aderentes.push_back(novoAderente);
    this->updateAderentes(novoAderente);

    cout << "\n>>>Novo aderente dos Amigos da Cinematega registado com successo!<<<\n"
         << novoAderente;
}

void
Cinemateca::registarUtilizadorNaoAderente(u_int nif) {
    Utilizador novoUtilizador(nif);

    for (auto utilizador : this->naoAderentes){
        if (nif == utilizador.getNif())
            return;
    }

    this->naoAderentes.push_back(novoUtilizador);
    this->updateNaoAderentes(novoUtilizador);

    cout << "\n>>>Novo utilizador registado com successo!<<<\n"
         << novoUtilizador;
}

void
Cinemateca::apagarAderente(u_int nif){
    for(auto aderente : this->aderentes){
        if(aderente.getNif()==nif){
            aderentes.remove(aderente);
        }
    }
    deleteFileData("../aderentes.dat");

    for(auto aderente : this->aderentes){
        updateAderentes(aderente);
    }
}

void
Cinemateca::adicionarEvento(string nome, Date data, Time hora, u_int duracao, u_int lotMax, float preco){

    Evento novoEvento(nome, data, hora, duracao, lotMax, preco);
    this->eventos.push_back(novoEvento);

    Evento* eventoPtr = &novoEvento;
    this->alocarSala(eventoPtr);

    // Adicionar à fila de ratings
    this->adicionarRating(novoEvento);

    // Write to file
    this->updateEventos(novoEvento);

    cout << "\n>>>Novo evento adicionado com sucesso!<<<\n"
         << novoEvento;
}

void Cinemateca::removerEvento(string nome){
    bool found = false;
    for (auto evento : this->eventos) {
        if (nome == evento.getNome()){
            found = true;
            eventos.remove(evento);
        }
    }

    if (!found)
        throw InvalidEvent();

    deleteFileData("../eventos.dat");

    for(auto evento : this->eventos){
        updateEventos(evento);
    }
}

void
Cinemateca::alocarSala(Evento* evento){

    this->ordenarSalasCapacidade();

    for (auto sala : this->salas){

        if (sala.getCapacidade() >= evento->getLotMax()){
            bool salaDisponivel = sala.checkDisponibilidade(*evento);

            if (salaDisponivel){
                evento->setSala((u_int) stoi(sala.getNome()));
                break;
            }
        }
    }
}

// BILHETES

int
Cinemateca::comprarBilhete(Aderente aderente, list<Evento>::iterator evento) {

    if (evento->isLotado()){
        cout << "Evento " << toUpper(evento->getNome()) << " ja se encontra lotado\n";

        return EXIT_FAILURE;
    }

    float valorComDesconto;
    bool bilheteGratuito = false;

    // Bilhete gratuito - caso o aderente tenha +65anos, evento no Porto,
    // menos de 8h para o inicio, menos de 50% bilehtes vendidos
    if (this->getLocalizacao() == "Porto") {
        if ((this->getAnoAtual() - aderente.getDataNasc().getA()) >= 65) {
            if ((evento->getBilhetesComprados() / evento->getLotMax()) < 0.5) {
                char answer;
                cout << "\nCaso falte menos de 8 horas para o inicio do evento"
                     << "\npode usufruir dum bilhete gratuito por ter +65anos\n"
                     << "\nDeseja assistir ao evento gratuitamente?"
                     << "\nS ou N ?\n" << endl;
                cin >> answer;
                if(answer == 'S'){
                    valorComDesconto = 0.0;
                    bilheteGratuito = true;
                }

            }
        }
    }
    if (!bilheteGratuito) {
        valorComDesconto = evento->getPreco() - (evento->getPreco() * (this->anoAtual - aderente.getAnoAdesao()) * 0.01);
    }

    evento->alocarParticipante(aderente);
    evento->updateBilhetesComprados();
    evento->updateTotalVendas(valorComDesconto);

    this->updateBilhetesComprados();
    this->updateTotalVendas(valorComDesconto);

    // Re-escrever o ficheiro eventos.dat
    deleteFileData("../eventos.dat");

    for (auto evento : this->eventos) {
        this->updateEventos(evento);
    }

    cout << "\nBilhete comprado com sucesso!\n"
         << "\nEvento: " << toUpper(evento->getNome())
         << "\nTitular: " << aderente.getNome()
         << "\nNIF: " << aderente.getNif()
         << "\nPvP: " << valorComDesconto
         << endl;

    return EXIT_SUCCESS;
}

int
Cinemateca::comprarBilhete(Utilizador utilizador, list<Evento>::iterator evento){

    if (evento->isLotado()){
        cout << "Evento " << toUpper(evento->getNome()) << " ja se encontra lotado\n";

        return EXIT_FAILURE;
    }

    evento->alocarParticipante(utilizador);
    evento->updateBilhetesComprados();
    evento->updateTotalVendas(evento->getPreco());

    this->updateBilhetesComprados();
    this->updateTotalVendas(evento->getPreco());

    // Re-escrever o ficheiro eventos.dat
    deleteFileData("../eventos.dat");

    for (auto evento : this->eventos) {
        this->updateEventos(evento);
    }

    cout << "\nBilhete comprado com sucesso!\n"
         << "\nEvento: " << toUpper(evento->getNome())
         << "\nNIF: " << utilizador.getNif()
         << "\nPvP: " << evento->getPreco()
         << endl;

    return EXIT_SUCCESS;
}

// TRABALHADORES

int
Cinemateca::registarTrabalhadores() {
    for (auto trabalhador : this->contratacoes) {
        pair<HashTableTrabalhadores::iterator, bool> res = this->registoTrabalhadores.insert(trabalhador->getNome());
        if (!res.second) {
            RegistoTrabalhador novoRegisto = *res.first;

            novoRegisto.setAtual(trabalhador->getAtual());
            novoRegisto.setLocalizacao(this->localizacao);
            novoRegisto.setDataContratacao(trabalhador->getDataContatacao());
            novoRegisto.setDataDespedimento(trabalhador->getDataDespedimento());

            this->registoTrabalhadores.erase(res.first);
            this->registoTrabalhadores.insert(novoRegisto);
        }
    }
    return this->registoTrabalhadores.size();
}

void
Cinemateca::contratarTrabalhador(string nome) {
    Trabalhador* novoTrabalhador = new Trabalhador(nome, this->localizacao);
    this->contratacoes.push_back(novoTrabalhador);
    this->registarTrabalhadores();

    deleteFileData("../trabalhadores.dat");

    for (auto trabalhador : this->contratacoes) {
        this->updateTrabalhadores(trabalhador);
    }
}

void
Cinemateca::despedirTrabalhador(string nome) {
    vector<Trabalhador *>::iterator it;
    for (it = this->contratacoes.begin(); it != this->contratacoes.end(); ++it) {
        if ((*it)->getNome() == nome) {
            if ((*it)->getDataDespedimento().undefined()) {
                auto now = Clock::now();
                std::time_t now_c = Clock::to_time_t(now);
                struct tm *parts = std::localtime(&now_c);

                Date dataDesp(parts->tm_mday, parts->tm_mon + 1, 1900 + parts->tm_year);
                (*it)->setDataDespedimento(dataDesp);
                (*it)->setAtual(false);

                break;
            }
        }
    }
    this->registarTrabalhadores();

    deleteFileData("../trabalhadores.dat");

    for (auto trabalhador : this->contratacoes) {
        this->updateTrabalhadores(trabalhador);
    }
}

HashTableTrabalhadores
Cinemateca::getRegistoTrabalhadores() {
    return this->registoTrabalhadores;
}

RegistoTrabalhador
Cinemateca::getRegisto(int pos) {
    RegistoTrabalhador rt;

    int i = 0;
    for (auto trabalhador : this->registoTrabalhadores) {
        if (i == pos) {
            rt = trabalhador;
            break;
        }
        i++;
    }

    return rt;
}

RegistoTrabalhador
Cinemateca::getRegisto(string nome) {
    return *this->registoTrabalhadores.find(nome);
}

void
Cinemateca::setContratacoes(const vector<Trabalhador *> v) {
    this->contratacoes = v;
}

// PARSING

void
Cinemateca::parseSalas(){
    salasDB = readFile("../salas.dat");
    salasData = parseFile(salasDB);

    list<Sala> parsedSalas;

    for (auto tuple : salasData){
        vector<string> data = split(tuple, ';');

        string nome = data[0];
        u_int capacidade = (u_int) stoi(data[1]);

        Sala novaSala(nome, capacidade);

        for (auto tuple : eventosData){
            vector<string> data = split(tuple, ';');

            if (stoi(data[6]) == stoi(nome)){
                string nome = data[0];
                u_int duracao = (u_int) stoi(data[3]);
                u_int lotMax = (u_int) stoi(data[4]);
                // float preco = stof(data[5]);
                float preco = 12.99;

                // parse date
                vector<string> dataEventoStr = split(data[1], '/');

                u_int d = (u_int) stoi(dataEventoStr[0]);
                u_int m = (u_int) stoi(dataEventoStr[1]);
                u_int a = (u_int) stoi(dataEventoStr[2]);

                Date dataEvento(d, m, a);

                // parse time
                vector<string> horaStr = split(data[2], ':');

                u_int h = (u_int) stoi(horaStr[0]);
                u_int min = (u_int) stoi(horaStr[1]);
                u_int s = (u_int) stoi(horaStr[2]);

                Time hora(h, min, s);

                Evento novoEvento(nome, dataEvento, hora, duracao, lotMax, preco);
                novaSala.adicionarEvento(novoEvento);
            }
        }

        parsedSalas.push_back(novaSala);
    }

    this->setSalas(parsedSalas);
}

void
Cinemateca::parseEventos(){
    eventosDB = readFile("../eventos.dat");
    eventosData = parseFile(eventosDB);

    ratingsDB = readFile("../satizfacao.dat");
    ratingsData = parseFile(ratingsDB);

    list<Evento> parsedEventos;
    map<string, float> parsedRatings;

    for (auto tuple : ratingsData) {
        vector<string> data = split(tuple, ';');

        string evento = data[0];
        float satizfacao = stof(data[1]);

        parsedRatings[evento] = satizfacao;
    }

    for (auto tuple : eventosData){
        vector<string> data = split(tuple, ';');

        string nome = data[0];
        u_int duracao = (u_int) stoi(data[3]);
        u_int lotMax = (u_int) stoi(data[4]);
        u_int sala = (u_int) stoi(data[6]);
        // float preco = stof(data[5]);
        float preco = 12.99;
        u_int bilhetesComprados = (u_int) stoi(data[7]);

        // parse date
        vector<string> dataEventoStr = split(data[1], '/');

        u_int dia = (u_int) stoi(dataEventoStr[0]);
        u_int mes = (u_int) stoi(dataEventoStr[1]);
        u_int ano = (u_int) stoi(dataEventoStr[2]);

        Date dataEvento(dia, mes, ano);

        // parse time
        vector<string> horaStr = split(data[2], ':');

        u_int h = (u_int) stoi(horaStr[0]);
        u_int m = (u_int) stoi(horaStr[1]);
        u_int s = (u_int) stoi(horaStr[2]);

        Time hora(h, m, s);

        Evento novoEvento(nome, dataEvento, hora, duracao, lotMax, preco, sala, bilhetesComprados);
        parsedEventos.push_back(novoEvento);
    }

    // popular fila de ratings da cinemateca
    for (auto evento : parsedEventos) {
        Evento* ptrEv = new Evento(evento.getNome(), evento.getData(), evento.getHora(), evento.getDuracao(), evento.getLotMax(), evento.getPreco(), evento.getSala(), evento.getBilhetesComprados());
        ItemEvento novoItem(ptrEv);
        novoItem.setSatizfacao(parsedRatings[evento.getNome()]);
        this->ratings.push(novoItem);
    }

    // popular lista de eventos da cinemateca
    this->setEventos(parsedEventos);
}

void
Cinemateca::parseAderentes(){
    aderentesDB = readFile("../aderentes.dat");
    aderentesData = parseFile(aderentesDB);

    list<Aderente> parsedAderentes;

    for (auto tuple : aderentesData){
        vector<string> data = split(tuple, ';');

        string nome = data[0];
        u_int nif = (u_int) stoi(data[1]);
        u_int anoAdesao = (u_int) stoi(data[3]);

        // parse date
        vector<string> dataNascStr = split(data[2], '/');

        u_int d = (u_int) stoi(dataNascStr[0]);
        u_int m = (u_int) stoi(dataNascStr[1]);
        u_int a = (u_int) stoi(dataNascStr[2]);

        Date dataNasc(d, m, a);

        Aderente novoAderente(nome, nif, dataNasc, anoAdesao);
        parsedAderentes.push_back(novoAderente);
    }

    this->setAderentes(parsedAderentes);
}

void
Cinemateca::parseNaoAderentes(){
    naoAderentesDB = readFile("../nao_aderentes.dat");
    naoAderentesData = parseFile(naoAderentesDB);

    list<Utilizador> parsedNaoAderentes;

    for (auto tuple : naoAderentesData){
        vector<string> data = split(tuple, ';');

        u_int nif = (u_int) stoi(data[0]);

        Utilizador novoUtilizador(nif);
        parsedNaoAderentes.push_back(novoUtilizador);
    }

    this->setNaoAderentes(parsedNaoAderentes);
}


void
Cinemateca::parseTrabalhadores() {
    trabalhadoresDB = readFile("../trabalhadores.dat");
    trabalhadoresData = parseFile(trabalhadoresDB);

    vector<Trabalhador *> tmp;

    for (auto tuple : trabalhadoresData) {
        vector<string> data = split(tuple, ';');
        string n = data[0], l = data[1];
        vector<string> dataC = split(data[2], '/'), dataD = split(data[3], '/');

        u_int d1 = (u_int) stoi(dataC[0]);      u_int d2 = (u_int) stoi(dataD[0]);
        u_int m1 = (u_int) stoi(dataC[1]);      u_int m2 = (u_int) stoi(dataD[1]);
        u_int a1 = (u_int) stoi(dataC[2]);      u_int a2 = (u_int) stoi(dataD[2]);

        Date dataCont(d1, m1, a1), dataDesp(d2, m2, a2);
        bool atual = dataDesp.undefined();

        Trabalhador* t = new Trabalhador(n, l, dataCont, dataDesp, atual);
        tmp.push_back(t);
    }

    this->setContratacoes(tmp);
}


// UPDATE

void
Cinemateca::updateAderentes(Aderente aderente) const {
    string data = "";

    data += aderente.getNome() + "; " + to_string(aderente.getNif()) + "; "
         + to_string(aderente.getDataNasc().getD()) + "/" + to_string(aderente.getDataNasc().getM()) + "/" + to_string(aderente.getDataNasc().getA()) + "; "
         + to_string(aderente.getAnoAdesao());

    writeData(data, "../aderentes.dat");
}

void
Cinemateca::updateNaoAderentes(Utilizador naoAderente) const {
    string data = "";

    data += to_string(naoAderente.getNif());

    writeData(data, "../nao_aderentes.dat");
}

void
Cinemateca::updateEventos(Evento evento) const {
    string data = "";

    data += evento.getNome() + "; "
         + to_string(evento.getData().getD()) + "/" + to_string(evento.getData().getM()) + "/" + to_string(evento.getData().getA()) + "; "
         + to_string(evento.getHora().getH()) + ":" + to_string(evento.getHora().getM()) + ":" + to_string(evento.getHora().getS()) + "; "
         + to_string(evento.getDuracao()) + "; " + to_string(evento.getLotMax()) + "; " + to_string(evento.getPreco()) + "; "
         + to_string(evento.getSala()) + to_string(evento.getBilhetesComprados());


    writeData(data, "../eventos.dat");
}

void
Cinemateca::updateTrabalhadores(Trabalhador* trabalhador) const {
    string data = "";

    data += trabalhador->getNome() + "; "
         + trabalhador->getLocalizacao() + "; "
         + to_string(trabalhador->getDataContatacao().getD()) + "/" + to_string(trabalhador->getDataContatacao().getM()) + "/" + to_string(trabalhador->getDataContatacao().getA()) + "; "
         + to_string(trabalhador->getDataDespedimento().getD()) + "/" + to_string(trabalhador->getDataDespedimento().getM()) + "/" + to_string(trabalhador->getDataDespedimento().getA());

    writeData(data, "../trabalhadores.dat");
}

void
Cinemateca::updateRatings(ItemEvento item) const {
    string data = "";

    data += item.getEvento()->getNome() + "; "
         + to_string(item.getSatizfacao());

    writeData(data, "../satizfacao.dat");
}

void
Cinemateca::updateBilhetesComprados(){
    this->bilhetesComprados++;
}

void
Cinemateca::updateTotalVendas(const float valor){
    this->totalVendas += (double) valor;
}

// ORDENAR SALAS

void
Cinemateca::ordenarSalasNome(){
    this->salas.sort();
}

void
Cinemateca::ordenarSalasCapacidade(){
    this->salas.sort([](const Sala& s1, const Sala& s2){
        return s1.getCapacidade() < s2.getCapacidade();
    });
}

// ORDENAR EVENTOS

void
Cinemateca::ordenarEventosNome(){
    this->eventos.sort();
}

void
Cinemateca::ordenarEventosData(){
    this->eventos.sort([](const Evento& e1, const Evento& e2){
        return e1.getData() < e2.getData();
    });
}

void
Cinemateca::ordenarEventosPreco(){
    this->eventos.sort([](const Evento& e1, const Evento& e2){
        return e1.getPreco() < e2.getPreco() ;
    });
}

void
Cinemateca::ordenarEventosLotMax(){
    this->eventos.sort([](const Evento& e1, const Evento& e2){
        return e1.getLotMax() < e2.getLotMax() ;
    });
}

// ORDENAR ADERENTES

void
Cinemateca::ordenarAderentesNome(){
    this->aderentes.sort();
}

void
Cinemateca::ordenarAderentesDataNasc(){
    this->aderentes.sort([](const Aderente& a1, const Aderente& a2){
        return a1.getDataNasc() < a2.getDataNasc() ;
    });
}

void
Cinemateca::ordenarAderentesAnoAdesao(){
    this->aderentes.sort([](const Aderente& a1, const Aderente& a2){
        return a1.getAnoAdesao() < a2.getAnoAdesao() ;
    });
}












