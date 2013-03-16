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

#if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)


// INÍCIO DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO /////////////////////////////

/* Rasteriza o segmento de reta corrente e atualiza os buffers de cor (framebuffer) e de profundidade (dephtbuffer).
 *
 *   Argumentos de entrada:
 *     'segment'                        : Segmento de reta a ser rasterizado.
 *     'viewport_x', 'viewport_y', 'viewport_width', 'viewport_height': Posição e tamanho da janela de visualização (viewport).
 *     'texture_mapping_enabled'        : Indica se o mapeamento de textura está habilitado.
 *     'texture_width', 'texture_height': Largura e altura da imagem de textura ('texture_rgba').
 *     'texture_rgba'                   : Imagem de textura. Cada texel é representado por quatro compnentes de cor no espaço
 *                                        RGBA, onde cada componente pode assumir valores no intervalo [0.0f, 1.0f]. A imagem
 *                                        está organizada por linha no buffer. Ou seja, o índice do coponente de cor c do
 *                                        texel de posição (x,y) na imagem é calculado como i = (y*texture_width + x)*4 + c.
 *     'depth_test_enabled'             : Indica se o teste de profundidade (depth test) está habilitado.
 *     'buffer_width', 'buffer_height'  : Largura e alrura dos buffers de cor ('framebuffer') de profundidade ('depthbuffer').
 *
 *   Argumentos de saída:
 *     'framebuffer'                    : Imagem resultante. Cada pixel é representado por quatro compnentes de cor no espaço
 *                                        RGBA, onde cada componente pode assumir valores no intervalo [0.0f, 1.0f]. A imagem
 *                                        está organizada por linha no buffer. Ou seja, o índice do coponente de cor c do
 *                                        pixel de posição (x,y) na imagem é calculado como i = (y*buffer_width + x)*4 + c.
 *     'depthbuffer'                    : Imagem de profundidade resultante. Cada pixel é representado uma compnentes de
 *                                        profundidade que pode assumir valores no intervalo [0.0f, 1.0f], onde 0.0f significa
 *                                        sobre o near plane e 1.0f sobre o far plane. A imagem está organizada por linha no
 *                                        buffer. Ou seja, o índice do coponente de posição (x,y) na imagem é calculado como
 *                                        i = y*buffer_width + x.
 */
void rasterize_segment(const segment_struct &segment, int viewport_x, int viewport_y, int viewport_width, int viewport_height, bool texture_mapping_enabled, int texture_width, int texture_height, const float *texture_rgba, bool depth_test_enabled, int buffer_width, int buffer_height, float *framebuffer, float *depthbuffer) {
    // Atualizar 'framebuffer'.
    // Atualizar 'depthbuffer'.
}

/* Rasteriza o triângulo corrente e atualiza os buffers de cor (framebuffer) e de profundidade (dephtbuffer).
 *
 *   Argumentos de entrada:
 *     'triangle'                       : Triângulo a ser rasterizado.
 *     'viewport_x', 'viewport_y', 'viewport_width', 'viewport_height': Posição e tamanho da janela de visualização (viewport).
 *     'texture_mapping_enabled'        : Indica se o mapeamento de textura está habilitado.
 *     'texture_width', 'texture_height': Largura e altura da imagem de textura ('texture_rgba').
 *     'texture_rgba'                   : Imagem de textura. Cada texel é representado por quatro compnentes de cor no espaço
 *                                        RGBA, onde cada componente pode assumir valores no intervalo [0.0f, 1.0f]. A imagem
 *                                        está organizada por linha no buffer. Ou seja, o índice do coponente de cor c do
 *                                        texel de posição (x,y) na imagem é calculado como i = (y*texture_width + x)*4 + c.
 *     'depth_test_enabled'             : Indica se o teste de profundidade (depth test) está habilitado.
 *     'buffer_width', 'buffer_height'  : Largura e alrura dos buffers de cor ('framebuffer') de profundidade ('depthbuffer').
 *
 *   Argumentos de saída:
 *     'framebuffer'                    : Imagem resultante. Cada pixel é representado por quatro compnentes de cor no espaço
 *                                        RGBA, onde cada componente pode assumir valores no intervalo [0.0f, 1.0f]. A imagem
 *                                        está organizada por linha no buffer. Ou seja, o índice do coponente de cor c do
 *                                        pixel de posição (x,y) na imagem é calculado como i = (y*buffer_width + x)*4 + c.
 *     'depthbuffer'                    : Imagem de profundidade resultante. Cada pixel é representado uma compnentes de
 *                                        profundidade que pode assumir valores no intervalo [0.0f, 1.0f], onde 0.0f significa
 *                                        sobre o near plane e 1.0f sobre o far plane. A imagem está organizada por linha no
 *                                        buffer. Ou seja, o índice do coponente de posição (x,y) na imagem é calculado como
 *                                        i = y*buffer_width + x.
 */
void rasterize_triangle(const triangle_struct &triangle, int viewport_x, int viewport_y, int viewport_width, int viewport_height, bool texture_mapping_enabled, int texture_width, int texture_height, const float *texture_rgba, bool depth_test_enabled, int buffer_width, int buffer_height, float *framebuffer, float *depthbuffer) {
    // Atualizar 'framebuffer'.
    // Atualizar 'depthbuffer'.
}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
