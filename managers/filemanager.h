#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <QString>
#include <memory>
#include <QOpenGLTexture>

class Vertex;

class FileManager
{
public:
    static FileManager* GetInstance();

    std::pair<std::vector<Vertex>, std::vector<unsigned int> > ReadFile(const QString &File);
    std::shared_ptr<QOpenGLTexture> LoadTexture(const QString& File, bool MirrorHorziontally=false, bool MirrorVertically=true);
    void WriteTXTFile(const QString& File, std::vector<Vertex> &Vertices);

private:
    static FileManager* m_Instance;

    std::pair<std::vector<Vertex>, std::vector<unsigned int> > ReadTXTFile(const QString &File);
    std::pair<std::vector<Vertex>, std::vector<unsigned int> > ReadOBJFile(const QString &File);

    const QString m_DirPath = "../GSOpenGL2019/data/Objects/";
    const QString m_DirTexturePath = "../GSOpenGL2019/data/Textures/";

    FileManager();
    ~FileManager();
};

#endif // FILEMANAGER_H
