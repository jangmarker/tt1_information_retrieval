#include "search.h"

#include "test_helper.h"
#include "3rdparty/catch.h"

TEST_CASE("Query lowers input", "[search]") {
    LocaleSetter setLocale;

    Query query{L"Deutschland"};

    REQUIRE(query.termFrequencies[L"deutschland"] == 1);
}

TEST_CASE("Query removes - from input", "[search]") {
    LocaleSetter setLocale;

    Query query{L"BDSM-Session"};

    REQUIRE(query.termFrequencies[L"bdsmsession"] == 1);
}