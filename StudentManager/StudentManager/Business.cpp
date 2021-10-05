#include "Business.h"

CMyHash<CMyString, size_t, CStudent> DataInfo::s_student;              //�洢ѧ��
CMyHash<CMyString, size_t, CSubject> DataInfo::s_subject;              //�洢�γ�
CArray<CBST<size_t, CScore> *> DataInfo::s_aryScore;                   //�洢�ɼ�

void CreateData()
{
    //student
    fstream fs;
    fs.open("StudentInfo.data", ios::trunc | ios::out | ios::binary);
    if (!fs.is_open())
    {
        return;
    }
    long lnOff = 0;
    for (size_t i = 0; i < 100000; i++)
    {
        CMyString str(CMyString::ValueOf((int)i).Append("����"));
        CStudent stu(str, lnOff);
        fs << stu;
        lnOff = fs.tellp();
    }
    fs.close();

    //subject
    fs.open("SubjectInfo.data", ios::trunc | ios::out | ios::binary);
    if (!fs.is_open())
    {
        return;
    }
    fstream fsTxt;
    fsTxt.open("course.txt", ios::in | ios::binary);
    if (!fsTxt.is_open())
    {
        return;
    }
    lnOff = 0;
    while (fsTxt.peek() != EOF)
    {
        char szName[100];
        fsTxt.getline(szName, 100);
        //����β��\r
        if (szName[strlen(szName) - 1] == '\r')
        {
            szName[strlen(szName) - 1] = '\0';
        }
        CSubject sub(szName, lnOff);
        fs << sub;
        lnOff = fs.tellp();
    }
    fsTxt.close();
    fs.close();

    //score
    fs.open("ScoreInfo.data", ios::trunc | ios::out | ios::binary);
    if (!fs.is_open())
    {
        return;
    }
    lnOff = 0;
    for (size_t i = 0; i < CStudent::GetPrimaryKey(); i++)
    {
        CList<size_t> randomList;
        for (size_t j = 0; j < 10; j++)
        {
            //��֤�γ̲��ظ�
            size_t nSubID = 0;
            bool isBreak = true;
            while (true)
            {
                nSubID = rand() % CSubject::GetPrimaryKey() + 1;
                for (auto num : randomList)
                {
                    if (nSubID == num)
                    {
                        isBreak = false;
                        break;
                    }
                    else
                    {
                        isBreak = true;
                    }
                }

                if (isBreak)
                {
                    break;
                }
            }
            randomList.InsertTail(nSubID);

            size_t nScore = rand() % 101;
            CScore elective(i, nSubID, nScore, lnOff);

            fs << elective;
            lnOff = fs.tellp();
        }
    }
    fs.close();
}

bool Init()
{
    return ReadStu() &&
        ReadSub() &&
        ReadScore();
}

bool ReadStu()
{
    //���ļ�
    fstream fs;
    fs.open("StudentInfo.data", ios::in | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //��
    while (fs.peek() != EOF)
    {
        CStudent stu;
        fs >> stu;
        if (!stu.GetIsDelete())
        {
            //��ӵ��ڴ���
            DataInfo::s_student.Insert(stu.GetStuName(), stu.GetID(), stu);
        }
    }
    //�ر�
    fs.close();

    return true;
}

bool ReadSub()
{
    //���ļ�
    fstream fs;
    fs.open("SubjectInfo.data", ios::in | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //��
    while (fs.peek() != EOF)
    {
        CSubject sub;
        fs >> sub;
        if (!sub.GetIsDelete())
        {
            //��ӵ��ڴ���
            DataInfo::s_subject.Insert(sub.GetSubName(), sub.GetID(), sub);
        }
    }
    //�ر�
    fs.close();

    return true;
}

bool ReadScore()
{
    //���ļ�
    fstream fs;
    fs.open("ScoreInfo.data", ios::in | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //��̬�����ʼ��
    for (size_t i = 0; i < CSubject::GetPrimaryKey(); i++)
    {
        CBST<size_t, CScore> *pTree = new CBST<size_t, CScore>();
        DataInfo::s_aryScore.InsertTail(pTree);
    }
    //��
    while (fs.peek() != EOF)
    {
        CScore sre;
        fs >> sre;
        int a = sre.GetSubjectID();
        if (!sre.GetIsDelete())
        {
            //��Ӷ����ڴ�
            /*if (sre.GetSubjectID() > DataInfo::s_aryScore.GetLen())
            {
                CBST<size_t, CScore> *pTree = new CBST<size_t, CScore>();
                pTree->Insert(sre.GetStuID(), sre);
                DataInfo::s_aryScore.InsertTail(pTree);
            }
            else
            {
                DataInfo::s_aryScore[sre.GetSubjectID() - 1]->Insert(sre.GetStuID(), sre);
            }*/
            DataInfo::s_aryScore[sre.GetSubjectID() - 1]->Insert(sre.GetStuID(), sre);
        }
    }
    //�ر�
    fs.close();

    return true;
}

bool InsertStu(char *szName)
{
    //���ļ�
    fstream fs;
    fs.open("StudentInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //��ȡ���ݴ���λ��
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //��������
    CStudent stu(szName, lnOff);

    //��Ӷ����ڴ�
    DataInfo::s_student.Insert(stu.GetStuName(), stu.GetID(), stu);

    //��Ӷ����ļ�
    fs << stu;

    //�ر��ļ�
    fs.close();

    return true;
}

bool DeleteStu(size_t nID)
{
    //���Ҷ���
    CStudent stu;
    if (!QueryStuByID(nID, stu))
    {
        return false;
    }

    //���ļ�
    fstream fs;
    fs.open("StudentInfo.data", ios::in | ios::out | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //ɾ������
    stu.SetIsDelete(true);
    DataInfo::s_student.Delete(stu.GetStuName(), stu.GetID());

    //��ȡɾ��λ��
    bool isDel = stu.GetIsDelete();
    fs.seekp(stu.GetLocationIsDel(), ios_base::beg);

    //д��
    fs.write((char *)&isDel, sizeof(isDel));

    //�ر�
    fs.close();

    //ɾ����Ӧ�ɼ���
    CQueue<CScore> quScore = QueryScoreByStu(stu.GetID());
    while (!quScore.IsEmpty())
    {
        size_t nSubID = quScore.Front().GetSubjectID();
        DeleteScore(stu.GetID(), nSubID);
        quScore.Pop();
    }

    return true;
}

bool UpdateStu(size_t nID, char *szName)
{
    //���ļ�
    fstream fs;
    fs.open("StudentInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //ɾ��ԭ����
    if (!DeleteStu(nID))
    {
        fs.close();
        return false;
    }

    //��ȡ���ݴ���λ��
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //�����¶���
    CStudent stuNew(szName, lnOff, nID);

    //��Ӷ����ڴ�
    DataInfo::s_student.Insert(stuNew.GetStuName(), nID, stuNew);

    //��Ӷ����ļ�
    fs << stuNew;

    //�ر��ļ�
    fs.close();

    return true;
}

bool QueryStuByID(size_t nID, CStudent &stu)
{
    //���Ҷ���
    for (size_t i = 0; i < TABLE_LEN; i++)
    {
        //CBST<size_t, CStudent> item = ;
        if (DataInfo::s_student[i].Find(nID, stu))
        {
            return true;
        }
    }

    return false;
}

CQueue<CStudent> QueryStuByName(const char *szName)
{
    CQueue<CStudent> qu;

    for (size_t i = 0; i < TABLE_LEN; i++)
    {
        CQueue<CStudent> tempQu = DataInfo::s_student[i].LMR_LOOP();
        while (!tempQu.IsEmpty())
        {
            CStudent tempStu = tempQu.Front();
            if (tempStu.GetStuName() == szName)
            {
                qu.Push(tempStu);
            }
            tempQu.Pop();
        }
    }

    return qu;
}

bool InsertSub(char *szName)
{
    //���ļ�
    fstream fs;
    fs.open("SubjectInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //��ȡ���ݴ���λ��
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //��������
    CSubject sub(szName, lnOff);

    //��Ӷ����ڴ�
    DataInfo::s_subject.Insert(sub.GetSubName(), sub.GetID(), sub);

    //��Ӷ����ļ�
    fs << sub;

    //�ر��ļ�
    fs.close();

    return true;
}

bool DeleteSub(size_t nID)
{
    //���Ҷ���
    CSubject sub;
    if (!QuerySubByID(nID, sub))
    {
        return false;
    }

    //���ļ�
    fstream fs;
    fs.open("SubjectInfo.data", ios::in | ios::out | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //ɾ������
    sub.SetIsDelete(true);
    DataInfo::s_subject.Delete(sub.GetSubName(), sub.GetID());

    //��ȡɾ��λ��
    bool isDel = sub.GetIsDelete();
    fs.seekp(sub.GetLocationIsDel(), ios_base::beg);

    //д��
    fs.write((char *)&isDel, sizeof(isDel));

    //�ر�
    fs.close();

    //ɾ����Ӧ�ɼ���
    CBST<size_t, CScore> tree = QueryScoreBySub(nID);
    CQueue<CScore> quScore = tree.LMR_LOOP();
    while (!quScore.IsEmpty())
    {
        size_t nStuID = quScore.Front().GetStuID();
        DeleteScore(nStuID, sub.GetID());
        quScore.Pop();
    }

    return true;
}

bool UpdateSub(size_t nID, char *szName)
{
    //���ļ�
    fstream fs;
    fs.open("SubjectInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //ɾ��ԭ����
    if (!DeleteSub(nID))
    {
        fs.close();
        return false;
    }

    //��ȡ���ݴ���λ��
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //�����¶���
    CSubject subNew(szName, lnOff, nID);

    //��Ӷ����ڴ�
    DataInfo::s_subject.Insert(subNew.GetSubName(), subNew.GetID(), subNew);

    //��Ӷ����ļ�
    fs << subNew;

    //�ر��ļ�
    fs.close();

    return true;
}

bool QuerySubByID(size_t nID, CSubject &sub)
{
    //���Ҷ���
    for (size_t i = 0; i < TABLE_LEN; i++)
    {
        CBST<size_t, CSubject> item = DataInfo::s_subject[i];
        if (item.Find(nID, sub))
        {
            return true;
        }
    }

    return false;
}

CQueue<CSubject> QuerySubByName(const char *szName)
{
    CQueue<CSubject> qu;

    for (size_t i = 0; i < TABLE_LEN; i++)
    {
        auto item = DataInfo::s_subject[i];
        CQueue<CSubject> tempQu = item.LMR_LOOP();
        while (!tempQu.IsEmpty())
        {
            CSubject tempStu = tempQu.Front();
            if (tempStu.GetSubName() == szName)
            {
                qu.Push(tempStu);
            }
            tempQu.Pop();
        }
    }

    return qu;
}

bool InsertScore(size_t nStuID, size_t nSubID, float fScore)
{
    //���ļ�
    fstream fs;
    fs.open("ScoreInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //��ȡ���ݴ���λ��
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //��������
    CScore sre(nStuID, nSubID, fScore, lnOff);

    //��Ӷ����ڴ�
    if (nSubID > DataInfo::s_aryScore.GetLen())
    {
        CBST<size_t, CScore> *pTree = new CBST<size_t, CScore>();
        pTree->Insert(nStuID, sre);
        DataInfo::s_aryScore.InsertTail(pTree);
    }
    else
    {
        DataInfo::s_aryScore[nSubID - 1]->Insert(nStuID, sre);
    }

    //��Ӷ����ļ�
    fs << sre;

    //�ر��ļ�
    fs.close();

    return true;
}

bool DeleteScore(size_t nStuID, size_t nSubID)
{
    //���Ҷ���
    CScore sre;
    if (!QueryScoreByStuAndSub(nStuID, nSubID, sre))
    {
        return false;
    }

    //���ļ�
    fstream fs;
    fs.open("ScoreInfo.data", ios::in | ios::out | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //ɾ������
    sre.SetIsDelete(true);
    DataInfo::s_aryScore[nSubID - 1]->Delete(nStuID);

    //��ȡɾ��λ��
    bool isDel = sre.GetIsDelete();
    fs.seekp(sre.GetLocationIsDel(), ios_base::beg);

    //д��
    fs.write((char *)&isDel, sizeof(isDel));

    //�ر�
    fs.close();

    return true;
}

bool UpdateScore(size_t nStuID, size_t nSubID, float fScore)
{
    //���ļ�
    fstream fs;
    fs.open("ScoreInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //ɾ��ԭ����
    if (!DeleteScore(nStuID, nSubID))
    {
        fs.close();
        return false;
    }

    //��ȡ���ݴ���λ��
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //�����¶���
    CScore sreNew(nSubID, nSubID, fScore, lnOff);

    //��Ӷ����ڴ�
    DataInfo::s_aryScore[nSubID - 1]->Insert(nStuID, sreNew);

    //��Ӷ����ļ�
    fs << sreNew;

    //�ر��ļ�
    fs.close();

    return true;
}

bool QueryScoreByStuAndSub(size_t nStuID, size_t nSubID, CScore &sre)
{
    //���Ҷ���
    auto tree = DataInfo::s_aryScore[nSubID - 1];
    if (tree == nullptr)
    {
        return false;
    }

    if (tree->Find(nStuID, sre))
    {
        return true;
    }

    return false;
}

CQueue<CScore> QueryScoreByStu(size_t nStuID)
{
    CQueue<CScore> quSre;
    size_t nLength = DataInfo::s_aryScore.GetLen();
    for (size_t i = 0; i < nLength; i++)
    {
        CScore sre;
        if (DataInfo::s_aryScore[i]->Find(nStuID, sre))
        {
            quSre.Push(sre);
        }
    }

    return quSre;
}

CBST<size_t, CScore> QueryScoreBySub(size_t nSubID)
{
    return *(DataInfo::s_aryScore[nSubID - 1]);
}

//CQueue<TABLE> GetTableInfo(CQueue<CScore> &qu)
//{
//
//
//    return nullptr;
//}
