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
	printf("eyex %f \n", eyex);printf("eyey %f \n", eyey); printf("eyez %f \n", eyez);
	printf("centerx %f \n", centerx);printf("centery %f \n", centery); printf("centerz %f \n", centerz);
	printf("upx %f \n", upx);printf("upy %f \n", upy); printf("upz %f \n", upz);

	float dotProductX, dotProductY, dotProductZ;
	float normal_zx, normal_zy, normal_zz;
	float normal_xx, normal_xy, normal_xz;
	float normal_yx, normal_yy, normal_yz;
	float x_x, x_y, x_z;
	float y_x, y_y, y_z;
	float z_x = eyex - centerx;
	float z_y = eyey - centery;
	float z_z = eyez - centerz;


	normalize(&z_x, &z_y, &z_z);

	crossProduct(upx, upy, upz, z_x, z_y, z_z, &x_x, &x_y, &x_z);
	
	normalize(&x_x, &x_y, &x_z);
	    
	crossProduct(z_x, z_y, z_z, x_x, x_y, x_z, &y_x, &y_y, &y_z);

	normalize(&y_x, &y_y, &y_z);  
	//&y_x, &y_y, &y_z
	/*normal_yx = y_x;
	normal_yy = y_y;
	normal_yz = y_z;*/

	/*printf("normal_zx %f \n", normal_zx);
	printf("normal_zy %f \n", normal_zy);
	printf("normal_zz %f \n", normal_zz);

	printf("normal_xx %f \n", normal_xx);
	printf("normal_xy %f \n", normal_xy);
	printf("normal_xz %f \n", normal_xz);

	printf("normal_yx %f \n", normal_yx);
	printf("normal_yy %f \n", normal_yy);
	printf("normal_yz %f \n", normal_yz);*/
	printf("y_x %f \n", y_x);
	printf("y_x %f \n", y_x);
	printf("y_z %f \n", y_z);

	dotProductX =  dotProduct(x_x, x_y, x_z, eyex, eyey, eyez);
	dotProductY =  dotProduct(y_x, y_y, y_z, eyex, eyey, eyez);
	dotProductZ =  dotProduct(z_x, z_y, z_z, eyex, eyey, eyez);
	
	printf("dot Product x %f \n", dotProductX);
	printf("dot Product y %f \n", dotProductY);
	printf("dot Product z %f \n", dotProductZ);

	//lookat_matrix = matrix_struct( x_x,y_x,z_x,0,x_y,y_y,z_y,0,x_z,y_z, z_z,0,dotProductX, dotProductY, dotProductZ,1);

	lookat_matrix = matrix_struct();
	lookat_matrix(0,0) = x_x; printf("(0,0) %f \n", lookat_matrix(0,0));
	lookat_matrix(0,1) = y_x; printf("(0,1) %f \n", lookat_matrix(0,1));
	lookat_matrix(0,2) = z_x; printf("(0,2) %f \n", lookat_matrix(0,2));
	lookat_matrix(0,3) = eyex;			printf("(0,3) %f \n", lookat_matrix(0,3));

	lookat_matrix(1,0) = x_y; printf("(1,0) %f \n", lookat_matrix(1,0));
	lookat_matrix(1,1) = y_y; printf("(1,1) %f \n", lookat_matrix(1,1));
	lookat_matrix(1,2) = z_y; printf("(1,2) %f \n", lookat_matrix(1,2));
	lookat_matrix(1,3) = eyey;			printf("(1,3) %f \n", lookat_matrix(1,3));
	
	lookat_matrix(2,0) = x_z; printf("(2,0) %f \n", lookat_matrix(2,0));
	lookat_matrix(2,1) = y_z; printf("(2,1) %f \n", lookat_matrix(2,1));
	lookat_matrix(2,2) = z_z; printf("(2,2) %f \n", lookat_matrix(2,2));
	lookat_matrix(2,3) = eyez;			printf("(2,3) %f \n", lookat_matrix(2,3));

	lookat_matrix(3,0) = 0.0f; printf("(3,0) %f \n", lookat_matrix(3,0));
	lookat_matrix(3,1) = 0.0f; printf("(3,1) %f \n", lookat_matrix(3,1));
	lookat_matrix(3,2) = 0.0f; printf("(3,2) %f \n", lookat_matrix(3,2));
	lookat_matrix(3,3) = 1.0f;			  printf("(3,3) %f \n", lookat_matrix(3,3));

}


void normalize (float *axisx, float *axisy, float *axisz) {
	float module = sqrt(pow(*axisx, 2) + pow(*axisy, 2) + pow(*axisz, 2));
	if(module > 0.0){
		*axisx /= module;
	    *axisy /= module;
		*axisz /= module;
	}
}

void crossProduct(float Ax, float Ay, float Az, float Bx, float By, float Bz, float *Rx, float *Ry, float *Rz) {
	*Rx = Ay * Bz - Az * By;
	*Ry = - (Ax * Bz) + (Az * Bx);
	*Rz = Ax * By - Ay * Bx;
}

float dotProduct(float Ax, float Ay, float Az, float Bx, float By, float Bz) {
	return Ax*Bx + Ay*By + Az*Bz;
}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
