#ifndef PROPAGATE_FLAGS_H
#define PROPAGATE_FLAGS_H

#include "ift.h"

class PropagateFlags {
  public:
    virtual ~PropagateFlags() {};
    virtual void propagate_flags(IFTGraph& G) = 0;
};

class IterativePropagate : public PropagateFlags {
  public: 
    void propagate_flags(IFTGraph& G);
};

class MultithreadPropagate : public PropagateFlags {
  public: 
    void propagate_flags(IFTGraph& G);
};

class GraphItPropagate : public PropagateFlags {
  public: 
    void propagate_flags(IFTGraph& G);

  private:
    // stuff
};

#endif  // PROPAGATE_FLAGS_H