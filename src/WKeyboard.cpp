/* ========================================================================
 *
 *     Filename:  WKeyboard.hpp
 *  Description:  W Compositor WKeyboard class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "WKeyboard.hpp"
#include "prelude.hpp"
#include "global.hpp"
#include <LScene.h>
#include <LClient.h>
#include <LCompositor.h>
#include <LCursor.h>
#include <LLauncher.h>
#include <LOutput.h>
#include <LSurface.h>
#include <linux/input-event-codes.h>
#include <unistd.h>

WKeyboard::WKeyboard(Handle<Params> params) noexcept : LKeyboard(params)
{
}

void WKeyboard::keyEvent(U32 keyCode, KeyState keyState) noexcept
{
	G::scene()->handleKeyEvent(keyCode, keyState);
}

void WKeyboard::keyModifiersEvent(U32 depressed, U32 latched, U32 locked,
				  U32 group) noexcept
{
	G::scene()->handleKeyModifiersEvent(depressed, latched, locked, group);
}
