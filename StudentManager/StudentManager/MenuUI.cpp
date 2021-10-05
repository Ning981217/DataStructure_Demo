#include "MenuUI.h"
/*
* UI层,显示菜单
*/

using namespace std;

//学生
void StuManager();
bool AddStudent();
bool DelStudent();
bool UpdateStudent();
void QueryStudent();

//课程
void SubjectManager();
bool AddSubject();
bool DelSubject();
bool UpdateSubject();
void QuerySubject();

//成绩
void ScoreManager();
bool AddScore();
bool DelScore();
bool UpdateScore();
void QueryScore();

void ShowMenu()
{
    system("cls");

    cout << "==================================================" << endl;
    cout << "1、学生管理" << endl;
    cout << "2、课程管理" << endl;
    cout << "3、成绩管理" << endl;
    cout << "4、退出系统" << endl;
    cout << "请选择 : ";

    int nChoose = 0;
    cin >> nChoose;

    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    switch (nChoose)
    {
        case 1:
            StuManager();
            break;
        case 2:
            SubjectManager();
            break;
        case 3:
            ScoreManager();
            break;
        case 4:
            exit(0);
            break;
        default:
            cout << "选择错误!!!!!" << endl;
            system("pause");
            break;
    }
}

//学生管理
#pragma region 学生管理
void StuManager()
{
    system("cls");
    cout << "==================================================" << endl;
    cout << "1、添加学生信息" << endl;
    cout << "2、删除学生信息" << endl;
    cout << "3、修改学生信息" << endl;
    cout << "4、查询学生信息" << endl;
    cout << "5、返回上一层" << endl;
    cout << "请选择 : ";

    int nChoose = 0;
    cin >> nChoose;

    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    switch (nChoose)
    {
        case 1:
            if (!AddStudent())
            {
                cout << "添加失败" << endl;
                system("pause");
                break;
            }
            cout << "添加成功" << endl;
            system("pause");
            break;
        case 2:
            if (!DelStudent())
            {
                cout << "删除失败" << endl;
                system("pause");
                break;
            }
            cout << "删除成功" << endl;
            system("pause");
            break;
        case 3:
            if (!UpdateStudent())
            {
                cout << "修改失败" << endl;
                system("pause");
                break;
            }
            cout << "修改成功" << endl;
            system("pause");
            break;
        case 4:
            QueryStudent();
            break;
        case 5:
            ShowMenu();
            break;
        default:
            cout << "选择错误!!!!!" << endl;
            system("pause");
            StuManager();
            break;
    }
}

//添加学生信息
bool AddStudent()
{
    cout << "请输入学生姓名" << endl;

    char szName[64] = { '\0' };
    cin.getline(szName, 64);

    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return InsertStu(szName);
}

//删除学生信息
bool DelStudent()
{
    cout << "请输入要删除的学生ID" << endl;

    size_t nID = 0;
    cin >> nID;

    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    //验证学生ID
    CStudent stu;
    if (!QueryStuByID(nID, stu))
    {
        cout << "没有此学生" << endl;
        return false;
    }

    return DeleteStu(nID);
}

//修改学生信息
bool UpdateStudent()
{
    cout << "请输入要修改的学生ID" << endl;
    size_t nID = 0;
    cin >> nID;
    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "请输入修改后学生的姓名" << endl;
    char szName[64] = { '\0' };
    cin.getline(szName, 64);
    //忽略剩余缓冲区
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    //验证学生ID
    CStudent stu;
    if (!QueryStuByID(nID, stu))
    {
        cout << "没有此学生" << endl;
        return false;
    }

    return UpdateStu(nID, szName);
}

//查询学生信息
void QueryStudent()
{
    cout << "********************" << endl;
    cout << "1、根据学生ID查询" << endl;
    cout << "2、根据学生姓名查询" << endl;
    cout << "请选择:";

    int nChoose = 0;
    cin >> nChoose;
    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    CStudent stu;
    CQueue<CStudent> quStu;

    switch (nChoose)
    {
        case 1:
        {
            cout << "请输入要查询的ID" << endl;

            size_t nID = 0;
            cin >> nID;
            //忽略剩余缓冲区
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            if (QueryStuByID(nID, stu))
            {
                cout << "ID : " << stu.GetID() << "\t姓名 : " << stu.GetStuName().GetStr() << endl;
            }
            else
            {
                cout << "查无此人" << endl;
            }
            system("pause");
            break;
        }
        case 2:
        {
            cout << "请输入要查询的姓名" << endl;

            char szName[64] = { '\0' };
            cin.getline(szName, 64);
            //忽略剩余缓冲区
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            quStu = QueryStuByName(szName);
            if (quStu.IsEmpty())
            {
                cout << "没有该学生" << endl;
            }
            while (!quStu.IsEmpty())
            {
                CStudent tempStu = quStu.Front();
                cout << "ID : " << tempStu.GetID() << "\t姓名 : " << tempStu.GetStuName().GetStr() << endl;
                quStu.Pop();
            }

            system("pause");
            break;
        }
        default:
        {
            cout << "选择错误!!!!!" << endl;
            system("pause");
            QueryStudent();
            break;
        }
    }
}
#pragma endregion


//课程管理
#pragma region 课程管理
void SubjectManager()
{
    system("cls");
    cout << "==================================================" << endl;
    cout << "1、添加课程信息" << endl;
    cout << "2、删除课程信息" << endl;
    cout << "3、修改课程信息" << endl;
    cout << "4、查询课程信息" << endl;
    cout << "5、返回上一层" << endl;
    cout << "请选择 : ";

    int nChoose = 0;
    cin >> nChoose;

    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    switch (nChoose)
    {
        case 1:
            if (!AddSubject())
            {
                cout << "添加失败" << endl;
                system("pause");
                break;
            }
            cout << "添加成功" << endl;
            system("pause");
            break;
        case 2:
            if (!DelSubject())
            {
                cout << "删除失败" << endl;
                system("pause");
                break;
            }
            cout << "删除成功" << endl;
            system("pause");
            break;
        case 3:
            if (!UpdateSubject())
            {
                cout << "修改失败" << endl;
                system("pause");
                break;
            }
            cout << "修改成功" << endl;
            system("pause");
            break;
        case 4:
            QuerySubject();
            break;
        case 5:
            ShowMenu();
            break;
        default:
            cout << "选择错误!!!!!" << endl;
            system("pause");
            SubjectManager();
            break;
    }
}

//添加课程
bool AddSubject()
{
    cout << "请输入课程名" << endl;

    char szName[64] = { '\0' };
    cin.getline(szName, 64);

    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return InsertSub(szName);
}

//删除课程
bool DelSubject()
{
    cout << "请输入要课程名ID" << endl;

    size_t nID = 0;
    cin >> nID;

    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return DeleteSub(nID);
}

//修改课程
bool UpdateSubject()
{
    cout << "请输入要修改的课程ID" << endl;
    size_t nID = 0;
    cin >> nID;
    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "请输入修改后课程名" << endl;
    char szName[64] = { '\0' };
    cin.getline(szName, 64);
    //忽略剩余缓冲区
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return UpdateSub(nID, szName);
}

//查询课程
void QuerySubject()
{
    cout << "********************" << endl;
    cout << "1、根据课程ID查询" << endl;
    cout << "2、根据课程名查询" << endl;
    cout << "请选择:";

    int nChoose = 0;
    cin >> nChoose;
    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    CSubject sub;
    CQueue<CSubject> quSub;

    switch (nChoose)
    {
        case 1:
        {
            cout << "请输入要查询的ID" << endl;

            size_t nID = 0;
            cin >> nID;
            //忽略剩余缓冲区
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            if (QuerySubByID(nID, sub))
            {
                cout << "ID : " << sub.GetID() << "\t课程名 : " << sub.GetSubName().GetStr() << endl;
            }
            else
            {
                cout << "没有该课程" << endl;
            }
            system("pause");
            break;
        }
        case 2:
        {
            cout << "请输入要查询的课程名" << endl;

            char szName[64] = { '\0' };
            cin.getline(szName, 64);
            //忽略剩余缓冲区
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            quSub = QuerySubByName(szName);
            if (quSub.IsEmpty())
            {
                cout << "没有该课程" << endl;
            }
            while (!quSub.IsEmpty())
            {
                CSubject tempStu = quSub.Front();
                cout << "ID : " << tempStu.GetID() << "\t课程名 : " << tempStu.GetSubName().GetStr() << endl;
                quSub.Pop();
            }

            system("pause");
            break;
        }
        default:
        {
            cout << "选择错误!!!!!" << endl;
            system("pause");
            QuerySubject();
            break;
        }
    }
}
#pragma endregion

//成绩管理
#pragma region 成绩管理
void ScoreManager()
{
    system("cls");
    cout << "==================================================" << endl;
    cout << "1、添加选课信息" << endl;
    cout << "2、删除选课信息" << endl;
    cout << "3、修改选课成绩" << endl;
    cout << "4、查询选课信息" << endl;
    cout << "5、返回上一层" << endl;
    cout << "请选择 : ";

    int nChoose = 0;
    cin >> nChoose;

    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    switch (nChoose)
    {
        case 1:
            if (!AddScore())
            {
                cout << "添加失败" << endl;
                system("pause");
                break;
            }
            cout << "添加成功" << endl;
            system("pause");
            break;
        case 2:
            if (!DelScore())
            {
                cout << "删除失败" << endl;
                system("pause");
                break;
            }
            cout << "删除成功" << endl;
            system("pause");
            break;
        case 3:
            if (!UpdateScore())
            {
                cout << "修改失败" << endl;
                system("pause");
                break;
            }
            cout << "修改成功" << endl;
            system("pause");
            break;
        case 4:
            QueryScore();
            break;
        case 5:
            ShowMenu();
            break;
        default:
            cout << "选择错误!!!!!" << endl;
            system("pause");
            ScoreManager();
            break;
    }
}

//添加选课信息
bool AddScore()
{
    cout << "请输入要添加的学生ID" << endl;

    size_t nStuID = 0;
    cin >> nStuID;

    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "请输入要添加的课程ID" << endl;

    size_t nSubID = 0;
    cin >> nSubID;

    //忽略剩余缓冲区
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "请输入成绩" << endl;

    float fScore = 0.0f;
    cin >> fScore;

    //忽略剩余缓冲区
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return InsertScore(nStuID, nSubID, fScore);
}

//删除选课信息
bool DelScore()
{
    cout << "请输入要删除的学生ID" << endl;
    size_t nStuID = 0;
    cin >> nStuID;
    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "请输入要删除的课程ID" << endl;
    size_t nSubID = 0;
    cin >> nSubID;
    //忽略剩余缓冲区
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    //查询学生ID有效性
    CStudent stu;
    if (!QueryStuByID(nStuID, stu))
    {
        cout << "没有这个学生" << endl;
        return false;
    }
    //查询课程ID有效性
    CSubject sub;
    if (!QuerySubByID(nSubID, sub))
    {
        cout << "没有这门课" << endl;
        return false;
    }

    return DeleteScore(nStuID, nSubID);
}

//更新选课成绩
bool UpdateScore()
{
    cout << "请输入要修改的学生ID" << endl;
    size_t nStuID = 0;
    cin >> nStuID;
    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "请输入要修改的课程ID" << endl;
    size_t nSubID = 0;
    cin >> nSubID;
    //忽略剩余缓冲区
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "请输入修改后的成绩" << endl;
    float fScore = 0.0f;
    cin >> fScore;
    //忽略剩余缓冲区
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    //查询学生ID有效性
    CStudent stu;
    if (!QueryStuByID(nStuID, stu))
    {
        cout << "没有这个学生" << endl;
        return false;
    }
    //查询课程ID有效性
    CSubject sub;
    if (!QuerySubByID(nSubID, sub))
    {
        cout << "没有这门课" << endl;
        return false;
    }

    return UpdateScore(nStuID, nSubID, fScore);
}

//查询选课信息
void QueryScore()
{
    cout << "********************" << endl;
    cout << "1、根据学生ID查询" << endl;
    cout << "2、根据课程ID查询" << endl;
    cout << "请选择:";

    int nChoose = 0;
    cin >> nChoose;
    //忽略剩余缓冲区
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    switch (nChoose)
    {
        case 1:
        {
            cout << "请输入要查询的学生ID" << endl;

            size_t nStuID = 0;
            cin >> nStuID;
            //忽略剩余缓冲区
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            //查询学生ID有效性
            CStudent stu;
            if (!QueryStuByID(nStuID, stu))
            {
                cout << "没有这个学生" << endl;
                system("pause");
                return;
            }

            auto qu = QueryScoreByStu(nStuID);
            if (qu.IsEmpty())
            {
                cout << "没有记录" << endl;
                system("pause");
                return;
            }

            while (!qu.IsEmpty())
            {
                CScore sre = qu.Front();
                CSubject sub;

                if (QuerySubByID(sre.GetSubjectID(), sub))
                {
                    cout << "姓名 : " << stu.GetStuName().GetStr() << ",选课名 : " << sub.GetSubName().GetStr() << ",成绩 : " << sre.GetScore() << endl;
                }

                qu.Pop();
            }

            system("pause");
            break;
        }
        case 2:
        {
            cout << "请输入要查询的课程ID" << endl;

            size_t nSubID = 0;
            cin >> nSubID;
            //忽略剩余缓冲区
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            //查询课程ID有效性
            CSubject sub;
            if (!QuerySubByID(nSubID, sub))
            {
                cout << "没有这门课" << endl;
                system("pause");
                return;
            }

            CBST<size_t, CScore> tree = QueryScoreBySub(nSubID);
            CQueue<CScore> qu = tree.LMR_LOOP();

            if (qu.IsEmpty())
            {
                cout << "没有记录" << endl;
                system("pause");
                return;
            }


            while (!qu.IsEmpty())
            {
                CScore sre = qu.Front();
                CStudent stu;

                if (QueryStuByID(sre.GetStuID(), stu))
                {
                    cout << "姓名 : " << stu.GetStuName().GetStr() << ",选课名 : " << sub.GetSubName().GetStr() << ",成绩 : " << sre.GetScore() << endl;
                }

                qu.Pop();
            }

            system("pause");
            break;
        }
        default:
        {
            cout << "选择错误!!!!!" << endl;
            system("pause");
            QuerySubject();
            break;
        }
    }
}
#pragma endregion
