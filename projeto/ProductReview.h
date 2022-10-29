#ifndef PRODUCTREVIEW_H_INCLUDED
#define PRODUCTREVIEW_H_INCLUDED

#include <string>;

using namespace std;

class ProductReview{
    private:
        string userId;
        string productId;
        float rating;
        string timestamp;
    public:
        ProductReview();
        ~ProductReview();
        void ProductReview::print();
};

#endif