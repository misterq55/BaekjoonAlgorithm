#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct TileInfo
{
    vector<pair<int, int>> TilePositions;
    int BaseY = 0;
    int Index = 0;
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
        if (type > 1)
        {
            tileInfo.TilePositions.emplace_back(tileBasePos.first + tileType.first,
                                                tileBasePos.second + tileType.second);
        }
        tileInfo.BaseY = tileBasePos.first;
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
    CTile()
    {
    }

    CTile(const TileInfo& tileInfo)
    {
        Info = tileInfo;
    }

    ~CTile()
    {
    }

public:
    void Move(const vector<int>& highestHeight)
    {
        int maxHeight = static_cast<int>(1e9);
        for (const auto& tilePos : Info.TilePositions)
        {
            const int x = tilePos.second;
            maxHeight = min(maxHeight, highestHeight[x]);
        }

        for (auto& tilePosition : Info.TilePositions)
        {
            tilePosition.first = maxHeight - (tilePosition.first - Info.BaseY);
        }
    }

    bool DeletePos(const int y, const int x)
    {
        Info.TilePositions.erase(remove(Info.TilePositions.begin(), Info.TilePositions.end(), make_pair(y, x)),
                                 Info.TilePositions.end());
        int temp = 0;

        return Info.TilePositions.empty();
    }

    vector<pair<int, int>> GetTilePositions()
    {
        return Info.TilePositions;
    }

    int GetIndex()
    {
        return Info.Index;
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

            if (!deletedLines.empty())
            {
                adjustHighestHeight();
            }
        }
        while (!deletedLines.empty());

        deletedLines = areaCheck();
        deleteLines(deletedLines);
        renewalBlocks(deletedLines);

        if (!deletedLines.empty())
        {
            adjustHighestHeight();
        }
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
    void addTileInternal(const vector<pair<int, int>>& tilePositions, const int type)
    {
        int maxHeight = static_cast<int>(1e9);
        const int size = static_cast<int>(tilePositions.size());
        for (int i = 0; i < size; i++)
        {
            pair<int, int> tilePosition = tilePositions[i];
            const int x = tilePosition.second;
            const int y = HighestHeight[x];
            maxHeight = min(y, maxHeight);
        }

        for (int i = 0; i < size; i++)
        {
            pair<int, int> tilePosition = tilePositions[i];
            const int x = tilePosition.second;
            const int y = maxHeight - tilePosition.first;
            Board[y][x] = type;
            HighestHeight[x] = y - 1;
        }
    }

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
        // for (int i = Row - 1; i >= 0; --i)
        // {
        //     vector<int>& line = Board[i];
        //     for (int j = 0; j < Col; ++j)
        //     {   
        //         if (line[j] == 0)
        //         {
        //             HighestHeight[j] = i;
        //             continue;
        //         }
        //     }
        // }

        for (int j = 0; j < Col; ++j)
        {
            for (int i = Row - 1; i >= 0; --i)
            {
                vector<int>& line = Board[i];

                if (line[j] == 0)
                {
                    HighestHeight[j] = i;
                    break;
                }
            }
        }

        sort(deletedLines.begin(), deletedLines.end());

        for (const int deletedLine : deletedLines)
        {
            for (int i = deletedLine; i >= 1; --i)
            {
                Board[i] = Board[i - 1];
            }
        }

        Board[0].clear();
        Board[0].resize(Col);
        Board[1].clear();
        Board[1].resize(Col);

        // 모노미노도미노
        // {
        //     for (pair<const int, shared_ptr<CTile>>& tilePair : Tiles)
        //     {
        //         shared_ptr<CTile> tile = tilePair.second;
        //         for (pair<int, int>& tilePos : tile->GetTilePositions())
        //         {
        //             const int y = tilePos.first;
        //             const int x = tilePos.second;
        //             Board[y][x] = 0;
        //         }
        //         
        //         tile->Move(HighestHeight);
        //
        //         for (pair<int, int>& tilePos : tile->GetTilePositions())
        //         {
        //             const int y = tilePos.first;
        //             const int x = tilePos.second;
        //             Board[y][x] = tile->GetIndex();
        //         }
        //     }
        // }
    }

    void adjustHighestHeight()
    {
        HighestHeight = {Row - 1, Row - 1, Row - 1, Row - 1,};

        for (int i = 0; i < Row; ++i)
        {
            vector<int>& line = Board[i];
            for (int j = 0; j < Col; ++j)
            {
                if (line[j] >= 1)
                {
                    HighestHeight[j] = i - 1;
                    continue;
                }
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
