#include <Geode/Geode.hpp>
using namespace geode::prelude;

class $modify(MyGameLayer, GJBaseGameLayer) {
    struct Fields {
        cocos2d::CCDrawNode* m_overlay = nullptr;
    };

    cocos2d::ccColor4F colorFor(GameObject* obj) {
        auto t = obj->getType();
        if (t == GameObjectType::Solid || t == GameObjectType::Slope)
            return {0.f, 0.5f, 1.f, 1.f};
        if (t == GameObjectType::Hazard)
            return {1.f, 0.f, 0.f, 1.f};
        if (t == GameObjectType::Portal || t == GameObjectType::Orb || t == GameObjectType::Modifier)
            return {0.f, 1.f, 0.f, 1.f};
        return {1.f, 1.f, 1.f, 1.f};
    }

    void update(float dt) {
        GJBaseGameLayer::update(dt);

        if (!m_fields->m_overlay) {
            m_fields->m_overlay = cocos2d::CCDrawNode::create();
            this->addChild(m_fields->m_overlay, 100);
        }
        auto node = m_fields->m_overlay;
        node->clear();

        if (!m_objects) return;
        for (auto obj : CCArrayExt<GameObject*>(m_objects)) {
            if (!obj || !obj->isVisible()) continue;
            auto rect = obj->getObjectRect();
            node->drawRect(rect, {0,0,0,0}, 1.f, colorFor(obj));
        }
    }
};
