#pragma once

namespace Omnity::Graphic {
	constexpr int UnknownBackend = 0;
	constexpr int VulkanBackend = 1;
	constexpr int DX12Backend = 2;

	bool CheckBackend(uint8_t backendId);
	void InitGraphic();
	bool SetupGraphicBackend(uint8_t backendId);
	bool SetupGraphicBackend();
}