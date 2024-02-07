/* ========================================================================
 *
 *     Filename:  WKeyboard.hpp
 *  Description:  W Compositor WKeyboard class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#pragma once
#include "prelude.hpp"
#include <LKeyboard.h>

using namespace Louvre;

class WKeyboard : public LKeyboard {
      public:
	WKeyboard(Handle<Params> params) noexcept;

	void keyEvent(U32 keyCode, KeyState keyState) noexcept override;
	void keyModifiersEvent(U32 depressed, U32 latched, U32 locked,
			       U32 group) noexcept override;
};
