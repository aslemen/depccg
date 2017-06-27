
#ifndef INCLUDE_CHART_H_
#define INCLUDE_CHART_H_

#include <vector>
#include "tree.h"

namespace myccg {


typedef std::pair<NodeType, float> ScoredNode;

struct ChartCell
{
    ChartCell();

    ~ChartCell() {}

    bool IsEmpty() const { return items.size() == 0; }
    std::vector<ScoredNode> GetBestParse() {
        return std::vector<ScoredNode>(
                {std::make_pair(best, best_prob)});
    }
    std::vector<ScoredNode> GetNBestParses();
    bool update(NodeType parse, float prob);
    std::unordered_map<Cat, ScoredNode> items;
    float best_prob;
    NodeType best;
};


class Chart
{
public:
    Chart(int sent_size);

    ~Chart();

    ChartCell* operator() (int row, int column);

    unsigned Size() const;
    bool IsEmpty() const;

    std::vector<ChartCell*>& GetCellsStartingAt(int idx) {
        return starting_cells_[idx];
    }

    std::vector<ChartCell*>& GetCellsEndingAt(int idx) {
        return ending_cells_[idx];
    }

private:
    int sent_size_;
    int chart_size_;
    ChartCell** chart_;
    std::vector<ChartCell*>* ending_cells_;
    std::vector<ChartCell*>* starting_cells_;
};

} // namespace myccg

#endif
