#include "partitioner.hpp"

#include <limits>

namespace analytics {

SortPartitioner::SortPartitioner(HadoopPipes::TaskContext& context) {
}

int SortPartitioner::partition(const std::string& key, int numOfReduces) {
    if (key == std::to_string(std::numeric_limits<size_t>::max())) {
        return 0;
    }
    return std::hash<std::string>()(key) % numOfReduces;
}

}
