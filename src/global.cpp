/* ========================================================================
 *
 *     Filename:  global.cpp
 *  Description:  W Compositor global helper class
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "global.hpp"
#include "WCompositor.hpp"
#include "WSurface.hpp"
#include "prelude.hpp"

fn G::scene() noexcept -> Handle<LScene>
{
	return &compositor()->scene;
}

void G::moveSurfaceWithChildren(Handle<WSurface> surface, Handle<LView> parent,
				subSurfacesOnly sso) noexcept
{
	surface->view.setParent(parent);
	var next = surface;

	if (sso == subSurfacesOnly::on) {
		while ((next = Handle<WSurface>(next->nextSurface())))
			if (next->isSubchildOf(surface) and
			    next->subsurface() != nullptr)
				next->view.setParent(parent);
	} else {
		while ((next = Handle<WSurface>(next->nextSurface())))
			if (next->isSubchildOf(surface))
				next->view.setParent(parent);
	}
}
