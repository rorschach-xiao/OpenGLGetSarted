#include "Mesh.h"
#include "stb_image.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#ifndef GETSTARTED_MODEL_H
#define GETSTARTED_MODEL_H

using namespace std;

namespace common {

    class Model {
    public:
        vector<Texture> textures_loaded;
        vector <Mesh> meshes;
        string directory;
        bool gammaCorrection;

        Model(char *path, bool gamma = false) :gammaCorrection(gamma){
            loadModel(path);
        }

        void Draw(MyShaderProgram shader);

    private:

        /*  函数   */
        void loadModel(string path);

        void processNode(aiNode *node, const aiScene *scene);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        vector <Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

        unsigned int TextureFromFile(const char *path, const string &directory);
    };

}

#endif //GETSTARTED_MODEL_H
