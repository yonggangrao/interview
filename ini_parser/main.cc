#include "ini_parser.h"
#include <iostream>
#include <string.h>
#include <assert.h>
#include <string>
using namespace std;


void test1()
{
    const char* ini_text= "a=1\nb=2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("a", NULL);
    assert(b != "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "");
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("a", NULL);
    assert(b != "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("a", NULL);
    assert(b != "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}
void test4()
{
    const char* ini_text = " a = 1 ||= 2||c= || d ||4||e==3||  "; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) 
    {
        assert(false);
    }

    bool found;
    std::string s = parser.Get("a", &found);
    assert(s == "1");
    assert(found == true);

    s = parser.Get("2", &found);
    assert(s == "");
    assert(found == false);


    s = parser.Get("c", &found);
    assert(s == "");
    assert(found == true);

    s = parser.Get("d", &found);
    assert(s == "");
    assert(found == false);

    s = parser.Get("4", &found);
    assert(s == "");
    assert(found == false);

    s = parser.Get("e", &found);
    assert(s == "=3");
    assert(found == true);
}

void test5()
{
    string file = "my.ini";
    qh::INIParser parser;
    if (!parser.Parse(file)) {
        assert(false);
    }
    string s;
    bool found = false;
    s = parser.Get("mysqlhotcopy", "test", &found);
    assert(s == "");
    assert(found == true);

    s = parser.Get("mysqldump", "max_allowed_packet", NULL);
    assert(s == "16M");
    s = parser.Get("client", "port", NULL);
    assert(s == "8080");
    s = parser.Get("mysqld", "port", NULL);
    assert(s == "8080");
    s = parser.Get("myisamchk", "sort_buffer_size", NULL);
    assert(s == "256M");
    s = parser.Get("mysqld", "port2", NULL);
    assert(s == "");
    s = parser.Get("mysqld2", "port", NULL);
    assert(s == "");
}

int main(int argc, char* argv[])
{

    
    test1();
    test2();
    test3();
    test4();
    test5();
 
    return 0;
}


