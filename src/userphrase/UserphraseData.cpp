#include "UserphraseData.h"

size_t UserphraseData::size() const
{
    return userphrase_.size();
}

const Userphrase &UserphraseData::get(size_t index)
{
    return userphrase_[index];
}

void UserphraseData::add(std::string &&phrase_, std::string &&bopomofo_)
{
    userphrase_.push_back(Userphrase{
        std::move(phrase_),
        std::move(bopomofo_),
    });
}

void UserphraseData::remove(size_t index)
{
    userphrase_.erase(userphrase_.begin() + index);
}

void UserphraseData::swap(std::vector<Userphrase> &userphrase)
{
    userphrase_.swap(userphrase);
}

void UserphraseData::refresh()
{
    refresh_impl();
}

void UserphraseData::save()
{
    save_impl();
}
