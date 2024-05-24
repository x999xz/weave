#pragma once

#include <d3d11.h>
#include <cstdint>
#include <dxgi.h>
#include <cmath>
#include <algorithm>
#include <memory>

class d3d11_helper
{
public:
	void set_swapchain(IDXGISwapChain* swapchain);
	void set_window(HWND window);

	auto get_device() const { return device_; }
	auto get_context() const { return context_; }
	auto get_render_target_view() const { return render_target_view_; }
	auto get_window() const { return window_; }

	auto reset_device() { 
		if (device_)
		{
			device_->Release();
			device_ = nullptr;
		}
	}

	void create_render_target();
	void cleanup_render_target();
	void set_render_targets();

private:
	IDXGISwapChain* swapchain_{};
	HWND window_{};
	ID3D11Device* device_{};
	ID3D11RenderTargetView* render_target_view_{};
	ID3D11DeviceContext* context_{};
};

inline auto g_d3d11_helper = std::make_unique<d3d11_helper>();