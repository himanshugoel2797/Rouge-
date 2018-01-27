#pragma once

#include <string>

#include "Context.h"
#include "DeferredContext.h"

namespace RougePP::Management {
	class Scene
	{
	private:
		std::string scene_name;
	public:
		Scene(std::string name, RougePP::Graphics::Context *ctxt, RougePP::Graphics::DeferredContext *dctxt);
		~Scene();

		RougePP::Graphics::Context *Context;
		RougePP::Graphics::DeferredContext *DeferredContext;

		std::string Name();

		virtual void Update(long frametime) = 0;
		virtual void Render(long frametime) = 0;
	};
}

