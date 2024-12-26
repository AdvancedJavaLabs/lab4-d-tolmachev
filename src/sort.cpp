#include "Pipes.hh"
#include "TemplateFactory.hh"

#include "mapper.hpp"
#include "partitioner.hpp"
#include "reducer.hpp"

int main() {
    return HadoopPipes::runTask(HadoopPipes::TemplateFactory<analytics::SortMapper, analytics::SortReducer, analytics::SortPartitioner, analytics::SortReducer>());
}
