#include "01_color_objects_scene.h"

#include "../examples/shader/color/color_shader.h"

namespace Example
{

	ColorObjectsScene::ColorObjectsScene() :
		m_colorAddDir(
			AN::Random::Int(0, 1) ? 1.0f : -1.0f,
			AN::Random::Int(0, 1) ? 1.0f : -1.0f,
			AN::Random::Int(0, 1) ? 1.0f : -1.0f),
		m_isWireframe(false)
	{

	}

	ColorObjectsScene::~ColorObjectsScene()
	{
		AN_DELETE(m_orbitControls);
	}

	bool ColorObjectsScene::Initialize()
	{
		AN::Core::GetGui()->SetTitle("01 - Color Objects");

		m_box = AddObject(new AN::Object("Box"));
		m_box->GetTransform()->SetScale(10.0f, 10.0f, 10.0f);
		AN::Renderer * cubeRenderer = m_box->AddComponent<AN::Renderer>(m_boxColorShader = new ColorShader(m_colorShader, m_box));
		cubeRenderer->Input()->SetVertices(m_boxVA->GetId(), m_boxGeometry->GetVertexCount());
		cubeRenderer->Input()->SetIndices(m_boxGeometry->GetIndexBufferId(), m_boxGeometry->GetIndexCount());
		m_boxColorShader->m_color = glm::vec4(
			AN::Random::Float(0.0f, 1.0f),
			AN::Random::Float(0.0f, 1.0f),
			AN::Random::Float(0.0f, 1.0f), 1.0f);

		m_camera = AddObject(new AN::Object("Camera"));
		AN::Camera * camera = m_camera->AddComponent<AN::Camera>();
		m_camera->GetTransform()->SetPositionZ(50.0f);
		m_orbitControls = new AN::OrbitControls(camera);

		return true;
	}

	bool ColorObjectsScene::OnUpdate()
	{
		for (unsigned i{ 0 }; i < 3; ++i)
		{
			if (m_boxColorShader->m_color[i] < 0.0f) { m_boxColorShader->m_color[i] = 0.0f; m_colorAddDir[i] = 1.0f; }
			if (m_boxColorShader->m_color[i] > 1.0f) { m_boxColorShader->m_color[i] = 1.0f; m_colorAddDir[i] = -1.0f; }
			m_boxColorShader->m_color[i] += AN::Random::Float(0.0f, 2.0f) * m_colorAddDir[i] * AN_DT;
		}

		return true;
	}

	bool ColorObjectsScene::OnRenderGui()
	{
		if (ImGui::Checkbox("Wireframe", &m_isWireframe))
		{
			m_camera->FindComponent<AN::Camera>()->Raster()->SetFillMode((m_isWireframe) ? AN::FillMode::Line : AN::FillMode::Fill);
		}

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		return true;
	}

	bool ColorObjectsScene::CreateResources()
	{
		/* Shaders */
		AN_CHECK(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader", RenderType::Forward));

		/* Geometry */
		AN_CHECK(m_boxGeometry = GetResources()->CreateGeometry());
		//AN_CHECK(m_boxGeometry->GenerateBox(2.0f, 2.0f, 2.0f, 2, 2, 2, false));
		AN_CHECK(m_boxGeometry->GenerateCylinder(false, 1.0f, 2.0f, 3.0f, 0.0f, PI2, 10, 1, false));
		AN_CHECK(m_boxVA = m_boxGeometry->GenerateVertexArray());

		return true;
	}

}
