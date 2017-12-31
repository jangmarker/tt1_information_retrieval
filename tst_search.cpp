#include "search.h"

#include "test_helper.h"
#include "3rdparty/catch.h"

TEST_CASE("Query lowers input", "[search]") {
    LocaleSetter setLocale;

    Query query{L"Deutschland"};

    REQUIRE(query.termFrequencies[L"deutschland"] == 1);
}