#include <Resources/ResourcesManager.h>

namespace Omnity {
	static ResourcesManager* gBuiltinResourceManager;

	void ResourcesManager::Initialize() {
		if (gBuiltinResourceManager == nullptr)
			gBuiltinResourceManager = new ResourcesManager();
	}
	void ResourcesManager::Destroy() {
		delete gBuiltinResourceManager;
	}
	ResourcesManager* ResourcesManager::GetInstance() {
		return gBuiltinResourceManager;
	}
}