#include <vector>
#include <iostream>

using namespace std;

class SMA666STRATEGY {
private:
    std::vector<double> window;
    int m_period;
    int m_index;
    int m_count;
    double m_sum;
public:
    SMA666STRATEGY(int period) 
        : m_period {period}
        , m_index {0}
        , m_count {0}
        , m_sum {0.0} {
            window.resize(period, 0.0);
        }
    double update(double price) {
        // remove oldest price from sum
        m_sum -= window[m_index];
        // insert new price
        window[m_index] = price;
        m_sum += price;
        // move index cyclically 
        m_index = (m_index + 1) % m_period;
        if (m_count < m_period) m_count++;
        return m_sum / m_count;
    }
};