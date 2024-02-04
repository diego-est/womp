/* ========================================================================
 *
 *     Filename:  WCompositor.hpp
 *  Description:  W Compositor class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#pragma once
#include "prelude.hpp"
#include <LCompositor.h>
#include <LLayerView.h>
#include <LScene.h>
#include <LTextureView.h>

using namespace Louvre;

class WCompositor : public LCompositor {
      public:
	WCompositor() noexcept;
	void initialized() noexcept override;

	// virtual constructors
	fn createOutputRequest() noexcept -> Handle<LOutput> override;
	fn createSurfaceRequest(Handle<LSurface::Params> params) noexcept -> Handle<LSurface> override;

	// scene and layers
	LScene scene;
	LLayerView backgroundLayer;
	LLayerView surfacesLayer;
	LLayerView overlayLayer;
	LLayerView fullscreenLayer;
	LLayerView cursorLayer;

	LTextureView softwareCursor;
};
