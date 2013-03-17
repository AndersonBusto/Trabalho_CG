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
#if defined(ICGL_ASSIGNMENT_02_LOOK_AT)
	void normalize(float axisx, float axisy, float axisz, float *normal_x, float *normal_y, float *normal_z);
    void crossProduct(float Ax, float Ay, float Az, float Bx, float By, float Bz, float *Rx, float *Ry, float *Rz);
	float dotProduct(float Ax, float Ay, float Az, float Bx, float By, float Bz);
#endif

#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
	void gaussian(matrix_struct a, int index[]);
	void transpose_matrix(const matrix_struct &original, matrix_struct & transposed);
	void inverse_matrix(matrix_struct &original, matrix_struct & inverted);
	float** alocaMatriz();
	float det(matrix_struct matrix);
	float det3(float** matrix);
	float cofator(int linha, int coluna, matrix_struct matrix);
	void matrixCofatores(matrix_struct original, matrix_struct &cofatores);
#endif

// FIM DA DEFINI��O DAS ROTINAS �TEIS IMPLEMENTADAS PELO ALUNO //////////////////////////////////////////////////////////////

#endif
