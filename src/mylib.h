/*
 * mylib.h
 *
 *  Created on: 14 de jun. de 2023
 *      Author: Arthur Sena de Sousa
 */


#ifndef MYLIB_H_
#define MYLIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RANDOM rand() % 1000
#define MAX_DEPENDENTES 2

typedef struct dependente dependente;
struct dependente {
	char nome[50];
	char codigo[12];
	char dataNasc[11];
	char tipoDependente;
	dependente *proxDependente;
	dependente *antDependente;

};

typedef struct cliente cliente;
struct cliente {
	char nome[50];
	char codigo[11];
	char dataNasc[11];
	float limite;
	char tipoCartao;
	int qtdeDependentes;
	dependente *dependente;
	cliente *proxCliente;
};

// Protótipo
void exibirMenu();



#endif /* MYLIB_H_ */
