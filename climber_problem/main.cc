#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <vector>
using namespace std;

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

int get_input(const char *input, int &n, vector <int> &v_input);

int resolve(const char* input)
{
    if(input == NULL)
        return 0;
    int n;
    vector <int> v_input;
    get_input(input, n, v_input); //处理后得到的v_input是这样的：{1,3,2,2,4,4,6,7,5},每三个元素对应一个triple

    int len = v_input[v_input.size() - 2] + 1;
    vector <int> v(len, 0); 
    
    size_t i;
    for(i = 0; i < v_input.size(); i += 3)
    {
        int begin = v_input[i];
        int end = v_input[i+1];
        int height = v_input[i+2];
        for(int j = begin; j < end; j++)
        {
            if(v[j] < height)
                v[j] = height; 
        }
    }
    //计算水平方向上的位移
    int s1 = v.size() - 1;

    //计算竖直方向上的位移
    int s2 = 0;
    if(v[0] > 0)
    {
        s2 = v[0];
    }
    for(i = 1; i < v.size(); i++)
    {
        if(v[i] > v[i-1])
        {
            s2 += v[i] - v[i-1];
        }
        else if(v[i] < v[i-1])
        {
            s2 += v[i-1] - v[i];
        }
    }

    return (s1 + s2);
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        "3\n1,2,3\n2,4,4\n3,4,1\n",
        "3\n1,2,4\n2,5,2\n3,7,4\n",
        "2\n1,3,4\n1,3,2\n",
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20, 12, 19, 11};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}


int get_input(const char *input, int &n, vector <int> &v_input)
{
    const char *p = input;
    n = *p - '0';
    p++;
    p++;
    while(*p != '\0')
    {
        int val = *p - '0';
        v_input.push_back(val);
        p++;
        p++;
        val = *p - '0';
        v_input.push_back(val);
        p++;
        p++;
        val = *p - '0';
        v_input.push_back(val);
        p++;
        if(*p == '\0')
            break;
        p++;
    }

    return 0;
}
