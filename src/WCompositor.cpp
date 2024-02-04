/* ========================================================================
 *
 *     Filename:  WCompositor.cpp
 *  Description:  W Compositor class definitions
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "WCompositor.hpp"
#include "WOutput.hpp"
#include "WSurface.hpp"
#include "prelude.hpp"
#include <LOutput.h>
#include <LSceneView.h>

WCompositor::WCompositor() noexcept
    : LCompositor(), scene(), backgroundLayer(scene.mainView()),
      surfacesLayer(scene.mainView()), overlayLayer(scene.mainView()),
      fullscreenLayer(scene.mainView()), cursorLayer(scene.mainView()),
      softwareCursor(nullptr, &cursorLayer)
{
	// set black as the scene clear color
	scene.mainView()->setClearColor(0.f, 0.f, 0.f, 1.f);

	// this allows us to define a custom size to an LTextureView
	softwareCursor.enableDstSize(true);
}

void WCompositor::initialized() noexcept
{
	// set a keyboard with dvorax layout
	seat()->keyboard()->setKeymap(nullptr, nullptr, "us", "dvorak");

	var totalWidth = 0;

	// initialize all available outputs
	for (Handle<LOutput> output : seat()->outputs()) {
		// set double scale to outputs with DPI >= 200
		output->setScale(output->dpi() >= 200 ? 2 : 1);

		output->setPos(LPoint(totalWidth, 0));
		totalWidth += output->size().w();

		addOutput(output);
		output->repaint();
	}
}

fn WCompositor::createOutputRequest() noexcept -> Handle<LOutput>
{
	return new WOutput;
}
fn WCompositor::createSurfaceRequest(Handle<LSurface::Params> params) noexcept
    -> Handle<LSurface>
{
	return new WSurface(params);
}
