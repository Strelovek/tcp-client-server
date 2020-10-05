#ifndef TVLENCODER_H
#define TVLENCODER_H
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>

namespace TVLEncoder
{
    enum lengthForms
    {
        shortForm = 0,
        longForm = 1
    };
    std::vector<uint8_t> encode(uint64_t length, lengthForms form);
    uint64_t decode(std::vector<uint8_t> data);
}; // namespace TVLEncoder
#endif