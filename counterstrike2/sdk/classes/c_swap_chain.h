#pragma once

class IDXGISwapChain;

class CSwapChainDx11
{
public:
	char pad[0x170];
	IDXGISwapChain* swap_chain;
};

class CSwapChains
{
public:
	CSwapChainDx11* swap_chain_dx;
};