#ifndef MISSIONS_PLANNER_H
#define MISSIONS_PLANNER_H


#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

#include "mission.h"


namespace {
    constexpr double X_MAX = 10000;
    constexpr double Y_MAX = 10000;
    constexpr double DEPTH_MAX = 100;
}

class Planner {
public:
    static double base_x;
    static double base_y;
    static double base_depth;

    Planner(double x, double y, double depth);

    bool add_mission(std::unique_ptr<Mission> mission);

    void save_to_file();

    void print_plan() {
        std::cout << serialize_missions();
    }

    bool delete_mission(size_t pos) {
        pos -= 1;
        if (pos < plan_.size()) {
            plan_.erase(plan_.begin() + static_cast<int>(pos));
            return true;
        }
        return false;
    }

    bool swap_missions(size_t pos1, size_t pos2) {
        pos1 -= 1;
        pos2 -= 1;
        if (std::max(pos1, pos2) < plan_.size()) {
            std::swap(plan_[pos1], plan_[pos2]);
            return true;
        }
        return false;
    }

    std::string serialize_missions();

private:
    void open_clear() {
        if (of_.is_open()) {
            of_.close();
        }
        of_.open("plan.txt", std::ofstream::out | std::ofstream::trunc);
    }

    std::vector<std::unique_ptr<Mission>> plan_;
    std::ofstream of_;
};


#endif //MISSIONS_PLANNER_H
