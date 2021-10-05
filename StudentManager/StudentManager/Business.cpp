#include "Business.h"

CMyHash<CMyString, size_t, CStudent> DataInfo::s_student;              //存储学生
CMyHash<CMyString, size_t, CSubject> DataInfo::s_subject;              //存储课程
CArray<CBST<size_t, CScore> *> DataInfo::s_aryScore;                   //存储成绩

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
        CMyString str(CMyString::ValueOf((int)i).Append("张三"));
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
        //处理尾部\r
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
            //保证课程不重复
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
    //打开文件
    fstream fs;
    fs.open("StudentInfo.data", ios::in | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //读
    while (fs.peek() != EOF)
    {
        CStudent stu;
        fs >> stu;
        if (!stu.GetIsDelete())
        {
            //添加到内存中
            DataInfo::s_student.Insert(stu.GetStuName(), stu.GetID(), stu);
        }
    }
    //关闭
    fs.close();

    return true;
}

bool ReadSub()
{
    //打开文件
    fstream fs;
    fs.open("SubjectInfo.data", ios::in | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //读
    while (fs.peek() != EOF)
    {
        CSubject sub;
        fs >> sub;
        if (!sub.GetIsDelete())
        {
            //添加到内存中
            DataInfo::s_subject.Insert(sub.GetSubName(), sub.GetID(), sub);
        }
    }
    //关闭
    fs.close();

    return true;
}

bool ReadScore()
{
    //打开文件
    fstream fs;
    fs.open("ScoreInfo.data", ios::in | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //动态数组初始化
    for (size_t i = 0; i < CSubject::GetPrimaryKey(); i++)
    {
        CBST<size_t, CScore> *pTree = new CBST<size_t, CScore>();
        DataInfo::s_aryScore.InsertTail(pTree);
    }
    //读
    while (fs.peek() != EOF)
    {
        CScore sre;
        fs >> sre;
        int a = sre.GetSubjectID();
        if (!sre.GetIsDelete())
        {
            //添加对象到内存
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
    //关闭
    fs.close();

    return true;
}

bool InsertStu(char *szName)
{
    //打开文件
    fstream fs;
    fs.open("StudentInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //获取数据存入位置
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //创建对象
    CStudent stu(szName, lnOff);

    //添加对象到内存
    DataInfo::s_student.Insert(stu.GetStuName(), stu.GetID(), stu);

    //添加对象到文件
    fs << stu;

    //关闭文件
    fs.close();

    return true;
}

bool DeleteStu(size_t nID)
{
    //查找对象
    CStudent stu;
    if (!QueryStuByID(nID, stu))
    {
        return false;
    }

    //打开文件
    fstream fs;
    fs.open("StudentInfo.data", ios::in | ios::out | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //删除对象
    stu.SetIsDelete(true);
    DataInfo::s_student.Delete(stu.GetStuName(), stu.GetID());

    //获取删除位置
    bool isDel = stu.GetIsDelete();
    fs.seekp(stu.GetLocationIsDel(), ios_base::beg);

    //写入
    fs.write((char *)&isDel, sizeof(isDel));

    //关闭
    fs.close();

    //删除对应成绩表
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
    //打开文件
    fstream fs;
    fs.open("StudentInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //删除原对象
    if (!DeleteStu(nID))
    {
        fs.close();
        return false;
    }

    //获取数据存入位置
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //构造新对象
    CStudent stuNew(szName, lnOff, nID);

    //添加对象到内存
    DataInfo::s_student.Insert(stuNew.GetStuName(), nID, stuNew);

    //添加对象到文件
    fs << stuNew;

    //关闭文件
    fs.close();

    return true;
}

bool QueryStuByID(size_t nID, CStudent &stu)
{
    //查找对象
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
    //打开文件
    fstream fs;
    fs.open("SubjectInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //获取数据存入位置
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //创建对象
    CSubject sub(szName, lnOff);

    //添加对象到内存
    DataInfo::s_subject.Insert(sub.GetSubName(), sub.GetID(), sub);

    //添加对象到文件
    fs << sub;

    //关闭文件
    fs.close();

    return true;
}

bool DeleteSub(size_t nID)
{
    //查找对象
    CSubject sub;
    if (!QuerySubByID(nID, sub))
    {
        return false;
    }

    //打开文件
    fstream fs;
    fs.open("SubjectInfo.data", ios::in | ios::out | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //删除对象
    sub.SetIsDelete(true);
    DataInfo::s_subject.Delete(sub.GetSubName(), sub.GetID());

    //获取删除位置
    bool isDel = sub.GetIsDelete();
    fs.seekp(sub.GetLocationIsDel(), ios_base::beg);

    //写入
    fs.write((char *)&isDel, sizeof(isDel));

    //关闭
    fs.close();

    //删除对应成绩表
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
    //打开文件
    fstream fs;
    fs.open("SubjectInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //删除原对象
    if (!DeleteSub(nID))
    {
        fs.close();
        return false;
    }

    //获取数据存入位置
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //构造新对象
    CSubject subNew(szName, lnOff, nID);

    //添加对象到内存
    DataInfo::s_subject.Insert(subNew.GetSubName(), subNew.GetID(), subNew);

    //添加对象到文件
    fs << subNew;

    //关闭文件
    fs.close();

    return true;
}

bool QuerySubByID(size_t nID, CSubject &sub)
{
    //查找对象
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
    //打开文件
    fstream fs;
    fs.open("ScoreInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }
    //获取数据存入位置
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //创建对象
    CScore sre(nStuID, nSubID, fScore, lnOff);

    //添加对象到内存
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

    //添加对象到文件
    fs << sre;

    //关闭文件
    fs.close();

    return true;
}

bool DeleteScore(size_t nStuID, size_t nSubID)
{
    //查找对象
    CScore sre;
    if (!QueryScoreByStuAndSub(nStuID, nSubID, sre))
    {
        return false;
    }

    //打开文件
    fstream fs;
    fs.open("ScoreInfo.data", ios::in | ios::out | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //删除对象
    sre.SetIsDelete(true);
    DataInfo::s_aryScore[nSubID - 1]->Delete(nStuID);

    //获取删除位置
    bool isDel = sre.GetIsDelete();
    fs.seekp(sre.GetLocationIsDel(), ios_base::beg);

    //写入
    fs.write((char *)&isDel, sizeof(isDel));

    //关闭
    fs.close();

    return true;
}

bool UpdateScore(size_t nStuID, size_t nSubID, float fScore)
{
    //打开文件
    fstream fs;
    fs.open("ScoreInfo.data", ios::app | ios::binary);
    if (!fs.is_open())
    {
        return false;
    }

    //删除原对象
    if (!DeleteScore(nStuID, nSubID))
    {
        fs.close();
        return false;
    }

    //获取数据存入位置
    fs.seekp(0, ios_base::end);
    long lnOff = fs.tellp();

    //构造新对象
    CScore sreNew(nSubID, nSubID, fScore, lnOff);

    //添加对象到内存
    DataInfo::s_aryScore[nSubID - 1]->Insert(nStuID, sreNew);

    //添加对象到文件
    fs << sreNew;

    //关闭文件
    fs.close();

    return true;
}

bool QueryScoreByStuAndSub(size_t nStuID, size_t nSubID, CScore &sre)
{
    //查找对象
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
