/*
 * funcoes.c
 *
 *  Created on: 14 de jun. de 2023
 *      Author: Arthur Sena de Sousa
 *
 */
#include "mylib.h"

void exibirMenuA(cliente **listaClientes, int *sequencial);
void exibirMenuB(cliente **listaCliente);
void exibirMenuC();
cliente* cadastrarCliente(cliente *lista, int *sequencial);
void cadastrarNome(char *nome);
void cadastrarCodigo(char *nome, char *codigo, int *sequencial);
char* cadastrarNascimento(int idadeMinima);
void cadastrarLimite(float *limite, int idade);
char cadastrarTipo();
void cadastrarQtdeDependente(cliente *cliente);
void cadastrarDependente(cliente *novoCliente, int *sequencialDependente);
void cadastrarTipoDependente(char *tipoDependente);
void cadastrarCodigoDependente(cliente *cliente, dependente *dependente, int *sequencial);
void inserirDependentePorCodigo(cliente *lista, char *codigo, int *sequencialDependente);
void excluirCliente(cliente **lista, char *codigo);
void excluirDependentePorCodigo(cliente **lista, char *codigoCliente, char *codigoDependente);
void imprimirClientes(cliente *lista, float *somaLimites, float *contLimites);
void imprimirDependentes(dependente *lista);
void buscarPorCodigo(cliente *lista, char *codigo);
void exibirPorCartao(cliente *lista, char *tipoCartao);

void exibirMenu() {
	char op;
	int sequencial = 0;
	cliente *listaClientes = NULL;
	do {
		printf("\nEmpresa FinCom\n"
			   "A - Inserir\n"
			   "B - Excluir\n"
			   "C - Relatórios\n"
			   "D - Finalizar\n"
			   "Digite sua opção: \n");
		scanf(" %c", &op);
		op = toupper(op);

		switch (op) {
			case 'A':
				exibirMenuA(&listaClientes, &sequencial);
				break;
			case 'B':
				exibirMenuB(&listaClientes);
				break;
			case 'C':
				exibirMenuC(listaClientes);
				break;
			case 'D':
				break;
			default:
				printf("Opção inválida\n");
		}
	} while (op != 'D');
}

void exibirMenuA(cliente **listaClientes, int *sequencial) {
	int op;
	char codigo[10];

		do {
			printf("1 - Efetuar inclusão de cliente\n"
				   "2 - Efetuar inclusão de dependente (por código)\n"
				   "3 - Retornar para menu principal\n"
				   "Digite sua opção: ");
			scanf(" %d", &op);
			if (op != 1 && op != 2 && op != 3) {
				printf("Opção inválida\n");
			}
		} while (op != 1 && op != 2 && op != 3);

		switch(op) {
			case 1:
				(*listaClientes) = cadastrarCliente(*listaClientes, sequencial);
				break;
			case 2:
				printf("\nDigite o código do cliente: ");
				scanf("%s", codigo);
				inserirDependentePorCodigo(*listaClientes, codigo, sequencial);
				break;
			case 3:
				printf("Retornando...\n\n");
				exibirMenu();
				break;
			default:
				printf("Opção Inválida");
		}
}

void exibirMenuB(cliente **listaCliente) {
	int op;
	char codigo[10];
	char codigoDependente[12];

		do {
			printf("1 - Efetuar exclusão de cliente\n"
				   "2 - Efetuar exclusão de dependente (por código)\n"
				   "3 - Retornar para menu principal\n"
				   "Digite sua opção: ");
			scanf(" %d", &op);
			if (op != 1 && op != 2 && op != 3) {
				printf("Opção inválida\n");
			}

			switch (op) {
				case 1:
					printf("\nDigite o código do cliente: ");
					scanf("%s", codigo);
					excluirCliente(listaCliente, codigo);
					break;
				case 2:
					printf("\nDigite o código do cliente: ");
					scanf("%s", codigo);
					printf("\nDigite o código do dependente: ");
					scanf("%s", codigoDependente);
					excluirDependentePorCodigo(listaCliente, codigo, codigoDependente);
					break;
				case 3:
					printf("Retornando...\n\n");
					exibirMenu();
					break;
			}
		} while (op != 1 && op != 2);
}

void exibirMenuC(cliente *lista) {
	float somaLimites = 0;
	float contLimites = 0;
	char codigo[10];
	char tipoCartao;

	int op;
		do {
			printf("1 - Listar todos os dados dos clientes e exibir a média dos limites\n"
				   "2 - Listar todos os dados do cliente por código\n"
				   "3 - Listar clientes por tipo de cartão\n"
				   "4 - Retornar para menu principal\n"
				   "Digite sua opção: ");
			scanf(" %d", &op);

			switch(op) {
				case 1:
					imprimirClientes(lista, &somaLimites, &contLimites);
					break;
				case 2:
					printf("\nDigite o código do cliente: ");
					scanf("%s", codigo);
					buscarPorCodigo(lista, codigo);
					break;
				case 3:
					tipoCartao = cadastrarTipo();
					exibirPorCartao(lista, &tipoCartao);
					break;
				case 4:
					printf("Retornando...\n\n");
					exibirMenu();
					break;
				default:
					printf("Opção inválida\n");
			}
		} while (op != 1 && op != 2 && op != 3 && op != 4);

}

cliente* cadastrarCliente(cliente *lista, int *sequencial) {
	cliente *novoCliente = (cliente*) malloc(sizeof(cliente));
	int dependentes = 0;
	int sequencialDependente = 0;
	char anoNascimento[5];
	int idade;
	int j;

	cadastrarNome(novoCliente->nome);
	strcpy(novoCliente->dataNasc, cadastrarNascimento(18));
	cadastrarCodigo(novoCliente->nome, novoCliente->codigo, sequencial);

	// Buscando o ano de nascimento //
	j = 0;
	for (int i = 0; i < 11; i++) {
		if (i > 5) {
			anoNascimento[j] = novoCliente->dataNasc[i];
			j++;
		}
	}

	idade = 2023 - atoi(anoNascimento);
	cadastrarLimite(&novoCliente->limite, idade);
	novoCliente->tipoCartao = cadastrarTipo();

	switch (novoCliente->tipoCartao) {
		case 'N':
			novoCliente->limite *= 1.05;
			break;
		case 'I':
			novoCliente->limite *= 1.2;
			break;
		default:
			break;
	}

	cadastrarQtdeDependente(novoCliente);
	novoCliente->dependente = NULL;
	if (novoCliente->qtdeDependentes > 0) {
		do {
			cadastrarDependente(novoCliente, &sequencialDependente);
			dependentes += 1;
		} while (dependentes < novoCliente->qtdeDependentes);
	}

	novoCliente->proxCliente = NULL;

	// Inserindo na lista pelo fim
	if (lista == NULL) {
		lista = novoCliente;
	} else {
		cliente *aux = lista;
		while (aux->proxCliente != NULL) {
			aux = aux->proxCliente;
		}
		aux->proxCliente = novoCliente;
	}

	return lista;
}

void cadastrarNome(char *nome) {
	fflush(stdin);
	printf("\nDigite o nome: ");
	scanf("%[^\n]", nome);
}

void cadastrarCodigo(char *nome, char *codigo, int *sequencial) {
	int controller;
	int code = RANDOM;
	char codeString[5];
	char sequencialString[4];

	codigo[0] = nome[0];

	for (int i = 0; i <= 50; i++) {
		if (nome[i] == ' ') {
			controller = i;
		} else if (nome[i] == '\0') {
			break;
		}
	}
	controller += 1;
	codigo[1] = tolower(nome[controller]);
	codigo[2] = '\0';

	sprintf(codeString, "%d", code);
	strcat(codigo, codeString);

	// Sequencial
	*sequencial += 1;
	sprintf(sequencialString, "%d", *sequencial);
	strcat(codigo, sequencialString);
}

char* cadastrarNascimento(int idadeMinima) { // Protótipo definido
	int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int ehValido;
	char *data = (char*) malloc(11);
	int dia, mes, ano;
	int j, k;
	char diaString[3], mesString[3], anoString[5];
	 do {
		 do {
			 ehValido = 1;
			 printf("\nDigite a data de nascimento do cliente (DD/MM/AAAA): ");
			 scanf(" %s", data);
			 if (data[10] != '\0') {
				 ehValido = 0;
				 printf("\nDigite uma data válida");
			 } else if (data[2] != '/' || data[5] != '/') {
				 ehValido = 0;
				 printf("\nDigite a data no formato DD/MM/AAAA");
			 }
		 } while(ehValido == 0);
		 j = 0;
		 k = 0;
		 for (int i = 0; i < 10; i++) {
			 if (i < 2) {
				 diaString[i] = data[i];
			 } else if (i > 2 && i < 5) {
				 mesString[j] = data[i];
				 j++;
			 } else if (i > 5) {
				 anoString[k] = data[i];
				 k++;
			 }
		 }
		 diaString[2] = '\0';
		 mesString[2] = '\0';
		 anoString[4] = '\0';

		 dia = atoi(diaString);
		 mes = atoi(mesString);
		 ano = atoi(anoString);

		if (dia > diasMes[mes - 1]) {
			printf("Erro! Dia inválido\n");
			ehValido = 0;
		} else if (mes < 1 || mes > 12) {
			printf("Erro! Mês inválido\n");
			ehValido = 0;
		} else if (ano > 2023) {
			printf("O ano de nascimento deve ser menor que o ano atual\n");
			ehValido = 0;
		} else if (2023 - ano < idadeMinima || 2023 - ano > 100) {
			printf("Apenas idades entre %d e 100 anos são permitidas\n", idadeMinima);
			ehValido = 0;
		}
	 } while (ehValido == 0);

	 return data;
}

void cadastrarLimite(float *limite, int idade) {
	if (idade <= 40) {
		*limite = 10000;
	} else if (idade <= 60) {
		*limite = 15000;
	} else if (idade <= 75) {
		*limite = 5000;
	} else {
		*limite = 2500;
	}
}

char cadastrarTipo() { // Protótipo definido
	char op;
	do {
		printf("\nU - Universitário"
			   "\nN - Nacional"
			   "\nI - Internacional"
			   "\nDigite uma opção: ");
		scanf(" %c", &op);
		op = toupper(op);
		if (op != 'U' && op != 'N' && op != 'I') {
			printf("Selecione uma opção válida!");
		}
	} while (op != 'U' && op != 'N' && op != 'I');

	return op;
}

void cadastrarQtdeDependente(cliente *cliente) {
	do {
		printf("Quantos dependentes deseja cadastrar para o cliente %s (max: 2)? ", cliente->nome);
		scanf("%d", &cliente->qtdeDependentes);
		if (cliente->qtdeDependentes < 0 || cliente->qtdeDependentes > MAX_DEPENDENTES) {
			printf("A quantidade de dependentes deve ser de 0 até %d\n", MAX_DEPENDENTES);
		}
	} while (cliente->qtdeDependentes < 0 || cliente->qtdeDependentes > MAX_DEPENDENTES);
}

void cadastrarDependente(cliente *novoCliente, int *sequencialDependente) {
	dependente *novoDependente = (dependente*) malloc(sizeof(dependente));
	cadastrarNome(novoDependente->nome);
	cadastrarCodigoDependente(novoCliente, novoDependente, sequencialDependente);
	strcpy(novoDependente->dataNasc, cadastrarNascimento(0));
	cadastrarTipoDependente(&novoDependente->tipoDependente);

	novoDependente->antDependente = NULL;

	// Inserir na lista pelo inicio
	if (novoCliente->dependente != NULL) {
		novoDependente->proxDependente = novoCliente->dependente;
		novoCliente->dependente->antDependente = novoDependente;
	} else {
		novoDependente->proxDependente = NULL;
	}

	novoCliente->dependente = novoDependente;
	printf("\nDependente cadastrado com sucesso!\n");
}

void cadastrarCodigoDependente(cliente *cliente, dependente *dependente, int *sequencial) {
	char sequencialDependente[3];
	*sequencial += 1;
	sprintf(sequencialDependente, "0%d", *sequencial);
	strcpy(dependente->codigo, cliente->codigo);
	strcat(dependente->codigo, sequencialDependente);
}

void cadastrarTipoDependente(char *tipoDependente) {
	do {
		printf("Digite o tipo de dependente a ser cadastrado:\n"
				"C - Cônjuje\n"
				"F - Filho\n"
				"E - Enteado\n");
		scanf(" %c", tipoDependente);
		*tipoDependente = toupper(*tipoDependente);
	} while (*tipoDependente != 'C' && *tipoDependente != 'F' && *tipoDependente != 'E');
}

void inserirDependentePorCodigo(cliente *lista, char *codigo, int *sequencialDependente) {
	cliente *aux = lista;
	if (aux != NULL) {
		if (strcmp(aux->codigo, codigo) == 0) {
			if (aux->qtdeDependentes < MAX_DEPENDENTES) {
				if(*sequencialDependente == 1){
					*sequencialDependente += 1;
				}
				cadastrarDependente(aux, sequencialDependente);
				aux->qtdeDependentes += 1;
			} else {
				printf("\nEsse cliente já antingiu a quantidade máxima de dependentes");
			}
		} else {
				aux = aux->proxCliente;
				inserirDependentePorCodigo(aux, codigo, sequencialDependente);
		}
	} else {
		printf("\n------- Fim dos clientes na lista ---------");
	}
}

void excluirCliente(cliente **lista, char *codigo) {
	cliente *aux = *lista;
	cliente *anterior = NULL;
	dependente *auxD = NULL;

	while (aux != NULL) {
		if (strcmp(aux->codigo, codigo) == 0) {
			if (aux->qtdeDependentes > 0) {
				auxD = aux->dependente;
				while (auxD->proxDependente != NULL) {
					auxD = auxD->proxDependente;
					free(auxD->antDependente);
				}
				free(auxD);
			}

			if (aux == *lista) {
				*lista = aux->proxCliente;
			} else {
				anterior->proxCliente = aux->proxCliente;
			}

			free(aux);
			printf("\nCliente excluído com sucesso\n");
			break;
		}

		anterior = aux;
		aux = aux->proxCliente;
	}
}

void excluirDependentePorCodigo(cliente **lista, char *codigoCliente, char *codigoDependente) {
	cliente *aux = *lista;
	dependente *auxD = NULL;

	while (aux != NULL) {
		if (strcmp(aux->codigo, codigoCliente) == 0) {
			if (aux->qtdeDependentes > 0) {
				auxD = aux->dependente;
				while (auxD != NULL) {
					if (strcmp(auxD->codigo, codigoDependente) == 0) {
						if (auxD == aux->dependente) {
							if(auxD->proxDependente != NULL){
								aux->dependente->antDependente = NULL;
							}
							aux->dependente = auxD->proxDependente;
						} else if (auxD->proxDependente == NULL) {
							auxD->antDependente->proxDependente = auxD->proxDependente;
						} else {
							auxD->proxDependente->antDependente = NULL;
						}

						free(auxD);
						aux->qtdeDependentes -= 1;
						printf("\nDependente excluído com sucesso");

					}
					auxD = auxD->proxDependente;
				}
			} else {
				printf("\nNão há dependentes na lista!\n");
			}
		}
		aux = aux->proxCliente;
	}
}

void imprimirClientes(cliente *lista, float *somaLimites, float *contLimites) {
	cliente *aux = lista;
	if (aux != NULL) {
		printf("Dados do cliente\n"
				"Nome: %s\n"
				"Código: %s\n"
				"Data de Nascimento: %s\n"
				"Limite: %f\n"
				"Tipo do cartão: %c\n"
				"Quantidade de Dependentes: %d\n\n",
				aux->nome, aux->codigo, aux->dataNasc, aux->limite, aux->tipoCartao, aux->qtdeDependentes);
		if (aux->qtdeDependentes > 0) {
			imprimirDependentes(aux->dependente);
		}

		*somaLimites += aux->limite;
		*contLimites += 1;

		imprimirClientes(aux->proxCliente, somaLimites, contLimites);
	} else if (*contLimites > 0) {
		printf("\nMédia dos Limites: %f\n", *somaLimites / *contLimites);
	} else {
		printf("\n------- Fim dos clientes na lista ---------");
	}
}

void imprimirDependentes(dependente *lista) {
	dependente *auxD = lista;
	if (auxD != NULL) {
		printf("Dados dos dependentes\n"
				"Nome: %s\n"
				"Código: %s\n"
				"Data de Nascimento: %s\n"
				"Tipo de dependente: %c\n"
				"-----------------------------\n",
				auxD->nome, auxD->codigo, auxD->dataNasc, auxD->tipoDependente);
		imprimirDependentes(auxD->proxDependente);
	}
}

void buscarPorCodigo(cliente *lista, char *codigo) {
	cliente *aux = lista;
	if (aux != NULL) {
		if (strcmp(aux->codigo, codigo) == 0) {
			printf("Dados do cliente\n"
					"Nome: %s\n"
					"Código: %s\n"
					"Data de Nascimento: %s\n"
					"Limite: %f\n"
					"Tipo do cartão: %c\n"
					"Quantidade de Dependentes: %d\n\n",
					aux->nome, aux->codigo, aux->dataNasc, aux->limite, aux->tipoCartao, aux->qtdeDependentes);

			if (aux->qtdeDependentes > 0) {
				imprimirDependentes(lista->dependente);
			}

		} else {
				aux = aux->proxCliente;
				buscarPorCodigo(aux, codigo);
		}

	} else {
		printf("\n------- Fim dos clientes na lista ---------");
	}
}

void exibirPorCartao(cliente *lista, char *tipoCartao) {
	cliente *aux = lista;

	if (aux != NULL) {
			if (aux->tipoCartao == *tipoCartao) {
				printf("Dados do cliente\n"
						"Nome: %s\n"
						"Código: %s\n"
						"Data de Nascimento: %s\n"
						"Limite: %f\n"
						"Tipo do cartão: %c\n"
						"Quantidade de Dependentes: %d\n\n",
						aux->nome, aux->codigo, aux->dataNasc, aux->limite, aux->tipoCartao, aux->qtdeDependentes);

				if (aux->qtdeDependentes > 0) {
					imprimirDependentes(lista->dependente);
				}
			}

			aux = aux->proxCliente;
			exibirPorCartao(aux, tipoCartao);

		} else {
			printf("\n------- Fim dos clientes na lista ---------");
		}
}
