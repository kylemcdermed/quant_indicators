#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "csv_utils.h"

using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string fetch_csv(string url) {
    CURL* curl = curl_easy_init();
    string readBuffer;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
            return "";
        }
    }
    return readBuffer;
}

int main() {
    string api_key = "XD07Y7EE4YZ2BA7H";
    string symbol = "NQ=F";
    string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&apikey=" + api_key + "&datatype=csv";

    cout << "Fetching data for " << symbol << " from Alpha Vantage...\n";

    string csv_data = fetch_csv(url);
    if (csv_data.empty()) {
        cout << "Failed to fetch data\n";
        return 1;
    }

    vector<Candle> candles = parse_csv_data(csv_data);
    cout << "Fetched " << candles.size() << " candles\n";

    for (int i = 0; i < min(5, (int)candles.size()); ++i) {
        cout << candles[i].timestamp << " O:" << candles[i].open << " H:" << candles[i].high << " L:" << candles[i].low << " C:" << candles[i].close << "\n";
    }

    // TODO: Call your simpleMovingAverage functions here with candles vector.

    return 0;
}
