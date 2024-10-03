#include <gtest/gtest.h>
#include <graphic/texture.h>
#include <base/types.h>

TEST(resource, serialize) {
	omnity::texture tex(1, 2);
}

TEST(resource, register_and_get) {
    /*Omnity::ResourcesManager::Initialize();
    auto resManager = Omnity::ResourcesManager::GetInstance();
    resManager->RegisterResource<Omnity::Texture>(1, 1920, 1080);
    auto res = resManager->GetResource(1);
    auto& texture = res->Content<Omnity::Texture>();
    EXPECT_EQ(texture.Width(), 1920);
    EXPECT_EQ(texture.Height(), 1920);*/
}