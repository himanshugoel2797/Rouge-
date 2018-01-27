#pragma once

#include "../Engine/Management/Scene.h"

#include "Context.h"
#include "DeferredContext.h"

namespace RougePP::Runtime {
	class CoreLoop : public RougePP::Management::Scene
	{
	public:
		CoreLoop(RougePP::Graphics::Context *ctxt, RougePP::Graphics::DeferredContext *dctxt);
		~CoreLoop();

		// Inherited via Scene
		virtual void Update(long frametime) override;
		virtual void Render(long frametime) override;
	};
}
