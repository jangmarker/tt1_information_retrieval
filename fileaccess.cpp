#include "fileaccess.h"

#include "tokenizer.h"

#include <fstream>
#include <locale>
#include <iomanip>

std::vector<Document> FileAccess::documentsFromDirectory(const std::experimental::filesystem::path& dir)
{
    std::vector<Document> docs;

    std::experimental::filesystem::directory_iterator files(dir);
    for (const auto& file : files) {
        docs.emplace_back(documentFromFile(file.path()));
    }

    return docs;
}

Document FileAccess::documentFromFile(const std::experimental::filesystem::path& file)
{
    Document document;
    document.id = file.filename().stem().generic_wstring();

    std::wifstream stream(file);
    stream.imbue(std::locale(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>())));
    stream >> document.termFrequencies;

    return document;
}

void FileAccess::matrixToFile(const Database& database, std::string_view fileName)
{
    std::wofstream stream(fileName.data());
    stream.imbue(std::locale(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>())));

    const auto & documents = database.documents();

    stream << L"Term" << L';';
    for (auto & [documentId, document] : documents) {
        stream << documentId << L';';
    }
    stream << std::endl;

    for (auto & [termId, frequency] : database.termFrequencies()) {
        stream << termId << L';';
        for (auto & [documentId, document] : documents) {
            stream << std::setprecision(8);
            if (document.termFrequencies.find(termId) == document.termFrequencies.end())
                stream << 0.0f;
            else
                stream << document.termWeights.at(termId);
            stream << L';';
        }
        stream << std::endl;
    }

}