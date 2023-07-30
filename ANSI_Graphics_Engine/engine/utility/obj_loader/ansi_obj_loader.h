#pragma once

#include "common/ansi_common.h"

#include "tinyobjloader/tiny_obj_loader.h"

namespace AN
{

	class ObjLoader
	{
	public:
		static bool Load(const std::string & filePath, unsigned & vertexBufferId, unsigned & vertexCount, unsigned & stride, unsigned & flag);

	private:
		explicit ObjLoader() = delete;

		static bool CreateVertexBuffer(const std::vector<float> & rawVerticesData, unsigned & vertexBufferId);
		static bool ParseObj(const std::string & filePath,
			std::vector<glm::vec3> & loadedPositions,
			std::vector<glm::vec2> & loadedTexCoords,
			std::vector<glm::vec3> & loadedNormals,
			std::vector<glm::uvec3> & loadedIndices);
		static void AssembleVertices(
			const std::vector<float> & loadedPositions,
			const std::vector<float> & loadedTexCoords,
			const std::vector<float> & loadedNormals,
			const std::vector<tinyobj::index_t> & loadedIndices,
			std::vector<float> & rawVerticesData);

	};

}
