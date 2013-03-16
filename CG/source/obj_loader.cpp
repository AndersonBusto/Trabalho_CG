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


// INCLUDES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <obj_loader.h>


// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE MATERIAL_STRUCT //////////////////////////////////////////////////////////////////////

object_material_struct::object_material_struct() :
    name("default"), ambient(0.2f, 0.2f, 0.2f, 1.0f), diffuse(0.8f, 0.8f, 0.8f, 1.0f), specular(1.0f, 1.0f, 1.0f, 1.0f), shininess(0.0f) {
}

object_material_struct::object_material_struct(const object_material_struct &other) :
    name(other.name), ambient(other.ambient), diffuse(other.diffuse), specular(other.specular), shininess(other.shininess), texture_filename(other.texture_filename) {
}

object_material_struct::object_material_struct(const std::string &name_) :
    name(name_), ambient(0.2f, 0.2f, 0.2f, 1.0f), diffuse(0.8f, 0.8f, 0.8f, 1.0f), specular(1.0f, 1.0f, 1.0f, 1.0f), shininess(0.0f) {
}


// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE OBJECT_TRIANGLE_STRUCT ///////////////////////////////////////////////////////////////

object_triangle_struct::object_triangle_struct() :
    material_index(geometric_object::no_material_tag) {

    for (size_t i=0; i!=vertex_count; ++i) {
        normal_index[i] = geometric_object::no_normal_tag;
        texcoord_index[i] = geometric_object::no_texcoord_tag;
        vertex_index[i] = geometric_object::no_vertex_tag;
    }
}


// INICIALIZAÇÃO DOS ATRIBUTOS ESTÁTICOS DA CLASSE GEOMETRIC_OBJECT /////////////////////////////////////////////////////////

const size_t geometric_object::no_material_tag = std::numeric_limits<size_t>::max();
const size_t geometric_object::no_normal_tag = std::numeric_limits<size_t>::max();
const size_t geometric_object::no_texcoord_tag = std::numeric_limits<size_t>::max();
const size_t geometric_object::no_vertex_tag = std::numeric_limits<size_t>::max();

const char* geometric_object::whitespaces = " \t\n\r";

// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE GEOMETRIC_OBJECT /////////////////////////////////////////////////////////////////////

bool geometric_object::empty() const {
    return m_triangles.empty();
}

void geometric_object::clear() {
    m_vertices.clear();
    m_normals.clear();
    m_texcoords.clear();
    m_materials.clear();
    m_triangles.clear();
}

size_t geometric_object::convert_from_obj_index(const size_t count, const int index) const {
    if (index > 0) {
        return (size_t)index + 1;
    }

    if (index < 0) {
        return count + index;
    }

    return std::numeric_limits<size_t>::max();
}

const direction_struct& geometric_object::get_normal(const size_t i) const {
    return m_normals[i];
}

const object_material_struct& geometric_object::get_material(const size_t i) const {
    return m_materials[i];
}

size_t geometric_object::get_material_index(const std::string &name) const {
    for (size_t imaterial=0; imaterial!=m_materials.size(); ++imaterial) {
        if (m_materials[imaterial].name.compare(name) == 0) {
            return imaterial;
        }
    }
    return no_material_tag;
}
        
const texcoord_struct& geometric_object::get_texcoord(const size_t i) const {
    return m_texcoords[i];
}

const object_triangle_struct& geometric_object::get_triangle(const size_t i) const {
    return m_triangles[i];
}

const location_struct& geometric_object::get_vertex(const size_t i) const {
    return m_vertices[i];
}

size_t geometric_object::materials_count() const {
    return m_materials.size();
}

size_t geometric_object::normals_count() const {
    return m_normals.size();
}

size_t geometric_object::texcoords_count() const {
    return m_texcoords.size();
}

size_t geometric_object::triangles_count() const {
    return m_triangles.size();
}

size_t geometric_object::vertices_count() const {
    return m_vertices.size();
}
    
void geometric_object::load_from_file(const std::string &path, const std::string &filename) {
    // Carregar estrutura codificada no arquivo OBJ.
    parse_obj_file(path, filename);
	
    // Normalizar coordenadas de vértices do modelo para intervalo [-0.5, +0.5].
    float lower[3] = {FLT_MAX, FLT_MAX, FLT_MAX}, upper[3] = {FLT_MIN, FLT_MIN, FLT_MIN};

    for (size_t ivertex=0; ivertex!=m_vertices.size(); ++ivertex) {
        const location_struct &vertex = m_vertices[ivertex];

        for (int i=0; i!=3; ++i) {
            if (lower[i] > vertex[i]) {
                lower[i] = vertex[i];
            }

            if (upper[i] < vertex[i]) {
                upper[i] = vertex[i];
            }
        }
    }

    const float translation[3] = {-0.5f * (lower[0] + upper[0]), -0.5f * (lower[1] + upper[1]), -0.5f * (lower[2] + upper[2])};
    const float scale = 1.0f / std::max(std::max(upper[0] - lower[0], upper[1] - lower[1]), upper[2] - lower[2]);

    for (size_t ivertex=0; ivertex!=m_vertices.size(); ++ivertex) {
        location_struct &vertex = m_vertices[ivertex];

        for (int i=0; i!=3; ++i) {
            vertex[i] += translation[i];
            vertex[i] *= scale;
        }
    }
}

color_struct geometric_object::parse_color() const {
    color_struct result;
    parse_values(result.data(), 3);
    return result;
}

void geometric_object::parse_mtl_file(const std::string &path, const std::string &filename) {
    const size_t line_size = 1024;

    FILE* file_stream;
    int line_number = 0;
    bool material_open = false;
    char *current_token = NULL;
    char current_line[line_size];
    size_t current_material_index = no_material_tag; 

    char mtl_filename[1024] = {'\0'};
    strcat(strcat(strcat(mtl_filename, path.c_str()), "/"), filename.c_str());

    // Abrir o material.
    file_stream = fopen(mtl_filename, "r");
    if(file_stream == NULL) {
        char msg[1024] = {'\0'};
        sprintf(msg, "Error reading file: %s.", mtl_filename);
        throw std::runtime_error(msg);
    }
	
    try {
        while (fgets(current_line, line_size, file_stream)) {
            current_token = strtok(current_line, whitespaces);
            line_number++;
		
            // Pular comentários.
            if ((current_token == NULL) || (strcmp(current_token, "//") == 0) || (strcmp(current_token, "#") == 0)) {
                continue;
            }

            // Criar novo material.
            if (strcmp(current_token, "newmtl") == 0) {
                material_open = true;
                m_materials.push_back(object_material_struct(strtok(NULL, whitespaces)));
                current_material_index = m_materials.size() - 1;
                continue;
            }

            if (material_open) {
                // Componente ambiente.
                if (strcmp(current_token, "Ka") == 0) {
                    m_materials[current_material_index].ambient = parse_color();
                    continue;
                }

                // Componente difuso.
                if (strcmp(current_token, "Kd") == 0) {
                    m_materials[current_material_index].diffuse = parse_color();
                    continue;
                }
		
                // Componente especular.
                if (strcmp(current_token, "Ks") == 0) {
                    m_materials[current_material_index].specular = parse_color();
                    continue;
                }

                // Brilho.
                if (strcmp(current_token, "Ns") == 0) {
                    m_materials[current_material_index].shininess = (float)atof(strtok(NULL, whitespaces));
                    continue;
                }

                // Mapa de textura para componente difusa.
                if (strcmp(current_token, "map_Kd") == 0) {
                    char tex_filename[1024] = {};
                    strcat(strcat(strcat(tex_filename, path.c_str()), "/"), strtok(NULL, whitespaces));
                    m_materials[current_material_index].texture_filename = tex_filename;
                    continue;
                }

                // Ignorar comandos que não recebem suporte nesta classe.
                if (strcmp(current_token, "d") == 0) {
                    continue;
                }
                if (strcmp(current_token, "r") == 0) {
                    continue;
                }
                if (strcmp(current_token, "sharpness") == 0) {
                    continue;
                }
                if (strcmp(current_token, "Ni") == 0) {
                    continue;
                }
                if (strcmp(current_token, "illum") == 0) {
                    continue;
                }
            }
            
            // Comando desconhecido.
            char msg[1024] = {'\0'};
            sprintf(msg, "Unknown command '%s' in MTL code at line %i: \"%s\".", current_token, line_number, current_line);
            throw std::runtime_error(msg);
        }

        fclose(file_stream);
    }
    catch (std::exception &error) {
        fclose(file_stream);
        throw error;
    }
}

direction_struct geometric_object::parse_normal() const {
    direction_struct result;
    parse_values(result.data(), 3);
    
    float inv_norm = 1.0f / sqrt(result.x*result.x + result.y*result.y + result.z*result.z);
    result.x *= inv_norm;
    result.y *= inv_norm;
    result.z *= inv_norm;

    return result;
}

void geometric_object::parse_obj_file(const std::string &path, const std::string &filename) {
    const size_t line_size = 1024;

    FILE* file_stream;
    int line_number = 0;
    char *current_token = NULL;
    char current_line[line_size];
    size_t current_material_index = no_material_tag; 

    char obj_filename[1024] = {'\0'};
    strcat(strcat(strcat(obj_filename, path.c_str()), "/"), filename.c_str());

    // Abrir a cena.
    file_stream = fopen(obj_filename, "r");
    if(file_stream == NULL) {
        char msg[1024] = {'\0'};
        sprintf(msg, "Error reading file: %s.", obj_filename);
        throw std::runtime_error(msg);
    }

    try {
        // Loop principal.
        while (fgets(current_line, line_size, file_stream)) {
            current_token = strtok(current_line, whitespaces);
            line_number++;
		
            // Pular comentários.
            if ((current_token == NULL) || (strcmp(current_token, "#") == 0)) {
                continue;
            }

            // Carregar objeto.
            else {
                // Processar localização do vértice.
                if (strcmp(current_token, "v") == 0) {
                    m_vertices.push_back(parse_vertex());
                    continue;
                }
            
                // Processar coordenadas do vetor normal.
                if (strcmp(current_token, "vn") == 0) {
                    m_normals.push_back(parse_normal());
                    continue;
                }
            
                // Processar coordenadas de textura.
                if (strcmp(current_token, "vt") == 0) {
                    m_texcoords.push_back(parse_texcoord());
                    continue;
                }
            
                // Processar face.
                if (strcmp(current_token, "f") == 0) {
                    m_triangles.push_back(parse_triangle(current_material_index));
                    continue;
                }

                // Processar usemtl.
                if (strcmp(current_token, "usemtl") == 0) {
                    current_material_index = get_material_index(strtok(NULL, whitespaces));
                    continue;
                }
            
                // Processar mtllib.
                if (strcmp(current_token, "mtllib") == 0) {
                    parse_mtl_file(path.c_str(), strtok(NULL, whitespaces));
                    continue;
                }

                // Ignorar comandos que não recebem suporte nesta classe.
                if (strcmp(current_token, "sp") == 0) {
                    continue;
                }
                if (strcmp(current_token, "pl") == 0) {
                    continue;
                }
                if (strcmp(current_token, "p") == 0) {
                    continue;
                }
                if (strcmp(current_token, "lp") == 0) {
                    continue;
                }
                if (strcmp(current_token, "ld") == 0) {
                    continue;
                }
                if (strcmp(current_token, "lq") == 0) {
                    continue;
                }
                if (strcmp(current_token, "c") == 0) {
                    continue;
                }
                if (strcmp(current_token, "o") == 0) {
                    continue;
                }
                if (strcmp(current_token, "s") == 0) {
                    continue;
                }
                if (strcmp(current_token, "g") == 0) {
                    continue;
                }

                // Comando desconhecido.
                char msg[1024] = {'\0'};
                sprintf(msg, "Unknown command '%s' in OBJ code at line %i: \"%s\".", current_token, line_number, current_line);
                throw std::runtime_error(msg);
            }
        }

        fclose(file_stream);
    }
    catch (std::exception &error) {
        fclose(file_stream);
        throw error;
    }

    // Verificar se foram carregados vértices.
    if (m_vertices.empty()) {
        throw std::runtime_error("The geometric object in given OBJ file has no vertices.");
    }
}

texcoord_struct geometric_object::parse_texcoord() const {
    texcoord_struct result;
    parse_values(result.data(), 2);
    return result;
}

object_triangle_struct geometric_object::parse_triangle(size_t material_index) const {
	size_t ivertex = 0;
	char *temp_str, *token;
    object_triangle_struct result;

    result.material_index = material_index;

    while (((token = strtok(NULL, whitespaces)) != NULL) && (ivertex < result.vertex_count)) {
        result.vertex_index[ivertex] = convert_from_obj_index(m_vertices.size(), atoi(token));
		
        if (strstr(token, "//") != NULL) {
            temp_str = strchr(token, '/');
            temp_str++;
            result.normal_index[ivertex] = convert_from_obj_index(m_normals.size(), atoi(++temp_str));
        }
        else if (strstr(token, "/") != NULL) {
            temp_str = strchr(token, '/');
            result.texcoord_index[ivertex] = convert_from_obj_index(m_texcoords.size(), atoi(++temp_str));

            if (strstr(temp_str, "/") != NULL) {
                temp_str = strchr(temp_str, '/');
                result.normal_index[ivertex] = convert_from_obj_index(m_normals.size(), atoi(++temp_str));
            }
        }
		
        ivertex++;
    }

    if ((token != NULL) || (ivertex != result.vertex_count)) {
        throw std::runtime_error("There are faces in the OBJ file that are not triangles.");
    }

    return result;
}

void geometric_object::parse_values(float *result, size_t count) const {
    while ((count--) > 0) {
        *(result++) = (float)atof(strtok(NULL, whitespaces));
    }
}

location_struct geometric_object::parse_vertex() const {
    location_struct result;
    parse_values(result.data(), 3);
    return result;
}
