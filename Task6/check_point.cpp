#include "check_point.h"
#include <sstream>
#include <iomanip>

CheckPoint::CheckPoint(const std::string &name, const Coordinates &coords) : label(name), position(coords) {}

std::string CheckPoint::getName() const {
    return label;
}

Coordinates CheckPoint::getCoords() const {
    return position;
}

MandatoryCheckPoint::MandatoryCheckPoint(const std::string &name, const Coordinates &coords) : CheckPoint(name, coords) {}

std::string MandatoryCheckPoint::getPenaltyString() const {
    return "незачёт СУ";
}

double MandatoryCheckPoint::getPenaltyValue() const {
    return 0.0;
}

OptionalCheckPoint::OptionalCheckPoint(const std::string &name, const Coordinates &coords, double penaltyHours) : CheckPoint(name, coords), penaltyHours(penaltyHours) {}

std::string OptionalCheckPoint::getPenaltyString() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << penaltyHours << " ч";
    return oss.str();
}

double OptionalCheckPoint::getPenaltyValue() const {
    return penaltyHours;
}