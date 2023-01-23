#pragma once
#ifndef __UTIL__
#define __UTIL__

#include "GLM/vec2.hpp"
#include "GLM/vec4.hpp"
#include "ShapeType.h"
#include <SDL.h>

#include "GameObject.h"
#include "Renderer.h"

class Util
{
public:
	static const float EPSILON;
	static const float Deg2Rad;
	static const float Rad2Deg;

	static float Sign(float value);
	static float Clamp(float value, float min, float max);

	static b2Vec2 Clamp(b2Vec2 vec, float max_length);

	static float Clamp01(float value);
	static float Distance(b2Vec2 vec_a, b2Vec2 vec_b);
	static float SquaredDistance(b2Vec2 vec_a, b2Vec2 vec_b);
	static float Magnitude(b2Vec2 vec);
	static float SquaredMagnitude(b2Vec2 vec);
	static b2Vec2 LimitMagnitude(b2Vec2 vector, float magnitude);

	static float Lerp(float a, float b, float t);
	static b2Vec2 Lerp(b2Vec2 p0, b2Vec2 p1, float t);

	static float LerpUnclamped(float a, float b, float t);
	static float LerpAngle(float a, float b, float t);
	static float Repeat(float t, float length);

	static float RandomRange(float min, float max);
	static b2Vec2 RandomRange(b2Vec2 p0, b2Vec2 p1);

	static float Sanitize(float value);
	static b2Vec2 Min(b2Vec2 vec_a, b2Vec2 vec_b);
	static float Min(float a, float b);
	static b2Vec2 Max(b2Vec2 vec_a, b2Vec2 vec_b);
	static float Max(float a, float b);
	static b2Vec2 Negate(b2Vec2 vec);
	static b2Vec2 Inverse(b2Vec2 vec);
	static b2Vec2 Normalize(b2Vec2 vec);
	static float Angle(b2Vec2 from, b2Vec2 to);
	static float Dot(b2Vec2 lhs, b2Vec2 rhs);
	static float SignedAngle(b2Vec2 from, b2Vec2 to);

	// debugging convenience functions
	static void DrawLine(b2Vec2 start, b2Vec2 end, glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), SDL_Renderer* renderer = Renderer::Instance().GetRenderer());
	static void DrawRect(b2Vec2 position, int width, int height, glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), SDL_Renderer* renderer = Renderer::Instance().GetRenderer());
	static void DrawFilledRect(b2Vec2 position, int width, int height, glm::vec4 fill_colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), SDL_Renderer* renderer = Renderer::Instance().GetRenderer());
	static void DrawCircle(b2Vec2 centre, float radius, glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), ShapeType type = ShapeType::SYMMETRICAL, SDL_Renderer* renderer = Renderer::Instance().GetRenderer());
	static void DrawCapsule(b2Vec2 position, int width, int height, glm::vec4 colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), SDL_Renderer* renderer = Renderer::Instance().GetRenderer());

	static float GetClosestEdge(b2Vec2 vec_a, GameObject* object);

	static SDL_Color ToSDLColour(glm::vec4 colour);

private:
	Util();
	~Util();

};




#endif /* defined (__UTIL__) */
