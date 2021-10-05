#pragma once

/*
* �߼���
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
    static CMyHash<CMyString, size_t, CStudent> s_student;              //�洢ѧ��
    static CMyHash<CMyString, size_t, CSubject> s_subject;              //�洢�γ�
    static CArray<CBST<size_t, CScore> *> s_aryScore;                   //�洢�ɼ�
};

//typedef struct tagTempTable
//{
//    CMyString stuName;
//    CMyString subName;
//    float fScore;
//}TABLE;

#pragma region ��������
void CreateData();
#pragma endregion



#pragma region ��ʼ������
bool Init();

/// <summary>
/// ��ȡѧ���ļ�
/// </summary>
bool ReadStu();

/// <summary>
/// ��ȡ�γ��ļ�
/// </summary>
bool ReadSub();

/// <summary>
/// ��ȡ�ɼ��ļ�
/// </summary>
bool ReadScore();
#pragma endregion


#pragma region ѧ������
/// <summary>
/// ���ѧ��
/// </summary>
/// <param name="szName">ѧ������</param>
/// <returns></returns>
bool InsertStu(char *szName);

/// <summary>
/// ɾ��ѧ��
/// </summary>
/// <param name="szName">ѧ��ID</param>
/// <returns></returns>
bool DeleteStu(size_t nID);

/// <summary>
/// �޸�ѧ��
/// </summary>
/// <param name="nID">ѧ��ID</param>
/// <param name="szName">�޸ĺ������</param>
/// <returns></returns>
bool UpdateStu(size_t nID, char *szName);

/// <summary>
/// ����ID��ѯ
/// </summary>
/// <param name="nID">Ҫ��ѯ��ID</param>
/// <param name="stu">���ز���</param>
/// <returns></returns>
bool QueryStuByID(size_t nID, CStudent &stu);

/// <summary>
/// ����������ѯ
/// </summary>
/// <param name="szName">ѧ������</param>
/// <returns></returns>
CQueue<CStudent> QueryStuByName(const char *szName);
#pragma endregion


#pragma region �γ̹���
/// <summary>
/// ��ӿγ�
/// </summary>
/// <param name="szName">�γ���</param>
/// <returns></returns>
bool InsertSub(char *szName);

/// <summary>
/// ɾ���γ�
/// </summary>
/// <param name="szName">�γ�ID</param>
/// <returns></returns>
bool DeleteSub(size_t nID);

/// <summary>
/// �޸Ŀγ�
/// </summary>
/// <param name="nID">�γ�ID</param>
/// <param name="szName">�޸ĺ�Ŀγ�</param>
/// <returns></returns>
bool UpdateSub(size_t nID, char *szName);

/// <summary>
/// ����ID��ѯ
/// </summary>
/// <param name="nID">Ҫ��ѯ��ID</param>
/// <param name="stu">���ز���</param>
/// <returns></returns>
bool QuerySubByID(size_t nID, CSubject &sub);

/// <summary>
/// ���ݿγ̲�ѯ
/// </summary>
/// <param name="szName">�γ���</param>
/// <returns></returns>
CQueue<CSubject> QuerySubByName(const char *szName);
#pragma endregion


#pragma region �ɼ�����
/// <summary>
/// ���ѡ�μ�¼
/// </summary>
/// <param name="nStuID">ѧ��ID</param>
/// <param name="nSubID">�γ�ID</param>
/// <param name="nScore">����</param>
/// <returns></returns>
bool InsertScore(size_t nStuID, size_t nSubID, float fScore = 0.0f);

/// <summary>
/// ɾ��ѡ�μ�¼
/// </summary>
/// <param name="nStuID">ѧ��ID</param>
/// <param name="nSubID">�γ�ID</param>
/// <returns></returns>
bool DeleteScore(size_t nStuID, size_t nSubID);

/// <summary>
/// �޸�ѡ���еĳɼ�
/// </summary>
/// <param name="nStuID"></param>
/// <param name="nSubID"></param>
/// <param name="nScore"></param>
/// <returns></returns>
bool UpdateScore(size_t nStuID, size_t nSubID, float fScore = 0.0f);

/// <summary>
/// ����ѧ��ID�Ϳγ�ID��ѯ
/// </summary>
/// <param name="nStuID">ѧ��ID</param>
/// <param name="nSubID">�γ�ID</param>
/// <param name="sre">���ز���</param>
/// <returns></returns>
bool QueryScoreByStuAndSub(size_t nStuID, size_t nSubID, CScore &sre);

/// <summary>
/// ����ѧ��ID��ѯ
/// </summary>
/// <param name="nStuID">ѧ��ID</param>
/// <returns></returns>
CQueue<CScore> QueryScoreByStu(size_t nStuID);

/// <summary>
/// ���ݿγ�ID��ѯ
/// </summary>
/// <param name="nSubID">�γ�ID</param>
/// <returns></returns>
CBST<size_t, CScore> QueryScoreBySub(size_t nSubID);

//CQueue<TABLE> GetTableInfo(CQueue<CScore> &qu);
#pragma endregion
