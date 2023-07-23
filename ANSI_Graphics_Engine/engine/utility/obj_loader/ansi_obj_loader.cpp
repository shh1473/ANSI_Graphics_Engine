#include "ansi_obj_loader.h"

#include "core/log/ansi_log.h"
#include "utility/converter/ansi_converter.h"

namespace AN
{

	bool ObjLoader::Load(const std::string & filePath, unsigned & vertexBufferId, unsigned & vertexCount, unsigned & stride)
	{
		std::vector<float> rawVerticesData;

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string error;
		std::string warning;

		bool result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, filePath.c_str());

		if (!error.empty()) { AN_ERROR_LOG(Converter::ToUnicode(error)); }
		if (!warning.empty()) { AN_ERROR_LOG(Converter::ToUnicode(warning)); }
		AN_CHECK_LOG(result);

		stride = 3 * sizeof(float);
		if (attrib.texcoords.size() > 0) { stride += 2 * sizeof(float); }
		if (attrib.normals.size() > 0) { stride += 3 * sizeof(float); }

		vertexCount = static_cast<unsigned>(shapes[0].mesh.indices.size());
		rawVerticesData.reserve(vertexCount * stride / sizeof(float));

		AssembleVertices(attrib.vertices, attrib.texcoords, attrib.normals, shapes[0].mesh.indices, rawVerticesData);

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
							file >> tmpIndices.x;
							file.get(ch);
							file >> tmpIndices.y;
							file.get(ch);
							file >> tmpIndices.z;

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
		const std::vector<float> & loadedPositions,
		const std::vector<float> & loadedTexCoords,
		const std::vector<float> & loadedNormals,
		const std::vector<tinyobj::index_t> & loadedIndices,
		std::vector<float> & rawVerticesData)
	{
		int index{ 0 };

		for (unsigned i{ 0 }; i < loadedIndices.size(); ++i)
		{
			index = loadedIndices[i].vertex_index * 3;
			if (index >= 0)
			{
				rawVerticesData.push_back(loadedPositions[index]);
				rawVerticesData.push_back(loadedPositions[index + 1]);
				rawVerticesData.push_back(loadedPositions[index + 2]);
			}

			index = loadedIndices[i].texcoord_index * 2;
			if (index >= 0)
			{
				rawVerticesData.push_back(loadedTexCoords[index]);
				rawVerticesData.push_back(loadedTexCoords[index + 1]);
			}

			index = loadedIndices[i].normal_index * 3;
			if (index >= 0)
			{
				rawVerticesData.push_back(loadedNormals[index]);
				rawVerticesData.push_back(loadedNormals[index + 1]);
				rawVerticesData.push_back(loadedNormals[index + 2]);
			}
		}
	}

}
