#include "AssetImporter.h"
#include "Mesh.h"
#include "Debug.h"
#include <fstream>
#include "TLCore.h"


Assimp::Importer AssetImporter::modelImporter;
std::map<std::string, std::shared_ptr<Mesh>> AssetImporter::buildinModels;

void AssetImporter::Init()
{
    Debug::GetEngineLogger()->info("AssetImporter init");
    buildinModels["Sphere"] = LoadMeshs(MODEL_PATH"Sphere/Sphere.obj")[0];
    buildinModels["Cube"] = LoadMeshs(MODEL_PATH"Cube/Cube.obj")[0];
    buildinModels["Cylinder"]=LoadMeshs(MODEL_PATH"Cylinder/Cylinder.obj")[0];
    buildinModels["Plane"] = LoadMeshs(MODEL_PATH"Plane/Plane.obj")[0];
    Debug::GetEngineLogger()->info("AssetImporter inited");
}

std::vector<std::shared_ptr<Mesh>> AssetImporter::LoadMeshs(std::string path)
{
    Debug::GetEngineLogger()->info("Load model {0}",path);
    std::vector<std::shared_ptr<Mesh>> res;

    const aiScene* scene = modelImporter.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        Debug::GetEngineLogger()->error("ERROR::ASSIMP:: {0}", modelImporter.GetErrorString());
        return res;
    }
    // retrieve the directory path of the filepath
    std::string directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    ProcessNode(scene->mRootNode, scene,  res);
    return res;
}

std::shared_ptr<Mesh> AssetImporter::LoadMesh(std::string path)
{
    return std::shared_ptr<Mesh>();
}

std::shared_ptr<Mesh> AssetImporter::GetMeshByName(std::string name)
{
    if (buildinModels.count(name))
        return buildinModels[name];
    else
    {
        Debug::GetEngineLogger()->info("Can not find buildin mesh {0}",name);
        return nullptr;
    }
}

void AssetImporter::ProcessNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<Mesh>>& res)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        res.push_back(std::shared_ptr<Mesh>(ProcessMesh(mesh, scene)));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, res);
    }
}

Mesh* AssetImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // return a mesh object created from the extracted mesh data
    return new Mesh(vertices, indices);
}