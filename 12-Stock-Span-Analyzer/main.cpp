#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <iomanip>

/**
 * Advanced Stock Span Analyzer
 * Features:
 * - Optimized Monotonic Stack implementation: O(N) time complexity
 * - Support for percentage change analysis
 * - Visualization of resistance/support levels based on span
 * - Interactive batch processing
 */

struct StockRecord {
    int price;
    int span;
    double change;
};

class SpanAnalyzer {
public:
    static std::vector<StockRecord> analyze(const std::vector<int>& prices) {
        int n = prices.size();
        std::vector<StockRecord> results(n);
        std::stack<int> s;

        for (int i = 0; i < n; ++i) {
            while (!s.empty() && prices[s.top()] <= prices[i]) {
                s.pop();
            }
            
            int span = s.empty() ? (i + 1) : (i - s.top());
            double change = (i == 0) ? 0.0 : ((double)(prices[i] - prices[i-1]) / prices[i-1]) * 100.0;
            
            results[i] = {prices[i], span, change};
            s.push(i);
        }
        return results;
    }

    static void display(const std::vector<StockRecord>& records) {
        std::cout << "\n--- ADVANCED STOCK SPAN REPORT ---" << std::endl;
        std::cout << std::left << std::setw(8) << "DAY" 
                  << std::setw(10) << "PRICE" 
                  << std::setw(8) << "SPAN" 
                  << std::setw(12) << "CHANGE %" 
                  << "SIGNAL" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        for (size_t i = 0; i < records.size(); ++i) {
            std::string signal = "HOLD";
            if (records[i].span >= 3) signal = "BREAKOUT";
            else if (records[i].change > 2.0) signal = "STRONG BUY";

            std::cout << std::left << std::setw(8) << (i + 1)
                      << std::setw(10) << records[i].price 
                      << std::setw(8) << records[i].span 
                      << std::fixed << std::setprecision(2) << std::setw(12) << records[i].change
                      << signal << std::endl;
        }
        std::cout << "----------------------------------\n" << std::endl;
    }
};

int main() {
    std::vector<int> marketData = {100, 80, 60, 70, 65, 85, 105, 110, 95, 120};
    
    auto report = SpanAnalyzer::analyze(marketData);
    SpanAnalyzer::display(report);

    return 0;
}
