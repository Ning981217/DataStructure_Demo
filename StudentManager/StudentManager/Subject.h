#pragma once

/*
* 课程类
*/

#include <iostream>
#include "MyString.h"

#define STARTID 1                               //自增长ID初始值
#define STRIDE  1                               //ID的增长步长

class CSubject
{
public:
    CSubject();
    CSubject(const CSubject &sub);
    ~CSubject();
    CSubject &operator=(const CSubject &sub);

    CSubject(CMyString strSubject, long lnOff, size_t nID = GetPrimaryKey());

    friend std::ostream &operator<<(std::ostream &os, CSubject &sub);
    friend std::istream &operator>>(std::istream &is, CSubject &sub);

    //封装
    size_t GetID();
    CMyString GetSubName();
    bool GetIsDelete();
    void SetIsDelete(bool isDelete);
    long GetOff();

    //静态
    static size_t GetPrimaryKey();              //获取主键ID
    static void SetPrimaryKey(size_t nID);      //修改主键ID

    //获取删除标记位置
    long GetLocationIsDel();

private:
    size_t m_nID;                               //课程ID
    size_t m_nSubjectSize;                      //课程名长度
    CMyString m_strSubject;                     //课程名
    bool m_isDelete;                            //是否被删除
    long m_lnOff;                               //当前数据起始位置
    size_t m_nSize;                             //数据总长度

    static size_t s_AutoincrementID;            //自增长ID

    void Init();                                //初始化
};

