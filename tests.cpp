#include <gtest/gtest.h>
#include "sharedPtr.h"

struct Example {
        int* val;
        Example(int* val_){val = val_;}
        Example(const Example& ex) {
            val = ex.val;
        }
        ~Example(){ val = nullptr;}
        void multiply(int times) {
            if(val) {
                val[0]*= times;
            }
            else {
                return;
            }
        }
    };

TEST(Constructor, Default){
    SharedPTR<int> ptr;
    EXPECT_FALSE(ptr); 
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(Constructor, PointerToObj){
    int* p1 = new int[100];
    SharedPTR<int> ptr(p1);
    EXPECT_EQ(ptr.get(), p1);

    Example * p2 = new Example(p1);
    SharedPTR <Example> ptr2(p2);
    EXPECT_EQ(ptr2.get(), p2);
    
}

TEST(Constructor, Move){
    int* p1 = new int[100];
    SharedPTR<int> ptr(std::move(p1));
    EXPECT_TRUE(ptr.get());
    EXPECT_FALSE(p1);

    Example * p2 = new Example(new int [10]);
    SharedPTR <Example> ptr2(std::move(p2));
    EXPECT_TRUE(ptr2.get());
    EXPECT_FALSE(p2);
    
}

TEST(Constructor, Copy){
    int* p1 = new int[100];
    SharedPTR<int> ptr(p1);
    SharedPTR<int> ptr_(ptr);
    EXPECT_EQ(ptr.get(), ptr_.get());
    
    Example * p2 = new Example(p1);
    SharedPTR <Example> ptr2(p2);
    SharedPTR<Example> ptr2_(ptr2);
    EXPECT_EQ(ptr2.get(), ptr2_.get());
      
}

TEST(Assignment,Move) {

    int* p1 = new int[10];
    SharedPTR<int> ptr(p1);
    int* p2 = new int[100];
    SharedPTR <int> ptr2(p2);
    ptr = std::move(ptr2);

    EXPECT_EQ(ptr.get(),p2);
    EXPECT_EQ(ptr2, NULL);
}

TEST(Assignment,Copy) {
    int* p1 = new int[100];
    SharedPTR<int> ptr(p1);
    int* p2 = new int[10];
    SharedPTR <int> ptr2(p2);
    ptr = ptr2;
    EXPECT_EQ(ptr.get(),p2);
    EXPECT_EQ(ptr2.get(), p2);
}

TEST(Assignment,Object) {
    int* p1 = new int[100];
    int* p1_ = new int[10];
    SharedPTR<int> ptr(p1);
    ptr = p1_;
    EXPECT_EQ(ptr.get(),p1_);
    
    Example * p2 = new Example(p1);
    SharedPTR <Example> ptr2(p2);
    Example * p2_ = new Example(p1_);
    ptr2 = p2_;
    EXPECT_EQ(ptr2.get(),p2_);
}

TEST(Operators,Dereference){
    SharedPTR <Example> ptr;
    int * new_int = new int[10];
    Example * p2 = new Example(new_int);

    SharedPTR <Example> ptr2(p2);
    //EXPECT_EQ(*ptr2, p2); ????????
    EXPECT_EQ(ptr2->val, new_int);
    ptr2->multiply(0);
    EXPECT_EQ(p2->val[0], 0);
    
}

TEST(Release,NoErrors){
    int * new_int = new int[10];
    Example * p2 = new Example(new_int);
    SharedPTR <Example> ptr2(p2);
    SharedPTR <Example> ptr(ptr2);
    ptr2.release();
    EXPECT_EQ(ptr2.get(), nullptr);
}

