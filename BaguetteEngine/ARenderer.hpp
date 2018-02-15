#pragma once

#include "ofMain.h"

#include "NonCopyable.hpp"

class ARenderer : private NonCopyable
{
public:
	ARenderer(void);
	virtual ~ARenderer(void);

	virtual void draw(ofVboMesh & vbo) = 0;
};

