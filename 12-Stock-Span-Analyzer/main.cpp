#include <iostream>
#include <vector>
#include <stack>

class StockSpan {
public:
    static std::vector<int> calculateSpan(const std::vector<int>& prices) {
        int n = prices.size();
        std::vector<int> spans(n);
        std::stack<int> s;

        for (int i = 0; i < n; ++i) {
            while (!s.empty() && prices[s.top()] <= prices[i]) {
                s.pop();
            }
            spans[i] = s.empty() ? (i + 1) : (i - s.top());
            s.push(i);
        }
        return spans;
    }
};

int main() {
    std::vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    std::vector<int> spans = StockSpan::calculateSpan(prices);

    std::cout << "Stock Prices: ";
    for (int p : prices) std::cout << p << " ";
    std::cout << "\nSpans:        ";
    for (int s : spans) std::cout << s << " ";
    std::cout << "\n";
    return 0;
}
