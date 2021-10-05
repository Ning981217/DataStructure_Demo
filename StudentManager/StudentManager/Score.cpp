#include "Score.h"

size_t CScore::s_AutoincrementID = STARTID;

CScore::CScore()
{
    Init();
}

CScore::CScore(const CScore &sor)
{
    *this = sor;
}

CScore::~CScore()
{
}

CScore &CScore::operator=(const CScore &sor)
{
    this->m_nID = sor.m_nID;
    this->m_nStuID = sor.m_nStuID;
    this->m_nSubjectID = sor.m_nSubjectID;
    this->m_fScore = sor.m_fScore;
    this->m_isDelete = sor.m_isDelete;
    this->m_lnOff = sor.m_lnOff;
    this->m_nSize = sor.m_nSize;

    return *this;
}

std::ostream &operator<<(std::ostream &os, CScore &sor)
{
    os.write((char *)&sor.m_nID, sizeof(sor.m_nID));
    os.write((char *)&sor.m_nStuID, sizeof(sor.m_nStuID));
    os.write((char *)&sor.m_nSubjectID, sizeof(sor.m_nSubjectID));
    os.write((char *)&sor.m_fScore, sizeof(sor.m_fScore));
    os.write((char *)&sor.m_isDelete, sizeof(sor.m_isDelete));
    os.write((char *)&sor.m_lnOff, sizeof(sor.m_lnOff));
    os.write((char *)&sor.m_nSize, sizeof(sor.m_nSize));

    //更新静态ID
    CScore::SetPrimaryKey(sor.m_nID + STRIDE);

    return os;
}

std::istream &operator>>(std::istream &is, CScore &sor)
{
    is.read((char *)&sor.m_nID, sizeof(sor.m_nID));
    is.read((char *)&sor.m_nStuID, sizeof(sor.m_nStuID));
    is.read((char *)&sor.m_nSubjectID, sizeof(sor.m_nSubjectID));
    is.read((char *)&sor.m_fScore, sizeof(sor.m_fScore));
    is.read((char *)&sor.m_isDelete, sizeof(sor.m_isDelete));
    is.read((char *)&sor.m_lnOff, sizeof(sor.m_lnOff));
    is.read((char *)&sor.m_nSize, sizeof(sor.m_nSize));

    size_t temp = sor.m_nID;

    //更新静态ID
    CScore::SetPrimaryKey(sor.m_nID + STRIDE);

    return is;
}

CScore::CScore(size_t nStuID, size_t nSubjectID, float fScore, long lnOff)
    : m_nStuID(nStuID), m_nSubjectID(nSubjectID), m_fScore(fScore), m_lnOff(lnOff)
{
    this->m_nID = CScore::GetPrimaryKey();
    this->m_isDelete = false;
    this->m_nSize = sizeof(CScore);
}

size_t CScore::GetID()
{
    return this->m_nID;;
}

size_t CScore::GetStuID()
{
    return this->m_nStuID;
}

void CScore::SetStuID(size_t nStuID)
{
    this->m_nStuID = nStuID;
}

size_t CScore::GetSubjectID()
{
    return this->m_nSubjectID;
}

void CScore::SetSubjectID(size_t nSubjectID)
{
    this->m_nSubjectID = nSubjectID;
}

float CScore::GetScore()
{
    return this->m_fScore;
}

void CScore::SetScore(float fScore)
{
    this->m_fScore = fScore;
}

bool CScore::GetIsDelete()
{
    return this->m_isDelete;
}

void CScore::SetIsDelete(bool isDelete)
{
    this->m_isDelete = isDelete;
}

long CScore::GetOff()
{
    return this->m_lnOff;
}

size_t CScore::GetPrimaryKey()
{
    return s_AutoincrementID;
}

void CScore::SetPrimaryKey(size_t nID)
{
    if (nID > s_AutoincrementID)
    {
        s_AutoincrementID = nID;
    }
}

long CScore::GetLocationIsDel()
{
    return  sizeof(this->m_nID) +
        sizeof(this->m_nStuID) +
        sizeof(this->m_nSubjectID) +
        sizeof(this->m_fScore);
}

void CScore::Init()
{
    this->m_nID = 0;                               //主键ID
    this->m_nStuID = 0;                            //学生ID
    this->m_nSubjectID = 0;                        //学生ID
    this->m_fScore = 0.0f;                         //分数
    this->m_isDelete = false;                      //是否被删除
    this->m_lnOff = 0;                             //当前数据起始位置
    this->m_nSize = 0;                             //数据总长度
}
