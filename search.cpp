#include "search.h"
#include "tokenizer.h"

#include <algorithm>
#include <locale>
#include <iostream>
#include <codecvt>

namespace {
    template<typename Terms>
    void convertToTermFrequencies(const Terms& terms, TermFrequencies* frequencies) {
        for (auto& termView : terms) {
            std::wstring term = normalize(termView);
            (*frequencies)[term]++;
        }
    }
}

Query::Query(std::initializer_list<std::wstring_view> terms)
{
    convertToTermFrequencies(terms, &termFrequencies);
}

Query::Query(const std::vector<std::string>& terms)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

    std::vector<std::wstring> wTerms;
    wTerms.reserve(terms.size());
    for (const auto& term : terms) {
        wTerms.push_back(std::move(conv.from_bytes(term)));
    }
    convertToTermFrequencies(wTerms, &termFrequencies);
}

SearchResult::SearchResult(const DocumentId& documentId, double similarity)
    : documentId(documentId)
    , similarity(similarity)
{

}

bool operator<(const SearchResult& lhs, const SearchResult& rhs)
{
    return lhs.similarity > rhs.similarity;
}

std::wostream& operator<<(std::wostream& stream, const SearchResult& result)
{
    stream << result.documentId << ": "<< result.similarity;
    return stream;
}
