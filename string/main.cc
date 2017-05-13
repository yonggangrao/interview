#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"

#include <iostream>
using namespace std;
#include <assert.h>
#include <string.h>

void test1()
{
    qh::string s;
    assert(s.data() == NULL);
    assert(s.size() == 0);
    assert(sizeof(s.c_str()) != NULL);
    assert(s[0] == NULL);
}
void test2()
{
    char *str = "abc";

    qh::string s(str);
    assert(s.size() == 3);
    const char *p = s.data();
    for(int i = 0; i < s.size(); i++)
    {
        assert(*(p + i) == str[i]);
    }
    assert(!strcmp(s.c_str(), "abc"));
    for(int i = 0; i < s.size(); i++)
    {
        assert(*(s[i]) == str[i]);
    }
    *(s[0]) = 'A';
    assert(!strcmp(s.c_str(), "Abc"));
    assert(s[3] == NULL);
}
void test3()
{
    char *str = "";
    qh::string s(str);
    assert(s.data() != NULL);
    assert(s.size() == 0);
    assert(!strcmp(s.c_str(), ""));
    assert(s[0] == NULL);
    assert(s[2] == NULL);
}
void test4()
{
    char *str = "abcd";
    qh::string s(str, 3);
    assert(s.size() == 3);
    assert(!strcmp(s.c_str(), "abc"));
    const char *p = s.data();
    for(int i = 0; i < s.size(); i++)
    {
        assert(*(p + i) == str[i]);
    }
    *(s[2]) = 'C';
    assert(!strcmp(s.c_str(), "abC"));
    assert(*(s[0]) == 'a');
    assert(s[3] == NULL);
}
void test5()
{
    char *str = "abcd";
    qh::string s1(str);
    qh::string s2(s1);

    assert(s2.size() == 4);
    assert(!strcmp(s2.c_str(), "abcd"));
    const char *p = s2.data();
    for(int i = 0; i < s2.size(); i++)
    {
        assert(*(p + i) == str[i]);
    }
    qh::string s3 = s2;
    assert(s3.size() == 4);
    assert(!strcmp(s3.c_str(), "abcd"));
    p = s3.data();
    for(int i = 0; i < s3.size(); i++)
    {
        assert(*(p + i) == str[i]);
    }
}
void test6()
{
    char *str = "";
    qh::string s1(str);
    qh::string s2(s1);

    qh::string s3 = s2;
    assert(s3.size() == 0);
    assert(!strcmp(s3.c_str(), ""));
    assert(s3[0] == NULL);
    assert(s3[2] == NULL);
}
void test7()
{
    qh::string s1;
    qh::string s2(s1);

    qh::string s3 = s2;
    assert(s3.size() == 0);
    assert(s3.data() == NULL);
    assert(!strcmp(s3.c_str(), ""));
    assert(s3[0] == NULL);
    assert(s3[2] == NULL);
}

int main(int argc, char* argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

