#include "Scene3D.hpp"

Scene3D::Scene3D(void)
{
	cam_.setDistance(10);
	cam_.setNearClip(0.01);
	cam_.setFarClip(1000);

	cam_.setPosition(ofVec3f(0, 10, 5));
	cam_.rotate(0, 0, 0, 0);
	cam_.lookAt(ofVec3f(0, 0, 0));
}

Scene3D::~Scene3D(void)
{
}

void Scene3D::update(float dt)
{
	AScene::update(dt);
	cam_.update(dt);
}

void Scene3D::render(ARenderer & renderer)
{
	cam_.begin();
	ofDrawGrid(1, 8U, false, false, true, false);
	// ofDrawAxis(2); // x = red ; y = green ; z = blue.
	AScene::render(renderer);
	cam_.end();
}

void Scene3D::setDrawablePosition(const Identifiable & drawableId, const ofVec3f & pos, bool save)
{
	AScene::setDrawablePosition(drawableId, pos, save);
	cam_.targetPositionChanged();
}

const Identifiable & Scene3D::instanciateDrawable(const std::string & type, const Identifiable & parent)
{
	ensureDrawableExistance(parent);
	SceneNode::Ptr node = nullptr;

	if (type == "sphere")
		node = SceneGraph::CreateSceneNode<AMesh, SphereGenerator>();
	else if (type == "plane")
		node = SceneGraph::CreateSceneNode<AMesh, PlaneGenerator>();
	else if (type == "cube")
		node = SceneGraph::CreateSceneNode<AMesh, CubeGenerator>();
	else if (type == "cone")
		node = SceneGraph::CreateSceneNode<AMesh, ConeGenerator>();
	else if (type.find("/") != std::string::npos
				|| type.find("\\") != std::string::npos
				|| type.find(".") != std::string::npos)
		node = SceneGraph::CreateSceneNode<AMesh, Model3DGenerator>(type);
	else
		std::cerr << type << " not found !" << std::endl;
	try {
		const Identifiable & id = graph_.attachTo(std::move(node), parent);
		historic_.pushTransformation(std::make_pair(id, ofMatrix4x4::newIdentityMatrix()));
		return id;
	}
	catch (const std::runtime_error & e) {
		throw (e);
	}
}

std::string Scene3D::getName(void) const
{
	return "Editeur 3D";
}

int Scene3D::getNbDimensions(void) const
{
	return 3;
}

void Scene3D::setFocusedDrawable(const Identifiable & drawableId)
{
	AScene::setFocusedDrawable(drawableId);

	SceneNode *node = ensureDrawableExistance(drawableId);
	if (node && drawableId != 0) {
		cam_.setTargetSceneNode(node);
	}
	else {
		cam_.setTargetSceneNode(nullptr);
	}
}	