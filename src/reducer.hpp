#ifndef REDUCER_HPP
#define REDUCER_HPP

#include "Pipes.hh"

namespace analytics {

class AggregateReducer : public HadoopPipes::Reducer {
public:
    AggregateReducer(HadoopPipes::TaskContext& context);

    void reduce(HadoopPipes::ReduceContext& context);
};

class SortReducer : public HadoopPipes::Reducer {
public:
    SortReducer(HadoopPipes::TaskContext& context);

    void reduce(HadoopPipes::ReduceContext& context);

private:
    bool is_first_;
};

}

#endif
