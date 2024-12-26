#ifndef PARTITIONER_HPP
#define PARTITIONER_HPP

#include "Pipes.hh"

#include <string>

namespace analytics {

class SortPartitioner : public HadoopPipes::Partitioner {
public:
    SortPartitioner(HadoopPipes::TaskContext& context);

    int partition(const std::string& key, int numOfReduces) override;
};

}

#endif
