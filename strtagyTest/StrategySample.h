#ifndef MY_STG_H
#define MY_STG_H

#include "InstrumentStrategy.h"



#ifdef STG_API_EXPORT
#ifdef WINDOWS
#define STG_API_DLL_EXPORT __declspec(dllexport)
#else
#define STG_API_DLL_EXPORT __attribute__ ((visibility("default")))
#endif
#else
#define STG_API_DLL_EXPORT 
#endif

class StrategySample :public InstrumentStrategySpi
{
public:
	StrategySample(InstrumentStrategyI* instrumentStrategy);
	~StrategySample();

	// 通过 InstrumentStrategySpi 继承
	virtual void OnRealtimeMarketData(const RealtimeDepthMarketDataEx & marketData) override;
	virtual void OnStrategyStart() override;
	virtual void OnStrategyStop() override;
	virtual string GetStrategyStatus() override;
	virtual double GetActualInitCapital(double initCapital) override;

private:
	InstrumentStrategyI * m_InstrumentStrategy = nullptr;
	const Instrument m_Instrument;
	const StrategyParameter m_StrategyParameter;
	InstrumentStrategyContext& m_StrategyContext;
	int m_isLimit=0;					
	int m_minVolume=0;
	double m_minPrice=0;
	int m_preSendVolume=0;   //封单量的price只可能是limitPrice
	double m_preSendPrice=0;
};

#endif
