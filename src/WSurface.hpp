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

class WSurface : public LSurface {
      public:
	WSurface(Handle<LSurface::Params> params) noexcept;

	void roleChanged() noexcept override;
	void orderChanged() noexcept override;

	LSurfaceView view;
};
