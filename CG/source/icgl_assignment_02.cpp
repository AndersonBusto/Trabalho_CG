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
	float dotProductX, dotProductY, dotProductZ;
	float normal_zx, normal_zy, normal_zz;
	float normal_xx, normal_xy, normal_xz;
	float normal_yx, normal_yy, normal_yz;
	float x_x, x_y, x_z;
	float y_x, y_y, y_z;
	float z_x = centerx - eyex;
	float z_y = centery - eyey;
	float z_z = centerz - eyez;
	normalize(z_x, z_y, z_z, &normal_zx, &normal_zy, &normal_zz);

	crossProduct(upx, upy, upz, normal_zx, normal_zy, normal_zz, &x_x, &x_y, &x_z);
	normalize(x_x, x_y, x_z, &normal_xx, &normal_xy, &normal_xz);

	crossProduct(normal_zx, normal_zy, normal_zz, normal_xx, normal_xy, normal_xz, &y_x, &y_y, &y_z);
	//normalize(normal_yx, normal_yy, normal_yz, &normal_yx, &normal_yy, &normal_yz);
	normal_yx = y_x;
	normal_yy = y_y;
	normal_yz = y_z;

	dotProductX =  dotProduct(normal_xx, normal_xy, normal_xz, -eyex, -eyey, -eyez);
	dotProductY =  dotProduct(normal_yx, normal_yy, normal_yz, -eyex, -eyey, -eyez);
	dotProductZ =  dotProduct(normal_zx, normal_zy, normal_zz, -eyex, -eyey, -eyez);
	printf("eyey %f \n", eyex);
	printf("%f \n", dotProductX);
	printf("%f \n", dotProductY);
	printf("%f \n", dotProductZ);

	lookat_matrix(0,0) = normal_xx; printf("%f \n", lookat_matrix(0,0));
	lookat_matrix(0,1) = normal_yx; printf("%f \n", lookat_matrix(0,1));
	lookat_matrix(0,2) = normal_zx; printf("%f \n", lookat_matrix(0,2));
	lookat_matrix(0,3) = 0;

	lookat_matrix(1,0) = normal_xy; printf("%f \n", lookat_matrix(1,0));
	lookat_matrix(1,1) = normal_yy; printf("%f \n", lookat_matrix(1,1));
	lookat_matrix(1,2) = normal_zy; printf("%f \n", lookat_matrix(1,2));
	lookat_matrix(1,3) = 0;
	
	lookat_matrix(2,0) = normal_xz; printf("%f \n", lookat_matrix(2,0));
	lookat_matrix(2,1) = normal_yz; printf("%f \n", lookat_matrix(2,1));
	lookat_matrix(2,2) = normal_zz; printf("%f \n", lookat_matrix(2,2));
	lookat_matrix(2,3) = 0;

	lookat_matrix(3,0) = dotProductX; printf("%f \n", lookat_matrix(3,0));
	lookat_matrix(3,1) = dotProductY; printf("%f \n", lookat_matrix(3,1));
	lookat_matrix(3,2) = dotProductZ; printf("%f \n", lookat_matrix(3,2));
	lookat_matrix(3,3) = 1;

}


void normalize (float axisx, float axisy, float axisz, float *normal_x, float *normal_y, float *normal_z) {
	float module = sqrt(pow(axisx, 2) + pow(axisy, 2) + pow(axisz, 2));
	*normal_x = axisx / module;
	*normal_y = axisy / module;
	*normal_z = axisz / module;
}

void crossProduct(float Ax, float Ay, float Az, float Bx, float By, float Bz, float *Rx, float *Ry, float *Rz) {
	*Rx = Ay * Bz - Az * By;
	*Ry = - (Ax * Bz - Az * Bx);
	*Rz = Ax * By - Ay * Bx;
}

float dotProduct(float Ax, float Ay, float Az, float Bx, float By, float Bz) {
	return Ax*Bx + Ay*By + Az*Bz;
}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
