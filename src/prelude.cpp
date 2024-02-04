/* ========================================================================
 *
 *     Filename:  prelude.hpp
 *  Description:  C++ sensible prelude - Definitions
 *       Author:  Diego A. Estrada Rivera
 *      Version:  0.0.4
 *      License:  GPL-3.0
 *
 * ======================================================================== */
#include "prelude.hpp"

/* type-safe main */
I32 main(const I32 argc, const Handle<const CString> argv)
{
	proc Main(std::span<const std::string_view>) noexcept -> I32;
	let args = std::vector<std::string_view>(
	    argv, std::next(argv, static_cast<std::ptrdiff_t>(argc)));
	return Main(args);
}

/* Sensible IO */
#include <iostream>

proc getLine() noexcept -> String
{
	var str = String();
	getline(std::cin, str);
	return str;
}

proc getChar() noexcept -> Char
{
	var c = Char();
	std::cin >> c;
	return c;
}

proc print(const std::string_view& f) noexcept -> Unit
{
	std::cout << f;
	return Unit();
}

proc println(const std::string_view& f) noexcept -> Unit
{
	std::cout << f << std::endl;
	return Unit();
}
