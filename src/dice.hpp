#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

using u32 = std::uint32_t;

#warning remove this
using Shader = u32;

struct Vertex {
    glm::vec3 position;
    glm::vec2 tex_coords;
};

struct Texture {
    GLuint id;
    std::string type;
};

class Mesh {
private:
    GLuint m_vao, m_vbo, m_ebo;

    std::vector<Vertex> m_vertices;
    std::vector<u32> m_indices;
    std::vector<Texture> m_textures;

public:
    Mesh(std::vector<Vertex>, std::vector<u32>, std::vector<Texture>);

    void draw(const Shader &);
};
