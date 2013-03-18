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
	float S_x, S_y, S_z;
	float V_x, V_y, V_z;
	float H_x, H_y, H_z;

	if(lighting_enabled) {
		//Diffuse
		S_x = light_ec.x - vertex_ec.x;
		S_y = light_ec.y - vertex_ec.y;
		S_z = light_ec.z - vertex_ec.z;
		normalize( &S_x, &S_y, &S_z);
		float dotProductDiffuse = dotProduct (S_x, S_y, S_z, unit_normal_ec.x, unit_normal_ec.y, unit_normal_ec.z);

		color_struct lightDiffuse = color_struct();
		lightDiffuse.r = light_diffuse.r * material_diffuse.r * maxV(dotProductDiffuse, 0.0f);
		lightDiffuse.g = light_diffuse.g * material_diffuse.g * maxV(dotProductDiffuse, 0.0f);
		lightDiffuse.b = light_diffuse.b * material_diffuse.b * maxV(dotProductDiffuse, 0.0f);
		lightDiffuse.a = light_diffuse.a * material_diffuse.a * maxV(dotProductDiffuse, 0.0f);

		//Specular
		V_x = - vertex_ec.x;
		V_y = - vertex_ec.y;
		V_z = - vertex_ec.z;
		normalize(&V_x, &V_y, &V_z);

		H_x = S_x + V_x;
		H_y =  S_y + V_y;
		H_z = S_z + V_z;
		normalize(&H_x, &H_y, &H_z);
		float dotProductSpecular = dotProduct(H_x, H_y, H_z, unit_normal_ec.x, unit_normal_ec.y, unit_normal_ec.z);

		color_struct lightSpecular = color_struct();
		lightSpecular.r = light_specular.r * material_specular.r * pow(maxV(dotProductSpecular, 0.0f), material_shininess);
		lightSpecular.g = light_specular.g * material_specular.g * pow(maxV(dotProductSpecular, 0.0f), material_shininess);
		lightSpecular.b = light_specular.b * material_specular.b * pow(maxV(dotProductSpecular, 0.0f), material_shininess);
		lightSpecular.a = light_specular.a * material_specular.a * pow(maxV(dotProductSpecular, 0.0f), material_shininess);

		//Ambient
		color_struct lightAmbient = color_struct();
		lightAmbient.r = light_ambient.r * material_ambient.r;
		lightAmbient.g = light_ambient.g * material_ambient.g;
		lightAmbient.b = light_ambient.b * material_ambient.b;
		lightAmbient.a = light_ambient.a * material_ambient.a;

		//Result
		vertex_color = color_struct(lightDiffuse.r + lightSpecular.r + lightAmbient.r, 
			lightDiffuse.g + lightSpecular.g + lightAmbient.g, 
			lightDiffuse.b + lightSpecular.b + lightAmbient.b, 
			1.0f);
	} else {
		vertex_color = color_struct(base_color);
	}
}

float maxV(float a, float b) {
	return a > b ? a : b;
}
// FIM DA IMPLEMENTA��O DOS PROCEDIMENTOS ASSOCIADOS COM A TAREFA RELACIONADA A ESTE ARQUIVO ////////////////////////////////

#endif
