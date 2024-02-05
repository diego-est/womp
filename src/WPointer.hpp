/* ========================================================================
 *
 *     Filename:  WPointer.hpp
 *  Description:  W Compositor WPointer class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#pragma once
#include "prelude.hpp"
#include <LPointer.h>

using namespace Louvre;

class WPointer : public LPointer {
      public:
	WPointer(Handle<Params> params) noexcept;

	void pointerMoveEvent(F32 x, F32 y, Bool absolute) noexcept override;
	void pointerButtonEvent(Button button,
				ButtonState state) noexcept override;
	void pointerAxisEvent(F64 axisX, F64 axisY, I32 discreteX,
			      I32 discreteY,
			      AxisSource source) noexcept override;
};
