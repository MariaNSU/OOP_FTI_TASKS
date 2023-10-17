#pragma once
#include <iostream>
#include <stddef.h>
template<typename Type, class TDeleter = std::default_delete<Type> >
class SharedPTR {
    using t_SharedPTR = SharedPTR<Type, TDeleter>;
private:
    Type * ptr;
    int counter; 
public: // Constructors and destructor.
    SharedPTR() {ptr = NULL; counter = 0;}
    SharedPTR(Type *pObj) {ptr = pObj; counter = 0;}
    SharedPTR(t_SharedPTR &&uniquePTR) { 
        ptr = uniquePTR.ptr;
        counter = uniquePTR.counter;
        uniquePTR.ptr = NULL;
        uniquePTR.counter = 0;

    } // Move constructor.
    SharedPTR(const t_SharedPTR& obj) {
        ptr = obj.ptr;
        counter++;
    }
    ~SharedPTR() {
        if(ptr != NULL && counter == 0) {
            // TDeleter(ptr);
        }
        else {
            counter--;
        }
    }
public: // Assignment.
    t_SharedPTR& operator=(t_SharedPTR &&sharedPTR);
    t_SharedPTR& operator=(Type *pObject) {
        ptr = pObject;
    }
    t_SharedPTR& operator=(const t_SharedPTR& obj) {
        ptr = obj.ptr;
        counter ++;
        return *this;
    }
public: // Observers.
    Type& operator*() const {return *ptr;}// Dereference the stored pointer.
    Type* operator->() const {return ptr;} // Return the stored pointer.
    Type* get() const {return ptr;} // Return the stored pointer.
    TDeleter& get_deleter(); // Return a reference to the stored deleter.
    operator bool() const {
        if(ptr == NULL) {
            return false;
        }
        else {
            return true;
        }
    } // Return false if the stored pointer is null.
public: // Modifiers.
    void release() {counter--;} // Release ownership of any stored pointer.
    void reset(Type *pObject = nullptr) {ptr = pObject;}// Replace the stored pointer.
    void swap(t_SharedPTR &sharedPTR) {
        T & tmp = ptr;
        int count = counter;

        ptr = sharedPTR.ptr;
        sharedPTR.ptr = tmp;
        
        counter = sharedPTR.counter;
        sharedPTR.counter = count
    } // Exchange the pointer with another object.
};

