#include "AMesh.hpp"
#include "ARenderer.hpp"
#include "ofGraphics.h"

AMesh::AMesh(void)
{
	mesh_ = nullptr;
	init();
}

AMesh::~AMesh(void)
{
}

void AMesh::draw(ARenderer & renderer)
{
	ofPushMatrix();
	ofTranslate(getGlobalPosition().x, getGlobalPosition().y, getGlobalPosition().z);
	if (isFocused()) ofDrawAxis(std::max({ getScale().x, getScale().y, getScale().z }) + 1);
	ofPopMatrix();

	if (texture()) texture()->getTexture().bind();

	// shader_.begin();
	// shader_.setUniformMatrix4f("model", getGlobalTransformMatrix());
	// renderer.draw(vbo_);

	ofPushMatrix();
	ofTranslate(getGlobalPosition());
	ofRotateX(getOrientationEuler().x);
	ofRotateY(getOrientationEuler().y);
	ofRotateZ(getOrientationEuler().z);
	ofScale(getScale());
	draw_();
	ofPopMatrix();

	// shader_.end();
	if (texture()) texture()->getTexture().unbind();
}

void AMesh::init(void)
{
	// shader_.load("./vertex_shader.vert", "./fragment_shader.frag");
	meshType_ = InstantiableMesh::UNDEFINED;

	texture_ = new Texture;
	texture_->loadImage(TextureGenerator::perlinNoise(500, 500, 0.01f));
	// texture_ = new Texture;
	// texture_->loadImage(TextureGenerator::monochrome(1500, 1500, 255, 0, 0));
}

void AMesh::setMesh(ofMesh * oMesh)
{
	// vbo_ = oMesh;
	mesh_ = oMesh;
	init();
	initColor();
}

const std::vector<ofPoint>& AMesh::getVertices() const
{
	return mesh_->getVertices();
}

void AMesh::setFillColor(const ofColor & c)
{
	// const std::vector<ofPoint> & vertices = vbo_.getVertices();
	if (mesh_)
	{
		const std::vector<ofPoint> & vertices = mesh_->getVertices();

		for (int i = 0; i < vertices.size(); i++) {
			mesh_->setColor(i, { c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f });
		}
	}
}

const ofColor & AMesh::getFillColor(void) const
{
	// return vbo_.getColor(0);
	return mesh_->getColor(0);
}

void AMesh::setOutlineColor(const ofColor & color)
{
}

const ofColor & AMesh::getOutlineColor(void) const
{
	return getFillColor();
}

void AMesh::setOutlineThickness(int thickness)
{
}

int AMesh::getOutlineThickness(void) const
{
	return 0;
}

AMesh::InstantiableMesh AMesh::getType(void) const
{
	return meshType_;
}

void AMesh::update(float dt)
{
}

/* void AMesh::draw(ARenderer & renderer)
{
	ofPushMatrix();
		ofTranslate(getGlobalPosition().x, getGlobalPosition().y, getGlobalPosition().z);
		if (isFocused()) ofDrawAxis(std::max({ getScale().x, getScale().y, getScale().z }) + 1);
	ofPopMatrix();

	shader_.begin();
	// if (texture()) texture()->getTexture().bind();
		shader_.setUniformMatrix4f("model", getGlobalTransformMatrix());
		renderer.draw(*mesh_);
	// if (texture()) texture()->getTexture().unbind();
	shader_.end();
} */

void AMesh::setTexture(Texture * texture)
{
	texture_ = texture;
	/* if (texture_) {
		mapTexCoordsFromTexture(texture_->getTexture());
	} */
}
void AMesh::mapTexCoordsFromTexture(const ofTexture& inTexture)
{
	// const ofTextureData & tdata = inTexture.getTextureData();
	// mapTexCoords(0, 0, inTexture.getWidth(), inTexture.getHeight());
}

void AMesh::mapTexCoords(float u1, float v1, float u2, float v2)
{

}

void AMesh::invalidate(void)
{
}

void AMesh::initColor(void)
{
	const std::vector<ofPoint> & vertices = mesh_->getVertices();

	for (int i = 0; i < vertices.size(); i++) {
		mesh_->addColor(ofFloatColor::white);
	}
}