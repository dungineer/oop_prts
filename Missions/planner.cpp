#include "planner.h"

#include <sstream>


double Planner::base_x = 0.0;
double Planner::base_y = 0.0;
double Planner::base_depth = 0.0;

Planner::Planner(double x, double y, double depth) {
    if (x > X_MAX || x < 0 ||
        y > Y_MAX || y < 0 ||
        depth > DEPTH_MAX || depth < 0) {
        throw std::runtime_error("Coordinates are incorrect!");
    }
    base_x = x;
    base_y = y;
    base_depth = depth;
}

bool Planner::add_mission(std::unique_ptr<Mission> mission) {
    if (mission->get_x() > X_MAX || mission->get_x() < 0 ||
        mission->get_y() > Y_MAX || mission->get_y() < 0 ||
        mission->get_depth() > DEPTH_MAX || mission->get_depth() < 0) {
        return false;
    }
    plan_.emplace_back(std::move(mission));
    return true;
}

std::string Planner::serialize_missions() {
    std::stringstream ss;
    for (size_t i = 0; i < plan_.size(); ++i) {
        ss << "[ Mission " << i + 1 << " ]\n";
        ss << plan_[i]->serialize();
        ss << "\n";
    }
    return ss.str();
}

void Planner::save_to_file() {
    if (plan_.empty()) {
        return;
    }

    if (!dynamic_cast<Return *>(&(*plan_.back()))) {
        add_mission(std::make_unique<Return>(base_x, base_y, base_depth));
        std::cout << "No return mission provided at the end.\n"
                  << "Adding new return mission:\n"
                  << plan_.back()->serialize();
    }
    open_clear();
    auto plan_str = serialize_missions();
    of_.write(plan_str.c_str(), plan_str.size());
    of_.close();
}
