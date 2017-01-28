inline void MovableObject::setParent(SceneNode* parent) {
    _parent = parent;
}

inline SceneNode* MovableObject::getParent() {
    return _parent;
}

inline const std::string& MovableObject::getName() const {
    return _name;
}