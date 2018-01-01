#include "cli.h"
#include "search.h"

#include "3rdparty/catch.h"
#include "test_helper.h"

#include <sstream>

TEST_CASE("cli: 'Tür' without matrix", "[cli]") {
    LocaleSetter setLocale;

    char* argv[] = {
            const_cast<char*>("tst_cli"),
            const_cast<char*>("--db"),
            const_cast<char*>("../schlag/"),
            const_cast<char*>("Tür"),
    };
    constexpr int argc = sizeof(argv) / sizeof(char*);

    std::wstringstream cout_simulation;

    cli(argc, argv, cout_simulation);
    SearchResults expectedSearchResults = {
            // TODO verify numbers in calculations?
            {L"Türbeschlag",            0.401237},
            {L"Taubenschlag",           0.0162393},
            {L"Blitzeinschlag",         0},
            {L"Faustschlag",            0},
            {L"Feldblock",              0},
            {L"Kreuzschlag (Seile)",    0},
            {L"Paddelschlag",           0},
            {L"Peitsche (Schlagwaffe)", 0},
            {L"Reepschläger (Beruf)",   0},
            {L"Schlag (Hunderassen)",   0},
            {L"Schlag (Ort)",           0},
            {L"Schlag (Takt)",          0},
            {L"Schlag (Torfabbau)",     0},
            {L"Schlag (Wald)",          0},
            {L"Schlaganfall",           0},
            {L"Schlaghosen",            0},
            {L"Schlagzahl (Kanusport)", 0},
            {L"Schlagzahl (Uhr)",       0},
            {L"Stoßgesetze",            0},
            {L"Stromschlag",            0},
            {L"Uhrschlag",              0},
    };

    std::wstringstream expectedStream;

    for (const SearchResult& result : expectedSearchResults) {
        expectedStream << result << std::endl;

        std::wstring actual, expected;
        std::getline(cout_simulation, actual);
        std::getline(expectedStream, expected);

        REQUIRE(actual == expected);
    }
}
