#include "rally_director.h"
#include "check_point.h"
#include "report_builder.h"

void RallyDirector::process(const std::vector<std::unique_ptr<CheckPoint>> &points,
                            ReportBuilder &reportBuilder)
{
    for (size_t idx = 0; idx < points.size(); ++idx)
    {
        reportBuilder.addCheckPoint(static_cast<int>(idx + 1), *points[idx]);
    }
}