#ifndef TT1_INFORMATION_RETRIEVAL_SEARCH_H
#define TT1_INFORMATION_RETRIEVAL_SEARCH_H

#include "document.h"

struct Query : public Document
{
    Query(std::initializer_list<std::wstring_view> terms);
};

struct SearchResult {
    SearchResult(const DocumentId& documentId, double similarity);

    DocumentId documentId;
    double similarity;
};
using SearchResults = std::vector<SearchResult>;

bool operator<(const SearchResult& lhs, const SearchResult& rhs);
std::wostream& operator<<(std::wostream& stream, const SearchResult& result);

#endif //TT1_INFORMATION_RETRIEVAL_SEARCH_H
