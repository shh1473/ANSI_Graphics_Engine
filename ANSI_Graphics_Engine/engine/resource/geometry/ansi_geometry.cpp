#include "ansi_geometry.h"

#include "core/log/ansi_log.h"
#include "resource/vertex_array/ansi_vertex_array.h"
#include "utility/geometry_generator/plane/ansi_plane_geometry_generator.h"
#include "utility/geometry_generator/box/ansi_box_geometry_generator.h"
#include "utility/geometry_generator/sphere/ansi_sphere_geometry_generator.h"
#include "utility/geometry_generator/cylinder/ansi_cylinder_geometry_generator.h"
#include "utility/obj_loader/ansi_obj_loader.h"

namespace AN
{

	Geometry::Geometry() :
		m_vertexCount(0),
		m_indexCount(0),
		m_vertexBufferId(0),
		m_indexBufferId(0),
		m_vertexArrays()
	{

	}

	Geometry::~Geometry()
	{
		if (m_vertexBufferId) {
			GL_ERROR_LOG(glBindBuffer(GL_ARRAY_BUFFER, 0));
			GL_ERROR_LOG(glDeleteBuffers(1, &m_vertexBufferId));
		}
		if (m_indexBufferId) {
			GL_ERROR_LOG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
			GL_ERROR_LOG(glDeleteBuffers(1, &m_indexBufferId));
		}
		for (auto & vertexArray : m_vertexArrays) {
			AN_DELETE(vertexArray);
		}
	}

	VertexArray * Geometry::GenerateVertexArray(unsigned flag)
	{
		AN_CHECK_NULL(m_vertexCount != 0);

		unsigned id{ 0 };
		GL_CHECK_NULL(glGenVertexArrays(1, &id));
		GL_CHECK_NULL(glBindVertexArray(id));
		GL_CHECK_NULL(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));

		std::vector<unsigned> elementCounts;
		std::vector<unsigned *> offsets;

		if (flag & POSITION) {
			elementCounts.push_back(3);
			offsets.push_back(0);
		}
		if (flag & TEXCOORD) {
			elementCounts.push_back(2);
			offsets.push_back(reinterpret_cast<unsigned *>(3 * sizeof(float)));
		}
		if (flag & NORMAL) {
			elementCounts.push_back(3);
			offsets.push_back(reinterpret_cast<unsigned *>(5 * sizeof(float)));
		}

		for (unsigned i{ 0 }; i < elementCounts.size(); ++i)
		{
			GL_CHECK_NULL(glEnableVertexAttribArray(i));
			GL_CHECK_NULL(glVertexAttribPointer(i, elementCounts[i], GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<const void *>(offsets[i])));
		}

		m_vertexArrays.push_back(new VertexArray(id));
		return m_vertexArrays.back();
	}

	void Geometry::RemoveVertexArray(VertexArray * vertexArray)
	{
		m_vertexArrays.erase(std::find(m_vertexArrays.begin(), m_vertexArrays.end(), vertexArray));
		AN_DELETE(vertexArray);
	}

	bool Geometry::GeneratePlane(float width, float height, unsigned widthSegments, unsigned heightSegments)
	{
		AN_CHECK_LOG(m_vertexCount == 0);
		return PlaneGeometryGenerator::Generate(
			width, height, widthSegments, heightSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	bool Geometry::GenerateBox(float width, float height, float depth, unsigned widthSegments, unsigned heightSegments, unsigned depthSegments)
	{
		AN_CHECK_LOG(m_vertexCount == 0);
		return BoxGeometryGenerator::Generate(
			width, height, depth, widthSegments, heightSegments, depthSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	bool Geometry::GenerateSphere(float radius, unsigned widthSegments, unsigned heightSegments)
	{
		AN_CHECK_LOG(m_vertexCount == 0);
		return SphereGeometryGenerator::Generate(radius, widthSegments, heightSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	bool Geometry::GenerateCylinder(float topRadius, float bottomRadius, float height, unsigned radialSegments, unsigned heightSegments)
	{
		AN_CHECK_LOG(m_vertexCount == 0);
		return CylinderGeometryGenerator::Generate(topRadius, bottomRadius, height, radialSegments, heightSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	bool Geometry::GenerateFromObj(const std::string & filePath)
	{
		AN_CHECK_LOG(m_vertexCount == 0);
		return ObjLoader::Load(filePath, m_vertexBufferId, m_vertexCount);
	}

}
