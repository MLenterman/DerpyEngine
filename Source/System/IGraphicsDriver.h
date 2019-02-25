#pragma once

#include <iostream>
#include <map>

#include "EGraphicsDriver.h"

namespace Derpy { namespace System {

	enum class EGraphicsDriverFeature{
		RENDER_TO_TARGET,
		HARDWARE_TL,
		MULTITEXTURE,
		BILINEAR_FILTER,
		MIP_MAP,
		MIP_MAP_AUTO_UPDATE,
		STENCIL_BUFFER,
		VERTEX_SHADER_1_1,
		VERTEX_SHADER_2_0,
		VERTEX_SHADER_3_0,
		PIXEL_SHADER_1_1,
		PIXEL_SHADER_1_2,
		PIXEL_SHADER_1_3,
		PIXEL_SHADER_1_4,
		PIXEL_SHADER_2_0,
		PIXEL_SHADER_3_0,
		ARB_VERTEX_PROGRAM_1,
		ARB_FRAGMENT_PROGRAM_1,
		ARB_GLSL,
		HLSL,
		TEXTURE_NSQUARE,
		TEXTURE_NPOT,
		FRAMEBUFFER_OBJECT,
		VERTEX_BUFFER_OBJECT,
		ALPHA_TO_COVERAGE,
		COLOR_MASK,
		MULTIPLE_RENDER_TARGETS,
		MRT_BLEND,
		MRT_COLOR_MASK,
		MRT_BLEND_FUNC,
		GEOMETRY_SHADER,
		OCCLUSION_QUERY,
		POLYGON_OFFSET,
		BLEND_OPERATIONS,
		TEXTURE_MATRIX,
		CG,
		COUNT
	};

	class IGraphicsDriver{
	protected:
		

	public:
		IGraphicsDriver(EGraphicsDriver driver);
		virtual ~IGraphicsDriver();

		virtual bool queryDriverFeature(EGraphicsDriverFeature feature) = 0;
		virtual bool disableDriverFeature(EGraphicsDriverFeature feature) = 0;

	};



} }