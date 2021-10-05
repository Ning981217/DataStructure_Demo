#include "Subject.h"

size_t CSubject::s_AutoincrementID = STARTID;

CSubject::CSubject()
{
    Init();
}

CSubject::CSubject(const CSubject &sub)
{
    *this = sub;
}

CSubject::~CSubject()
{
}

CSubject &CSubject::operator=(const CSubject &sub)
{
    this->m_nID = sub.m_nID;
    this->m_nSubjectSize = sub.m_nSubjectSize;
    this->m_strSubject = sub.m_strSubject;
    this->m_isDelete = sub.m_isDelete;
    this->m_lnOff = sub.m_lnOff;
    this->m_nSize = sub.m_nSize;

    return *this;
}

CSubject::CSubject(CMyString strSubject, long lnOff, size_t nID)
    :m_strSubject(strSubject), m_lnOff(lnOff)
{
    this->m_nID = nID;
    this->m_nSubjectSize = strSubject.GetLen() + 1;
    this->m_isDelete = false;
    this->m_nSize =
        sizeof(this->m_nID) +
        sizeof(this->m_nSubjectSize) +
        this->m_nSubjectSize +
        sizeof(this->m_isDelete) +
        sizeof(this->m_lnOff) +
        sizeof(this->m_nSize);
}

std::ostream &operator<<(std::ostream &os, CSubject &sub)
{
    os.write((char *)&sub.m_nID, sizeof(sub.m_nID));
    os.write((char *)&sub.m_nSubjectSize, sizeof(sub.m_nSubjectSize));
    os.write(sub.m_strSubject.GetStr(), sub.m_nSubjectSize);
    os.write((char *)&sub.m_isDelete, sizeof(sub.m_isDelete));
    os.write((char *)&sub.m_lnOff, sizeof(sub.m_lnOff));
    os.write((char *)&sub.m_nSize, sizeof(sub.m_nSize));

    //更新静态ID
    CSubject::SetPrimaryKey(sub.m_nID + STRIDE);

    return os;
}

std::istream &operator>>(std::istream &is, CSubject &sub)
{
    //存储读取到的临时课程
    char *szSubject = nullptr;

    //nID
    is.read((char *)&sub.m_nID, sizeof(sub.m_nID));

    //nSubjectSize
    is.read((char *)&sub.m_nSubjectSize, sizeof(sub.m_nSubjectSize));

    //strSubject
    szSubject = new char[sub.m_nSubjectSize]{ '\0' };
    if (szSubject == nullptr)
    {
        //清掉数据，申请内存失败
        sub.m_nID = 0;
        sub.m_nSubjectSize = 0;

        return is;
    }
    is.read(szSubject, sub.m_nSubjectSize);
    sub.m_strSubject = szSubject;
    delete[] szSubject;

    //isDelete
    is.read((char *)&sub.m_isDelete, sizeof(sub.m_isDelete));

    //lnOff
    is.read((char *)&sub.m_lnOff, sizeof(sub.m_lnOff));

    //nSize
    is.read((char *)&sub.m_nSize, sizeof(sub.m_nSize));

    //更新静态ID
    CSubject::SetPrimaryKey(sub.m_nID + STRIDE);

    return is;
}

size_t CSubject::GetID()
{
    return this->m_nID;
}

CMyString CSubject::GetSubName()
{
    return this->m_strSubject;
}

bool CSubject::GetIsDelete()
{
    return this->m_isDelete;;
}

void CSubject::SetIsDelete(bool isDelete)
{
    this->m_isDelete = isDelete;
}

long CSubject::GetOff()
{
    return this->m_lnOff;
}

size_t CSubject::GetPrimaryKey()
{
    return s_AutoincrementID;
}

void CSubject::SetPrimaryKey(size_t nID)
{
    if (nID > s_AutoincrementID)
    {
        s_AutoincrementID = nID;
    }
}

long CSubject::GetLocationIsDel()
{
    return this->GetOff() +
        sizeof(this->m_nID) +
        sizeof(this->m_nSubjectSize) +
        this->m_nSubjectSize;
}

void CSubject::Init()
{
    this->m_nID = 0;                      //课程ID
    this->m_nSubjectSize = 0;             //课程名长度
    this->m_strSubject;                   //课程名
    this->m_isDelete = false;             //是否被删除
    this->m_lnOff = 0;                    //当前数据起始位置
    this->m_nSize = 0;                    //数据总长度
}
