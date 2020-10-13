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
	if (marketData.DataTimeStamp >= 92000000 && marketData.DataTimeStamp <= 92500000)
	{
		if (marketData.BidPrice1==marketData.UpperLimitPrice)   ///如果买一是limitPrice
		{
			///涨停判断封单量
			m_isLimit = 1;
			if (m_preSendVolume == 0)
			{
				m_preSendVolume = marketData.BidVolume1;
			}
			else
			{
				//否则判断是否增量，有增量则替换	m_preSendVolume
				if ((marketData.BidVolume1 - m_preSendVolume) > 0)
				{
					int num = marketData.BidVolume1 - m_preSendVolume;
					m_preSendVolume = marketData.BidVolume1;
					StrategyExecuteReport report;
					report.StrategyName = "925";
					report.Text = marketData.SecurityID + to_string(marketData.DataTimeStamp) + to_string((num* marketData.BidPrice1) / (m_minVolume* marketData.BidPrice1));
					m_InstrumentStrategy->SendExecuteReportToClient(report);
				}

			}
				
		}
		else
		{
			if (m_isLimit == 1)  //破板了
			{
				return;
			}
			else
			{
				if (m_preSendPrice == 0)
				{
					m_preSendPrice = marketData.BidPrice1;
				}
				else
				{
					//否则判断是否增量，有增量则替换	m_preSendPrice
					if ((marketData.BidPrice1 - m_preSendPrice) > 0)
					{
						double scale=marketData.BidPrice1 - m_preSendPrice;
						m_preSendPrice = marketData.BidPrice1;
						StrategyExecuteReport report;
						report.StrategyName = "925";
						report.Text = marketData.SecurityID + to_string(marketData.DataTimeStamp) + to_string(scale / m_minPrice);
						m_InstrumentStrategy->SendExecuteReportToClient(report);
					}

				}

			}

		}

	}
	if (marketData.DataTimeStamp >= 93000000)
	{
		OnStrategyStop();
	}
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
	
	return "StrategySampleGetStrategyStatus\n";
}

double StrategySample::GetActualInitCapital(double initCapital)
{
	return initCapital * 2;
}
