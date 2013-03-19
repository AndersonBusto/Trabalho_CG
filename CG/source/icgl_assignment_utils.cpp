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
 * Procedimentos auxiliares dever ser declarados neste arquivo.
 *
 * Copyright (C) 2013 - A.Montenegro, L.A.F.Fernandes, M.Lage.
 */


// INCLUDES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* - ICGL - IC-UFF Graphics Library
 * Conjunto de operações utilizadas para ensino de Pipeline Gráfico no Instito de Computação (IC) da Universidade Federal Fluminense (UFF).
 */
#include <icgl.h>

// DECLARAÇÃO DAS ROTINAS ÚTEIS IMPLEMENTADAS PELO ALUNO ////////////////////////////////////////////////////////////////////

void normalize (direction_struct &vector) {
	float module = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	if(module > 0.0) {
		vector.x /= module;
	    vector.y/= module;
		vector.z /= module;
	}
}

void crossProduct(direction_struct a, direction_struct b, direction_struct &r) {
	r.x = a.y * b.z - a.z * b.y;
	r.y = - (a.x * b.z) + (a.z * b.x);
	r.z = a.x * b.y - a.y * b.x;
}

float dotProduct(direction_struct a, direction_struct b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

void inverse_matrix(const matrix_struct &original, matrix_struct &inverse) {
	matrix_struct cofatores = matrix_struct();
	matrix_struct transposeCof = matrix_struct();

	float determinant = det4(original);
	matrixCofatores(original, cofatores);
	transpose_matrix(cofatores, transposeCof);

	inverse(0,0) = transposeCof(0,0) / determinant;
	inverse(0,1) = transposeCof(0,1) / determinant;
	inverse(0,2) = transposeCof(0,2) / determinant;
	inverse(0,3) = transposeCof(0,3) / determinant;
	inverse(1,0) = transposeCof(1,0) / determinant;
	inverse(1,1) = transposeCof(1,1) / determinant;
	inverse(1,2) = transposeCof(1,2) / determinant;
	inverse(1,3) = transposeCof(1,3) / determinant;
	inverse(2,0) = transposeCof(2,0) / determinant;
	inverse(2,1) = transposeCof(2,1) / determinant;
	inverse(2,2) = transposeCof(2,2) / determinant;
	inverse(2,3) = transposeCof(2,3) / determinant;
	inverse(3,0) = transposeCof(3,0) / determinant;
	inverse(3,1) = transposeCof(3,1) / determinant;
	inverse(3,2) = transposeCof(3,2) / determinant;
	inverse(3,3) = transposeCof(3,3) / determinant;
}

float** alocateMatriz()
   {
       float **p; 
	   p =  (float**) malloc(3 * sizeof (float*));
       
       int i;
       for(i=0; i < 3; i++)
               p[i] = (float*) malloc(3 * sizeof (float));

       return p;       
   }

float det4(matrix_struct matrix){
	return matrix(0,0) * cofator(0,0, matrix) - matrix(0,1) * cofator(0,1, matrix) + matrix(0,2)
		* cofator(0,2,matrix) - matrix(0,3) * cofator(0,3,matrix);
}


float det3(float** matrix){
	return (matrix[0][0] * matrix[1][1] * matrix[2][2])
		+  (matrix[0][1] * matrix[1][2] * matrix[2][0])
		+  (matrix[0][2] * matrix[1][0] * matrix[2][1])
		-  (matrix[2][0] * matrix[1][1] * matrix[0][2])
		-  (matrix[2][1] * matrix[1][2] * matrix[0][0])
		-  (matrix[2][2] * matrix[1][0] * matrix[0][1]);
}

float cofator(int row, int column, matrix_struct matrix){
	float** matrixAux;
	matrixAux = alocateMatriz();
	int indexColumn = 0, indexRow = 0, i, j;
	for(i=0; i<=3; i++){
		for(j=0; j<=3; j++){
			if(row != i && column != j){
				matrixAux[indexRow][indexColumn] = matrix(i,j);
				indexColumn++;
			}
		}
		if(indexColumn != 0){
			indexRow++;
			indexColumn = 0;		
		}
	}
	return det3(matrixAux);
}

void matrixCofatores(matrix_struct original, matrix_struct &cofatores){
	cofatores(0,0) = cofator(0, 0, original);
	cofatores(0,1) = -cofator(0, 1, original);
	cofatores(0,2) = cofator(0, 2, original);
	cofatores(0,3) = -cofator(0, 3, original);
	cofatores(1,0) = -cofator(1, 0, original);
	cofatores(1,1) = cofator(1, 1, original);
	cofatores(1,2) = -cofator(1, 2, original);
	cofatores(1,3) = cofator(1, 3, original);
	cofatores(2,0) = cofator(2, 0, original);
	cofatores(2,1) = -cofator(2, 1, original);
	cofatores(2,2) = cofator(2, 2, original);
	cofatores(2,3) = -cofator(2, 3, original);
	cofatores(3,0) = -cofator(3, 0, original);
	cofatores(3,1) = cofator(3, 1, original);
	cofatores(3,2) = -cofator(3, 2, original);
	cofatores(3,3) = cofator(3, 3, original);
}

void transpose_matrix(const matrix_struct &original, matrix_struct &transposed) {
	for (int i = 0; i < original.cols_count; i++) {
		for (int j = 0; j < original.rows_count; j++) {
			transposed(j, i) = original(i, j);
		}
	}	
}

float maxV(float a, float b) {
	return a > b ? a : b;
}



// FIM DA DECLARAÇÃO DAS ROTINAS ÚTEIS IMPLEMENTADAS PELO ALUNO /////////////////////////////////////////////////////////////
