#ifndef INSTRUMENT_STG_H
#define INSTRUMENT_STG_H

#include "InstrumentStrategyStructType.h"
#include <string>



using namespace Lev2;

class InstrumentStrategyI
{
public:
	//获取策略名称
	virtual string Name() = 0;
	//获取当前策略的合约信息
	virtual Instrument& GetInstrument() = 0;
	//获取当前策略参数设置
	virtual StrategyParameter& GetStrategyParameter() = 0;
	//获取当前策略运行时状态
	virtual InstrumentStrategyContext& GetInstrumentStrategyContext() = 0;
	//按合约信息中的价和量发送买单
	virtual void SendBuyOrder() = 0;
	//撤销排队中的委托（买单或卖单），参数sInfo指定过滤条件，满足特定条件的委托才会撤单
	virtual void SendCancelOrder(const string& sInfo = "") = 0;
	//发送执行报告至客户端
	virtual void SendExecuteReportToClient(StrategyExecuteReport&) = 0;
	//获取当前策略的服务端执行报告
	virtual InstrumentStrategyExecuteReport& GetInstrumentStrategyExecuteReport() = 0;
	//保存服务端执行报告
	virtual void SaveInstrumentStrategyExecuteReport() = 0;
	//查询当前策略的委托单信息
	virtual StrategyOrderInfo QryStrategyOrderInfo() = 0;
	//记录日志
	virtual void writelog(const string categary, const int dataTimeStamp, const string text) = 0;
	//判断当前策略是否有当日买单
	virtual bool HasBuyOrders() = 0;
	//获取可用持仓
	virtual map<string, long> GetAvailablePositions() = 0;
	//买单触发后置处理
	virtual void PostBuyTriggered() = 0;

	//启动TWAP卖出任务
	virtual void StartTWAPSell() = 0;
	//启动开板TWAP卖出
	virtual void StartSellUplmt() = 0;
	//启动集合竞价卖出
	virtual void StartSellAuction() = 0;
	//是否为实盘场景
	virtual bool IsRealtimeScenario() = 0;

};


class InstrumentStrategySpi
{
public:
	/**
	*行情流入策略的主入口
	*/
	virtual void OnRealtimeMarketData(const RealtimeDepthMarketDataEx& marketData)=0;

	/**
	*策略启动时调用此方法，完成前策略不做任何其他处理
	*/
	virtual void OnStrategyStart()=0;

	/**
	*策略停止时调用此方法
	*/
	virtual void OnStrategyStop()=0;

	/*策略状态查询*/
	virtual string GetStrategyStatus() = 0;

	/*动态调仓
	*@param initCapital 初始仓位金额
	*/
	virtual double GetActualInitCapital(double initCapital) = 0;

	/*更改触发器参数
	*@param triggerParameter 触发器参数
	*/
	virtual void OnTriggerParameterUpdate(const TriggerParameter& triggerParameter) = 0;

};



#endif
