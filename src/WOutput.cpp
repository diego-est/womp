/* ========================================================================
 *
 *     Filename:  WOutput.cpp
 *  Description:  W Compositor output class definitions
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "WOutput.hpp"
#include "WCompositor.hpp"
#include "WSurface.hpp"
#include "WTopBar.hpp"
#include "global.hpp"
#include "prelude.hpp"
#include <LCompositor.h>
#include <LCursor.h>
#include <LDNDManager.h>
#include <LLog.h>
#include <LOpenGL.h>
#include <LPainter.h>
#include <LSeat.h>
#include <LTexture.h>
#include <LTextureView.h>
#include <memory>

WOutput::WOutput() noexcept
{
}

void WOutput::initializeGL() noexcept
{
	wallpaperView = std::make_unique<LTextureView>(
	    nullptr, &G::compositor()->backgroundLayer);

	/*
	 * TextureView's have a default nullptr translucent region, which means
	 * they are considered completely translucent by the scene. However,
	 * setting an empty LRegion (not nullptr) indicates to the scene that
	 * the view is completely opaque.
	 */
	let emptyRegion = LRegion();
	wallpaperView->setTranslucentRegion(&emptyRegion);

	updateWallpaper();
	topBar = std::make_unique<WTopBar>(this);
	G::scene()->handleInitializeGL(this);
	repaint();
}

void WOutput::moveGL() noexcept
{
	wallpaperView->setPos(pos());
	topBar->update();
	G::scene()->handleMoveGL(this);
	repaint();
}

void WOutput::resizeGL() noexcept
{
	updateWallpaper();
	topBar->update();
	G::scene()->handleResizeGL(this);
	repaint();
}

void WOutput::paintGL() noexcept
{
	// check if HW cursor is supported
	if (cursor()->hasHardwareSupport(this)) {
		G::compositor()->softwareCursor.setTexture(nullptr);
	} else {
		G::compositor()->softwareCursor.setTexture(cursor()->texture());
		G::compositor()->softwareCursor.setPos(cursor()->rect().pos());
		G::compositor()->softwareCursor.setDstSize(
		    cursor()->rect().size());
		G::compositor()->softwareCursor.setVisible(cursor()->visible());
	}
	topBar->update();
	// start test for efficient rendering
	/*
	painter()->clearScreen();
	G::scene()->handlePaintGL(this);

	var damage = LRegion();
	damage.addRect(rect());
	setBufferDamage(damage);
	*/
	// end test for efficient rendering
	G::scene()->handlePaintGL(this);
}

void WOutput::uninitializeGL() noexcept
{
	/*
	 * set minimized output to nullptr to prevent the compositor from
	 * crashing when a surface is unminimized and
	 * WSurface::minimizeChanged() is triggered
	 */
	for (let surface : G::surfaces())
		if (surface->minimizedOutput == this)
			surface->minimizedOutput = nullptr;

	G::scene()->handleUninitializeGL(this);

	if (wallpaperView->texture())
		delete wallpaperView->texture();
}

void WOutput::updateWallpaper() const noexcept
{
	if (wallpaperView->texture()) {
		// if the current wallpaper size is equal to the output size
		// then the output simply changed its scale
		if (wallpaperView->texture()->sizeB() == sizeB()) {
			wallpaperView->setBufferScale(scale());
			wallpaperView->setPos(pos());
			return;
		}

		delete wallpaperView->texture();
	}

	// load the original wallpaper
	let originalWallpaper = std::unique_ptr<LTexture>(LOpenGL::loadTexture(
	    "/home/Michorron/Media/Pictures/Wallpapers/bliss.jpg"));

	if (originalWallpaper == nullptr) {
		LLog::error("[louvre-example] Failed to load wallpaper.");
		return;
	}

	/*
	 * This section calculates the source wallpaper rect that needs to be
	 * copied and scaled to cover the entire output while maintaining the
	 * image's aspect ratio
	 */

	// define the source rect within the texture to clip
	var srcRect = LRect(0);

	let scaledWidth =
	    F32(size().w() * originalWallpaper->sizeB().h()) / F32(size().h());

	// if the scaled width is greater than or equal to the output's width,
	// we clip the texture's left and right sides.
	if (scaledWidth >= originalWallpaper->sizeB().w()) {
		srcRect.setH(originalWallpaper->sizeB().h());
		srcRect.setW((originalWallpaper->sizeB().h() * size().w()) /
			     size().h());
		srcRect.setY((originalWallpaper->sizeB().w() - srcRect.w()) /
			     2.0);
	} else { // otherwise clip the texture's top and bottom sides
		srcRect.setW(originalWallpaper->sizeB().w());
		srcRect.setH(originalWallpaper->sizeB().h() * size().h() /
			     size().w());
		srcRect.setY((originalWallpaper->sizeB().h() - srcRect.h()) /
			     2.0);
	}

	// copy the srcRect of the originall wallpaper and scale it to match the
	// output buffer size
	wallpaperView->setTexture(originalWallpaper->copyB(sizeB(), srcRect));

	// set the buffer scale of the wallpaper view to match the output scale
	wallpaperView->setBufferScale(scale());

	// delete the original wallpaper texture since we are using the scaled
	// copy
	wallpaperView->setPos(pos());
}
