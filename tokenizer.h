#ifndef TT1_INFORMATION_RETRIEVAL_TOKENIZER_H
#define TT1_INFORMATION_RETRIEVAL_TOKENIZER_H

#include "database.h"
#include "document.h"

#include <istream>
#include <locale>

struct Token {
    std::wstring value;
};

std::wstring normalize(const std::wstring_view& source);

std::wistream& operator>>(std::wistream& stream, Token& token);
std::wistream& operator>>(std::wistream& stream, TermFrequencies& termFrequencies);

#endif //TT1_INFORMATION_RETRIEVAL_TOKENIZER_H
