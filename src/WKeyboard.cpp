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
	sendKeyEvent(keyCode, keyState);

	/* === TODO: refactor this monstrosity === */
	let L_CTRL = isKeyCodePressed(KEY_LEFTCTRL);
	let L_SHIFT = isKeyCodePressed(KEY_LEFTSHIFT);
	let mods = isKeyCodePressed(KEY_LEFTALT) && L_CTRL;
	let sym = keySymbol(keyCode);

	if (keyState == Released) {
		if (keyCode == KEY_F1 and not mods) {
			// launches weston-terminal
			LLauncher::launch("weston-terminal");
		} else if (L_CTRL and (sym == XKB_KEY_q or sym == XKB_KEY_Q)) {
			// terminates client connection
			if (focus())
				focus()->client()->destroy();
		} else if (L_CTRL and (sym == XKB_KEY_m or sym == XKB_KEY_M)) {
			// minimizes currently focused surface
			if (focus() != nullptr and
			    focus()->toplevel() != nullptr and
			    not focus()->toplevel()->fullscreen())
				focus()->setMinimized(true);
		} else if (L_CTRL and L_SHIFT and keyCode == KEY_3) {
			if (cursor()->output()->bufferTexture(0) != nullptr)
				cursor()->output()->bufferTexture(0)->save(
				    "/tmp/image.png");
		} else if (keyCode == KEY_ESC and L_CTRL and L_SHIFT) {
			compositor()->finish();
			return;
		} else if (L_CTRL and not L_SHIFT) {
			seat()->dndManager()->setPreferredAction(
			    LDNDManager::Copy);
		} else if (not L_CTRL and L_SHIFT) {
			seat()->dndManager()->setPreferredAction(
			    LDNDManager::Move);
		} else if (not L_CTRL and not L_SHIFT) {
			seat()->dndManager()->setPreferredAction(
			    LDNDManager::NoAction);
		} else { // keypress
			// ctrl sets copy as the preferred action in a drag &
			// drop session
			if (L_CTRL) {
				seat()->dndManager()->setPreferredAction(
				    LDNDManager::Copy);
			} else if (L_SHIFT) { // shift sets the preferred action
					      // in a drag & drop session
				seat()->dndManager()->setPreferredAction(
				    LDNDManager::Move);
			}
		}
	}
}

void WKeyboard::keyModifiersEvent(U32 depressed, U32 latched, U32 locked,
				  U32 group) noexcept
{
	sendModifiersEvent(depressed, latched, locked, group);
}
