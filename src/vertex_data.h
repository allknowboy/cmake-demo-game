#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <glm/glm.hpp>
using std::vector;
using std::distance;

using std::ofstream;
using std::ios;
using std::string;


//顶点
struct Vertex
{
        glm::vec3 pos_; // 位置
        glm::vec4 color_;       // 颜色
        glm::vec2 uv_;  // uv
};

static const Vertex kVertexs[36] = {
        glm::vec3{ -1.0f, -1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.25f},
        glm::vec3{ 1.0f, -1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.5f},
        glm::vec3{ 1.0f, 1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.f, 0.5f},
        glm::vec3{ 1.0f, 1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.f, 0.5f},
        glm::vec3{ -1.0f, 1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.f, 0.25f},
        glm::vec3{ -1.0f, -1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.25f},

        glm::vec3{ 1.0f, -1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.5f},
        glm::vec3{ -1.0f, -1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.25f},
        glm::vec3{ -1.0f, 1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.75f, 0.25f},
        glm::vec3{ -1.0f, 1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.75f, 0.25f},
        glm::vec3{ 1.0f, 1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.75f, 0.5f},
        glm::vec3{ 1.0f, -1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.5f},

        glm::vec3{ -1.0f, -1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.25f},
        glm::vec3{ -1.0f, -1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.25f},
        glm::vec3{ -1.0f, 1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.f},
        glm::vec3{ -1.0f, 1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.f},
        glm::vec3{ -1.0f, 1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.f},
        glm::vec3{ -1.0f, -1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.25f},

        glm::vec3{ 1.0f, -1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.5f},
        glm::vec3{ 1.0f, -1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.5f},
        glm::vec3{ 1.0f, 1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.75f},
        glm::vec3{ 1.0f, 1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.75f},
        glm::vec3{ 1.0f, 1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.75f},
        glm::vec3{ 1.0f, -1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.5f},

        glm::vec3{ -1.0f, 1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 1.f, 0.25f},
        glm::vec3{ 1.0f, 1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 1.f, 0.5f},
        glm::vec3{ 1.0f, 1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.75f, 0.5f},
        glm::vec3{ 1.0f, 1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.75f, 0.5f},
        glm::vec3{ -1.0f, 1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.75f, 0.25f},
        glm::vec3{ -1.0f, 1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 1.0f, 0.25f},

        glm::vec3{ -1.0f, -1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.25f},
        glm::vec3{ 1.0f, -1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.5f},
        glm::vec3{ 1.0f, -1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.5f},
        glm::vec3{ 1.0f, -1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.5f},
        glm::vec3{ -1.0f, -1.0f, 1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.25f, 0.25f},
        glm::vec3{ -1.0f, -1.0f, -1.0f}, glm::vec4(1.0f,1.0f,1.0f,1.0f), glm::vec2{ 0.5f, 0.25f}
};

//去重的顶点Vector
static vector<Vertex> kVertexRemoveDumplicateVector;
//顶点索引Vector
static vector<unsigned short> kVertexIndexVector;

//顶点去重
static void VertexRemoveDumplicate() {
        for (int i = 0; i < 36; ++i) {
                const Vertex& vertex = kVertexs[i];
                //判断顶点是否存在
                int index = -1;
                for (int j = 0; j < kVertexRemoveDumplicateVector.size(); ++j) {
                        if (vertex.pos_ == kVertexRemoveDumplicateVector[j].pos_ 
                        && vertex.color_ == kVertexRemoveDumplicateVector[j].color_ 
                        && vertex.uv_ == kVertexRemoveDumplicateVector[j].uv_) {
                                index=j;
                                break;
                        }
                }
                if(index < 0) {
                        //没找到就将目标顶点加入kVertexRemoveDumplicateVector，并记录索引为kVertexRemoveDumplicateVector.size()。
                        kVertexRemoveDumplicateVector.push_back(vertex);
                        kVertexIndexVector.push_back(kVertexRemoveDumplicateVector.size() - 1);
                } else {
                        //找到了目标顶点，记录索引为kVertexRemoveDumplicateVector的位置。
                        kVertexIndexVector.push_back(index);
                }
        }
}

//Mesh文件头
struct MeshFileHead{
        char type_[4];
        unsigned short vertex_num_;//顶点个数
        unsigned short vertex_index_num_;//索引个数
};

//导出Mesh文件
static void ExportMesh(string save_path) {
        ofstream output_file_stream(save_path, ios::out | ios::binary);
        MeshFileHead mesh_file_head;
        mesh_file_head.type_[0] = 'm';
        mesh_file_head.type_[1] = 'e';
        mesh_file_head.type_[2] = 's';
        mesh_file_head.type_[3] = 'h';
        mesh_file_head.vertex_num_ = kVertexRemoveDumplicateVector.size();
        mesh_file_head.vertex_index_num_ = kVertexIndexVector.size();
        //写入文件头
        output_file_stream.write((char*)&mesh_file_head, sizeof(mesh_file_head));
        //写入顶点数据
        output_file_stream.write((char*)&kVertexRemoveDumplicateVector[0], kVertexRemoveDumplicateVector.size() * sizeof(Vertex));
        //写入索引数据
        output_file_stream.write((char*)&kVertexIndexVector[0], kVertexIndexVector.size() * sizeof(unsigned short));
        output_file_stream.close();
}