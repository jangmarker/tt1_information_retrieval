#include "database.h"
#include "document.h"

#include <cmath>
#include <ostream>
#include <iomanip>
#include <string>

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


void Database::addDocuments(std::vector<Document>&& documents)
{
    for (auto&& doc : documents) {
        addDocument(std::move(doc));
    }
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

namespace {
    using namespace std::literals;

    std::wostream& fixed_width(std::wostream& stream, std::wstring_view str, int width) {
        stream << std::setw(width) << std::setfill(L' ');
        const long moreThanWidthPos = str.length()-width;
        if (moreThanWidthPos > 0) {
            stream << L"..."s + str.substr(
                                 static_cast<std::size_t>(moreThanWidthPos) + 2,
                                 static_cast<std::size_t>(width) - 2
                                ).data();
        } else {
            stream << str.data();
        }
        return stream;
    }

    template<typename T>
    std::wostream& header_row(std::wostream& stream, const std::map<std::wstring, T>& items,
                              int cellWidth, bool even, int offset = 0) {
        static constexpr int cellSeparatorWidth = 1;
        const int large_cell_width = 2 * cellWidth + cellSeparatorWidth - 1;
        const int remainder = even ? 0 : 1;

        fixed_width(stream, L"", offset);

        int index = 0;
        for (auto & [identifier, _unused] : items) {
            stream << L' '; // don't overlap with values of left column
            if (index % 2 == remainder) {
                if (identifier.length() > large_cell_width) {
                    fixed_width(stream, identifier, large_cell_width);
                } else {
                    const int unsigned spaces_needed = large_cell_width - identifier.length();
                    unsigned int spaces_left = spaces_needed / 2;
                    std::wstring spaces;
                    spaces.reserve(spaces_left);
                    for (; spaces_left > 0; spaces_left--) {
                        spaces += L' ';
                    }
                    stream << std::left << std::setw(large_cell_width-1) << std::setfill(L' ') << (spaces + identifier);
                }
                stream << L' '; // separator between columns
            }
            index++;
        }

        stream << std::endl;

        return stream;
    }

    template<typename T>
    std::wostream& header(std::wostream& stream, const std::map<std::wstring, T>& items,
                          int first_column_width, int other_columns_width) {
        header_row(stream, items, other_columns_width, true, first_column_width - other_columns_width + 1);
        header_row(stream, items, other_columns_width, false, first_column_width + 1);
        return stream;
    }
}

std::wostream& operator<<(std::wostream& stream, const Database& database)
{
    static const int first_column_width = 20;
    static const int other_columns_width = 10;
    const auto & documents = database.documents();

    int row = 0;
    for (auto & [termId, frequency] : database.termFrequencies()) {
        if (row % 20 == 0) {
            header(stream, documents, first_column_width, other_columns_width);
        }
        stream << std::right;
        fixed_width(stream, termId, first_column_width);
        stream << L' ';
        for (auto & [documentId, document] : documents) {
            stream << L' ';
            stream << std::setprecision(other_columns_width-2) << std::left << std::setw(other_columns_width) << std::setfill(L' ');
            if (document.termFrequencies.find(termId) == document.termFrequencies.end())
                stream << 0.0f;
            else
                stream << document.termWeights.at(termId);
        }
        stream << std::endl;
        row++;
    }

    return stream;
}
