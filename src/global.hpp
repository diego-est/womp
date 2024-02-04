/* ========================================================================
 *
 *     Filename:  global.hpp
 *  Description:  W Compositor global helper class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#pragma once
#include "prelude.hpp"
#include <LCompositor.h>

#define TOPBAR_HEIGHT 32
#define TOPBAR_PADDING 4
#define THUMBNAIL_MARGIN 4
#define THUMBNAIL_HEIGHT (TOPBAR_HEIGHT - 2 * TOPBAR_PADDING)

// avoid bool in moveSurfaceWithChildren
enum class subSurfacesOnly { off, on };

using namespace Louvre;

class WCompositor;
class WOutput;
class WSurface;

class G {
      public:
	fn static inline compositor() noexcept -> Handle<WCompositor>
	{
		return Handle<WCompositor>(LCompositor::compositor());
	}

	fn static inline outputs() noexcept -> Ref<std::list<Handle<WOutput>>>
	{
		return Ref<std::list<Handle<WOutput>>>(
		    LCompositor::compositor()->outputs());
	}

	fn static scene() noexcept -> Handle<LScene>;

	// cast the LCompositor::surfaces() from LSurface to WSurface
	fn static inline surfaces() noexcept -> Ref<std::list<Handle<WSurface>>>
	{
		return Ref<std::list<Handle<WSurface>>>(
		    LCompositor::compositor()->surfaces());
	}

	// move surface views with children
	static void moveSurfaceWithChildren(
	    Handle<WSurface> surface, Handle<LView> parent,
	    subSurfacesOnly opt = subSurfacesOnly::off) noexcept;
};
