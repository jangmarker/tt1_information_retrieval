#include "tokenizer.h"

#include "test_helper.h"
#include "3rdparty/catch.h"

#include <locale>
#include <sstream>

static const std::wstring sentence =
        L"Ein Feldblock ist eine zusammenhängende landwirtschaftlich nutzbare Fläche, die von in der Natur "
         "erkennbaren Außengrenzen (beispielsweise Wald, Straßen, bebautes Gelände, Gewässer, Gräben) umgeben ist.";
static const Token sentenceTokens[] = {
        {L"ein"}, {L"feldblock"}, {L"ist"}, {L"eine"}, {L"zusammenhängende"}, {L"landwirtschaftlich"},
        {L"nutzbare"}, {L"fläche"}, {L"die"}, {L"von"}, {L"in"}, {L"der"}, {L"natur"}, {L"erkennbaren"},
        {L"außengrenzen"}, {L"beispielsweise"}, {L"wald"}, {L"straßen"}, {L"bebautes"}, {L"gelände"},
        {L"gewässer"}, {L"gräben"}, {L"umgeben"}, {L"ist"},
};

TEST_CASE("normalizer", "[tokenizer]") {
    LocaleSetter setLocale;

    REQUIRE(normalize(L"Österreich") == L"österreich");
//    REQUIRE(normalize(L"Deutsch-land") == L"deutsch-land");
    REQUIRE(normalize(L"\"deutsch\"") == L"deutsch");
    REQUIRE(normalize(L"deutsch,") == L"deutsch");
    REQUIRE(normalize(L"deutsch.") == L"deutsch");
    REQUIRE(normalize(L"42.") == L"42");
}

TEST_CASE("tokenizer", "[tokenizer]") {
    LocaleSetter setLocale;

    std::wistringstream stream(sentence);

    for (const auto& sentenceToken : sentenceTokens) {
        Token token;
        stream >> token;
        REQUIRE(token.value == sentenceToken.value);
    }
}

TEST_CASE("document reader", "[tokenizer]") {
    LocaleSetter setLocale;

    std::wistringstream stream(sentence);

    Document doc;
    stream >> doc.termFrequencies;

    REQUIRE(doc.termFrequencies.size() == 23);
    REQUIRE(doc.termFrequencies[L"ist"] == 2);
    REQUIRE(doc.termFrequencies[L"umgeben"] == 1);
}