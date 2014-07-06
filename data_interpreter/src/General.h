#pragma once

#include <stdint.h>

class DateTime{
public:
	uint16_t year() const{ return 2000 + yOff; };
	uint8_t month() const{ return m; };
	uint8_t day() const{ return d; };
	uint8_t hour() const{ return hh; };
	uint8_t minute() const{ return mm; };
	uint8_t second() const{ return ss; };
protected:
	uint8_t yOff, m, d, hh, mm, ss;
};

struct Reading{
	float temperature;
	DateTime date;
};

char *getInput(int);
