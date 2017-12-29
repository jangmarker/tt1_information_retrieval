#include "database.h"

#include <cmath>

namespace
{
    double calculateWeight(std::size_t termFreqInDocument, std::size_t termDocumentCount, std::size_t documentCount)
    {
        return termFreqInDocument *
               std::log2(static_cast<double>(documentCount) / static_cast<double>(termDocumentCount));
    }

    void calculateWeights(Document* document, TermFrequencies& termDocumentCount, size_t documentCount) {
        TermWeights& termWeights = document->termWeights;
        double squareSum = 0.0;
        for (auto & [termId, frequency] : document->termFrequencies) {
            double weight = calculateWeight(frequency, termDocumentCount[termId], documentCount);
            termWeights[termId] = weight;
            squareSum += weight * weight;
        }
        document->euclideanNorm = std::sqrt(squareSum);
    }

    double calculateSimilarity(const Document &query, const Document &doc) {
        double topSum = 0.0;

        for (auto & [termId, weight] : query.termWeights) {
            if (doc.termWeights.find(termId) != doc.termWeights.end()) {
                topSum += doc.termWeights.at(termId) * weight;
            }
        }

        return topSum / (query.euclideanNorm * doc.euclideanNorm);
    }
}

SearchResult::SearchResult(const DocumentId& documentId, double similarity)
    : documentId(documentId)
    , similarity(similarity)
{

}

void Database::addDocument(Document&& document)
{
    for (const auto& termFrequency : document.termFrequencies) {
        mTermFrequency[termFrequency.first]++;
    }
    mDocuments.emplace(document.id, std::move(document));
}

void Database::addDocument(const Document& document)
{
    auto copy = document;
    addDocument(std::move(copy));
}

void Database::recalculateWeights()
{
    // C++17 structured bindings - Clion doesn't like them, yet :-(
    for (auto & [documentId, document] : mDocuments) {
        calculateWeights(&document, mTermFrequency, mDocuments.size());
    }
}

SearchResults Database::search(const Document& originalQuery)
{
    Document query(originalQuery);
    SearchResults results;

    calculateWeights(&query, mTermFrequency, mDocuments.size());
    for (auto& docWithId : mDocuments) {
        double similarity = calculateSimilarity(query, docWithId.second);
        results.emplace_back(docWithId.first, similarity);
    }

    return results;
}

const DocumentList& Database::documents() const
{
    return mDocuments;
}

const TermFrequencies& Database::termFrequencies() const
{
    return mTermFrequency;
}
