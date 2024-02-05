/* ========================================================================
 *
 *     Filename:  WPointer.cpp
 *  Description:  W Compositor WPointer class definitions
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "WPointer.hpp"
#include "global.hpp"
#include <LCompositor.h>
#include <LCursor.h>
#include <LDNDIconRole.h>
#include <LDNDManager.h>
#include <LKeyboard.h>
#include <LOutput.h>
#include <LScene.h>
#include <LSeat.h>
#include <LSurface.h>
#include <LToplevelRole.h>
#include <LView.h>

WPointer::WPointer(Handle<Params> params) noexcept : LPointer(params)
{
}

void WPointer::pointerMoveEvent(F32 x, F32 y, Bool absolute) noexcept
{
	let view = G::scene()->handlePointerMoveEvent(x, y, absolute);
	if ((view == nullptr or view->type() != LView::Type::Surface) and
	    not resizingToplevel() and not movingToplevel()) {
		cursor()->useDefault();
		cursor()->setVisible(true);
	}
}

void WPointer::pointerButtonEvent(Button button, ButtonState state) noexcept
{
	G::scene()->handlePointerButtonEvent(button, state);
}
void WPointer::pointerAxisEvent(F64 axisX, F64 axisY, I32 discreteX,
				I32 discreteY, AxisSource source) noexcept
{
	G::scene()->handlePointerAxisEvent(axisX, axisY, discreteX, discreteY,
					   source);
}
