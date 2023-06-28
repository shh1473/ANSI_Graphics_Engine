#pragma once

#include "common/ansi_common.h"

namespace AN
{

	struct VertexData
	{
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
	};

	struct VertexDataExtended
	{
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 binormal;
	};

	class ObjLoader
	{
	public:
		static bool LoadObj(const std::string & filePath, bool isIncludeTB, unsigned & vertexBufferId, unsigned & vertexCount);

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
			std::vector<VertexData> & assembledVertices);
		static void AssembleVerticesExtended(
			const std::vector<glm::vec3> & loadedPositions,
			const std::vector<glm::vec2> & loadedTexCoords,
			const std::vector<glm::vec3> & loadedNormals,
			const std::vector<glm::uvec3> & loadedIndices,
			std::vector<VertexDataExtended> & assembledVertices);
		static void PackVertices(const std::vector<VertexData> & verticesData, std::vector<float> & rawVerticesData);
		static void PackVerticesExtended(const std::vector<VertexDataExtended> & verticesData, std::vector<float> & rawVerticesData);
		static void CalculateTangentBinormal(std::vector<VertexDataExtended> & assembledVertices);

	};

}
