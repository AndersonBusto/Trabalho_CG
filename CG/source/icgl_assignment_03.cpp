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

#if defined(ICGL_ASSIGNMENT_03_PERSPECTIVE_PROJECTION)


// INÍCIO DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO /////////////////////////////

/* Atribui ao argumento de saída 'perspective_matrix' uma matriz de projeção perspectiva.
 *
 *   Argumentos de entrada:
 *     'fovy'              : Ângulo do campo de visão da câmera (em graus) na direção y.
 *     'aspect'            : Raio aspecto que determina o campo de visão da direção x. O raio aspecto é a taxa entre a
 *                           largura e altura da imagem.
 *     'znear', 'zfar'     : Distância dos planos de corte em relação ao observador. Esses valores são sempre positivos.
 *
 *   Argumentos de saída:
 *     'perspective_matrix': Matriz 4x4 de projeção perspectiva.
 */
void make_perspective_matrix(float fovy, float aspect, float znear, float zfar, matrix_struct &perspective_matrix) {
    // Calcular 'perspective_matrix'.
}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
