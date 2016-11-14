#include "assignment7/Assignment7.h"
#include "common/core.h"

std::shared_ptr<Camera> Assignment7::CreateCamera() const
{
    const glm::vec2 resolution = GetImageOutputResolution();
    std::shared_ptr<Camera> camera = std::make_shared<PerspectiveCamera>(resolution.x / resolution.y, 26.6f);
    camera->SetPosition(glm::vec3(0.f, -4.1469f, 0.73693f));
    camera->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    return camera;
}


// Assignment 7 Part 1 TODO: Change the '1' here.
// 0 -- Naive.
// 1 -- BVH.
// 2 -- Grid.
#define ACCELERATION_TYPE 2

std::shared_ptr<Scene> Assignment7::CreateScene() const
{
    std::shared_ptr<Scene> newScene = std::make_shared<Scene>();

    // Material
    std::shared_ptr<BlinnPhongMaterial> cubeMaterial = std::make_shared<BlinnPhongMaterial>();
    cubeMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    cubeMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    cubeMaterial->SetReflectivity(0.3f);
    
    std::shared_ptr<BlinnPhongMaterial> balloonMaterial = std::make_shared<BlinnPhongMaterial>();
    balloonMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    balloonMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    balloonMaterial->SetReflectivity(0.3f);
    balloonMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("assignment7/rainbow.jpg"));
    
    std::shared_ptr<BlinnPhongMaterial> deerMaterial = std::make_shared<BlinnPhongMaterial>();
    deerMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    deerMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    deerMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("assignment7/marble.jpg"));

    // Objects
    /*
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials;
    std::vector<std::shared_ptr<MeshObject>> cubeObjects = MeshLoader::LoadMesh("CornellBox/CornellBox-Assignment7-Alt.obj", &loadedMaterials);
    for (size_t i = 0; i < cubeObjects.size(); ++i) {
        std::shared_ptr<Material> materialCopy = cubeMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        cubeObjects[i]->SetMaterial(materialCopy);

        std::shared_ptr<SceneObject> cubeSceneObject = std::make_shared<SceneObject>();
        cubeSceneObject->AddMeshObject(cubeObjects[i]);
        cubeSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);

        cubeSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
        cubeSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
            BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
            accelerator->SetMaximumChildren(2);
            accelerator->SetNodesOnLeaves(2);
        });

        cubeSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
            BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
            accelerator->SetMaximumChildren(2);
            accelerator->SetNodesOnLeaves(2);
        });
        newScene->AddSceneObject(cubeSceneObject);
    }
     */
    
    
    // Balloon
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials2;
    std::vector<std::shared_ptr<MeshObject>> balloonObject = MeshLoader::LoadMesh("assignment7/small_balloon.obj", &loadedMaterials2);
    for (size_t i = 0; i < balloonObject.size(); ++i) {
        std::shared_ptr<Material> materialCopy = balloonMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials2[i]);
        balloonObject[i]->SetMaterial(materialCopy);
    }
    
    std::shared_ptr<SceneObject> balloonSceneObject = std::make_shared<SceneObject>();
    balloonSceneObject->AddMeshObject(balloonObject);
    balloonSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    balloonSceneObject->Translate(glm::vec3(0.55f, 0.0f, 0.0f));
    
    balloonSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
    balloonSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    
    balloonSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    newScene->AddSceneObject(balloonSceneObject);

    
    // Deer
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials3;
    std::vector<std::shared_ptr<MeshObject>> deerObject = MeshLoader::LoadMesh("assignment7/small_deer.obj", &loadedMaterials3);
    for (size_t i = 0; i < deerObject.size(); ++i) {
        std::shared_ptr<Material> materialCopy = deerMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials3[i]);
        deerObject[i]->SetMaterial(materialCopy);
    }
    
    std::shared_ptr<SceneObject> deerSceneObject = std::make_shared<SceneObject>();
    deerSceneObject->AddMeshObject(deerObject);
    deerSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    deerSceneObject->Translate(glm::vec3(0.55f, 1.2f, 0.0f));
    
    deerSceneObject->CreateAccelerationData(AccelerationTypes::BVH);
    deerSceneObject->ConfigureAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    
    deerSceneObject->ConfigureChildMeshAccelerationStructure([](AccelerationStructure* genericAccelerator) {
        BVHAcceleration* accelerator = dynamic_cast<BVHAcceleration*>(genericAccelerator);
        accelerator->SetMaximumChildren(2);
        accelerator->SetNodesOnLeaves(2);
    });
    newScene->AddSceneObject(deerSceneObject);
    
    
    
    // Lights
    std::shared_ptr<Light> pointLight = std::make_shared<PointLight>();
    pointLight->SetPosition(glm::vec3(0.01909f, 0.0101f, 1.97028f));
    pointLight->SetLightColor(glm::vec3(1.f, 1.f, 1.f));
    
    std::shared_ptr<Light> pointLight2 = std::make_shared<PointLight>();
    pointLight2->SetPosition(glm::vec3(1.97028f, 0.01909f, 0.0101f));
    pointLight2->SetLightColor(glm::vec3(1.f, 1.f, 1.f));

#if ACCELERATION_TYPE == 0
    newScene->GenerateAccelerationData(AccelerationTypes::NONE);
#elif ACCELERATION_TYPE == 1
    newScene->GenerateAccelerationData(AccelerationTypes::BVH);
#else
    UniformGridAcceleration* accelerator = dynamic_cast<UniformGridAcceleration*>(newScene->GenerateAccelerationData(AccelerationTypes::UNIFORM_GRID));
    assert(accelerator);
    // Assignment 7 Part 2 TODO: Change the glm::ivec3(10, 10, 10) here.
    accelerator->SetSuggestedGridSize(glm::ivec3(3, 3, 3));
#endif
    newScene->AddLight(pointLight);
    newScene->AddLight(pointLight2);

    return newScene;

}
std::shared_ptr<ColorSampler> Assignment7::CreateSampler() const
{
    std::shared_ptr<JitterColorSampler> jitter = std::make_shared<JitterColorSampler>();
    jitter->SetGridSize(glm::ivec3(1, 1, 1));
    return jitter;
}

std::shared_ptr<class Renderer> Assignment7::CreateRenderer(std::shared_ptr<Scene> scene, std::shared_ptr<ColorSampler> sampler) const
{
    return std::make_shared<BackwardRenderer>(scene, sampler);
}

int Assignment7::GetSamplesPerPixel() const
{
    return 1;
}

bool Assignment7::NotifyNewPixelSample(glm::vec3 inputSampleColor, int sampleIndex)
{
    return true;
}

int Assignment7::GetMaxReflectionBounces() const
{
    return 2;
}

int Assignment7::GetMaxRefractionBounces() const
{
    return 4;
}

glm::vec2 Assignment7::GetImageOutputResolution() const
{
    return glm::vec2(640.f, 480.f);
}
