#pragma once

#include "IGraphicsDriver.h"

namespace Derpy { namespace System {

	class GraphicsDriver_GL : public IGraphicsDriver{
	public:
		GraphicsDriver_GL(EGraphicsDriver driver)
		: IGraphicsDriver(driver){

		}

		virtual bool queryDriverFeature(EGraphicsDriverFeature feature) override;
		virtual bool disableDriverFeature(EGraphicsDriverFeature feature) override;
	};



} }