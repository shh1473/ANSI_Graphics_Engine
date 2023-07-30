#include "color_scene.h"

#include "material/color/color_material.h"

namespace Example
{

	const std::string ColorScene::m_SceneName{ "01 - Colors" };

	ColorScene::ColorScene() :
		m_isWireframe(false)
	{

	}

	bool ColorScene::Initialize()
	{
		/* === Gui === */
		AN::Core::GetGui()->SetTitle(m_SceneName);

		/* === Box Object === */
		m_box = AddObject(new AN::Object("Box"));
		m_box->GetTransform()->SetScale(5.0f, 5.0f, 5.0f);

		auto boxMaterial = new ColorMaterial(m_colorShader);
		boxMaterial->SetDiffuseColor(glm::vec3(0.0f, 1.0f, 0.0f));
		auto boxRenderer = m_box->AddComponent<AN::Renderer>(boxMaterial);
		boxRenderer->GetInput()->SetGeometry(m_boxVA);

		/* === Sphere Object === */
		m_sphere = AddObject(new AN::Object("Sphere"));
		m_sphere->GetTransform()->SetPositionX(20.0f);
		m_sphere->GetTransform()->SetScale(5.0f, 5.0f, 5.0f);

		auto sphereMaterial = new ColorMaterial(m_colorShader);
		sphereMaterial->SetDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));
		auto sphereRenderer = m_sphere->AddComponent<AN::Renderer>(sphereMaterial);
		sphereRenderer->GetInput()->SetGeometry(m_sphereVA);

		/* === Cylinder Object === */
		m_cylinder = AddObject(new AN::Object("Cylinder"));
		m_cylinder->GetTransform()->SetPositionX(-20.0f);
		m_cylinder->GetTransform()->SetScale(5.0f, 5.0f, 5.0f);

		auto cylinderMaterial = new ColorMaterial(m_colorShader);
		cylinderMaterial->SetDiffuseColor(glm::vec3(1.0f, 0.0f, 0.0f));
		auto cylinderRenderer = m_cylinder->AddComponent<AN::Renderer>(cylinderMaterial);
		cylinderRenderer->GetInput()->SetGeometry(m_cylinderVA);

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(50.0f);

		auto camera = m_camera->AddComponent<AN::Camera>();
		m_orbitControls = new AN::OrbitControls(camera);
		camera->SetOrbitControls(m_orbitControls);

		return true;
	}

	bool ColorScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		if (ImGui::Checkbox("Wireframe", &m_isWireframe))
		{
			static auto boxMaterial{ static_cast<ColorMaterial *>(m_box->FindComponent<AN::Renderer>()->GetMaterial()) };
			static auto sphereMaterial{ static_cast<ColorMaterial *>(m_sphere->FindComponent<AN::Renderer>()->GetMaterial()) };
			static auto cylinderMaterial{ static_cast<ColorMaterial *>(m_cylinder->FindComponent<AN::Renderer>()->GetMaterial()) };

			boxMaterial->SetFillMode((m_isWireframe) ? AN::FillMode::Wireframe : AN::FillMode::Solid);
			boxMaterial->SetCullMode((m_isWireframe) ? AN::CullMode::None : AN::CullMode::Back);
			sphereMaterial->SetFillMode((m_isWireframe) ? AN::FillMode::Wireframe : AN::FillMode::Solid);
			sphereMaterial->SetCullMode((m_isWireframe) ? AN::CullMode::None : AN::CullMode::Back);
			cylinderMaterial->SetFillMode((m_isWireframe) ? AN::FillMode::Wireframe : AN::FillMode::Solid);
			cylinderMaterial->SetCullMode((m_isWireframe) ? AN::CullMode::None : AN::CullMode::Back);
		}

		if (ImGui::Button("Reset camera")) { m_orbitControls->Reset(); }

		return ExampleScene::OnRenderGui();
	}

	bool ColorScene::CreateResources()
	{
		/* === Shader === */
		/* Color */
		AN_CHECK(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader", AN::RenderType::Forward));

		/* === Geometry === */
		/* Box */
		auto boxGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(boxGeometry->GenerateBox(2.0f, 2.0f, 2.0f, 1, 1, 1));
		/* Sphere */
		auto sphereGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(sphereGeometry->GenerateSphere(1.0f, 16, 8));
		/* Cylinder */
		auto cylinderGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(cylinderGeometry->GenerateCylinder(1.0f, 1.0f, 2.0f, 12, 1));

		/* Box VA */
		AN_CHECK(m_boxVA = boxGeometry->GenerateVertexArray(0));
		/* Sphere VA */
		AN_CHECK(m_sphereVA = sphereGeometry->GenerateVertexArray(0));
		/* Cylinder VA */
		AN_CHECK(m_cylinderVA = cylinderGeometry->GenerateVertexArray(0));

		return true;
	}

}
