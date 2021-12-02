#ifndef TRAXPARSER_PARSER_H
#define TRAXPARSER_PARSER_H


#include <set>

enum TraxIDs {
    kHeading = 5,
    kPitch = 24,
    kRoll = 25,
    kHeadingStatus = 79,
    kQuaternion = 77,
    kTemperature = 7,
    kDistortion = 8,
    kCalStatus = 9,
    kAccelX = 21,
    kAccelY = 22,
    kAccelZ = 23,
    kMagX = 27,
    kMagY = 28,
    kMagZ = 29,
    kGyroX = 74,
    kGyroY = 75,
    kGyroZ = 76
};

#pragma pack(push, 1)

typedef struct {
    float kHeading;
    float kPitch;
    float kRoll;
    char kHeadingStatus;
    float kQuaternion[4];
    float kTemperature;
    bool kDistortion;
    bool kCalStatus;
    float kAccelX;
    float kAccelY;
    float kAccelZ;
    float kMagX;
    float kMagY;
    float kMagZ;
    float kGyroX;
    float kGyroY;
    float kGyroZ;
} TraxDataStruct;

#pragma pack(pop)

std::pair<TraxDataStruct, std::set<int>> parse_trax_data(unsigned char *data, size_t n);


#endif //TRAXPARSER_PARSER_H
