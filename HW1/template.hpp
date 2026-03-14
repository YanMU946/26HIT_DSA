#ifndef __TEMP_HPP__
#define __TEMP_HPP__
#include <iostream>
#include <stdio.h>

class dsa_man
{
public:
    dsa_man(int _num, char *_name);

    ~dsa_man() = delete;

private:
    int num;
    char *name;
};

#endif /* End template */
