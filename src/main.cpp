/* ========================================================================
 *
 *     Filename:  main.cpp
 *  Description:  W Compositor entry point
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *      Version:  0.2.0
 *
 * ======================================================================== */
#include "WCompositor.hpp"
#include "prelude.hpp"
#include <LCompositor.h>
#include <LLauncher.h>
#include <LLog.h>

using namespace Louvre;

proc Main([[maybe_unused]] std::span<const std::string_view> args) noexcept
    -> I32
{
	LLauncher::startDaemon();

	var compositor = WCompositor();

	if (!compositor.start()) {
		LLog::fatal("[louvre-example] Failed to start compositor.");
		return 1;
	}

	while (compositor.state() != LCompositor::Uninitialized)
		compositor.processLoop(-1);

	return 0;
}
