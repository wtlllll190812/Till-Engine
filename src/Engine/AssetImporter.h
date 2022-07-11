#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh;
class AssetImporter
{
public:
	AssetImporter();
	~AssetImporter();

	Mesh* LoadMesh(std::string path);
private:
	Assimp::Importer modelImporter;
};