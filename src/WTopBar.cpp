/* ========================================================================
 *
 *     Filename:  WTopBar.cpp
 *  Description:  W Compositor top bar class definitions
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "WTopBar.hpp"
#include "WCompositor.hpp"
#include "WOutput.hpp"
#include "WTopBarItem.hpp"
#include "global.hpp"

WTopBar::WTopBar(Handle<WOutput> output) noexcept
    : output(output), view(0.f, 0.f, 0.f, 0.8f, &G::compositor()->overlayLayer)
{
	// copy thumbnails from an already initialized output
	for (let o : G::outputs()) {
		if (o == output)
			continue;

		for (let item : Ref<std::list<Handle<WTopBarItem>>>(
			 o->topBar->view.children()))
			new WTopBarItem(this, item->surface);

		break;
	}
	update();
}

WTopBar::~WTopBar() noexcept
{
	while (not view.children().empty())
		delete view.children().back();
}

void WTopBar::update() noexcept
{
	view.setSize(output->size().w(), TOPBAR_HEIGHT);
	view.setPos(output->pos());

	// update thumbnails
	for (var x = TOPBAR_PADDING;
	     let item : Ref<std::list<Handle<WTopBarItem>>>(view.children())) {
		item->setPos(x, TOPBAR_PADDING);
		x += item->size().w() + THUMBNAIL_MARGIN;
	}

	output->repaint();
}
