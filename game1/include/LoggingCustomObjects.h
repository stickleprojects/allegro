#ifndef LOGGINGCUSTOMOBJECTS_H_
#define LOGGINGCUSTOMOBJECTS_H_

#include <spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

std::ostream& operator<<(std::ostream& os, const ALLEGRO_EVENT& e);
std::ostream& operator<<(std::ostream& os, const ALLEGRO_COLOR& c);

#endif   // LOGGINGCUSTOMOBJECTS_H_
