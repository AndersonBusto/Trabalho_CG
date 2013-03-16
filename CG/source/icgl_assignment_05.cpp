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

#if defined(ICGL_ASSIGNMENT_05_VERTEX_LIGHTING)


// INÍCIO DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO /////////////////////////////

/* Aplica o modelo de iluminação para o cálculo da cor do vértice corrente.
 *
 *   Argumentos de entrada:
 *     'vertex_ec'         : Localização do vértice representada no sistema de coordenadas da câmera (eye coordinates, EC).
 *     'unit_normal_ec'    : Vetor normal à superfície representado no sistema de coordenadas da câmera (EC). Assume-se que
 *                           a norma deste vetor é igual a 1.0f.
 *     'base_color'        : Cor base para o vértice. Utilizada quando a iluminação está desabilitada.
 *     'lighting_enabled'  : Indica se a iluminação está habilitada.
 *     'material_ambient'  : Cor da componente ambiente do material.
 *     'material_diffuse'  : Cor da componente difusa do material.
 *     'material_specular' : Cor da componente especular do material.
 *     'material_shininess': Expoente que define o tamanho do brilho especular do material.
 *     'light_ec'          : Localização da fonte de luz no sistema de coordenadas da câmera (EC).
 *     'light_ambient'     : Intensidade da componente ambiente da fonte de luz.
 *     'light_diffuse'     : Intensidade da componente difusa da fonte de luz.
 *     'light_specular'    : Intensidade da componente especular da fonte de luz.
 *
 *   Argumentos de saída:
 *     'vertex_color'      : Cor do vértice corrente. É igual a 'base_color' caso a iluminação esteja desabilitada ou é
 *                           calculada por meio de modelo de reflexão de Blin-Phong, caso contrário.
 */
void vertex_lighting(const location_struct &vertex_ec, const direction_struct &unit_normal_ec, const color_struct &base_color, bool lighting_enabled, const color_struct &material_ambient, const color_struct &material_diffuse, const color_struct &material_specular, float material_shininess, const location_struct &light_ec, const color_struct &light_ambient, const color_struct &light_diffuse, const color_struct &light_specular, color_struct &vertex_color) {
    // Calcular 'vertex_color'.
}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
