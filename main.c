#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estruturas para Habilidades
struct Habilidade {
    char nome[50];
    char tipo[20];
    int poder;
};

struct NoHabilidade {
    struct Habilidade habilidade;
    struct NoHabilidade* proximo;
    struct NoHabilidade* anterior;
};

struct ListaHabilidades {
    struct NoHabilidade* cabeca;
};

// Estruturas para Personagens
struct Personagem {
    char nome[50];
    int forca;
    int agilidade;
    int inteligencia;
    int classe;
    struct ListaHabilidades habilidades; // Lista de habilidades do personagem
};

struct No {
    struct Personagem personagem;
    struct No* proximo;
};

struct ListaSimples {
    struct No* cabeca;
};

// FunÃ§Ãµes para manipulaÃ§Ã£o de lista de personagens
void inicializar_lista(struct ListaSimples* lista) {
    lista->cabeca = NULL;
}

void adicionar_personagem(struct ListaSimples* lista, struct Personagem personagem) {
    struct No* novo_no = (struct No*)malloc(sizeof(struct No));
    novo_no->personagem = personagem;
    novo_no->proximo = lista->cabeca;
    lista->cabeca = novo_no;
}

void liberar_lista(struct ListaSimples* lista) {
    struct No* atual = lista->cabeca;
    while (atual != NULL) {
        struct No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->cabeca = NULL;
}

void listar_personagens_lista(struct ListaSimples* lista) {
    struct No* atual = lista->cabeca;
    if (atual == NULL) {
        printf("\033[31mNenhum personagem na lista.\033[m\n");
        return;
    }

    // Array com o nome das classes
    char* nomes_classes[] = {
        "\033[36mMago\033[m",
        "\033[37mPaladino\033[m",
        "\033[33mGuerreiro\033[m",
        "\033[31mAssassino\033[m"
    };

    while (atual != NULL) {
        printf("\033[33mNome:\033[m %s, \033[35mForÃ§a:\033[m %d, \033[35mAgilidade:\033[m %d, \033[35mInteligÃªncia:\033[m %d, Classe: %s\n",
               atual->personagem.nome, atual->personagem.forca, atual->personagem.agilidade,
               atual->personagem.inteligencia, nomes_classes[atual->personagem.classe]);
        atual = atual->proximo;
    }
}

// FunÃ§Ã£o para mostrar sinopse
void mostrarSinopse(int indice) {
    char *sinopses[] = {
        "\033[34mMago: Mestre dos arcanos, o Mago manipula poderosas forÃ§as mÃ¡gicas para alterar a realidade...\033[m",
        "\033[37mPaladino: GuardiÃ£o da justiÃ§a, o Paladino Ã© um guerreiro sagrado que empunha espada e fÃ© em igual medida...\033[m",
        "\033[33mGuerreiro: Um combatente experiente, o Guerreiro Ã© versÃ¡til no campo de batalha...\033[m",
        "\033[31mAssassino: Silencioso e letal, o Assassino Ã© um mestre das sombras...\033[m"
    };

    if (indice >= 0 && indice < 4) {
        printf("%s\n", sinopses[indice]);
    } else {
        printf("\033[31mClasse invÃ¡lida!\033[m\n");
    }
}

// FunÃ§Ã£o para criar um personagem
struct Personagem criar_personagem() {
    struct Personagem personagem;
    
    // ValidaÃ§Ã£o do nome
    while (1) {
        printf("\033[33mDigite o nome do personagem:\033[m ");
        scanf(" %[^\n]", personagem.nome);
        int valido = 1;
        for (int i = 0; personagem.nome[i] != '\0'; i++) {
            if (!isalpha(personagem.nome[i]) && personagem.nome[i] != ' ') {
                valido = 0;
                break;
            }
        }
        if (valido) break;
        printf("\033[31mNome invÃ¡lido! Apenas letras e espaÃ§os sÃ£o permitidos. Tente novamente.\033[m\n");
    }

    // FunÃ§Ã£o auxiliar para leitura e validaÃ§Ã£o de atributos
   // FunÃ§Ã£o para validar se a entrada Ã© numÃ©rica
int validar_entrada_numerica(char entrada[]) {
    for (int i = 0; i < strlen(entrada); i++) {
        if (!isdigit(entrada[i])) {
            return 0; // Retorna 0 se encontrar algum caractere que nÃ£o seja um dÃ­gito
        }
    }
    return 1; // Retorna 1 se todos os caracteres forem dÃ­gitos
}

// FunÃ§Ã£o para ler um atributo do personagem com validaÃ§Ã£o
int ler_atributo(const char* nome_atributo) {
    char entrada[100];  // Buffer para armazenar a entrada do usuÃ¡rio como string
    int valor;

    do {
        printf("\033[32mDigite\033[m %s \033[32mdo personagem (1-10):\033[m ", nome_atributo);
        scanf("%s", entrada);  // LÃª a entrada como string

        // Verifica se a entrada Ã© numÃ©rica
        if (validar_entrada_numerica(entrada)) {
            valor = atoi(entrada);  // Converte a string para nÃºmero inteiro
            if (valor < 1 || valor > 10) {
                printf("\033[31mValor invÃ¡lido! %s \033[31mdeve estar entre 1 e 10.\033[m\n", nome_atributo);
            }
        } else {
            printf("\033[31mEntrada invÃ¡lida! Por favor, insira um nÃºmero entre 1 e 10.\033[m\n");
            valor = -1;  // Define valor invÃ¡lido para continuar o loop
        }

    } while (valor < 1 || valor > 10);  // Repete atÃ© receber um valor vÃ¡lido

    return valor;
}

    // Leitura e validaÃ§Ã£o de forÃ§a, agilidade e inteligÃªncia
    personagem.forca = ler_atributo("a FORÃ‡A\033[m");
    personagem.agilidade = ler_atributo("a AGILIDADE\033[m");
    personagem.inteligencia = ler_atributo("a INTELIGÃŠNCIA\033[m");

    // ValidaÃ§Ã£o da classe
    do {
        printf("\033[33mEscolha a classe do personagem:\033[m\n");
        printf("0. \033[36mMago\033[m\n");
        printf("1. \033[37mPaladino\033[m\n");
        printf("2. \033[33mGuerreiro\033[m\n");
        printf("3. \033[31mAssassino\033[m\n");
        printf("Digite o numero da classe (0 a 3): ");
        scanf("%d", &personagem.classe);
        if (personagem.classe < 0 || personagem.classe > 3) {
            printf("\033[31mClasse invÃ¡lida! Tente novamente.\033[m\n");
        }
    
   
    
        
    } while (personagem.classe < 0 || personagem.classe > 3);

    // Inicializa a lista de habilidades
    personagem.habilidades = (struct ListaHabilidades){ .cabeca = NULL };

    return personagem;
}

// FunÃ§Ãµes para manipulaÃ§Ã£o de habilidades
void inicializar_lista_habilidades(struct ListaHabilidades* lista) {
    lista->cabeca = NULL;
}

void adicionar_habilidade(struct ListaHabilidades* lista, struct Habilidade habilidade) {
    struct NoHabilidade* novo_no = (struct NoHabilidade*)malloc(sizeof(struct NoHabilidade));
    novo_no->habilidade = habilidade;
    novo_no->proximo = lista->cabeca;
    novo_no->anterior = NULL;

    if (lista->cabeca != NULL) {
        lista->cabeca->anterior = novo_no; // Ajustar o anterior do antigo cabeÃ§ote
    }
    lista->cabeca = novo_no; // Atualizar a cabeÃ§a da lista
}

void listar_habilidades_lista(struct ListaHabilidades* lista) {
    struct NoHabilidade* atual = lista->cabeca;
    if (atual == NULL) {
        printf("\033[31mNenhuma habilidade na lista.\033[m\n");
        return;
    }
    while (atual != NULL) {
        printf("\033[33mHabilidade:\033[m %s, Tipo: %s, Poder: %d\n",
               atual->habilidade.nome, atual->habilidade.tipo, atual->habilidade.poder);
        atual = atual->proximo;
    }
}

void liberar_lista_habilidades(struct ListaHabilidades* lista) {
    struct NoHabilidade* atual = lista->cabeca;
    while (atual != NULL) {
        struct NoHabilidade* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->cabeca = NULL;
}

struct Habilidade criar_habilidade() {
    struct Habilidade habilidade;
    int escolha;

    printf("\033[33mDigite o nome da habilidade:\033[m ");
    printf("\n1. \033[35mVeneno Mortal\033[m\n");
    printf("2. \033[35mNevasca\033[m\n");
    printf("3. \033[35mFÃºria Berserker\033[m\n");
    printf("4. \033[35mCura Divina\033[m\n");
    printf("Escolha uma das habilidades (1 a 4): ");
    scanf("%d", &escolha);
    switch (escolha) {
        case 1:
            strcpy(habilidade.nome, "\033[35mVeneno Mortal\033[m");
            strcpy(habilidade.tipo, "\033[34mDano\033[m");
            habilidade.poder = 50;
            break;
        case 2:
            strcpy(habilidade.nome, "\033[35mNevasca\033[m");
            strcpy(habilidade.tipo, "\033[34mMagia\033[m");
            habilidade.poder = 40;
            break;
        case 3:
            strcpy(habilidade.nome, "\033[35mFÃºria Berserker\033[m");
            strcpy(habilidade.tipo, "\033[34mFÃ­sico\033[m");
            habilidade.poder = 60;
            break;
        case 4:
            strcpy(habilidade.nome, "\033[35mCura Divina\033[m");
            strcpy(habilidade.tipo, "\033[34mCura\033[m");
            habilidade.poder = 30;
            break;
        default:
            printf("\033[31mOpÃ§Ã£o invÃ¡lida! Escolha uma habilidade vÃ¡lida.\033[m\n");
            break;
    }

    return habilidade;
}

void adicionar_habilidade_a_personagem(struct Personagem* personagem) {
    struct Habilidade nova_habilidade = criar_habilidade();
    adicionar_habilidade(&personagem->habilidades, nova_habilidade);
    printf("\033[32mHabilidade adicionada ao personagem!\033[m\n");
}


// FunÃ§Ã£o para ler um nÃºmero inteiro com validaÃ§Ã£o
int ler_inteiro() {
    int numero;
    if (scanf("%d", &numero) != 1) {
        while (getchar() != '\n'); // Limpa o buffer
        return -1;  // Retorna um valor invÃ¡lido se nÃ£o for um nÃºmero
    }
    return numero;
}

// FunÃ§Ã£o principal
int main() {
    struct Personagem personagens[50];
    int quantidade = 0;
    struct ListaSimples lista_personagens;
    inicializar_lista(&lista_personagens);
    int opcao;
    
    void exibirHistorico(struct Personagem personagens[], int quantidade) {
        if (quantidade == 0) {
            printf("\033[31mNenhum personagem foi criado ainda.\033[m\n");
        } else {
            for (int i = 0; i < quantidade; i++) {
                printf("\033[33mPersonagem %d:\033[m %s, ForÃ§a: %d, Agilidade: %d, InteligÃªncia: %d\n",  
                        i + 1, personagens[i].nome, personagens[i].forca, 
                        personagens[i].agilidade, personagens[i].inteligencia);
            }
        }
    }

    while (1) {
        printf("\n\033[32mMenu Principal\033[m\n");
        printf("1. \033[36mCriar Personagem\033[m\n");
        printf("2. \033[36mAdicionar Personagem Ã  Lista\033[m\n");
        printf("3. \033[36mVisualizar Personagens\033[m\n");
        printf("4. \033[36mVer Sinopse das Classes\033[m\n");
        printf("5. \033[36mAdicionar Habilidade ao Personagem\033[m\n");
        printf("6. \033[36mVer HistÃ³rico de Personagens\033[m\n");
        printf("7. \033[36mInventÃ¡rio\033[m\n");
        printf("8. \033[31mSair\033[m\n");
        printf("Escolha uma opcao: ");
         opcao = ler_inteiro();  // Usando a funÃ§Ã£o de leitura com validaÃ§Ã£o

        if (opcao == -1) {  // Caso a entrada seja invÃ¡lida
            printf("\033[31mEntrada invÃ¡lida! Por favor, insira um nÃºmero vÃ¡lido.\033[m\n");
            continue;  // Volta ao inÃ­cio do loop e mostra o menu novamente
        }
        
        if (opcao == 1) {
            struct Personagem novo_personagem = criar_personagem();
            if (quantidade < 50) {
                personagens[quantidade++] = novo_personagem;
                printf("\033[32mPersonagem criado com sucesso!\033[m\n");
                mostrarSinopse(novo_personagem.classe);
            } else {
                printf("\033[31mLimite de personagens atingido!\033[m\n");
            }
        } else if (opcao == 2) {
            if (quantidade > 0) {
                adicionar_personagem(&lista_personagens, personagens[quantidade - 1]);
                printf("\033[32mPersonagem adicionado Ã  lista com sucesso!\033[m\n");
            } else {
                printf("\033[31mNenhum personagem disponÃ­vel para adicionar!\033[m\n");
            }
        } else if (opcao == 3) {
            listar_personagens_lista(&lista_personagens);
        } else if (opcao == 4) {
            int classe;
            printf("\033[34mEscolha uma classe para ver a sinopse (0-3):\033[m ");
            scanf("%d", &classe);
            mostrarSinopse(classe);
        } else if (opcao == 5) {
            if (quantidade > 0) {
                int indice;
                printf("\033[35mEscolha o personagem para adicionar habilidade (%d a 50):\033[m ", quantidade - 1);
                scanf("%d", &indice);
                if (1<indice<50 && indice < quantidade) {
                    adicionar_habilidade_a_personagem(&personagens[indice]);
                } else {
                    printf("\033[31mPersonagem nÃ£o encontrado\033[m\n");
                }
            } else {
                printf("\033[31mNenhum personagem criado para adicionar habilidade.\033[m\n");
            }
        }else if (opcao == 6) {
            exibirHistorico(personagens, quantidade);
        }else if (opcao == 7) {
            typedef struct Item {
                char nome[30];
                struct Item* proximo;
            } Item;
            
         
            typedef struct Pilha {
                Item* topo;
            } Pilha;
            
            
            void inicializarPilha(Pilha* inventario) { inventario->topo = NULL; }
            
            void adicionarItem(Pilha* inventario, const char* nomeItem) {
                Item* novoItem = (Item*)malloc(sizeof(Item));
                strcpy(novoItem->nome, nomeItem);
                novoItem->proximo = inventario->topo;
                inventario->topo = novoItem;
                printf("\033[32mItem %s adicionado.\033[m\n", nomeItem);
            }
            
            void removerItem(Pilha* inventario) {
                if (inventario->topo) {
                    Item* temp = inventario->topo;
                    printf("\033[31mItem %s removido.\033[m\n", temp->nome);
                    inventario->topo = temp->proximo;
                    free(temp);
                } else {
                    printf("\033[31mInventÃ¡rio vazio!\033[m\n");
                }
            }
            
            void listarItens(Pilha* inventario) {
                Item* atual = inventario->topo;
                if (!atual) printf("\033[31mInventÃ¡rio vazio!\033[m\n");
                while (atual) {
                    printf("- %s\n", atual->nome);
                    atual = atual->proximo;
                }
            }
            
            // FunÃ§Ã£o para exibir lista de itens predefinidos
            void exibirItensDisponiveis() {
                printf("\n\033[33mEscolha um item para adicionar ao inventÃ¡rio:\033[m\n");
                printf("1. \033[34mEspada de Ferro\033[m\n");
                printf("2. \033[31mPoÃ§Ã£o de Cura\n\033[m");
                printf("3. \033[34mEscudo de Madeira\n\033[m");
                printf("4. \033[34mArco de CaÃ§a\033[m\n");
                printf("5. \033[34mArmadura de Couro\033[m\n");
                printf("OpÃ§Ã£o: ");
            }
            
            // FunÃ§Ã£o principal com menu
            
            Pilha inventario;
            inicializarPilha(&inventario);
            int opcao, itemEscolhido;
            char* itens[] = {"\033[34mEspada de Ferro\033[m", "\033[31mPoÃ§Ã£o de Cura\033[m",
             "\033[34mEscudo de Madeira\033[m", "\033[34mArco de CaÃ§a\033[m", "\033[34mArmadura de Couro\033[m"};
            
            do {
                printf("\n\033[32m1. Adicionar item\033[m\n\033[31m2. Remover item\033[m\n3. Listar itens\n4. Sair\nOpÃ§Ã£o: ");
                scanf("%d", &opcao);
            
                switch (opcao) {
                    case 1:
                        exibirItensDisponiveis();
                        scanf("%d", &itemEscolhido);
                        if (itemEscolhido >= 1 && itemEscolhido <= 5) {
                            adicionarItem(&inventario, itens[itemEscolhido - 1]);
                        } else {
                            printf("\033[31mOpÃ§Ã£o invÃ¡lida!\033[m\n");
                        }
                        break;
                    case 2:
                        removerItem(&inventario);
                        break;
                    case 3:
                        listarItens(&inventario);
                        break;
                    case 4:
                        printf("\033[37mSaindo...\033[m\n");
                        break;
                    default:
                        printf("\033[31mOpÃ§Ã£o invÃ¡lida! Tente novamente.\033[m\n");
                }
            } while (opcao != 4);
        
        } else if (opcao == 8) {
            liberar_lista(&lista_personagens);
            break;
        } else {
            printf("\033[31mOpcao invÃ¡lida! Tente novamente.\033[m\n");
        }
    }



     return 0;
}
