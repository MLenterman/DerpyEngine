#pragma once

#include <iostream>

#include "System/EGraphicsDriver.h"
#include "System/IGraphicsDriver.h"
#include "System/GraphicsDriver_GL.h"

namespace Derpy {

	class Engine{
	private:
		System::IGraphicsDriver* m_GraphicsDriver;

	public:
		void start();

		System::IGraphicsDriver* getGraphicsDriver() const;
		bool setGraphicsDriver(System::EGraphicsDriver driver);
		

	};


}