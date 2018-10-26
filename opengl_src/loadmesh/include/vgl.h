#pragma once

#include <assimp/mesh.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <iostream>
using namespace std;

#include <vector>
#include "native.h"

std::vector<aiVector3D> vec_vertexs;

class LearnAssimp
{
public:
	bool DoTheSceneProcessing(const aiScene* scene) {
		bool has_mesh = scene->HasMeshes();
		if (has_mesh) {
			std::cout << "mesh: " << scene->mNumMeshes << std::endl;
			aiMesh **mesh = scene->mMeshes;
			for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
				aiMesh *currmesh = scene->mMeshes[i];
				aiString mesh_name = currmesh->mName;
				std::cout << "currmesh: " << std::to_string(i) << " " << mesh_name.C_Str() << std::endl;
				std::cout << "    mNumVertices:" << currmesh->mNumVertices << std::endl;

				/*for (unsigned int j = 0; j < currmesh->mNumVertices; ++j) {
					aiVector3D vertex = currmesh->mVertices[j];
					std::cout << " x" << vertex.x << " y" << vertex.y << " z" << vertex.z << std::endl;
				}*/
				/*std::cout << "    mNumFaces:" << currmesh->mNumFaces << std::endl;
				for (unsigned int j = 0; j < currmesh->mNumFaces; ++j) {
					aiFace *currface = currmesh->mFaces;
				}*/
			}
		}
		else {
			std::cout << "this scene not have mesh" << std::endl;
		}
		return true;
	}


	bool DoTheImportThing(const std::string& pFile) {
		// Create an instance of the Importer class
		Assimp::Importer importer;
		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll 
		// propably to request more postprocessing than we do in this example.
		const aiScene* scene = importer.ReadFile(pFile,
												 aiProcess_CalcTangentSpace |
												 aiProcess_Triangulate |
												 aiProcess_JoinIdenticalVertices |
												 aiProcess_SortByPType);

		// If the import failed, report it
		if (!scene) {
			std::cout << "scene is nullptr" << std::endl;
			return false;
		}
		// Now we can access the file's contents. 
		DoTheSceneProcessing(scene);
		// We're done. Everything will be cleaned up by the importer destructor
		return true;
	}
};
