#include "ansi_obj_loader.h"

#include "core/log/ansi_log.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	bool ObjLoader::LoadObj(const std::string & filePath, unsigned & vertexBufferId, unsigned & vertexCount)
	{
		std::vector<float> rawVerticesData;

		std::vector<glm::vec3> loadedPositions;
		std::vector<glm::vec2> loadedTexCoords;
		std::vector<glm::vec3> loadedNormals;
		std::vector<glm::uvec3> loadedIndices;

		AN_CHECK(ParseObj(filePath, loadedPositions, loadedTexCoords, loadedNormals, loadedIndices));
		AssembleVertices(loadedPositions, loadedTexCoords, loadedNormals, loadedIndices, rawVerticesData);
		vertexCount = static_cast<unsigned>(loadedIndices.size());

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
				} break;
			}
		}

		return true;
	}

	void ObjLoader::AssembleVertices(
		const std::vector<glm::vec3> & loadedPositions,
		const std::vector<glm::vec2> & loadedTexCoords,
		const std::vector<glm::vec3> & loadedNormals,
		const std::vector<glm::uvec3> & loadedIndices,
		std::vector<float> & rawVerticesData)
	{
		for (unsigned i{ 0 }; i < loadedIndices.size(); ++i)
		{
			rawVerticesData.push_back(loadedPositions[loadedIndices[i].x].x);
			rawVerticesData.push_back(loadedPositions[loadedIndices[i].x].y);
			rawVerticesData.push_back(loadedPositions[loadedIndices[i].x].z);

			rawVerticesData.push_back(loadedTexCoords[loadedIndices[i].y].x);
			rawVerticesData.push_back(loadedTexCoords[loadedIndices[i].y].y);

			rawVerticesData.push_back(loadedNormals[loadedIndices[i].z].x);
			rawVerticesData.push_back(loadedNormals[loadedIndices[i].z].y);
			rawVerticesData.push_back(loadedNormals[loadedIndices[i].z].z);
		}
	}

}
