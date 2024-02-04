/* ========================================================================
 *
 *     Filename:  WTopBarItem.hpp
 *  Description:  W Compositor WTopBarItem class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "WTopBarItem.hpp"
#include "WSurface.hpp"
#include "WTopBar.hpp"
#include "prelude.hpp"

WTopBarItem::WTopBarItem(Handle<WTopBar> topBar,
			 Handle<WSurface> surface) noexcept
    : LTextureView(surface->thumbnail, &topBar->view), topBar(topBar),
      surface(surface)
{
	surface->topBarItems.push_back(this);
	surfaceLink = std::prev(surface->topBarItems.end());

	setBufferScale(2);
	enableParentOpacity(false);
	topBar->update();
}

WTopBarItem::~WTopBarItem()
{
	surface->topBarItems.erase(surfaceLink);
	setParent(nullptr);
	topBar->update();
}
