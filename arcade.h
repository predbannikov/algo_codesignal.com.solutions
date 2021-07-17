#pragma once

int centuryFromYear(int year) {
	if (!(year % 10) && year > 99)
		return year / 100;
	return year / 100 + 1;
}

void testArcade() {
	std::cout << centuryFromYear(2005) << std::endl;
}