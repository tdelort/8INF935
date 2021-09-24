#pragma once

class IIntegrable
{
public:
	virtual void Integrate(double deltaTime) = 0;
	virtual ~IIntegrable() {};
};

