#pragma once

#include "kernel/systemobject.h"
#include "kernel/xregistrykey.h"

// Протоколы
#include "Uniteller.Framework.Kernel.h"
#include "Uniteller.Framework.Kernel.Host.h"
#include "Uniteller.CrossroadController.h"
#include "Uniteller.MainLogic.h"
#include "Uniteller.DeviceController.h"

// some other includes
#include <future>
#include <thread>
#include <chrono>
#include <map>
#include <functional>



using namespace Uniteller::Framework::Kernel;

namespace Uniteller
{
	namespace CrossroadController
	{
		/// <summary>
		/// Converting ColorType of CrossroadController protocol to ColorType of DeviceController protocol.
		/// </summary>
		Uniteller::DeviceController::Protocol::G1::ColorType ConvertColorType(const Protocol::G1::ColorType& color);

		/// <summary>
		/// Simple countdown timer. It counts down time on a separate thread and invokes a callback function (if it has been set) when it's done.
		/// Also it is possible to prematurely stop the timer.
		/// </summary>
		class Timer
		{
		public:
			using Callback = std::function<void(void)>;

			// forbiding copy
			Timer(const Timer&) = delete;
			Timer& operator=(const Timer&) = delete;
			// default destructor
			~Timer() = default;
			/// <summary>
			/// Constructs a timer with a 
			/// </summary>
			explicit Timer(int);
			// allowing move
			Timer(Timer&&);
			Timer& operator=(Timer&&);
			/// <summary>
			/// Sets a new callback. Change will take place when timer starts next time.
			/// </summary>
			void SetCallback(const Callback& callback);
			void SetCallback(Callback&& callback);
			/// <summary>
			/// Check if timer's thread is alive. Returns true if so owerthise false.
			/// </summary>
			bool IsAlive();
			/// <summary>
			/// Prematurely stops timer's thread. Calling it on a dead thread will couse no effect.
			/// </summary>
			bool Stop();
			/// <summary>
			/// Starts a timer. Counts downs time seconds.
			/// </summary>
			/// <param name="time">Indicates how long countdown will last.</param>
			void operator()(uint16_t time);

		private:
			/// <summary>
			/// Via this flag it's become possible to get know whenever thread is alive or not.
			/// </summary>
			std::future<void> _completionFlag;
			/// <summary>
			/// Cancelation token. When set_value() is called, it iterrupts a thread.
			/// </summary>
			std::promise<void> _cancelationToken;
			/// <summary>
			/// Time span between checking if timer was prematurely stopped. Also indicates time step.
			/// </summary>
			std::chrono::milliseconds _span;
			/// <summary>
			/// Callback function to be invoked when timer stopped.
			/// </summary>
			Callback _callback;
		};

		/// <summary>
		/// Главный класс модуля
		/// </summary>
		class Machine : public SystemObject<Machine, ISystemObject>
		{
		public:
			// Карта обработчиков событий конечного автомата
			BEGIN_HANDLERS_MAP()
				REGISTER_HANDLER("StartState", "Pause", Framework::Kernel::Protocol::G1::Codes::Start, &Machine::KernelStartHandler);
				REGISTER_HANDLER("Pause", "TurningLightOn", Uniteller::MainLogic::Protocol::G1::Codes::Start, &Machine::MainLogicStartHandler);
				REGISTER_HANDLER("TurningLightOn", "LightTurnedOn", Uniteller::DeviceController::Protocol::G1::Codes::Success, &Machine::SuccessHandler);
				REGISTER_HANDLER("TurningLightOn", "Pause", Uniteller::DeviceController::Protocol::G1::Codes::Fail, &Machine::FailHandler);
				REGISTER_HANDLER("TurningLightOn", "Pause", Framework::Kernel::Protocol::G1::Codes::TimeOut, &Machine::TimeOutHandler);
				REGISTER_HANDLER("LightTurnedOn", "TurningLightOn", Uniteller::CrossroadController::Protocol::G1::Codes::SetNextLight, &Machine::SetNextLightHandler);
				REGISTER_HANDLER("Pause", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
				REGISTER_HANDLER("Pause", "End", Uniteller::MainLogic::Protocol::G1::Codes::Shutdown, &Machine::ShutdownHandler);
				REGISTER_HANDLER("TurningLightOn", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
				REGISTER_HANDLER("TurningLightOn", "End", Uniteller::MainLogic::Protocol::G1::Codes::Shutdown, &Machine::ShutdownHandler);
				REGISTER_HANDLER("LightTurnedOn", "End", Framework::Kernel::Protocol::G1::Codes::Stop, &Machine::StopHandler);
				REGISTER_HANDLER("LightTurnedOn", "End", Uniteller::MainLogic::Protocol::G1::Codes::Shutdown, &Machine::ShutdownHandler);
			END_HANDLERS_MAP()
		public:
			Machine(IKernelApi * api) : SystemObject<Machine, ISystemObject>("Uniteller.CrossroadController", api),
				timer(Timer(100))
			{
				_colorCycle[0] = Protocol::G1::ColorType::Red;
				_colorCycle[1] = Protocol::G1::ColorType::Yellow;
				_colorCycle[2] = Protocol::G1::ColorType::Green;
			}

			~Machine();
		private: // Используемые протоколы
			USE_PROTOCOL(Uniteller::MainLogic, 1, ControlLogic);
			USE_PROTOCOL(Uniteller::DeviceController, 1, LedDriver);

			IMPLEMENT_PROTOCOL(Uniteller::CrossroadController, 1, Protocol);

			/// <summary>
			/// Карта точек соединения (по каким адресам располагаются те или иные протоколы)
			/// </summary>         
			BEGIN_ENDPOINTS()
				PROTOCOL_ENDPOINT(Protocol, GetUnicalId());
				PROTOCOL_ENDPOINT(ControlLogic, "ControlLogic");
				PROTOCOL_ENDPOINT(LedDriver, "LedDriver"); 
			END_ENDPOINTS()

		protected: // Обработчики событий автомата
			//void MachineInitErrorHandlerSystem(IMessage * message);
			DECLARE_HANDLER(KernelStartHandler, Framework::Kernel::Protocol::G1::Start);
			DECLARE_HANDLER(StopHandler, Framework::Kernel::Protocol::G1::Stop);
			DECLARE_HANDLER(ShutdownHandler, Uniteller::MainLogic::Protocol::G1::Shutdown);
			DECLARE_HANDLER(MainLogicStartHandler, Uniteller::MainLogic::Protocol::G1::Start);
			DECLARE_HANDLER(FailHandler, Uniteller::DeviceController::Protocol::G1::Fail);
			DECLARE_HANDLER(TimeOutHandler, Framework::Kernel::Protocol::G1::TimeOut);
			DECLARE_HANDLER(SetNextLightHandler, Uniteller::CrossroadController::Protocol::G1::SetNextLight);
			DECLARE_HANDLER(SuccessHandler, Uniteller::DeviceController::Protocol::G1::Success);

		private: // Закрытые данные
			static const size_t _colorCycleSize = 3;
			/// <summary>
			/// Mapping of color to time duration.
			/// </summary>
			Protocol::G1::ColorType _colorCycle[_colorCycleSize];
			/// <summary>
			/// Pointer to a current color in cycle.
			/// </summary>
			const Protocol::G1::ColorType* _currentColor;
			/// <summary>
			/// Indicates a direction. [true] means that a pointer to a current color shoukd be incremented,
			/// while [false] -- to be decremented.
			/// </summary>
			bool _increment;
			/// <summary>
			/// Timer counts out a time the color signal should be turned on before switch to th next one.
			/// </summary>
			Timer timer;

		private: // Закрытые методы 
			/// <summary>
			/// Очищает ресурсы
			/// </summary>
			void Clear();
			/// <summary>
			/// Initialize resources
			/// </summary>
			void Init();
			/// <summary>
			/// Resets data and timer to initial state.
			/// </summary>
			void Reset();
		};

	} // пространство имен ComponentBuilder
} // пространство имен Uniteller
