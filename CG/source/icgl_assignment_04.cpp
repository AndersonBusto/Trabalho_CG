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
#include <cstdlib>
#include <malloc.h>

#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)


// INÍCIO DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO /////////////////////////////

/* Aplica transformações geométrica à localização do vértice corrente e ao vetor normal associado a ele.
 *
 *   Argumentos de entrada:
 *     'vertex_oc'        : Localização do vértice representada no sistema de coordenadas do objeto (object coordinates, OC).
 *     'normal_oc'        : Vetor normal à superfície representada no sistema de coordenadas do objeto (OC).
 *     'modelview_matrix' : Matriz 4x4 composta pelas transformações de modelo e visualização (view_matrix * model_matrix).
 *     'projection_matrix': Matriz 4x4 de projeção.
 *
 *   Argumentos de saída:
 *     'vertex_ec'        : Localização do vértice representada no sistema de coordenadas da câmera (eye coordinates, EC).
 *     'vertex_cc'        : Localização do vértice representada no sistema coordenadas de recorte (clip coordinates, CC).
 *     'unit_normal_ec'   : Vetor normal à superfície representado no sistema de coordenadas da câmera (EC). Assume-se que
 *                          a norma deste vetor é igual a 1.0f.
 */
void vertex_transformation(const location_struct &vertex_oc, const direction_struct &normal_oc, const matrix_struct &modelview_matrix, const matrix_struct &projection_matrix, location_struct &vertex_ec, location_struct &vertex_cc, direction_struct &unit_normal_ec) {
     //Calcular 'vertex_ec'.
     //Calcular 'vertex_cc'.
     //Calcular 'unit_normal_ec'.

	vertex_ec[0] = vertex_oc[0] * modelview_matrix(0,0) + vertex_oc[1] * modelview_matrix(0,1) + 
		vertex_oc[2] * modelview_matrix(0,2) + vertex_oc[3] * modelview_matrix(0,3);
	vertex_ec[1] = vertex_oc[0] * modelview_matrix(1,0) + vertex_oc[1] * modelview_matrix(1,1) + 
		vertex_oc[2] * modelview_matrix(1,2) + vertex_oc[3] * modelview_matrix(1,3);;
	vertex_ec[2] = vertex_oc[0] * modelview_matrix(2,0) + vertex_oc[1] * modelview_matrix(2,1) + 
		vertex_oc[2] * modelview_matrix(2,2) + vertex_oc[3] * modelview_matrix(2,3);;
	vertex_ec[3] = vertex_oc[0] * modelview_matrix(3,0) + vertex_oc[1] * modelview_matrix(3,1) + 
		vertex_oc[2] * modelview_matrix(3,2) + vertex_oc[3] * modelview_matrix(3,3);;

	vertex_cc[0] = vertex_ec[0] * projection_matrix(0,0) + vertex_ec[1] * projection_matrix(0,1) + 
		vertex_ec[2] * projection_matrix(0,2) + vertex_ec[3] * projection_matrix(0,3);
	vertex_cc[1] = vertex_ec[0] * projection_matrix(1,0) + vertex_ec[1] * projection_matrix(1,1) + 
		vertex_ec[2] * projection_matrix(1,2) + vertex_ec[3] * projection_matrix(1,3);
	vertex_cc[2] = vertex_ec[0] * projection_matrix(2,0) + vertex_ec[1] * projection_matrix(2,1) + 
		vertex_ec[2] * projection_matrix(2,2) + vertex_ec[3] * projection_matrix(2,3);
	vertex_cc[3] = vertex_ec[0] * projection_matrix(3,0) + vertex_ec[1] * projection_matrix(3,1) + 
		vertex_ec[2] * projection_matrix(3,2) + vertex_ec[3] * projection_matrix(3,3);

	matrix_struct transposta = matrix_struct();
	matrix_struct cofatores = matrix_struct();
	matrix_struct transpostaCof = matrix_struct();
	matrix_struct inversa = matrix_struct();

	//inverse_matrix(modelview_matrix, inversa);

	float determinante = det(modelview_matrix);
	matrixCofatores(modelview_matrix, cofatores);
	transpose_matrix(cofatores, transpostaCof);

	inversa(0,0) = transpostaCof(0,0) / determinante;
	inversa(0,1) = transpostaCof(0,1) / determinante;
	inversa(0,2) = transpostaCof(0,2) / determinante;
	inversa(0,3) = transpostaCof(0,3) / determinante;
	inversa(1,0) = transpostaCof(1,0) / determinante;
	inversa(1,1) = transpostaCof(1,1) / determinante;
	inversa(1,2) = transpostaCof(1,2) / determinante;
	inversa(1,3) = transpostaCof(1,3) / determinante;
	inversa(2,0) = transpostaCof(2,0) / determinante;
	inversa(2,1) = transpostaCof(2,1) / determinante;
	inversa(2,2) = transpostaCof(2,2) / determinante;
	inversa(2,3) = transpostaCof(2,3) / determinante;
	inversa(3,0) = transpostaCof(3,0) / determinante;
	inversa(3,1) = transpostaCof(3,1) / determinante;
	inversa(3,2) = transpostaCof(3,2) / determinante;
	inversa(3,3) = transpostaCof(3,3) / determinante;

	transpose_matrix(inversa, transposta);

	unit_normal_ec[0] = normal_oc[0] * transposta(0,0) +  normal_oc[1] *  transposta(0,1) + 
		normal_oc[2] *  transposta(0,2); 
	unit_normal_ec[1] = normal_oc[0] * transposta(1,0) +  normal_oc[1] *  transposta(1,1) + 
		normal_oc[2] *  transposta(1,2); 
	unit_normal_ec[2] = normal_oc[0] * transposta(2,0) +  normal_oc[1] *  transposta(2,1) + 
		normal_oc[2] *  transposta(2,2); 

	unit_normal_ec[0] /= sqrt(pow(unit_normal_ec[0], 2) + pow(unit_normal_ec[1], 2) + pow(unit_normal_ec[2], 2));
	unit_normal_ec[1] /= sqrt(pow(unit_normal_ec[0], 2) + pow(unit_normal_ec[1], 2) + pow(unit_normal_ec[2], 2));
	unit_normal_ec[2] /= sqrt(pow(unit_normal_ec[0], 2) + pow(unit_normal_ec[1], 2) + pow(unit_normal_ec[2], 2));


	//Teste

	matrix_struct transpostaTeste = matrix_struct();
	matrix_struct cofatoresTeste = matrix_struct();
	matrix_struct transpostaCofTeste = matrix_struct();
	matrix_struct inversaTeste = matrix_struct();
	matrix_struct viewTeste = matrix_struct(1, 2, -1, 2, 2, 2, -1, 1, -1, -1, 1, -1, 2, 1, -1, 2);

	float determinanteTeste = det(viewTeste);

	matrixCofatores(viewTeste, cofatoresTeste);
	transpose_matrix(cofatoresTeste, transpostaCofTeste);

	inversaTeste(0,0) = transpostaCofTeste(0,0) / determinanteTeste;
	inversaTeste(0,1) = transpostaCofTeste(0,1) / determinanteTeste;
	inversaTeste(0,2) = transpostaCofTeste(0,2) / determinanteTeste;
	inversaTeste(0,3) = transpostaCofTeste(0,3) / determinanteTeste;
	inversaTeste(1,0) = transpostaCofTeste(1,0) / determinanteTeste;
	inversaTeste(1,1) = transpostaCofTeste(1,1) / determinanteTeste;
	inversaTeste(1,2) = transpostaCofTeste(1,2) / determinanteTeste;
	inversaTeste(1,3) = transpostaCofTeste(1,3) / determinanteTeste;
	inversaTeste(2,0) = transpostaCofTeste(2,0) / determinanteTeste;
	inversaTeste(2,1) = transpostaCofTeste(2,1) / determinanteTeste;
	inversaTeste(2,2) = transpostaCofTeste(2,2) / determinanteTeste;
	inversaTeste(2,3) = transpostaCofTeste(2,3) / determinanteTeste;
	inversaTeste(3,0) = transpostaCofTeste(3,0) / determinanteTeste;
	inversaTeste(3,1) = transpostaCofTeste(3,1) / determinanteTeste;
	inversaTeste(3,2) = transpostaCofTeste(3,2) / determinanteTeste;
	inversaTeste(3,3) = transpostaCofTeste(3,3) / determinanteTeste;

	printf("Teste!!!\n\n");

	printf("%.2f ", inversaTeste(0,0));
	printf("%.2f ", inversaTeste(0,1));
	printf("%.2f ", inversaTeste(0,2));
	printf("%.2f\n", inversaTeste(0,3));
	printf("%.2f ", inversaTeste(1,0));
	printf("%.2f ", inversaTeste(1,1));
	printf("%.2f ", inversaTeste(1,2));
	printf("%.2f\n", inversaTeste(1,3));
	printf("%.2f ", inversaTeste(2,0));
	printf("%.2f ", inversaTeste(2,1));
	printf("%.2f ", inversaTeste(2,2));
	printf("%.2f\n", inversaTeste(2,3));
	printf("%.2f ", inversaTeste(3,0));
	printf("%.2f ", inversaTeste(3,1));
	printf("%.2f ", inversaTeste(3,2));
	printf("%.2f\n", inversaTeste(3,3));


	transpose_matrix(inversaTeste, transpostaTeste);

	printf("TRANSPOSTA!!!\n\n");

	printf("%.2f ", transpostaTeste(0,0));
	printf("%.2f ", transpostaTeste(0,1));
	printf("%.2f ", transpostaTeste(0,2));
	printf("%.2f\n", transpostaTeste(0,3));
	printf("%.2f ", transpostaTeste(1,0));
	printf("%.2f ", transpostaTeste(1,1));
	printf("%.2f ", transpostaTeste(1,2));
	printf("%.2f\n", transpostaTeste(1,3));
	printf("%.2f ", transpostaTeste(2,0));
	printf("%.2f ", transpostaTeste(2,1));
	printf("%.2f ", transpostaTeste(2,2));
	printf("%.2f\n", transpostaTeste(2,3));
	printf("%.2f ", transpostaTeste(3,0));
	printf("%.2f ", transpostaTeste(3,1));
	printf("%.2f ", transpostaTeste(3,2));
	printf("%.2f\n", transpostaTeste(3,3));

}

void inverse_matrix(const matrix_struct &modelview_matrix, matrix_struct &matrizInvertida) {

	float s0 = modelview_matrix(0,0) * modelview_matrix(1,1) - modelview_matrix(1,0) * modelview_matrix(0,1);
	float s1 = modelview_matrix(0,0) * modelview_matrix(1,2) - modelview_matrix(1,0) * modelview_matrix(0,2);
	float s2 = modelview_matrix(0,0) * modelview_matrix(1,3) - modelview_matrix(1,0) * modelview_matrix(0,3);
	float s3 = modelview_matrix(0,1) * modelview_matrix(1,2) - modelview_matrix(1,1) * modelview_matrix(0,2);
	float s4 = modelview_matrix(0,1) * modelview_matrix(1,3) - modelview_matrix(1,1) * modelview_matrix(0,3);
	float s5 = modelview_matrix(0,2) * modelview_matrix(1,3) - modelview_matrix(1,2) * modelview_matrix(0,3);

	float c5 = modelview_matrix(2,2) * modelview_matrix(3,3) - modelview_matrix(3,2) * modelview_matrix(2,3);
	float c4 = modelview_matrix(2,1) * modelview_matrix(3,3) - modelview_matrix(3,1) * modelview_matrix(2,3);
	float c3 = modelview_matrix(2,1) * modelview_matrix(3,2) - modelview_matrix(3,1) * modelview_matrix(2,2);
	float c2 = modelview_matrix(2,0) * modelview_matrix(3,3) - modelview_matrix(3,0) * modelview_matrix(2,3);
	float c1 = modelview_matrix(2,0) * modelview_matrix(3,2) - modelview_matrix(3,0) * modelview_matrix(2,2);
	float c0 = modelview_matrix(2,0) * modelview_matrix(3,1) - modelview_matrix(3,0) * modelview_matrix(2,1);
    

    // Should check for 0 determinant

    float invdet  = 1 / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

	matrizInvertida(0,0) = ( modelview_matrix(1,1) * c5 -  modelview_matrix(1,2) * c4 +  modelview_matrix(1,3) * c3) * invdet;
	matrizInvertida(0,1) = ( -modelview_matrix(0,1) * c5 +  modelview_matrix(0,2) * c4 -  modelview_matrix(0,3) * c3) * invdet;
	matrizInvertida(0,2) = ( modelview_matrix(3,1) * s5 -  modelview_matrix(3,2) * s4 +  modelview_matrix(3,3) * s3) * invdet;
	matrizInvertida(0,3) = ( -modelview_matrix(2,1) * s5 +  modelview_matrix(2,2) * s4 -  modelview_matrix(2,3) * s3) * invdet;

	matrizInvertida(1,0) = (- modelview_matrix(1,0) * c5 +  modelview_matrix(1,2) * c2 -  modelview_matrix(1,3) * c1) * invdet;
	matrizInvertida(1,1) = ( modelview_matrix(0,0) * c5 -  modelview_matrix(0,2) * c2 +  modelview_matrix(0,3) * c1) * invdet;
	matrizInvertida(1,2) = (- modelview_matrix(3,0) * s5 +  modelview_matrix(3,2) * s2 -  modelview_matrix(3,3) * s1) * invdet;
	matrizInvertida(1,3) = ( modelview_matrix(2,0) * s5 -  modelview_matrix(2,2) * s2 +  modelview_matrix(2,3) * s1) * invdet;
	
	matrizInvertida(2,0) = ( modelview_matrix(1,0) * c4 -  modelview_matrix(1,1) * c2 +  modelview_matrix(1,3) * c0) * invdet;
	matrizInvertida(2,1) = ( -modelview_matrix(0,0) * c4 +  modelview_matrix(0,1) * c2 -  modelview_matrix(0,3) *c0) * invdet;
	matrizInvertida(2,2) = ( modelview_matrix(3,0) * s4 -  modelview_matrix(3,1) * s2 +  modelview_matrix(3,3) * s0) * invdet;
	matrizInvertida(2,3) = ( -modelview_matrix(2,0) * s4 +  modelview_matrix(2,1) * s2 - modelview_matrix(2,3) * s0) * invdet;
   
	matrizInvertida(3,0) = ( -modelview_matrix(1,0) * c3 + modelview_matrix(1,1) * c1 -  modelview_matrix(1,2) * c0) * invdet;
	matrizInvertida(3,1) = ( modelview_matrix(0,0) * c3 -  modelview_matrix(0,1) * c1 +  modelview_matrix(0,2) * c0) * invdet;
	matrizInvertida(3,2) = ( -modelview_matrix(3,0) * s3 +  modelview_matrix(3,1) * s1 -  modelview_matrix(3,2) * s0) * invdet;
	matrizInvertida(3,3) = ( modelview_matrix(2,0) * s3 -  modelview_matrix(2,1) * s1 +  modelview_matrix(2,2) * s0) * invdet;
}

float** alocaMatriz()
   {
       float **p; 
	   p =  (float**) malloc(3 * sizeof (float*));
       
       int i;
       for(i=0; i < 3; i++)
               p[i] = (float*) malloc(3 * sizeof (float));

       return p;       
   }

float det(matrix_struct matrix){
	return matrix(0,0) * cofator(0,0, matrix) - matrix(0,1) * cofator(0,1, matrix) + matrix(0,2)
		* cofator(0,2,matrix) - matrix(0,3) * cofator(0,3,matrix);
}


float det3(float** matrix){
	return (matrix[0][0] * matrix[1][1] * matrix[2][2])
		+  (matrix[0][1] * matrix[1][2] * matrix[2][0])
		+  (matrix[0][2] * matrix[1][0] * matrix[2][1])
		
		-  (matrix[2][0] * matrix[1][1] * matrix[0][2])
		-  (matrix[2][1] * matrix[1][2] * matrix[0][0])
		-  (matrix[2][2] * matrix[1][0] * matrix[0][1])
		;

}

float cofator(int linha, int coluna, matrix_struct matrix){
	float** matrixAux;
	matrixAux = alocaMatriz();
	int pc = 0, pl = 0, i, j;
	for(i=0; i<=3; i++){
		for(j=0; j<=3; j++){
			if(linha != i && coluna != j){
				matrixAux[pl][pc] = matrix(i,j);
				pc++;
			}
		}
		if(pc!=0){
			pl++; pc=0;		
		}
	}
	return det3(matrixAux);
}

void matrixCofatores(matrix_struct original, matrix_struct &cofatores){
	cofatores(0,0) = cofator(0,0,original);
	cofatores(0,1) = -cofator(0,1,original);
	cofatores(0,2) = cofator(0,2,original);
	cofatores(0,3) = -cofator(0,3,original);
	cofatores(1,0) = -cofator(1,0,original);
	cofatores(1,1) = cofator(1,1,original);
	cofatores(1,2) = -cofator(1,2,original);
	cofatores(1,3) = cofator(1,3,original);
	cofatores(2,0) = cofator(2,0,original);
	cofatores(2,1) = -cofator(2,1,original);
	cofatores(2,2) = cofator(2,2,original);
	cofatores(2,3) = -cofator(2,3,original);
	cofatores(3,0) = -cofator(3,0,original);
	cofatores(3,1) = cofator(3,1,original);
	cofatores(3,2) = -cofator(3,2,original);
	cofatores(3,3) = cofator(3,3,original);
}

void transpose_matrix(const matrix_struct &original, matrix_struct &transposed) {
	//transposed = matrix_struct();
	for (int i = 0; i < original.cols_count; i++) {
		for (int j = 0; j < original.rows_count; j++) {
			transposed(i, j) = original(j, i);
		}
	}	
}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
