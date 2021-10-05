#pragma once

/*
* ѧ����
*/

#include <iostream>
#include "MyString.h"

#define STARTID 1                               //������ID��ʼֵ
#define STRIDE  1                               //ID����������

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

    //��װ
    size_t GetID();
    CMyString GetStuName();
    bool GetIsDelete();
    void SetIsDelete(bool isDelete);
    long GetOff();

    //��̬
    static size_t GetPrimaryKey();              //��ȡ����ID
    static void SetPrimaryKey(size_t nID);      //�޸�����ID

    //��ȡɾ�����λ��
    long GetLocationIsDel();

private:
    size_t m_nID;                               //ѧ��ID
    size_t m_nNameSize;                         //��������
    CMyString m_strName;                        //ѧ������
    bool m_isDelete;                            //�Ƿ�ɾ��
    long m_lnOff;                               //��ǰ������ʼλ��
    size_t m_nSize;                             //�����ܳ���

    static size_t s_AutoincrementID;            //������ID

    void Init();                                //��ʼ��
};

