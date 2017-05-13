#include "qh_string.h"

#include <string.h>


namespace qh
{

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
        if(s == NULL)
        {
            data_ = NULL;
            len_ = 0;
        }
        else
        {
            int len = strlen(s);
            data_ = new char[len]; // data_ 末尾不存'\0'
            
            strncpy(data_, s, len);
            len_ = len;
        }
    }

    string::string( const char* s, size_t len )
    {
        if(s == NULL)
        {
            data_ = NULL;
            len_ = 0;
        }
        else
        {
            int length = strlen(s);
            if(length <= len)
            {
            	data_ = new char[length];
            	strncpy(data_, s, length);
            	len_ = length;
            }
            else
            {
            	data_ = new char[len];
            	strncpy(data_, s, len);
            	len_ = len;
            }
        }
    }

    string::string( const string& rhs )
    {
    	const char *s = rhs.data();
        size_t len = rhs.size();
		if(s == NULL)
        {
            data_ = NULL;
            len_ = 0;
        }
        else
        {
            data_ = new char[len];
            strncpy(data_, s, len);
            len_ = len;
        }
    }

    string& string::operator=( const string& rhs )
    {
        const char *s = rhs.data();
        size_t len = rhs.size();
        if(s == NULL)
        {
            data_ = NULL;
            len_ = 0;
        }
        else
        {
            data_ = new char[len];
            strncpy(data_, s, len);
            len_ = len;
        }
        return *this;
    }

    string::~string()
    {
    	if(data_ != NULL)
			delete [] data_;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        char *s = new char[len_ + 1];
        strncpy(s, data_, len_);
        s[len_] = '\0';

        return s;
    }

    char* string::operator[]( size_t index )
    {
        if(index >= len_)
        {
            return NULL;
        }
        return data_ + index;
    }
}
