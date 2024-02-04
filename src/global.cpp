/* ========================================================================
 *
 *     Filename:  global.cpp
 *  Description:  W Compositor global helper class
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "global.hpp"
#include "WCompositor.hpp"
#include "prelude.hpp"

fn G::scene() noexcept -> Handle<LScene>
{
	return &compositor()->scene;
}
