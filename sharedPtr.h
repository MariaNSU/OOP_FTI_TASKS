#pragma once
#include <iostream>
#include <stddef.h>
template<typename Type, class TDeleter = std::default_delete<Type> >
class SharedPTR {
    using t_SharedPTR = SharedPTR<Type, TDeleter>;
private:
    Type * ptr;
    size_t counter; 
public: 
    // Constructors and destructor.
    SharedPTR() {ptr = NULL; counter = 0;}
    SharedPTR(Type *pObj) {ptr = pObj; counter = 0;}
    // Move constructor.
    SharedPTR(t_SharedPTR &&uniquePTR) { 
        ptr = uniquePTR.ptr;
        counter = uniquePTR.counter;
        uniquePTR.ptr = NULL;
        uniquePTR.counter = 0;

    } 
    SharedPTR(const t_SharedPTR& obj) {
        ptr = obj.ptr;
        counter++;
    }
    ~SharedPTR() {
        if(ptr != NULL && counter == 0) {
            TDeleter()(ptr);
        }
        else {
            counter--;
        }
    }
public: // Assignment.
    t_SharedPTR& operator=(t_SharedPTR &&sharedPTR) {
        ptr = sharedPTR.ptr;
        return *this;
    }
    t_SharedPTR& operator=(Type *pObject) {
        ptr = pObject;
        return *this;
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
    TDeleter& get_deleter() { return TDeleter(); } // Return a reference to the stored deleter.
    // Return false if the stored pointer is null.
    operator bool() const {
        if(ptr == NULL) {
            return false;
        }
        else {
            return true;
        }
    } 
public: // Modifiers

    // Release ownership of any stored pointer.
    void release() {
        if(counter > 0) {
            counter--;
        }
        else 
            return;} 
    // Replace the stored pointer.
    void reset(Type *pObject = NULL) {ptr = pObject;}

    // Exchange the pointer with another object.
    void swap(t_SharedPTR &sharedPTR) {
        std::swap(counter,sharedPTR.counter);
        std::swap(ptr,sharedPTR.ptr);
    } 
};

