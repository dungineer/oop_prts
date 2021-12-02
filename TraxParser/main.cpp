#include <iostream>
#include <vector>
#include <sstream>

#include "parser.h"

template<typename T>
std::string print_if(T t, bool is_set) {
    std::stringstream ss;
    ss << std::boolalpha;
    if (is_set) {
        ss << t;
    } else {
        ss << '-';
    }
    return ss.str();
}

template<typename T>
std::string print_if(T *t_ar, size_t t_ar_size, bool is_set) {
    std::stringstream ss;
    ss << std::boolalpha;
    if (is_set) {
        ss << '[';
        for (size_t i = 0; i < t_ar_size - 1; ++i) {
            ss << t_ar[i] << ", ";
        }
        ss << t_ar[t_ar_size - 1];
        ss << ']';
    } else {
        ss << '-';
    }
    return ss.str();
}

void print_tds(std::pair<TraxDataStruct, std::set<int>> tds) {
    std::cout << "kHeading:       " << print_if(tds.first.kHeading, tds.second.count(kHeading)) << "\n";
    std::cout << "kPitch:         " << print_if(tds.first.kPitch, tds.second.count(kPitch)) << "\n";
    std::cout << "kRoll:          " << print_if(tds.first.kRoll, tds.second.count(kRoll)) << "\n";
    std::cout << "kHeadingStatus: " << print_if(static_cast<int>(tds.first.kHeadingStatus), \
        tds.second.count(kHeadingStatus)) << "\n";
    std::cout << "kQuaternion:    " << print_if(tds.first.kQuaternion, sizeof(tds.first.kQuaternion) / \
        sizeof(tds.first.kQuaternion[0]), tds.second.count(kQuaternion)) << "\n";
    std::cout << "kTemperature:   " << print_if(tds.first.kTemperature, tds.second.count(kTemperature)) << "\n";
    std::cout << "kDistortion:    " << print_if(tds.first.kDistortion, tds.second.count(kDistortion)) << "\n";
    std::cout << "kCalStatus:     " << print_if(tds.first.kCalStatus, tds.second.count(kCalStatus)) << "\n";
    std::cout << "kAccelX:        " << print_if(tds.first.kAccelX, tds.second.count(kAccelX)) << "\n";
    std::cout << "kAccelY:        " << print_if(tds.first.kAccelY, tds.second.count(kAccelY)) << "\n";
    std::cout << "kAccelZ:        " << print_if(tds.first.kAccelZ, tds.second.count(kAccelZ)) << "\n";
    std::cout << "kMagX:          " << print_if(tds.first.kMagX, tds.second.count(kMagX)) << "\n";
    std::cout << "kMagY:          " << print_if(tds.first.kMagY, tds.second.count(kMagY)) << "\n";
    std::cout << "kMagZ:          " << print_if(tds.first.kMagZ, tds.second.count(kMagZ)) << "\n";
    std::cout << "kGyroX:         " << print_if(tds.first.kGyroX, tds.second.count(kGyroX)) << "\n";
    std::cout << "kGyroY:         " << print_if(tds.first.kGyroY, tds.second.count(kGyroY)) << "\n";
    std::cout << "kGyroZ:         " << print_if(tds.first.kGyroZ, tds.second.count(kGyroZ)) << "\n";
}

std::vector<std::vector<unsigned char>> tests{
        // Test 1
        {0x05, 0x3F, 0x80, 0x00, 0x00, 0x09, 0x01, 0x1C, 0x40, 0x00, 0x00, 0x00},
        // Test 2
        {0x4C, 0x41, 0xA4, 0x00, 0x00, 0x4B, 0x3F, 0x91, 0xBC, 0xD8},
        // Test 3
        {0x07, 0x41, 0xA4, 0x00, 0x00, 0x05, 0x3F, 0x91, 0xBC, 0xD8, 0x19, 0x41, 0x35, 0x47, 0xAE},
        // Test 4
        {0x05, 0x43, 0x0D, 0x08, 0x3B, 0x18, 0x3F, 0x91, 0xBC, 0xD8, 0x19, 0x3E, 0xDF, 0x4D, 0xE9, 0x4D, 0x42, 0x28, \
            0x69, 0xE2, 0x41, 0xF8, 0xF5, 0xC3, 0x41, 0xDE, 0xC2, 0x8F, 0x3C, 0x59, 0x4D, 0x0E},
        // Test 5
        {0x05, 0x43, 0x0D, 0x08, 0x3B, 0x18, 0x3F, 0x91, 0xBC, 0xD8, 0x19, 0x3E, 0xDF, 0x4D, 0xE9, 0x4F, 0x00, 0x08, \
            0x00, 0x15, 0xBC, 0xA4, 0x08, 0xC0, 0x16, 0x3B, 0xFB, 0x4D, 0xAB, 0x17, 0x3F, 0x80, 0xF5, 0x08, 0x1B, \
            0xC1, 0x6E, 0xA4, 0x37, 0x1C, 0xC1, 0x2D, 0x31, 0x27, 0x1D, 0x42, 0x51, 0x3D, 0x4F, 0x4A, 0x00, 0x00, \
            0x00, 0x00, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x4C, 0x00, 0x00, 0x00, 0x00}
};

int main() {
    for (size_t i = 0; i < tests.size(); ++i) {
        std::cout << "Test " << i + 1 << "\n";
        std::cout << "------------------------------\n";
        print_tds(parse_trax_data(tests[i].data(), tests[i].size()));
        std::cout << "------------------------------\n\n";
    }

    return 0;
}
