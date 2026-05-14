#ifndef POINTCLOUD_H_
#define POINTCLOUD_H_

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

class PointCloud {
public:
    void Init(std::string pc_type, size_t points_count) {
        pointcloud_type_ = std::move(pc_type);
        size_ = points_count;

        if (pointcloud_type_ == "XYZIR") {
            point_size_ = 5;
        } else if (pointcloud_type_ == "XYZIRDAT") {
            point_size_ = 8;
        } else {
            throw std::runtime_error("unknown pointcloud type");
        }

        points_.assign(size_ * point_size_, 0.0);
    }

    void AddPoint(const std::vector<double>& point, size_t ind) {
        if ((pointcloud_type_ == "XYZIR" && point.size() != 5) ||
            (pointcloud_type_ == "XYZIRDAT" && point.size() != 8)) {
            throw std::runtime_error("Point has unsupported size = " +
                                     std::to_string(point.size()) + " for type " + pointcloud_type_);
        }

        const auto offset = point_size_ * ind;
        std::copy(point.begin(), point.end(), points_.begin() + offset);
    }

    std::string pointcloud_type_{""};
    size_t size_ = 0;
    size_t point_size_ = 0;
    std::vector<double> points_;
};

inline void FillPointCloud(PointCloud* pc, size_t points_count, const std::string& point_type, const std::vector<double>& data) {
    const size_t point_size = (point_type == "XYZIR") ? 5 : 8;
    pc->Init(point_type, points_count);

    for (size_t ind = 0; ind < points_count; ++ind) {
        const auto first = ind * point_size;
        pc->AddPoint(std::vector<double>(data.begin() + first, data.begin() + first + point_size), ind);
    }
}

#endif //POINTCLOUD_H_
