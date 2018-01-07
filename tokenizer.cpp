#include "tokenizer.h"

#include <iostream>

std::wstring normalize(std::wstring_view source)
{
    std::wstring target;
    target.reserve(source.length());
    for (std::wstring::value_type c : source) {
        if (std::isalpha(c, std::locale()))
            target += tolower(c, std::locale());
        // TODO improve number of recognized word patters, like abc-def or abc's
    }
    return target;
}

std::wistream& operator>>(std::wistream& stream, Token& token)
{
    stream >> token.value;
    token.value = normalize(token.value);
    return stream;
}

std::wistream& operator>>(std::wistream& stream, TermFrequencies& termFrequencies)
{
    while (!stream.eof()) {
        Token token;
        stream >> token;
        if (!token.value.empty())
            termFrequencies[token.value]++;
    }

    return stream;
}
