#include "Student.h"

//自增长ID从1开始
size_t CStudent::s_AutoincrementID = STARTID;

CStudent::CStudent()
{
    Init();
}

CStudent::CStudent(const CStudent &stu)
{
    *this = stu;
}

CStudent::~CStudent()
{
}

CStudent &CStudent::operator=(const CStudent &stu)
{
    this->m_nID = stu.m_nID;
    this->m_nNameSize = stu.m_nNameSize;
    this->m_strName = stu.m_strName;
    this->m_isDelete = stu.m_isDelete;
    this->m_lnOff = stu.m_lnOff;
    this->m_nSize = stu.m_nSize;

    return *this;
}

CStudent::CStudent(CMyString strName, long lnOff, size_t nID)
    :m_strName(strName), m_lnOff(lnOff)
{
    this->m_nID = nID;
    this->m_nNameSize = strName.GetLen() + 1;
    this->m_isDelete = false;
    this->m_nSize =
        sizeof(this->m_nID) +                               //nID
        sizeof(this->m_nNameSize) +                         //nNameSize
        this->m_nNameSize +                                 //strName
        sizeof(this->m_isDelete) +                          //isDelete
        sizeof(this->m_lnOff) +                             //lnOff
        sizeof(this->m_nSize);                              //nSize
}

std::ostream &operator<<(std::ostream &os, CStudent &stu)
{
    os.write((char *)&stu.m_nID, sizeof(stu.m_nID));
    os.write((char *)&stu.m_nNameSize, sizeof(stu.m_nNameSize));
    os.write(stu.m_strName.GetStr(), stu.m_strName.GetLen() + 1);
    os.write((char *)&stu.m_isDelete, sizeof(stu.m_isDelete));
    os.write((char *)&stu.m_lnOff, sizeof(stu.m_lnOff));
    os.write((char *)&stu.m_nSize, sizeof(stu.m_nSize));

    //更新静态ID
    CStudent::SetPrimaryKey(stu.m_nID + STRIDE);

    return os;
}

std::istream &operator>>(std::istream &is, CStudent &stu)
{
    //存储读取到的临时姓名
    char *szName = nullptr;

    //nID
    is.read((char *)&stu.m_nID, sizeof(stu.m_nID));

    //nNameSize
    is.read((char *)&stu.m_nNameSize, sizeof(stu.m_nNameSize));

    //strName
    szName = new char[stu.m_nNameSize]{ '\0' };
    if (szName == nullptr)
    {
        //清掉数据，申请内存失败
        stu.m_nID = 0;
        stu.m_nNameSize = 0;

        return is;
    }
    is.read(szName, stu.m_nNameSize);
    stu.m_strName = szName;
    delete[] szName;

    //isDelete
    is.read((char *)&stu.m_isDelete, sizeof(stu.m_isDelete));

    //lnOff
    is.read((char *)&stu.m_lnOff, sizeof(stu.m_lnOff));

    //nSize
    is.read((char *)&stu.m_nSize, sizeof(stu.m_nSize));

    //更新静态ID
    CStudent::SetPrimaryKey(stu.m_nID + STRIDE);

    return is;
}

size_t CStudent::GetID()
{
    return this->m_nID;
}

CMyString CStudent::GetStuName()
{
    return this->m_strName;
}

bool CStudent::GetIsDelete()
{
    return this->m_isDelete;
}

void CStudent::SetIsDelete(bool isDelete)
{
    this->m_isDelete = isDelete;
}

long CStudent::GetOff()
{
    return this->m_lnOff;
}

size_t CStudent::GetPrimaryKey()
{
    return s_AutoincrementID;
}

void CStudent::SetPrimaryKey(size_t nID)
{
    if (nID > s_AutoincrementID)
    {
        s_AutoincrementID = nID;
    }
}

long CStudent::GetLocationIsDel()
{
    return this->GetOff() +
        sizeof(this->m_nID) +
        sizeof(this->m_nNameSize) +
        this->m_nNameSize;
}

void CStudent::Init()
{
    this->m_nID = 0;                    //学生ID
    this->m_nNameSize = 0;              //姓名长度
    this->m_strName;                    //学生姓名
    this->m_isDelete = false;           //是否被删除
    this->m_lnOff = 0;                  //当前数据起始位置
    this->m_nSize = 0;                  //数据总长度
}