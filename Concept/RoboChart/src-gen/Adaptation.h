#ifndef ROBOCALC_CONTROLLERS_ADAPTATION_H_
#define ROBOCALC_CONTROLLERS_ADAPTATION_H_

#include "UR5WithCamera.h"
#include "RoboCalcAPI/Controller.h"
#include "DataTypes.h"

#include "Adaptation_Monitor.h"
#include "Adaptation_Analyse.h"
#include "Adaptation_Legitimate.h"
#include "Adaptation_Knowledge.h"
#include "Adaptation_Plan.h"
#include "Adaptation_Execute.h"

class Adaptation: public robocalc::Controller 
{
public:
	Adaptation(UR5WithCamera& _platform) : platform(&_platform){};
	Adaptation() : platform(nullptr){};
	
	~Adaptation() = default;
	
	void Execute()
	{
		adaptation_Monitor.execute();
		adaptation_Analyse.execute();
		adaptation_Legitimate.execute();
		adaptation_Knowledge.execute();
		adaptation_Plan.execute();
		adaptation_Execute.execute();
	}
	
	struct Channels
	{
		Adaptation& instance;
		Channels(Adaptation& _instance) : instance(_instance) {}
		
		EventBuffer* tryEmitGet_newConfidences(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_newConfidences_Plan(args))
				instance.adaptation_Knowledge.get_newConfidences_Plan_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_newConfidences_Plan_in;
		}
		
		EventBuffer* tryEmitAmbientLight(void* sender, std::tuple<double> args)
		{
			if(instance.adaptation_Monitor.canReceiveAmbientLight(args))
				instance.adaptation_Monitor.ambientLight_in.trigger(sender, args);
				
			return &instance.adaptation_Monitor.ambientLight_in;
		}
		
		EventBuffer* tryEmitGet_newModel(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_newModel_Execute(args))
				instance.adaptation_Knowledge.get_newModel_Execute_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_newModel_Execute_in;
		}
		
		EventBuffer* tryEmitGet_imagesWithPoorLight(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_imagesWithPoorLight_Plan(args))
				instance.adaptation_Knowledge.get_imagesWithPoorLight_Plan_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_imagesWithPoorLight_Plan_in;
		}
		
		EventBuffer* tryEmitGet_newModel(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_newModel_Legitimate(args))
				instance.adaptation_Knowledge.get_newModel_Legitimate_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_newModel_Legitimate_in;
		}
		
		EventBuffer* tryEmitProcessedData(void* sender, std::tuple<std::tuple<ScrewImageData, double, unsigned int>> args)
		{
			if(instance.adaptation_Analyse.canReceiveProcessedData(args))
				instance.adaptation_Analyse.processedData_in.trigger(sender, args);
				
			return &instance.adaptation_Analyse.processedData_in;
		}
		
		EventBuffer* tryEmitImagesWithLight_Analyse(void* sender, std::tuple<std::vector<std::tuple<ScrewImageData, double, unsigned int>>> args)
		{
			if(instance.adaptation_Analyse.canReceiveImagesWithLight(args))
				instance.adaptation_Analyse.imagesWithLight_in.trigger(sender, args);
				
			return &instance.adaptation_Analyse.imagesWithLight_in;
		}
		
		EventBuffer* tryEmitGet_imagesWithLight(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_imagesWithLight_Plan(args))
				instance.adaptation_Knowledge.get_imagesWithLight_Plan_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_imagesWithLight_Plan_in;
		}
		
		EventBuffer* tryEmitNewModel_Execute(void* sender, std::tuple<unsigned int> args)
		{
			if(instance.adaptation_Execute.canReceiveNewModel(args))
				instance.adaptation_Execute.newModel_in.trigger(sender, args);
				
			return &instance.adaptation_Execute.newModel_in;
		}
		
		EventBuffer* tryEmitGet_newModel(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_newModel(args))
				instance.adaptation_Knowledge.get_newModel_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_newModel_in;
		}
		
		EventBuffer* tryEmitPlanAccepted(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Execute.canReceiveExecutePlan(args))
				instance.adaptation_Execute.executePlan_in.trigger(sender, args);
				
			return &instance.adaptation_Execute.executePlan_in;
		}
		
		EventBuffer* tryEmitImagesWithPoorLight(void* sender, std::tuple<std::vector<unsigned int>> args)
		{
			if(instance.adaptation_Analyse.canReceiveImagesWithPoorLight(args))
				instance.adaptation_Analyse.imagesWithPoorLight_in.trigger(sender, args);
				
			return &instance.adaptation_Analyse.imagesWithPoorLight_in;
		}
		
		EventBuffer* tryEmitSet_newModel(void* sender, std::tuple<unsigned int> args)
		{
			if(instance.adaptation_Knowledge.canReceiveSet_newModel(args))
				instance.adaptation_Knowledge.set_newModel_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.set_newModel_in;
		}
		
		EventBuffer* tryEmitImagesWithLight(void* sender, std::tuple<std::vector<std::tuple<ScrewImageData, double, unsigned int>>> args)
		{
			if(instance.adaptation_Monitor.canReceiveImagesWithLight(args))
				instance.adaptation_Monitor.imagesWithLight_in.trigger(sender, args);
				
			return &instance.adaptation_Monitor.imagesWithLight_in;
		}
		
		EventBuffer* tryEmitGet_imagesWithPoorLight(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_imagesWithPoorLight(args))
				instance.adaptation_Knowledge.get_imagesWithPoorLight_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_imagesWithPoorLight_in;
		}
		
		EventBuffer* tryEmitAnomalyFound(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Plan.canReceiveRequestPlan(args))
				instance.adaptation_Plan.requestPlan_in.trigger(sender, args);
				
			return &instance.adaptation_Plan.requestPlan_in;
		}
		
		EventBuffer* tryEmitPlanningCompleted(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Legitimate.canReceiveVerifyPlan(args))
				instance.adaptation_Legitimate.verifyPlan_in.trigger(sender, args);
				
			return &instance.adaptation_Legitimate.verifyPlan_in;
		}
		
		EventBuffer* tryEmitPlanRejected(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Plan.canReceivePlanRejected(args))
				instance.adaptation_Plan.planRejected_in.trigger(sender, args);
				
			return &instance.adaptation_Plan.planRejected_in;
		}
		
		EventBuffer* tryEmitImagesWithLight_Legitimate(void* sender, std::tuple<std::vector<std::tuple<ScrewImageData, double, unsigned int>>> args)
		{
			if(instance.adaptation_Legitimate.canReceiveImagesWithLight(args))
				instance.adaptation_Legitimate.imagesWithLight_in.trigger(sender, args);
				
			return &instance.adaptation_Legitimate.imagesWithLight_in;
		}
		
		EventBuffer* tryEmitGet_imagesWithPoorLight(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_imagesWithPoorLight_Legitimate(args))
				instance.adaptation_Knowledge.get_imagesWithPoorLight_Legitimate_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_imagesWithPoorLight_Legitimate_in;
		}
		
		EventBuffer* tryEmitGet_imagesWithLight(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_imagesWithLight_Legitimate(args))
				instance.adaptation_Knowledge.get_imagesWithLight_Legitimate_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_imagesWithLight_Legitimate_in;
		}
		
		EventBuffer* tryEmitCurrentModel(void* sender, std::tuple<unsigned int> args)
		{
			if(instance.adaptation_Monitor.canReceiveCurrentModel(args))
				instance.adaptation_Monitor.currentModel_in.trigger(sender, args);
				
			return &instance.adaptation_Monitor.currentModel_in;
		}
		
		EventBuffer* tryEmitImageTaken(void* sender, std::tuple<ScrewImageData> args)
		{
			if(instance.adaptation_Monitor.canReceiveImageTaken(args))
				instance.adaptation_Monitor.imageTaken_in.trigger(sender, args);
				
			return &instance.adaptation_Monitor.imageTaken_in;
		}
		
		EventBuffer* tryEmitSet_newConfidences(void* sender, std::tuple<std::vector<std::vector<EstimatedPosition>>> args)
		{
			if(instance.adaptation_Knowledge.canReceiveSet_newConfidences(args))
				instance.adaptation_Knowledge.set_newConfidences_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.set_newConfidences_in;
		}
		
		EventBuffer* tryEmitSet_imagesWithLight(void* sender, std::tuple<std::vector<std::tuple<ScrewImageData, double, unsigned int>>> args)
		{
			if(instance.adaptation_Knowledge.canReceiveSet_imagesWithLight(args))
				instance.adaptation_Knowledge.set_imagesWithLight_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.set_imagesWithLight_in;
		}
		
		EventBuffer* tryEmitSet_imagesWithPoorLight(void* sender, std::tuple<std::vector<unsigned int>> args)
		{
			if(instance.adaptation_Knowledge.canReceiveSet_imagesWithPoorLight(args))
				instance.adaptation_Knowledge.set_imagesWithPoorLight_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.set_imagesWithPoorLight_in;
		}
		
		EventBuffer* tryEmitNewConfidences(void* sender, std::tuple<std::vector<std::vector<EstimatedPosition>>> args)
		{
			if(instance.adaptation_Legitimate.canReceiveNewConfidences(args))
				instance.adaptation_Legitimate.newConfidences_in.trigger(sender, args);
				
			return &instance.adaptation_Legitimate.newConfidences_in;
		}
		
		EventBuffer* tryEmitImagesWithPoorLight_Plan(void* sender, std::tuple<std::vector<unsigned int>> args)
		{
			if(instance.adaptation_Plan.canReceiveImagesWithPoorLight(args))
				instance.adaptation_Plan.imagesWithPoorLight_in.trigger(sender, args);
				
			return &instance.adaptation_Plan.imagesWithPoorLight_in;
		}
		
		EventBuffer* tryEmitSwitchModel(void* sender, std::tuple<unsigned int> args)
		{
			switchModel_in.trigger(sender, args);
			return &switchModel_in;
		}
		
		EventBuffer* tryEmitGet_imagesWithLight(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_imagesWithLight_Analyse(args))
				instance.adaptation_Knowledge.get_imagesWithLight_Analyse_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_imagesWithLight_Analyse_in;
		}
		
		EventBuffer* tryEmitNewModel_Legitimate(void* sender, std::tuple<unsigned int> args)
		{
			if(instance.adaptation_Legitimate.canReceiveNewModel(args))
				instance.adaptation_Legitimate.newModel_in.trigger(sender, args);
				
			return &instance.adaptation_Legitimate.newModel_in;
		}
		
		EventBuffer* tryEmitImagesWithPoorLight_Legitimate(void* sender, std::tuple<std::vector<unsigned int>> args)
		{
			if(instance.adaptation_Legitimate.canReceiveImagesWithPoorLight(args))
				instance.adaptation_Legitimate.imagesWithPoorLight_in.trigger(sender, args);
				
			return &instance.adaptation_Legitimate.imagesWithPoorLight_in;
		}
		
		EventBuffer* tryEmitGet_newConfidences(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_newConfidences(args))
				instance.adaptation_Knowledge.get_newConfidences_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_newConfidences_in;
		}
		
		EventBuffer* tryEmitAdaptationCompleted(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Analyse.canReceiveAdaptationCompleted(args))
				instance.adaptation_Analyse.adaptationCompleted_in.trigger(sender, args);
				
			return &instance.adaptation_Analyse.adaptationCompleted_in;
		}
		
		EventBuffer* tryEmitNewConfidences_Plan(void* sender, std::tuple<std::vector<std::vector<EstimatedPosition>>> args)
		{
			if(instance.adaptation_Plan.canReceiveNewConfidences(args))
				instance.adaptation_Plan.newConfidences_in.trigger(sender, args);
				
			return &instance.adaptation_Plan.newConfidences_in;
		}
		
		EventBuffer* tryEmitGet_imagesWithLight(void* sender, std::tuple<> args)
		{
			if(instance.adaptation_Knowledge.canReceiveGet_imagesWithLight(args))
				instance.adaptation_Knowledge.get_imagesWithLight_in.trigger(sender, args);
				
			return &instance.adaptation_Knowledge.get_imagesWithLight_in;
		}
		
		EventBuffer* tryEmitNewModel(void* sender, std::tuple<unsigned int> args)
		{
			if(instance.adaptation_Plan.canReceiveNewModel(args))
				instance.adaptation_Plan.newModel_in.trigger(sender, args);
				
			return &instance.adaptation_Plan.newModel_in;
		}
		
		EventBuffer* tryEmitImagesWithLight_Plan(void* sender, std::tuple<std::vector<std::tuple<ScrewImageData, double, unsigned int>>> args)
		{
			if(instance.adaptation_Plan.canReceiveImagesWithLight(args))
				instance.adaptation_Plan.imagesWithLight_in.trigger(sender, args);
				
			return &instance.adaptation_Plan.imagesWithLight_in;
		}
		
		struct SwitchModel_t : public EventBuffer
		{
			THREAD_SAFE_ONLY(std::mutex _mutex;)
			std::tuple<unsigned int> _args;
			void* _sender = nullptr;
			void* getSender() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				return _sender;
			}
			
			void reset() override
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_sender = nullptr;
			}
			
			void trigger(void* sender, std::tuple<unsigned int> args)
			{
				THREAD_SAFE_ONLY(std::lock_guard<std::mutex> lock{_mutex};)
				_args = args;
				_sender = sender;
			}
		} switchModel_in;
	};
	
	Channels channels{*this};
	
	UR5WithCamera* platform;
	Adaptation_Monitor_StateMachine<Adaptation> adaptation_Monitor{*platform, *this, &adaptation_Monitor};
	Adaptation_Analyse_StateMachine<Adaptation> adaptation_Analyse{*platform, *this, &adaptation_Analyse};
	Adaptation_Legitimate_StateMachine<Adaptation> adaptation_Legitimate{*platform, *this, &adaptation_Legitimate};
	Adaptation_Knowledge_StateMachine<Adaptation> adaptation_Knowledge{*platform, *this, &adaptation_Knowledge};
	Adaptation_Plan_StateMachine<Adaptation> adaptation_Plan{*platform, *this, &adaptation_Plan};
	Adaptation_Execute_StateMachine<Adaptation> adaptation_Execute{*platform, *this, &adaptation_Execute};
};

#endif
