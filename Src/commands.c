#include <stdio.h>

#include "Utils/cli.h"
#include "Utils/commands.h"

const sTermEntry_t *cli_entries[] =
{
      &hEntry,
      &helpEntry,
      &rebootEntry,
      &bootEntry,
      0
};
