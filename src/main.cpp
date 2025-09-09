#include "Scene.hpp"

#include "Helpers.hpp"

int main()
{
    engine::Scene scene({800, 600});

    for (int i = 0; i < 1; i++)
    {
        engine::Object obj(scene);
        obj.setPosition({
            scene.GetWindow().getSize().x / 2.f,
            scene.GetWindow().getSize().y / 2.f //
        });
        obj.move(utils::getRandomVector(200, i));
        obj.setVelocity(utils::getRandomVector(200, i));
        obj.setAcceleration({0, 1000});
        scene.AddObject(obj);
    }

    scene.StartLoop();
}