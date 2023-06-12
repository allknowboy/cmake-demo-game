#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "component/component.h"

using std::vector;
using std::string;

class MeshFilter : public Component {
public:
    MeshFilter();
    ~MeshFilter();
public:
    //顶点
    struct Vertex
    {
        glm::vec3 pos_;
        glm::vec4 color_;
        glm::vec2 uv_;
    };

    //Mesh文件头
    struct MeshFileHead {
        char type_[4];
        unsigned short vertex_num_; // 顶点个数
        unsigned short vertex_index_num_; // 索引个数
    };

    //Mesh数据
    struct Mesh {
        unsigned short vertex_num_; // 顶点个数
        unsigned short vertex_index_num_; // 索引个数
        Vertex* vertex_data_; // 顶点数据
        unsigned short* vertex_index_data_; // 顶点索引数据
    };

    void LoadMesh(string mesh_file_path); // 加载Mesh文件
    void LoadObj(string obj_file_path); // 加载Obj文件

    Mesh* mesh(){ return mesh_; }; // Mesh对象
private:
    Mesh* mesh_; // Mesh对象
    typedef struct {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texcoords;
        std::vector<unsigned short> v_indices;
        std::vector<unsigned short> vn_indices;
        std::vector<unsigned short> vt_indices;
        std::vector<Vertex> vertex_data;
    } ObjMesh;
    ObjMesh* objMesh_; // ObjMesh
};