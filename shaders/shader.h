#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_4_1_Core>

class Shader : protected QOpenGLFunctions_4_1_Core
{
public:
    Shader( const GLchar *vertexPath, const GLchar *fragmentPath );

    void use();

    GLuint getProgram() const;

    GLint getUniformLocation(const char* name);

    void setInt(const char* name, const int data);
    void setFloat(const char* name, const float data);
    void setVec3(const char* name, const float* data);
    void setMat4(const char* name, const float* data);

private:
    GLuint program;
};

#endif
