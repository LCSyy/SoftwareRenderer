#include "scenenode.h"

SceneNode::SceneNode(const std::vector<Point2D> &shape, SceneNode *parent)
    : mParent(parent)
    , mShape(shape)
{
    if(mParent) {
        mParent->addChild(this);
    }
}

SceneNode::~SceneNode()
{
    for(SceneNode *child: mChildren) {
        if(child) {
            delete child;
            child = nullptr;
        }
    }
}

void SceneNode::addChild(SceneNode *child)
{
    if(child) {
        mChildren.push_back(child);
    }
}

Point2D SceneNode::transformedData(size_t i) const
{
    Point2D p;
    p.x = mShape.at(i).x
            * mTransform.mRotate.m[0][0]
            * mTransform.mScale.m[0][0]
            + mShape.at(i).y
            * mTransform.mRotate.m[1][0]
            * mTransform.mScale.m[0][0]
            + mTransform.mTranslation._x;

    p.y = mShape.at(i).x
            * mTransform.mRotate.m[0][1]
            * mTransform.mScale.m[1][1]
            + mShape.at(i).y
            * mTransform.mRotate.m[1][1]
            * mTransform.mScale.m[1][1]
            + mTransform.mTranslation._y;

    return p;
}
