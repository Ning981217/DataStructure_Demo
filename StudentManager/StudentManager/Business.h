#pragma once

/*
* 逻辑层
*/

#include <fstream>

#include "MyString.h"
#include "MyAVLTree.h"
#include "MyHash.h"
#include "MyQueue.h"
#include "MyArray.h"
#include "Score.h"
#include "Student.h"
#include "Subject.h"

using namespace std;

class DataInfo
{
public:
    static CMyHash<CMyString, size_t, CStudent> s_student;              //存储学生
    static CMyHash<CMyString, size_t, CSubject> s_subject;              //存储课程
    static CArray<CBST<size_t, CScore> *> s_aryScore;                   //存储成绩
};

//typedef struct tagTempTable
//{
//    CMyString stuName;
//    CMyString subName;
//    float fScore;
//}TABLE;

#pragma region 数据生成
void CreateData();
#pragma endregion



#pragma region 初始化数据
bool Init();

/// <summary>
/// 读取学生文件
/// </summary>
bool ReadStu();

/// <summary>
/// 读取课程文件
/// </summary>
bool ReadSub();

/// <summary>
/// 读取成绩文件
/// </summary>
bool ReadScore();
#pragma endregion


#pragma region 学生管理
/// <summary>
/// 添加学生
/// </summary>
/// <param name="szName">学生姓名</param>
/// <returns></returns>
bool InsertStu(char *szName);

/// <summary>
/// 删除学生
/// </summary>
/// <param name="szName">学生ID</param>
/// <returns></returns>
bool DeleteStu(size_t nID);

/// <summary>
/// 修改学生
/// </summary>
/// <param name="nID">学生ID</param>
/// <param name="szName">修改后的姓名</param>
/// <returns></returns>
bool UpdateStu(size_t nID, char *szName);

/// <summary>
/// 根据ID查询
/// </summary>
/// <param name="nID">要查询的ID</param>
/// <param name="stu">返回参数</param>
/// <returns></returns>
bool QueryStuByID(size_t nID, CStudent &stu);

/// <summary>
/// 根据姓名查询
/// </summary>
/// <param name="szName">学生姓名</param>
/// <returns></returns>
CQueue<CStudent> QueryStuByName(const char *szName);
#pragma endregion


#pragma region 课程管理
/// <summary>
/// 添加课程
/// </summary>
/// <param name="szName">课程名</param>
/// <returns></returns>
bool InsertSub(char *szName);

/// <summary>
/// 删除课程
/// </summary>
/// <param name="szName">课程ID</param>
/// <returns></returns>
bool DeleteSub(size_t nID);

/// <summary>
/// 修改课程
/// </summary>
/// <param name="nID">课程ID</param>
/// <param name="szName">修改后的课程</param>
/// <returns></returns>
bool UpdateSub(size_t nID, char *szName);

/// <summary>
/// 根据ID查询
/// </summary>
/// <param name="nID">要查询的ID</param>
/// <param name="stu">返回参数</param>
/// <returns></returns>
bool QuerySubByID(size_t nID, CSubject &sub);

/// <summary>
/// 根据课程查询
/// </summary>
/// <param name="szName">课程名</param>
/// <returns></returns>
CQueue<CSubject> QuerySubByName(const char *szName);
#pragma endregion


#pragma region 成绩管理
/// <summary>
/// 添加选课记录
/// </summary>
/// <param name="nStuID">学生ID</param>
/// <param name="nSubID">课程ID</param>
/// <param name="nScore">分数</param>
/// <returns></returns>
bool InsertScore(size_t nStuID, size_t nSubID, float fScore = 0.0f);

/// <summary>
/// 删除选课记录
/// </summary>
/// <param name="nStuID">学生ID</param>
/// <param name="nSubID">课程ID</param>
/// <returns></returns>
bool DeleteScore(size_t nStuID, size_t nSubID);

/// <summary>
/// 修改选课中的成绩
/// </summary>
/// <param name="nStuID"></param>
/// <param name="nSubID"></param>
/// <param name="nScore"></param>
/// <returns></returns>
bool UpdateScore(size_t nStuID, size_t nSubID, float fScore = 0.0f);

/// <summary>
/// 根据学生ID和课程ID查询
/// </summary>
/// <param name="nStuID">学生ID</param>
/// <param name="nSubID">课程ID</param>
/// <param name="sre">返回参数</param>
/// <returns></returns>
bool QueryScoreByStuAndSub(size_t nStuID, size_t nSubID, CScore &sre);

/// <summary>
/// 根据学生ID查询
/// </summary>
/// <param name="nStuID">学生ID</param>
/// <returns></returns>
CQueue<CScore> QueryScoreByStu(size_t nStuID);

/// <summary>
/// 根据课程ID查询
/// </summary>
/// <param name="nSubID">课程ID</param>
/// <returns></returns>
CBST<size_t, CScore> QueryScoreBySub(size_t nSubID);

//CQueue<TABLE> GetTableInfo(CQueue<CScore> &qu);
#pragma endregion
