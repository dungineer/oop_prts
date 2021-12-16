#include <iostream>
#include <sstream>

#include "mission.h"
#include "planner.h"

int main() {
    auto input = std::string{};
    double base_x{}, base_y{}, base_depth{};
    std::cout << "Type `?` or `help` to get command list\n";
    std::cout << "Enter start coordinates:\n";
    std::cout << "x0 =";
    std::cin >> base_x;
    std::cout << "y0 =";
    std::cin >> base_y;
    std::cout << "depth0 =";
    std::cin >> base_depth;
    if (base_x > X_MAX || base_x < 0 ||
        base_y > Y_MAX || base_y < 0 ||
        base_depth > DEPTH_MAX || base_depth < 0) {
        std::cerr << "Incorrect base coordinates provided!\n";
        std::exit(1);
    }
    Planner planner{base_x, base_y, base_depth};
    std::cout << ">>";

    while (true) {
        std::cin >> input;
        if (input == "?" || input == "help") {
            std::stringstream ss;
            ss << "<mission_name> - add one of the following missions:\n"
               << "                     lift, dive, move, return\n"
               << "`delete`       - remove one of the missions\n"
               << "`swap`         - swap missions\n"
               << "`exit`         - write to file and exit\n"
               << "`save`         - write to file\n"
               << "`print`        - print missions\n";
            std::cout << ss.str();
        } else if (input == "delete") {
            int number{};
            std::cout << "Enter mission number:\n"
                      << "mission ¹=";
            std::cin >> number;
            if (planner.delete_mission(number)) {
                std::cout << "Mission " << number << " deleted\n";
            } else {
                std::cout << "Wrong number provided\n";
            }
        } else if (input == "swap") {
            int number1{};
            int number2{};
            std::cout << "Enter mission numbers:\n"
                      << "First mission N=";
            std::cin >> number1;
            std::cout << "Enter mission numbers:\n"
                      << "Second mission N=";
            std::cin >> number2;
            if (planner.swap_missions(number1, number2)) {
                std::cout << "Swapped missions " << number1
                          << " and " << number2 << "\n";
            } else {
                std::cout << "Wrong numbers provided\n";
            }
        } else if (input == "lift" || input == "dive") {
            std::cout << "Creating mission: " << input << "\n";
            // Get new depth
            std::cout << "Enter new depth:\n"
                      << "depth =";
            double depth{};
            std::cin >> depth;

            auto mission_type = input;
            // Create mission
            std::unique_ptr<LiftDive> lift_dive;
            if (mission_type == "lift") {
                lift_dive = std::make_unique<Lift>(depth);
            } else {
                lift_dive = std::make_unique<Dive>(depth);
            }

            // Ask if values if OK
            std::cout << "-----------\n";
            std::cout << "New mission: " << mission_type << "\n"
                      << lift_dive->serialize()
                      << "Commands to configure the mission:\n"
                      << "    `add` to add mission\n"
                      << "    `dmode` to set depth mode\n"
                      << "    `vmode` to set " << mission_type << " mode\n"
                      << "    `print` to print mission values\n"
                      << "    `stop` to abort creation\n"
                      << "new " << mission_type << ">>";


            auto confirmed = false;
            while (true) {
                std::cin >> input;
                if (input == "add") {
                    confirmed = true;
                    break;
                } else if (input == "dmode") {
                    // Get depth mode
                    int depth_mode{};
                    std::cout << "Enter depth mode:\n"
                              << "    " << static_cast<int>(Mission::DepthMode::Depth)
                              << " - distance from surface\n"
                              << "    " << static_cast<int>(Mission::DepthMode::Offset)
                              << " - distance from bottom of the sea\n"
                              << "dmode =";
                    std::cin >> depth_mode;
                    lift_dive->set_depth_mode(static_cast<Mission::DepthMode>(depth_mode));
                } else if (input == "vmode") {
                    // Get lift mode
                    int lift_dive_mode{};
                    std::cout << "Enter " << mission_type << " mode:\n"
                              << "    " << static_cast<int>(LiftDive::LiftDiveMode::Vertical)
                              << " - vertical " << mission_type << "\n"
                              << "    " << static_cast<int>(LiftDive::LiftDiveMode::Spiral)
                              << " - spiral " << mission_type << "\n"
                              << "vmode =";
                    std::cin >> lift_dive_mode;
                    lift_dive->set_lift_dive_mode(static_cast<LiftDive::LiftDiveMode>(lift_dive_mode));
                } else if (input == "print") {
                    std::cout << lift_dive->serialize();
                } else if (input == "stop") {
                    break;
                } else if (input == "?" || input == "help") {
                    std::cout << "Commands to configure the mission:\n"
                              << "    `add` to add mission\n"
                              << "    `dmode` to set depth mode\n"
                              << "    `vmode` to set " << mission_type << " mode\n"
                              << "    `print` to print mission values\n"
                              << "    `stop` to abort creation\n";
                } else {
                    std::cout << "Unknown command. Type `stop` to abort.\n";
                }
                std::cout << "new " << mission_type << ">>";
            }
            // Add mission to the plan
            if (confirmed) {
                if (planner.add_mission(std::move(lift_dive))) {
                    std::cout << "Added new mission: " << mission_type << "\n";
                } else {
                    std::cout << "Coordinates are incorrect!\n";
                }
            }
        } else if (input == "move") {
            std::cout << "Creating mission: " << input << "\n";
            // Get new x, y
            double x{};
            std::cout << "Enter new x:\n"
                      << "x =";
            std::cin >> x;
            double y{};
            std::cout << "Enter new y:\n"
                      << "y =";
            std::cin >> y;

            auto mission_type = input;
            // Create mission
            auto move = std::make_unique<Move>(x, y);

            // Ask if values if OK
            std::cout << "-----------\n";
            std::cout << "New mission: " << mission_type << "\n"
                      << move->serialize()
                      << "Commands to configure the mission:\n"
                      << "    `add` to add mission\n"
                      << "    `dmode` to set depth mode\n"
                      << "    `mmode` to set " << mission_type << " mode\n"
                      << "    `accuracy` to set accuracy\n"
                      << "    `print` to print mission values\n"
                      << "    `stop` to abort creation\n"
                      << "new " << mission_type << ">>";

            auto confirmed = false;
            while (true) {
                std::cin >> input;
                if (input == "add") {
                    confirmed = true;
                    break;
                } else if (input == "dmode") {
                    // Get depth mode
                    int depth_mode{};
                    std::cout << "Enter depth mode:\n"
                              << "    " << static_cast<int>(Mission::DepthMode::Depth)
                              << " - distance from surface\n"
                              << "    " << static_cast<int>(Mission::DepthMode::Offset)
                              << " - distance from bottom of the sea\n"
                              << "dmode =";
                    std::cin >> depth_mode;
                    move->set_depth_mode(static_cast<Mission::DepthMode>(depth_mode));
                } else if (input == "mmode") {
                    // Get lift mode
                    int move_mode{};
                    std::cout << "Enter " << mission_type << " mode:\n"
                              << "    " << static_cast<int>(Move::MoveMode::Stay)
                              << " - stay at the target point\n"
                              << "    " << static_cast<int>(Move::MoveMode::Proceed)
                              << " - keep moving among the line\n"
                              << "mmode =";
                    std::cin >> move_mode;
                    move->set_move_mode(static_cast<Move::MoveMode>(move_mode));
                } else if (input == "accuracy") {
                    // Get accuracy
                    double accuracy{};
                    std::cout << "Enter accuracy:\n"
                              << "accuracy =";
                    std::cin >> accuracy;
                    move->set_accuracy(accuracy);
                } else if (input == "print") {
                    std::cout << move->serialize();
                } else if (input == "stop") {
                    break;
                } else if (input == "?" || input == "help") {
                    std::cout << "Commands to configure the mission:\n"
                              << "    `add` to add mission\n"
                              << "    `dmode` to set depth mode\n"
                              << "    `mmode` to set " << mission_type << " mode\n"
                              << "    `accuracy` to set accuracy\n"
                              << "    `print` to print mission values\n"
                              << "    `stop` to abort creation\n";
                } else {
                    std::cout << "Unknown command. Type `stop` to abort.\n";
                }
                std::cout << "new " << mission_type << ">>";
            }
            // Add mission to the plan
            if (confirmed) {
                if (planner.add_mission(std::move(move))) {
                    std::cout << "Added new mission: " << mission_type << "\n";
                } else {
                    std::cout << "Coordinates are incorrect!\n";
                }
            }
        } else if (input == "return") {
            std::cout << "Creating mission: " << input << "\n";
            auto ret_mission = std::make_unique<Return>(Planner::base_x,
                                                        Planner::base_y,
                                                        Planner::base_depth);
            // Ask if values if OK
            std::cout << "-----------\n";
            std::cout << "New mission: " << input << "\n"
                      << ret_mission->serialize()
                      << "Add this mission?\n[y/n]:";
            char agreement{};
            std::cin >> agreement;
            // Add mission to the plan
            if (agreement == 'y') {
                planner.add_mission(std::move(ret_mission));
            }
        } else if (input == "save") {
            planner.save_to_file();
        } else if (input == "print") {
            planner.print_plan();
        } else if (input == "exit") {
            planner.save_to_file();
            break;
        } else {
            std::cout << "Unknown command: `" << input << "` , use `?` or `help` to get command list\n";
        }
        std::cout << ">>";
    }
    return 0;
}
