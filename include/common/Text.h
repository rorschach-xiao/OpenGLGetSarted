#include <iostream>
#include <map>
#include <string>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

#include "common/MyShaderProgram.h"


#ifndef GETSTARTED_TEXT_H
#define GETSTARTED_TEXT_H
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};
namespace common {

    class Text {
    public:
        Text(const char *fontPath);
        void RenderText(MyShaderProgram &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    private:
        std::map<GLchar, Character> Characters;
        GLuint VAO, VBO;
        void setupText(const char *fontPath);
    };
}

#endif //GETSTARTED_TEXT_H
