#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class CSubject
{
public:
    CSubject() {}
    CSubject(const string& subjectName,
        const double& mark,
        const string& grade)
            :SubjectName(subjectName)
            , Mark(mark)
            , Grade(grade)
    {
        TotalMark = Mark * markTable[grade];
    }
    
    ~CSubject() {}

public:
    double GetTotalMark() const noexcept
    {
        return TotalMark;
    }
private:
    unordered_map<string, double> markTable = {
        {"A+", 4.5},
        {"A0", 4.0},
        {"B+", 3.5},
        {"B0", 3.0},
        {"C+", 2.5},
        {"C0", 2.0},
        {"D+", 1.5},
        {"D0", 1.0},
        {"F", 0},
    };

    string SubjectName;
    double Mark = 0.0;
    string Grade;
    double TotalMark = 0.0;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    const int n = 20;
    vector<CSubject> subjects;

    double sumMark = 0.0;
    for (int i = 0; i < n; ++i)
    {
        string subjectName;
        double mark;
        string grade;
        cin >> subjectName >> mark >> grade;

        if (grade == "P")
        {
            continue;
        }

        sumMark += mark;
        
        subjects.emplace_back(subjectName, mark, grade);
    }

    double sumTotalMark = 0.0;

    for (const CSubject& subject : subjects)
    {
        sumTotalMark += subject.GetTotalMark();
    }

    cout << sumTotalMark / sumMark << "\n";

    return 0;
}
