#pragma once
#include <iostream>
#include <stddef.h>

// Ошибок много, пройдусь по каждой функции.

template<typename Type, class TDeleter = std::default_delete<Type> >
class SharedPTR {
    using t_SharedPTR = SharedPTR<Type, TDeleter>;
private:
    Type* ptr = nullptr;
    size_t* counter = nullptr;

    // Если выделить память у counter, то else не нужен
    void incCounter() {
        if(ptr) {
            *counter++;
        }
        else {
            *counter = 0;
        }
    }
public:
    // Constructors and destructor.
    SharedPTR() = default;

// Не выделяешь память под counter через new. Поэтому у тебя не будет синхронизации счетчика ссылок между Shared Pointer'ами, которые ссылаются на один ресурс.
// И еще один вопрос: если pObj это nullptr, надо ли делать incCounter и вообще заводить его?)
// И используй пожалуйста во всех конструкторах member initializer list.
    SharedPTR(Type *pObj) {
        ptr = pObj; 
        incCounter();
        }
    // Move constructor.
    SharedPTR(t_SharedPTR &&uniquePTR) {
        ptr = uniquePTR.ptr;
        counter = uniquePTR.counter;
        uniquePTR.ptr = nullptr;
        uniquePTR.counter = 0;
    }
    SharedPTR(const t_SharedPTR& obj) {
        ptr = obj.ptr;
        counter = obj.counter;
        incCounter();
    }
    ~SharedPTR() {
        release();
    }
public: // Assignment.

    // А как же освободить this от владения текущим ресурсом. Надо сделать release.
    t_SharedPTR& operator=(t_SharedPTR &&sharedPTR) {
        if(ptr == sharedPTR.ptr) {
            return *this;
        }
        ptr = sharedPTR.ptr;
        counter = sharedPTR.counter;
        sharedPTR.ptr = nullptr;
        sharedPTR.counter = nullptr;
        return *this;
    }

    //Можно сделать в одну строчку типа *this = t_SharedPTR(pObject) что ли...
    t_SharedPTR& operator=(Type *pObject) {
        if(ptr == pObject){
            return *this;
        }
        else {
            ptr = pObject;
            return *this;
        }
        
    }
    //То же самое, надо release сделать
    t_SharedPTR& operator=(const t_SharedPTR& obj) {
        if(ptr == obj.ptr) {
            return *this;
        }
        ptr = obj.ptr;
        counter = obj.counter;
        incCounter();
        return *this;
    }
public: // Observers.


    // Dereference the stored pointer.
    // Здесь можно вернуть *get()
    Type& operator*() const {
        if(ptr!= nullptr)
            return *ptr;
        else{
            throw std::invalid_argument("ptr is NULL");
        }}
    // Return the stored pointer.
    //Здесь можно вернуть просто get()
    Type* operator->() const {
        if(ptr!= nullptr)
            return ptr;
        else{
            throw std::invalid_argument("ptr is NULL");
        }} 
    // Return the stored pointer. 
    Type* get() const {
        return ptr;
        } 
    // Return a reference to the stored deleter.
    TDeleter& get_deleter() {
        return TDeleter(); 
        } 
    // Return false if the stored pointer is null.
    operator bool() const {
        return(ptr != nullptr); 
        }
public:
     // Modifiers

    // Release ownership of any stored pointer.
    // последний if не нужен, просто делаешь (*counter)--
    // А вот во втором if нужно почистить ресурсы counter тоже, ну и в конце все указатели присвоить nullptr
    void release() {
        if (counter == nullptr) {
            return;
        }
        if(*counter == 1) {
            TDeleter()(ptr);
            return;
        }
        if(counter != nullptr){
            *counter--;
        }
    }
    // Replace the stored pointer.
    // Здесь можно вообще в одну строчку через оператор присваивания нового shared pointer
    void reset(Type *pObject = nullptr) {
        if(ptr == pObject) {
            std::invalid_argument("Nothing to reset");
        }
        else {
            pObject = ptr;
        }
        }

    // Exchange the pointer with another object.
    void swap(t_SharedPTR &sharedPTR) {
        std::swap(counter,sharedPTR.counter);
        std::swap(ptr,sharedPTR.ptr);
    }

// Добавь функцию use_count, которая будет возвращать значение counter.
// Добавь функциб unique() см cpp_reference

};
