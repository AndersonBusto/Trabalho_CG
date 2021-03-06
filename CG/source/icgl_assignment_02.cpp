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
 * A fim de presentar o funcionamento esperado para o programa, apenas o corpo dos procedimentos associados com a
 * tarefa relacionada a este arquivo deve ser modificado. Procedimentos auxiliares podem ser criados.
 *
 * Copyright (C) 2013 - A.Montenegro, L.A.F.Fernandes, M.Lage.
 */


// INCLUDES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* - ICGL - IC-UFF Graphics Library
 * Conjunto de opera��es utilizadas para ensino de Pipeline Gr�fico no Instito de Computa��o (IC) da Universidade Federal Fluminense (UFF).
 */
#include <icgl.h>

#if defined(ICGL_ASSIGNMENT_02_LOOK_AT)


// IN�CIO DA IMPLEMENTA��O DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO /////////////////////////////

/* Atribui ao argumento de sa�da 'lookat_matrix' uma matriz de visualiza��o a partir de um visualizador em um ponto (eye), um
 * ponto de refer�ncia indicando um alvo na cena (center) e um vetor indicando a dire��o assumida para cima (up).
 *
 *   Argumentos de entrada:
 *     'eyex', 'eyey', 'eyez'         : Coordenadas x, y e z do ponto onde est� localizado o centro de proje��o da c�mera.
 *     'centerx', 'centery', 'centerz': Coordenadas x, y e z do ponto de refer�ncia indicando um alvo na cena.
 *     'upx', 'upy', 'upz'            : Coordenadas x, y e z do vetor que indica a dire��o assumida como sendo para cima.
 *
 *   Argumentos de sa�da:
 *     'lookat_matrix'                : Matriz 4x4 de visualiza��o.
 */
void make_lookat_matrix(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz, matrix_struct &lookat_matrix) {
    // Calcular 'lookat_matrix'.	
	direction_struct up = direction_struct(upx, upy, upz);
	direction_struct eye = direction_struct(eyex, eyey, eyez);

	direction_struct z = direction_struct(eyex - centerx, eyey - centery,  eyez - centerz);	
	direction_struct x = direction_struct();
	direction_struct y = direction_struct();

	normalize(z);

	crossProduct(up, z, x);	
	normalize(x);
	    
	crossProduct(z, x, y);
	normalize(y);  
	
	lookat_matrix = matrix_struct();
	lookat_matrix(0,0) = x.x;
	lookat_matrix(0,1) = y.x;
	lookat_matrix(0,2) = z.x;
	lookat_matrix(0,3) = eyex;

	lookat_matrix(1,0) = x.y;
	lookat_matrix(1,1) = y.y;
	lookat_matrix(1,2) = z.y;
	lookat_matrix(1,3) = eyey;
	
	lookat_matrix(2,0) = x.z;
	lookat_matrix(2,1) = y.z;
	lookat_matrix(2,2) = z.z;
	lookat_matrix(2,3) = eyez;

	lookat_matrix(3,0) = 0.0f;
	lookat_matrix(3,1) = 0.0f;
	lookat_matrix(3,2) = 0.0f;
	lookat_matrix(3,3) = 1.0f;
}

// FIM DA IMPLEMENTA��O DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
