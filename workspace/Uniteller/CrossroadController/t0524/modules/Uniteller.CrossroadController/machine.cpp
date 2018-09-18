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
		
#pragma region Machine implementation

		Machine::~Machine()
		{
			Clear();
		}

		void Machine::Reset()
		{
			_currentColor = _colorCycle;
			_increment = true;
			_turnignOnLight = false;
		}

		void Machine::Clear()
		{
			Reset();
		}

		void Machine::Init()
		{
			_colorCycle[0] = DCG1Protocol::ColorType::Red;
			_colorCycle[1] = DCG1Protocol::ColorType::Yellow;
			_colorCycle[2] = DCG1Protocol::ColorType::Green;
			Reset();
		}

		void Machine::AdvanceCycle()
		{
			_turnignOnLight = false;
			if (_increment && ++_currentColor == _colorCycle + _colorCycleSize)
			{
				--_currentColor;
				_increment = !_increment;
			}
			else if (!_increment && _currentColor-- == _colorCycle)
			{
				_currentColor = _colorCycle;
				_increment = !_increment;
			}
		}

#pragma endregion
#pragma region Обработчики сообщений
        void Machine::KernelStartHandler(const KG1Protocol::Start&)
        {
			Init();
        }

		void Machine::MainLogicStartHandler(const MLG1Protocol::Start&)
		{
			m_Protocol.RaiseSetNextLight();
		}
		
		void Machine::SetNextLightHandler(const CCG1Protocol::SetNextLight&)
		{
			_turnignOnLight = true;
			m_LedDriver.SetLight(*_currentColor);
		}

		void Machine::FailHandler(const DCG1Protocol::Fail&)
		{
			Reset();
			m_ControlLogic.ProblemDetected();
		}

		void Machine::TimeOutHandler(const KG1Protocol::TimeOut&)
		{
			if (_turnignOnLight)
			{
				Reset();
				m_ControlLogic.ProblemDetected();
			}
			else
			{
				m_Protocol.RaiseSetNextLight();
			}
		}

		void Machine::StopHandler(const KG1Protocol::Stop&)
		{
			Reset();
		}

		void Machine::ShutdownHandler(const MLG1Protocol::Shutdown&)
		{
			Reset();
		}

		void Machine::SuccessHandler(const DCG1Protocol::Success&)
		{
			switch (*_currentColor)
			{
			case DCG1Protocol::ColorType::Red:
				m_Protocol.RaiseCountDownRed();
				break;
			case DCG1Protocol::ColorType::Yellow:
				m_Protocol.RaiseCountDownYellow();
				break;
			case DCG1Protocol::ColorType::Green:
				m_Protocol.RaiseCountDownGreen();
				break;
			default:
				break;
			}
		}

		void Machine::CountDownRedHandler(const CCG1Protocol::CountDownRed&)
		{
			AdvanceCycle();
		}

		void Machine::CountDownYellowHandler(const CCG1Protocol::CountDownYellow&)
		{
			AdvanceCycle();
		}

		void Machine::CountDownGreenHandler(const CCG1Protocol::CountDownGreen&)
		{
			AdvanceCycle();
		}

#pragma endregion             


	} // пространство имен ComponentBuilder

} // пространство имен Uniteller

