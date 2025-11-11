// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Contantes Globais ---
#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100 
#define TAM_STRING 100

// --- Defininção de Estruturas ---

struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel;
};


struct Emprestimo {
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
};

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}


// --- Função Principal (main) ---
int main(){
    
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    
    biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));

    
    emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: falha ao alocar memoria. \n");
        return 1; // Retorna 1 para indicar um erro.
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        printf("====================================\n");
        printf("      BIBLIOTECA - PARTE 2\n");
        printf("====================================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar empréstimo\n");
        printf("4 - Listar empréstimos\n");
        printf("0 - Sair\n");
        printf("----------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1: //CADASTRO DE LIVRO
                printf("--- Cadastro de Novo Livro --- \n\n");
                if (totalLivros < MAX_LIVROS) {
                    //O acesso aos campos é igual ao do array estático.
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    // ... (demais leituras são iguais à Parte 1) ...
                    printf("Digite o autor: ");
                    fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
                    printf("Digite a editora: ");
                    fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                    biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")];
                    biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n") ];
                    biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")];

                    printf("Digite a edicao: ");
                    scanf("%d", &biblioteca[totalLivros].edicao);
                    limparBufferEntrada();

                    //Ao cadastrar, o livro automaticamente se torna disponível.
                    biblioteca[totalLivros].disponivel = 1;

                    totalLivros++;

                    printf("\nLivro Cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia! Nao e possivel cadastrar mais livros.\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar(); // Pausa para o usuário ler a mensagem antes de voltar ao menu
                break;

            case 2: //LISTAGEM DE LIVROS
                printf(" --- Lista de livros Cadastrados --- \n\n");

                if(totalLivros == 0) {
                    printf("Nenhum livro cadastrado ainda.\n");
                } else {
                    for (int i = 0; i < totalLivros; i++){
                        printf("------------------------------------\n");
                        printf("LIVRO %d\n", i + 1);
                        printf("Nome: %s\n", biblioteca[i].nome);
                        printf("Autor: %s\n", biblioteca[i].autor);
                        printf("Editora: %s\n", biblioteca[i].editora);
                        printf("Edicao: %d\n", biblioteca[i].edicao);
                    };

                    printf("---------------------------------------\n");
                };


                
                printf("\nPressione Enter pra continuar...");
                getchar(); 
                break;
            
            case 3: //Realizar empréstimos
                printf("--- Realizar Emprestimo --- \n\n");

                if(totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de emprestimos atingido!\n");
                } else {
                    printf("Livros disponíveis: \n");
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++) {
                        if(biblioteca[i].disponivel) {
                            printf("%d - %s\n", i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0) {
                        printf("Nenhum livro disponivel para emprestimo.\n");
                    } else {
                        printf("\nDigite o numero do livro que deseja emprestar: ");
                        int numLivro;
                        scanf("%d", &numLivro);
                        limparBufferEntrada();

                        int indice = numLivro - 1;// Converte para o indice do arry (0 a N -1).

                        //Validação da escolha do usuário.
                        if(indice >=0 && indice < totalLivros && biblioteca[indice].disponivel) {
                            printf("Digite o nome do usuario que está pegando o livro: ");
                            fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")];

                        //Registra o empréstimo
                        emprestimos[totalEmprestimos].indiceLivro = indice;

                        //Atualiza o status do livro para indisponível.
                        biblioteca[indice].disponivel = 0;

                        totalEmprestimos++;
                        printf("\nEmprestimo realizado com sucesso!\n");

                    } else {
                        printf("\nNumero de livro invalido ou livro indisponivel.\n");
                    }
                }
            } 
            printf("\nPressione Enter pra continuar...");
            getchar();
            break;



            case 4:
            printf("--- Listar emprestimos\n\n");
            if(totalEmprestimos == 0) {
                printf("Nenhum emprestimo realizado.\n");
            } else {
                for (int i = 0; i < totalEmprestimos; i++) {
                    int indiceLivro = emprestimos[i].indiceLivro;
                    printf("----------------------------------\n");
                    printf("EMPRESTIMO %d\n", i + 1);
                    printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                    printf("Usuário: %s\n", emprestimos[i].nomeUsuario);
                }
                printf("------------------------------------\n");
            }
            printf("\nPressione Enter pra continuar...");
            getchar();
            break;


            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            
            default: 
                printf("\nOpção invalida! Tente novamente.\n");
                printf("\nPressione Enter pra continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);


    // 2. LIBERAÇÃO DA MEMORIA 
    

    free(biblioteca);
    free(emprestimos);

    printf("Memória liberada com sucesso.\n");

    return  0; 

}