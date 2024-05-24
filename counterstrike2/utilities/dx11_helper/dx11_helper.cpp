// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "dx11_helper.hpp"
#include "../debug_console/debug.hpp"
#include "../xorstr.h"

#define RELEASE_D3D(p) if(p) { p->Release(); p = nullptr; }

void d3d11_helper::create_render_target()
{
	ID3D11Texture2D* backbuffer;

	if (SUCCEEDED(swapchain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backbuffer))))
	{
		D3D11_RENDER_TARGET_VIEW_DESC desc{};
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;

		device_->CreateRenderTargetView(backbuffer, &desc, &render_target_view_);

		RELEASE_D3D(backbuffer);
	}
}

void d3d11_helper::cleanup_render_target()
{
	RELEASE_D3D(render_target_view_);
}

void d3d11_helper::set_render_targets()
{
	context_->OMSetRenderTargets(1, &render_target_view_, NULL);
}

void d3d11_helper::set_swapchain(IDXGISwapChain* swapchain)
{
	DXGI_SWAP_CHAIN_DESC desc;

	swapchain_ = swapchain;

	if (FAILED(swapchain_->GetDevice(__uuidof(ID3D11Device), (void**)&device_)))
		g_debug.log(xorstr_("device: failed to get device.\n"));

	device_->GetImmediateContext(&context_);

	window_ = FindWindowA("SDL_app", "Counter-Strike 2");
}
