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

#if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)


// INÍCIO DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO /////////////////////////////

/* Monta segmentos de reta a partir das listas de propriedades de vértices informadas. Esta rotina também é responsável por
 * realizar o recorte (clipping) das primitivas que não estão completamente contidas no volume de visualização (frustum).
 *
 *   Argumentos de entrada:
 *     'vertices_cc'             : Lista de localização de vértices no sistema de coordenadas de recorte (clip coordinates, CC).
 *                                 O tamanho desta lista é sempre um múltiplo de dois, sendo que cada par corresponde aos
 *                                 vértices de um segmento de reta.
 *     'vertices_texcoords'      : Lista de coordenadas de textura dos vértices. Os elementos desta lista possuem relação
 *                                 um-para-um com os elementos de 'vertices_cc'.
 *     'vertices_texture_ids'    : Lista de identificadores de textura dos vértices. Os elementos desta lista possuem relação
 *                                 um-para-um com os elementos de 'vertices_cc'. Os dois vértices de um mesmo segmento de reta
 *                                 possuem o mesmo identificador de textura.
 *
 *   Argumentos de saída:
 *     'primitives'              : Lista de segmentos de reta completamente contidos no volume de visualização.
 */
void make_segments(const std::vector<location_struct> &vertices_cc, const std::vector<color_struct> &vertices_colors, const std::vector<texcoord_struct> &vertices_texcoords, const std::vector<int> &vertices_texture_ids, std::vector<segment_struct> &primitives) {
    // Calcular 'primitives'.
}

/* Monta triângulos a partir das listas de propriedades de vértices informadas. Esta rotina também é responsável por realizar
 * o recorte (clipping) das primitivas que não estão completamente contidas no volume de visualização (frustum) e a supressão
 * (culling) de triângulos conforme a orientação assumida para as faces dos modelos geométricos.
 *
 *   Argumentos de entrada:
 *     'vertices_cc'             : Lista de localização de vértices no sistema de coordenadas de recorte (clip coordinates, CC).
 *                                 O tamanho desta lista é sempre um múltiplo de três, sendo que cada trio corresponde aos
 *                                 vértices de um triângulo.
 *     'vertices_texcoords'      : Lista de coordenadas de textura dos vértices. Os elementos desta lista possuem relação
 *                                 um-para-um com os elementos de 'vertices_cc'.
 *     'vertices_texture_ids'    : Lista de identificadores de textura dos vértices. Os elementos desta lista possuem relação
 *                                 um-para-um com os elementos de 'vertices_cc'. Os três vértices de um mesmo triângulo possuem
 *                                 o mesmo identificador de textura.
 *     'backface_culling_enabled': Indica se a supressão de faces traseiras está habilitada.
 *     'front_face_orientation'  : Orientação assumida para as faces frontais, podendo ser sentido horário (clockwise,
 *                                 'cw_orientation') ou sentido anti-horário (counterclockwise, 'ccw_orientation').
 *
 *   Argumentos de saída:
 *     'primitives'              : Lista de triângulos completamente contidos no volume de visualização e orientadas conforme a
 *                                 convensão para faces frontais, caso a supressão de faces traseiras esteja habilitada.
 */
void make_triangles(const std::vector<location_struct> &vertices_cc, const std::vector<color_struct> &vertices_colors, const std::vector<texcoord_struct> &vertices_texcoords, const std::vector<int> &vertices_texture_ids, bool backface_culling_enabled, orientation_type front_face_orientation, std::vector<triangle_struct> &primitives) {
    // Calcular 'primitives'.
}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
