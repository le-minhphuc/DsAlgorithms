#pragma once

#include <cstring>
#include <string>
#include <vector>

namespace ds_algorithms {

namespace string {

/*
Arguments:
    - augStr: original string with $ appended to the end of it.
Return:
    - suffix-index array p: p[i] = the index (i.e. order) of suffix augStr[i:] in the sorted suffix array
*/
inline std::vector<uint32_t> buildSuffixArray(const std::string& augStr)
{
    std::vector<uint32_t> pos(augStr.size(), 0);
    std::vector<uint32_t> grp(augStr.size(), 0);

    // counting sort on first char
    std::vector<uint32_t> cnt((uint32_t)'z' + 1, 0);
    for (int i = 0; i < augStr.size(); ++i)
        cnt[augStr[i]]++;
    for (int i = 0; i < 'z'; ++i)
        cnt[i + 1] += cnt[i];
    for (int i = 0; i < augStr.size(); ++i)
    {
        uint32_t suffix = cnt[(uint32_t)augStr[i] - 1]++;
        pos[suffix] = i;
    }

    // assign groups
    uint32_t maxGrp = 0;
    for (int i = 0; i < pos.size(); ++i)
    {
        if (i > 0 && augStr[pos[i - 1]] != augStr[pos[i]])
            maxGrp++;
        grp[pos[i]] = maxGrp;
    }

    std::vector<uint32_t> newPos(augStr.size(), 0);
    std::vector<uint32_t> newGrp(augStr.size(), 0);
    for (uint32_t k = 2; k <= augStr.size(); k *= 2)
    {
        uint32_t offset = k/2;
        // counting sort by second group, cnt[0] reserved for group -1
        cnt.assign(maxGrp + 2, 0);
        for (int i = 0; i < augStr.size(); ++i)
        {
            if (i + offset >= augStr.size())
                cnt[1]++;
            else
                cnt[grp[i + offset] + 1]++;
        }
        for (int i = 0; i < cnt.size() - 1; ++i)
            cnt[i + 1] += cnt[i];
        for (int i = 0; i < pos.size(); ++i)
        {
            uint32_t suffix = pos[i];
            uint32_t suffixGrp = (suffix + offset >= augStr.size() ? 0 : grp[suffix + offset]);
            newPos[cnt[suffixGrp]++] = suffix;
        }
        pos.assign(newPos.begin(), newPos.end());

        // counting sort by first group
        cnt.assign(maxGrp + 2, 0);
        for (int i = 0; i < augStr.size(); ++i)
            cnt[grp[i] + 1]++;
        for (int i = 0; i < cnt.size() - 1; ++i)
            cnt[i + 1] += cnt[i];
        for (int i = 0; i < pos.size(); ++i)
        {
            uint32_t suffixIdx = pos[i];
            newPos[cnt[grp[suffixIdx]]++] = suffixIdx;
        }
        pos.assign(newPos.begin(), newPos.end());

        // assign new groups
        maxGrp = 0;
        uint32_t prevFirstGrp = grp[pos[0]];
        uint32_t prevSecondGrp = (pos[0] + offset >= augStr.size() ? 0 : grp[ pos[0] + offset ]);
        for (uint32_t i = 0; i < pos.size(); ++i)
        {
            uint32_t suffix = pos[i];
            uint32_t suffixFirstGrp = grp[suffix];
            uint32_t suffixSecondGrp = (suffix + offset >= augStr.size() ? 0 : grp[suffix + offset]);
            if (i > 0
                && (suffixFirstGrp != prevFirstGrp || suffixSecondGrp != prevSecondGrp) )
            {
                maxGrp++;
                prevFirstGrp = suffixFirstGrp;
                prevSecondGrp = suffixSecondGrp;
            }
            newGrp[suffix] = maxGrp;
        }
        grp.assign(newGrp.begin(), newGrp.end());
    }

    return pos;
}

/*
Arguments:
    - augStr: original string with $ appended to the end of it.
    - p[i]: the index (i.e. order) of suffix augStr[i:] in the sorted suffix array
Return:
    - Longest Common Prefix (lcp) array: lcp[i] = length of longest common prefix between (i-1)-th and i-th elements of
    the sorted suffix array
*/
inline std::vector<uint32_t> buildLcpArray(const std::string& augStr, const std::vector<uint32_t> p)
{
    // Kasai's algorithms
    std::vector<uint32_t> rank(augStr.size(), 0);
    std::vector<uint32_t> lcp(p.size(), 0);
    for (int i = 0; i < p.size(); ++i)
        rank[p[i]] = i;
    uint32_t h = 0;
    for (int i = 0; i < augStr.size(); ++i)
    {
        // calculate lcp[rank[i]]
        if (rank[i] > 0)
        {
            int j = p[rank[i] - 1];
            while (augStr[i + h] == augStr[j + h])
                h++;
            lcp[rank[i]] = h;
            if (h > 0)
                h--;
        }
    }
    return lcp;
}

} // namespace string

} // namespace ds_algorithms