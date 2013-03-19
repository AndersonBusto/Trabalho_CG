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

#if defined(ICGL_ASSIGNMENT_01_ROTATION_SCALE_TRANSLATION)
	void normalize(direction_struct &vector);
#endif

#if defined(ICGL_ASSIGNMENT_02_LOOK_AT)
    void crossProduct(direction_struct a, direction_struct b, direction_struct &r);
	float dotProduct(direction_struct a, direction_struct b);
#endif

#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
	void transpose_matrix(const matrix_struct &original, matrix_struct & transposed);
	void inverse_matrix(const matrix_struct &original, matrix_struct &inverted);
	float** alocateMatriz();
	float det4(matrix_struct matrix);
	float det3(float** matrix);
	float cofator(int row, int column, matrix_struct matrix);
	void matrixCofatores(matrix_struct original, matrix_struct &cofatores);
#endif

#if defined(ICGL_ASSIGNMENT_05_VERTEX_LIGHTING)
	float maxV(float a, float b);
#endif

// FIM DA DEFINI��O DAS ROTINAS �TEIS IMPLEMENTADAS PELO ALUNO //////////////////////////////////////////////////////////////

#endif
