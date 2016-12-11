#include "assignment6/Assignment6.h"
#include "common/core.h"

std::shared_ptr<Camera> Assignment6::CreateCamera() const
{
    const glm::vec2 resolution = GetImageOutputResolution();
    std::shared_ptr<Camera> camera = std::make_shared<PerspectiveCamera>(resolution.x / resolution.y, 26.6f);
    camera->SetPosition(glm::vec3(-0.3f, -2.7f, 5.2f));
    camera->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    
    //camera->Rotate(glm::vec3(0.f, 0.f, 1.f), PI / 10.f); // Looking left slightly
    camera->Rotate(glm::vec3(-1.f, 0.f, 0.f), PI / 8.f); // Looking down slightly
    return camera;
}

std::shared_ptr<Scene> Assignment6::CreateScene() const
{
    std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
    std::vector<std::shared_ptr<aiMaterial>> loadedMaterials;
 
    
    //// Bowl
    
    std::shared_ptr<BlinnPhongMaterial> bowlMaterial = std::make_shared<BlinnPhongMaterial>();
    bowlMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    bowlMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    bowlMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("final/bowl.jpg"));
    
    std::vector<std::shared_ptr<MeshObject>> bowlObject = MeshLoader::LoadMesh("final/bowl.obj", &loadedMaterials);
    for (size_t i = 0; i < bowlObject.size(); ++i) {
        std::shared_ptr<Material> materialCopy = bowlMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        bowlObject[i]->SetMaterial(materialCopy);
    }
    
    std::shared_ptr<SceneObject> bowlSceneObject = std::make_shared<SceneObject>();
    bowlSceneObject->AddMeshObject(bowlObject);
    bowlSceneObject->Rotate(glm::vec3(0.f, 1.f, 0.f), PI / 0.75f); // turn the bowl backwards
    bowlSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    bowlSceneObject->Translate(glm::vec3(-1.30f, 8.0f, -0.3f));
    bowlSceneObject->AddScale(0.5f);
    bowlSceneObject->CreateAccelerationData(AccelerationTypes::UNIFORM_GRID);
    newScene->AddSceneObject(bowlSceneObject);
    
    
    //// Banana
    
    std::shared_ptr<BlinnPhongMaterial> bananaMaterial = std::make_shared<BlinnPhongMaterial>();
    bananaMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    bananaMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    bananaMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("final/banana.jpg"));
    
    std::vector<std::shared_ptr<MeshObject>> bananaObject = MeshLoader::LoadMesh("final/banana.obj", &loadedMaterials);
    for (size_t i = 0; i < bananaObject.size(); ++i) {
        std::shared_ptr<Material> materialCopy = bananaMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        bananaObject[i]->SetMaterial(materialCopy);
    }
    
    std::shared_ptr<SceneObject> bananaSceneObject = std::make_shared<SceneObject>();
    bananaSceneObject->AddMeshObject(bananaObject);
    bananaSceneObject->Rotate(glm::vec3(0.f, 1.f, 0.f), PI / 0.75f); // turn the bowl backwards
    bananaSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    bananaSceneObject->Translate(glm::vec3(-1.30f, 8.0f, -0.3f));
    bananaSceneObject->AddScale(0.5f);
    bananaSceneObject->CreateAccelerationData(AccelerationTypes::UNIFORM_GRID);
    newScene->AddSceneObject(bananaSceneObject);
    
    
    //// Apple
    
    std::shared_ptr<BlinnPhongMaterial> appleMaterial = std::make_shared<BlinnPhongMaterial>();
    appleMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    appleMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    appleMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("final/apple.tif"));
    
    std::vector<std::shared_ptr<MeshObject>> appleObject = MeshLoader::LoadMesh("final/apple.obj", &loadedMaterials);
    for (size_t i = 0; i < appleObject.size(); ++i) {
        std::shared_ptr<Material> materialCopy = appleMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        appleObject[i]->SetMaterial(materialCopy);
    }
    
    std::shared_ptr<SceneObject> appleSceneObject = std::make_shared<SceneObject>();
    appleSceneObject->AddMeshObject(appleObject);
    appleSceneObject->Rotate(glm::vec3(0.f, 1.f, 0.f), PI / 0.75f); // turn the bowl backwards
    appleSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    appleSceneObject->Translate(glm::vec3(-1.30f, 8.0f, -0.3f));
    appleSceneObject->AddScale(0.5f);
    appleSceneObject->CreateAccelerationData(AccelerationTypes::UNIFORM_GRID);
    newScene->AddSceneObject(appleSceneObject);
    
    
    //// Pear
    
    std::shared_ptr<BlinnPhongMaterial> pearMaterial = std::make_shared<BlinnPhongMaterial>();
    pearMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    pearMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    pearMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("final/pear.jpg"));
    
    std::vector<std::shared_ptr<MeshObject>> pearObject = MeshLoader::LoadMesh("final/pear.obj", &loadedMaterials);
    for (size_t i = 0; i < pearObject.size(); ++i) {
        std::shared_ptr<Material> materialCopy = pearMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        pearObject[i]->SetMaterial(materialCopy);
    }
    
    std::shared_ptr<SceneObject> pearSceneObject = std::make_shared<SceneObject>();
    pearSceneObject->AddMeshObject(pearObject);
    pearSceneObject->Rotate(glm::vec3(0.f, 1.f, 0.f), PI / 0.75f); // turn the bowl backwards
    pearSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    pearSceneObject->Translate(glm::vec3(-1.30f, 8.0f, -0.3f));
    pearSceneObject->AddScale(0.5f);
    pearSceneObject->CreateAccelerationData(AccelerationTypes::UNIFORM_GRID);
    newScene->AddSceneObject(pearSceneObject);
    
    
    //// Orange
    
    std::shared_ptr<BlinnPhongMaterial> orangeMaterial = std::make_shared<BlinnPhongMaterial>();
    orangeMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    orangeMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    orangeMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("final/orange.jpg"));
    
    std::vector<std::shared_ptr<MeshObject>> orangeObject = MeshLoader::LoadMesh("final/orange.obj", &loadedMaterials);
    for (size_t i = 0; i < orangeObject.size(); ++i) {
        std::shared_ptr<Material> materialCopy = orangeMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        orangeObject[i]->SetMaterial(materialCopy);
    }
    
    std::shared_ptr<SceneObject> orangeSceneObject = std::make_shared<SceneObject>();
    orangeSceneObject->AddMeshObject(orangeObject);
    orangeSceneObject->Rotate(glm::vec3(0.f, 1.f, 0.f), PI / 0.75f); // turn the bowl backwards
    orangeSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    orangeSceneObject->Translate(glm::vec3(-1.30f, 8.0f, -0.3f));
    orangeSceneObject->AddScale(0.5f);
    orangeSceneObject->CreateAccelerationData(AccelerationTypes::UNIFORM_GRID);
    newScene->AddSceneObject(orangeSceneObject);
    
    
    //// Shelf
    
    std::shared_ptr<BlinnPhongMaterial> tableMaterial = std::make_shared<BlinnPhongMaterial>();
    tableMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    tableMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    tableMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("final/shelf.jpg"));
    
    std::vector<std::shared_ptr<MeshObject>> tableObject = MeshLoader::LoadMesh("final/shelf.obj", &loadedMaterials);
    for (size_t i = 0; i < tableObject.size(); ++i) {
        std::shared_ptr<Material> materialCopy = tableMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        tableObject[i]->SetMaterial(materialCopy);
    }
    
    std::shared_ptr<SceneObject> tableSceneObject = std::make_shared<SceneObject>();
    tableSceneObject->AddMeshObject(tableObject);
    tableSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    tableSceneObject->Translate(glm::vec3(0.30f, 8.0f, -1.00f));
    tableSceneObject->CreateAccelerationData(AccelerationTypes::UNIFORM_GRID);
    newScene->AddSceneObject(tableSceneObject);
    
    
    //// Wall
    
    std::shared_ptr<BlinnPhongMaterial> wallMaterial = std::make_shared<BlinnPhongMaterial>();
    wallMaterial->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    wallMaterial->SetSpecular(glm::vec3(0.6f, 0.6f, 0.6f), 40.f);
    wallMaterial->SetTexture("diffuseTexture", TextureLoader::LoadTexture("final/wall_large.jpg"));
    
    std::vector<std::shared_ptr<MeshObject>> wallObject = MeshLoader::LoadMesh("final/wall_small_2.obj", &loadedMaterials);
    for (size_t i = 0; i < wallObject.size(); ++i) {
        std::shared_ptr<Material> materialCopy = wallMaterial->Clone();
        materialCopy->LoadMaterialFromAssimp(loadedMaterials[i]);
        wallObject[i]->SetMaterial(materialCopy);
    }
    
    std::shared_ptr<SceneObject> wallSceneObject = std::make_shared<SceneObject>();
    wallSceneObject->AddMeshObject(wallObject);
    wallSceneObject->Rotate(glm::vec3(1.f, 0.f, 0.f), PI / 2.f);
    wallSceneObject->Translate(glm::vec3(0.30f, 8.0f, -1.00f));
    wallSceneObject->CreateAccelerationData(AccelerationTypes::UNIFORM_GRID);
    newScene->AddSceneObject(wallSceneObject);
    
    
    
    //// Lights
    std::shared_ptr<PointLight> highPointLight = std::make_shared<PointLight>();
    highPointLight->SetPosition(glm::vec3(0.f, 2.f, 4.8f));
    highPointLight->SetLightColor(glm::vec3(0.75f, 0.65f, 0.65f));
    newScene->AddLight(highPointLight);
    
    std::shared_ptr<PointLight> leftPointLight = std::make_shared<PointLight>();
    leftPointLight->SetPosition(glm::vec3(-8.30f, 3.0f, 3.f));
    leftPointLight->SetLightColor(glm::vec3(0.6f, 0.6f, 0.6f));
    newScene->AddLight(leftPointLight);
    
    std::shared_ptr<PointLight> lowPointLight = std::make_shared<PointLight>();
    lowPointLight->SetPosition(glm::vec3(0.f, 5.0101f, -2.f));
    lowPointLight->SetLightColor(glm::vec3(0.5f, 0.5f, 0.5f));
    newScene->AddLight(lowPointLight);
    

    return newScene;
}

std::shared_ptr<ColorSampler> Assignment6::CreateSampler() const
{
    std::shared_ptr<JitterColorSampler> jitter = std::make_shared<JitterColorSampler>();
    // ASSIGNMENT 6 TODO: Change the grid size to be glm::ivec3(X, Y, 1).
    jitter->SetGridSize(glm::ivec3(1, 1, 1));

    std::shared_ptr<SimpleAdaptiveSampler> sampler = std::make_shared<SimpleAdaptiveSampler>();
    sampler->SetInternalSampler(jitter);

    // ASSIGNMENT 6 TODO: Change the '1.f' in '1.f * SMALL_EPSILON' here to be higher and see what your results are. (Part 3)
    sampler->SetEarlyExitParameters(1.f * SMALL_EPSILON, 16);

    // ASSIGNMENT 6 TODO: Comment out 'return jitter;' to use the adaptive sampler. (Part 2)
    //return jitter;
    return sampler;
}

std::shared_ptr<class Renderer> Assignment6::CreateRenderer(std::shared_ptr<Scene> scene, std::shared_ptr<ColorSampler> sampler) const
{
    return std::make_shared<BackwardRenderer>(scene, sampler);
}

int Assignment6::GetSamplesPerPixel() const
{
    // ASSIGNMENT 6 TODO: Change the '1' here to increase the maximum number of samples used per pixel. (Part 1).
    return 1;
}

bool Assignment6::NotifyNewPixelSample(glm::vec3 inputSampleColor, int sampleIndex)
{
    return true;
}

int Assignment6::GetMaxReflectionBounces() const
{
    return 0;
}

int Assignment6::GetMaxRefractionBounces() const
{
    return 0;
}

glm::vec2 Assignment6::GetImageOutputResolution() const
{
    return glm::vec2(640.f, 480.f);
}
