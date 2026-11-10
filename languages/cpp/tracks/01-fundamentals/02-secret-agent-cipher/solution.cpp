#include <string>
#include <string_view>
#include <cctype>

std::string caesar(std::string_view text, int shift) {
    std::string cpy(text);
    for (auto& ch : cpy) {
        ch = isalpha(ch) ? islower(ch) ? 'a' + (((ch - 'a' + shift) % 26) + 26) % 26 : 'A' + (((ch - 'A' + shift) % 26) + 26) % 26 : ch;
    }
    return cpy;
}
