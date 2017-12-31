#include "search.h"

#include <algorithm>
#include <locale>
#include <iostream>

Query::Query(std::initializer_list<std::wstring_view> terms)
{
    for (auto& termView : terms) {
        std::wstring term;
        term.reserve(termView.length());
        for (auto& c : termView) {
            term += tolower(c, std::locale());
        }
        termFrequencies[term]++;
    }
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
