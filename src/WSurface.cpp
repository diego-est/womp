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
#include "WCompositor.hpp"
#include "WOutput.hpp"
#include "WTopBarItem.hpp"
#include "global.hpp"
#include "prelude.hpp"
#include <LCursor.h>
#include <LSceneView.h>

WSurface::WSurface(Handle<Params> params) noexcept
    : LSurface(params), view(this, &G::compositor()->surfacesLayer)
{
	view.enableParentOffset(false);
}

WSurface::~WSurface() noexcept
{
	// destroy thumbnails
	while (not topBarItems.empty())
		delete topBarItems.back();

	// destroy thumbnail texture
	if (thumbnail != nullptr)
		delete thumbnail;
}

void WSurface::roleChanged() noexcept
{
	// hide cursor surfaces before we use LCursor
	if (cursorRole()) {
		view.setVisible(false);

	} else if (dndIcon()) { // move drag & drop icons to the cursor layer so
				// they always appear above other views
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
	} else { // if there is no prev surface, insert it at the beginning of
		 // the current parent's children list
		view.insertAfter(nullptr, false);
	}
}

void WSurface::minimizedChanged() noexcept
{
	// remove pointer and keyboard focus
	if (minimized()) {
		if (hasPointerFocus())
			seat()->pointer()->setFocus(nullptr);

		if (hasKeyboardFocus())
			seat()->keyboard()->setFocus(nullptr);
	}

	/*
	 * When a surface is minimized, all its children are also minimized.
	 * We only want to display toplevels in the top bar so we ignore the
	 * rest.
	 */

	if (not toplevel()) {
		view.setVisible(not minimized());
		return;
	}

	/*
	 * would be nice if this piece of code was more expressive
	 * (functions?) TODO
	 */
	if (minimized()) {
		minimizedOutput = findPrimaryOutput();

		if (minimizedOutput != nullptr) {
			/*
			 * Save the current surface position relative to the
			 * output position as a percentage so we can restore it
			 * later even if the outputs arrangement changes or the
			 * given output is no longer available.
			 */
			let localPos = rolePos() - minimizedOutput->pos();
			prevMinimizedPos =
			    localPos / LSizeF(minimizedOutput->size());
		} else {
			/*
			 * In case the surface is not visible on any output, we
			 * select the first available output and position the
			 * surface 1/4 of the output as a fallback.
			 */
			minimizedOutput = G::outputs().front();
			prevMinimizedPos = LPointF(0.25f, 0.25f);
		}

		var tmpScene = LSceneView(sizeB(), bufferScale());
		capture(&tmpScene);

		// scale it to the thumbnail size
		thumbnail = tmpScene.texture()->copyB(
		    LSize((THUMBNAIL_HEIGHT * sizeB().w()) / sizeB().h(),
			  THUMBNAIL_HEIGHT) *
		    2);

		// create a top bar item for each top bar
		for (let output : G::outputs())
			new WTopBarItem(output->topBar.get(), this);
	} else {
		// if minimized output is nullptr, it's because it was
		// uninitialized while the surface was minimized
		if (minimizedOutput == nullptr) {
			minimizedOutput = G::outputs().front();
			prevMinimizedPos = LPointF(0.25f, 0.25f);
		}

		// destroy thumbnails
		while (not topBarItems.empty())
			delete topBarItems.front();

		// restore back the previous unminimized position
		setPos(minimizedOutput->pos() +
		       (prevMinimizedPos * minimizedOutput->size()));
		minimizedOutput = nullptr;
		view.setVisible(true);

		// stack the surface above the rest
		raise();
	}
}

fn WSurface::findPrimaryOutput() const noexcept -> Handle<WOutput>
{
	var bestOutput = Handle<WOutput>(nullptr);
	var bestArea = 0;
	var surfaceRect = LRect();

	// ignore the decoration of toplevel and pop-up roles
	if (toplevel())
		surfaceRect =
		    LRect(rolePos() + toplevel()->windowGeometry().pos(),
			  toplevel()->windowGeometry().size());
	else if (popup())
		surfaceRect = LRect(rolePos() + popup()->windowGeometry().pos(),
				    popup()->windowGeometry().size());
	else
		surfaceRect = LRect(rolePos(), size());

	/*
	 * Calculate the area of the surface intersected with each output and
	 * return the one with the largest area
	 */
	for (let output : G::outputs()) {
		// we use LRegion to intersect both rects
		var tmpRegion = LRegion();
		tmpRegion.addRect(surfaceRect);
		tmpRegion.clip(output->rect());

		let extents = tmpRegion.extents();
		let area =
		    (extents.x2 - extents.x1) * (extents.y2 - extents.y1);

		if (area > bestArea) {
			bestArea = area;
			bestOutput = output;
		}
	}

	return bestOutput;
}

void WSurface::capture(Handle<LSceneView> sceneView)
{
	/*
	 * Instead of moving each view to the sceneView, we move the scene to
	 * the views' position. This is why disabling parent offset is required.
	 */
	sceneView->setPos(rolePos());

	/*
	 * Add the view and any child subsurface view to the scene. Notice that
	 * we exclude child surfaces with the popup or toplevel roles.
	 */
	G::moveSurfaceWithChildren(this, sceneView, G::SubSurfacesOnly::on);
	sceneView->render();

	// restore views to the surface layer
	while (not sceneView->children().empty())
		sceneView->children().front()->setParent(
		    &G::compositor()->surfacesLayer);
}
