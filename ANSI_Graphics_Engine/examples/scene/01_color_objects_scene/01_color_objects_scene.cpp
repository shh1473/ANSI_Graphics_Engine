#include "01_color_objects_scene.h"

#include "../examples/shader/color/color_shader.h"

namespace Example
{

	ColorObjectsScene::ColorObjectsScene() :
		m_isWireframe(false)
	{

	}

	ColorObjectsScene::~ColorObjectsScene()
	{
		AN_DELETE(m_orbitControls);
	}

	bool ColorObjectsScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle("01 - Color Objects");

		/* === Box Object === */
		m_box = AddObject(new AN::Object("Box"));
		m_box->GetTransform()->SetScale(10.0f, 10.0f, 10.0f);
		AN::Renderer * cubeRenderer = m_box->AddComponent<AN::Renderer>(m_boxColorShader = new ColorShader(m_colorShader, m_box));
		cubeRenderer->Input()->SetVertices(m_boxVA->GetId(), m_boxGeometry->GetVertexCount());
		cubeRenderer->Input()->SetIndices(m_boxGeometry->GetIndexBufferId(), m_boxGeometry->GetIndexCount());
		m_boxColorShader->m_color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

		/* === Sphere Object === */
		m_sphere = AddObject(new AN::Object("Sphere"));
		m_sphere->GetTransform()->SetPositionX(30.0f);
		m_sphere->GetTransform()->SetScale(10.0f, 10.0f, 10.0f);
		AN::Renderer * sphereRenderer = m_sphere->AddComponent<AN::Renderer>(m_sphereColorShader = new ColorShader(m_colorShader, m_sphere));
		sphereRenderer->Input()->SetVertices(m_sphereVA->GetId(), m_sphereGeometry->GetVertexCount());
		sphereRenderer->Input()->SetIndices(m_sphereGeometry->GetIndexBufferId(), m_sphereGeometry->GetIndexCount());
		m_sphereColorShader->m_color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

		/* === Cylinder Object === */
		m_cylinder = AddObject(new AN::Object("Cylinder"));
		m_cylinder->GetTransform()->SetPositionX(-30.0f);
		m_cylinder->GetTransform()->SetScale(10.0f, 10.0f, 10.0f);
		AN::Renderer * cylinderRenderer = m_cylinder->AddComponent<AN::Renderer>(m_cylinderColorShader = new ColorShader(m_colorShader, m_cylinder));
		cylinderRenderer->Input()->SetVertices(m_cylinderVA->GetId(), m_cylinderGeometry->GetVertexCount());
		cylinderRenderer->Input()->SetIndices(m_cylinderGeometry->GetIndexBufferId(), m_cylinderGeometry->GetIndexCount());
		m_cylinderColorShader->m_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		AN::Camera * camera = m_camera->AddComponent<AN::Camera>();
		m_camera->GetTransform()->SetPositionZ(50.0f);
		m_orbitControls = new AN::OrbitControls(camera);

		return true;
	}

	bool ColorObjectsScene::OnUpdate()
	{
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
		/* === Shaders === */
		/* Color */
		AN_CHECK(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader", RenderType::Forward));

		/* === Geometries === */
		/* Box */
		AN_CHECK(m_boxGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_boxGeometry->GenerateBox(2.0f, 2.0f, 2.0f, 1, 1, 1));
		AN_CHECK(m_boxVA = m_boxGeometry->GenerateVertexArray(AN::POSITION));
		/* Sphere */
		AN_CHECK(m_sphereGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_sphereGeometry->GenerateSphere(1.0f, 16, 8));
		AN_CHECK(m_sphereVA = m_sphereGeometry->GenerateVertexArray(AN::POSITION));
		/* Cylinder */
		AN_CHECK(m_cylinderGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_cylinderGeometry->GenerateCylinder(1.0f, 1.0f, 2.0f, 12, 1));
		AN_CHECK(m_cylinderVA = m_cylinderGeometry->GenerateVertexArray(AN::POSITION));

		return true;
	}

}
