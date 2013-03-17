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
    // Calcular 'vertex_ec'.
    // Calcular 'vertex_cc'.
    // Calcular 'unit_normal_ec'.

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

	unit_normal_ec[0] = vertex_ec[0] / normal_oc[0];
	unit_normal_ec[1] = vertex_ec[1] / normal_oc[1];
	unit_normal_ec[2] = vertex_ec[2] / normal_oc[2];

	unit_normal_ec[0] /= sqrt(pow(normal_oc[0], 2) + pow(normal_oc[1], 2) + pow(normal_oc[2], 2));
	unit_normal_ec[1] /= sqrt(pow(normal_oc[0], 2) + pow(normal_oc[1], 2) + pow(normal_oc[2], 2));
	unit_normal_ec[2] /= sqrt(pow(normal_oc[0], 2) + pow(normal_oc[1], 2) + pow(normal_oc[2], 2));

}

void transpose_matrix(matrix_struct &original, matrix_struct & transposed) {
	matrix_struct transposed = matrix_struct();
	for (int i = 0; i < original.cols_count; i++) {
		for (int j = 0; j < original.rows_count; j++) {
			transposed(j, i) = original(i, j);
		}
	}	
}

void inverse_matrix(matrix_struct &original, matrix_struct & inverted) {

}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
