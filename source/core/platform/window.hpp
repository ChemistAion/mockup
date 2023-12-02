#pragma once

namespace Mockup::Core
{
	constexpr decltype(auto) cWindowClass_Name = _T("mockup::WindowClass");
	constexpr decltype(auto) cWindowTitle_Name = _T("mockup::Window");

	class Window final : public Singleton<Window>
	{
	public:
		using Pump = std::function<LRESULT(HWND handle, UINT message, WPARAM w_param, LPARAM l_param)>;
	private:
		HWND handle_ = NULL;
		DWORD error_ = ERROR_SUCCESS;

		ATOM atom_ = 0;

		std::list<Pump> pool_pump_;

		static LRESULT CALLBACK WindowProcedure(HWND handle, UINT message, WPARAM w_param, LPARAM l_param);

		friend Singleton<Window>;
		Window();

		~Window();
	public:
		HWND GetHandle() const noexcept
		{
			return handle_;
		}

		auto GetWindowWidth() const noexcept
		{
			RECT rect;
			::GetWindowRect(handle_, &rect);

			return rect.right - rect.left;
		}

		auto GetWindowHeight() const noexcept
		{
			RECT rect;
			::GetWindowRect(handle_, &rect);

			return rect.bottom - rect.top;
		}

		auto GetClientWidth() const noexcept
		{
			RECT rect;
			::GetClientRect(handle_, &rect);

			return rect.right - rect.left;
		}

		auto GetClientHeight() const noexcept
		{
			RECT rect;
			::GetClientRect(handle_, &rect);

			return rect.bottom - rect.top;
		}

		////////////////////////////////////////////////////////////////////////////////

		void Create();

		void RegisterPump(Pump&& pump)
		{
			//TODO: bind...
			pool_pump_.push_back(std::move(pump));
		}
	};
};