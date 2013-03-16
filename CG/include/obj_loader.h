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
 * A fim de presentar o funcionamento esperado para o programa, este arquivo não deve ser modificado.
 *
 * Copyright (C) 2013 - A.Montenegro, L.A.F.Fernandes, M.Lage.
 */

#ifndef _OBJ_LOADER_HEADER_
#define _OBJ_LOADER_HEADER_


// INCLUDES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* - STL - Standard Template Library
 * API padrão que estabelece padrões e estruturas de dados para aplicações C++.
 * Geralmente disponibilizada com o sistema operacional ou plataforma de desenvolvimento.
 */
#include <cfloat>
#include <stdexcept>

/* - ICGL - IC-UFF Graphics Library
 * Conjunto de operações utilizadas para ensino de Pipeline Gráfico no Instito de Computação (IC) da Universidade Federal Fluminense (UFF).
 * É responsabilidade de cada aluno de Computação Gráfica do IC-UFF implementar a sua própria biblioteca ICGL.
 */
#include <icgl.h>


// DECLARAÇÃO DAS ESTRUTURAS UTILIZADAS PARA ARMAZENAR A GEOMETRIA //////////////////////////////////////////////////////////

/* Classe que representa um material.
 */
class object_material_struct {
public:

    // Nome do material.
    std::string name;

    // Componente ambiente.
    color_struct ambient;

    // Componente difusa.
    color_struct diffuse;

    // Componente especular.
    color_struct specular;

    // Brilho.
    float shininess;

    // Arquivo de textura que contém a componente difusa.
    std::string texture_filename;

public:

    // Construtor padrão da classe.
    object_material_struct();

    // Construtor de cópia.
    object_material_struct(const object_material_struct &other);

    // Construtor de inicialização.
    object_material_struct(const std::string &name);
};

/* Classe que representa um triângulo que pertence a uma malha.
 */
class object_triangle_struct {
public:

    // Número de vértices no triângulo.
    static const size_t vertex_count = 3;

    // Índice do vetor normal associado a cada um dos vértices.
    size_t normal_index[vertex_count];

    // Índice da coordenada de textura associada a cada um dos vértices.
    size_t texcoord_index[vertex_count];

    // Índice da localização associada a cada um dos vértices.
    size_t vertex_index[vertex_count];
    
    // Índice do material associado ao triângulo.
    size_t material_index;

public:

    // Default class constructor.
    object_triangle_struct();
};

/* Classe que representa um objeto definido por uma malha de triângulos.
 */
class geometric_object {
public:

    // Etiqueta que indica que nenhum elemento do tipo respectivo está sendo referenciado.
    static const size_t no_material_tag;
    static const size_t no_normal_tag;
    static const size_t no_texcoord_tag;
    static const size_t no_vertex_tag;

public:

    // Retorna se o objeto foi carregado.
    bool empty() const;

    // Limpa o objeto.
    void clear();
    
    // Carrega objeto do arquivo informado.
    void load_from_file(const std::string &path, const std::string &filename);

public:

    // Retorna o vértice de índice informado.
    const direction_struct& get_normal(const size_t i) const;

    // Retorna o material de índice informado.
    const object_material_struct& get_material(const size_t i) const;

    // Retorna o índice do material de nome informado.
    size_t get_material_index(const std::string &name) const;
    
    // Retorna a coordenada de textura de índice informado.
    const texcoord_struct& get_texcoord(const size_t i) const;

    // Retorna o triângulo de índice informado.
    const object_triangle_struct& get_triangle(const size_t i) const;

    // Retorna o vértice de índice informado.
    const location_struct& get_vertex(const size_t i) const;

    // Retorna o número de materiais usados na malha.
    size_t materials_count() const;

    // Retorna o número de vetores normais na malha.
    size_t normals_count() const;

    // Retorna o número de coordenadas de textura na malha.
    size_t texcoords_count() const;

    // Retorna o número de triângulos na malha.
    size_t triangles_count() const;

    // Retorna o número de vértices na malha.
    size_t vertices_count() const;

private:

    // Caracteres "brancos".
    static const char *whitespaces;

private:

    // Converte o índice informado no padrão OBJ para indexação absoluta. Este método é utilizado por parse_triangle().
    size_t convert_from_obj_index(const size_t count, const int index) const;
    
    // Método auxiliar utilizado por parse_mtl_file() para leitura de canais de cor.
    color_struct parse_color() const;

    // Método auxiliar utilizado na leitura do arquivo MTL.
    void parse_mtl_file(const std::string &path, const std::string &filename);
    
    // Método auxiliar utilizado por parse_obj_file() para leitura de coordendas de vetor normal.
    direction_struct parse_normal() const;

    // Método auxiliar utilizado na leitura do arquivo OBJ.
    void parse_obj_file(const std::string &path, const std::string &filename);
    
    // Método auxiliar utilizado por parse_obj_file() para leitura de coordendas de textura.
    texcoord_struct parse_texcoord() const;

    // Método auxiliar utilizado por parse_obj_file() para leitura de triângulo.
    object_triangle_struct parse_triangle(size_t material_id) const;

    // Método auxiliar utilizado por parse_obj_file() para leitura de coordendas de vértice.
    void parse_values(float *result, size_t count) const;

    // Método auxiliar utilizado por parse_color(), parse_normal(), parse_texcoord() e parse_vertex() para leitura de valures numéricos.
    location_struct parse_vertex() const;

private:
    
    // Lista de vértices.
    std::vector<location_struct> m_vertices;

    // Lista de vetores normais.
    std::vector<direction_struct> m_normals;

    // Lista de coordenadas de textura.
    std::vector<texcoord_struct> m_texcoords;

    // Lista de materiais.
    std::vector<object_material_struct> m_materials;

    // Lista de triângulos.
    std::vector<object_triangle_struct> m_triangles;
};

#endif
