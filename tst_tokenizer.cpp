#include "tokenizer.h"

#include "test_helper.h"
#include "3rdparty/catch.h"
#include "document.h"

#include <locale>
#include <codecvt>

static const std::wstring sentence =
        L"Ein Feldblock ist eine zusammenhängende landwirtschaftlich nutzbare Fläche, die von in der Natur "
        L"erkennbaren Außengrenzen (beispielsweise Wald, Straßen, bebautes Gelände, Gewässer, Gräben) umgeben ist.";
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
    REQUIRE(normalize(L"42.").empty());
}
TEST_CASE("tokenize example sentence", "[tokenizer]") {
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

TEST_CASE("task conformity", "[tokenizer]") {
    LocaleSetter setLocale;

    std::map<std::wstring, std::wstring> data{
            {L"123", L""},
            {L"REST", L"rest"},
            {L".", L""},
    };

    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

    for (auto & [input, expected] : data) {
        std::wistringstream stream(input);
        SECTION("tokenizer: " + conv.to_bytes(input)) {
            Token token;
            stream >> token;
            REQUIRE(token.value == expected);
        }
        SECTION("document reader: " + conv.to_bytes(input)) {
            Document doc;
            stream >> doc.termFrequencies;
            if (expected == L"") {
                REQUIRE(doc.termFrequencies.empty());
            } else {
                REQUIRE(doc.termFrequencies.size() > 0);
                REQUIRE(doc.termFrequencies[expected] == 1);
            }
        }
    }
}