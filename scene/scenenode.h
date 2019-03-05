#ifndef SCENENODE_H
#define SCENENODE_H

#include "math/vector.h"
#include "math/matrix.h"
#include <vector>

class SceneNode
{
public:
    SceneNode(const std::vector<Point2D> &shape, SceneNode *parent=nullptr);
    ~SceneNode();

    void addChild(SceneNode *child);

    Transform2D &transform() { return mTransform; }

    Point2D transformedData(size_t i) const;

    const std::vector<Point2D> &data() const { return mShape; }

private:
    SceneNode *mParent{nullptr};
    std::vector<SceneNode*> mChildren;

    Transform2D mTransform;

    std::vector<Point2D> mShape;
};

#endif // SCENENODE_H
