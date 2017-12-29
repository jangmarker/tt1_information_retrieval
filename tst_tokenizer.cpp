#include "tokenizer.h"

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
    std::setlocale(LC_ALL, "de_DE.UTF-8");
    std::locale::global(std::locale("de_DE.UTF-8"));

    REQUIRE(normalize(L"Österreich") == L"österreich");
//    REQUIRE(normalize(L"Deutsch-land") == L"deutsch-land");
    REQUIRE(normalize(L"\"deutsch\"") == L"deutsch");
    REQUIRE(normalize(L"deutsch,") == L"deutsch");
    REQUIRE(normalize(L"deutsch.") == L"deutsch");
    REQUIRE(normalize(L"42.") == L"42");
}

TEST_CASE("tokenizer", "[tokenizer]") {
    std::wistringstream stream(sentence);

    for (const auto& sentenceToken : sentenceTokens) {
        Token token;
        stream >> token;
        REQUIRE(token.value == sentenceToken.value);
    }
}