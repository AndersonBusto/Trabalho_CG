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

/* - ICGL - IC-UFF Graphics Library
 * Conjunto de operações utilizadas para ensino de Pipeline Gráfico no Instito de Computação (IC) da Universidade Federal Fluminense (UFF).
 */
#include <icgl.h>


// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE COLOR_STRUCT /////////////////////////////////////////////////////////////////////////

color_struct::color_struct() :
    r(m_channels[0]), g(m_channels[1]), b(m_channels[2]), a(m_channels[3]) {

    r = 1.0f; g = 1.0f; b = 1.0f; a = 1.0f;
}

color_struct::color_struct(float r_, float g_, float b_, float a_) :
    r(m_channels[0]), g(m_channels[1]), b(m_channels[2]), a(m_channels[3]) {

    r = r_; g = g_; b = b_; a = a_;
}

color_struct::color_struct(const color_struct &other) :
    r(m_channels[0]), g(m_channels[1]), b(m_channels[2]), a(m_channels[3]) {

    for (size_t i=0; i!=channels_count; ++i) {
        m_channels[i] = other.m_channels[i];
    }
}

float* color_struct::data() {
    return m_channels;
}

const float* color_struct::data() const {
    return m_channels;
}

color_struct& color_struct::operator = (const color_struct &other) {
    for (size_t i=0; i!=channels_count; ++i) {
        m_channels[i] = other.m_channels[i];
    }
    return *this;
}

float& color_struct::operator [] (size_t i) {
    return m_channels[i];
}

const float& color_struct::operator [] (size_t i) const {
    return m_channels[i];
}


// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE DIRECTION_STRUCT /////////////////////////////////////////////////////////////////////

direction_struct::direction_struct() :
    x(m_coords[0]), y(m_coords[1]), z(m_coords[2]) {

    x = 0.0f; y = 0.0f; z = 1.0f;
}

direction_struct::direction_struct(float x_, float y_, float z_) :
    x(m_coords[0]), y(m_coords[1]), z(m_coords[2]) {

    x = x_; y = y_; z = z_;
}

direction_struct::direction_struct(const direction_struct &other) :
    x(m_coords[0]), y(m_coords[1]), z(m_coords[2]) {

    for (size_t i=0; i!=coords_count; ++i) {
        m_coords[i] = other.m_coords[i];
    }
}

float* direction_struct::data() {
    return m_coords;
}

const float* direction_struct::data() const {
    return m_coords;
}

direction_struct& direction_struct::operator = (const direction_struct &other) {
    for (size_t i=0; i!=coords_count; ++i) {
        m_coords[i] = other.m_coords[i];
    }
    return *this;
}

float& direction_struct::operator [] (size_t i) {
    return m_coords[i];
}

const float& direction_struct::operator [] (size_t i) const {
    return m_coords[i];
}


// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE LOCATION_STRUCT //////////////////////////////////////////////////////////////////////

location_struct::location_struct() :
    x(m_coords[0]), y(m_coords[1]), z(m_coords[2]), w(m_coords[3]) {

    x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f;
}


location_struct::location_struct(float x_, float y_, float z_, float w_) :
    x(m_coords[0]), y(m_coords[1]), z(m_coords[2]), w(m_coords[3]) {

    x = x_; y = y_; z = z_; w = w_;
}

location_struct::location_struct(const location_struct &other) :
    x(m_coords[0]), y(m_coords[1]), z(m_coords[2]), w(m_coords[3]) {

    for (size_t i=0; i!=coords_count; ++i) {
        m_coords[i] = other.m_coords[i];
    }
}

float* location_struct::data() {
    return m_coords;
}

const float* location_struct::data() const {
    return m_coords;
}

location_struct& location_struct::operator = (const location_struct &other) {
    for (size_t i=0; i!=coords_count; ++i) {
        m_coords[i] = other.m_coords[i];
    }
    return *this;
}

float& location_struct::operator [] (size_t i) {
    return m_coords[i];
}

const float& location_struct::operator [] (size_t i) const {
    return m_coords[i];
}


// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE TEXCOORD_STRUCT //////////////////////////////////////////////////////////////////////

texcoord_struct::texcoord_struct() :
    u(m_coords[0]), v(m_coords[1]) {

    u = 0.0f; v = 0.0f;
}

texcoord_struct::texcoord_struct(float u_, float v_) :
    u(m_coords[0]), v(m_coords[1]) {

    u = u_; v = v_;
}

texcoord_struct::texcoord_struct(const texcoord_struct &other) :
    u(m_coords[0]), v(m_coords[1]) {

    for (size_t i=0; i!=coords_count; ++i) {
        m_coords[i] = other.m_coords[i];
    }
}

float* texcoord_struct::data() {
    return m_coords;
}

const float* texcoord_struct::data() const {
    return m_coords;
}

texcoord_struct& texcoord_struct::operator = (const texcoord_struct &other) {
    for (size_t i=0; i!=coords_count; ++i) {
        m_coords[i] = other.m_coords[i];
    }
    return *this;
}

float& texcoord_struct::operator [] (size_t i) {
    return m_coords[i];
}

const float& texcoord_struct::operator [] (size_t i) const {
    return m_coords[i];
}


// IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE MATRIX_STRUCT ////////////////////////////////////////////////////////////////////////

matrix_struct::matrix_struct() {
    m_elems[0] = 1.0f; m_elems[4] = 0.0f; m_elems[ 8] = 0.0f; m_elems[12] = 0.0f;
    m_elems[1] = 0.0f; m_elems[5] = 1.0f; m_elems[ 9] = 0.0f; m_elems[13] = 0.0f;
    m_elems[2] = 0.0f; m_elems[6] = 0.0f; m_elems[10] = 1.0f; m_elems[14] = 0.0f;
    m_elems[3] = 0.0f; m_elems[7] = 0.0f; m_elems[11] = 0.0f; m_elems[15] = 1.0f;
}

matrix_struct::matrix_struct(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31, float m02, float m12, float m22, float m32, float m03, float m13, float m23, float m33) {
    m_elems[0] = m00; m_elems[4] = m01; m_elems[ 8] = m02; m_elems[12] = m03;
    m_elems[1] = m10; m_elems[5] = m11; m_elems[ 9] = m12; m_elems[13] = m13;
    m_elems[2] = m20; m_elems[6] = m21; m_elems[10] = m22; m_elems[14] = m23;
    m_elems[3] = m30; m_elems[7] = m31; m_elems[11] = m32; m_elems[15] = m33;
}

matrix_struct::matrix_struct(const matrix_struct &other) {
    for (size_t i=0; i!=elems_count; ++i) {
        m_elems[i] = other.m_elems[i];
    }
}

float* matrix_struct::data() {
    return m_elems;
}

const float* matrix_struct::data() const {
    return m_elems;
}

matrix_struct& matrix_struct::operator = (const matrix_struct &other) {
    for (size_t i=0; i!=elems_count; ++i) {
        m_elems[i] = other.m_elems[i];
    }
    return *this;
}

float& matrix_struct::operator [] (size_t i) {
    return m_elems[i];
}

const float& matrix_struct::operator [] (size_t i) const {
    return m_elems[i];
}

float& matrix_struct::operator () (size_t row, size_t col) {
    return m_elems[(col*rows_count)+row];
}

const float& matrix_struct::operator () (size_t row, size_t col) const {
    return m_elems[(col*rows_count)+row];
}
