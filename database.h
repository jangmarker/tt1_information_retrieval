#ifndef TT1_INFORMATION_RETRIEVAL_DATABASE_H
#define TT1_INFORMATION_RETRIEVAL_DATABASE_H

#include <map>
#include <vector>

using DocumentId = std::wstring;
using TermId = std::wstring;
using TermFrequencies = std::map<TermId, std::size_t>;
using TermWeights = std::map<TermId, double>;

struct Document
{
    DocumentId id;
    TermFrequencies termFrequencies;
    TermWeights termWeights;
    double euclideanNorm;
};

using DocumentList = std::map<DocumentId, Document>;

struct SearchResult {
    SearchResult(const DocumentId& documentId, double similarity);

    DocumentId documentId;
    double similarity;
};
using SearchResults = std::vector<SearchResult>;

class Database
{

public:
    void addDocument(Document&& document);
    void addDocument(const Document& document);
    void addDocuments(std::vector<Document>&& documents);
    void recalculateWeights();

    SearchResults search(const Document& query);

    const DocumentList& documents() const;
    const TermFrequencies& termFrequencies() const;

private:
    DocumentList mDocuments;
    TermFrequencies mTermFrequency;
};

#endif //TT1_INFORMATION_RETRIEVAL_DATABASE_H
