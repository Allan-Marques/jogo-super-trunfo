# Logica-Super-Trunfo

Como Jogar
Configuração Inicial:

O jogo começa com dois jogadores. Cada jogador escolhe um nome.

Em seguida, as cartas do deck são embaralhadas aleatoriamente.

Distribuição das Cartas:

O deck é dividido igualmente entre os dois jogadores, ficando cada jogador com metade das cartas.

Escolhendo o Jogador Inicial:

Um sorteio é realizado para decidir qual jogador começa o jogo. A partir daí, os jogadores alternam as jogadas a cada rodada.

Atributos das Cartas:

Cada carta possui informações sobre uma cidade brasileira, incluindo:

Estado e código da cidade

Nome da cidade

População

Área

PIB (Produto Interno Bruto)

Número de pontos turísticos

Como Funciona uma Rodada:

A cada rodada, o jogador ativo vê sua carta e escolhe um dos atributos para comparar com a carta do oponente.

As opções de atributos são:

População

Área

PIB

Número de Pontos Turísticos

O jogador escolhe um atributo e revela as cartas. O jogador que tiver o valor mais alto no atributo escolhido vence a rodada.

Exemplo: Se o jogador escolher "População", o valor de população das cartas será comparado. Quem tiver o maior valor vence.

Vencedor da Rodada:

Se o jogador ativo vencer a rodada, ele ganha ambas as cartas e as coloca no final do seu deck.

Se o oponente vencer, ele ganha ambas as cartas.

Em caso de empate, ambas as cartas são recolocadas no final do respectivo deck.

Troca de Jogador:

Quando um jogador perde a rodada, o turno passa para o outro jogador.

Fim de Jogo:

O jogo continua até que um dos jogadores fique sem cartas. O vencedor será o jogador que tiver todas as cartas ou o jogador que tiver mais cartas ao final da partida.

Funções Importantes no Jogo
1. lerNomesJogadores:
kotlin
Copiar
- Essa função solicita que os jogadores insiram seus nomes no início do jogo.
2. sorteiaJogadorInicial:
css
Copiar
- Realiza um sorteio aleatório para determinar qual jogador começa.
3. embaralharCartas:
vbnet
Copiar
- As cartas são embaralhadas aleatoriamente para garantir a imprevisibilidade do jogo.
4. removeTopCard:
arduino
Copiar
- Remove a carta do topo do deck do jogador, essencial para o funcionamento das rodadas.
5. addCardToBottom:
cpp
Copiar
- Adiciona a carta ao final do deck do jogador após ganhar uma rodada ou em caso de empate.
6. exibirCartaComOpcoes:
csharp
Copiar
- Exibe as informações detalhadas da carta de um jogador, incluindo as opções de atributos para comparação.
7. lerEscolhaAtributo:
css
Copiar
- Recebe a escolha do jogador sobre qual atributo ele deseja usar para a comparação.
8. pausa:
css
Copiar
- Pausa a execução do jogo até que o jogador pressione a tecla Enter, permitindo que o jogador se prepare para a próxima rodada.
9. exibirTutorial:
csharp
Copiar
- Mostra as regras do jogo e como jogar antes de iniciar.
Considerações Finais
Rodadas e Estratégia: Cada rodada exige que os jogadores escolham o atributo que melhor se adapta à sua carta. Estratégias de escolha do atributo são essenciais, pois as cartas têm diferentes características de valores para cada atributo.

Empates: Empates são possíveis, e nesse caso, ambos os jogadores recolocam suas cartas no final do deck.

Final do Jogo: O jogo termina quando um jogador fica sem cartas, sendo o outro jogador declarado vencedor.

