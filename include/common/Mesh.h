
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <vector>
#include "MyShaderProgram.h"

#ifndef GETSTARTED_MESH_H
#define GETSTARTED_MESH_H
#define MAX_BONE_INFLUENCE 4
using namespace std;


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
//    // tangent
//    glm::vec3 Tangent;
//    // bitangent
//    glm::vec3 Bitangent;
//    //bone indexes which will influence this vertex
//    int m_BoneIDs[MAX_BONE_INFLUENCE];
//    //weights from each bone
//    float m_Weights[MAX_BONE_INFLUENCE];
};
struct Texture {
    unsigned int id;
    string type;
    string path;
};

namespace common {
    class Mesh {
    public:
        /*  网格数据  */
        vector <Vertex> vertices;
        vector<unsigned int> indices;
        vector <Texture> textures;

        /*  函数  */
        Mesh(vector <Vertex> vertices, vector<unsigned int> indices, vector <Texture> textures);

        void Draw(MyShaderProgram shader);

    private:
        /*  渲染数据  */
        unsigned int VAO, VBO, EBO;

        /*  函数  */
        void setupMesh();
    };
}

#endif //GETSTARTED_MESH_H
