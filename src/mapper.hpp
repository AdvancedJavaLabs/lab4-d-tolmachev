#ifndef MAPPER_HPP
#define MAPPER_HPP

#include "Pipes.hh"

namespace analytics {

class AggregateMapper : public HadoopPipes::Mapper {
public:
    AggregateMapper(HadoopPipes::TaskContext& context);

    void map(HadoopPipes::MapContext& context);
};

class SortMapper : public HadoopPipes::Mapper {
public:
    SortMapper(HadoopPipes::TaskContext& context);

    void map(HadoopPipes::MapContext& context);

private:
    bool is_first_;
};

}

#endif
