//
//  main.cpp
//  testCpp
//
//  Created by Tiny on 16/4/20.
//  Copyright © 2016年 Tiny. All rights reserved.
// 函数

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <list>
#include "testClass.hpp"

//节点结构
typedef   struct node
{
    int content;
    node* next;
}NODE;

using namespace std;

//创建新节点
node* creatNode(int i)
{
   return new node {i,NULL};
}

//倒序
node* reverse(node* head)
{
    node* cur = NULL;
    
    for (node* p = head; p != NULL ; ) {
        node* re_next = p->next;
        p->next = cur;
        cur = p;
        p = re_next;
    }
    return cur;
}

//后置插入 返回值为新的头
node* push_back(node* node , int content)
{
    NODE* res = new NODE {content,NULL};
    if (!node) {
        return res;
    }
    else{
        for (NODE* p1 = node; true; p1 = p1 -> next) {
            if(p1->next == NULL)
            {
                p1->next = res;
            }
        }
        return node;
    }
    return NULL;
}

//前置插入 返回值为新的头
node* push_front(node* node , int content)
{
    NODE* res = new NODE {content,node};
    return res;
}

//位后插入
bool insert_behind(NODE* tar,NODE* res)
{
    res->next = tar->next;
    tar->next = res;
    return true;
}

//位前插入
NODE* insert_front(NODE* tar,NODE* res,NODE* head)
{
    if (tar == res) {
        return head;
    }
    
    NODE* prev = head;
    if (tar == head) {
        res -> next = tar;
        head = res;
        return head;
    }
    
    for (NODE* p1 = head; p1 != NULL; p1 = p1 -> next) {
        if (p1 == tar) {
            prev->next = res;
            res -> next = p1;
            break;
        }
        prev = p1;
    }
    return head;
}

//删除节点
bool delete_node(NODE* tar,NODE* head)
{
    NODE* prev = head;
    for (NODE* p1 = head; p1 != NULL; p1 = p1 -> next) {
        if (p1 == tar) {
            prev -> next = p1->next;
            break;
        }
        prev = p1;
    }
    return true;
}

//交换
bool swap(NODE* p1,NODE* p2)
{
    NODE temp = *p1;
    *p1 = *p2;
    p1->next = temp.next;
    temp.next = p2->next;
    *p2 = temp;
    return true;
}

//序列新建

NODE* create_new_list(int head[],int array_size)
{
    NODE* h =  creatNode( head[array_size - 1]);
    for (int i = array_size - 2; i >= 0; i --) {
        h = push_front(h, head[i]);
    }
    return h;
}

//显示链表数据
bool show_list (NODE* head)
{
    cout << " | ";
    for (NODE* p1 = head; p1 != NULL; p1 = p1 -> next) {
        cout << p1->content <<" | ";
    }
    cout << endl;
    return true;
}

//得到顺序位
NODE* get_bit(NODE* head,int num)
{
    NODE* p1 = head;
    for (; p1 != NULL && num > 0; p1 = p1 -> next,num -- ) ;
    if (p1 == NULL) {
        cerr << "overflow" <<endl;;
        return NULL;
    }
    
    return p1;
}

//自己定义怎么样算作"大"
bool who_is_big(NODE* n1,NODE* n2)
{
    return n1->content > n2->content;
}

int get_rise(NODE* head)
{
    int sum = 0;
    for (NODE* p_ = head;  p_ != NULL ; p_ = p_-> next) {
        sum ++;
    }
    return sum;
}

//插入排序
NODE* insert_sort(NODE* head,bool func( NODE* n1,NODE* n2))
{
    for (NODE* p = head -> next; p != NULL;) {
        //先储存下一针方位
        NODE* p1 = p -> next;
        for (NODE* p_ = head; p_ != p && p_ != NULL ;) {
            //先储存下一针方位
            NODE* p2 = p_ -> next;
            if (func(p_,p)) {
                //删除原本节点
                delete_node(p,head);
                //插入合适位置
                head = insert_front(p_,p,head);
                break;
            }
            p_ = p2;
        }
        p = p1;
    }
    return head;
}



//选择排序
NODE* chooise_sort(NODE* head,bool func( NODE* n1,NODE* n2))
{
    int size =  get_rise(head);
    for (int i = 0 ; i < size - 1; i ++) {
        NODE* head_res = get_bit(head,i);
        NODE* small  = head_res;
        for (NODE* p = head_res; p != NULL; p = p->next) {
            if (func(small,p)) {
                small = p;
            }
        }
        
        delete_node(small, head);
        insert_front(get_bit(head,i), small, head);
        if (i == 0) {
            head = small;
        }
    }
    return head;
}

//冒泡排序
NODE* moo_sort(NODE* head,bool func( NODE* n1,NODE* n2))
{
    int size =  get_rise(head);
    for (int i = 0 ; i < size ; i ++) {
        NODE* p = head ;
        int j = 0;
        NODE* prev = head;
        for ( ; ((p != NULL) && (j <= (size - i))) ; j++,p = p->next ) {
            
            if (func(prev , p)) {
                if (j == 0) {
                    head = p;
                }
                swap(prev,p);
            }
            prev = p;
        }
    }
    return head;
}

void quick_sort(int s[],int l,int r)
{
    if(l < r)
    {
        //Swap(s[l],s[(l+r)/2]);//将中间这个数和第一个数交换
        int i = l,j = r ,x = s[l];
        // 0 , 9 , 3
        while (i < j) {
            while (i < j && s[j] >= x) {
                //如果i,j没有重合，并且 中间量小于 右边界量，缩小右边界
                j--;
            }
            // j = 8
            if(i < j)
            {
                //左基准数位置被右边待交换数字替换，并且步进i++到下一个左边的带判断位
                s[i ++] = s[j];
            }
            // 2,1,9,6,0,5,8,4,2,7
            while (i < j && s[i] < x)
            {
                //如果i,j没有重合，并且 中间量 大于左边界量，缩小左边界
                i ++ ;
            }
            //i = 2
            if (i < j)
            {
                //
                s[j --] = s[i];
            }
            // 2,1,9,6,0,5,8,4,9,7
            
            // i = 2,j = 7 ,x =3
            
        }
        
        s[i] = x;
        
        cout << " | ";
        for (int k = l; k <= r; k ++) {
            cout  << s[k] << " | ";
        }
        cout <<endl;
        
        quick_sort(s, l, i - 1);//递归调用
        quick_sort(s, i+1, r);
    }
}

void split(char* words[] , char fd[] , int size)
{
    
//    char* words[20];
    for (int i =0; i < 20; i++) {
        words[i] = NULL;
    }
    char fd_copy[size];
    strcpy(fd_copy, fd);
    int i =0;
    words[i] = fd_copy;
    for (char* p = fd_copy ; *p != '\0'  ; p++) {
        if (*p == ' ') {
            while (*(p + 1) == ' ') {
                p++;
            }
            *p = '\0';
            i++;
            words[i] = p + 1 ;
        }
    }
    
    for (int i = 0; i < 20; i ++) {
        
        if (words[i] == NULL) {
            break;
        }
        char * p_ =  new char (strlen(words[i]));
        strcpy(p_ , words[i]);
        words[i] = p_;
    }
}


int main(int argc, const char * argv[]) {
//    int hh[10] = {3,1,9,6,0,5,8,4,2,7};
//    cout << " | ";
//    for (int i = 0; i < 10; i ++) {
//        cout << hh[i] << " | ";
//    }
//    cout << endl;
//    NODE* head = create_new_list(hh,10);
//    show_list(head);
//    
//    head =  reverse(head);
//    show_list(head);
//    
//    NODE* xx = get_bit(head,3);
//    NODE* yy = get_bit(head,7);
//    swap(xx,yy);
//    show_list(head);
//    
//    delete_node(yy,head);
//    show_list(head);
    
//    head = insert_front(head,yy,head);
//    show_list(head);
//
//    head =  insert_sort(head,who_is_big);
//    show_list(head);
    
//    head =  chooise_sort(head,who_is_big);
//    show_list(head);
    
//    head = moo_sort(head,who_is_big);
//    show_list(head);
    
//    quick_sort(hh, 0, 9);
//    for (int i =0; i < 10; i ++) {
//        cout << hh[i] << endl;
//     }
    
//    cout << get_rise(head);
//    char fd[100];
//    cin.getline(fd,100);
//    
//    char* words[20];
//    split(words , fd, 100);
//    
//    for (int i = 0; i < 20; i ++) {
//        if (words[i] == NULL) {
//            break;
//        }
//        cout << words[i] << endl;
//    }
    
    A* a = new A();
    A* b = new B();
    
    delete a;
    delete b;
    
    return 0;
}



