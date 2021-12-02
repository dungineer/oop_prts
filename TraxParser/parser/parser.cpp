#include "parser.h"

#include "swap_endian.h"

#include <vector>
#include <utility>
#include <unordered_map>


namespace {
    using TDS = TraxDataStruct;

    const std::unordered_map<int, std::pair<int, int>> TDT{
            {kHeading,       {sizeof(TDS::kHeading),       offsetof(TDS, kHeading)}},
            {kPitch,         {sizeof(TDS::kPitch),         offsetof(TDS, kPitch)}},
            {kRoll,          {sizeof(TDS::kRoll),          offsetof(TDS, kRoll)}},
            {kHeadingStatus, {sizeof(TDS::kHeadingStatus), offsetof(TDS, kHeadingStatus)}},
            {kQuaternion,    {sizeof(TDS::kQuaternion),    offsetof(TDS, kQuaternion)}},
            {kTemperature,   {sizeof(TDS::kTemperature),   offsetof(TDS, kTemperature)}},
            {kDistortion,    {sizeof(TDS::kDistortion),    offsetof(TDS, kDistortion)}},
            {kCalStatus,     {sizeof(TDS::kCalStatus),     offsetof(TDS, kCalStatus)}},
            {kAccelX,        {sizeof(TDS::kAccelX),        offsetof(TDS, kAccelX)}},
            {kAccelY,        {sizeof(TDS::kAccelY),        offsetof(TDS, kAccelY)}},
            {kAccelZ,        {sizeof(TDS::kAccelZ),        offsetof(TDS, kAccelZ)}},
            {kMagX,          {sizeof(TDS::kMagX),          offsetof(TDS, kMagX)}},
            {kMagY,          {sizeof(TDS::kMagY),          offsetof(TDS, kMagY)}},
            {kMagZ,          {sizeof(TDS::kMagZ),          offsetof(TDS, kMagZ)}},
            {kGyroX,         {sizeof(TDS::kGyroX),         offsetof(TDS, kGyroX)}},
            {kGyroY,         {sizeof(TDS::kGyroY),         offsetof(TDS, kGyroY)}},
            {kGyroZ,         {sizeof(TDS::kGyroZ),         offsetof(TDS, kGyroZ)}}
    };
}

std::pair<TraxDataStruct, std::set<int>> parse_trax_data(unsigned char *data, size_t n) {
    TDS result{};
    std::set<int> res_ids;
    for (int i = 0; i < n; ++i) {
        res_ids.insert(static_cast<int>(data[i]));
        int size = TDT.at(data[i]).first;
        int offset = TDT.at(data[i]).second;

        swap_endian_float_array((float *) (data + i + 1), size / 4);
        std::memcpy((unsigned char *) &result + offset, data + i + 1, size);
        i += size;
    }
    return {result, res_ids};
}
