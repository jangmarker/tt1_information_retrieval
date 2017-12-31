#include "fileaccess.h"

#include "tokenizer.h"

#include <fstream>
#include <locale>

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
