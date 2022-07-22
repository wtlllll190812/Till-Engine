#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <memory>
#include <map>

class Mesh;
class AssetImporter
{
public:
	static std::map<std::string,std::shared_ptr<Mesh>> buildinModels;

public:
	static void Init();
	static std::vector<std::shared_ptr<Mesh>> LoadMeshs(std::string path);
	static std::shared_ptr<Mesh> LoadMesh(std::string path);
	static std::shared_ptr<Mesh> GetMeshByName(std::string);

private:
	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<Mesh>>& res);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
private:
	static Assimp::Importer modelImporter;
};