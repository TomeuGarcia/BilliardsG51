#pragma once
#include "../Colliders/Collider2D.h"


class Collision2D
{
public:
	enum class Status { 
		Enter,
		Stay,
		Exit
	};


public:
	Collision2D(Collider2D* colliderA, Collider2D* colliderB);
	~Collision2D();

	void UpdateStatus(const bool& keepColliding);


	Collider2D* GetColliderA() const;
	Collider2D* GetColliderB() const;
	const Status GetStatus() const;


private:
	void NotifyEnter();


private:
	Collider2D* m_colliderA;
	Collider2D* m_colliderB;
	Status m_status;

};