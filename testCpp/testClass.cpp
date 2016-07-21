//
//  testClass.cpp
//  testCpp
//
//  Created by Tiny on 16/4/26.
//  Copyright © 2016年 Tiny. All rights reserved.
//

#include "testClass.hpp"
#include <iostream>

void A::func1()
{
    std::cout << "hello" <<std::endl;
}
void A::func2()
{
}

A::A():a(0),b(0)
{
}
A::~A()
{
    printf("析构A\n");
}

B::B()
{
    
}
B::~B()
{
    printf("析构B\n");
}





