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
	
	for (int i = 0; i < vertices_cc.size(); i += 2) {
		segment_struct aux = segment_struct();
		aux.texture_id = vertices_texture_ids[i];
		aux.color[i].r = vertices_colors[i].r;
		aux.color[i].g = vertices_colors[i].g;
		aux.color[i].b = vertices_colors[i].b;
		aux.color[i].a = vertices_colors[i].a;
		aux.texcoord[i].u = vertices_texcoords[i].u;
		aux.texcoord[i].v = vertices_texcoords[i].v;
		aux.vertex_cc[i].x = vertices_cc[i].x;
		aux.vertex_cc[i].y = vertices_cc[i].y;
		aux.vertex_cc[i].z = vertices_cc[i].z;
		aux.vertex_cc[i].w = vertices_cc[i].w;
		
		aux.color[i + 1].r = vertices_colors[i + 1].r;
		aux.color[i + 1].g = vertices_colors[i + 1].g;
		aux.color[i + 1].b = vertices_colors[i + 1].b;
		aux.color[i + 1].a = vertices_colors[i + 1].a;
		aux.texcoord[i + 1].u = vertices_texcoords[i + 1].u;
		aux.texcoord[i + 1].v = vertices_texcoords[i + 1].v;
		aux.vertex_cc[i + 1].x = vertices_cc[i + 1].x;
		aux.vertex_cc[i + 1].y = vertices_cc[i + 1].y;
		aux.vertex_cc[i + 1].z = vertices_cc[i + 1].z;
		aux.vertex_cc[i + 1].w = vertices_cc[i + 1].w;
		primitives.push_back(aux);  
	}
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
	float p_x ,p_y, p_z;
	triangle_struct aux = triangle_struct();

	for (int i = 0; i < vertices_cc.size(); i += 3) {		
		aux.texture_id = vertices_texture_ids[i];
		aux.color[i].r = vertices_colors[i].r;
		aux.color[i].g = vertices_colors[i].g;
		aux.color[i].b = vertices_colors[i].b;
		aux.color[i].a = vertices_colors[i].a;
		aux.texcoord[i].u = vertices_texcoords[i].u;
		aux.texcoord[i].v = vertices_texcoords[i].v;
		aux.vertex_cc[i].x = vertices_cc[i].x;
		aux.vertex_cc[i].y = vertices_cc[i].y;
		aux.vertex_cc[i].z = vertices_cc[i].z;
		aux.vertex_cc[i].w = vertices_cc[i].w;
		
		aux.color[i + 1].r = vertices_colors[i + 1].r;
		aux.color[i + 1].g = vertices_colors[i + 1].g;
		aux.color[i + 1].b = vertices_colors[i + 1].b;
		aux.color[i + 1].a = vertices_colors[i + 1].a;
		aux.texcoord[i + 1].u = vertices_texcoords[i + 1].u;
		aux.texcoord[i + 1].v = vertices_texcoords[i + 1].v;
		aux.vertex_cc[i + 1].x = vertices_cc[i + 1].x;
		aux.vertex_cc[i + 1].y = vertices_cc[i + 1].y;
		aux.vertex_cc[i + 1].z = vertices_cc[i + 1].z;
		aux.vertex_cc[i + 1].w = vertices_cc[i + 1].w;

		aux.color[i + 2].r = vertices_colors[i + 2].r;
		aux.color[i + 2].g = vertices_colors[i + 2].g;
		aux.color[i + 2].b = vertices_colors[i + 2].b;
		aux.color[i + 2].a = vertices_colors[i + 2].a;
		aux.texcoord[i + 2].u = vertices_texcoords[i + 2].u;
		aux.texcoord[i + 2].v = vertices_texcoords[i + 2].v;
		aux.vertex_cc[i + 2].x = vertices_cc[i + 2].x;
		aux.vertex_cc[i + 2].y = vertices_cc[i + 2].y;
		aux.vertex_cc[i + 2].z = vertices_cc[i + 2].z;
		aux.vertex_cc[i + 2].w = vertices_cc[i + 2].w;
	}

	if(backface_culling_enabled) {
		for (int i = 0; i < vertices_cc.size(); i+=3) {			
			location_struct  p1  = vertices_cc[i];
			location_struct   p2  = vertices_cc[i + 1];
			location_struct   p3  = vertices_cc[i + 2];
			crossProduct(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z, p3.x - p2.x, p3.y - p2.y, p3.z - p2.z, &p_x , &p_y, &p_z);
			if(ccw_orientation && p_z < 0.0f) {			
				primitives.push_back(aux);
			}
			else if (p_z > 0.0f) {
				primitives.push_back(aux);
			}
		}
	}
	else {
		primitives.push_back(aux);
	}
}

// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
