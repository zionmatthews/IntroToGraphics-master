#pragma once
class Actor
{
public:
	Actor() {}
	~Actor() {}

	virtual bool update(double detaTime) { return true; }
	virtual bool draw() { return true; }
};

