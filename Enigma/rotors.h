#pragma once
#include "forward.h"

namespace Rotors
{
	/*
	For the sake of performance and other things, we're ditching ASCII
	and using the numbers 0 to 25 to mark the letters of the alphabet.

	They're put into this namespace so that the rest of the code can use single-character variable names w/o overriding these.
	*/
	const char a = 0;
	const char b = 1;
	const char c = 2;
	const char d = 3;
	const char e = 4;
	const char f = 5;
	const char g = 6;
	const char h = 7;
	const char i = 8;
	const char j = 9;
	const char k = 10;
	const char l = 11;
	const char m = 12;
	const char n = 13;
	const char o = 14;
	const char p = 15;
	const char q = 16;
	const char r = 17;
	const char s = 18;
	const char t = 19;
	const char u = 20;
	const char v = 21;
	const char w = 22;
	const char x = 23;
	const char y = 24;
	const char z = 25;

	char wheels[][26] = {
		{e, k, m, f, l, g, d, q, v, z, n, t, o, w, y, h, x, u, s, p, a, i, b, r, c, j}, // rotor I
		{a, j, d, k, s, i, r, u, x, b, l, h, w, t, m, c, q, g, z, n, p, y, f, v, o, e}, // rotor II
		{b, d, f, h, j, l, c, p, r, t, x, v, z, n, y, e, i, w, g, a, k, m, u, s, q, o}, // rotor III
		{e, s, o, v, p, z, j, a, y, q, u, i, r, h, x, l, n, f, t, g, k, d, c, m, w, b}, // rotor IV
		{v, z, b, r, g, i, t, y, u, p, s, d, n, h, l, x, a, w, m, j, q, o, f, e, c, k}  // rotor V
	};

	char notch[] = { // The letter upon which the rotor forces the one to its left to rotate.
		q, // rotor I
		e, // rotor II
		v, // rotor III
		j, // rotor IV
		z  // rotor V
	};
}