#include "stdafx.h"
#include "Utils.h"

int Utils::Clamp(int pNumber, int pMin, int pMax) {
	return pNumber < pMin ? pMin : (pNumber > pMax ? pMax : pNumber);

}