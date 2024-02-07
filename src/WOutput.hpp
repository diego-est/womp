/* ========================================================================
 *
 *     Filename:  WOutput.hpp
 *  Description:  W Compositor output class declaration
 *  GitHub Repo:  https://github.com/diego-est/womp
 *       Author:  Diego A. Estrada Rivera
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#pragma once
#include "prelude.hpp"
#include <LOutput.h>
#include <memory>

using namespace Louvre;

class WTopBar;

class WOutput : public LOutput {
      public:
	WOutput() noexcept;

	void initializeGL() noexcept override;
	void moveGL() noexcept override;
	void resizeGL() noexcept override;
	void paintGL() noexcept override;
	void uninitializeGL() noexcept override;

	std::unique_ptr<LTextureView> wallpaperView;
	void updateWallpaper() const noexcept;

	void damageRenderingTest() noexcept;

	fn calculateWallpaperRect(
	    LSize const& originalWallpaperSize) const noexcept -> LRect;

	std::unique_ptr<WTopBar> topBar;
};
