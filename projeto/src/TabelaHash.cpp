//
// Created by Kayan on 09/11/2022.
//

#include "../headers/TabelaHash.h"

bool TabelaHash::tabelaVazia(){
int sum = 0;

for(int i = 0; i < hashGroups; i++){
    sum += table[i].size();
    }

    if(!sum){
        return true;
    }

    return false;
}
