#ifndef TT1_INFORMATION_RETRIEVAL_FILEACCESS_H
#define TT1_INFORMATION_RETRIEVAL_FILEACCESS_H

#include "database.h"

#include <experimental/filesystem>

namespace FileAccess
{

    std::vector<Document> documentsFromDirectory(const std::experimental::filesystem::path& dir);
    Document documentFromFile(const std::experimental::filesystem::path& file);

    void matrixToFile(const Database& database, std::string_view fileName);
}

#endif //TT1_INFORMATION_RETRIEVAL_FILEACCESS_H
