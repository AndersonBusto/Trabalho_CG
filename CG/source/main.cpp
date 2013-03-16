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

/* - Windows -
 * Cabeçalho principal requerido em aplicações gráficas Windows. Em ambiente Windows, DEVE ser incluído antes de <GL/gl.h>.
 */
#if defined( _MSC_VER ) || defined( __MINGW32__ )
    #define WIN32_LEAN_AND_MEAN
    #define NO_MIN_MAX
    #include <windows.h>
#endif

/* - OpenGL - Open Graphics Library
 * API livre utilizada no desenvolvimento de aplicativos gráficos, ambientes 3D, jogos, entre outros.
 * Geralmente disponibilizada com o sistema operacional ou plataforma de desenvolvimento.
 */
#if defined( __APPLE__ )
    #include <OpenGl/gl.h>
#elif defined( _MSC_VER ) || defined( __MINGW32__ ) || defined(__GNUC__)
    #include <Gl/gl.h>
#endif

/* - GLU - OpenGL Utility Library
 * Biblioteca que adiciona funcionalidades de mais alto nível ao OpenGL.
 * Geralmente disponibilizada com o sistema operacional ou plataforma de desenvolvimento.
 */
#if defined( __APPLE__ )
    #include <OpenGl/glu.h>
#elif defined( _MSC_VER ) || defined( __MINGW32__ ) || defined(__GNUC__)
    #include <Gl/glu.h>
#endif

/* - FreeGLUT - Free OpenGL Utility Toolkit
 * Fornece rotinas para criar janelas contendo contextos OpenGL.
 * Disponível em http://sourceforge.net/projects/freeglut/
 */
#if defined( __APPLE__ )
    #include <GLUT/glut.h>
#elif defined( _MSC_VER ) || defined( __MINGW32__ ) || defined(__GNUC__)
    #include <GL/glut.h>
#endif

/* - GLUI - GLUT-Based C++ User Interface Library
 * Fornece rotinas para criar interfaces gráficas muito simples baseadas em OpenGL.
 * Disponível em http://glui.sourceforge.net/
 */
#pragma warning( push )
#pragma warning( disable : 4244 )
#if defined( __APPLE__ )
    #include <GLUI/glui.h>
#elif defined( _MSC_VER ) || defined( __MINGW32__ ) || defined(__GNUC__)
    #include <Gl/glui.h>
#endif
#pragma warning( pop )

/* - DevIL - Developer's Image Library
 * Fornece rotinas para manipulação de diversos tipos de arquivos de imagem.
 * Disponível em http://openil.sourceforge.net/
 */
#if defined( __APPLE__ )
    #include <il.h>
#elif defined( _MSC_VER ) || defined( __MINGW32__ ) || defined(__GNUC__)
    #include <IL/il.h>
#endif

/* - ICGL - IC-UFF Graphics Library
 * Conjunto de operações utilizadas para ensino de Pipeline Gráfico no Instito de Computação (IC) da Universidade Federal Fluminense (UFF).
 * É responsabilidade de cada aluno de Computação Gráfica do IC-UFF implementar a sua própria biblioteca ICGL.
 */
#include <icgl.h>

/* - OBJ_LOADER - OBJ Loader
 * Fornece classes para carregar arquivos no formato Wavefront's Object (OBJ) com material no formato Material Template Library (MTL).
 */
#include <obj_loader.h>

/* - STL - Standard Template Library
 * API padrão que estabelece padrões e estruturas de dados para aplicações C++.
 * Geralmente disponibilizada com o sistema operacional ou plataforma de desenvolvimento.
 */
#include <cmath>
#include <cstdlib>


// VARIÁVEIS GLOBAIS UTILIZADAS PELOS PROCEDIMENTOS ESCRITOS ABAIXO /////////////////////////////////////////////////////////

/* Identificadores da janela principal da aplicação e das subjanelas.
 */
int main_window_id = 0;

int control_subwindow_id = 0;
int gl_subwindow_id = 0;
int icgl_subwindow_id = 0;

/* Variáveis "vivas" utilizadas pelos controles da GLUI.
 */

// Índice do modelo geométrico selecionado.
int current_model_index = -1; // Nenhum

// Parâmetros de projeção da câmera.
float camera_fovy = 45.0f;
float camera_aspect = 1.0f;
float camera_znear = 0.01f;
float camera_zfar = 20.0f;

// Posição e orientação inicial da câmera.
const float camera_eye[3] = {0.0f, 0.0f, -4.0f};
const float camera_center[3] = {0.0f, 0.0f, 0.0f};
const float camera_up[3] = {0.0f, 1.0f, 0.0f};

// Rotação e translação aplicadas à câmera.
matrix_struct camera_rotation_matrix;                          // Sem rotação.
float camera_translation_displacement[3] = {0.0f, 0.0f, 0.0f}; // Sem translação.

// Propriedades da fonte de luz.
class light_struct {
public:

    // Localização da luz.
    location_struct position;

    // Intensidade das componentes ambiente, difusa e especular.
    color_struct ambient;
    color_struct diffuse;
    color_struct specular;

public:

    // Contrutor padrão.
    light_struct() :
        position(0.6f, 0.6f, -2.0f, 1.0f), ambient(0.2f, 0.2f, 0.2f, 1.0f), diffuse(1.0f, 1.0f, 1.0f, 1.0f), specular(1.0f, 1.0f, 1.0f, 1.0f) {
    }

} light;

// Geometria da fonte de luz.
const direction_struct light_normal(0.0f, 0.0f, 1.0f);
const texcoord_struct  light_texcoord(0.0f, 0.0f);
const location_struct  light_vertices[8] = {location_struct(-0.7071f,  0.3536f,  0.3536f, 1.0f), location_struct(-0.0000f, -0.1464f,  0.8536f, 1.0f), location_struct( 0.7071f,  0.3536f,  0.3536f, 1.0f), location_struct( 0.0000f,  0.8536f, -0.1464f, 1.0f), location_struct(-0.7071f, -0.3536f, -0.3536f, 1.0f), location_struct(-0.0000f, -0.8536f,  0.1464f, 1.0f), location_struct( 0.7071f, -0.3536f, -0.3536f, 1.0f), location_struct( 0.0000f,  0.1464f, -0.8536f, 1.0f)};
const size_t           light_indices[36] = {0, 1, 2, 0, 2, 3, 0, 4, 5, 0, 5, 1, 2, 6, 7, 2, 7, 3, 3, 7, 4, 3, 4, 0, 1, 5, 6, 1, 6, 2, 5, 4, 7, 5, 7, 6};
const size_t           light_triangles_count = 12;

// Cor padrão para vértices que não recebem material.
color_struct model_base_color(1.0f, 1.0f, 1.0f, 1.0f); // Branco

// Rotação, escala e translação aplicadas ao modelo.
matrix_struct model_rotation_matrix;                          // Sem rotação.
float model_scaling_factor[3]           = {1.5f, 1.5f, 1.5f}; // Escala uniforme de 1.5x.
float model_translation_displacement[3] = {0.0f, 0.0f, 0.0f}; // Sem translação.

// Orientação assumida para que a face projetada não esteja "de costas" para o observador.
int front_face_orientation = 1; // CW = 0, CCW = 1

// Ferramentas de depuração.
int display_light_source = false;
int display_normal_vectors = false;

// Outras propriedades que configuram o rendering.
int backface_culling_enabled = true;
int depth_test_enabled = true;
int lighting_enabled = true;
int texture_mapping_enabled = true;
int wireframe_enabled = false;

// Cor padrão para o framebuffer.
color_struct clear_color(0.75f, 0.88f, 1.0f, 1.0f);

/* Lista de modelos geométricos disponíveis na pasta "media".
 */
const int model_count = 1;
const char* model_filenames[] = {"cube"};

/* Modelo geométrico atual.
 */
geometric_object current_model;

std::vector<GLuint> gl_current_model_textures;

#if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)

    // Propriedades da textura. É assumido espaço de cores RGBA.
    class texture_struct {
    public:

        // Flag que indica se a textura é válida.
        bool is_valid;
        
        // Tamanho da textura.
        int width;
        int height;

        // Texels.
        std::vector<float> texels;

    public:

        // Contrutor padrão da classe.
        texture_struct() :
            is_valid(false), width(0), height(0) {
        }
    };

    std::vector<texture_struct> icgl_current_model_textures;

#else
    std::vector<GLuint> icgl_current_model_textures;
#endif


/* Variáveis auxiliares repassadas para a ICGL (elas evitam repetidas alocações de memória).
 */
#if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
    std::vector<location_struct> primitive_vertices_cc; // Lista de localização de vértices.
    std::vector<color_struct> primitive_colors;         // Lista de colores de vértices.
    std::vector<texcoord_struct> primitive_texcoords;   // Lista de coordenadas de textura associadas a vértices.
    std::vector<int> primitive_texture_ids;             // Lista de identificadores da textura associada a cada vértice. Vértices da mesma primitiva recebem o mesmo identificador.

    std::vector<segment_struct> segments;               // Lista de primitivas do tipo segmento de reta.
    std::vector<triangle_struct> triangles;             // Lista de primitivas do tipo triângulo.
#endif

#if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
    std::vector<float> framebuffer; // Sistema de cores RGBA é assumido.
    std::vector<float> depthbuffer; // Um único canal de profundidade é assumido.

    std::vector<texture_struct*> primitives_textures; // Ponteiro para a textura associada a cada primitiva.
#endif

const color_struct black(0.0f, 0.0f, 0.0f, 1.0f);

// ROTINAS AUXILIARES ///////////////////////////////////////////////////////////////////////////////////////////////////////

/* Desenha o texto informado.
 */
void draw_text(const std::string &text) {
    for (size_t i=0; i!=text.size(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (unsigned char)text[i]);
    }
}

/* Invoca a ICGL para construção de uma matriz "look at" e repassa a matriz construída para o OpenGL.
 */
void icgl_lookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz) {
#if defined(ICGL_ASSIGNMENT_02_LOOK_AT)
    matrix_struct matrix;
    make_lookat_matrix(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz, matrix);
    glMultMatrixf(matrix.data());
#else
    gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
#endif
}

/* Invoca a ICGL para construção de uma matriz de projeção perspectiva e repassa a matriz construída para o OpenGL.
 */
void icgl_perspective(float fovy, float aspect, float znear, float zfar) {
#if defined(ICGL_ASSIGNMENT_03_PERSPECTIVE_PROJECTION)
    matrix_struct matrix;
    make_perspective_matrix(fovy, aspect, znear, zfar, matrix);
    glMultMatrixf(matrix.data());
#else
    gluPerspective(fovy, aspect, znear, zfar);
#endif
}

/* Invoca a ICGL para construção de uma matriz de rotação e repassa a matriz construída para o OpenGL.
 */
void icgl_rotate(float angle_in_degrees, float axisx, float axisy, float axisz) {
#if defined(ICGL_ASSIGNMENT_01_ROTATION_SCALE_TRANSLATION)
    matrix_struct matrix;
    make_rotation_matrix(angle_in_degrees, axisx, axisy, axisz, matrix);
    glMultMatrixf(matrix.data());
#else
    glRotatef(angle_in_degrees, axisx, axisy, axisz);
#endif
}

/* Invoca a ICGL para construção de uma matriz de escala e repassa a matriz construída para o OpenGL.
 */
void icgl_scale(float scalex, float scaley, float scalez) {
#if defined(ICGL_ASSIGNMENT_01_ROTATION_SCALE_TRANSLATION)
    matrix_struct matrix;
    make_scale_matrix(scalex, scaley, scalez, matrix);
    glMultMatrixf(matrix.data());
#else
    glScalef(scalex, scaley, scalez);
#endif
}

/* Invoca a ICGL para construção de uma matriz de translação e repassa a matriz construída para o OpenGL.
 */
void icgl_translate(float deltax, float deltay, float deltaz) {
#if defined(ICGL_ASSIGNMENT_01_ROTATION_SCALE_TRANSLATION)
    matrix_struct matrix;
    make_translation_matrix(deltax, deltay, deltaz, matrix);
    glMultMatrixf(matrix.data());
#else
    glTranslatef(deltax, deltay, deltaz);
#endif
}

/* Extrai de uma matriz de rotação o ângulo (em graus) e o eixo de rotação.
 */
void rotation_matrix_to_parameters(const matrix_struct &matrix, float &angle, float *axis) {
    const float &Qxx = matrix[0]; const float &Qyx = matrix[4]; const float &Qzx = matrix[8];
    const float &Qxy = matrix[1]; const float &Qyy = matrix[5]; const float &Qzy = matrix[9];
    const float &Qxz = matrix[2]; const float &Qyz = matrix[6]; const float &Qzz = matrix[10];
    
    float &x = axis[0];
    float &y = axis[1];
    float &z = axis[2];

    x = Qzy - Qyz;
    y = Qxz - Qzx;
    z = Qyx - Qxy;

    const float r = sqrt(x*x + y*y + z*z);
    
    if (r != 0.0f) {
        const float t = Qxx + Qyy + Qzz;

        angle = (180.0f / pi) * atan2f(r, t - 1.0f);
    }
    else
    {
        z = 1.0f;
        angle = 0.0f;
    }
}


// ROTINAS RELACIONADAS COM A JANELA PRINCIPAL DA APLICAÇÃO /////////////////////////////////////////////////////////////////

/* Procedimento chamado toda vez que o conteúdo da janela principal da aplicação precisar ser redesenhado.
 */
void main_window_display_callback() {

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    const int border = 5;
    const int fontsize = 18;
    const int &x = viewport[0], &y = viewport[1], &width = viewport[2], &height = viewport[3];

    // Definir valores padrões para os buffers RGBA e DEPTH e limpar ambos.
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definir matrizes.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width - 1.0, 0, height - 1.0, -1.0, 1.0);

    // Desenhar legenda das imagens.
    glColor3f(0.0f, 0.0f, 0.0f);

    glRasterPos2i(x + border, height - (y + border + fontsize));
    draw_text("Rendered by OpenGL");

    glRasterPos2i(x + (width + border)/2, height - (y + border + fontsize));
#if defined(ICGL_ASSIGNMENT_00_WARMING_UP)
    
    std::string student;
    give_me_your_name(student);

    #if   defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
        const int assignment_number = 7;
    #elif defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
        const int assignment_number = 6;
    #elif defined(ICGL_ASSIGNMENT_05_VERTEX_LIGHTING)
        const int assignment_number = 5;
    #elif defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
        const int assignment_number = 4;
    #elif defined(ICGL_ASSIGNMENT_03_PERSPECTIVE_PROJECTION)
        const int assignment_number = 3;
    #elif defined(ICGL_ASSIGNMENT_02_LOOK_AT)
        const int assignment_number = 2;
    #elif defined(ICGL_ASSIGNMENT_01_ROTATION_SCALE_TRANSLATION)
        const int assignment_number = 1;
    #else
        const int assignment_number = 0;
    #endif

    char text[2014] = {};
    sprintf(text, "Rendered by %s (Assignment %02d)", student.c_str(), assignment_number);
    draw_text(text);
#else
    draw_text("Rendered by OpenGL");
#endif


    // Tornar visível o buffer atualizado.
    glutSwapBuffers();
}

/* Procedimento chamado toda vez que uma tecla simples é pressionada no teclado.
 */
void main_window_keyboard_callback(unsigned char key, int x, int y) {
    // Não fazer nada.
}

/* Procedimento chamado toda vez que uma tecla especial é pressionada no teclado.
 */
void main_window_keyboard_special_callback(int key, int x, int y) {
    // Não fazer nada.
}

/* Procedimento chamado toda vez que um botão é pressionada no mouse.
 */
void main_window_mouse_callback(int button, int state, int x, int y) {
    // Não fazer nada.
}

/* Procedimento chamado toda vez que a janela principal da aplicação for redimensionada.
 */
void main_window_reshape_callback(int width, int height) {

    const int border = 5;
    const int fontsize = 18;
    int x, y, w, h;
    GLUI_Master.get_viewport_area(&x, &y, &w, &h);

    // Ao redimensionar a janela, fazer com que a viewport também seja redimensionada.
    glViewport(x, y, w, h);

    // Redimensionar subjanela onde é exibido o rendering do OpenGL.
    glutSetWindow(gl_subwindow_id);
    glutPositionWindow(x + border, y + 2*border + fontsize);
    glutReshapeWindow((w - 3*border)/2, h - 3*border - fontsize);

    // Redimensionar subjanela onde é exibido o rendering do ICGL.
    glutSetWindow(icgl_subwindow_id);
    glutPositionWindow(x + (w + border)/2, y + 2*border + fontsize);
    glutReshapeWindow((w - 3*border)/2, h - 3*border - fontsize);
}


// ROTINAS RELACIONADAS COM A SUBJANELA QUE RECEBE O RENDERING DO OPENGL ////////////////////////////////////////////////////

/* Procedimento chamado toda vez que o conteúdo da subjanela OpenGL precisar ser redesenhado.
 */
void gl_subwindow_display_callback() {
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    // Definir que vetores normais serão normalizados antes do uso.
    glEnable(GL_NORMALIZE);

    // Habilitar ou desabilitar depth test.
    if (depth_test_enabled) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }

    // Definir valores padrão para os buffers RGBA e DEPTH e limpar ambos.
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definir projeção.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(camera_fovy, (camera_aspect * glutGet(GLUT_WINDOW_WIDTH)) / glutGet(GLUT_WINDOW_HEIGHT), camera_znear, camera_zfar);

    // Definir posição da fonte de luz, câmera e modelo.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Exibir fonte de luz.
    if (display_light_source) {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();
        glTranslatef(light.position.x, light.position.y, light.position.z);
        glScalef(0.01f, 0.01f, 0.01f);

        glBegin(GL_TRIANGLES);
        for (size_t itriangle=0; itriangle!=light_triangles_count; ++itriangle) {
            for (size_t ivertex=0; ivertex!=3; ++ivertex) {
                glTexCoord2fv(light_texcoord.data());
                glColor4fv(light.diffuse.data());
                glNormal3fv(light_normal.data());
                glVertex4fv(light_vertices[light_indices[itriangle*3+ivertex]].data());
            }
        }
        glEnd();

        glPopMatrix();
        glPopAttrib();
    }

    // Posicionar fonte de luz.
    glLightfv(GL_LIGHT0, GL_POSITION, light.position.data());
    glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient.data());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse.data());
    glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular.data());

    // Configurar modelo de iluminação.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black.data());

    // Posicionar câmera.
    GLfloat camera_rotation_angle = 0.0f;
    GLfloat camera_rotation_axis[3] = {0.0f, 0.0f, 1.0f};
    rotation_matrix_to_parameters(camera_rotation_matrix, camera_rotation_angle, camera_rotation_axis);

    glTranslatef(-camera_translation_displacement[0], -camera_translation_displacement[1], camera_translation_displacement[2]);
    glRotatef(camera_rotation_angle, camera_rotation_axis[0], camera_rotation_axis[1], camera_rotation_axis[2]);

    gluLookAt(camera_eye[0], camera_eye[1], camera_eye[2], camera_center[0], camera_center[1], camera_center[2], camera_up[0], camera_up[1], camera_up[2]);

    // Posicionar modelo.
    GLfloat model_rotation_angle = 0.0f;
    GLfloat model_rotation_axis[3] = {0.0f, 0.0f, 1.0f};
    rotation_matrix_to_parameters(model_rotation_matrix, model_rotation_angle, model_rotation_axis);

    glTranslatef(model_translation_displacement[0], model_translation_displacement[1], model_translation_displacement[2]);
    glScalef(model_scaling_factor[0], model_scaling_factor[1], model_scaling_factor[2]);
    glRotatef(model_rotation_angle, model_rotation_axis[0], model_rotation_axis[1], model_rotation_axis[2]);

    // Definir orientação padrão das faces.
    glFrontFace((front_face_orientation == 0) ? GL_CW : GL_CCW);

    // Habilitar ou desabilitar back-face culling.
    if (backface_culling_enabled) {
        glEnable(GL_CULL_FACE);
    }
    else {
        glDisable(GL_CULL_FACE);
    }

    // Definir modo de rasterização de polígonos.
    glPolygonMode(GL_FRONT_AND_BACK, (wireframe_enabled) ? GL_LINE : GL_FILL);

    // Renderizar modelo.
    if ((0 <= current_model_index) && (current_model_index < model_count)) {
        
        for (size_t itriangle=0; itriangle!=current_model.triangles_count(); ++itriangle) {
            const object_triangle_struct &triangle = current_model.get_triangle(itriangle);

            glPushAttrib(GL_ALL_ATTRIB_BITS);
            
            // Definir propriedades do material.
            if (triangle.material_index != geometric_object::no_material_tag) {
                const object_material_struct &material = current_model.get_material(triangle.material_index);

                if (lighting_enabled) {
                    glEnable(GL_LIGHT0);
                    glEnable(GL_LIGHTING);

                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient.data());
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse.data());
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular.data());
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
                }

                const GLuint texture_name = gl_current_model_textures[triangle.material_index];

                if ((texture_mapping_enabled) && (texture_name != 0)) {
                    glBindTexture(GL_TEXTURE_2D, texture_name);
                    glEnable(GL_TEXTURE_2D);
                }
            }

            // Renderizar triângulos com o material corrente.
            glBegin(GL_TRIANGLES);
            
            for (size_t ivertex=0; ivertex!=triangle.vertex_count; ++ivertex) {
                const texcoord_struct &texcoord = current_model.get_texcoord(triangle.texcoord_index[ivertex]);
                const direction_struct &normal_oc = current_model.get_normal(triangle.normal_index[ivertex]);
                const location_struct &vertex_oc = current_model.get_vertex(triangle.vertex_index[ivertex]);

                glTexCoord2fv(texcoord.data());
                glColor4fv(model_base_color.data());
                glNormal3fv(normal_oc.data());
                glVertex4fv(vertex_oc.data());
            }

            glEnd();

            glPopAttrib();

            // Exibir vetores normais.
            if (display_normal_vectors) {
                glPushAttrib(GL_ALL_ATTRIB_BITS);
                glBegin(GL_LINES);

                for (size_t ivertex=0; ivertex!=triangle.vertex_count; ++ivertex) {
                    const direction_struct &normal_oc = current_model.get_normal(triangle.normal_index[ivertex]);
                    const location_struct &vertex_oc = current_model.get_vertex(triangle.vertex_index[ivertex]);

                    glColor3f(0.5f*normal_oc.x + 0.5f, 0.5f*normal_oc.y + 0.5f, 0.5f*normal_oc.z + 0.5f);
                    glVertex4f(vertex_oc.x, vertex_oc.y, vertex_oc.z, vertex_oc.w);
                    glVertex4f(vertex_oc.x/vertex_oc.w + 0.05f*normal_oc.x, vertex_oc.y/vertex_oc.w + 0.05f*normal_oc.y, vertex_oc.z/vertex_oc.w + 0.05f*normal_oc.z, 1.0f);
                }

                glEnd();
                glPopAttrib();
            }
        }
    }

    glPopAttrib();

    // Tornar visível o buffer atualizado.
    glutSwapBuffers();
}

/* Procedimento chamado toda vez que a subjanela OpenGL for redimensionada.
 */
void gl_subwindow_reshape_callback(int width, int height) {

    // Ao redimensionar a janela, fazer com que a viewport também seja redimensionada.
    glViewport(0, 0, width, height);
}

/* Procedimento que cria a subjaneja que recebe o rendering OpenGL.
 */
int create_gl_subwindow(const int main_window_id) {

    // Criar a subjanela.
    int resulting_id = glutCreateSubWindow(main_window_id, 0, 0, 1, 1);
    
    // Atribuir rotinas para tratamento de eventos.
    glutDisplayFunc(gl_subwindow_display_callback);
    glutReshapeFunc(gl_subwindow_reshape_callback);

    // Retornar o identificado da subjanela criada.
    return resulting_id;
}


// ROTINAS RELACIONADAS COM A SUBJANELA QUE RECEBE O RENDERING DO ICGL //////////////////////////////////////////////////////

/* Procedimento chamado toda vez que o conteúdo da subjanela ICGL precisar ser redesenhado.
 */
void icgl_subwindow_display_callback() {
    glPushAttrib(GL_ALL_ATTRIB_BITS);

#if !defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
    // Definir que vetores normais serão normalizados antes do uso.
    glEnable(GL_NORMALIZE);
#endif

#if !defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
    // Habilitar ou desabilitar depth test.
    if (depth_test_enabled) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }
#endif

#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
    direction_struct unit_normal_ec;
    location_struct vertex_ec, vertex_cc;
#endif

    // Definir valores padrão para os buffers RGBA e DEPTH e limpar ambos.
#if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);

    for (size_t ipixel=0; ipixel!=depthbuffer.size(); ++ipixel) {
        for (size_t ichannel=0; ichannel!=clear_color.channels_count; ++ichannel) {
            framebuffer[(ipixel*4)+ichannel] = clear_color[ichannel];
        }
        depthbuffer[ipixel] = 1.0f;
    }

    const int buffer_width = glutGet(GLUT_WINDOW_WIDTH);
    const int buffer_height = glutGet(GLUT_WINDOW_HEIGHT);
#else
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    glClearDepth(1.0f);
#endif

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definir projeção.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    icgl_perspective(camera_fovy, (camera_aspect * glutGet(GLUT_WINDOW_WIDTH)) / glutGet(GLUT_WINDOW_HEIGHT), camera_znear, camera_zfar);
    
#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
    matrix_struct projection_matrix;
    glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix.data());
    glLoadIdentity();
#endif

    // Definir posição da fonte de luz, câmera e modelo.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Exibir fonte de luz.
    if (display_light_source) {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushMatrix();
        icgl_translate(light.position.x, light.position.y, light.position.z);
        icgl_scale(0.01f, 0.01f, 0.01f);

#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
        matrix_struct modelview_matrix;
        glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix.data());
        glLoadIdentity();
#endif

#if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
        triangles.clear();
        primitive_vertices_cc.clear();
        primitive_colors.clear();
        primitive_texcoords.clear();
        primitive_texture_ids.clear();
#endif

#if !defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
        glBegin(GL_TRIANGLES);
        glTexCoord2fv(light_texcoord.data());
#endif

        for (size_t itriangle=0; itriangle!=light_triangles_count; ++itriangle) {
            for (size_t ivertex=0; ivertex!=3; ++ivertex) {
                const direction_struct &normal_oc = light_normal;
                const location_struct &vertex_oc = light_vertices[light_indices[itriangle*3+ivertex]];

#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
                vertex_transformation(vertex_oc, normal_oc, modelview_matrix, projection_matrix, vertex_ec, vertex_cc, unit_normal_ec);

    #if defined(ICGL_ASSIGNMENT_05_VERTEX_LIGHTING)
                color_struct color;
                vertex_lighting(vertex_ec, unit_normal_ec, model_base_color, false, black, black, black, 0.0f, location_struct(0.0f, 0.0f, 0.0f, 1.0f), black, black, black, color);

        #if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
                primitive_vertices_cc.push_back(vertex_cc);
                primitive_colors.push_back(color);
                primitive_texcoords.push_back(light_texcoord);
                primitive_texture_ids.push_back(-1);
        #else
                glColor4fv(color.data());
                glNormal3fv(unit_normal_ec.data());
                glVertex4fv(vertex_cc.data());
        #endif
    #else
                glColor4fv(light.diffuse.data());
                glNormal3fv(unit_normal_ec.data());
                glVertex4fv(vertex_cc.data());
    #endif
#else
                glColor4fv(light.diffuse.data());
                glNormal3fv(normal_oc.data());
                glVertex4fv(vertex_oc.data());
#endif
            }
        }

#if !defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
        glEnd();
#endif

#if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
        make_triangles(primitive_vertices_cc, primitive_colors, primitive_texcoords, primitive_texture_ids, true, ccw_orientation, triangles);

        if (!triangles.empty()) {
    #if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
            int viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            for (size_t itriangle=0; itriangle!=triangles.size(); ++itriangle) {
                const triangle_struct &triangle = triangles[itriangle];
                rasterize_triangle(triangles[itriangle], viewport[0], viewport[1], viewport[2], viewport[3], false, 0, 0, NULL, (depth_test_enabled != 0), buffer_width, buffer_height, &framebuffer.front(), &depthbuffer.front());
            }
    #else
            glBegin(GL_TRIANGLES);
            for (size_t itriangle=0; itriangle!=triangles.size(); ++itriangle) {
                const triangle_struct &triangle = triangles[itriangle];

                for (size_t ivertex=0; ivertex!=triangle.vertices_count; ++ivertex) {
                    glTexCoord2fv(triangle.texcoord[ivertex].data());
                    glColor4fv(triangle.color[ivertex].data());
                    glVertex4fv(triangle.vertex_cc[ivertex].data());
                }
            }
            glEnd();
    #endif
        }
#endif

        glPopMatrix();
        glPopAttrib();
    }

#if !defined(ICGL_ASSIGNMENT_05_VERTEX_LIGHTING)
    // Posicionar fonte de luz.
    glLightfv(GL_LIGHT0, GL_POSITION, light.position.data());
    glLightfv(GL_LIGHT0, GL_AMBIENT, light.ambient.data());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light.diffuse.data());
    glLightfv(GL_LIGHT0, GL_SPECULAR, light.specular.data());

    // Configurar modelo de iluminação.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
#endif
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black.data());

    // Posicionar câmera.
    GLfloat camera_rotation_angle = 0.0f;
    GLfloat camera_rotation_axis[3] = {0.0f, 0.0f, 1.0f};
    rotation_matrix_to_parameters(camera_rotation_matrix, camera_rotation_angle, camera_rotation_axis);

    icgl_translate(-camera_translation_displacement[0], -camera_translation_displacement[1], camera_translation_displacement[2]);
    icgl_rotate(camera_rotation_angle, camera_rotation_axis[0], camera_rotation_axis[1], camera_rotation_axis[2]);

    icgl_lookat(camera_eye[0], camera_eye[1], camera_eye[2], camera_center[0], camera_center[1], camera_center[2], camera_up[0], camera_up[1], camera_up[2]);

    // Posicionar modelo.
    GLfloat model_rotation_angle = 0.0f;
    GLfloat model_rotation_axis[3] = {0.0f, 0.0f, 1.0f};
    rotation_matrix_to_parameters(model_rotation_matrix, model_rotation_angle, model_rotation_axis);

    icgl_translate(model_translation_displacement[0], model_translation_displacement[1], model_translation_displacement[2]);
    icgl_scale(model_scaling_factor[0], model_scaling_factor[1], model_scaling_factor[2]);
    icgl_rotate(model_rotation_angle, model_rotation_axis[0], model_rotation_axis[1], model_rotation_axis[2]);

#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
    matrix_struct modelview_matrix;
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix.data());
    glLoadIdentity();
#endif

#if !defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
    // Definir orientação padrão das faces.
    glFrontFace((front_face_orientation == 0) ? GL_CW : GL_CCW);

    // Habilitar ou desabilitar back-face culling.
    if (backface_culling_enabled) {
        glEnable(GL_CULL_FACE);
    }
    else {
        glDisable(GL_CULL_FACE);
    }
#endif

#if !defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
    // Definir modo de rasterização de polígonos.
    glPolygonMode(GL_FRONT_AND_BACK, (wireframe_enabled) ? GL_LINE : GL_FILL);
#endif

    // Renderizar modelo.
    if ((0 <= current_model_index) && (current_model_index < model_count)) {

        // Exibir superfície.
        object_material_struct material;

#if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
        triangles.clear();
        primitive_vertices_cc.clear();
        primitive_colors.clear();
        primitive_texcoords.clear();
        primitive_texture_ids.clear();
#endif

        for (size_t itriangle=0; itriangle!=current_model.triangles_count(); ++itriangle) {
            GLuint texture_name = 0;
            const object_triangle_struct &triangle = current_model.get_triangle(itriangle);

            glPushAttrib(GL_ALL_ATTRIB_BITS);

            // Definir propriedades do material.
            if (triangle.material_index != geometric_object::no_material_tag) {
                material = current_model.get_material(triangle.material_index);

#if !defined(ICGL_ASSIGNMENT_05_VERTEX_LIGHTING)
                if (lighting_enabled) {
                    glEnable(GL_LIGHT0);
                    glEnable(GL_LIGHTING);

                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient.data());
                    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse.data());
                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular.data());
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
                }
#endif

#if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
                texture_name = triangle.material_index;
#else
                texture_name = gl_current_model_textures[triangle.material_index];

    #if !defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
                if ((texture_mapping_enabled) && (texture_name != 0)) {
                    glBindTexture(GL_TEXTURE_2D, texture_name);
                    glEnable(GL_TEXTURE_2D);
                }
    #endif
#endif
            }

            // Renderizar triângulos com o material corrente.
#if !defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
            glBegin(GL_TRIANGLES);
#endif
            
            for (size_t ivertex=0; ivertex!=triangle.vertex_count; ++ivertex) {
                const texcoord_struct &texcoord = current_model.get_texcoord(triangle.texcoord_index[ivertex]);
                const direction_struct &normal_oc = current_model.get_normal(triangle.normal_index[ivertex]);
                const location_struct &vertex_oc = current_model.get_vertex(triangle.vertex_index[ivertex]);

    #if !defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
                glTexCoord2fv(texcoord.data());
    #endif

#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
                vertex_transformation(vertex_oc, normal_oc, modelview_matrix, projection_matrix, vertex_ec, vertex_cc, unit_normal_ec);

    #if defined(ICGL_ASSIGNMENT_05_VERTEX_LIGHTING)

                color_struct color;
                vertex_lighting(vertex_ec, unit_normal_ec, model_base_color, ((lighting_enabled) && (triangle.material_index != geometric_object::no_material_tag)), material.ambient, material.diffuse, material.specular, material.shininess, light.position, light.ambient, light.diffuse, light.specular, color);

        #if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
                primitive_vertices_cc.push_back(vertex_cc);
                primitive_colors.push_back(color);
                primitive_texcoords.push_back(texcoord);
                primitive_texture_ids.push_back((int)texture_name);
        #else
                glColor4fv(color.data());
                glNormal3fv(unit_normal_ec.data());
                glVertex4fv(vertex_cc.data());
        #endif
    #else
                glColor4fv(model_base_color.data());
                glNormal3fv(unit_normal_ec.data());
                glVertex4fv(vertex_cc.data());
    #endif
#else
                glColor4fv(model_base_color.data());
                glNormal3fv(normal_oc.data());
                glVertex4fv(vertex_oc.data());
#endif
            }

#if !defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
            glEnd();
#endif
            glPopAttrib();
        }

#if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
        make_triangles(primitive_vertices_cc, primitive_colors, primitive_texcoords, primitive_texture_ids, (backface_culling_enabled != 0), ((front_face_orientation == 0) ? cw_orientation : ccw_orientation), triangles);

        if (!triangles.empty()) {
    #if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
            int viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);

            if (wireframe_enabled != 0) {
                segment_struct segment;

                for (size_t itriangle=0; itriangle!=triangles.size(); ++itriangle) {
                    const triangle_struct &triangle = triangles[itriangle];

                    for (size_t isegment=0; isegment!=3; ++isegment) {
                        for (size_t ivertex_segment=0; ivertex_segment!=segment.vertices_count; ++ivertex_segment) {
                            const size_t ivertex_triangle = (isegment + ivertex_segment) % triangle.vertices_count;

                            segment.vertex_cc[ivertex_segment] =  triangle.vertex_cc[ivertex_triangle];
                            segment.color[ivertex_segment] = triangle.color[ivertex_triangle];
                            segment.texcoord[ivertex_segment] = triangle.texcoord[ivertex_triangle];
                            segment.texture_id = triangle.texture_id;
                        }

                        if ((0 <= triangle.texture_id) && (triangle.texture_id < (int)icgl_current_model_textures.size())) {
                            const texture_struct &texture = icgl_current_model_textures[triangle.texture_id];
                            rasterize_segment(segment, viewport[0], viewport[1], viewport[2], viewport[3], ((texture_mapping_enabled != 0) && (texture.is_valid)), texture.width, texture.height, ((!texture.texels.empty()) ? &texture.texels.front() : NULL), (depth_test_enabled != 0), buffer_width, buffer_height, &framebuffer.front(), &depthbuffer.front());
                        }
                        else {
                            rasterize_segment(segment, viewport[0], viewport[1], viewport[2], viewport[3], false, 0, 0, NULL, (depth_test_enabled != 0), buffer_width, buffer_height, &framebuffer.front(), &depthbuffer.front());
                        }
                    }
                }
            }
            else {
                for (size_t itriangle=0; itriangle!=triangles.size(); ++itriangle) {
                    const triangle_struct &triangle = triangles[itriangle];

                    if ((0 <= triangle.texture_id) && (triangle.texture_id < (int)icgl_current_model_textures.size())) {
                        const texture_struct &texture = icgl_current_model_textures[triangle.texture_id];
                        rasterize_triangle(triangles[itriangle], viewport[0], viewport[1], viewport[2], viewport[3], ((texture_mapping_enabled != 0) && (texture.is_valid)), texture.width, texture.height, ((!texture.texels.empty()) ? &texture.texels.front() : NULL), (depth_test_enabled != 0), buffer_width, buffer_height, &framebuffer.front(), &depthbuffer.front());
                    }
                    else {
                        rasterize_triangle(triangles[itriangle], viewport[0], viewport[1], viewport[2], viewport[3], false, 0, 0, NULL, (depth_test_enabled != 0), buffer_width, buffer_height, &framebuffer.front(), &depthbuffer.front());
                    }
                }
            }
    #else
            for (size_t itriangle=0; itriangle!=triangles.size(); ++itriangle) {
                const triangle_struct &triangle = triangles[itriangle];

                glPushAttrib(GL_ALL_ATTRIB_BITS);
                
                if ((texture_mapping_enabled) && (triangle.texture_id != 0)) {
                    glBindTexture(GL_TEXTURE_2D, triangle.texture_id);
                    glEnable(GL_TEXTURE_2D);
                }

                glBegin(GL_TRIANGLES);
                for (size_t ivertex=0; ivertex!=triangle.vertices_count; ++ivertex) {
                    glTexCoord2fv(triangle.texcoord[ivertex].data());
                    glColor4fv(triangle.color[ivertex].data());
                    glVertex4fv(triangle.vertex_cc[ivertex].data());
                }
                glEnd();

                glPopAttrib();
            }
    #endif
        }
#endif

        // Exibir vetores normais.
        if (display_normal_vectors) {

#if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
            segments.clear();
            primitive_vertices_cc.clear();
            primitive_colors.clear();
            primitive_texcoords.clear();
            primitive_texture_ids.clear();

            texcoord_struct texcoord(0.0f, 0.0f);
            color_struct color(0.0f, 0.0f, 0.0f, 1.0f);
#endif

            for (size_t itriangle=0; itriangle!=current_model.triangles_count(); ++itriangle) {
                const object_triangle_struct &triangle = current_model.get_triangle(itriangle);

#if !defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
                glBegin(GL_LINES);
#endif

                for (size_t ivertex=0; ivertex!=triangle.vertex_count; ++ivertex) {
                    const direction_struct &normal_oc = current_model.get_normal(triangle.normal_index[ivertex]);
                    const location_struct &vertex1_oc = current_model.get_vertex(triangle.vertex_index[ivertex]);
                    const location_struct vertex2_oc(vertex1_oc.x/vertex1_oc.w + 0.05f*normal_oc.x, vertex1_oc.y/vertex1_oc.w + 0.05f*normal_oc.y, vertex1_oc.z/vertex1_oc.w + 0.05f*normal_oc.z, 1.0f);

#if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
                    color.r = 0.5f*normal_oc.x + 0.5f;
                    color.g = 0.5f*normal_oc.y + 0.5f;
                    color.b = 0.5f*normal_oc.z + 0.5f;
#else
                    glColor3f(0.5f*normal_oc.x + 0.5f, 0.5f*normal_oc.y + 0.5f, 0.5f*normal_oc.z + 0.5f);
#endif

#if defined(ICGL_ASSIGNMENT_04_VERTEX_TRANSFORMATION)
                    vertex_transformation(vertex1_oc, normal_oc, modelview_matrix, projection_matrix, vertex_ec, vertex_cc, unit_normal_ec);

    #if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
                    primitive_vertices_cc.push_back(vertex_cc);
                    primitive_colors.push_back(color);
                    primitive_texcoords.push_back(texcoord);
                    primitive_texture_ids.push_back(-1);
    #else
                    glVertex4fv(vertex_cc.data());
    #endif

                    vertex_transformation(vertex2_oc, normal_oc, modelview_matrix, projection_matrix, vertex_ec, vertex_cc, unit_normal_ec);

    #if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
                    primitive_vertices_cc.push_back(vertex_cc);
                    primitive_colors.push_back(color);
                    primitive_texcoords.push_back(texcoord);
                    primitive_texture_ids.push_back(-1);
    #else
                    glVertex4fv(vertex_cc.data());
    #endif
#else
                    glVertex4fv(vertex1_oc.data());
                    glVertex4fv(vertex2_oc.data());
#endif
                }

#if !defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)
                glEnd();
#endif
            }

#if defined(ICGL_ASSIGNMENT_06_PRIMITIVE_ASSEMBLY_CLIPPING_AND_CULLING)

            make_segments(primitive_vertices_cc, primitive_colors, primitive_texcoords, primitive_texture_ids, segments);

            if (!segments.empty()) {

    #if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
                int viewport[4];
                glGetIntegerv(GL_VIEWPORT, viewport);

                for (size_t isegment=0; isegment!=segments.size(); ++isegment) {
                    rasterize_segment(segments[isegment], viewport[0], viewport[1], viewport[2], viewport[3], false, 0, 0, NULL, (depth_test_enabled != 0), buffer_width, buffer_height, &framebuffer.front(), &depthbuffer.front());
                }
    #else
                glBegin(GL_LINES);
                for (size_t isegment=0; isegment!=segments.size(); ++isegment) {
                    const segment_struct &segment = segments[isegment];

                    for (size_t ivertex=0; ivertex!=segment.vertices_count; ++ivertex) {
                        glColor4fv(segment.color[ivertex].data());
                        glTexCoord2fv(segment.texcoord[ivertex].data());
                        glVertex4fv(segment.vertex_cc[ivertex].data());
                    }
                }
                glEnd();
    #endif
            }
#endif
        }
    }

#if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, buffer_width - 1.0, 0.0, buffer_height - 1.0, -1.0, 1.0);

    glRasterPos2i(0, 0);
    glDrawPixels(buffer_width, buffer_height, GL_RGBA, GL_FLOAT, &framebuffer.front());
#endif

    glPopAttrib();

    // Tornar visível o buffer atualizado.
    glutSwapBuffers();
}

/* Procedimento chamado toda vez que a subjanela ICGL for redimensionada.
 */
void icgl_subwindow_reshape_callback(int width, int height) {
    
    // Ao redimensionar a janela, fazer com que a viewport também seja redimensionada.
    glViewport(0, 0, width, height);

#if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
    // Redimensionar buffers.
    framebuffer.resize(width * height * 4);
    depthbuffer.resize(width * height);
#endif
}

/* Procedimento que cria a subjaneja que recebe o rendering produzido pela biblioteca do aluno.
 */
int create_icgl_subwindow(const int main_window_id) {

    // Criar a subjanela.
    int resulting_id = glutCreateSubWindow(main_window_id, 0, 0, 1, 1);

    // Atribuir rotinas para tratamento de eventos.
    glutDisplayFunc(icgl_subwindow_display_callback);
    glutReshapeFunc(icgl_subwindow_reshape_callback);

    // Retornar o identificado da subjanela criada.
    return resulting_id;
}


// ROTINAS RELACIONADAS COM A SUBJANEJA QUE CONTÉM OS CONTROLES DE INTERFACE ////////////////////////////////////////////////

/* Procedimento chamado toda vez que um controle simples da GLUI é acionado.
 */
void glui_simple_control_callback(int control) {
    
    // Informar a todas as janelas e subjanelas que o rendering atual está desatualizado.
    glutSetWindow(main_window_id);
    glutPostRedisplay();

    glutSetWindow(gl_subwindow_id);
    glutPostRedisplay();

    glutSetWindow(icgl_subwindow_id);
    glutPostRedisplay();
}

/* Procedimento chamado sempre que a seleção de modelo geométrico selecionado é alterada.
 */
void current_model_changed(int control) {

    // Liberar recursos ocupados pelo modelo carregado anteriormente.
    for (size_t imaterial=0; imaterial<gl_current_model_textures.size(); ++imaterial) {
        glutSetWindow(gl_subwindow_id);
        glDeleteTextures(1, &gl_current_model_textures[imaterial]);

#if !defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
        glutSetWindow(icgl_subwindow_id);
        glDeleteTextures(1, &icgl_current_model_textures[imaterial]);
#endif
    }
    gl_current_model_textures.clear();
    icgl_current_model_textures.clear();
    
    current_model.clear();

    // Caso a seleção seja válida, carregar o novo modelo.
    if ((0 <= current_model_index) && (current_model_index < model_count)) {
        char path[1024] = {};
        sprintf(path, "../media/%s", model_filenames[current_model_index]);
        
        char filename[1024] = {};
        sprintf(filename, "%s.obj", model_filenames[current_model_index]);

        // Abrir modelo e materiais.
        current_model.load_from_file(path, filename);

        // Carregar texturas.
        gl_current_model_textures.resize(current_model.materials_count());
        icgl_current_model_textures.resize(current_model.materials_count());

        for (size_t imaterial=0; imaterial!=current_model.materials_count(); ++imaterial) {
            const object_material_struct &material = current_model.get_material(imaterial);

            if (!material.texture_filename.empty()) {
                ILuint image_name = ilGenImage();
                
                ilBindImage(image_name);
                if (!ilLoadImage(material.texture_filename.c_str())) {
                    ilDeleteImage(image_name);
                    
                    char msg[1024] = {};
                    sprintf(msg, "The image file '%s' could not be opened.", material.texture_filename.c_str());
                    throw std::runtime_error(msg);
                }
                
                const ILint texture_width = ilGetInteger(IL_IMAGE_WIDTH);
                const ILint texture_height = ilGetInteger(IL_IMAGE_HEIGHT);
                const ILint texture_format = ilGetInteger(IL_IMAGE_FORMAT);
                const ILint texture_type = ilGetInteger(IL_IMAGE_TYPE);
                const ILubyte *texture_pixels = ilGetData();
                
                glutSetWindow(gl_subwindow_id);
                glGenTextures(1, &gl_current_model_textures[imaterial]);
                glBindTexture(GL_TEXTURE_2D, gl_current_model_textures[imaterial]);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, texture_format, texture_type, texture_pixels);

#if defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
                texture_struct &texture = icgl_current_model_textures[imaterial];
                texture.is_valid = ((texture_width > 0) && (texture_height > 0));
                texture.width = texture_width;
                texture.height = texture_height;
                texture.texels.resize(texture_width * texture_height * 4);
                ilCopyPixels(0, 0, 0, texture_width, texture_height, 1, IL_RGBA, IL_FLOAT, &texture.texels.front());
#else
                glutSetWindow(icgl_subwindow_id);
                glGenTextures(1, &icgl_current_model_textures[imaterial]);
                glBindTexture(GL_TEXTURE_2D, icgl_current_model_textures[imaterial]);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, texture_format, texture_type, texture_pixels);
#endif
                
                ilDeleteImage(image_name);
            }
            else {
                gl_current_model_textures[imaterial] = 0;
#if !defined(ICGL_ASSIGNMENT_07_RASTERIZATION)
                icgl_current_model_textures[imaterial] = 0;
#endif
            }
        }
    }

    // Informar às subjanelas que o rendering atual está desatualizado.
    glutSetWindow(main_window_id);
    glutPostRedisplay();

    glutSetWindow(gl_subwindow_id);
    glutPostRedisplay();

    glutSetWindow(icgl_subwindow_id);
    glutPostRedisplay();
}

/* Procedimento que cria a subjaneja de controles de interface.
 */
int create_control_subwindow(const int main_window_id) {

    // Criar a subjanela.
    GLUI *glui = GLUI_Master.create_glui_subwindow(main_window_id, GLUI_SUBWINDOW_RIGHT);

    // Atribuir rotinas para tratamento de eventos.
    GLUI_Master.set_glutIdleFunc(NULL);

    // Criar controles de interface.
    {
        GLUI_Rollout *rollout = glui->add_rollout("Model");

        {
            current_model_index = (model_count > 0) ? 0 : -1;

            GLUI_Panel *panel = glui->add_panel_to_panel(rollout, "Current Model");
            GLUI_RadioGroup *group = glui->add_radiogroup_to_panel(panel, &current_model_index, -1, current_model_changed);
            for (int i=0; i<model_count; ++i) {
                glui->add_radiobutton_to_group(group, model_filenames[i]);
            }

            if (current_model_index != -1) {
                current_model_changed(-1);
            }
        }

        {
            GLUI_Rollout *subrollout = glui->add_rollout_to_panel(rollout, "Model Transformation");

            {
                GLUI_Panel *panel = glui->add_panel_to_panel(subrollout, "", GLUI_PANEL_NONE);

                {
                    GLUI_Panel *subpanel = glui->add_panel_to_panel(panel, "Rotation", GLUI_PANEL_NONE);

                    glui->add_rotation_to_panel(subpanel, "Rotation", model_rotation_matrix.data(), -1, glui_simple_control_callback);
                }

                glui->add_column_to_panel(panel, false);

                {
                    GLUI_Panel *subpanel = glui->add_panel_to_panel(panel, "Translation");
        
                    GLUI_Translation *xy_translation = glui->add_translation_to_panel(subpanel, "XY", GLUI_TRANSLATION_XY, &model_translation_displacement[0], -1, glui_simple_control_callback);
                    xy_translation->set_speed(0.05f);

                    glui->add_column_to_panel(subpanel, false);
                
                    GLUI_Translation *z_translation = glui->add_translation_to_panel(subpanel, "Z", GLUI_TRANSLATION_Z, &model_translation_displacement[2], -1, glui_simple_control_callback);
                    z_translation->set_speed(0.05f);
                }
            }
        }

        {
            GLUI_Rollout *subrollout = glui->add_rollout_to_panel(rollout, "Other Options");
        
            glui->add_checkbox_to_panel(subrollout, "Display light source", &display_light_source, -1, glui_simple_control_callback);
            glui->add_checkbox_to_panel(subrollout, "Display normal vectors", &display_normal_vectors, -1, glui_simple_control_callback);
            glui->add_checkbox_to_panel(subrollout, "Wireframe mode enabled", &wireframe_enabled, -1, glui_simple_control_callback);
            glui->add_checkbox_to_panel(subrollout, "Texture mapping enabled", &texture_mapping_enabled, -1, glui_simple_control_callback);

            GLUI_Rollout *subsubrollout = glui->add_rollout_to_panel(subrollout, "Base Color", false);

            {
                GLUI_Spinner *red = glui->add_spinner_to_panel(subsubrollout, "Red ", GLUI_SPINNER_FLOAT, &model_base_color[0], -1, glui_simple_control_callback);
                red->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
                red->set_speed(0.01f);
                red->set_alignment(GLUI_ALIGN_RIGHT);

                GLUI_Spinner *green = glui->add_spinner_to_panel(subsubrollout, "Green ", GLUI_SPINNER_FLOAT, &model_base_color[1], -1, glui_simple_control_callback);
                green->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
                green->set_speed(0.01f);
                green->set_alignment(GLUI_ALIGN_RIGHT);

                GLUI_Spinner *blue = glui->add_spinner_to_panel(subsubrollout, "Blue ", GLUI_SPINNER_FLOAT, &model_base_color[2], -1, glui_simple_control_callback);
                blue->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
                blue->set_speed(0.01f);
                blue->set_alignment(GLUI_ALIGN_RIGHT);
            }
        }

        {
            GLUI_Rollout *subrollout = glui->add_rollout_to_panel(rollout, "Front-Face Orientation");
            GLUI_RadioGroup *group = glui->add_radiogroup_to_panel(subrollout, &front_face_orientation, -1, glui_simple_control_callback);
            glui->add_radiobutton_to_group(group, "CW");
            glui->add_radiobutton_to_group(group, "CCW");

            glui->add_checkbox_to_panel(subrollout, "Back-face culling enabled", &backface_culling_enabled, -1, glui_simple_control_callback);
        }
    }

    {
        GLUI_Rollout *rollout = glui->add_rollout("Camera", false);

        {
            GLUI_Rollout *subrollout = glui->add_rollout_to_panel(rollout, "Perspective Projection", false);

            GLUI_Spinner *fovy = glui->add_spinner_to_panel(subrollout, "Field of view (Y)", GLUI_SPINNER_FLOAT, &camera_fovy, -1, glui_simple_control_callback);
            fovy->set_float_limits(0.0f, FLT_MAX, GLUI_LIMIT_CLAMP);
            fovy->set_speed(0.001f);
            fovy->set_alignment(GLUI_ALIGN_RIGHT);

            GLUI_Spinner *aspect = glui->add_spinner_to_panel(subrollout, "Aspect ratio", GLUI_SPINNER_FLOAT, &camera_aspect, -1, glui_simple_control_callback);
            aspect->set_float_limits(0.0f, FLT_MAX, GLUI_LIMIT_CLAMP);
            fovy->set_speed(0.001f);
            aspect->set_alignment(GLUI_ALIGN_RIGHT);
        
            GLUI_Spinner *znear = glui->add_spinner_to_panel(subrollout, "Near plane (Z)", GLUI_SPINNER_FLOAT, &camera_znear, -1, glui_simple_control_callback);
            znear->set_float_limits(0.0f, FLT_MAX, GLUI_LIMIT_CLAMP);
            fovy->set_speed(0.001f);
            znear->set_alignment(GLUI_ALIGN_RIGHT);
        
            GLUI_Spinner *zfar = glui->add_spinner_to_panel(subrollout, "Far plane (Z)", GLUI_SPINNER_FLOAT, &camera_zfar, -1, glui_simple_control_callback);
            zfar->set_float_limits(0.0f, FLT_MAX, GLUI_LIMIT_CLAMP);
            fovy->set_speed(0.001f);
            zfar->set_alignment(GLUI_ALIGN_RIGHT);
        }

        {
            GLUI_Rollout *subrollout = glui->add_rollout_to_panel(rollout, "Camera Transformation", false);

            {
                GLUI_Panel *panel = glui->add_panel_to_panel(subrollout, "", GLUI_PANEL_NONE);

                {
                    GLUI_Panel *subpanel = glui->add_panel_to_panel(panel, "Rotation", GLUI_PANEL_NONE);

                    glui->add_rotation_to_panel(subpanel, "Rotation", camera_rotation_matrix.data(), -1, glui_simple_control_callback);
                }

                glui->add_column_to_panel(panel, false);

                {
                    GLUI_Panel *subpanel = glui->add_panel_to_panel(panel, "Translation");
        
                    GLUI_Translation *xy_translation = glui->add_translation_to_panel(subpanel, "XY", GLUI_TRANSLATION_XY, &camera_translation_displacement[0], -1, glui_simple_control_callback);
                    xy_translation->set_speed(0.05f);

                    glui->add_column_to_panel(subpanel, false);
                
                    GLUI_Translation *z_translation = glui->add_translation_to_panel(subpanel, "Z", GLUI_TRANSLATION_Z, &camera_translation_displacement[2], -1, glui_simple_control_callback);
                    z_translation->set_speed(0.05f);
                }
            }
        }
    }

    {
        GLUI_Rollout *rollout = glui->add_rollout("Light", true);
        
        glui->add_checkbox_to_panel(rollout, "Lighting enabled", &lighting_enabled, -1, glui_simple_control_callback);

        {
            GLUI_Rollout *subrollout = glui->add_rollout_to_panel(rollout, "Ambient Intensity", false);
            
            GLUI_Spinner *red = glui->add_spinner_to_panel(subrollout, "Red ", GLUI_SPINNER_FLOAT, &light.ambient[0], -1, glui_simple_control_callback);
            red->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
            red->set_speed(0.01f);
            red->set_alignment(GLUI_ALIGN_RIGHT);

            GLUI_Spinner *green = glui->add_spinner_to_panel(subrollout, "Green ", GLUI_SPINNER_FLOAT, &light.ambient[1], -1, glui_simple_control_callback);
            green->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
            green->set_speed(0.01f);
            green->set_alignment(GLUI_ALIGN_RIGHT);

            GLUI_Spinner *blue = glui->add_spinner_to_panel(subrollout, "Blue ", GLUI_SPINNER_FLOAT, &light.ambient[2], -1, glui_simple_control_callback);
            blue->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
            blue->set_speed(0.01f);
            blue->set_alignment(GLUI_ALIGN_RIGHT);
        }

        {
            GLUI_Rollout *subrollout = glui->add_rollout_to_panel(rollout, "Diffuse Intensity", false);
            
            GLUI_Spinner *red = glui->add_spinner_to_panel(subrollout, "Red ", GLUI_SPINNER_FLOAT, &light.diffuse[0], -1, glui_simple_control_callback);
            red->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
            red->set_speed(0.01f);
            red->set_alignment(GLUI_ALIGN_RIGHT);

            GLUI_Spinner *green = glui->add_spinner_to_panel(subrollout, "Green ", GLUI_SPINNER_FLOAT, &light.diffuse[1], -1, glui_simple_control_callback);
            green->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
            green->set_speed(0.01f);
            green->set_alignment(GLUI_ALIGN_RIGHT);

            GLUI_Spinner *blue = glui->add_spinner_to_panel(subrollout, "Blue ", GLUI_SPINNER_FLOAT, &light.diffuse[2], -1, glui_simple_control_callback);
            blue->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
            blue->set_speed(0.01f);
            blue->set_alignment(GLUI_ALIGN_RIGHT);
        }

        {
            GLUI_Rollout *subrollout = glui->add_rollout_to_panel(rollout, "Specular Intensity", false);
            
            GLUI_Spinner *red = glui->add_spinner_to_panel(subrollout, "Red ", GLUI_SPINNER_FLOAT, &light.specular[0], -1, glui_simple_control_callback);
            red->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
            red->set_speed(0.01f);
            red->set_alignment(GLUI_ALIGN_RIGHT);

            GLUI_Spinner *green = glui->add_spinner_to_panel(subrollout, "Green ", GLUI_SPINNER_FLOAT, &light.specular[1], -1, glui_simple_control_callback);
            green->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
            green->set_speed(0.01f);
            green->set_alignment(GLUI_ALIGN_RIGHT);

            GLUI_Spinner *blue = glui->add_spinner_to_panel(subrollout, "Blue ", GLUI_SPINNER_FLOAT, &light.specular[2], -1, glui_simple_control_callback);
            blue->set_float_limits(0.0f, 1.0f, GLUI_LIMIT_CLAMP);
            blue->set_speed(0.01f);
            blue->set_alignment(GLUI_ALIGN_RIGHT);
        }
    }

    {
        GLUI_Rollout *rollout = glui->add_rollout("Other Options");
        
        glui->add_checkbox_to_panel(rollout, "Depth test enabled", &depth_test_enabled, -1, glui_simple_control_callback);
    }

    // Informar para a GLUI quem é a janela principal.
    glui->set_main_gfx_window(main_window_id);

    // Retornar o identificado da subjanela criada.
    return glui->get_glut_window_id();
}

// PROGRAMA PRINCIPAL ///////////////////////////////////////////////////////////////////////////////////////////////////////

/* Procedimento principal da aplicação. É aqui que a diversão começa!
 */
int main(int argc, char *argv[]) {

    // Inicializar a FreeGLUT.
    glutInit(&argc, argv);

    // Iniializar DevIL.
    ilInit();

    // Definir configuração dos buffers gerados no rendering. Nós queremos front e back buffers para RGBA e DEPTH.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // Obter dimensões da tela.
    const int screen_width = glutGet(GLUT_SCREEN_WIDTH);
    const int screen_height = glutGet(GLUT_SCREEN_HEIGHT);

    // Criar janela principal da aplicação.
    const int width = screen_width - 100;
    const int height = screen_height - 150;

    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    
    main_window_id = glutCreateWindow("OpenGL vs. ICGL");
    GLUI_Master.set_glutDisplayFunc(main_window_display_callback);
    GLUI_Master.set_glutKeyboardFunc(main_window_keyboard_callback);
    GLUI_Master.set_glutSpecialFunc(main_window_keyboard_special_callback);
    GLUI_Master.set_glutMouseFunc(main_window_mouse_callback);
    GLUI_Master.set_glutReshapeFunc(main_window_reshape_callback);

    // Criar subjanela onde é exibido o rendering do OpenGL.
    gl_subwindow_id = create_gl_subwindow(main_window_id);

    // Criar subjanela onde é exibido o rendering do ICGL.
    icgl_subwindow_id = create_icgl_subwindow(main_window_id);

    // Criar subjanela onde serão colocados os controles da interface.
    control_subwindow_id = create_control_subwindow(main_window_id);

    // Invocar loop principal da aplicação. A partir daqui a execução do main(...) não
    // avançará e os callbacks da FreeGLUT serão chamados em resposta a eventos.
    glutMainLoop();
    
    // Destrutir janela principal.
    glutDestroyWindow(main_window_id);

    // Sinalizar término bem sucedido do programa.
    return EXIT_SUCCESS;
}
