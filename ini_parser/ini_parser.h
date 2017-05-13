#ifndef QIHOO_INI_PARSER_H_
#define QIHOO_INI_PARSER_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

namespace qh
{
    class INIParser
    {
    public:
        INIParser();
        ~INIParser();

        //! \brief 解析一个磁盘上的INI文件
        //! \param[in] - const std::string & ini_file_path
        //! \return - bool
        bool Parse(const std::string& ini_file_path);

        //! \brief 解析一段形如INI格式的内存数据。
        //!   例如：ini_data="a:1||b:2||c:3"
        //!         调用<code>Parse(ini_data, ini_data_len, "||", ":")</code>即可解析出这段数据。
        //!         解析完毕之后 
        //!         Get("a")=="1" && Get("b")=="2" && Get("c")=="3"
        //! \param[in] - const char * ini_data
        //! \param[in] - size_t ini_data
        //! \param[in] - const std::string & line_seperator
        //! \param[in] - const std::string & key_value_seperator
        //! \return - bool
        bool Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=");

        //! \brief 从默认section中查找某个key，并返回找到的value。如果找不到，返回一个空串
        //! \param[in] - const std::string & key
        //! \param[in] - bool * found - 输出参数，true表明找到这个key
        //! \return - const std::string& - 返回的具体key对应的value
        const std::string& Get(const std::string& key, bool* found);
        const std::string& Get(const std::string& section, const std::string& key, bool* found);

        //! \brief 将字符串分割成子串
        //! \param[in] - const std::string & seperator - 以seperator为界分割
        //! \param[in] - std::vector<std::string>& con - 分割后得到的子串存入con中
        //! \return - int - 函数执行成功与否
        int Split(const std::string& input, const std::string& seperator, std::vector<std::string>& con);

        //! \brief 去掉string两端的空白字符
        //! \param[in] - std::string & s
        //! \return - std::string& - 返回的修改后的string
        std::string& Trim(std::string &s);
        //! \brief 从形如"key=value"的字符串解析出key和value。与Split不同，即使key和value为空，都需要将空串保留在con中
        //! \param[in] - const std::string & seperator - 以seperator为界分割
        //! \param[in] - std::vector<std::string>& con - 分割后得到的子串存入con中
        //! \return - int - 函数执行成功与否
        int Get_key_value(const std::string& input, const std::string& seperator, std::vector<std::string>& con);


    private:
        map <string, string> map_all_;
        map <string, string> map_section_;
        string value_;
    };
}

#endif

