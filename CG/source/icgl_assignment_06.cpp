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
	segment_struct aux = segment_struct();
	
	for (int i = 0; i < vertices_cc.size(); i+= 2) {		
		for (int j = 0; j < 2; j++) {
			aux.texture_id = vertices_texture_ids[i+j];	
			aux.color[j].r = vertices_colors[i+j].r;
			aux.color[j].g = vertices_colors[i+j].g;
			aux.color[j].b = vertices_colors[i+j].b;
			aux.color[j].a = vertices_colors[i+j].a;
			aux.texcoord[j].u = vertices_texcoords[i+j].u;
			aux.texcoord[j].v = vertices_texcoords[i+j].v;
			aux.vertex_cc[j].x = vertices_cc[i+j].x;
			aux.vertex_cc[j].y = vertices_cc[i+j].y;
			aux.vertex_cc[j].z = vertices_cc[i+j].z;
			aux.vertex_cc[j].w = vertices_cc[i+j].w;
			aux.color[j].r = vertices_colors[i+j].r;
			aux.color[j].g = vertices_colors[i+j].g;
			aux.color[j].b = vertices_colors[i+j].b;
			aux.color[j].a = vertices_colors[i+j].a;
		}
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
	//float p_x ,p_y, p_z;
	direction_struct p = direction_struct();
	location_struct p1, p2, p3;
	direction_struct aux1 = direction_struct();
	direction_struct aux2 = direction_struct();
	bool in = true;

	std::vector<triangle_struct> aux;
	triangle_struct triangle = triangle_struct();
	
	for (int i = 0; i < vertices_cc.size(); i+= 3) {		
		for (int j = 0; j < 3; j++) {
			triangle.texture_id = vertices_texture_ids[i+j];	
			triangle.color[j].r = vertices_colors[i+j].r;
			triangle.color[j].g = vertices_colors[i+j].g;
			triangle.color[j].b = vertices_colors[i+j].b;
			triangle.color[j].a = vertices_colors[i+j].a;
			triangle.texcoord[j].u = vertices_texcoords[i+j].u;
			triangle.texcoord[j].v = vertices_texcoords[i+j].v;
			triangle.vertex_cc[j].x = vertices_cc[i+j].x;
			triangle.vertex_cc[j].y = vertices_cc[i+j].y;
			triangle.vertex_cc[j].z = vertices_cc[i+j].z;
			triangle.vertex_cc[j].w = vertices_cc[i+j].w;
			triangle.color[j].r = vertices_colors[i+j].r;
			triangle.color[j].g = vertices_colors[i+j].g;
			triangle.color[j].b = vertices_colors[i+j].b;
			triangle.color[j].a = vertices_colors[i+j].a;

			bool test_vertex = !(triangle.vertex_cc[j].x > -triangle.vertex_cc[j].w && triangle.vertex_cc[j].x < triangle.vertex_cc[j].w) || 
				!(triangle.vertex_cc[j].y > -triangle.vertex_cc[j].w && triangle.vertex_cc[j].y < triangle.vertex_cc[j].w) ||
				!(triangle.vertex_cc[j].z > -triangle.vertex_cc[j].w && triangle.vertex_cc[j].z < triangle.vertex_cc[j].w);

			if(test_vertex)
				in = false;

		}

		if(in)
			aux.push_back(triangle);
		else
			in = true;		
	}

	if(backface_culling_enabled) {		
		for (int i = 0; i < aux.size(); i++) {
			p1  = aux[i].vertex_cc[0];
			p2  = aux[i].vertex_cc[1];
			p3  = aux[i].vertex_cc[2];
			aux1.x = p2.x - p1.x;
			aux1.y = p2.y - p1.y;
			aux1.z = p2.z - p1.z;
			aux2.x = p3.x - p1.x;
			aux2.y = p3.y - p1.y;
			aux2.z = p3.z - p1.z;
			crossProduct(aux1, aux2, p);
			
			float angle = dotProduct(p, direction_struct(p2.x, p2.y, p2.z));

			if (front_face_orientation == cw_orientation) {				
				if(angle < 0)
					primitives.push_back(aux[i]);
			} else {
				if(angle > 0)
					primitives.push_back(aux[i]);
			}			
		}

	} else {
		for(int i = 0; i < aux.size(); i++) {
			primitives.push_back(aux[i]);
		}
	}
	
}


// FIM DA IMPLEMENTAÇÃO DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
