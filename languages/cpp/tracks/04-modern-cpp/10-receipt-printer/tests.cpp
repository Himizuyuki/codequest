#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using S = std::string;

TEST(receipt_line_example) {
    //                                 item (12)        qty(3)  " x "  price (8)    " = "  total (9)
    CHECK_EQ(receipt_line("coffee", 2, 3.5), S("coffee      ") + "  2" + " x " + "    3.50" + " = " + "     7.00");
}

TEST(receipt_line_has_a_fixed_width) {
    CHECK_EQ(receipt_line("tea", 1, 2.0).size(), std::size_t{38});
    CHECK_EQ(receipt_line("", 0, 0.0), S("            ") + "  0" + " x " + "    0.00" + " = " + "     0.00");
}

TEST(long_item_names_are_cut) {
    CHECK_EQ(receipt_line("extra-large-cappuccino", 1, 5.25),
             S("extra-large-") + "  1" + " x " + "    5.25" + " = " + "     5.25");
    CHECK_EQ(receipt_line("twelve-chars", 1, 1.0), S("twelve-chars") + "  1" + " x " + "    1.00" + " = " + "     1.00");
}

TEST(receipt_line_big_numbers) {
    CHECK_EQ(receipt_line("gold bar", 120, 1999.99),
             S("gold bar    ") + "120" + " x " + " 1999.99" + " = " + "239998.80");
}

TEST(receipt_line_rounds_to_cents) {
    CHECK_EQ(receipt_line("candy", 3, 0.125), S("candy       ") + "  3" + " x " + "    0.12" + " = " + "     0.38");
}

TEST(hex_bytes) {
    CHECK_EQ(hex_byte(15), S("0x0f"));
    CHECK_EQ(hex_byte(255), S("0xff"));
    CHECK_EQ(hex_byte(0), S("0x00"));
    CHECK_EQ(hex_byte(65), S("0x41"));   // not "0x A"
}

TEST(percentages) {
    CHECK_EQ(percent(0.256), S("25.6%"));
    CHECK_EQ(percent(1.0), S("100.0%"));
    CHECK_EQ(percent(0.0), S("0.0%"));
    CHECK_EQ(percent(0.3333), S("33.3%"));
}

TEST(padded_ids) {
    CHECK_EQ(pad_id(42), S("000042"));
    CHECK_EQ(pad_id(0), S("000000"));
    CHECK_EQ(pad_id(1234567), S("1234567"));
    CHECK_EQ(pad_id(-42), S("-00042"));
}
