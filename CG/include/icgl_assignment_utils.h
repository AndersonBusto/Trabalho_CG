/* UNIVERSIDADE FEDERAL FLUMINENSE
 * INTITUTO DE COMPUTA��O
 * DEPARTAMENTO DE CI�NCIA DA COMPUTA��O
 *
 * Este programa foi elaborado pelos professores
 *
 *   Anselmo Antunes Montenegro (anselmo@ic.uff.br),
 *   Leandro Augusto Frata Fernandes (laffernandes@ic.uff.br) e
 *   Marcos de Oliveira Lage Ferreira (mlage@ic.uff.br)
 *
 * como parte do material did�tico da disciplina de Computa��o Gr�fica (TCC-00.179) do curso de
 * Bacharelado em Ci�ncia da Computa��o ministrado no Instituto de Computa��o da Universidade Federal Fluminense.
 *
 * A fim de presentar o funcionamento esperado para o programa, apenas as defini��es das tarefas aceitas para serem
 * resolvidas devem ser modificadas. Isso implica em comentar ou descomentar as linhas que cont�m c�digo de formato
 *
 *   #define ICGL_ASSIGNMENT_[N�MERO]_[DESCRI��O].
 *
 * Rotinas �teis podem ser definidas e declaradas no arquivo icgl_assignment_utils.cpp.
 *
 * Copyright (C) 2013 - A.Montenegro, L.A.F.Fernandes, M.Lage.
 */

#ifndef _ICGL_ASSIGNMENT_UTILS_
#define _ICGL_ASSIGNMENT_UTILS_


// DEFINI��O DAS ROTINAS �TEIS IMPLEMENTADAS PELO ALUNO /////////////////////////////////////////////////////////////////////

/* Coloque aqui a defini��o de suas rotinas auxiliares.
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
	Calcula o cofator pra o c�lculo de matriz inversa
*/
float cofator(int row, int column, matrix_struct matrix);

/*
	Calcula a matriz de cofatores da matriz original
*/
void matrixCofatores(matrix_struct original, matrix_struct &cofatores);

/*
	Retorna o valor m�ximo entre a e b
*/
float maxV(float a, float b);

// FIM DA DEFINI��O DAS ROTINAS �TEIS IMPLEMENTADAS PELO ALUNO //////////////////////////////////////////////////////////////

#endif
