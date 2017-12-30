#include "test_helper.h"

namespace {
    void setLocale(std::string_view name)
    {
        setlocale(LC_ALL, name.data());
        std::locale::global(std::locale(name.data()));
    }
}

LocaleSetter::LocaleSetter(std::string_view locale)
{
    mPreviousLocale = std::locale();
    setLocale(locale);
}

LocaleSetter::~LocaleSetter()
{
    setLocale(mPreviousLocale.name());
}
