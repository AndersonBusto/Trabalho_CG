/* UNIVERSIDADE FEDERAL FLUMINENSE
 * INTITUTO DE COMPUTA��O
 * DEPARTAMENTO DE CI�NCIA DA COMPUTA��O
 *
 * Este programa foi elaborado pelos professores
 *
 *   Anselmo Antunes Montenegro (anselmo@ic.uff.br),
 *   Leandro Augusto Frata Fernandes (laffernandes@ic.uff.br) e
 *   Marcos de Oliveira Lage Ferreira (mlage@ic.uff.br)
 *
 * como parte do material did�tico da disciplina de Computa��o Gr�fica (TCC-00.179) do curso de
 * Bacharelado em Ci�ncia da Computa��o ministrado no Instituto de Computa��o da Universidade Federal Fluminense.
 *
 * A fim de presentar o funcionamento esperado para o programa, apenas o corpo dos procedimentos associados com a
 * tarefa relacionada a este arquivo deve ser modificado. Procedimentos auxiliares podem ser criados.
 *
 * Copyright (C) 2013 - A.Montenegro, L.A.F.Fernandes, M.Lage.
 */


// INCLUDES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* - ICGL - IC-UFF Graphics Library
 * Conjunto de opera��es utilizadas para ensino de Pipeline Gr�fico no Instito de Computa��o (IC) da Universidade Federal Fluminense (UFF).
 */
#include <icgl.h>

#if defined(ICGL_ASSIGNMENT_05_VERTEX_LIGHTING)


// IN�CIO DA IMPLEMENTA��O DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO /////////////////////////////

/* Aplica o modelo de ilumina��o para o c�lculo da cor do v�rtice corrente.
 *
 *   Argumentos de entrada:
 *     'vertex_ec'         : Localiza��o do v�rtice representada no sistema de coordenadas da c�mera (eye coordinates, EC).
 *     'unit_normal_ec'    : Vetor normal � superf�cie representado no sistema de coordenadas da c�mera (EC). Assume-se que
 *                           a norma deste vetor � igual a 1.0f.
 *     'base_color'        : Cor base para o v�rtice. Utilizada quando a ilumina��o est� desabilitada.
 *     'lighting_enabled'  : Indica se a ilumina��o est� habilitada.
 *     'material_ambient'  : Cor da componente ambiente do material.
 *     'material_diffuse'  : Cor da componente difusa do material.
 *     'material_specular' : Cor da componente especular do material.
 *     'material_shininess': Expoente que define o tamanho do brilho especular do material.
 *     'light_ec'          : Localiza��o da fonte de luz no sistema de coordenadas da c�mera (EC).
 *     'light_ambient'     : Intensidade da componente ambiente da fonte de luz.
 *     'light_diffuse'     : Intensidade da componente difusa da fonte de luz.
 *     'light_specular'    : Intensidade da componente especular da fonte de luz.
 *
 *   Argumentos de sa�da:
 *     'vertex_color'      : Cor do v�rtice corrente. � igual a 'base_color' caso a ilumina��o esteja desabilitada ou �
 *                           calculada por meio de modelo de reflex�o de Blin-Phong, caso contr�rio.
 */
void vertex_lighting(const location_struct &vertex_ec, const direction_struct &unit_normal_ec, const color_struct &base_color, bool lighting_enabled, const color_struct &material_ambient, const color_struct &material_diffuse, const color_struct &material_specular, float material_shininess, const location_struct &light_ec, const color_struct &light_ambient, const color_struct &light_diffuse, const color_struct &light_specular, color_struct &vertex_color) {
    // Calcular 'vertex_color'.
}

// FIM DA IMPLEMENTA��O DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif