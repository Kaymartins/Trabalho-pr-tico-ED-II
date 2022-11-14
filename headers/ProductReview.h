#ifndef PRODUCTREVIEW_H_INCLUDED
#define PRODUCTREVIEW_H_INCLUDED

#include <string>;

using namespace std;

class ProductReview {
    private:
        string userId;
        int productId;
        float rating;
        int timestamp;
    public:
        void ProductReview::print();
};

#endif