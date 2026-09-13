#include "./app.hpp"

int main()
{
    return saucer::application::create({.id = "yume-nikki-online"})->run(start);
}