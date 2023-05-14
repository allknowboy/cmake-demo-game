#include <fstream>
#include "mesh_filter.h"
#include "Utils/application.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iostream>


using std::ifstream;
using std::ios;


MeshFilter::MeshFilter()
    :mesh_(nullptr) {
}

void MeshFilter::LoadMesh(string mesh_file_path) {
    //读取 Mesh文件头
    ifstream input_file_stream((Application::data_path() + mesh_file_path).c_str(), ios::in | ios::binary);
    MeshFileHead mesh_file_head;
    input_file_stream.read((char*)&mesh_file_head, sizeof(mesh_file_head));
    //读取顶点数据
    unsigned char* vertex_data = (unsigned char*)malloc(mesh_file_head.vertex_num_ * sizeof(Vertex));
    input_file_stream.read((char*)vertex_data, mesh_file_head.vertex_num_ * sizeof(Vertex));
    //读取顶点索引数据
    unsigned short* vertex_index_data = (unsigned short*)malloc(mesh_file_head.vertex_index_num_ * sizeof(unsigned short));
    input_file_stream.read((char*)vertex_index_data, mesh_file_head.vertex_index_num_ * sizeof(unsigned short));
    input_file_stream.close();

    mesh_ = new Mesh();
    mesh_->vertex_num_ = mesh_file_head.vertex_num_;
    mesh_->vertex_index_num_ = mesh_file_head.vertex_index_num_;
    mesh_->vertex_data_ = (Vertex*)vertex_data;
    mesh_->vertex_index_data_ = vertex_index_data;
}

void MeshFilter::LoadObj(string obj_file_path) {
    tinyobj::callback_t cb;
    // 名称回调
    cb.object_cb = [](void *user_data, const char *name) {
        std::cout << "object_cb: " << name << std::endl;
    };
    // mtllib回调
    cb.mtllib_cb = [](void *user_data, const tinyobj::material_t *materials, int num_materials) {
        printf("mtllib. # of materials = %d\n", num_materials);
    };
    // 顶点回调
    cb.vertex_cb = [](void *user_data, float x, float y, float z, float w){
        auto mesh = reinterpret_cast<ObjMesh *>(user_data);
        mesh->vertices.push_back(glm::vec3(x, y, z));
    };
    // 法线回调
    cb.normal_cb = [](void *user_data, float x, float y, float z){
        auto mesh = reinterpret_cast<ObjMesh *>(user_data);
        mesh->normals.push_back(glm::vec3(x, y, z));
    };
    // 材质uv
    cb.texcoord_cb = [](void *user_data, float x, float y, float z){
        auto mesh = reinterpret_cast<ObjMesh *>(user_data);
        mesh->texcoords.push_back(glm::vec2(x, y));
    };
    // 索引
    cb.index_cb = [](void *user_data, tinyobj::index_t *indices, int num_indices){
        auto mesh = reinterpret_cast<ObjMesh *>(user_data);
        for (int i = 0; i < num_indices; i++) {
            tinyobj::index_t idx = indices[i];
            if (idx.vertex_index != 0) {
                // 顶点索引
                mesh->v_indices.push_back(idx.vertex_index - 1);
            }
            if (idx.normal_index != 0) {
                // 法线索引
                mesh->vn_indices.push_back(idx.normal_index - 1);
            }
            if (idx.texcoord_index != 0) {
                // uv索引
                mesh->vt_indices.push_back(idx.texcoord_index -1);
            }
        }
    };
    // 使用材质回调
    cb.usemtl_cb = [](void *user_data, const char *name, int material_idx){
        if (material_idx > -1) {
            printf("usemtl. material id = %d\n", material_idx);
        } else {
            printf("usemtl. name = %s\n", name);
        }
    };
    // 组回调
    cb.group_cb = [](void *user_data, const char **names, int num_names){

    };

    std::ifstream ifs((Application::data_path() + obj_file_path).c_str());
    if (ifs.fail()) {
    std::cerr << "file not found." << std::endl;
        return;
    }
    objMesh_ = new ObjMesh();
    std::string warn;
    std::string err;
    tinyobj::MaterialFileReader mtlReader((Application::data_path() + "obj/").c_str());
    tinyobj::LoadObjWithCallback(ifs, cb, objMesh_, &mtlReader, &err);
    if (!err.empty()) {
        std::cerr << err << std::endl;
    }
    mesh_ = new Mesh();
    size_t n = objMesh_->vertices.size();
    for (int i = 0; i < n; ++i) {
        objMesh_->vertex_data.push_back(Vertex{objMesh_->vertices[i], glm::vec4(1.f, 1.f, 1.f, 1.f), objMesh_->texcoords[i]});
    }
    mesh_->vertex_num_ = n;
    mesh_->vertex_index_num_ = objMesh_->v_indices.size();
    mesh_->vertex_data_ = objMesh_->vertex_data.data();
    mesh_->vertex_index_data_ = objMesh_->v_indices.data();
}

MeshFilter::~MeshFilter() {
    delete(mesh_);
    mesh_= nullptr;

    delete(objMesh_);
    objMesh_= nullptr;
}