/* ========================================================================
 *
 *     Filename:  WSurface.cpp
 *  Description:  W Compositor surface class definitions
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "WSurface.hpp"
#include "prelude.hpp"
#include "global.hpp"
#include "WCompositor.hpp"
#include <LCursor.h>


WSurface::WSurface(Handle<Params> params) noexcept : LSurface(params),
	view(this, &G::compositor()->surfacesLayer)
{
	view.enableParentOffset(false);
}

void WSurface::roleChanged() noexcept
{
	// hide cursor surfaces before we use LCursor
	if (cursorRole()) {
		view.setVisible(false);

	} else if (dndIcon()) { // move drag & drop icons to the cursor layer so they always appear above other views
		// ensure it is positioned behind 'softwareCursor'
		view.setParent(&G::compositor()->cursorLayer);
		view.insertAfter(nullptr, false);
		setPos(cursor()->pos());
	}
}

void WSurface::orderChanged() noexcept
{
	var prev = Handle<WSurface>(prevSurface());

	// if prev has a different parent view keep searching for a match
	while (prev != nullptr && prev->view.parent() != view.parent())
		prev = Handle<WSurface>(prev->prevSurface());

	// if prev is valid that means it has the same parent view. So we insert
	// view after prev's view
	if (prev != nullptr) {
		view.insertAfter(&prev->view, false);
	} else { // if there is no prev surface, insert it at the beginning of the current parent's children list
		view.insertAfter(nullptr, false);
	}
}
