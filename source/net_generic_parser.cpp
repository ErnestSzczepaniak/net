#include "net_generic_parser.h"

namespace net::generic
{

Parser::Parser()
{

}

Parser::~Parser()
{

}

char * Parser::_word_point(char * record, int index)
{
    if (index == 0) return record;

    int count = 0;
    int length = strlen(record);

    for (int i = 0; i < length; i++)
    {
        if (record[i] == ascii_space) count++;

        if (count == index) return &record[i + 1];
    }

    return nullptr;
}

bool Parser::_word_matches(char * record, int index, const char * value)
{
    auto * word = _word_point(record, index);

    if (word == nullptr) return false;

    return strncmp(word, value, strlen(value)) == 0;
}

bool Parser::_word_present(char * record, const char * value)
{
    auto length = strlen(record);
    auto value_length = strlen(value);

    for (int i = 0; i < length; i++)
    {
        if (strncmp(&record[i], value, value_length) == 0) return true;
    }

    return false;
}

int Parser::_word_index(char * record, const char * value)
{
    auto counter = 0;

    auto length = strlen(record);
    auto value_length = strlen(value);

    for (int i = 0; i < length; i++)
    {
        if (strncmp(&record[i], value, value_length) == 0) return counter;

        if (record[i] == ascii_space) counter++;
    }

    return -1;
}

}; /* namespace: net::generic */
