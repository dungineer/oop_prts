#include "mission.h"


std::string Mission::coordinates_str() const {
    std::stringstream ss;
    ss << "x: " << x_ << " y: " << y_ << " depth: " << depth_;
    return ss.str();
}

std::string LiftDive::coordinates_str() const {
    std::stringstream ss;
    ss << "depth: " << depth_;
    return ss.str();
}

std::string Move::coordinates_str() const {
    std::stringstream ss;
    ss << "x: " << x_ << " y: " << y_;
    return ss.str();
}

std::string Lift::serialize() {
    std::stringstream ss;
    ss << "Lift\n"
       << "    To:          " << coordinates_str() << "\n"
       << "    Depth mode:  " << static_cast<int>(depth_mode_) << " ";
    if (depth_mode_ == DepthMode::Depth) {
        ss << "(depth from the surface)\n";
    } else {
        ss << "(distance from the bottom of the sea)\n";
    }
    ss << "    Lift mode:   " << static_cast<int>(lift_dive_mode_) << " ";
    if (lift_dive_mode_ == LiftMode::Vertical) {
        ss << "(vertical lift)\n";
    } else {
        ss << "(spiral lift)\n";
    }
    return ss.str();
}

std::string Dive::serialize() {
    std::stringstream ss;
    ss << "Dive\n"
       << "    To:          " << coordinates_str() << "\n"
       << "    Depth mode:  " << static_cast<int>(depth_mode_) << " ";
    if (depth_mode_ == DepthMode::Depth) {
        ss << "(depth from the surface)\n";
    } else {
        ss << "(distance from the bottom of the sea)\n";
    }
    ss << "    Lift mode:   " << static_cast<int>(lift_dive_mode_) << " ";
    if (lift_dive_mode_ == DiveMode::Vertical) {
        ss << "(vertical dive)\n";
    } else {
        ss << "(spiral dive)\n";
    }
    return ss.str();
}

std::string Move::serialize() {
    std::stringstream ss;
    ss << "Move\n"
       << "    To:          " << coordinates_str() << "\n"
       << "    Accuracy:    " << accuracy_ << "\n"
       << "    Depth mode:  " << static_cast<int>(depth_mode_) << " ";
    if (depth_mode_ == DepthMode::Depth) {
        ss << "(depth from the surface)\n";
    } else {
        ss << "(distance from the bottom of the sea)\n";
    }
    ss << "    Move mode:   " << static_cast<int>(move_mode_) << " ";
    if (move_mode_ == MoveMode::Stay) {
        ss << "(stay at the target point)\n";
    } else {
        ss << "(keep moving among the line)\n";
    }
    return ss.str();
}

std::string Return::serialize() {
    std::stringstream ss;
    ss << "Return\n"
       << "    To:   " << coordinates_str() << "\n";
    return ss.str();
}
