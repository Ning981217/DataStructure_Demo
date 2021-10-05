#include "MenuUI.h"
/*
* UI��,��ʾ�˵�
*/

using namespace std;

//ѧ��
void StuManager();
bool AddStudent();
bool DelStudent();
bool UpdateStudent();
void QueryStudent();

//�γ�
void SubjectManager();
bool AddSubject();
bool DelSubject();
bool UpdateSubject();
void QuerySubject();

//�ɼ�
void ScoreManager();
bool AddScore();
bool DelScore();
bool UpdateScore();
void QueryScore();

void ShowMenu()
{
    system("cls");

    cout << "==================================================" << endl;
    cout << "1��ѧ������" << endl;
    cout << "2���γ̹���" << endl;
    cout << "3���ɼ�����" << endl;
    cout << "4���˳�ϵͳ" << endl;
    cout << "��ѡ�� : ";

    int nChoose = 0;
    cin >> nChoose;

    //����ʣ�໺����
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
            cout << "ѡ�����!!!!!" << endl;
            system("pause");
            break;
    }
}

//ѧ������
#pragma region ѧ������
void StuManager()
{
    system("cls");
    cout << "==================================================" << endl;
    cout << "1�����ѧ����Ϣ" << endl;
    cout << "2��ɾ��ѧ����Ϣ" << endl;
    cout << "3���޸�ѧ����Ϣ" << endl;
    cout << "4����ѯѧ����Ϣ" << endl;
    cout << "5��������һ��" << endl;
    cout << "��ѡ�� : ";

    int nChoose = 0;
    cin >> nChoose;

    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    switch (nChoose)
    {
        case 1:
            if (!AddStudent())
            {
                cout << "���ʧ��" << endl;
                system("pause");
                break;
            }
            cout << "��ӳɹ�" << endl;
            system("pause");
            break;
        case 2:
            if (!DelStudent())
            {
                cout << "ɾ��ʧ��" << endl;
                system("pause");
                break;
            }
            cout << "ɾ���ɹ�" << endl;
            system("pause");
            break;
        case 3:
            if (!UpdateStudent())
            {
                cout << "�޸�ʧ��" << endl;
                system("pause");
                break;
            }
            cout << "�޸ĳɹ�" << endl;
            system("pause");
            break;
        case 4:
            QueryStudent();
            break;
        case 5:
            ShowMenu();
            break;
        default:
            cout << "ѡ�����!!!!!" << endl;
            system("pause");
            StuManager();
            break;
    }
}

//���ѧ����Ϣ
bool AddStudent()
{
    cout << "������ѧ������" << endl;

    char szName[64] = { '\0' };
    cin.getline(szName, 64);

    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return InsertStu(szName);
}

//ɾ��ѧ����Ϣ
bool DelStudent()
{
    cout << "������Ҫɾ����ѧ��ID" << endl;

    size_t nID = 0;
    cin >> nID;

    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    //��֤ѧ��ID
    CStudent stu;
    if (!QueryStuByID(nID, stu))
    {
        cout << "û�д�ѧ��" << endl;
        return false;
    }

    return DeleteStu(nID);
}

//�޸�ѧ����Ϣ
bool UpdateStudent()
{
    cout << "������Ҫ�޸ĵ�ѧ��ID" << endl;
    size_t nID = 0;
    cin >> nID;
    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "�������޸ĺ�ѧ��������" << endl;
    char szName[64] = { '\0' };
    cin.getline(szName, 64);
    //����ʣ�໺����
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    //��֤ѧ��ID
    CStudent stu;
    if (!QueryStuByID(nID, stu))
    {
        cout << "û�д�ѧ��" << endl;
        return false;
    }

    return UpdateStu(nID, szName);
}

//��ѯѧ����Ϣ
void QueryStudent()
{
    cout << "********************" << endl;
    cout << "1������ѧ��ID��ѯ" << endl;
    cout << "2������ѧ��������ѯ" << endl;
    cout << "��ѡ��:";

    int nChoose = 0;
    cin >> nChoose;
    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    CStudent stu;
    CQueue<CStudent> quStu;

    switch (nChoose)
    {
        case 1:
        {
            cout << "������Ҫ��ѯ��ID" << endl;

            size_t nID = 0;
            cin >> nID;
            //����ʣ�໺����
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            if (QueryStuByID(nID, stu))
            {
                cout << "ID : " << stu.GetID() << "\t���� : " << stu.GetStuName().GetStr() << endl;
            }
            else
            {
                cout << "���޴���" << endl;
            }
            system("pause");
            break;
        }
        case 2:
        {
            cout << "������Ҫ��ѯ������" << endl;

            char szName[64] = { '\0' };
            cin.getline(szName, 64);
            //����ʣ�໺����
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            quStu = QueryStuByName(szName);
            if (quStu.IsEmpty())
            {
                cout << "û�и�ѧ��" << endl;
            }
            while (!quStu.IsEmpty())
            {
                CStudent tempStu = quStu.Front();
                cout << "ID : " << tempStu.GetID() << "\t���� : " << tempStu.GetStuName().GetStr() << endl;
                quStu.Pop();
            }

            system("pause");
            break;
        }
        default:
        {
            cout << "ѡ�����!!!!!" << endl;
            system("pause");
            QueryStudent();
            break;
        }
    }
}
#pragma endregion


//�γ̹���
#pragma region �γ̹���
void SubjectManager()
{
    system("cls");
    cout << "==================================================" << endl;
    cout << "1����ӿγ���Ϣ" << endl;
    cout << "2��ɾ���γ���Ϣ" << endl;
    cout << "3���޸Ŀγ���Ϣ" << endl;
    cout << "4����ѯ�γ���Ϣ" << endl;
    cout << "5��������һ��" << endl;
    cout << "��ѡ�� : ";

    int nChoose = 0;
    cin >> nChoose;

    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    switch (nChoose)
    {
        case 1:
            if (!AddSubject())
            {
                cout << "���ʧ��" << endl;
                system("pause");
                break;
            }
            cout << "��ӳɹ�" << endl;
            system("pause");
            break;
        case 2:
            if (!DelSubject())
            {
                cout << "ɾ��ʧ��" << endl;
                system("pause");
                break;
            }
            cout << "ɾ���ɹ�" << endl;
            system("pause");
            break;
        case 3:
            if (!UpdateSubject())
            {
                cout << "�޸�ʧ��" << endl;
                system("pause");
                break;
            }
            cout << "�޸ĳɹ�" << endl;
            system("pause");
            break;
        case 4:
            QuerySubject();
            break;
        case 5:
            ShowMenu();
            break;
        default:
            cout << "ѡ�����!!!!!" << endl;
            system("pause");
            SubjectManager();
            break;
    }
}

//��ӿγ�
bool AddSubject()
{
    cout << "������γ���" << endl;

    char szName[64] = { '\0' };
    cin.getline(szName, 64);

    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return InsertSub(szName);
}

//ɾ���γ�
bool DelSubject()
{
    cout << "������Ҫ�γ���ID" << endl;

    size_t nID = 0;
    cin >> nID;

    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return DeleteSub(nID);
}

//�޸Ŀγ�
bool UpdateSubject()
{
    cout << "������Ҫ�޸ĵĿγ�ID" << endl;
    size_t nID = 0;
    cin >> nID;
    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "�������޸ĺ�γ���" << endl;
    char szName[64] = { '\0' };
    cin.getline(szName, 64);
    //����ʣ�໺����
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return UpdateSub(nID, szName);
}

//��ѯ�γ�
void QuerySubject()
{
    cout << "********************" << endl;
    cout << "1�����ݿγ�ID��ѯ" << endl;
    cout << "2�����ݿγ�����ѯ" << endl;
    cout << "��ѡ��:";

    int nChoose = 0;
    cin >> nChoose;
    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    CSubject sub;
    CQueue<CSubject> quSub;

    switch (nChoose)
    {
        case 1:
        {
            cout << "������Ҫ��ѯ��ID" << endl;

            size_t nID = 0;
            cin >> nID;
            //����ʣ�໺����
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            if (QuerySubByID(nID, sub))
            {
                cout << "ID : " << sub.GetID() << "\t�γ��� : " << sub.GetSubName().GetStr() << endl;
            }
            else
            {
                cout << "û�иÿγ�" << endl;
            }
            system("pause");
            break;
        }
        case 2:
        {
            cout << "������Ҫ��ѯ�Ŀγ���" << endl;

            char szName[64] = { '\0' };
            cin.getline(szName, 64);
            //����ʣ�໺����
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            quSub = QuerySubByName(szName);
            if (quSub.IsEmpty())
            {
                cout << "û�иÿγ�" << endl;
            }
            while (!quSub.IsEmpty())
            {
                CSubject tempStu = quSub.Front();
                cout << "ID : " << tempStu.GetID() << "\t�γ��� : " << tempStu.GetSubName().GetStr() << endl;
                quSub.Pop();
            }

            system("pause");
            break;
        }
        default:
        {
            cout << "ѡ�����!!!!!" << endl;
            system("pause");
            QuerySubject();
            break;
        }
    }
}
#pragma endregion

//�ɼ�����
#pragma region �ɼ�����
void ScoreManager()
{
    system("cls");
    cout << "==================================================" << endl;
    cout << "1�����ѡ����Ϣ" << endl;
    cout << "2��ɾ��ѡ����Ϣ" << endl;
    cout << "3���޸�ѡ�γɼ�" << endl;
    cout << "4����ѯѡ����Ϣ" << endl;
    cout << "5��������һ��" << endl;
    cout << "��ѡ�� : ";

    int nChoose = 0;
    cin >> nChoose;

    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    switch (nChoose)
    {
        case 1:
            if (!AddScore())
            {
                cout << "���ʧ��" << endl;
                system("pause");
                break;
            }
            cout << "��ӳɹ�" << endl;
            system("pause");
            break;
        case 2:
            if (!DelScore())
            {
                cout << "ɾ��ʧ��" << endl;
                system("pause");
                break;
            }
            cout << "ɾ���ɹ�" << endl;
            system("pause");
            break;
        case 3:
            if (!UpdateScore())
            {
                cout << "�޸�ʧ��" << endl;
                system("pause");
                break;
            }
            cout << "�޸ĳɹ�" << endl;
            system("pause");
            break;
        case 4:
            QueryScore();
            break;
        case 5:
            ShowMenu();
            break;
        default:
            cout << "ѡ�����!!!!!" << endl;
            system("pause");
            ScoreManager();
            break;
    }
}

//���ѡ����Ϣ
bool AddScore()
{
    cout << "������Ҫ��ӵ�ѧ��ID" << endl;

    size_t nStuID = 0;
    cin >> nStuID;

    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "������Ҫ��ӵĿγ�ID" << endl;

    size_t nSubID = 0;
    cin >> nSubID;

    //����ʣ�໺����
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "������ɼ�" << endl;

    float fScore = 0.0f;
    cin >> fScore;

    //����ʣ�໺����
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    return InsertScore(nStuID, nSubID, fScore);
}

//ɾ��ѡ����Ϣ
bool DelScore()
{
    cout << "������Ҫɾ����ѧ��ID" << endl;
    size_t nStuID = 0;
    cin >> nStuID;
    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "������Ҫɾ���Ŀγ�ID" << endl;
    size_t nSubID = 0;
    cin >> nSubID;
    //����ʣ�໺����
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    //��ѯѧ��ID��Ч��
    CStudent stu;
    if (!QueryStuByID(nStuID, stu))
    {
        cout << "û�����ѧ��" << endl;
        return false;
    }
    //��ѯ�γ�ID��Ч��
    CSubject sub;
    if (!QuerySubByID(nSubID, sub))
    {
        cout << "û�����ſ�" << endl;
        return false;
    }

    return DeleteScore(nStuID, nSubID);
}

//����ѡ�γɼ�
bool UpdateScore()
{
    cout << "������Ҫ�޸ĵ�ѧ��ID" << endl;
    size_t nStuID = 0;
    cin >> nStuID;
    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "������Ҫ�޸ĵĿγ�ID" << endl;
    size_t nSubID = 0;
    cin >> nSubID;
    //����ʣ�໺����
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    cout << "�������޸ĺ�ĳɼ�" << endl;
    float fScore = 0.0f;
    cin >> fScore;
    //����ʣ�໺����
    cin.clear();
    nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    //��ѯѧ��ID��Ч��
    CStudent stu;
    if (!QueryStuByID(nStuID, stu))
    {
        cout << "û�����ѧ��" << endl;
        return false;
    }
    //��ѯ�γ�ID��Ч��
    CSubject sub;
    if (!QuerySubByID(nSubID, sub))
    {
        cout << "û�����ſ�" << endl;
        return false;
    }

    return UpdateScore(nStuID, nSubID, fScore);
}

//��ѯѡ����Ϣ
void QueryScore()
{
    cout << "********************" << endl;
    cout << "1������ѧ��ID��ѯ" << endl;
    cout << "2�����ݿγ�ID��ѯ" << endl;
    cout << "��ѡ��:";

    int nChoose = 0;
    cin >> nChoose;
    //����ʣ�໺����
    cin.clear();
    int nCntAvail = std::cin.rdbuf()->in_avail();
    std::cin.ignore(nCntAvail);

    switch (nChoose)
    {
        case 1:
        {
            cout << "������Ҫ��ѯ��ѧ��ID" << endl;

            size_t nStuID = 0;
            cin >> nStuID;
            //����ʣ�໺����
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            //��ѯѧ��ID��Ч��
            CStudent stu;
            if (!QueryStuByID(nStuID, stu))
            {
                cout << "û�����ѧ��" << endl;
                system("pause");
                return;
            }

            auto qu = QueryScoreByStu(nStuID);
            if (qu.IsEmpty())
            {
                cout << "û�м�¼" << endl;
                system("pause");
                return;
            }

            while (!qu.IsEmpty())
            {
                CScore sre = qu.Front();
                CSubject sub;

                if (QuerySubByID(sre.GetSubjectID(), sub))
                {
                    cout << "���� : " << stu.GetStuName().GetStr() << ",ѡ���� : " << sub.GetSubName().GetStr() << ",�ɼ� : " << sre.GetScore() << endl;
                }

                qu.Pop();
            }

            system("pause");
            break;
        }
        case 2:
        {
            cout << "������Ҫ��ѯ�Ŀγ�ID" << endl;

            size_t nSubID = 0;
            cin >> nSubID;
            //����ʣ�໺����
            cin.clear();
            nCntAvail = std::cin.rdbuf()->in_avail();
            std::cin.ignore(nCntAvail);

            //��ѯ�γ�ID��Ч��
            CSubject sub;
            if (!QuerySubByID(nSubID, sub))
            {
                cout << "û�����ſ�" << endl;
                system("pause");
                return;
            }

            CBST<size_t, CScore> tree = QueryScoreBySub(nSubID);
            CQueue<CScore> qu = tree.LMR_LOOP();

            if (qu.IsEmpty())
            {
                cout << "û�м�¼" << endl;
                system("pause");
                return;
            }


            while (!qu.IsEmpty())
            {
                CScore sre = qu.Front();
                CStudent stu;

                if (QueryStuByID(sre.GetStuID(), stu))
                {
                    cout << "���� : " << stu.GetStuName().GetStr() << ",ѡ���� : " << sub.GetSubName().GetStr() << ",�ɼ� : " << sre.GetScore() << endl;
                }

                qu.Pop();
            }

            system("pause");
            break;
        }
        default:
        {
            cout << "ѡ�����!!!!!" << endl;
            system("pause");
            QuerySubject();
            break;
        }
    }
}
#pragma endregion
