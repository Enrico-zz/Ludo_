#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Tamanho do tabuleiro
const int BOARD_SIZE = 57;
// Número de jogadores
const int NUM_PLAYERS = 4;
const int  NUM_PIECES = 4;
const int START_POSITIONS[] = {0, 0, 0, 0};
const char PLAYER1_NAME[] = {"RED"};
const char PLAYER2_NAME[] = {"GREEN"};
const char PLAYER3_NAME[] = {"YELLOW"};
const char PLAYER4_NAME[] = {"BLUE"};
int completelap = 0;

typedef struct {
    int position;
    int home;
    bool safe;
    bool finished;
} Piece;

typedef struct {
    bool hasFinished;
    Piece pieces[4];
} Player;

// Rolagem do dado
int rollDice() {
    return rand() % 6 + 1;
}
  //Função para mostrar o tabuleiro na tela
void printBoard(const Player players[],int numplayers, char PlayerName[][20]) {
    printf("=== Tabuleiro =================\n");
    for (int i = 0; i < numplayers; i++) {
        printf("Jogador %s:  ", PlayerName[i]);
        for (int j = 0; j < 4; j++) {
            if (players[i].pieces[j].finished) {
                printf("[F] ");
            } else {
                printf("[%d] ", players[i].pieces[j].position);
            }
        }
        printf("\n");
    }
    printf("===============================\n");
}
  //Função para verificar se o movimento é válido
bool isMoveValid(const Player *player, const Piece *piece, int newPosition, const Player players[], int currentPlayerIndex) {
    
  if ( currentPlayerIndex == 1) {
      if ( completelap == 1) {
        if ( newPosition > 31 && piece->finished == true ) {
           return false;  // Posição inválida
          }  else {
            return true;
              } 
      }  
  } 
      if (newPosition > BOARD_SIZE && piece->finished == true) {
        return false;  // Posição inválida
      }  else {
    return true;
        } 
    }

  // Função para mover a peça
void movePiece(Player *player, Piece *piece, int steps,  Player players[], int currentPlayerIndex, int numplayers, int pieceIndex, char PlayerName[][20]) {
    int currentPosition = piece->position;
    int newPosition = currentPosition + steps;
    int completelap = 0;
    
    if (isMoveValid(player, piece, newPosition, players, currentPlayerIndex)) {
        piece->position = newPosition;
        printf("== Seu peão foi para a casa %d ==\n\n", newPosition);
    } else {
      printf("== Jogada inválida, tire o número exato de casas para terminar o tabuleiro // Esta peça ja finalizou o jogo ==\n");
    }
  
    if (newPosition == 1 || newPosition == 9 || newPosition == 14 || newPosition == 22 || newPosition == 27 || newPosition == 35 || newPosition == 40 || newPosition == 48) {
        printf("O jogador %s está em um Safe Point\n", PlayerName[currentPlayerIndex]);
      piece->safe = true;
    } else {
      piece->safe = false;
    }

  if ( currentPlayerIndex == 1) {
    if ( piece->position >= 52) {
       piece->position = newPosition - 52;
      completelap++;
    }
  }

  if ( newPosition == (players[(currentPlayerIndex + 1) % numplayers].pieces->position) && (players[(currentPlayerIndex + 1) % numplayers].pieces->safe != true)) {
    players[(currentPlayerIndex + 1) % numplayers].pieces->position = 0;
    completelap = 0;
    printf(" O jogador %s comeu uma peça do jogador %s\n",PlayerName[currentPlayerIndex], PlayerName[(currentPlayerIndex + 1) % numplayers] );
  }
  
}

  // Função para confirmar se o jogador ganhou
bool hasPlayerWon(const Player *player) {
    for (int i = 0; i < 4; i++) {
        if (!player->pieces[i].finished) {
            return false;  // Ainda há peças não terminadas
        }
    }
    return true;  // Todas as peças foram terminadas
}

int main() {
    Player players[4];
    char PlayerName[5][20];
    int numPlayers;
    int currentPlayer = 0;
    int diceRoll;

    strcpy(PlayerName[0], PLAYER1_NAME);
    strcpy(PlayerName[1], PLAYER2_NAME);
    strcpy(PlayerName[2], PLAYER3_NAME);
    strcpy(PlayerName[3], PLAYER4_NAME);
  
    srand(time(NULL));  // Inicializar semente aleatória

    printf("=== Bem-vindo ao jogo Ludo!! ===\n");
    printf("Selecione o número de jogadores (2 ou 4): ");
    scanf("%d", &numPlayers);

    if (numPlayers != 2 && numPlayers != 4) {
        printf("Número de jogadores inválido. O jogo será encerrado.\n");
        return 0;
    }

    // Inicializar jogadores e peças
    for (int i = 0; i < numPlayers; i++) {
        players[i].hasFinished = false;
        for (int j = 0; j < 4; j++) {
            players[i].pieces[j].position = START_POSITIONS[i];
            players[i].pieces[j].home = START_POSITIONS[i];
            players[i].pieces[j].safe = true;
            players[i].pieces[j].finished = false;
        }
    }

    // Loop principal do jogo
    while (true) {
      
      // Tabuleiro 
      printBoard(players,numPlayers,PlayerName);
      
      printf("=== Vez do jogador %s ====\n", PlayerName[currentPlayer]);
        printf("Pressione enter para lançar o dado.\n");
        getchar();

      // Lançar o dado
        diceRoll = rollDice();
        printf("== Você lançou o dado e obteve: %d ==\n", diceRoll);

      // Mover uma peça
      int pieceIndex;
      int numDice = 0;
      int option;

      if (diceRoll == 6) {
        while (diceRoll == 6) {
            if (numDice == 3) {
              break;
            }
        
        printf("== Digite 0 para colocar uma peça no tabuleiro ou 1 para mover uma: ");
        scanf("%d", &option);
        
        if (option == 0) {
            printf("== Digite o índice da peça que deseja iniciar no tabuleiro (0-3): ");
            scanf("%d", &pieceIndex);

            if (players[currentPlayer].pieces[pieceIndex].finished == true) {
              printf(" Esta peça já terminou o jogo, escolha outra para iniciar no tabuleiro");
              continue;
            }
          
            if (players[currentPlayer].pieces[pieceIndex].position != 0) {
                printf("== Peça já está no tabuleiro. Digite outro índice: \n");
                continue;
            } else {
              if (currentPlayer == 1) {
                players[currentPlayer].pieces[pieceIndex].position = 27;
              } else {
                players[currentPlayer].pieces[pieceIndex].position = 1;
                }
            }
        } else if (option == 1) {
            printf("== Digite o índice da peça que deseja mover (0-3): ");
            scanf("%d", &pieceIndex);
              if (players[currentPlayer].pieces[pieceIndex].position == 0 && completelap < 1) {
            printf("== Jogada inválida. Tire um 6 no dado para colocar esta peça no tabuleiro ==\n");
                continue;
              } else {
            movePiece(&players[currentPlayer], &players[currentPlayer].pieces[pieceIndex], diceRoll, players, currentPlayer, numPlayers,pieceIndex, PlayerName);
              }
            
        } else {
            printf("== Número inválido. Digite novamente 0 ou 1 \n");
            continue;
        }
        
        printf("Pressione enter para lançar o dado novamente.\n");
        getchar();
        diceRoll = rollDice();
        printf("== Você lançou o dado e obteve: %d ==\n", diceRoll);
      if ( diceRoll != 6) {
            printf("== Digite o índice da peça que deseja mover (0-3): ");
            scanf("%d", &pieceIndex);
              if (players[currentPlayer].pieces[pieceIndex].position == 0 && completelap != 1) {
            printf("== Jogada inválida. Tire um 6 no dado para colocar esta peça no tabuleiro ==\n");
              } else {
            movePiece(&players[currentPlayer], &players[currentPlayer].pieces[pieceIndex], diceRoll, players, currentPlayer, numPlayers,pieceIndex, PlayerName);
                }
            continue;
      }
        numDice++;
    } 
} else {
    int numOfPiecesInGame = 0;
    for (int i = 0; i < 4; i++) {
        if (players[currentPlayer].pieces[i].position != 0 && completelap != 1) {
            numOfPiecesInGame++;
        } 
    }
    
    while (numOfPiecesInGame >= 1) {
        printf("== Digite o índice da peça que deseja mover (0-3): ");
        scanf("%d", &pieceIndex);
      if (pieceIndex >= 0 && pieceIndex < 4) {
        
        if (players[currentPlayer].pieces[pieceIndex].position == 0 ) {
            printf("== Jogada inválida. Tire um 6 no dado para colocar esta peça no tabuleiro ==\n");
          continue;
        } else {
            movePiece(&players[currentPlayer], &players[currentPlayer].pieces[pieceIndex], diceRoll, players, currentPlayer, numPlayers,pieceIndex, PlayerName);
        }
        
      } else {
        printf("== Índice inválido, digite 0 a 3: \n ");
        continue;
      }
      break;
    } if ( numOfPiecesInGame == 0 ) {
        printf(" ==== Passa a vez ====\n");
      }
    }
         
      if (currentPlayer == 1) {
            if ( completelap == 1) {
            // Verificar se a peça do jogador 2 terminou o jogo
            if (players[currentPlayer].pieces[pieceIndex].position == 31 ) {
                players[currentPlayer].pieces[pieceIndex].position = 0;
               players[currentPlayer].pieces[pieceIndex].finished = true;
              completelap = 0;
                printf("=== Player %s terminou uma peça! ===\n", PlayerName[currentPlayer]);
                // Verificar se o jogador terminou todas as peças
                if (hasPlayerWon(&players[currentPlayer])) {
                    players[currentPlayer].hasFinished = true;
                    printf("=== Player %s terminou todas as peças!!! ===\n", PlayerName[currentPlayer]);
                } else {
                  continue;
                }
            }
        } 
      } else {
          // Verificar se a peça do jogador 1 terminou o jogo
          if (players[currentPlayer].pieces[pieceIndex].position == BOARD_SIZE ) {
                players[currentPlayer].pieces[pieceIndex].position = 0;
               players[currentPlayer].pieces[pieceIndex].finished = true;
                printf("=== Player %s terminou uma peça! ===\n", PlayerName[currentPlayer]);
                // Verificar se o jogador terminou todas as peças
                if (hasPlayerWon(&players[currentPlayer])) {
                    players[currentPlayer].hasFinished = true;
                    printf("=== Player %s terminou todas as peças!!! ===\n", PlayerName[currentPlayer]);
                  }
          }
      }
      
      // Verificar se todos os jogadores terminaram o jogo
        bool allFinished = true;
        for (int i = 0; i < numPlayers; i++) {
            if (!players[i].hasFinished) {
                allFinished = false;
                break;
            }
        }

        // Verificar se o jogo acabou
        if (allFinished) {
            printf("!! O jogo acabou !!\n");
            break;
        }
      
        // Avançar para o próximo jogador
        currentPlayer = (currentPlayer + 1) % numPlayers;

        // Limpar o buffer de entrada
        while (getchar() != '\n');
    }
  
    return 0;
}
