#include <LoggingCustomObjects.h>

std::ostream& operator<<(std::ostream& os, const ALLEGRO_EVENT& e) {
    return os << e.type;
}

std::ostream& operator<<(std::ostream& os, const ALLEGRO_COLOR& c) {
    return os << c.r << c.g << c.b;
}
