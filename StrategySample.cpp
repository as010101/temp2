#include "StrategySample.h"
#include <time.h>
#include    <thread>
#include <algorithm>
#define TIME_LIMIT  9
extern "C"
{
	//
	// Factory function
	//

	STG_API_DLL_EXPORT InstrumentStrategySpi* createInstrumentStrategy(InstrumentStrategyI* p_InstrumentStrategy)
	{
		return new StrategySample(p_InstrumentStrategy);
	}
}

StrategySample::StrategySample(InstrumentStrategyI * instrumentStrategy)
	:m_InstrumentStrategy(instrumentStrategy),
	m_Instrument(instrumentStrategy->GetInstrument()),
	m_StrategyParameter(instrumentStrategy->GetStrategyParameter()),
	m_StrategyContext(instrumentStrategy->GetInstrumentStrategyContext())
{

}

StrategySample::~StrategySample()
{

}

void StrategySample::OnRealtimeMarketData(const RealtimeDepthMarketDataEx & marketData)
{
	myStrategy(marketData);
	printf("StrategySample OnRealtimeMarketData SecurityId=%s,Volume=%ld\n",marketData.SecurityID.c_str(),marketData.Volume);
}

void StrategySample::OnStrategyStart()
{
	printf("StrategySample OnStrategyStart\n");
}

void StrategySample::OnStrategyStop()
{
	printf("StrategySample OnStrategyStop\n");
}

string StrategySample::GetStrategyStatus()
{
	/*time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	int hour = p->tm_hour+8;
	int min = p->tm_min;
	if (hour==9 &&  min>=26 &&min<30 )
	{

	}*/
		
	SendStrategyReport();
	return "StrategySampleGetStrategyStatus\n";
}

double StrategySample::GetActualInitCapital(double initCapital)
{
	return initCapital * 2;
}



/*
�����
����ڹ�Ʊ������Ҳ��� �����ź� sendreport  ͬʱֹͣ����

*/



///   ���жϸ�Ʊ�Ƿ���ͣ�󷢹�����  ��������ֱ��ͣ�����ԣ�����ִ�в���
//// �ж�ʱ��  9��30ǰͨ��  bid price �ж��Ƿ����     ���ڵ���9��30ͨ���ж�lastPrice����    
////    �����ź�  ������   һ����926 �ֶ�����   ����930����򴥷�   ����֮��Ҫ���    m_TickSetClass  ÿ�δ�����Ҫ��tick���� m_TickLimitSet��ʹ���Լ��ֹͣ
void StrategySample::myStrategy(const RealtimeDepthMarketDataEx& marketData)
{

	string tick = marketData.SecurityID;
	int time = marketData.DataTimeStamp;
	vector<string>::iterator rlt = find(m_InstrumentStrategy->m_TickLimitSet.begin(), m_InstrumentStrategy->m_TickLimitSet.end(), tick);
	if (rlt != m_InstrumentStrategy->m_TickLimitSet.end())             ////��������ͣ�źŵ�stop
	{
		OnStrategyStop();
	}
	else
	{ 

		if (time < 93000000 && time >= 92500000)
		{


			if (marketData.BidPrice1 == marketData.UpperLimitPrice)
			{
				m_InstrumentStrategy->m_lock.lock();   //////////�ٽ�����
				m_InstrumentStrategy->m_TickLimitSet.push_back(tick);
				auto  itrGetPtr = m_InstrumentStrategy->m_classPoolPtr.find(tick);   ///ĳֻ��Ʊ�ĸ���   ��ͣ���ĺ�����ٴ�����Ҫ��֤�������Ĳ��ٴ���  ����  
				auto  itrGetCopy = m_InstrumentStrategy->m_classPoolCopy.find(tick);

				//auto   itrGetTickClass = m_InstrumentStrategy->m_allTickClass;

				vector<pair<string,vector<string>>>::iterator rlt = find(m_InstrumentStrategy->m_allTickClass.begin(), m_InstrumentStrategy->m_allTickClass.end(), tick);
				
				if (rlt != m_InstrumentStrategy->m_allTickClass.end())   //�ҵ���Ʊ��Ӧ�ĸ���    ������������
				{

					UpdateTickClass((*rlt).second);
				}
				else///�쳣��ֹ
				{
					ExceptionStockSend(tick);
				}


				//if (itrGetPtr != m_InstrumentStrategy->m_classPoolPtr.end())   ///�Ѵ���
				//{
				//	(*itrGetPtr).second++;
				//}
				//else
				//{
				//	m_InstrumentStrategy->m_classPoolPtr.insert(make_pair(tick, 1));

				//}

				//if (itrGetCopy != m_InstrumentStrategy->m_classPoolCopy.end())   ///�Ѵ���
				//{
				//	(*itrGetCopy).second++;

				//}
				//else
				//{
				//	m_InstrumentStrategy->m_classPoolCopy.insert(make_pair(tick, 1));

				//}
			}

		}
		else
		{
			m_InstrumentStrategy->m_lock.lock();	 //////////�ٽ�����
			m_InstrumentStrategy->m_TickLimitSet.push_back(tick);

			////�ŵ���ʮ��ֻ���� m_classPoolCopy
			if (marketData.LastPrice == marketData.UpdatePrice)
			{
				auto  itrGetCopy = m_InstrumentStrategy->m_classPoolCopy.find(tick);
				if (itrGetCopy != m_InstrumentStrategy->m_classPoolCopy.end())   ///�Ѵ���
				{
					(*itrGetCopy).second++;
					SendStrategyReport();
				}
				else
				{
					m_InstrumentStrategy->m_classPoolCopy.insert(make_pair(tick, 1));
					SendStrategyReport();
				}

			}




		}
		m_InstrumentStrategy->m_lock.unlock();
		
	}
	//map<string, int> classPoolPtr, classPoolCopy;
	//vector<pair<string, vector<string>>>       allTickClass;     /// ���й�Ʊ�ĸ���


}

void StrategySample::myStrategy2(const RealtimeDepthMarketDataEx& marketData)
{
	string tick = marketData.SecurityID;
	int time = marketData.DataTimeStamp;
	if (time < 93000000)
	{

	}
	else
	{
	}


}
//
//string StrategyName;
//string Category;
//string Time;                     
//int DataTimeStamp;
//string Text;

void StrategySample::SendStrategyReport()
{

	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	int hour = p->tm_hour+8;
	int min=p->tm_min;
	if (hour <= 9 && min < 30)
	{
		/// m_classPoolPtr  
		StrategyExecuteReport report;
		report.StrategyName = "tickClass";
		string text = "";
		
		m_InstrumentStrategy->SendExecuteReportToClient(report);
		//cout << 8 + p->tm_hour;
	}
	else
	{
	}


	m_InstrumentStrategy->m_TickSetClass.clear();        ///�������

}

void StrategySample::ExceptionStockSend(string &str)
{
	StrategyExecuteReport report;
	report.StrategyName = "tickClass";
	string text = str+"--�����ļ���û�иù�Ʊ";
	m_InstrumentStrategy->SendExecuteReportToClient(report);
	OnStrategyStop();
}

void StrategySample::UpdateTickClass(const vector<string>& tickClass)
{
	for (auto &ele : tickClass)
	{
		auto itrPtr = m_InstrumentStrategy->m_classPoolPtr.find(ele);
		auto itrCpy=m_InstrumentStrategy->m_classPoolCopy.find(ele);
		if (itrPtr != m_InstrumentStrategy->m_classPoolPtr.end())  ///�ҵ�ĳ��������
		{
			(*itrPtr).second++;
		}
		else
		{
			m_InstrumentStrategy->m_classPoolPtr.insert(make_pair(ele,1));
		}

		if (itrCpy != m_InstrumentStrategy->m_classPoolCopy.end())  ///�ҵ�ĳ��������
		{
			(*itrCpy).second++;
		}
		else
		{
			m_InstrumentStrategy->m_classPoolCopy.insert(make_pair(ele, 1));

		}


	}



}




