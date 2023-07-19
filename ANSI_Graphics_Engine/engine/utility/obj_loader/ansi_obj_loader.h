#pragma once

#include "common/ansi_common.h"

namespace AN
{

	class ObjLoader
	{
	public:
		static bool Load(const std::string & filePath, unsigned & vertexBufferId, unsigned & vertexCount);

	private:
		explicit ObjLoader() = delete;

		static bool CreateVertexBuffer(const std::vector<float> & rawVerticesData, unsigned & vertexBufferId);
		static bool ParseObj(const std::string & filePath,
			std::vector<glm::vec3> & loadedPositions,
			std::vector<glm::vec2> & loadedTexCoords,
			std::vector<glm::vec3> & loadedNormals,
			std::vector<glm::uvec3> & loadedIndices);
		static void AssembleVertices(
			const std::vector<glm::vec3> & loadedPositions,
			const std::vector<glm::vec2> & loadedTexCoords,
			const std::vector<glm::vec3> & loadedNormals,
			const std::vector<glm::uvec3> & loadedIndices,
			std::vector<float> & rawVerticesData);

	};

}
