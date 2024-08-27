
#include "Parser.h"
#include <cassert> // For basic assertions

void testParserInitialization() {
    Parser parser("test data", "testfile.txt");
    assert(parser.getReceipe() != nullptr); // Ensure that the Recipe is initialized
}

void testParseHeading() {
    Parser parser("# Title\n", "testfile.txt");
    parser.Parse();
    // Add assertions to check if title was set correctly
}


int main() {
    testParserInitialization();
    testParseHeading();

    return 0;
}
