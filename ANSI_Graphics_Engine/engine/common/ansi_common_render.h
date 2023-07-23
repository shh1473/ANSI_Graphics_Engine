#pragma once

const unsigned MaximumTextureCount{ 8 };

const unsigned CameraTypeCount{ 2 };
enum class CameraType
{
	Camera,
	Light,
};

const unsigned RenderTypeCount{ 4 };
enum class RenderType
{
	Packing,
	Deferred,
	Forward,
	Compute,
};
