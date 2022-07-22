#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <memory>
class Mesh;
class AssetImporter
{
public:
	AssetImporter();
	~AssetImporter();

	static std::vector<std::shared_ptr<Mesh>> LoadMeshs(std::string path);
	static std::shared_ptr<Mesh> LoadMesh(std::string path);
private:
	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<std::shared_ptr<Mesh>>& res);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

	static Assimp::Importer modelImporter;
};