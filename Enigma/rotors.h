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

	const char forwardrotors[][26] = {
		/*
				{a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z}
		*/
				{e, k, m, f, l, g, d, q, v, z, n, t, o, w, y, h, x, u, s, p, a, i, b, r, c, j}, // rotor I
				{a, j, d, k, s, i, r, u, x, b, l, h, w, t, m, c, q, g, z, n, p, y, f, v, o, e}, // rotor II
				{b, d, f, h, j, l, c, p, r, t, x, v, z, n, y, e, i, w, g, a, k, m, u, s, q, o}, // rotor III
				{e, s, o, v, p, z, j, a, y, q, u, i, r, h, x, l, n, f, t, g, k, d, c, m, w, b}, // rotor IV
				{v, z, b, r, g, i, t, y, u, p, s, d, n, h, l, x, a, w, m, j, q, o, f, e, c, k}  // rotor V
	};

	/*
	So, get this:
	When the signal goes backwards through the machine, it actually ends up going... backwards.
	Meaning that a naïve implementation for going backwards would have to be, a for-loop using the above forwardrotors thing
	that finds, like, which one has the A as its value and then returns that index, instead of an easy constant-time access.
	Instead of that, I generated a quick lua script to run through that process for us and have pasted its result here, to be held constant for our program.
	*/
	const char backwardrotors[][26] = {
		{u, w, y, g, a, d, f, p, v, z, b, e, c, k, m, t, h, x, s, l, r, i, n, q, o, j}, // rotor I
		{a, j, p, c, z, w, r, l, f, b, d, k, o, t, y, u, q, g, e, n, h, x, m, i, v, s}, // rotor II
		{t, a, g, b, p, c, s, d, q, e, u, f, v, n, z, h, y, i, x, j, w, l, r, k, o, m}, // rotor III
	};

	const char notch[] = { // The letter upon which the rotor forces the one to its left to rotate.
		r, // rotor I
		f, // rotor II
		w, // rotor III
		k, // rotor IV
		a  // rotor V
	};

	//When the rotors bounce back through themselves, they first stop at the (static) reflector.
	//The reflector implemented below is the UKW-B, the model used by Germany during most of WW2.
	//This array remains multidimensional in case we implement alternative reflectors.
	const char reflectors[][26] =
	{
		{y, r, u, h, q, s, l, d, p, x, n, g, o, k, m, i, e, b, f, z, c, w, v, j, a, t}
	};

	char constexpr to_char(size_t x)
	{
		return char(x + 65);
	}
	char constexpr to_char(char x)
	{
		return char(x + 65);
	}
}