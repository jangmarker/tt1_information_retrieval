#include "tokenizer.h"

#include <iostream>

std::wstring normalize(const std::wstring& source)
{
    std::wstring target;
    target.reserve(source.length());
    for (std::wstring::value_type c : source) {
        if (isalnum(c, std::locale()))
            target += tolower(c, std::locale());
        // TODO improve number of recognized word patters, like abc-def or abc's
    }
    return target;
}

std::wistream& operator>>(std::wistream& stream, Token& token)
{
    std::wstring string;
    stream >> token.value;
    token.value = normalize(token.value);
    return stream;
}
