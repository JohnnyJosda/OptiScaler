#pragma once

#include <framegen/IFGFeature_Dx12.h>

#include <proxies/XeLL_Proxy.h>
#include <proxies/XeFG_Proxy.h>

#include <xell.h>
#include <xell_d3d12.h>
#include <xefg_swapchain.h>
#include <xefg_swapchain_d3d12.h>
#include <xefg_swapchain_debug.h>

class XeFG_Dx12 : public virtual IFGFeature_Dx12
{
  private:
    xefg_swapchain_handle_t _swapChainContext = nullptr;

    uint32_t _width = 0;
    uint32_t _height = 0;
    int _featureFlags = 0;

    static void xefgLogCallback(const char* message, xefg_swapchain_logging_level_t level, void* userData);

  public:
    // IFGFeature
    const char* Name() override final;
    feature_version Version() override final;

    void StopAndDestroyContext(bool destroy, bool shutDown, bool useMutex) override final;

    // IFGFeature_Dx12
    bool CreateSwapchain(IDXGIFactory* factory, ID3D12CommandQueue* cmdQueue, DXGI_SWAP_CHAIN_DESC* desc,
                         IDXGISwapChain** swapChain) override final;
    bool CreateSwapchain1(IDXGIFactory* factory, ID3D12CommandQueue* cmdQueue, HWND hwnd, DXGI_SWAP_CHAIN_DESC1* desc,
                          DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGISwapChain1** swapChain) override final;
    bool ReleaseSwapchain(HWND hwnd) override final;

    void CreateContext(ID3D12Device* device, int featureFlags, uint32_t width, uint32_t height) override final;

    bool Dispatch(ID3D12GraphicsCommandList* cmdList, bool useHudless, double frameTime) override final;

    void* FrameGenerationContext() override final;
    void* SwapchainContext() override final;

    XeFG_Dx12() : IFGFeature_Dx12(), IFGFeature()
    {
        if (XeFGProxy::Module() == nullptr)
            XeFGProxy::InitXeFG();
    }
};
