#ifndef INSTRUMENT_STG_H
#define INSTRUMENT_STG_H

#include "InstrumentStrategyStructType.h"
#include <string>

#include <mutex>


using namespace Lev2;

class InstrumentStrategyI
{
public:
	////��ȡ��������
	//virtual string Name() = 0;
	////��ȡ��ǰ���Եĺ�Լ��Ϣ
	//virtual Instrument GetInstrument()=0;
	////��ȡ��ǰ���Բ�������
	//virtual StrategyParameter GetStrategyParameter() = 0;
	////��ȡ��ǰ��������ʱ״̬
	//virtual InstrumentStrategyContext& GetInstrumentStrategyContext() = 0;
	////����Լ��Ϣ�еļۺ���������
	//virtual void SendBuyOrder() = 0;
	////�����Ŷ��е�ί�У��򵥻�������������sInfoָ�����������������ض�������ί�вŻ᳷��
	//virtual void SendCancelOrder(const string& sInfo = "") = 0;
	////����ִ�б������ͻ���
	//virtual void SendExecuteReportToClient(StrategyExecuteReport&) = 0;
	////��ȡ��ǰ���Եķ����ִ�б���
	//virtual InstrumentStrategyExecuteReport& GetInstrumentStrategyExecuteReport() = 0;
	////��������ִ�б���
	//virtual void SaveInstrumentStrategyExecuteReport() = 0;
	////��ѯ��ǰ���Ե�ί�е���Ϣ
	//virtual StrategyOrderInfo QryStrategyOrderInfo() = 0;
	////��¼��־
	//virtual void writelog(const string categary, const int dataTimeStamp, const string text) = 0;
	////�жϵ�ǰ�����Ƿ��е�����
	//virtual bool HasBuyOrders() = 0;
	////��ȡ���óֲ�
	//virtual map<string, long> GetAvailablePositions() = 0;
	////�򵥴������ô���
	//virtual void PostBuyTriggered() = 0;

	////����TWAP��������
	//virtual void StartTWAPSell() = 0;
	////��������TWAP����
	//virtual void StartSellUplmt() = 0;
	////�������Ͼ�������
	//virtual void StartSellAuction() = 0;

	map<string, int> m_classPoolPtr, m_classPoolCopy;//////////
	vector<pair<string, vector<string>>>     m_allTickClass;     /// ���й�Ʊ�ĸ���
	vector<string>     m_TickSetClass;     /// ���Ͼ�����ͣϵ��  һ�η�������  tick  tickclass tickclassNum    ��������  һ�η���һֻ
	vector<string>     m_TickLimitSet;     /// ��������ͣ��ƱҪ��¼  ʹ��ĳƱ����ֹͣ
	  /// ����������ͣϵ��  ÿ�δ���ֻ����һ��Ʊ tick  tickclass tickclassNum    ʹ��  m_TickSetClass��ÿ�η������ݶ�Ҫ���
	mutex  m_lock;
};


class InstrumentStrategySpi
{
public:
	/**
	*����������Ե������
	*/
	virtual void OnRealtimeMarketData(const RealtimeDepthMarketDataEx& marketData)=0;

	/**
	*��������ʱ���ô˷��������ǰ���Բ����κ���������
	*/
	virtual void OnStrategyStart()=0;

	/**
	*����ֹͣʱ���ô˷���
	*/
	virtual void OnStrategyStop()=0;

	/*����״̬��ѯ*/
	virtual string GetStrategyStatus() = 0;

	/*��̬����
	*@param initCapital ��ʼ��λ���
	*/
	virtual double GetActualInitCapital(double initCapital) = 0;

};



#endif
