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
    Example * p2 = new Example(new int [10]);
    SharedPTR<Example> ptr(p2);
    EXPECT_TRUE(ptr);

    SharedPTR <Example> ptr2(std::move(ptr));
    EXPECT_TRUE(ptr2);
    EXPECT_FALSE(ptr);
    
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

    EXPECT_EQ(ptr2->val, new_int);
    ptr2->multiply(0);
    EXPECT_EQ(p2->val[0], 0);
    
    
}
TEST(Release,NoErrors){
    int * new_int = new int[10];
    Example * p2 = new Example(new_int);
    SharedPTR <Example> ptr2(p2);
    SharedPTR <Example> ptr(ptr2);
    EXPECT_EQ(ptr2.useCount(), 2);
    EXPECT_EQ(ptr.useCount(), 2);
    ptr2.release();
    EXPECT_EQ(ptr2.get(), nullptr);
    EXPECT_FALSE(ptr2.unique());
    EXPECT_TRUE(ptr.unique());
    ptr.release();
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.useCount(), 0);
    EXPECT_EQ(ptr2.get(),nullptr );
    EXPECT_EQ(ptr2.useCount(), 0);

}


TEST(Reset, NoErrors) {
    double * d = new double[100];
    SharedPTR <double> dPtr;
    dPtr.reset(d);
    EXPECT_EQ(dPtr.get(), d);
    SharedPTR <double> dPtr_(dPtr);
}

TEST(Swap, NoErrors) {
    SharedPTR <Example> ptr1 (new Example(new int[100]));
    SharedPTR <Example> ptr2 (ptr1);
    SharedPTR <Example> ptr3;
    ptr3.swap(ptr2);
    EXPECT_EQ(ptr3.get(), ptr1.get());
    EXPECT_EQ(ptr2.get(), nullptr);
}

TEST(MakeShared, NoErrors) {
    int * new_int = new int[10];
    auto ptr = makeShared<Example>(new_int);
    EXPECT_TRUE(ptr.unique());
    EXPECT_EQ(ptr.get()->val, new_int);
    auto ptr2 = makeShared<double>(100);
    EXPECT_TRUE(ptr2.unique());
}
