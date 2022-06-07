#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <map>
#include <memory>
#include <vector>

using defaultIDKeyType = std::string;

/**
    The abstract factory.
    Implemented using the Singleton pattern
*/
template <class manufacturedObj, typename classIDKey=defaultIDKeyType>
class genericFactory
{
    /* The following is C++11's typedef for a pointer to a function!
	 a BASE_CREATE_FN is a static factory method: a function that
     returns an smart pointer to a manufactuedObj.  Note that you can customize
     the type of parameters to allow overloaded ctors*/
     using BASE_CREATE_FN = std::unique_ptr<manufacturedObj> (*) (const std::string &par); 

    /* FN_REGISTRY is the registry of all the BASE_CREATE_FN
     pointers registered.  Functions are registered using the
     regCreateFn member function (see below).*/
    using FN_REGISTRY = std::map<classIDKey, BASE_CREATE_FN>;
    FN_REGISTRY registry;

    /* Singleton implementation */
    genericFactory():registry(){ }
    genericFactory(const genericFactory&) = delete; // Ruled out
    genericFactory &operator=(const genericFactory&) = delete; // Ruled out
public:

    /// Singleton access.
    static genericFactory &instance(){
        static genericFactory<manufacturedObj> inst;
        return inst;
    }

    /// Classes derived from manufacturedObj call this function once
    /// per program to register the class ID key, and a pointer to
    /// the function that creates the class.
    void regCreateFn(const classIDKey &k, BASE_CREATE_FN f){
        registry[k] = f;
    }

    /// Create a new class of the type specified by className.
    std::unique_ptr<manufacturedObj> create(const classIDKey &className,
						const std::string &param) const
        {   
            std::unique_ptr<manufacturedObj> ret(nullptr);
            typename FN_REGISTRY::const_iterator regEntry = registry.find(className);
            if(regEntry != registry.end()){
                return (*regEntry).second(param);
            }
            return ret;
        }
};

/// Helper template to make registration simple.
template <class ancestorType, class manufacturedObj, typename classIDKey=defaultIDKeyType>
class registerInFactory {
public:
    static std::unique_ptr<ancestorType> createInstance(const std::string &par){
        return std::unique_ptr<ancestorType>(manufacturedObj::createInstance(par));
    }
    registerInFactory(const classIDKey &id){
        genericFactory<ancestorType>::instance().regCreateFn(id,createInstance);
    }
};

#endif
