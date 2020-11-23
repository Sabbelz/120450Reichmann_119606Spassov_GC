
#ifndef GEOMETRYNODE_HPP
#define GEOMETRYNODE_HPP

#include "model.hpp"
#include "Node.hpp"

class GeometryNode : public Node {
public:
    model getGeometry() const;

    void setGeometry(model model);

private:
    model geometry_;
};
#endif //GEOMETRYNODE_HPP
