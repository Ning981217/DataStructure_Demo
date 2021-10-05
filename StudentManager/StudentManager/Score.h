#pragma once

/*
* �ɼ���
*/

#include <iostream>

#define STARTID 1                               //������ID��ʼֵ
#define STRIDE  1                               //ID����������

class CScore
{
public:
    CScore();
    CScore(const CScore &sor);
    ~CScore();
    CScore &operator=(const CScore &sor);

    CScore(size_t nStuID, size_t nSubjectID, float fScore, long lnOff);

    friend std::ostream &operator<<(std::ostream &os, CScore &sor);
    friend std::istream &operator>>(std::istream &is, CScore &sor);

    //��װ
    size_t GetID();
    size_t GetStuID();
    void SetStuID(size_t nStuID);
    size_t GetSubjectID();
    void SetSubjectID(size_t nSubjectID);
    float GetScore();
    void SetScore(float fScore);
    bool GetIsDelete();
    void SetIsDelete(bool isDelete);
    long GetOff();

    //��̬
    static size_t GetPrimaryKey();              //��ȡ����ID
    static void SetPrimaryKey(size_t nID);      //�޸�����ID

    //��ȡɾ�����λ��
    long GetLocationIsDel();

private:
    size_t m_nID;                               //����ID
    size_t m_nStuID;                            //ѧ��ID
    size_t m_nSubjectID;                        //ѧ��ID
    float m_fScore;                             //����
    bool m_isDelete;                            //�Ƿ�ɾ��
    long m_lnOff;                               //��ǰ������ʼλ��
    size_t m_nSize;                             //�����ܳ���

    static size_t s_AutoincrementID;            //������ID

    void Init();                                //��ʼ��
};

