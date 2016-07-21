//
//  testClass.hpp
//  testCpp
//
//  Created by Tiny on 16/4/26.
//  Copyright © 2016年 Tiny. All rights reserved.
//

#ifndef testClass_hpp
#define testClass_hpp

#include <stdio.h>




class A {
public:
    void func1();
    void func2();
public:
    A();
    virtual ~A();
private:
    int a ,b;
};

class B :public A {
public:
    B();
    virtual ~B();
};

#endif /* testClass_hpp */
