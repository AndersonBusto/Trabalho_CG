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
 * A fim de presentar o funcionamento esperado para o programa, apenas o corpo dos procedimentos associados com a
 * tarefa relacionada a este arquivo deve ser modificado. Procedimentos auxiliares podem ser criados.
 *
 * Copyright (C) 2013 - A.Montenegro, L.A.F.Fernandes, M.Lage.
 */


// INCLUDES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* - ICGL - IC-UFF Graphics Library
 * Conjunto de operações utilizadas para ensino de Pipeline Gráfico no Instito de Computação (IC) da Universidade Federal Fluminense (UFF).
 */
#include <icgl.h>

#if defined(ICGL_ASSIGNMENT_02_LOOK_AT)


// INÍCIO DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO /////////////////////////////

/* Atribui ao argumento de saída 'lookat_matrix' uma matriz de visualização a partir de um visualizador em um ponto (eye), um
 * ponto de referência indicando um alvo na cena (center) e um vetor indicando a direção assumida para cima (up).
 *
 *   Argumentos de entrada:
 *     'eyex', 'eyey', 'eyez'         : Coordenadas x, y e z do ponto onde está localizado o centro de projeção da câmera.
 *     'centerx', 'centery', 'centerz': Coordenadas x, y e z do ponto de referência indicando um alvo na cena.
 *     'upx', 'upy', 'upz'            : Coordenadas x, y e z do vetor que indica a direção assumida como sendo para cima.
 *
 *   Argumentos de saída:
 *     'lookat_matrix'                : Matriz 4x4 de visualização.
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

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
