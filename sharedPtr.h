#pragma once
#include <iostream>
#include <stddef.h>
template<typename Type, class TDeleter = std::default_delete<Type> >
class SharedPTR {
    using t_SharedPTR = SharedPTR<Type, TDeleter>;
private:
    Type* ptr = nullptr;
    size_t* counter = nullptr;

    void incCounter() {
        if(ptr) {
            *counter+=1;
        }
    }
public:
    // Constructors and destructor.
    SharedPTR() = default;
    SharedPTR(Type *pObj) {
        if(pObj != nullptr) {
            ptr = pObj;
            counter = new size_t(0);
            incCounter();
        }
        
        }
    // Move constructor.
    SharedPTR(t_SharedPTR &&uniquePTR) noexcept : ptr(uniquePTR.ptr), counter(uniquePTR.counter)  {
        uniquePTR.ptr = nullptr;
        uniquePTR.counter = nullptr;
    }
    SharedPTR(const t_SharedPTR& obj): ptr(obj.ptr), counter(obj.counter) {
        incCounter();
    }
    ~SharedPTR() {
        release();
    }
public: // Assignment.
    t_SharedPTR& operator=(t_SharedPTR &&sharedPTR) noexcept {
        if(ptr == sharedPTR.ptr) {
            return *this;
        }
        release();
        ptr = sharedPTR.ptr;
        counter = sharedPTR.counter;
        sharedPTR.ptr = nullptr;
        sharedPTR.counter = nullptr;
        return *this;
    }
    t_SharedPTR& operator=(Type *pObject) {
        *this = t_SharedPTR(pObject);
        return *this;
        
    }
    t_SharedPTR& operator=(const t_SharedPTR& obj) noexcept {
        if(ptr == obj.ptr) {
            return *this;
        }
        release();
        ptr = obj.ptr;
        counter = obj.counter;
        incCounter();
        return *this;
    }
public: // Observers.
    // Dereference the stored pointer.
    Type& operator*() const {
        return *(get());
        }
    // Return the stored pointer.
    Type* operator->() const {
        return get();}
    // Return the stored pointer.
    Type* get() const {
        return ptr;
        }
    // Return a reference to the stored deleter.
    TDeleter& get_deleter() const{
        return TDeleter();
        }
    // Return false if the stored pointer is null.
    operator bool() const {
        return(ptr != nullptr);
        }
public:
     // Modifiers

    // Release ownership of any stored pointer.
    void release() {
        if (counter == nullptr) {
            return;
        }
        if(*(counter) == 1) {
            TDeleter()(ptr);
            delete counter;
            ptr = nullptr;
            counter = nullptr;
            return;
        }
        *(counter)-=1;
        ptr = nullptr;
        counter = nullptr;

    }
    // Replace the stored pointer.
    void reset(Type *pObject = nullptr) {
        *this = SharedPTR(pObject); 
    }

    // Exchange the pointer with another object.
    void swap(t_SharedPTR &sharedPTR) {
        std::swap(counter,sharedPTR.counter);
        std::swap(ptr,sharedPTR.ptr);
    }
    int useCount() const{
        if(counter) {
            return *counter;
        }
        else {
            return 0;
        }
        
    }
    bool unique() const {
        return (useCount() == 1);
    }
    
};
template< class T, class... Args >
SharedPTR<T> makeShared( Args&&... args ){
    return SharedPTR<T>(new T(std::forward<Args>(args)...));
}
