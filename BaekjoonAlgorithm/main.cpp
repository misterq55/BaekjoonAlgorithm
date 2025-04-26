#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <memory>
using namespace std;

struct TileInfo
{
    vector<pair<int, int>> TilePositions;
    int Index = 0;
    int LowestHeight = 0;
};

class CTileInfoGenerator
{
public:
    TileInfo GenerateTileInfo(const int type, const int col, const int y, const int x, const bool breverse)
    {
        TileInfo tileInfo;
        pair<int, int> tileBasePos = {breverse ? x : y, breverse ? col - 1 - y : x};
        const int tileTypeIndex = breverse ? 1 : 0;
        const pair<int, int> tileType = TileTypes[tileTypeIndex][type - 1];
        tileInfo.TilePositions.emplace_back(tileBasePos);
        tileInfo.LowestHeight = tileBasePos.first;

        if (type > 1)
        {
            tileInfo.TilePositions.emplace_back(tileBasePos.first + tileType.first,
                                                tileBasePos.second + tileType.second);

            tileInfo.LowestHeight = max(tileInfo.LowestHeight, tileBasePos.first + tileType.first);
        }
        tileInfo.Index = Index++;
        return move(tileInfo);
    }

private:
    int Index = 1;
    vector<vector<pair<int, int>>> TileTypes = {{{0, 0}, {0, 1}, {1, 0}}, {{0, 0}, {1, 0}, {0, -1}}};
};

class CTile
{
public:
    CTile(){}

    CTile(const TileInfo& tileInfo)
    {
        Info = tileInfo;
    }

    ~CTile(){}

public:
    void Move(const vector<int>& highestHeight)
    {
        int maxHeight = static_cast<int>(1e9);
        for (const auto& tilePos : Info.TilePositions)
        {
            const int x = tilePos.second;
            maxHeight = min(maxHeight, highestHeight[x]);
        }

        Info.LowestHeight = 0;
        int originalBasePos = Info.TilePositions[0].first;
        for (auto& tilePosition : Info.TilePositions)
        {
            originalBasePos = min(originalBasePos, tilePosition.first);
        }
        
        for (auto& tilePosition : Info.TilePositions)
        {
            tilePosition.first = maxHeight - (tilePosition.first - originalBasePos);
            Info.LowestHeight = max(Info.LowestHeight, tilePosition.first);
        }
    }

    bool DeletePos(const int y, const int x)
    {
        Info.TilePositions.erase(remove(Info.TilePositions.begin(), Info.TilePositions.end(), make_pair(y, x)),
                                 Info.TilePositions.end());

        Info.LowestHeight = 0;
        const bool bisPositionsEmpty = Info.TilePositions.empty();
        if (!bisPositionsEmpty)
        {
            for (const auto& tilePosition : Info.TilePositions)
            {
                Info.LowestHeight = max(Info.LowestHeight, tilePosition.first);
            }
        }
        
        return bisPositionsEmpty;
    }

    vector<pair<int, int>> GetTilePositions()
    {
        return Info.TilePositions;
    }

    int GetIndex()
    {
        return Info.Index;
    }

    int GetLowestHeight()
    {
        return Info.LowestHeight;
    }

private:
    TileInfo Info;
};

class CBoard
{
public:
    CBoard()
    {
    }

    CBoard(const int row, const int col)
        : Row(row), Col(col)
    {
        Board = move(vector<vector<int>>(Row, vector<int>(Col, 0)));
        HighestHeight = move(vector<int>(Col, Row - 1));
    }

    ~CBoard()
    {
    }

public:
    void AddTile(shared_ptr<CTile> tile)
    {
        Tiles.emplace(tile->GetIndex(), tile);
        addTileInternal(tile);

        vector<int> deletedLines;

        do
        {
            deletedLines = lineScoreCheck();
            deleteLines(deletedLines);
            renewalBlocks(deletedLines);
        }
        while (!deletedLines.empty());

        deletedLines = areaCheck();
        deleteLines(deletedLines);
        renewalBlocks(deletedLines);
    }

    int CountBlocks()
    {
        int count = 0;

        for (int i = 0; i < Row; ++i)
        {
            vector<int>& line = Board[i];
            for (int j = 0; j < Col; j++)
            {
                if (line[j] >= 1)
                {
                    ++count;
                }
            }
        }

        return count;
    }

    int GetScore()
    {
        return Score;
    }

private:
    void addTileInternal(shared_ptr<CTile> tile)
    {
        tile->Move(HighestHeight);
        const vector<pair<int, int>> tilePositions = tile->GetTilePositions();
        const int index = tile->GetIndex();

        for (const pair<int, int>& tilePosition : tile->GetTilePositions())
        {
            const int y = tilePosition.first;
            const int x = tilePosition.second;
            Board[y][x] = index;
            HighestHeight[x] = y - 1;
        }
    }

    vector<int> lineScoreCheck()
    {
        vector<int> deletedLines;

        for (int i = 0; i < Row; ++i)
        {
            int lineFillCounter = 0;
            vector<int>& line = Board[i];
            for (int j = 0; j < Col; j++)
            {
                if (line[j] >= 1)
                {
                    lineFillCounter++;
                }
            }

            if (lineFillCounter == Col)
            {
                Score++;
                deletedLines.push_back(i);
            }
        }

        return move(deletedLines);
    }

    void deleteLines(const vector<int>& deletedLines)
    {
        if (deletedLines.empty())
        {
            return;
        }

        const int size = static_cast<int>(deletedLines.size());
        for (int i = 0; i < size; ++i)
        {
            vector<int>& line = Board[deletedLines[i]];
            for (int j = 0; j < Col; ++j)
            {
                if (line[j] >= 1)
                {
                    shared_ptr<CTile> tile = Tiles[line[j]];
                    if (tile->DeletePos(deletedLines[i], j))
                    {
                        Tiles.erase(Tiles.find(line[j]));
                    }
                }
            }
            line.clear();
            line.resize(Col);
        }
    }

    vector<int> areaCheck()
    {
        vector<int> deletedLines;
        int counter = 0;
        for (int i = 0; i <= 1; ++i)
        {
            vector<int>& line = Board[i];
            for (int j = 0; j < Col; ++j)
            {
                if (line[j] >= 1)
                {
                    counter++;
                    break;
                }
            }
        }

        for (int i = 0; i < counter; ++i)
        {
            deletedLines.push_back(Row - 1 - i);
        }

        return move(deletedLines);
    }

    void renewalBlocks(vector<int>& deletedLines)
    {
        if (deletedLines.empty())
        {
            return;
        }

        HighestHeight = {Row - 1, Row - 1, Row - 1, Row - 1,};

        priority_queue<pair<int, shared_ptr<CTile>>> pq;

        for (pair<const int, shared_ptr<CTile>>& tilePair : Tiles)
        {
            shared_ptr<CTile> tile = tilePair.second;
            pq.push({tile->GetLowestHeight(), tile});
        }

        while (!pq.empty())
        {
            auto& curr = pq.top();
            shared_ptr<CTile> tile = curr.second;
            pq.pop();

            for (pair<int, int>& tilePos : tile->GetTilePositions())
            {
                const int y = tilePos.first;
                const int x = tilePos.second;
                Board[y][x] = 0;
            }

            tile->Move(HighestHeight);

            for (pair<int, int>& tilePos : tile->GetTilePositions())
            {
                const int y = tilePos.first;
                const int x = tilePos.second;
                Board[y][x] = tile->GetIndex();
                HighestHeight[x] = y - 1;
            }
        }
    }

private:
    vector<vector<int>> Board;
    vector<int> HighestHeight;
    int Score = 0;
    int Row = 0, Col = 0;
    unordered_map<int, shared_ptr<CTile>> Tiles;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    CBoard greenBoard(6, 4), blueBoard(6, 4);
    int n;
    cin >> n;

    CTileInfoGenerator tileInfoGenerator;

    for (int i = 0; i < n; ++i)
    {
        int t, y, x;
        cin >> t >> y >> x;

        shared_ptr<CTile> tileForGreen = make_shared<CTile>((tileInfoGenerator.GenerateTileInfo(t, 4, y, x, false)));
        greenBoard.AddTile(tileForGreen);

        shared_ptr<CTile> tileForBlue = make_shared<CTile>((tileInfoGenerator.GenerateTileInfo(t, 4, y, x, true)));
        blueBoard.AddTile(tileForBlue);
    }

    cout << greenBoard.GetScore() + blueBoard.GetScore() << "\n";
    cout << greenBoard.CountBlocks() + blueBoard.CountBlocks() << "\n";

    return 0;
}
