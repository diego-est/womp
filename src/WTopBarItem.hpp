/* ========================================================================
 *
 *     Filename:  WTopBarItem.hpp
 *  Description:  W Compositor WTopBarItem class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#pragma once

#include "prelude.hpp"
#include <LTextureView.h>

using namespace Louvre;

class WTopBar;
class WSurface;

class WTopBarItem : public LTextureView {
      public:
	WTopBarItem(Handle<WTopBar> topBar, Handle<WSurface> surface) noexcept;
	~WTopBarItem();

	void pointerButtonEvent(LPointer::Button button,
				LPointer::ButtonState state) noexcept override;

	std::list<Handle<WTopBarItem>>::iterator surfaceLink;

	Handle<WTopBar> topBar = nullptr;
	Handle<WSurface> surface = nullptr;
};
