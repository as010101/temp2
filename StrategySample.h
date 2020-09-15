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
    string GetStrategyStatus();
	//virtual StrategyParameter GetStrategyParameter();
	virtual double GetActualInitCapital(double initCapital) override;
	void myStrategy(const RealtimeDepthMarketDataEx& marketData);
	void SendStrategyReport();
	void  ExceptionStockSend(string&);
	void  UpdateTickClass(const vector<string>&);//更新  概念池

	void init();
private:
	InstrumentStrategyI * m_InstrumentStrategy = nullptr;
	const StrategyParameter m_StrategyParameter;
	string isLimit;

};

#endif
