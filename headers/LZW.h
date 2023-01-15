#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED

#include "string"
#include <bits/stdc++.h>
using namespace std;


class LZW{
    private:
        unordered_map<string, int> table;
        unsigned int nComparacoes;

    public:
        LZW();
        ~LZW();
        vector<int> encoding(string s1);
        void decoding(vector<int> op);
};


#endif