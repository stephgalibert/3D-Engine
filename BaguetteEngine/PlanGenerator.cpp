#include "PlanGenerator.hpp"

PlanGenerator::PlanGenerator()
{
	plan_.setPosition(ofVec3f(0, 0, 0));
	plan_.set(1, 1);
}

PlanGenerator::PlanGenerator(const ofVec2f pos, const float width, const float height)
{
	plan_.setPosition(pos);
	plan_.set(width, height);
}

AMesh PlanGenerator::operator()(void) const
{
	return generate();
}

AMesh PlanGenerator::generate() const
{
	return AMesh(plan_.getMesh());
}

void PlanGenerator::setSize(const float width, const float height)
{
	plan_.set(width, height);
}

void PlanGenerator::setPosition(const ofVec3f pos)
{
	plan_.setPosition(pos);
}
