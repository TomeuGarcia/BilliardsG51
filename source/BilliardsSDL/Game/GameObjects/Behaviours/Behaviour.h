#pragma once


class Behaviour
{
public:
	Behaviour() {}
	~Behaviour() {}

public:
	virtual void Start() {}
	virtual void Update() {}

	//virtual void OnCollisionEnter();
	//virtual void OnTriggerEnter();
};