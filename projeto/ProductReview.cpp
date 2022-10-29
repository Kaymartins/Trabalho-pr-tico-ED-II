#include <iostream>
#include <fstream>
#include "ProductReview.h"

using namespace std;

ProductReview::ProductReview()
{}

ProductReview::~ProductReview()
{}

void ProductReview::print()
{
    //imprime o conteúdo do registro:
    cout << "userId: " << this->userId << endl;
    cout << "productId: " << this->productId << endl;
    cout << "rating: " << this->rating << endl;
    cout << "timestamp: " << this->timestamp << endl;
}