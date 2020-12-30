#include "UI.h"

/*
 * Globals
 */

Cinemateca cinemateca("Porto", "Rua da Cinemateca, 632");


/*
 * Criação dinâmica de menus
 */

void
close(){
    cout << "\n\nPress ENTER to continue";
    int ch = getchar();

    if (ch == '\n')
        return;
    else
        cin.ignore(1000, '\n');
}

void
createMenu(string menuTitle, vector< pair<string, menuFunctionPtr> > menuItems){
    string errorMsg = "Invalid input: insert a value between 0 and " + to_string(menuItems.size()) + "\n";

    while (true){
        int option;

        cout << "\n ------ " << menuTitle << " ------\n  _\n |\n";

        for (int  i = 0; i < menuItems.size(); i++)
            cout << " | " <<  i + 1 <<  " - " << menuItems[i].first << "\n |\n";

        cout << " | 0 - Back\n |_\n\n----------------------------------------------- \n\n";

        option = getUnsignedIntInputInclusive(0, menuItems.size(), errorMsg);

        if (option == 0)
            break;
        else
            menuItems[option - 1].second();
    }
}

u_int
getUnsignedIntInputInclusive(u_int lowerBound, u_int higherBound, string errorMsg){
    int result;
    cin >> result;

    while (not cin.good() or result < lowerBound or result > higherBound){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << errorMsg << endl;
        cin >> result;
    }

    cin.ignore(1000, '\n');
    return result;
}


/*
 * Menus
 */

void
menuMain(){
    createMenu("Cinemateca Portuguesa - Main Menu", {
            {"Aderentes", menuAderentes},
            {"Eventos", menuEventos},
            {"Kiosk", menuKiosk},
            {"Recursos Humanos", menuRecursosHumanos},
            {"Markting", menuMarketing}
    });
}

void
menuAderentes(){
    createMenu("Cinemateca Portuguesa - Aderentes", {
            {"Registar Novo Aderente", viewRegistarAderente},
            {"Listar Aderentes", viewListarAderentes},
            {"Ordenar Aderentes", menuOrdenarAderentes},
            {"Apagar Registo do Aderente", viewApagarAderente}
    });
}

void
menuEventos(){
    createMenu("Cinemateca Portuguesa - Eventos", {
            {"Adicionar Evento", viewAdicionarEvento},
            {"Listar Eventos", viewListarEventos},
            {"Ordenar Eventos", menuOrdenarEventos},
            {"Apagar Evento", viewApagarEvento},
            {"Ratings", viewRatings},
            {"Pesquisar Evento com Maior Satizfacao", viewEventoMaiorSatisfacao}
    });
}

void
menuKiosk(){
    createMenu("Cinemateca Portuguesa - Kiosk", {
            {"Comprar Bilhete", viewComprarBilhetes},
            {"Ver Bilhetes Comprados", viewBilhetesComprados},
            {"Ver Valor das Vendas", viewValorDeVendas}
    });
}

void
menuRecursosHumanos() {
    createMenu("Cinemateca Portuguesa - Recursos Humanos", {
            {"Pesquisar Trabalhador", viewPesquisarTrabalhador},
            {"Contratar Trabalhador", viewContratarTrabalhador},
            {"Listar Trabalhadores", viewListarTrabalhadores},
            {"Listar Ex-trabalhadores", viewListarExTrabalhadores}
    });
}

void
menuMarketing() {
    createMenu("Cinemateca Portuguesa - Marketing", {
            {"Top 10 Bilheteira", viewTopBilheteira},
            {"Eventos Com Lotacao Maxima", viewEventosLotMax}
    });
}

void menuOrdenarAderentes() {
    createMenu("Cinemateca Portuguesa - Ordenar Aderentes", {
            {"Ordenar por Nome", funcOrdenarAderentesNome},
            {"Ordenar por Data de Nascimento", funcOrdenarAderentesDataNasc},
            {"Ordenar por Ano de Adesao", funcOrdenarAderentesAnoAdesao}
    });
}

void menuOrdenarEventos() {
    createMenu("Cinemateca Portuguesa - Ordenar Aderentes", {
            {"Ordenar por Nome", funcOrdenarEventosNome},
            {"Ordenar por Data", funcOrdenarEventosData},
            {"Ordenar por Preco", funcOrdenarEventosPreco}
    });
}


/*
 * Views
 */

// ADERENTE

void viewRegistarAderente() {
    try {
        string nome, dataStr;
        u_int nif;

        // input nome
        cout << "Nome completo: ";
        getline(cin, nome);
        cin.clear();
        cin.ignore(1000, '\n');

        // input nif
        cout << "NIF: ";
        cin >> nif;
        cin.clear();
        cin.ignore(1000, '\n');


        // input dataNasc
        bool dataInvalid = true;
        while (dataInvalid) {
            cout << "Data de nascimento (dd/mm/aaaa): ";
            cin >> dataStr;
            cin.clear();
            cin.ignore(1000, '\n');
            int found = dataStr.find('/');
            if (found >= dataStr.length()) {
                cout << "Formato de data invalido, por favor use dd/mm/aaaa como indicado" << endl;
            } else {
                dataInvalid = false;
            }
        }

        vector<string> dataArr = split(dataStr, '/');
        Date dataNasc(stoi(dataArr[0]), stoi(dataArr[1]), stoi(dataArr[2]));

        cinemateca.registarAderente(nome, nif, dataNasc, cinemateca.getAnoAtual());
    } catch (exception& e) {
        cout << endl << e.what() << endl << endl;
    }
}

void viewApagarAderente(){
    u_int nif;
    cout << "NIF: ";
    cin >> nif;
    cin.clear();
    cin.ignore(1000, '\n');

    cinemateca.apagarAderente(nif);

    cout << "Registo do aderente foi apagado com sucesso" << endl;
}

void viewListarAderentes() {
    cout << ">>> AMIGOS DA CINEMATECA <<<" << endl << endl;

    for (auto aderente : cinemateca.getAderentes())
        cout << aderente;
}


// TRABALHADOR

void viewListarTrabalhadores() {
    cout << ">>> TRABALHADORES DA CINEMATECA <<<" << endl << endl;

    vector<string> tmp;

    int i = 1;
    for (auto registo : cinemateca.getRegistoTrabalhadores()) {
        if (registo.getAtual()) {
            cout << i << ". " << registo.getTrabalhador() << endl;
            tmp.push_back(registo.getTrabalhador());
            i++;
        }
    }

    cout << "\n\n0. Back\n";

    string input;
    while (true) {
        cin >> input;
        if (stoi(input) >= 1 and stoi(input) <= i - 1) {
            int pos = stoi(input) - 1;
            string nomeTrabalhador = tmp[pos];
            viewMostrarTrabalhador(cinemateca.getRegisto(nomeTrabalhador));
            break;
        } else if (stoi(input) == 0) {
            menuRecursosHumanos();
            break;
        }
    }
}

void viewListarExTrabalhadores() {
    cout << ">>> EX TRABALHADORES DA CINEMATECA <<<" << endl << endl;

    vector<string> tmp;

    int i = 1;
    for (auto registo : cinemateca.getRegistoTrabalhadores()) {
        if (!registo.getAtual()) {
            cout << i << ". " << registo.getTrabalhador() << endl;
            tmp.push_back(registo.getTrabalhador());
            i++;
        }
    }

    cout << "\n\n0. Back\n";

    string input;
    while (true) {
        cin >> input;
        if (stoi(input) >= 1 and stoi(input) <= i - 1) {
            int pos = stoi(input) - 1;
            string nomeTrabalhador = tmp[pos];
            viewMostrarTrabalhador(cinemateca.getRegisto(nomeTrabalhador));
            break;
        } else if (stoi(input) == 0) {
            menuRecursosHumanos();
            break;
        }
    }
}

void viewMostrarTrabalhador(RegistoTrabalhador registo) {
    cout << "\n------------------------------------------\n\n"
         << "Informacoes do trabalhador: \n\n"
         << registo;

    string input;

    if (registo.getAtual()) {
        cout << "1. Despedir"
             << "\t0. Back\n";

        while (true) {
            cin >> input;
            if (input == "1") {
                cinemateca.despedirTrabalhador(registo.getTrabalhador());
                cout << "\n--- Trabalhador despedido ---\n\n";
                viewListarTrabalhadores();
                break;
            } else if (input == "0") {
                viewListarTrabalhadores();
                break;
            }
        }

    } else {
        cout << "1. Contratar"
             << "\t0. Back\n";

        while (true) {
            cin >> input;
            if (input == "1") {
                cinemateca.contratarTrabalhador(registo.getTrabalhador());
                cout << "\n--- Trabalhador contratado ---\n";
                viewListarExTrabalhadores();
                break;
            } else if (input == "0") {
                viewListarExTrabalhadores();
                break;
            }
        }
    }
}

void viewPesquisarTrabalhador() {
    cout << ">>> PESQUISAR TRABALHADOR <<<" << endl << endl;

    string input;

    while (true) {
        cout << "\n0. Back\n";
        cout << "\npesquisar: ";

        getline(cin, input);
        cin.clear();
        cin.ignore(1000, '\n');

        if (input == "0") {
            menuRecursosHumanos();
            break;
        }

        auto registo = cinemateca.getRegistoTrabalhadores().find(input);
        if (registo != cinemateca.getRegistoTrabalhadores().end()) {
            viewMostrarTrabalhador(*registo);
            break;
        } else {
            cout << "\n--- Trabalhador não encontrado ---\n";
        }
    }
}

void viewContratarTrabalhador() {
    cout << ">>> CONTRATAR TRABALHADOR <<<" << endl << endl;

    string input;

    while (true) {
        cout << "\n0. Back\n";
        cout << "\nNome: ";

        getline(cin, input);
        cin.clear();
        cin.ignore(1000, '\n');

        if (input == "0") {
            menuRecursosHumanos();
        }

        auto registo = cinemateca.getRegistoTrabalhadores().find(input);
        if (registo == cinemateca.getRegistoTrabalhadores().end()) {
            cinemateca.contratarTrabalhador(input);
            cout << "\n--- Trabalhador contratado com sucesso! ---\n";
            menuRecursosHumanos();
            break;
        } else {
            if (registo->getAtual()) {
                cout << "\n--- Trabalhador ja esta atualmente contratado. ---\n";
            } else {
                cinemateca.contratarTrabalhador(input);
                cout << "\n--- Trabalhador contratado com sucesso! ---\n";
                menuRecursosHumanos();
                break;
            }
        }
    }
}


// HISTORICO

void viewTopBilheteira() {
    cout << ">>> EXITOS DE BILHETEIRA <<<" << endl << endl;

    int i = 1;
    for (auto item : cinemateca.getExitosBilheteira()) {
        cout << i << ". " << item.getNome() << " - " << item.getBilhetesComprados() << " bilhetes vendidos" << endl;
        i++;
    }

    string input;
    while (true) {
        cout << "\n0. Back\n";
        cin >> input;

        if (input == "0") {
            menuMain();
            break;
        }
    }
}

void viewEventosLotMax() {
    cout << ">>> EVENTOS COM LOTACAO MAXIMA <<<" << endl << endl;

    int i = 1;
    for (auto item : cinemateca.getEventosLotMax()) {
        cout << i << ". " << item.getNome() << " - " << item.getBilhetesComprados() << " bilhetes vendidos" << endl;
        i++;
    }

    string input;
    while (true) {
        cout << "\n0. Back\n";
        cin >> input;

        if (input == "0") {
            menuMain();
            break;
        }
    }
}


// EVENTO

void viewAdicionarEvento() {
    try {
        string nome, dataStr, horaStr;
        u_int duracao, lotMax;
        float preco;

        // input nome
        cout << "Nome do evento: ";
        getline(cin, nome);
        cin.clear();
        cin.ignore(1000, '\n');

        // input data
        cout << "Data (dd/mm/aa): ";
        cin >> dataStr;
        cin.clear();
        cin.ignore(1000, '\n');

        vector<string> dataArr = split(dataStr, '/');
        Date data(stoi(dataArr[0]), stoi(dataArr[1]), stoi(dataArr[2]));

        // input hora
        cout << "Hora (hh:mm:ss): ";
        cin >> horaStr;
        cin.clear();
        cin.ignore(1000, '\n');

        vector<string> horaArr = split(horaStr, ':');
        Time hora(stoi(horaArr[0]), stoi(horaArr[1]), stoi(horaArr[2]));

        // input duracao
        cout << "Duracao: ";
        cin >> duracao;
        cin.clear();
        cin.ignore(1000, '\n');

        // input lotMax
        cout << "Lotacao maxima: ";
        cin >> lotMax;
        cin.clear();
        cin.ignore(1000, '\n');

        // input preco
        cout << "Preco: ";
        cin >> preco;
        cin.clear();
        cin.ignore(1000, '\n');

        cinemateca.adicionarEvento(nome, data, hora, duracao, lotMax, preco);
    } catch (exception& e) {
        cout << endl << e.what() << endl << endl;
    }
}

void viewApagarEvento(){
    try {
        string nome;
        cout << "Nome do evento que quer apagar: ";
        getline(cin, nome);
        cin.clear();
        cin.ignore(1000, '\n');

        cinemateca.removerEvento(nome);

        cout << "\n----- Evento removido com sucesso -----\n";
    } catch (exception& e) {
        cout << endl << e.what() << endl << endl;
    }
}

void viewListarEventos() {
    cout << ">>> EVENTOS <<<" << endl << endl;

    int i = 1;
    for (auto evento : cinemateca.eventos){
        cout << i << ". " << evento.getNome() << endl;
        i++;
    }

    string input;

    while (true){
        cin >> input;

        if (stoi(input) >= 1 and stoi(input) <= i - 1){
            int pos = stoi(input) - 1;
            viewMostrarEvento(cinemateca.getEvento(pos));

            break;
        }
    }
}

void
viewMostrarEvento(Evento evento){
    cout << "\n------------------------------------------\n\n"
         << "Informacoes do evento: \n\n"
         << evento;

    cout << "Lista de participantes: \n";
    for (auto participante : evento.getParticipantes())
        cout << participante.getNif() << endl;

    cout << "\nSala: ";
    for (auto sala : cinemateca.getSalas()){
        for (auto eventoSala : sala.getEventos()){
            if (eventoSala == evento)
                cout << sala << endl;
        }
    }

    cout << "Bilhetes comprados: " << evento.getBilhetesComprados() << endl;
    cout << "Total de Vendas: " << evento.getTotalVendas() << " euros\n";

    cout << "\n0. Continuar \t1. Atribuir Satizfacao\n";

    u_int input;
    while (true) {
        cin >> input;
        if (input == 1) {
            viewAtribuirSatizfacao(evento.getNome());
            break;
        } else if (input == 0) {
            break;
        }
    }
}

void viewAtribuirSatizfacao(string evento) {
    u_int rating = 0;

    while (true) {
        try {
            cout << "Atribua um rating de 1 a 5: ";
            cin >> rating;

            if (rating >= 1 and rating <= 5) {
                cinemateca.atribuirRating(evento, rating);
                break;
            }
        } catch (exception& e) {
            cout << endl << e.what() << endl << endl;
        }
    }
}

void viewComprarBilhetes() {
    string input;

    cout << "Tem cartao Amigos da Cinemateca? (Y/N)\n";
    cin >> input;
    bool eventFound = false;
    if (input == "Y" or input == "y"){

        u_int nifIntroduzido;
        string nomeEvento;

        cout << "NIF: ";
        cin >> nifIntroduzido;

        cout << "Nome do Evento: ";
        cin >> nomeEvento;

        cout << endl;

        for (auto aderente : cinemateca.getAderentes()){
            if (aderente.getNif() == nifIntroduzido){
                list<Evento>::iterator it;
                for (it = cinemateca.eventos.begin(); it != cinemateca.eventos.end(); ++it){
                    if (it->getNome() == nomeEvento){
                        cinemateca.comprarBilhete(aderente, it);
                        eventFound = true;
                        break;
                    }
                }
                break;
            }
        }
        if(!eventFound){
            cout << "O nome do evento introduzido nao existe" << endl;
        }
    } else if (input == "N" or input == "n"){

        // Registar novo utilizador

        u_int nif;

        bool nifInvalid= true;
        while(nifInvalid){
            // input nif
            cout << "NIF: ";
            cin >> nif;
            cin.clear();
            cin.ignore(1000, '\n');
            if(to_string(nif).length() == 9){
                nifInvalid = false;
            }
            else{
                cout << "\nO NIF introduzido tem de ter 9 digitos\n";
            }
        }

        cinemateca.registarUtilizadorNaoAderente(nif);


        // Procurar Evento na Cinemateca

        string nomeEvento;

        cout << "Nome do Evento: ";
        cin >> nomeEvento;

        list<Evento>::iterator it;
        for (it = cinemateca.eventos.begin(); it != cinemateca.eventos.end(); ++it){
            if (it->getNome() == nomeEvento){
                Utilizador novoUtilizador(nif);
                cinemateca.comprarBilhete(novoUtilizador, it);
                eventFound = true;
                break;
            }
        }
        if(!eventFound){
            cout << "O nome do evento introduzido nao existe" << endl;
        }
    } else {
        return viewComprarBilhetes();
    }
}

void viewRatings() {
    cout << ">>> RATING DE SATIZFACAO <<<" << endl << endl;

    cout << "\tEvento - Rating\n\n";

    int i = 1;
    priority_queue<ItemEvento> ratingsCpy = cinemateca.getRatings();
    while (!ratingsCpy.empty()) {
        cout << i << ". " << ratingsCpy.top().getEvento()->getNome() << " - " << ratingsCpy.top().getSatizfacao() << endl;

        ratingsCpy.pop();
        i++;
    }

    string input;
    while (true){
        ratingsCpy = cinemateca.getRatings();
        cin >> input;

        if (stoi(input) >= 1 and stoi(input) <= i - 1){

            int j = 1;
            while (!ratingsCpy.empty()) {
                if (stoi(input) == j) {
                    viewMostrarEvento(*ratingsCpy.top().getEvento());
                    break;
                }
                j++;
                ratingsCpy.pop();
            }
            break;
        }
    }
}

void viewEventoMaiorSatisfacao() {
    cout << ">>> PESQUISAR EVENTO <<<" << endl << endl;

    string inputDataChao, inputDataTeto;

    while (true) {
        try {
            vector<string> arrData;

            cout << "Introduza data chao (dd/mm/aaaa): ";
            cin >> inputDataChao;
            arrData = split(inputDataChao, '/');
            Date dataChao((u_int) stoi(arrData[0]), (u_int) stoi(arrData[1]), (u_int) stoi(arrData[2]));

            cout << "Introduza data teto (dd/mm/aaaa): ";
            cin >> inputDataTeto;
            arrData = split(inputDataTeto, '/');
            Date dataTeto((u_int) stoi(arrData[0]), (u_int) stoi(arrData[1]), (u_int) stoi(arrData[2]));

            if (dataChao < dataTeto) {
                viewMostrarEvento(cinemateca.pesquisarEvento(dataChao, dataTeto));
                break;
            } else {
                cout << "\nData Chao deve ser anterior a Data Teto\n";
            }
        } catch (exception& e) {
            cout << endl << e.what() << endl << endl;
        }
    }
}

// BILHETES E VENDAS

void viewBilhetesComprados() {
    cout << "Bilhetes Comprados: " << to_string(cinemateca.getBilhetesComprados()) << endl;
}

void viewValorDeVendas() {
    cout << "Total de Vendas: " << to_string(cinemateca.getTotalVendas()) << " euros\n";
}


/*
 * Funções
 */

void
funcOrdenarAderentesNome(){
    cinemateca.ordenarAderentesNome();
}

void
funcOrdenarAderentesDataNasc(){
    cinemateca.ordenarAderentesDataNasc();
}

void
funcOrdenarAderentesAnoAdesao(){
    cinemateca.ordenarAderentesAnoAdesao();
}

void
funcOrdenarEventosNome(){
    cinemateca.ordenarEventosNome();
}

void
funcOrdenarEventosData(){
    cinemateca.ordenarEventosData();
}

void
funcOrdenarEventosPreco(){
    cinemateca.ordenarEventosPreco();
}

