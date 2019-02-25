#pragma once

namespace Derpy { namespace System {

	enum class EGraphicsDriver{
		NONE,
		SOFTWARE,
		DIRECT3D9,
		DIRECT3D10,
		DIRECT3D11,
		OPENGL,
		OPENGLES
	};


} }