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
		m_box->GetTransform()->SetScale(5.0f, 5.0f, 5.0f);

		auto boxShader = new ColorShader(m_colorShader, m_box);
		auto cubeRenderer = m_box->AddComponent<AN::Renderer>(boxShader);
		cubeRenderer->Input()->SetVertices(m_boxVA->GetId(), m_boxGeometry->GetVertexCount());
		cubeRenderer->Input()->SetIndices(m_boxGeometry->GetIndexBufferId(), m_boxGeometry->GetIndexCount());
		boxShader->m_color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

		/* === Sphere Object === */
		m_sphere = AddObject(new AN::Object("Sphere"));
		m_sphere->GetTransform()->SetPositionX(20.0f);
		m_sphere->GetTransform()->SetScale(5.0f, 5.0f, 5.0f);

		auto sphereShader = new ColorShader(m_colorShader, m_sphere);
		auto sphereRenderer = m_sphere->AddComponent<AN::Renderer>(sphereShader);
		sphereRenderer->Input()->SetVertices(m_sphereVA->GetId(), m_sphereGeometry->GetVertexCount());
		sphereRenderer->Input()->SetIndices(m_sphereGeometry->GetIndexBufferId(), m_sphereGeometry->GetIndexCount());
		sphereShader->m_color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

		/* === Cylinder Object === */
		m_cylinder = AddObject(new AN::Object("Cylinder"));
		m_cylinder->GetTransform()->SetPositionX(-20.0f);
		m_cylinder->GetTransform()->SetScale(5.0f, 5.0f, 5.0f);

		auto cylinderShader = new ColorShader(m_colorShader, m_cylinder);
		auto cylinderRenderer = m_cylinder->AddComponent<AN::Renderer>(cylinderShader);
		cylinderRenderer->Input()->SetVertices(m_cylinderVA->GetId(), m_cylinderGeometry->GetVertexCount());
		cylinderRenderer->Input()->SetIndices(m_cylinderGeometry->GetIndexBufferId(), m_cylinderGeometry->GetIndexCount());
		cylinderShader->m_color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(50.0f);

		auto camera = m_camera->AddComponent<AN::Camera>();
		camera->Raster()->SetCullMode(AN::CullMode::None);
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
		/* Sphere */
		AN_CHECK(m_sphereGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_sphereGeometry->GenerateSphere(1.0f, 16, 8));
		/* Cylinder */
		AN_CHECK(m_cylinderGeometry = GetResources()->CreateGeometry());
		AN_CHECK(m_cylinderGeometry->GenerateCylinder(1.0f, 1.0f, 2.0f, 12, 1));

		/* Box VA */
		AN_CHECK(m_boxVA = m_boxGeometry->GenerateVertexArray(AN::POSITION));
		/* Sphere VA */
		AN_CHECK(m_sphereVA = m_sphereGeometry->GenerateVertexArray(AN::POSITION));
		/* Cylinder VA */
		AN_CHECK(m_cylinderVA = m_cylinderGeometry->GenerateVertexArray(AN::POSITION));

		return true;
	}

}
