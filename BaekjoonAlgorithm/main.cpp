#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <tuple>
using namespace std;

class CUnionFound
{
public:
    CUnionFound() {}
    ~CUnionFound() {}

public:
    void Initialize(const int n)
    {
        Parent = move(vector<int>(n + 1, 0));
        for (int i = 1; i <= n; ++i)
        {
            Parent[i] = i;
        }
    }

    int Find(const int x)
    {
        if (x != Parent[x])
        {
            Parent[x] = Find(Parent[x]);
        }

        return Parent[x];
    }

    void Union(int x, int y)
    {
        x = Find(x);
        y = Find(y);
        if (x != y)
        {
            Parent[x] = y;
        }
    }
private:
    vector<int> Parent;
};

double CalculateDistance(const pair<double, double>& starPosA, const pair<double, double>& starPosB)
{
    const double x1 = starPosA.first;
    const double y1 = starPosA.second;
    const double x2 = starPosB.first;
    const double y2 = starPosB.second;

    const double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    return distance;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<pair<double, double>> stars(n + 1);
    vector<tuple<double, int, int>> edges;
    vector<bool> visited(n + 1, false);

    for (int i = 1; i <= n; ++i)
    {
        cin >> stars[i].first >> stars[i].second;
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (i != j)
            {
                edges.push_back(make_tuple(CalculateDistance(stars[i], stars[j]), i, j));
            }
        }
    }

    double weight = 0.f;

    CUnionFound unionFind;
    unionFind.Initialize(n);

    sort(edges.begin(), edges.end());

    for (const auto& edge : edges)
    {
        const int x = get<1>(edge);
        const int y = get<2>(edge);

        if (unionFind.Find(x) == unionFind.Find(y))
        {
            continue;
        }

        weight += get<0>(edge);
        unionFind.Union(x, y);
    }

    cout << fixed << setprecision(2) << weight << "\n";

    return 0;
}
