#include <string>
#include <vector>

std::vector<std::string> fizzbuzz_reloaded(int n) {
    std::vector<std::string> result = {};
    for (size_t i = 1; i <= n; i++) {
        std::string tmp = "";
        if (i % 3 == 0) {
            tmp.append("Fizz");
        } 
        if (i % 5 == 0) {
            tmp.append("Buzz");
        } 
        if (i % 7 == 0) {
            tmp.append("Zap");
        }
        tmp.empty() ? result.push_back(std::to_string(i)) : result.push_back(tmp);
    }
    return result;
}
