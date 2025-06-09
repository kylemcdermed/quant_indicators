#include "csv_utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<Candle> read_csv(const string& filename) {
    vector<Candle> candles;
    ifstream file(filename);
    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Candle c;

        getline(ss, c.timestamp, ',');
        getline(ss, token, ','); c.open = stod(token);
        getline(ss, token, ','); c.high = stod(token);
        getline(ss, token, ','); c.low = stod(token);
        getline(ss, token, ','); c.close = stod(token);

        candles.push_back(c);
    }

    return candles;
}

vector<Candle> parse_csv_data(const string& csv_data) {
    vector<Candle> candles;
    istringstream file(csv_data);
    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Candle c;

        getline(ss, c.timestamp, ',');
        getline(ss, token, ','); c.open = stod(token);
        getline(ss, token, ','); c.high = stod(token);
        getline(ss, token, ','); c.low = stod(token);
        getline(ss, token, ','); c.close = stod(token);

        candles.push_back(c);
    }

    return candles;
}
