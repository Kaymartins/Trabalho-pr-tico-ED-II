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
        void setUserId(string userId){this->userId = userId;};
        void setProductId(string productId){this->productId = productId;};
        void setRating(float rating){this->rating = rating;};
        void setTimestamp(string timestamp){this->timestamp = timestamp;};
        void ProductReview::print();
};

#endif