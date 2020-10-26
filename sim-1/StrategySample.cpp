#include "StrategySample.h"


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
//	m_count++;
//	int res = m_count % 10;
//	printf("%d",res);
//	if (res == 0 )
//	{
//		m_flag = 1;
//		StrategyExecuteReport report;
//		report.DataTimeStamp = marketData.DataTimeStamp;
//		report.StrategyName = "920-925";
//		report.Text = "flagMessage-"+ marketData.SecurityID;										
//		m_InstrumentStrategy->SendExecuteReportToClient(report);										
//
//	}
	

	if (marketData.DataTimeStamp >= 92000000 && marketData.DataTimeStamp <= 92500000)
	{

		if (m_preSendPrice == 0)
		{

			//StrategyExecuteReport report;
			//report.StrategyName = "TEST";
			//report.Time = marketData.DataTimeStamp;
			//report.Text = "--init price-";
			m_preSendPrice = marketData.BidPrice1;
			m_minPrice = marketData.BidPrice1;
		}
		else
		{

			//否则判断是否增量，有增量则替换	m_preSendPrice
			if ((marketData.BidPrice1 - m_preSendPrice) > 0)
			{

				double scale = marketData.BidPrice1 - m_minPrice;

				m_preSendPrice = marketData.BidPrice1;
				StrategyExecuteReport report;
				report.StrategyName = "920-925";
				report.Time = to_string(marketData.DataTimeStamp);
				report.DataTimeStamp = marketData.DataTimeStamp;
				report.Text = marketData.SecurityID + "--" + to_string(marketData.DataTimeStamp) + "scale:" + to_string(scale / m_minPrice) + "price:" + to_string(m_preSendPrice);
				m_InstrumentStrategy->SendExecuteReportToClient(report);
				double PriceFactor = (marketData.BidPrice1 - m_minPrice) / m_minPrice;  ///相对于初始价格涨了多少
				if (PriceFactor > m_PriceFactor)  ///从9：20开始 volume  scale超过一定尺度，则委托
				{
				
					StrategyExecuteReport report;
					report.Time = to_string(marketData.DataTimeStamp);
					report.DataTimeStamp = marketData.DataTimeStamp;
					report.StrategyName = "920-925";
					report.Text = "exec buy order--price trigger !!!--currScale" + to_string(PriceFactor);
					m_InstrumentStrategy->SendExecuteReportToClient(report);
					m_InstrumentStrategy->SendBuyOrder();
					OnStrategyStop();
				}
			}
		}
	}


	printf("StrategySample OnRealtimeMarketData SecurityId=%s,Volume=%ld ,Time=%d\n",marketData.SecurityID.c_str(),marketData.Volume,marketData.DataTimeStamp);
}

void StrategySample::OnStrategyStart()
{
	printf("StrategySample OnStrategyStart\n");
}

void StrategySample::OnStrategyStop()
{
	printf("StrategySample OnStrategyStop\n");
}
void StrategySample::OnTriggerParameterUpdate(const TriggerParameter& triggerParameter)
{
	printf("StrategySample OnTriggerParameterUpdate\n");
}

string StrategySample::GetStrategyStatus()
{
	
	return "StrategySampleGetStrategyStatus\n";
}

double StrategySample::GetActualInitCapital(double initCapital)
{
	return initCapital * 2;
}
