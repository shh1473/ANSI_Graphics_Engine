#include "point_shadows_scene.h"

#include "material/point_shadows_3/point_shadows_3_material.h"

namespace Example
{

	const std::string PointShadowsScene::m_SceneName{ "Three Point Shadows" };

	PointShadowsScene::PointShadowsScene() :
		m_isAnimateRotation(false),
		m_lightRadius(300.0f),
		m_lightRotation(0.0f)
	{

	}

	bool PointShadowsScene::Initialize()
	{
		/* === Point Light Objects === */
		AN::PointLight * pointLights[3]{ nullptr, };

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			m_pointLights[i] = AddObject(new AN::Object(std::string("Point Light ") + std::to_string(i + 1)));
			m_pointLights[i]->GetTransform()->SetRotationX(45.0f * (i + 1));
			m_pointLights[i]->GetTransform()->SetScale(10.0f, 10.0f, 10.0f);

			pointLights[i] = m_pointLights[i]->AddComponent<AN::PointLight>(m_lightRadius);
			AN_CHECK(pointLights[i]->CastShadow());
		}

		// Create Renderers after creating Lights
		for (unsigned i{ 0 }; i < 3; ++i)
		{
			auto pointLightMaterial = new PointShadows3Material(m_pointShadows3Shader, pointLights);
			pointLightMaterial->SetCullMode(AN::CullMode::None);
			m_pointLights[i]->AddComponent<AN::Renderer>(m_shadowCastSphereVA, pointLightMaterial);
		}

		pointLights[0]->SetColor(glm::vec3(1.0f, 0.4f, 0.4f));
		pointLights[1]->SetColor(glm::vec3(0.4f, 1.0f, 0.4f));
		pointLights[2]->SetColor(glm::vec3(0.4f, 0.4f, 1.0f));
		UpdateLightRotation();

		/* === RG Rat Object === */
		m_rgrat = AddObject(new AN::Object("RG Rat"));

		auto rgratMaterial = new PointShadows3Material(m_pointShadows3Shader, pointLights);
		auto rgratRenderer = m_rgrat->AddComponent<AN::Renderer>(m_rgratVA, rgratMaterial);

		/* === Box Object === */
		m_box = AddObject(new AN::Object("Box"));
		m_box->SetIsCastShadow(false);
		m_box->GetTransform()->SetScale(200.0f, 200.0f, 200.0f);

		auto boxMaterial = new PointShadows3Material(m_pointShadows3Shader, pointLights);
		auto boxRenderer = m_box->AddComponent<AN::Renderer>(m_boxVA, boxMaterial);

		/* === Camera Object === */
		m_camera = AddObject(new AN::Object("Camera"));
		m_camera->GetTransform()->SetPositionZ(200.0f);

		auto camera = m_camera->AddComponent<AN::Camera>();
		m_orbitControls = new AN::OrbitControls(camera);
		camera->SetOrbitControls(m_orbitControls);

		return true;
	}

	bool PointShadowsScene::OnUpdate()
	{
		if (m_isAnimateRotation)
		{
			m_lightRotation += 20.0f * AN::Core::GetTimer()->GetDeltaTime();
			UpdateLightRotation();
		}

		return true;
	}

	bool PointShadowsScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		if (ImGui::DragFloat("Light Radius", &m_lightRadius, 1.0f, 0.0f, 300.0f))
		{
			for (unsigned i{ 0 }; i < 3; ++i) { m_pointLights[i]->FindComponent<AN::PointLight>()->SetRadius(m_lightRadius); }
		}

		if (!m_isAnimateRotation)
		{
			if (ImGui::DragFloat("Light Rotation", &m_lightRotation, 1.0f, -720.0f, 720.0f))
			{
				UpdateLightRotation();
			}
		}

		if (ImGui::Checkbox("Animate Rotation", &m_isAnimateRotation))
		{
			if (!m_isAnimateRotation)
			{
				while (m_lightRotation > 360.0f) { m_lightRotation -= 360.0f; }
			}
		}

		if (ImGui::Button("Reset camera"))
		{
			m_orbitControls->Reset();
		}

		return ExampleScene::OnRenderGui();
	}

	bool PointShadowsScene::CreateResources()
	{
		/* === Shader === */
		/* Point Lights 3 */
		AN_CHECK(m_pointShadows3Shader = GetResources()->CreateShader("assets/shader/point_shadows_3.shader", AN::RenderType::Forward));

		/* === Geometry === */
		/* RG Rat */
		auto rgratGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(rgratGeometry->GenerateFromObj("assets/model/ptn_rgrat.obj"));
		/* Shadow Cast Sphere */
		auto shadowCastSphereGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(shadowCastSphereGeometry->GenerateFromObj("assets/model/shadow_cast_sphere.obj"));
		/* Box */
		auto boxGeometry{ GetResources()->CreateGeometry() };
		AN_CHECK(boxGeometry->GenerateFromObj("assets/model/box_flipped_normal.obj"));

		/* RG Rat VA */
		AN_CHECK(m_rgratVA = rgratGeometry->GenerateVertexArray(AN::NORMAL));
		/* Shadow Cast Sphere VA */
		AN_CHECK(m_shadowCastSphereVA = shadowCastSphereGeometry->GenerateVertexArray(AN::NORMAL));
		/* Box VA */
		AN_CHECK(m_boxVA = boxGeometry->GenerateVertexArray(AN::NORMAL));

		return true;
	}

	void PointShadowsScene::UpdateLightRotation()
	{
		float cos{ 0.0f }, sin{ 0.0f };

		for (unsigned i{ 0 }; i < 3; ++i)
		{
			cos = std::cos(glm::radians(m_lightRotation * (i + 1)));
			sin = std::sin(glm::radians(m_lightRotation * (i + 1)));

			m_pointLights[i]->GetTransform()->SetPosition(cos * 50.0f, (50.0f * i) - 50.0f, sin * 50.0f);
			m_pointLights[i]->GetTransform()->SetRotationZ(m_lightRotation * (i + 1));
		}
	}

}
