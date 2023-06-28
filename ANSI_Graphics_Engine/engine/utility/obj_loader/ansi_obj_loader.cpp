#include "ansi_obj_loader.h"

#include "core/log/ansi_log.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	bool ObjLoader::LoadObj(const std::string & filePath, bool isIncludeTB, unsigned & vertexBufferId, unsigned & vertexCount)
	{
		std::vector<float> rawVerticesData;

		std::vector<glm::vec3> loadedPositions;
		std::vector<glm::vec2> loadedTexCoords;
		std::vector<glm::vec3> loadedNormals;
		std::vector<glm::uvec3> loadedIndices;

		AN_CHECK(ParseObj(filePath, loadedPositions, loadedTexCoords, loadedNormals, loadedIndices));
		vertexCount = static_cast<unsigned>(loadedIndices.size());

		if (isIncludeTB)
		{
			std::vector<VertexDataExtended> verticesData;
			AssembleVerticesExtended(loadedPositions, loadedTexCoords, loadedNormals, loadedIndices, verticesData);
			CalculateTangentBinormal(verticesData);
			PackVerticesExtended(verticesData, rawVerticesData);
		}
		else
		{
			std::vector<VertexData> verticesData;
			AssembleVertices(loadedPositions, loadedTexCoords, loadedNormals, loadedIndices, verticesData);
			PackVertices(verticesData, rawVerticesData);
		}

		AN_CHECK(CreateVertexBuffer(rawVerticesData, vertexBufferId));

		return true;
	}

	bool ObjLoader::CreateVertexBuffer(const std::vector<float> & rawVerticesData, unsigned & vertexBufferId)
	{
		GL_CHECK(glGenBuffers(1, &vertexBufferId));
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), &rawVerticesData[0], GL_STATIC_DRAW));

		return true;
	}

	bool ObjLoader::ParseObj(
		const std::string & filePath,
		std::vector<glm::vec3> & loadedPositions,
		std::vector<glm::vec2> & loadedTexCoords,
		std::vector<glm::vec3> & loadedNormals,
		std::vector<glm::uvec3> & loadedIndices)
	{
		std::ifstream file;

		file.open(filePath);
		AN_CHECK_LOG(file.is_open());

		char ch{ 0 };
		glm::vec3 tmpPosition(0.0f);
		glm::vec2 tmpTexCoord(0.0f);
		glm::vec3 tmpNormal(0.0f);
		glm::uvec3 tmpIndices(0);

		while (!file.eof())
		{
			file.get(ch);
			switch (ch)
			{
				case 'v':
				{
					file.get(ch);
					switch (ch)
					{
						case ' ':
						{
							file >> tmpPosition.x >> tmpPosition.y >> tmpPosition.z;
							loadedPositions.push_back(tmpPosition);
						} break;
						case 't':
						{
							file >> tmpTexCoord.x >> tmpTexCoord.y;
							loadedTexCoords.push_back(tmpTexCoord);
						} break;
						case 'n':
						{
							file >> tmpNormal.x >> tmpNormal.y >> tmpNormal.z;
							loadedNormals.push_back(tmpNormal);
						}
					}
				} break;
				case 'f':
				{
					file.get(ch);
					if (ch == ' ')
					{
						for (unsigned i{ 0 }; i < 3; ++i)
						{
							file >> tmpIndices.x >> ch >> tmpIndices.y >> ch >> tmpIndices.z;
							tmpIndices -= 1;
							loadedIndices.push_back(tmpIndices);
						}
					}
				}
			}
		}

		return true;
	}

	void ObjLoader::AssembleVertices(
		const std::vector<glm::vec3> & loadedPositions,
		const std::vector<glm::vec2> & loadedTexCoords,
		const std::vector<glm::vec3> & loadedNormals,
		const std::vector<glm::uvec3> & loadedIndices,
		std::vector<VertexData> & assembledVertices)
	{
		for (unsigned i{ 0 }; i < loadedIndices.size(); ++i)
		{
			assembledVertices.push_back({
				loadedPositions[loadedIndices[i].x],
				loadedTexCoords[loadedIndices[i].y],
				loadedNormals[loadedIndices[i].z] });
		}
	}

	void ObjLoader::AssembleVerticesExtended(
		const std::vector<glm::vec3> & loadedPositions,
		const std::vector<glm::vec2> & loadedTexCoords,
		const std::vector<glm::vec3> & loadedNormals,
		const std::vector<glm::uvec3> & loadedIndices,
		std::vector<VertexDataExtended> & assembledVertices)
	{
		for (unsigned i{ 0 }; i < loadedIndices.size(); ++i)
		{
			assembledVertices.push_back({
				loadedPositions[loadedIndices[i].x],
				loadedTexCoords[loadedIndices[i].y],
				loadedNormals[loadedIndices[i].z],
				glm::vec3(0.0f), glm::vec3(0.0f) });
		}
	}

	void ObjLoader::PackVertices(const std::vector<VertexData> & verticesData, std::vector<float> & rawVerticesData)
	{
		for (unsigned i{ 0 }; i < verticesData.size(); ++i)
		{
			rawVerticesData.push_back(verticesData[i].position.x);
			rawVerticesData.push_back(verticesData[i].position.y);
			rawVerticesData.push_back(verticesData[i].position.z);
			rawVerticesData.push_back(verticesData[i].texCoord.x);
			rawVerticesData.push_back(verticesData[i].texCoord.y);
			rawVerticesData.push_back(verticesData[i].normal.x);
			rawVerticesData.push_back(verticesData[i].normal.y);
			rawVerticesData.push_back(verticesData[i].normal.z);
		}
	}

	void ObjLoader::PackVerticesExtended(const std::vector<VertexDataExtended> & verticesData, std::vector<float> & rawVerticesData)
	{
		for (unsigned i{ 0 }; i < verticesData.size(); ++i)
		{
			rawVerticesData.push_back(verticesData[i].position.x);
			rawVerticesData.push_back(verticesData[i].position.y);
			rawVerticesData.push_back(verticesData[i].position.z);
			rawVerticesData.push_back(verticesData[i].texCoord.x);
			rawVerticesData.push_back(verticesData[i].texCoord.y);
			rawVerticesData.push_back(verticesData[i].normal.x);
			rawVerticesData.push_back(verticesData[i].normal.y);
			rawVerticesData.push_back(verticesData[i].normal.z);
			rawVerticesData.push_back(verticesData[i].tangent.x);
			rawVerticesData.push_back(verticesData[i].tangent.y);
			rawVerticesData.push_back(verticesData[i].tangent.z);
			rawVerticesData.push_back(verticesData[i].binormal.x);
			rawVerticesData.push_back(verticesData[i].binormal.y);
			rawVerticesData.push_back(verticesData[i].binormal.z);
		}
	}

	void ObjLoader::CalculateTangentBinormal(std::vector<VertexDataExtended> & assembledVertices)
	{
		unsigned index{ 0 }, v1{ 0 }, v2{ 0 }, v3{ 0 };
		float denominator{ 0.0f };
		glm::vec3 tangent(0.0f), binormal(0.0f);
		glm::vec3 deltaPosition1(0.0f), deltaPosition2(0.0f);
		glm::vec2 deltaTexCoord1(0.0f), deltaTexCoord2(0.0f);

		for (unsigned i{ 0 }; i < assembledVertices.size() / 3; ++i)
		{
			v1 = index++;
			v2 = index++;
			v3 = index++;

			deltaPosition1 = assembledVertices[v2].position - assembledVertices[v1].position;
			deltaPosition2 = assembledVertices[v3].position - assembledVertices[v1].position;
			deltaTexCoord1 = assembledVertices[v2].texCoord - assembledVertices[v1].texCoord;
			deltaTexCoord2 = assembledVertices[v3].texCoord - assembledVertices[v1].texCoord;

			denominator = deltaTexCoord1.x * deltaTexCoord2.y - deltaTexCoord1.y * deltaTexCoord2.x;
			denominator = (denominator) ? 1.0f / denominator : 0.0f;

			tangent = (deltaPosition1 * deltaTexCoord2.y - deltaPosition2 * deltaTexCoord1.y) * denominator;
			binormal = (deltaPosition2 * deltaTexCoord1.x - deltaPosition1 * deltaTexCoord2.x) * denominator;

			tangent = glm::normalize(tangent);
			binormal = glm::normalize(binormal);

			assembledVertices[v1].tangent = tangent;
			assembledVertices[v2].tangent = tangent;
			assembledVertices[v3].tangent = tangent;
			assembledVertices[v1].binormal = binormal;
			assembledVertices[v2].binormal = binormal;
			assembledVertices[v3].binormal = binormal;
		}
	}

}
