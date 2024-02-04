/* ========================================================================
 *
 *     Filename:  WTopBar.hpp
 *  Description:  W Compositor top bar class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#pragma once
#include "prelude.hpp"
#include <memory>

#include <LSolidColorView.h>

using namespace Louvre;

class WOutput;

class WTopBar : public LObject {
      public:
	WTopBar(Handle<WOutput> output) noexcept;
	~WTopBar() noexcept;

	Handle<WOutput> output;
	LSolidColorView view;

	void update() noexcept;
};
