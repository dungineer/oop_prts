#ifndef MISSIONS_MISSION_H
#define MISSIONS_MISSION_H


#include <string>
#include <sstream>


class Mission {
public:
    enum class DepthMode : int {
        Depth,
        Offset
    };

    virtual ~Mission() = default;

    virtual std::string serialize() = 0;

    void set_depth_mode(DepthMode depth_mode) {
        depth_mode_ = depth_mode;
    }

    double get_x() const {
        return x_;
    }

    double get_y() const {
        return y_;
    }

    double get_depth() const {
        return depth_;
    }

protected:
    virtual std::string coordinates_str() const;

    DepthMode depth_mode_ = DepthMode::Depth;

    double x_ = 0.0;
    double y_ = 0.0;
    double depth_ = 0.0;
};

class LiftDive : public Mission {
public:
    enum class LiftDiveMode : int {
        Vertical,
        Spiral
    };

    explicit LiftDive(double depth) {
        depth_ = depth;
    }

    void set_lift_dive_mode(LiftDiveMode lift_dive_mode) {
        lift_dive_mode_ = lift_dive_mode;
    }

protected:
    std::string coordinates_str() const override;

    LiftDiveMode lift_dive_mode_ = LiftDiveMode::Vertical;
};

class Dive : public LiftDive {
public:
    using LiftDive::LiftDive;
    using DiveMode = LiftDiveMode;

    std::string serialize() override;
};

class Lift : public LiftDive {
public:
    using LiftDive::LiftDive;
    using LiftMode = LiftDiveMode;

    std::string serialize() override;
};

class Move : public Mission {
public:
    enum class MoveMode : int {
        Stay,
        Proceed
    };

    explicit Move(double x, double y) {
        x_ = x;
        y_ = y;
    }

    std::string serialize() override;

    void set_move_mode(MoveMode move_mode) {
        move_mode_ = move_mode;
    }

    void set_accuracy(double accuracy) {
        accuracy_ = accuracy;
    }

protected:
    std::string coordinates_str() const override;

    MoveMode move_mode_ = MoveMode::Stay;

    double accuracy_ = 1.0; // Meters
};

class Return : public Mission {
public:
    Return(double base_x, double base_y, double base_depth) {
        x_ = base_x;
        y_ = base_y;
        depth_ = base_depth;
    }

    std::string serialize() override;
};

#endif //MISSIONS_MISSION_H
