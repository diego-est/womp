/* ========================================================================
 *
 *     Filename:  WSurface.hpp
 *  Description:  W Compositor surface class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#pragma once
#include "prelude.hpp"
#include <LSurface.h>
#include <LSurfaceView.h>

using namespace Louvre;

class WTopBarItem;
class WOutput;

class WSurface : public LSurface {
      public:
	WSurface(Handle<LSurface::Params> params) noexcept;
	~WSurface() noexcept;

	void roleChanged() noexcept override;
	void orderChanged() noexcept override;
	void minimizedChanged() noexcept override;

	// return the output where the surface is currently the most visible
	fn findPrimaryOutput() const noexcept -> Handle<WOutput>;

	// take a snapshot of the surface, including its subsurfaces
	void capture(Handle<LSceneView> sceneView);

	LSurfaceView view;

	// a single thumbnail texture shared by all top bar items
	Handle<LTexture> thumbnail = nullptr;

	// list of thumbnail views, one for each output's topbar
	std::list<Handle<WTopBarItem>> topBarItems;

	// the output where the surface was most visible before being minimized
	Handle<WOutput> minimizedOutput = nullptr;

	LPointF prevMinimizedPos;
};
