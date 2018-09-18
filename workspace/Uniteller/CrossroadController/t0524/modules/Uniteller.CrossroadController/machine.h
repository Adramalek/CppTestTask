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


namespace KG1Protocol = Uniteller::Framework::Kernel::Protocol::G1;
namespace MLG1Protocol = Uniteller::MainLogic::Protocol::G1;
namespace DCG1Protocol = Uniteller::DeviceController::Protocol::G1;
namespace CCG1Protocol = Uniteller::CrossroadController::Protocol::G1;

namespace Uniteller
{
	namespace CrossroadController
	{
		/// <summary>
		/// Главный класс модуля
		/// </summary>
		class Machine : public SystemObject<Machine, ISystemObject>
		{
		public:
			// Карта обработчиков событий конечного автомата
			BEGIN_HANDLERS_MAP()
				REGISTER_HANDLER("StartState", "Pause", KG1Protocol::Codes::Start, &Machine::KernelStartHandler);
				REGISTER_HANDLER("Pause", "Pause", MLG1Protocol::Codes::Start, &Machine::MainLogicStartHandler);
				REGISTER_HANDLER("Pause", "TurningLightOn", CCG1Protocol::Codes::SetNextLight, &Machine::SetNextLightHandler);
				REGISTER_HANDLER("TurningLightOn", "Pause", DCG1Protocol::Codes::Fail, &Machine::FailHandler);
				REGISTER_HANDLER("TurningLightOn", "Pause", KG1Protocol::Codes::TimeOut, &Machine::TimeOutHandler);
				REGISTER_HANDLER("TurningLightOn", "TurningLightOn", DCG1Protocol::Codes::Success, &Machine::SuccessHandler);
				REGISTER_HANDLER("TurningLightOn", "RedLight", CCG1Protocol::Codes::CountDownRed, &Machine::CountDownRedHandler);
				REGISTER_HANDLER("TurningLightOn", "YellowLight", CCG1Protocol::Codes::CountDownYellow, &Machine::CountDownYellowHandler);
				REGISTER_HANDLER("TurningLightOn", "GreenLight", CCG1Protocol::Codes::CountDownGreen, &Machine::CountDownGreenHandler);
				REGISTER_HANDLER("RedLight", "TurningLightOn", CCG1Protocol::Codes::SetNextLight, &Machine::SetNextLightHandler);
				REGISTER_HANDLER("YellowLight", "TurningLightOn", CCG1Protocol::Codes::SetNextLight, &Machine::SetNextLightHandler);
				REGISTER_HANDLER("GreenLight", "TurningLightOn", CCG1Protocol::Codes::SetNextLight, &Machine::SetNextLightHandler);
				REGISTER_HANDLER("Pause", "End", KG1Protocol::Codes::Stop, &Machine::StopHandler);
				REGISTER_HANDLER("Pause", "End", MLG1Protocol::Codes::Shutdown, &Machine::ShutdownHandler);
				REGISTER_HANDLER("TurningLightOn", "End", KG1Protocol::Codes::Stop, &Machine::StopHandler);
				REGISTER_HANDLER("RedLight", "End", KG1Protocol::Codes::Stop, &Machine::StopHandler);
				REGISTER_HANDLER("YellowLight", "End", KG1Protocol::Codes::Stop, &Machine::StopHandler);
				REGISTER_HANDLER("GreenLight", "End", KG1Protocol::Codes::Stop, &Machine::StopHandler);
			END_HANDLERS_MAP()
		public:
			Machine(IKernelApi * api) : SystemObject<Machine, ISystemObject>("Uniteller.CrossroadController", api)
			{}

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
			DECLARE_HANDLER(KernelStartHandler, KG1Protocol::Start);
			DECLARE_HANDLER(StopHandler, KG1Protocol::Stop);
			DECLARE_HANDLER(ShutdownHandler, MLG1Protocol::Shutdown);
			DECLARE_HANDLER(MainLogicStartHandler, MLG1Protocol::Start);
			DECLARE_HANDLER(FailHandler, DCG1Protocol::Fail);
			DECLARE_HANDLER(SuccessHandler, DCG1Protocol::Success);
			DECLARE_HANDLER(TimeOutHandler, KG1Protocol::TimeOut);
			DECLARE_HANDLER(SetNextLightHandler, CCG1Protocol::SetNextLight);
			DECLARE_HANDLER(CountDownRedHandler, CCG1Protocol::CountDownRed);
			DECLARE_HANDLER(CountDownYellowHandler, CCG1Protocol::CountDownYellow);
			DECLARE_HANDLER(CountDownGreenHandler, CCG1Protocol::CountDownGreen);

		private: // Закрытые данные
			static const size_t _colorCycleSize = 3;
			/// <summary>
			/// Colors array.
			/// </summary>
			DCG1Protocol::ColorType _colorCycle[_colorCycleSize];
			/// <summary>
			/// Pointer to a current color in cycle.
			/// </summary>
			const DCG1Protocol::ColorType* _currentColor;
			/// <summary>
			/// Indicates a direction. [true] means that a pointer to a current color shoukd be incremented,
			/// while [false] -- to be decremented.
			/// </summary>
			bool _increment;
			bool _turnignOnLight;

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
			void AdvanceCycle();
		};

	} // пространство имен ComponentBuilder
} // пространство имен Uniteller
