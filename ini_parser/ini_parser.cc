#include "ini_parser.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cwctype>
using namespace std;

namespace qh
{
	INIParser::INIParser() { }
	INIParser::~INIParser() { }
	
	bool INIParser::Parse(const std::string& ini_file_path)
	{
		const char *file = ini_file_path.c_str();
		std::ifstream ifs(file);

        if(!ifs)
        {
            fprintf(stderr, "Can not open file %s..", file);
        	return false;
        }
        
        string section;
        while (!ifs.eof()) 
        {
            std::string line;
            getline(ifs, line);
            if (ifs.fail() && !ifs.eof()) 
            {
                fprintf(stderr, "INIParser::Parse readfile error!!");
                ifs.close();
                return false;
            }

            line = Trim(line);
            if (!line.size()) 
                continue;

            char comment = '#';
            if(line[0] == '[')
            {
            	section = line.substr(1, line.size() - 2);
            	section = Trim(section);
            }
            else if(line[0] == comment)
            {
            	continue;
            }
            else
            {
            	vector<string> vec;
	     		Get_key_value(line, "=", vec);
                if(vec.size() <= 1)
                    continue;
                
                string key = vec[0];
                string value = vec[1];
                key = Trim(key);
                value = Trim(value);

                if(key.size() <= 0)
                    continue;

            	key = section + ":" + key;
            	map_section_[key] = value;
			}

        }

        ifs.close();
        
    	return true;
	}

    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, 
    	const std::string& line_seperator, 
    	const std::string& key_value_seperator)
    {
    	string input(ini_data);
    	vector <string> con;

     	Split(input, line_seperator, con);

    	for(int i = 0; i < con.size(); i++)
    	{
            vector<string> vec;
            string item = Trim(con[i]);
            Get_key_value(item, key_value_seperator, vec);
            if(vec.size() <= 1)
                continue;
            
            string key = vec[0];
            string value = vec[1];
            key = Trim(key);
            value = Trim(value);

            if(key.size() <= 0)
                continue;

            map_all_[key] = value;
    	}

    	return true;
    }

	const std::string& INIParser::Get(const std::string& key, bool* found)
	{
		map <string, string> :: iterator iter = map_all_.find(key);

		if(iter == map_all_.end())
		{
			if(found)
				*found = false;
			value_ = "";
			return value_;
		}

		if(found)
			*found = true;

		return iter->second;
	}

    const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
    {
    	string k = section + ":" + key;
    	map <string, string> :: iterator iter = map_section_.find(k);

		if(iter == map_section_.end())
		{
			if(found)
				*found = false;
			value_ = "";
			return value_;
		}

		if(found)
			*found = true;
		return iter->second;
    }

    std::string& INIParser::Trim(std::string &s)
    {
    	if(s.empty())
    	{
    		return s;
    	}
    	string::iterator iter;
    	for(iter = s.begin(); iter != s.end(); iter++)
    	{
    		if(!iswspace(*iter))
    			break;
    	}
    	s.erase(s.begin(), iter);
    	for(iter = s.end() - 1; iswspace(*iter); iter--)
    	{
    		s.erase(iter);
    	}
    	return s;
    }

    int INIParser::Split(const std::string& input, const std::string& seperator, std::vector<std::string>& con)
	{
    	int len = seperator.size();
    	int pos = 0;
    	while(true)
    	{
    		int p = input.find(seperator, pos);
    		if(p < 0)
    		{
    			string s = input.substr(pos, input.size() - pos);
    			if(s.size())
    				con.push_back(s);
    			break;
    		}
    		string s = input.substr(pos, p - pos);
    		if(s.size())
				con.push_back(s);
    		pos = p + len;
    	}
    	return 0;
	}
    int INIParser::Get_key_value(const std::string& input, const std::string& seperator, std::vector<std::string>& con)
    {
        int len = seperator.size();

        int p = input.find(seperator, 0);
        if(p < 0)
        {
            string s = input.substr(0, input.size());
            con.push_back(s);
            return -1;
        }
        string s = input.substr(0, p);

        con.push_back(s);
        s = input.substr(p + len, input.size() - p - len);
        con.push_back(s);
        return 0;
    }
}