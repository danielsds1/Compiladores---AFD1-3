#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int retornaEstadoCom(int estado, char ch) {
	switch (ch)
	{
	case '/':
		switch (estado)
		{
		case 1:
			return 2;
		case 3:
			return 3;
		case 4:
			return 5;
		default:
			return 0;
		}
	case '*':
		switch (estado)
		{
		case 2:
			return 3;
		case 3:
			return 4;
		case 4:
			return 4;
		default:
			break;
		}
	default:
		switch (estado)
		{
		case 3:
			return 3;
		case 4:
			return 3;
		default:
			return 0;
		}
		break;
	}

}
int retornaEstadoVar(int estado, char ch) {
	if (isalpha(ch)) {
		switch (estado)
		{
		case 1:
			return 2;
		case 2:
			return 2;
		default:
			return 0;
		}
	}
	else if (isdigit(ch)) {
		if (estado == 2) {
			return 2;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}


}
int ReconheceComAFD3(char* frase) {
	int estado = 1;
	int novoEstado = 0;
	unsigned int ch = 0;
	while (ch < strlen(frase) && estado < 5 && estado > 0) {
		novoEstado = retornaEstadoCom(estado, frase[ch]);
		printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, frase[ch], estado);
		if (retornaEstadoCom(estado, frase[ch])) {
			estado = novoEstado;
		}
		ch++;
	}
	return estado;
}
int ReconheceComAFD2(char* frase) {
	int estado = 1;
	int novoEstado = 0;
	unsigned int ch = 0;
	while (ch < strlen(frase) && estado < 5 && estado > 0) {
		printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, frase[ch], estado);
		switch (estado) {
		case 1:
			switch (frase[ch]) {
			case '/':	ch++;
				estado = 2;
				break;
			default:
				estado = 100;
				break;
			}
			break;

		case 2:
			switch (frase[ch]) {
			case '*':	ch++;
				estado = 3;
				break;
			default:
				estado = 100;
				break;
			}
			break;
		case 3:
			switch (frase[ch]) {
			case '*':	ch++;
				estado = 4;
				break;
			default:
				ch++;
				break;
			}
			break;
		case 4:
			switch (frase[ch]) {
			case '/':	ch++;
				estado = 5;
				break;
			case '*': ch++;
				break;
			default: ch++;
				estado = 3;
				break;
			}
			break;
		}

	}
	return estado;
}
int ReconheceComAFD1(char* frase) {

	int estado = 1;
	int fim = 0;
	int novoEstado = 0;
	unsigned int ch = 0;
	while (ch < strlen(frase) && estado < 5 && estado > 0) {
		printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, frase[ch], estado);
		if (frase[ch] == '/') {
			ch++; estado = 2;
			printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, frase[ch], estado);
			if (frase[ch] == '*') {
				ch++; estado = 3;
				fim = 0;
				printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, frase[ch], estado);
				while (!fim) {
					while (frase[ch] != '*') {
						ch++;
						printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, frase[ch], estado);
					}
					ch++; estado = 4;
					while (frase[ch] == '*') {
						ch++;
						printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, frase[ch], estado);
					}
					if (frase[ch] == '/') {
						fim = 1;
					}
					ch++;
				}
				estado = 5;
			}
			else {
				estado = 0;
			}
		}
		else {
			estado = 0;
		}
	}
	return estado;
}
int ReconheceVarAFD1(char* variavel) {
	int estado = 1;
	unsigned int ch = 0;
	while (ch < strlen(variavel) && estado > 0) {
		printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, variavel[ch], estado);
		if (isalpha(variavel[ch]))
		{
			ch++;
			estado = 2;
			while (isalnum(variavel[ch]))
			{
				printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, variavel[ch], estado);
				ch++;
			}
		}
		else {
			estado = 0;
		}
	}
	return estado;
}
int ReconheceVarAFD2(char* variavel) {
	int estado = 1;
	unsigned int ch = 0;
	while (ch < strlen(variavel) && estado < 4) {
		printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, variavel[ch], estado);
		switch (estado) {
		case 1:
			if (isalpha(variavel[ch])) {
				estado = 2;
				ch++;
				break;
			}
			else {
				estado = 100;
				break;
			}
			break;
		case 2:
			if (isalnum(variavel[ch])) {
				estado = 2;
				ch++;
				break;
			}
			else
			{
				estado = 100;
				break;
			}
		}
	}
	return estado;
}
int ReconheceVarAFD3(char* variavel) {
	int estado = 1;
	unsigned int ch = 0;
	while (ch < strlen(variavel) && estado < 3 && estado > 0) {
		printf("\n %02d - Caractere[%c] - Estado [%d]", ch + 1, variavel[ch], estado);
		estado = retornaEstadoVar(estado, variavel[ch]);
		ch++;
	}
	return estado;
}
int main() {

	char frase[100];
	int tipo = 1;
	int metodo = 1;
	int estado = 1;
	int escolha = 1;

	while (escolha)
	{
		printf("Reconhecer: \n1. Comentario \n2. Variavel\nDigite a Opcao:");
		scanf("%d",&tipo);
		if (tipo == 1) {
			printf("\nDigite o Comentario:");
		}
		else {
			printf("\nDigite a Variável:");
		}
		scanf("%s", &frase);

		printf("\nEscolha um Metodo:");

		if (tipo == 1) {
			printf("\n1. Reconhecedor de Comentarios AFD1");
			printf("\n2. Reconhecedor de Comentarios AFD2");
			printf("\n3. Reconhecedor de Comentarios AFD3");
		}
		else {
			printf("\n1. Reconhecedor de Variaveis AFD1");
			printf("\n2. Reconhecedor de Variaveis AFD2");
			printf("\n3. Reconhecedor de Variaveis AFD3");
		}
		printf("\nDigite o Metodo:");
		scanf("%d", &metodo);
		metodo = (tipo == 2) ? metodo + 3 : metodo;
		switch (metodo) {
		case 1:
			estado = ReconheceComAFD1(frase);
			break;
		case 2:
			estado = ReconheceComAFD2(frase);
			break;
		case 3:
			estado = ReconheceComAFD3(frase);
			break;
		case 4:
			estado = ReconheceVarAFD1(frase);
			break;
		case 5:
			estado = ReconheceVarAFD2(frase);
			break;
		case 6:
			estado = ReconheceVarAFD3(frase);
			break;
		default:
			printf("\nMetodo Invalido.");
		}
		if (metodo < 4) {
			if (estado == 5) {
				printf("\n\nComentario reconhecido\n\n");
			}
			else {
				printf("\n\nComentario nao reconhecido\n\n");
			}
		}
		else {
			if (estado == 2) {
				printf("\n\nVariavel Reconhecida\n\n");
			}
			else {
				printf("\n\nVariavel Nao Reconhecida\n\n");
			}
		}
		printf("\nDeseja continuar? \n1 - Sim \n0 - Nao\n");
		scanf("%d", &escolha);
		system("@cls||clear");
	}
}
