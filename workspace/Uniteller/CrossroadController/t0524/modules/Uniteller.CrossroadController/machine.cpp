#include "machine.h"
#include "kernel/smartqipointer.h"
#include "kernel/utils.h"
#include "kernel/messagefilter.h"

#include "Uniteller.Framework.Kernel.Host.h"
//#include "CrossroadController.h"

#include <thread>

using namespace std;

namespace Uniteller
{
	namespace CrossroadController
	{

		Uniteller::DeviceController::Protocol::G1::ColorType ConvertColorType(const Protocol::G1::ColorType& color)
		{
			switch (color)
			{
			case Protocol::G1::ColorType::Red: return Uniteller::DeviceController::Protocol::G1::ColorType::Red;
			case Protocol::G1::ColorType::Yellow: return Uniteller::DeviceController::Protocol::G1::ColorType::Yellow;
			case Protocol::G1::ColorType::Green: return Uniteller::DeviceController::Protocol::G1::ColorType::Green;
			default: throw  KernelException("No way. Never happens. Good luck to throw this exception.", color);
			}
		}

#pragma region Timer implementation

		Timer::Timer(int span) : _span(span)
		{}

		Timer::Timer(Timer&& other) :
			_span(std::move(other._span)),
			_callback(std::move(other._callback)),
			_cancelationToken(std::move(other._cancelationToken)),
			_completionFlag(std::move(other._completionFlag))
		{}

		Timer& Timer::operator=(Timer&& other)
		{
			if (this != &other)
			{
				this->_span = std::move(other._span);
				this->_callback = std::move(other._callback);
				this->_cancelationToken = std::move(other._cancelationToken);
				this->_completionFlag = std::move(other._completionFlag);
			}
			return *this;
		}

		void Timer::operator()(uint16_t time)
		{
			this->_cancelationToken = std::promise<void>();
			auto sptrPromise = std::make_shared<std::promise<void>>();
			auto sptrCancelationToken = std::make_shared<std::future<void>>(this->_cancelationToken.get_future());
			this->_completionFlag = sptrPromise->get_future();
			std::thread([=](){
				std::chrono::milliseconds delay(time * 1000);
				std::chrono::high_resolution_clock::time_point start(std::chrono::high_resolution_clock::now());
				bool is_time_left = true;
				while ((sptrCancelationToken->wait_for(_span) == std::future_status::timeout) &&
					(is_time_left = (std::chrono::high_resolution_clock::now() - start <= delay)));
				if (_callback && !is_time_left)
					_callback();
				sptrPromise->set_value();
			}).detach();
		}

		void Timer::SetCallback(const Timer::Callback& callback)
		{
			_callback = callback;
		}

		void Timer::SetCallback(Timer::Callback&& callback)
		{
			_callback = callback;
		}

		bool Timer::IsAlive()
		{
			return this->_completionFlag.valid() && this->_completionFlag.wait_for(std::chrono::microseconds(0)) != std::future_status::ready;
		}

		bool Timer::Stop()
		{
			if (!this->_completionFlag.valid()) return false;
			_cancelationToken.set_value();
			_completionFlag.get();
			return true;
		}

#pragma endregion
#pragma region Machine implementation

		Machine::~Machine()
		{
			Clear();
		}

		void Machine::Reset()
		{
			timer.IsAlive() && timer.Stop();
			_increment = true;
			_currentColor = _colorCycle;
		}

		void Machine::Clear()
		{
			Reset();
		}

		void Machine::Init()
		{
			timer.SetCallback([this](){ m_Protocol.RaiseSetNextLight(); });
			Reset();
		}

#pragma endregion
#pragma region Обработчики сообщений
        void Machine::KernelStartHandler(const Framework::Kernel::Protocol::G1::Start & message)
        {
			Init();
        }

		void Machine::MainLogicStartHandler(const Uniteller::MainLogic::Protocol::G1::Start& message)
		{
			m_LedDriver.SetLight(ConvertColorType(*_currentColor));
		}
		
		void Machine::SetNextLightHandler(const Protocol::G1::SetNextLight& message)
		{
			m_LedDriver.SetLight(ConvertColorType(*_currentColor));
		}

		void Machine::FailHandler(const Uniteller::DeviceController::Protocol::G1::Fail& message)
		{
			Reset();
			m_ControlLogic.ProblemDetected();
		}

		void Machine::TimeOutHandler(const Framework::Kernel::Protocol::G1::TimeOut& message)
		{
			Reset();
			m_ControlLogic.ProblemDetected();
		}

		void Machine::StopHandler(const Framework::Kernel::Protocol::G1::Stop& message)
		{
			Reset();
		}

		void Machine::ShutdownHandler(const Uniteller::MainLogic::Protocol::G1::Shutdown& message)
		{
			Reset();
		}

		void Machine::SuccessHandler(const Uniteller::DeviceController::Protocol::G1::Success& message)
		{
			timer(static_cast<int>(*_currentColor));
			if (_increment && ++_currentColor == _colorCycle + _colorCycleSize)
			{
				_increment = !_increment;
				--_currentColor;
			}
			else if (!_increment && --_currentColor == _colorCycle)
			{
				this->_increment = !_increment;
			}
		}

#pragma endregion             


	} // пространство имен ComponentBuilder

} // пространство имен Uniteller

