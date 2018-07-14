#include <stdio.h>

#include "Utils/cli.h"
#include "Utils/commands.h"

void rtc_debug(uint8_t argc, char **argv);
const sTermEntry_t rtcEntry =
{ "date", "RTC date", rtc_debug };

void nrf(uint8_t argc, char **argv);
const sTermEntry_t nrfEntry =
{ "n", "NRF status", nrf };


const sTermEntry_t *cli_entries[] =
{
      &hEntry,
      &helpEntry,
      &rebootEntry,
      &bootEntry,
	  &rtcEntry,
	  &nrfEntry,
      0
};
