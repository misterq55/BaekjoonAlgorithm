#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class CTile
{
public:
    CTile(){}
    CTile(const int type, const int y, const int x, const bool reverse)
    {
        Type = type;
        const int tileTypeIndex = reverse ? 1 : 0;
        TilePosistions.emplace_back(y, x);

        if (type > 1)
        {
            const pair<int, int> addedTile = TileTypes[tileTypeIndex][type - 1];
            TilePosistions.emplace_back(y + addedTile.first, x + addedTile.second);
        }

        for (pair<int, int>& tilePosistion : TilePosistions)
        {
            tilePosistion.first -= y;
        }
    }
    ~CTile(){}

public:
    vector<pair<int, int>>& GetTilePositions() { return TilePosistions; }
    int GetType() { return Type; }
    
private:
    vector<pair<int, int>> TilePosistions;
    vector<vector<pair<int, int>>> TileTypes = {{{0, 0},{0, 1}, {1, 0} }, {{0, 0},{1, 0}, {0, -1} }};
    int Type = 0;
};

class CBoard
{
public:
    CBoard(){}

    CBoard(const int row, const int col)
    {
        Board = move(vector<vector<int>>(row, vector<int>(col, 0)));
        HighestHeight = move(vector<int>(col, row - 1));
    }

    ~CBoard(){}

public:
    void AddTile(CTile& tile)
    {
        vector<pair<int, int>>& tilePositions = tile.GetTilePositions();
        addTileInternal(tilePositions, tile.GetType());
        
        vector<int> deletedLines = lineScoreCheck();
        deleteLines(deletedLines);
        renewalBlocks(deletedLines);

        if (!deletedLines.empty())
        {
            adjustHighestHeight();
        }

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
        const int size = static_cast<int>(Board.size());
        int count = 0;
        
        for (int i = 0; i < size; ++i)
        {
            vector<int>& line = Board[i];
            const int lineSize = static_cast<int>(line.size());
            for (int j = 0; j < lineSize; j++)
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

    vector<int> lineScoreCheck()
    {
        vector<int> deletedLines;
        const int size = static_cast<int>(Board.size());
        
        for (int i = 0; i < size; ++i)
        {
            int lineFillCounter = 0;
            vector<int>& line = Board[i];
            const int lineSize = static_cast<int>(line.size());
            for (int j = 0; j < lineSize; j++)
            {
                if (line[j] >= 1)
                {
                    lineFillCounter++;
                }
            }

            if (lineFillCounter == lineSize)
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
            const int lineSize = static_cast<int>(line.size());
            line.clear();
            line.resize(lineSize);
        }
    }

    vector<int> areaCheck()
    {
        vector<int> deletedLines;
        int counter = 0;
        const int size = static_cast<int>(Board.size());
        for (int i = 0; i <= 1; ++i)
        {
            vector<int>& line = Board[i];
            const int lineSize = static_cast<int>(line.size());
            for (int j = 0; j < lineSize; ++j)
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
            deletedLines.push_back(size - 1 - i);
        }

        return move(deletedLines);
    }
    
    void renewalBlocks(vector<int>& deletedLines)
    {
        if (deletedLines.empty())
        {
            return;
        }

        sort(deletedLines.begin(), deletedLines.end());

        const int size = static_cast<int>(deletedLines.size());
        
        for (const int deletedLine : deletedLines)
        {
            for (int i = deletedLine; i >= 1; --i)
            {
                Board[i] = Board[i - 1];
            }
        }

        const int lineSize = static_cast<int>(Board[0].size());
        Board[0].clear();
        Board[0].resize(lineSize);
        Board[1].clear();
        Board[1].resize(lineSize);
    }

    void adjustHighestHeight()
    {
        HighestHeight = {5, 5, 5, 5};
        const int size = static_cast<int>(Board.size());

        for (int i = size - 1; i >= 0; --i)
        {
            vector<int>& line = Board[i];
            const int lineSize = static_cast<int>(line.size());
            for (int j = 0; j < lineSize; ++j)
            {   
                if (line[j] >= 1)
                {
                    HighestHeight[j] = i - 1;
                }
            }
        }
    }
private:
    vector<vector<int>> Board;
    vector<int> HighestHeight;
    int Score = 0;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    CBoard greenBoard(6, 4), blueBoard(6, 4);
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t, y, x;
        cin >> t >> y >> x;

        CTile tileForGreen(t, y, x, false);
        greenBoard.AddTile(tileForGreen);
        
        CTile tileForBlue(t, x, 4 - 1 - y, true);
        blueBoard.AddTile(tileForBlue);
    }

    cout << greenBoard.GetScore() + blueBoard.GetScore() << "\n";
    cout << greenBoard.CountBlocks() + blueBoard.CountBlocks() << "\n";
    
    return 0;
}
