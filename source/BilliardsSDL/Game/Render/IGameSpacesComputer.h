#pragma once
#include "../../Shared/Types/Rect/Rect.h"



class IGameSpacesComputer
{
public:
	virtual Vector2<int> WorldToWindowPosition(const Vector2<float>& worldPosition) = 0;
	virtual Vector2<float> WindowToWorldPosition(const Vector2<int>& windowPosition) = 0;

	virtual Vector2<int> WorldToWindowVector(const Vector2<float>& worldVector) = 0;
	virtual Vector2<float> WindowToWorldVector(const Vector2<int>& windowVector) = 0;

	virtual Rect<int> WorldToWindowRect(const Rect<float>& worldRect) = 0;
	virtual Rect<float> WindowToWorldRect(const Rect<int>& windowRect) = 0;

	virtual Line<int> WorldToWindowLine(const Line<float>& worldLine) = 0;
};