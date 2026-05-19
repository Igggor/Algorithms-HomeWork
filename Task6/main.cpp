#include "check_point.h"
#include "text_report_builder.h"
#include "penalty_sum_builder.h"
#include "rally_director.h"
#include <iostream>
#include <vector>
#include <memory>
#include <clocale>

int main() {
    setlocale(LC_ALL, "");

    std::vector<std::unique_ptr<CheckPoint>> points;

    points.push_back(std::make_unique<MandatoryCheckPoint>("Старт", Coordinates{55.7558, 37.6176}));
    points.push_back(std::make_unique<OptionalCheckPoint>("Лесной участок", Coordinates{55.7512, 37.6184}, 1.5));
    points.push_back(std::make_unique<MandatoryCheckPoint>("Мост", Coordinates{55.7483, 37.6201}));
    points.push_back(std::make_unique<OptionalCheckPoint>("Болото", Coordinates{55.7445, 37.6237}, 2.0));
    points.push_back(std::make_unique<MandatoryCheckPoint>("Финиш", Coordinates{55.7400, 37.6300}));

    RallyDirector rallyController;

    TextReportBuilder textReport;
    rallyController.process(points, textReport);
    std::cout << "ТЕКСТОВЫЙ ОТЧЁТ:\n"
              << textReport.getResult() << std::endl;

    PenaltySumBuilder penaltyCalculator;
    rallyController.process(points, penaltyCalculator);
    std::cout << penaltyCalculator.getResult() << std::endl;

    return 0;
}