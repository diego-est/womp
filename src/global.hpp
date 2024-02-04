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

using namespace Louvre;

class WCompositor;
class WOutput;

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
};
