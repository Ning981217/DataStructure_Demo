#pragma once

/*
* �γ���
*/

#include <iostream>
#include "MyString.h"

#define STARTID 1                               //������ID��ʼֵ
#define STRIDE  1                               //ID����������

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

    //��װ
    size_t GetID();
    CMyString GetSubName();
    bool GetIsDelete();
    void SetIsDelete(bool isDelete);
    long GetOff();

    //��̬
    static size_t GetPrimaryKey();              //��ȡ����ID
    static void SetPrimaryKey(size_t nID);      //�޸�����ID

    //��ȡɾ�����λ��
    long GetLocationIsDel();

private:
    size_t m_nID;                               //�γ�ID
    size_t m_nSubjectSize;                      //�γ�������
    CMyString m_strSubject;                     //�γ���
    bool m_isDelete;                            //�Ƿ�ɾ��
    long m_lnOff;                               //��ǰ������ʼλ��
    size_t m_nSize;                             //�����ܳ���

    static size_t s_AutoincrementID;            //������ID

    void Init();                                //��ʼ��
};

