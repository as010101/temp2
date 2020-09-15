#define _CRT_SECURE_NO_WARNINGS


#include "StrategySample.h"
#include <time.h>
#include    <thread>
#include <algorithm>
#include <fstream>
#include "json.hpp"
#define TIME_LIMIT  9


StrategySample::StrategySample(InstrumentStrategyI* instrumentStrategy)
	:m_InstrumentStrategy(instrumentStrategy)
{
	//using json = nlohmann::json;
	//json j= json::parse(m_StrategyParameter.BuyTriggerParameter.Expression);
	//for (json::iterator it = j.begin(); it != j.end(); ++it) {
	//	vector<string> vec;
	//	string mykey = it.key();
	//	m_InstrumentStrategy->m_allTickClass.push_back(make_pair(mykey,vec));
	//	vec.clear();
	//	for (int k = 0; k < (*it).size(); k++)
	//	{
	//vector<string>::iterator itr = find(vec.begin(), vec.end(), (*it));
	//if (itr != vec.end())
	//{
	//	continue;
	//}
	//else
	//{
	//	vec.push_back((*it)[k]);
	//}
	//	}
	//	vector<pair<string, vector<string>>>::iterator rlt = find_if(m_InstrumentStrategy->m_allTickClass.begin(), m_InstrumentStrategy->m_allTickClass.end(),
	//		[&mykey](const std::pair<std::string, vector<string>>& element) { return element.first == mykey; });
	//	(*rlt).second = vec;
	//}
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
概念处理
如果在股票概念集合找不到 则发送信号 sendreport  同时停止策略

*/



///   先判断该票是否涨停后发过数据  触发过了直接停掉策略，否则执行策略
//// 判断时间  9：30前通过  bid price 判断是否加锁     大于等于9：30通过判断lastPrice加锁    
////    发送信号  分两类   一种是926 手动触发   二是930后程序触发   触发之后都要清空    m_TickSetClass  每次触发都要将tick加入 m_TickLimitSet，使策略检查停止
void StrategySample::myStrategy(const RealtimeDepthMarketDataEx& marketData)
{

	string tick = marketData.SecurityID;
	int time = marketData.DataTimeStamp;
	vector<string>::iterator rlt = find(m_InstrumentStrategy->m_TickLimitSet.begin(), m_InstrumentStrategy->m_TickLimitSet.end(), tick);
	if (rlt != m_InstrumentStrategy->m_TickLimitSet.end())             ////触发过涨停信号的stop
	{
		OnStrategyStop();
	}
	else
	{ 

		if (time < 93000000 && time >= 92500000)
		{


			if (marketData.BidPrice1 == marketData.UpperLimitPrice)
			{
				m_InstrumentStrategy->m_lock.lock();   //////////临界区域
				m_InstrumentStrategy->m_TickLimitSet.push_back(tick);
				m_InstrumentStrategy->m_TickSetClass.push_back(tick);

				auto  itrGetPtr = m_InstrumentStrategy->m_classPoolPtr.find(tick);   ///某只股票的概念   涨停过的后面会再触发，要保证触发过的不再触发  保留  
				auto  itrGetCopy = m_InstrumentStrategy->m_classPoolCopy.find(tick);

				//auto   itrGetTickClass = m_InstrumentStrategy->m_allTickClass;
	
				vector<pair<string,vector<string>>>::iterator rlt = find_if(m_InstrumentStrategy->m_allTickClass.begin(), m_InstrumentStrategy->m_allTickClass.end(),
					[&tick](const std::pair<std::string, vector<string>>& element) { return element.first == tick; });
				

				if (rlt != m_InstrumentStrategy->m_allTickClass.end())   //找到股票对应的概念    逐个检查概念并更新
				{

					UpdateTickClass((*rlt).second);
				}
				else///异常终止
				{
					ExceptionStockSend(tick);
				}


				//if (itrGetPtr != m_InstrumentStrategy->m_classPoolPtr.end())   ///已存在
				//{
				//	(*itrGetPtr).second++;
				//}
				//else
				//{
				//	m_InstrumentStrategy->m_classPoolPtr.insert(make_pair(tick, 1));

				//}

				//if (itrGetCopy != m_InstrumentStrategy->m_classPoolCopy.end())   ///已存在
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


			////九点三十后只更新 m_classPoolCopy
			if (marketData.LastPrice == marketData.UpdatePrice)
			{

				m_InstrumentStrategy->m_lock.lock();	 //////////临界区域
				m_InstrumentStrategy->m_TickLimitSet.push_back(tick);
				m_InstrumentStrategy->m_TickSetClass.push_back(tick);

				auto  itrGetCopy = m_InstrumentStrategy->m_classPoolCopy.find(tick);
				if (itrGetCopy != m_InstrumentStrategy->m_classPoolCopy.end())   ///已存在
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
	//vector<pair<string, vector<string>>>       allTickClass;     /// 所有股票的概念


}

//void StrategySample::myStrategy2(const	& marketData)
//{
//	//string tick = marketData.SecurityID;
//	//int time = marketData.DataTimeStamp;
//	//if (time < 93000000)
//	//{
//
//	//}
//	//else
//	//{
//	//}
//
//
//}
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
	int hour = p->tm_hour + 8;
	int min = p->tm_min;
	StrategyExecuteReport report;
	report.StrategyName = "tickClass";
	string AllText = "";
	if (hour <= 9 && min < 30)
	{

		StrategyExecuteReport report;
		report.StrategyName = "tickClass";
		


		for (auto eles : m_InstrumentStrategy->m_TickSetClass)
		{
			//stockID = eles;
			//text = text + eles;
			string text = "";
			vector<pair<string, vector<string>>>::iterator rlt = find_if(m_InstrumentStrategy->m_allTickClass.begin(), m_InstrumentStrategy->m_allTickClass.end(),
				[&eles](const std::pair<std::string, vector<string>>& element) { return element.first == eles; });
			for (auto subele : (*rlt).second)
			{
				auto num = m_InstrumentStrategy->m_classPoolPtr.find(subele);
				text = text + to_string((*num).second) + subele + "|";

			}
			text = eles+":"+text + "#";

			AllText = AllText + text;
		}



	}
	else
	{
		for (auto eles : m_InstrumentStrategy->m_TickSetClass)
		{
			//stockID = eles;
			//text = text + eles;
			string text = "";
			vector<pair<string, vector<string>>>::iterator rlt = find_if(m_InstrumentStrategy->m_allTickClass.begin(), m_InstrumentStrategy->m_allTickClass.end(),
				[&eles](const std::pair<std::string, vector<string>>& element) { return element.first == eles; });
			for (auto subele : (*rlt).second)
			{
				auto num = m_InstrumentStrategy->m_classPoolCopy.find(subele);
				text = text + to_string((*num).second) + subele + "|";

			}
			text = eles + ":" + text + "#";

			AllText = AllText + text;
		}


	}
	report.Text = AllText;
//	m_InstrumentStrategy->SendExecuteReportToClient(report);

	m_InstrumentStrategy->m_TickSetClass.clear();        ///清空数据

}

void StrategySample::ExceptionStockSend(string &str)
{
	StrategyExecuteReport report;
	report.StrategyName = "tickClass";
	string text = str+"--概念文件中没有该股票";
//	m_InstrumentStrategy->SendExecuteReportToClient(report);
	OnStrategyStop();
}

void StrategySample::UpdateTickClass(const vector<string>& tickClass)
{
	for (auto &ele : tickClass)
	{
		auto itrPtr = m_InstrumentStrategy->m_classPoolPtr.find(ele);
		auto itrCpy=m_InstrumentStrategy->m_classPoolCopy.find(ele);
		if (itrPtr != m_InstrumentStrategy->m_classPoolPtr.end())  ///找到某个概念了
		{
			(*itrPtr).second++;
		}
		else
		{
			m_InstrumentStrategy->m_classPoolPtr.insert(make_pair(ele,1));
		}

		if (itrCpy != m_InstrumentStrategy->m_classPoolCopy.end())  ///找到某个概念了
		{
			(*itrCpy).second++;
		}
		else
		{
			m_InstrumentStrategy->m_classPoolCopy.insert(make_pair(ele, 1));

		}


	}



}

void StrategySample::init()
{

	using json = nlohmann::json;
	std::ifstream i("my.json");
	json j;
	i >> j;

for (json::iterator it = j.begin(); it != j.end(); ++it) {
	vector<string> vec;
	string mykey = it.key();
	m_InstrumentStrategy->m_allTickClass.push_back(make_pair(mykey,vec));
	vec.clear();
	for (int k = 0; k < (*it).size(); k++)
	{

		vector<string>::iterator itr = find(vec.begin(),vec.end(),(*it)[k]);
		if (itr != vec.end())
		{
			continue;
		}
		else
		{
			vec.push_back((*it)[k]);
		}
	//std::cout << (*it)[k]<< '\n';
	}
	vector<pair<string, vector<string>>>::iterator rlt = find_if(m_InstrumentStrategy->m_allTickClass.begin(), m_InstrumentStrategy->m_allTickClass.end(),
		[&mykey](const std::pair<std::string, vector<string>>& element) { return element.first == mykey; });
	(*rlt).second = vec;
}
}



//int main()
//{
//	return 0;
//}
