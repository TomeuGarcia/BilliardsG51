#pragma once
#include <vector>
#include "../GameObjects/Transform.h"
#include "../../Shared/Math/Math.h"
#include "../Render/Renderers/Renderer.h"


class GameTweener
{
private:
	struct TransformTween
	{
	public:
		TransformTween(Transform* transform, const Vector2<float>& origin, const Vector2<float>& goal, 
			const float& duration, const float& delay);

		void Update(const float& deltaTime);
		Vector2<float> GetCurrentValue() const;
		bool HasFinished();

	public:
		Transform* p_transform;
	private:
		Vector2<float> m_origin;
		Vector2<float> m_goal;
		float m_duration;
		float m_currentTime;
	};


	struct RendererColorTween
	{
	public:
		RendererColorTween(Renderer* renderer, const Color& origin, const Color& goal,
			const float& duration, const float& delay);

		void Update(const float& deltaTime);
		Color GetCurrentValue() const;
		bool HasFinished();

	public:
		Renderer* p_renderer;
	private:
		Color m_origin;
		Color m_goal;
		float m_duration;
		float m_currentTime;
	};






public:
	GameTweener();
	~GameTweener();

	static GameTweener* GetInstance();

public:
	void Update(const float& deltaTime);
	void Clear();

public:
	void TweenPosition(Transform* transform, const Vector2<float>& goalPosition, const float& duration, const float& delay);
	void TweenColor(Renderer* renderer, const Color& goalColor, const float& duration, const float& delay);

private:
	void UpdatePositionTweens(const float& deltaTime);
	void UpdateColorTweens(const float& deltaTime);


private:
	std::vector<TransformTween> m_positionTweens;
	std::vector<RendererColorTween> m_colorTweens;

private:
	static GameTweener* s_instance;
};