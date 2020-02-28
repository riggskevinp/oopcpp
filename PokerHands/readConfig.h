#ifndef READCONFIG_H
#define READCONFIG_H

#include "card.h"

#ifdef _WIN32
#define LIBCONFIG_STATIC
#include <../../libconfig/lib/libconfig.h++>
#endif

#include <string>
#include <vector>

std::vector<Card> readConfig(const std::string& str);

#endif // READCONFIG_H
