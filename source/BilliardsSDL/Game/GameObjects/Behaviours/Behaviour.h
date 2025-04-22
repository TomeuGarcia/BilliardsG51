#pragma once

class GameObject;

class Behaviour
{
public:
	Behaviour() {}
	~Behaviour() {}

public:
	virtual void Start() {}
	virtual void Update() {}
	virtual void OnDestroy() {}

	virtual void OnCollisionEnter(GameObject* other) {}
	virtual void OnCollisionExit(GameObject* other) {}
	
	virtual void OnTriggerEnter(GameObject* other) {}
	virtual void OnTriggerExit(GameObject* other) {}
};