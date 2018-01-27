#include "stdafx.h"
#include "Scene.h"

using namespace RougePP::Management;

Scene::Scene(std::string name, RougePP::Graphics::Context *ctxt, RougePP::Graphics::DeferredContext *dctxt)
{
	scene_name = name;
	Context = ctxt;
	DeferredContext = dctxt;
}

std::string Scene::Name() {
	return scene_name;
}

Scene::~Scene()
{
}
