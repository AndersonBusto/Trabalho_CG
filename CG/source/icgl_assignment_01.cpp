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

#if defined(ICGL_ASSIGNMENT_01_ROTATION_SCALE_TRANSLATION)


// INÍCIO DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO /////////////////////////////

/* Atribui ao argumento de saída 'rotation_matrix' uma matriz de rotação que rotação.
 *
 *   Argumentos de entrada:
 *     'angle_degrees'          : Ângulo de rotação (em graus).
 *     'axisx', 'axisy', 'axisz': Coordenadas do eixo de rotação em 3D. A normalização do eixo informado não é garantida.
 *
 *   Argumentos de saída:
 *     'rotation_matrix'        : Matriz 4x4 que codifica a rotação de 'angle_degrees' graus ao redor do eixo
 *                                ('axisx', 'axisy', 'axisz').
 */
void make_rotation_matrix(float angle_degrees, float axisx, float axisy, float axisz, matrix_struct &rotation_matrix) {
    // Calcular 'rotation_matrix'.
	direction_struct point = direction_struct(axisx, axisy, axisz);
	normalize(point);
	
	angle_degrees = angle_degrees * pi / 180;

	rotation_matrix(0,0) = cos(angle_degrees) + (1 - cos(angle_degrees)) * pow(point.x, 2);
	rotation_matrix(0,1) = point.y * point.x * (1 - cos(angle_degrees)) - point.z* sin(angle_degrees);
	rotation_matrix(0,2) = point.z * point.x * (1- cos(angle_degrees)) + point.y * sin(angle_degrees);
	rotation_matrix(0,3) = 0;

	rotation_matrix(1,0) = point.x * point.y * (1- cos(angle_degrees)) + point.z * sin(angle_degrees);
	rotation_matrix(1,1) = cos(angle_degrees) + (1- cos(angle_degrees)) * pow(point.y, 2);
	rotation_matrix(1,2) = point.z * point.y * (1- cos(angle_degrees)) - point.x * sin(angle_degrees);
	rotation_matrix(1,3) = 0;

	rotation_matrix(2,0) = point.x * point.z * (1- cos(angle_degrees)) - point.y * sin(angle_degrees);
	rotation_matrix(2,1) = point.y * point.z * (1- cos(angle_degrees)) + point.x * sin(angle_degrees);
	rotation_matrix(2,2) = cos(angle_degrees) + (1- cos(angle_degrees)) * pow(point.z, 2);
	rotation_matrix(2,3) = 0;

	rotation_matrix(3,0) = 0;
	rotation_matrix(3,1) = 0;
	rotation_matrix(3,2) = 0;
	rotation_matrix(3,3) = 1;
}

/* Atribui ao argumento de saída 'scale_matrix' uma matriz de escala.
 *
 *   Argumentos de entrada:
 *     'scalex', 'scaley', 'scalez': Escala, respectivamente, nos eixos x, y e z do espaço.
 *
 *   Argumentos de saída:
 *     'scale_matrix'              : Matriz 4x4 que codifica a escala não uniforme pretendida.
 */
void make_scale_matrix(float scalex, float scaley, float scalez, matrix_struct &scale_matrix) {
    // Calcular 'scale_matrix'.
	scale_matrix(0,0) = scalex;
	scale_matrix(0,1) = 0;
	scale_matrix(0,2) = 0;
	scale_matrix(0,3) = 0;

	scale_matrix(1,0) = 0;
	scale_matrix(1,1) = scaley;
	scale_matrix(1,2) = 0;
	scale_matrix(1,3) = 0;

	scale_matrix(2,0) = 0;
	scale_matrix(2,1) = 0;
	scale_matrix(2,2) = scalez;
	scale_matrix(2,3) = 0;

	scale_matrix(3,0) = 0;
	scale_matrix(3,1) = 0;
	scale_matrix(3,2) = 0;
	scale_matrix(3,3) = 1;
}

/* Atribui ao argumento de saída 'translation_matrix' uma matriz de translação.
 *
 *   Argumentos de entrada:
 *     'deltax', 'deltay', 'deltaz': Deslocamento, respectivamente, nos eixos x, y e z do espaço.
 *
 *   Argumentos de saída:
 *     'translation_matrix'         : Matriz 4x4 que codifica a translação pretendida.
 */
void make_translation_matrix(float deltax, float deltay, float deltaz, matrix_struct &translation_matrix) {
    // Calcular 'translation_matrix'.
	translation_matrix(0,0) = 1;
	translation_matrix(0,1) = 0;
	translation_matrix(0,2) = 0;
	translation_matrix(0,3) = deltax;

	translation_matrix(1,0) = 0;
	translation_matrix(1,1) = 1;
	translation_matrix(1,2) = 0;
	translation_matrix(1,3) = deltay;

	translation_matrix(2,0) = 0;
	translation_matrix(2,1) = 0;
	translation_matrix(2,2) = 1;
	translation_matrix(2,3) = deltaz;

	translation_matrix(3,0) = 0;
	translation_matrix(3,1) = 0;
	translation_matrix(3,2) = 0;
	translation_matrix(3,3) = 1;
}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
