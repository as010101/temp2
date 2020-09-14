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
	void myStrategy(const RealtimeDepthMarketDataEx& marketData);
	void myStrategy2(const RealtimeDepthMarketDataEx& marketData);
	void SendStrategyReport();
	void  ExceptionStockSend(string&);
	void  UpdateTickClass(const vector<string>&);//更新  概念池

private:
	InstrumentStrategyI * m_InstrumentStrategy = nullptr;
	const Instrument m_Instrument;
	const StrategyParameter m_StrategyParameter;
	InstrumentStrategyContext& m_StrategyContext;
	string isLimit;

};

#endif
