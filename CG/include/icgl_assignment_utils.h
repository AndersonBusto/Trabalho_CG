/* UNIVERSIDADE FEDERAL FLUMINENSE
 * INTITUTO DE COMPUTAÇÃO
 * DEPARTAMENTO DE CIÊNCIA DA COMPUTAÇÃO
 *
 * Este programa foi elaborado pelos professores
 *
 *   Anselmo Antunes Montenegro (anselmo@ic.uff.br),
 *   Leandro Augusto Frata Fernandes (laffernandes@ic.uff.br) e
 *   Marcos de Oliveira Lage Ferreira (mlage@ic.uff.br)
 *
 * como parte do material didático da disciplina de Computação Gráfica (TCC-00.179) do curso de
 * Bacharelado em Ciência da Computação ministrado no Instituto de Computação da Universidade Federal Fluminense.
 *
 * A fim de presentar o funcionamento esperado para o programa, apenas as definições das tarefas aceitas para serem
 * resolvidas devem ser modificadas. Isso implica em comentar ou descomentar as linhas que contém código de formato
 *
 *   #define ICGL_ASSIGNMENT_[NÚMERO]_[DESCRIÇÃO].
 *
 * Rotinas úteis podem ser definidas e declaradas no arquivo icgl_assignment_utils.cpp.
 *
 * Copyright (C) 2013 - A.Montenegro, L.A.F.Fernandes, M.Lage.
 */

#ifndef _ICGL_ASSIGNMENT_UTILS_
#define _ICGL_ASSIGNMENT_UTILS_


// DEFINIÇÃO DAS ROTINAS ÚTEIS IMPLEMENTADAS PELO ALUNO /////////////////////////////////////////////////////////////////////

/* Coloque aqui a definição de suas rotinas auxiliares.
 */

/*
	Normaliza o vetor
*/
void normalize(direction_struct &vector);

/*
	Produto vetorial entre 2 vetores
	Retorno: direction_struct &r
*/
void crossProduct(direction_struct a, direction_struct b, direction_struct &r);

/*
	Produto escalar entre 2 vetorees
*/
float dotProduct(direction_struct a, direction_struct b);

/*
	Calcula matriz transposta
*/
void transpose_matrix(const matrix_struct &original, matrix_struct & transposed);

/*
	Calcula matriz inversa
*/
void inverse_matrix(const matrix_struct &original, matrix_struct &inverted);

/*
	Aloca uma matriz dinamicamente
*/
float** alocateMatriz();

/*
	Calcula uma determinante de uma matriz 4x4
*/
float det4(matrix_struct matrix);

/*
	Calcula uma determinante de uma matriz 3x3
*/
float det3(float** matrix);

/*
	Calcula o cofator pra o cálculo de matriz inversa
*/
float cofator(int row, int column, matrix_struct matrix);

/*
	Calcula a matriz de cofatores da matriz original
*/
void matrixCofatores(matrix_struct original, matrix_struct &cofatores);

/*
	Retorna o valor máximo entre a e b
*/
float maxV(float a, float b);

// FIM DA DEFINIÇÃO DAS ROTINAS ÚTEIS IMPLEMENTADAS PELO ALUNO //////////////////////////////////////////////////////////////

#endif
