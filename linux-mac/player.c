#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Card.h"
#include "player.h"
#define gotoxy(x,y) printf("\033[%d;%dH", (y) , (x))

struct player{
    char nome[20];
    Card cards[5];
    int ncards;
};

//Função para criar um jogador
Player newPlayer(char *nomeN){
    Player p = (Player) malloc(sizeof(struct player));
    int i = 0;
	if (p){
		for (i = 0; i < 5; i++) {
			p->cards[i] = NULL;
		}
		strcpy(p->nome, nomeN);
		p->ncards = 5;
	}
    return p;
}

//Função para obter uma carta do jogador
Card getCard(Player p, int i){
    return p->cards[i];
}

//Função para obter as cartas do jogador
Card* getCards(Player p){
    return p->cards;
}

//Função para obter e retirar uma carta do jogador
Card grCard(Player j, int i){
    Card aux = j->cards[i];
    j->cards[i] = NULL;
    return aux;
}

//Função para obter o tamanho do nome do jogador
int tamNpl(Player p){
    return strlen(p->nome);
}

//Função que faz o jogador escolher um numero para dar a dica
int selNum(Player p, int play){
    int n = 0;
    int i = 0;
    int arr[5];
    int j = 0;
    char val = 0;
    //Guarda os numeros disponiveis sem repetição
    for (i = 0; i < p->ncards; i++){
        if(checkNum( ( (char) getCnum(p->cards[i]) + 48 ), arr, j ) || i == 0){
            arr[j] = getCnum(p->cards[i]);
            j++;
        }
    }

    //Ordena os numeros disponiveis para dicas
    quickSort(arr, 0, j-1);

    //Perguntar qual é o numero que o utilizador deseja indicar
    gotoxy(0, 18);
    printf("                                       ");
    gotoxy(0, 18);
    printf("Qual e o numero que quer indicar?");
    gotoxy(0, 19);
    printf("                                       ");
    gotoxy(0, 19);
    printf("Numero: %d", arr[0]);
    for (i = 1; i < j; i++){
        printf(" %d", arr[i]);
    }
    gotoxy(0, 20);
    printf("                                       ");
    gotoxy(0, 20);
    printf("0 - Voltar para o menu");
    gotoxy(0, 21);
    printf("                                       ");
    gotoxy(0, 21);
    printf("->");
    gotoxy(0, 22);
    printf("                                       ");
    gotoxy(0, 23);
    printf("                                       ");
    gotoxy(3, 21);
    val = getchar();
    while (getchar()!='\n');

    while ((checkNum(val, arr, j))){
        
        gotoxy(0, 18);
        printf("                                       ");
        gotoxy(0, 18);
        printf("Esse numero não existe!!!\n");
        gotoxy(0, 19);
        printf("                                       ");
        gotoxy(0, 19);
        printf("Qual e o numero que quer indicar?");
        gotoxy(0, 20);
        printf("                                       ");
        gotoxy(0, 20);
        printf("Numero: %d", arr[0]);
        for (i = 1; i < j; i++){
            printf(" %d", arr[i]);
        }
        gotoxy(0, 21);
        printf("                                       ");
        gotoxy(0, 21);
        printf("0 - Voltar para o menu");
        gotoxy(0, 22);
        printf("                                       ");
        gotoxy(0, 22);
        printf("->");
        gotoxy(0, 23);
        printf("                                       ");
        gotoxy(3, 22);
        val = getchar();
        while (getchar()!='\n');
    }
    
    if (((int)val)-48){
        giveTipN(p->cards, ((int)val)-48);//Função que atribui a dica à carta correspondente
        return (((int)val)-48);
    }
    else{
        return 0;
    }
    
    
}

//Função que faz o jogador escolher uma cor para dar a dica
int selCor(Player p, int play){
    int n = 0;
    int i = 0;
    char arr[5];
    int j = 0;
    char val = 0;
    //Armazena as letras disponiveis sem ter repetidas
    for (i = 0; i < p->ncards; i++){
        if(checkChar(getCc(p->cards[i]), arr, j) || i == 0){
            arr[j] = getCc(p->cards[i]);
            j++;
        }
    }

    //Perguntar qual é a cor que o utilizador deseja indicar
    gotoxy(0, 18);
    printf("                                       ");
    gotoxy(0, 18);
    printf("Qual e o cor que quer indicar?");
    gotoxy(0, 19);
    printf("                                       ");
    gotoxy(0, 19);
    printf("Cor: %c", arr[0]);
    for (i = 1; i < j; i++){
        printf(" %c", arr[i]);
    }
    gotoxy(0, 20);
    printf("                                       ");
    gotoxy(0, 20);
    printf("0 - Voltar para o menu");
    gotoxy(0, 21);
    printf("                                       ");
    gotoxy(0, 21);
    printf("->");
    gotoxy(0, 22);
    printf("                                       ");
    gotoxy(0, 23);
    printf("                                       ");
    gotoxy(4, 21);
    val = getchar();
    while (getchar()!='\n');

    val = toupper(val);
    
    while (checkChar(val, arr, j)){

        gotoxy(0, 18);
        printf("                                       ");
        gotoxy(0, 18);
        printf("Essa cor não existe!!!\n");
        gotoxy(0, 19);
        printf("                                       ");
        gotoxy(0, 19);
        printf("Qual e o cor que quer indicar?\n");
        gotoxy(0, 20);
        printf("                                       ");
        gotoxy(0, 20);
        printf("Cor: %c", arr[0]);
        for (i = 1; i < j; i++){
            printf(" %c", arr[i]);
        }
        gotoxy(0, 21);
        printf("                                       ");
        gotoxy(0, 21);
        printf("0 - Voltar para o menu");
        gotoxy(0, 22);
        printf("                                       ");
        gotoxy(0, 22);
        printf("->");
        gotoxy(0, 23);
        printf("                                       ");
        gotoxy(4, 22);
        val = getchar();
        while (getchar()!='\n');
        val = toupper(val);
    }

    if (val != '0'){
        giveTipC(p->cards, val);//Função que atribui a dica à carta correspondente
        return (((int)val)-48);
    }
    else{
        return 0;
    }
    
}

//retorna o numero de cartas de um jogador
int getNCP(Player p){
    return p->ncards;
}

//Função para obter a menor carta do jogador sem que o jogador não informação
int getLowerCard(Player p){
    int i = 0;
    int min = -1;
    int pos = -1;
    Card c = NULL;
    for (i = 0; i < getNCP(p); i++){
        c = getCard(p, i);
        if (c != NULL){
            if (((getCnum(c) < min) && getCvn(c) == 0) || (min == -1 && getCvn(c) == 0)){
                min = getCnum(c);
                pos = i;
            }
        }
    }
    return pos;
}

//Verifica se a carta é unica no numero ou cor
int cardsAlone(Player p, int num, char cor){
    int i = 0;
    int Ncolors[5] = {0, 0, 0, 0, 0};
    int Nnum = 0;
    int Ncor = 0;
    for (i = 0; i < getNCP(p); i++){
        if (getCard(p, i) != NULL){
            if(getCc(getCard(p, i)) == cor)
                Ncor++;
            if (getCnum(getCard(p, i)) == num)
                Nnum++;
        }
    }
    return (Ncor == 1 && Nnum == 1) ? 3 : (Ncor == 1 && Nnum != 1) ? 2 : (Ncor != 1 && Nnum == 1) ? 1 : 0;
}

//Função para trocar inteiros num array
void swapN(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//Função do quick sort
int partition (int *arr, int low, int high){
    // pivot (Element to be placed at right position)
    int pivot = arr[high];
 
    int i = (low - 1);  // Index of smaller element
    int j = 0;
    for (j = low; j <= high - 1; j++){
        // If current element is smaller than the pivot
        if (arr[j] <= pivot){
            i++;    // increment index of smaller element
            swapN(&arr[i], &arr[j]);
        }
    }
    swapN(&arr[i + 1], &arr[high]);
    return (i + 1);
}

//Função do quick sort
void quickSort(int *arr, int low, int high){
    if (low < high){
        /* pi is partitioning index, arr[pi] is now
        at right place */
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);  // Before pi
        quickSort(arr, pi + 1, high); // After pi
    }
}

//Função para obter o nome do jogador
char *getnome(Player p){
    return (p->nome);
}

//Jogar uma carta para a mesa
int playCard(Pilha pi, Player p, int posC, int np){
    int i = 0;
    int f = 0;
    int haveColor = 0;
    for (i = 0; (i < np) && !f; i++){
        if (compareCardC(getCpilha(pi, i), p->cards[posC])){
            haveColor = 1;
            if (compareCardN(getCpilha(pi, i), p->cards[posC]))
                f = 1;
        }
    }

    if ((haveColor == 0) && (getCnum(p->cards[posC]) == 1)){
        f = 1;
    }
    
    return f;
}

//Atribuir o nome a um jogador
void setNPlayer(Player p, char* nomeN){
    strcpy(p->nome, nomeN);
}

//Atribuir o numero de cartas que um jogador tem
void setNCplayer(Player p, int ncrds){
    p->ncards = ncrds;
}

//Função para atribuir uma carta a um jogador
void setCPlayer(Player p, Card c, int i){
    p->cards[i] = c;
}

//Puxa as cartas para a mão esquerda do jogador
void pushToLeft(Player p){
    int i = 0;
    for (i = 0; i < p->ncards; i++){
        if (p->cards[i] == NULL){
            p->cards[i] = p->cards[i+1];
            p->cards[i+1] = NULL;
        }
    }
}

//decrementa a variavel que contem o numero de cartas do jogador
void lessCardsP(Player p){
    p->ncards--;
}

//incrementa a variavel que contem o numero de cartas do jogador
void plusCardsP(Player p){
    p->ncards++;
}

//Função para definir todas as cores do jogador visiveis
void setAllVisCP(Player p){
    int i = 0;
    for (i = 0; i < 5; i++){
        if (p->cards[i] != NULL){
            setAllVisCC(p->cards[i]);
        }
    }
}

//Função para definir todas os numeros do jogador visiveis
void setAllVisNP(Player p){
    int i = 0;
    for (i = 0; i < 5; i++){
        if (p->cards[i] != NULL){
            setAllVisNC(p->cards[i]);
        }
    }
}

//Função que arrasta todas as cartas para a direita e adicona a nova carta na primeira posição
void pickCard(Player p, Card cardN){
    int i;
    int pos = 0;
    
    for(i = 4; i > 0; i--){
        if(p->cards[i] == NULL){
            p->cards[i] = setCardpos(p->cards[i - 1], i);
            p->cards[i - 1] = NULL;
        }
    }
    
    p->cards[0] = setCardpos(cardN, 0); //pega numa carta do Deck
}

//Função que distribui cartas para os jogadores antes de começar o jogo
void dealCards(Player jog, Player ai, Deck d, int *nc){
    int i = 0;
    time_t t;
    srand((unsigned) time(&t));
    int n = rand() % 2;
    for (i = 0; i < 5; i++){
        if(n == 0){
            ai->cards[i] = setCardpos(getCa(d, *nc), i);
            DeckNull(d, *nc);
            (*nc)--;
            jog->cards[i] = setCardpos(getCa(d, *nc), i);
            DeckNull(d, *nc);
            (*nc)--;
            n = 1;
        }
        else{
            jog->cards[i] = setCardpos(getCa(d, *nc), i);
            DeckNull(d, *nc);
            (*nc)--;
            ai->cards[i] = setCardpos(getCa(d, *nc), i);
            DeckNull(d, *nc);
            (*nc)--;
            n = 0;
        }
    }
    
}

//Função que imprime as cartas de um jogador(Debug)
void printCp(Player p){
    int i = 0;
    printf("Player: %s\nCards:\n", p->nome);
    for (i = 0; i < 5; i++){
        printf("Card %d - C: %c N: %d P: %d VC: %d VN: %d\n", i+1, getCc(p->cards[i]), getCnum(p->cards[i]), getCpos(p->cards[i]), getCvc(p->cards[i]), getCvn(p->cards[i]));
    }
}

//Função para libertar a memorio das variveis do tipo jogador
void freeP(Player p){
    int i = 0;
    for(i = 0; i < 5; i++){
        if(p->cards != NULL)
            free(p->cards[i]);
    }
    free(p);
}
