#ifndef ROBOCALC_STATEMACHINES_STM0_H_
#define ROBOCALC_STATEMACHINES_STM0_H_

#include "RoboCalcAPI/StateMachine.h"

#ifndef ROBOCALC_THREAD_SAFE
#define THREAD_SAFE_ONLY(x)
#else
#include <mutex>
#define THREAD_SAFE_ONLY(x) x
#endif

#include "UR5WithCamera.h"
#include "RoboCalcAPI/Timer.h"
#include "Functions.h"
#include "DataTypes.h"
#include <assert.h>
#include <set>

using namespace robocalc;
using namespace robocalc::functions;

template<typename ControllerType>
class stm0_StateMachine : public StateMachine<UR5WithCamera, ControllerType, stm0_StateMachine<ControllerType>>
{
	public:
		ControllerType& controller;
	public:
		class S0_State_t : public robocalc::State<ControllerType>
		{
			public:
				explicit S0_State_t(ControllerType& _controller, stm0_StateMachine<ControllerType>* topLevel) 
					: robocalc::State<ControllerType>(_controller)
				{
				}
				
				S0_State_t() = delete;
			
				void enter() override
				{
				}
				
				void exit() override
				{
				}
				
				void during() override
				{
				}
		};
		
		S0_State_t s0_State;
		
		enum PossibleStates
		{
			s_s0,
			j_i0
		} currentState = j_i0; 

	public:
		stm0_StateMachine(UR5WithCamera& _platform, ControllerType& _controller, stm0_StateMachine<ControllerType>* topLevel = nullptr) 
			: StateMachine<UR5WithCamera, ControllerType, stm0_StateMachine<ControllerType>>(_platform, _controller, topLevel), controller{_controller}
			,
			s0_State{_controller, this}
			{};
		stm0_StateMachine() = delete;
		~stm0_StateMachine() = default;
	
	
	
		void execute() override
		{
			while(tryTransitions());
		
			switch(currentState)
			{
			case s_s0:
			{
				s0_State.during();
				break;
			}
				default:
					break;
			}
		}
	
		bool tryTransitions() override
		{
			switch(currentState)
			{
				case s_s0:
				{

					break;
				}
				case j_i0:
				{
					
					;
					currentState = s_s0;
					s0_State.enter();
					return true;
				}
				default:
					break;
			}
				
			return false;
		}
};
	
#endif
