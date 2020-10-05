#include "TVLEncoder.h"
#include <cstdint>
#include <cmath>

std::vector<uint8_t> TVLEncoder::encode(uint64_t length, lengthForms form)
{
    /*
        У этой функции есть ограничение на кодируемый размер для полной формы.
        Он не должен превышать UINT64_MAX что меньше, чем прописано в стандарте.
    */
    std::vector<uint8_t> data;
    if (form == shortForm)
    {
        if (length > 127)
        {
            throw std::out_of_range("variable length out of range");
        }
        data.reserve(1);
        data.insert(data.begin(), 0b00000000 | static_cast<uint8_t>(length));
    }
    else
    {
        if (length == 0)
        {
            data.reserve(2);
            data.push_back(0b10000001);
            data.push_back(0);
            return data;
        }
        uint64_t octets = 1 + log2f(length) / 8;
        data.reserve(octets + 1);
        while (length != 0) //Перевод длины в систему счисления с основанием 256.
        {
            if (length > 256)
            {
                int t = length / 256;
                data.insert(data.begin(), length - (t * 256));
                length = t;
            }
            else
            {
                data.insert(data.begin(), length);
                length = 0;
            }
        }
        data.insert(data.begin(), 0b10000000 | octets);
    }
    return data;
}

uint64_t TVLEncoder::decode(std::vector<uint8_t> data)
{
    /*
        Функция имеет ограничение на декодируемый размер для полной формы равный UINT64_MAX.
    */
    uint64_t length = 0;
    int currentOctet = 0;
    uint8_t octet = data[currentOctet];
    if (octet >> 7 == TVLEncoder::longForm)
    {
        if (data.size() < 2 || data.size() == UINT64_MAX)
        {
            throw std::out_of_range("additional length octets out of range");
        }
        uint8_t nlengthOctets = octet & 0b01111111;
        if (nlengthOctets >= 8)
        {
            throw std::out_of_range("variable length out of range");
        }
        for (int i = nlengthOctets - 1; i >= 0; i--)
        {
            octet = data[++currentOctet];
            length += static_cast<uint64_t>(octet * pow(256, i));
        }
        return length;
    }
    else
    {
        return octet;
    }
}