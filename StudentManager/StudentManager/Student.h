#pragma once

/*
* 学生类
*/

#include <iostream>
#include "MyString.h"

#define STARTID 1                               //自增长ID初始值
#define STRIDE  1                               //ID的增长步长

class CStudent
{
public:
    CStudent();
    CStudent(const CStudent &stu);
    ~CStudent();
    CStudent &operator=(const CStudent &stu);

    CStudent(CMyString m_strName, long lnOff, size_t nID = GetPrimaryKey());

    friend std::ostream &operator<<(std::ostream &os, CStudent &stu);
    friend std::istream &operator>>(std::istream &is, CStudent &stu);

    //封装
    size_t GetID();
    CMyString GetStuName();
    bool GetIsDelete();
    void SetIsDelete(bool isDelete);
    long GetOff();

    //静态
    static size_t GetPrimaryKey();              //获取主键ID
    static void SetPrimaryKey(size_t nID);      //修改主键ID

    //获取删除标记位置
    long GetLocationIsDel();

private:
    size_t m_nID;                               //学生ID
    size_t m_nNameSize;                         //姓名长度
    CMyString m_strName;                        //学生姓名
    bool m_isDelete;                            //是否被删除
    long m_lnOff;                               //当前数据起始位置
    size_t m_nSize;                             //数据总长度

    static size_t s_AutoincrementID;            //自增长ID

    void Init();                                //初始化
};

