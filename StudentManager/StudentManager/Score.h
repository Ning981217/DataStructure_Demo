#pragma once

/*
* 成绩类
*/

#include <iostream>

#define STARTID 1                               //自增长ID初始值
#define STRIDE  1                               //ID的增长步长

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

    //封装
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

    //静态
    static size_t GetPrimaryKey();              //获取主键ID
    static void SetPrimaryKey(size_t nID);      //修改主键ID

    //获取删除标记位置
    long GetLocationIsDel();

private:
    size_t m_nID;                               //主键ID
    size_t m_nStuID;                            //学生ID
    size_t m_nSubjectID;                        //学生ID
    float m_fScore;                             //分数
    bool m_isDelete;                            //是否被删除
    long m_lnOff;                               //当前数据起始位置
    size_t m_nSize;                             //数据总长度

    static size_t s_AutoincrementID;            //自增长ID

    void Init();                                //初始化
};

