#include "Scene.hpp"

#include "Helpers.hpp"

int main()
{
    engine::Scene scene({800, 600});

    for (int i = 0; i < 10; i++)
    {
        engine::Object obj(scene);
        obj.shape.setPosition({
            scene.getWindow().getSize().x / 2.f,
            scene.getWindow().getSize().y / 2.f //
        });
        obj.shape.move(utils::getRandomVector(200, i));
        scene.addObject(obj);
    }

    scene.startLoop();
}