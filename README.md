# Cinemateca Portuguesa

A Cinemateca Portuguesa pretende informatizar o sistema de compra de bilhetes para as sessões de cinema e eventos que promove, permitindo implementar descontos dedicados aos aderentes do Cartão Amigos da Cinemateca.
As instalações da Cinemateca estão localizadas nas cidades do Porto e de Lisboa. Sobre cada localização da Cinemateca o sistema deve guardar a morada, os eventos que promoveram nos últimos 12 meses e os aderentes associados à respectiva localização. Em relação aos aderentes, e de forma a garantir a emissão do Cartão Amigos da Cinemateca, é importante guardar o nome, NIF, data de nascimento e ano de adesão.

---

## Requisitos Parte 1

O sistema deve incluir e permitir gerir informação relativa aos eventos da Cinemateca planeados para os próximos 12 meses e deve permitir reservar bilhetes. Um evento é caracterizado por nome do evento, data e hora, duração, lotação máxima e preço do bilhete. A lotação máxima do evento pode ser pré definida (valor a atribuir quando da criação do evento) ou indefinida (valor=0, a ser determinado quando da alocação da sala).

Os aderentes do Cartão Amigos da Cinemateca contam com um desconto equivalente aos anos de adesão ao Cartão Cinemateca (num máximo de 15%) sobre o valor do bilhete de qualquer evento promovido pela Cinemateca Portuguesa.

A Cinemateca dispõe de um conjunto de salas disponíveis para a realização de um evento. Uma sala é caracterizada por nome, capacidade da sala, horário de ocupação/disponibilidade. Antes de iniciar a venda de bilhetes para qualquer evento, deve ser alocada uma sala. Se o evento já possui lotação máxima, deve ser escolhida a sala disponível nesse horário, de menor capacidade que seja suficiente para esse evento (capacidade_sala>= lotação_máxima_evento). Se o evento possui lotação indefinida, deve ser escolhida a sala disponível nesse horário de maior capacidade. Se não existir sala disponível, o evento não pode ser realizado.

Numa estratégia conjunta com a Câmara Municipal do Porto, foi decidido avançar com a opção de permitir que aderentes com residência na cidade do Porto e com mais de 65 anos assistam sem qualquer custo a eventos a realizar-se nas instalações da Cinemateca na cidade do Porto. Esta opção apenas é acionada caso, faltando menos do que 8 horas para o início do evento, ainda não tenham sido vendidos mais do que 50% dos bilhetes disponíveis para o mesmo. Nesse caso, os aderentes 65+ recebem uma mensagem com esta informação e podem aceitar ou não assistir ao evento.

Pretende-se monitorar informação sobre os eventos existentes (bilhetes comprados, valor das vendas dos bilhetes), clientes (compra de bilhetes, descontos) e salas.

---

## Requisitos Parte 2

Complemente o sistema já implementado com as seguintes funcionalidades:

* De forma a direcionar as campanhas de marketing, mas também a melhorar os serviços prestados aos seus
associados, a Cinemateca pretende manter um registo das sessões de cinema e outros eventos nos quais
os aderentes ao Cartão Amigos da Cinemateca participaram. Guarde numa árvore binária de pesquisa os
eventos passados nos quais participaram os aderentes ao cartão, ordenados pelo número de aderentes que
participaram no evento e, em caso de empate, por ordem alfabética da localização. A identificação da
sessão deve incluir a localização da mesma. Devem ser permitidas listagens várias, tirando partido da
ordenação da árvore.

* A Cinemateca Portuguesa pretende aumentar o número de espectadores e, para tal, pretende avaliar a
satisfação dos participantes com as sessões e eventos que promove. A satisfação dos participantes é
avaliada através de rankings atribuídos pelos aderentes aos eventos: 1- avaliação muito negativa; 5 –
avaliação muito positiva.Para tal, pretende guardar numa fila de prioridade os rankings dos eventos
exibidos nos últimos 12 meses ordenados pelo grau de satisfação dos aderentes ao Cartão Amigos e através
dos quais deve ser possível aceder aos eventos correspondentes. O ranking que está no topo é aquele que
reúne maior satisfação dos aderentes. Para planeamento de sessões futuras, a Cinemateca pretende poder
escolher o evento com um grau de satisfação superior e com o preço entre um dado valor máximo e mínimo
a especificar.

* A Cinemateca mantém um registo de todos os seus trabalhadores (atuais ou antigos) numa tabela de
dispersão. A manutenção do registo de trabalhadores antigos justifica-se porque, no caso de necessidade
de contratação de um novo trabalhador, a entidade tem como preferência a contratação de trabalhadores
já conhecidos. O trabalhador deve estar associado à localização em que trabalha (se é um trabalhador atual
da empresa). Devem ser permitidas listagens ou pesquisas de trabalhadores, a especificar.