#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <string>
#include <vector>

struct Candle {
    std::string timestamp;
    double open, high, low, close;
};

std::vector<Candle> read_csv(const std::string& filename);
std::vector<Candle> parse_csv_data(const std::string& csv_data);

#endif
