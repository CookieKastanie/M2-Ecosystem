#pragma once

class Random {
public:
	static void init();
	static float generate();
	static bool greaterThan(float value);
	static int rangeInt(int min, int max);
	static int rangeInt(int range[2]);
};
