#ifndef TT1_INFORMATION_RETRIEVAL_TEST_HELPER_H
#define TT1_INFORMATION_RETRIEVAL_TEST_HELPER_H

#include "locale_names.h"

#include <locale>

class LocaleSetter {
public:
    explicit LocaleSetter(std::string_view locale = DE_LOCALE);
    ~LocaleSetter();

private:
    std::locale mPreviousLocale;
};

#endif //TT1_INFORMATION_RETRIEVAL_TEST_HELPER_H
