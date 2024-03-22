#include <vector>
#define vector1d std::vector<int>
#define vector2d std::vector<vector1d>

// For the time being everything gonna be in the header
// Will update in the future (hopefully)
class BlockTemplate
{
public:
    // Expand Block
    static const vector2d expandX(const vector2d &original, int columns) {
        vector2d expanded;

        for (vector1d row : original) {
            vector1d expandedRow;

            for (int i = 0; i < columns; ++i)
                expandedRow.push_back(row[0]);

            expanded.push_back(expandedRow); // Add the expanded row to the expanded vector
        }

        return expanded;
    }
    //---
    static const vector2d expandY(const vector2d& original, int rows) {
        vector2d expanded;
        vector1d row = original[0];

        for (int i = 0; i < rows; ++i)
            expanded.push_back(row);

        return expanded;
    }

    // Merge Block
    static const vector2d mergeX(
        const vector2d &vec1,
        const vector2d &vec2
    ){
        vector2d merged = vec1;

        for (int i = 0; i < vec2.size(); i++)
            for (int j = 0; j < vec2[0].size(); j++)
                merged[i].push_back(vec2[i][j]);

        return merged;
    }

    static const vector2d mergeX2(
        const vector2d &vecPre,
        const vector2d &vecCur,
        const vector2d &vecPost
    ){
        vector2d merged = vecPre;

        int height = vecCur.size();

        for (int i = 0; i < height; i++)
            for (int j = 0; j < vecCur[0].size(); j++)
                merged[i].push_back(vecCur[i][j]);

        for (int i = 0; i < height; i++)
            for (int j = 0; j < vecPost[0].size(); j++)
                merged[i].push_back(vecPost[i][j]);

        return merged;
    }
    //---
    static const vector2d mergeY(
        const vector2d &vec1,
        const vector2d &vec2
    ){
        vector2d merged = vec1;

        for (vector1d row : vec2)
            merged.push_back(row);

        return merged;
    }

    static const vector2d mergeY2(
        const vector2d &vecPre,
        const vector2d &vecCur,
        const vector2d &vecPost
    ){
        vector2d merged = vecPre;

        for (vector1d row : vecCur)
            merged.push_back(row);
        for (vector1d row : vecPost)
            merged.push_back(row);

        return merged;
    }
};