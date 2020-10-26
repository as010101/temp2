#ifndef __StgStruct_h__
#define __StgStruct_h__

#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

namespace Lev2
{
	typedef ::std::vector<long long> OrderVolumes;

	enum TriggerType
	{
		Buy,
		Sell,
		Cancel
	};

	enum SourceType
	{
		Snap,
		Realtime,
		Replay
	};


	enum class UpdateTypeEnum : unsigned char
	{
		OrderBuy,
		OrderSell,
		Traded,
		Canceled
	};


	struct RealtimeDepthMarketDataEx
	{
		int Id = 0;
		char ExchangeID = 0;
		::std::string SecurityID;
		double AskPrice1 = 0;
		long long int AskVolume1 = 0LL;
		double BidPrice1 = 0;
		long long int BidVolume1 = 0LL;
		double UpperLimitPrice = 0;
		double LowerLimitPrice = 0;
		double PreClosePrice = 0;
		double OpenPrice = 0;
		double LastPrice = 0;
		double HighestPrice = 0;
		double LowestPrice = 0;
		long long int Volume = 0LL;
		double Turnover = 0;
		double TotalAskAmount = 0;
		double TotalBidAmount = 0;
		long long int TotalAskVolume = 0LL;
		long long int TotalBidVolume = 0LL;
		long long int AskCount1 = 0LL;
		long long int BidCount1 = 0LL;
		double AskPrice2 = 0;
		long long int AskVolume2 = 0LL;
		long long int AskCount2 = 0LL;
		double AskPrice3 = 0;
		long long int AskVolume3 = 0LL;
		long long int AskCount3 = 0LL;
		double AskPrice4 = 0;
		long long int AskVolume4 = 0LL;
		long long int AskCount4 = 0LL;
		double AskPrice5 = 0;
		long long int AskVolume5 = 0LL;
		long long int AskCount5 = 0LL;
		double AskPrice6 = 0;
		long long int AskVolume6 = 0LL;
		long long int AskCount6 = 0LL;
		double AskPrice7 = 0;
		long long int AskVolume7 = 0LL;
		long long int AskCount7 = 0LL;
		double AskPrice8 = 0;
		long long int AskVolume8 = 0LL;
		long long int AskCount8 = 0LL;
		double AskPrice9 = 0;
		long long int AskVolume9 = 0LL;
		long long int AskCount9 = 0LL;
		double AskPrice10 = 0;
		long long int AskVolume10 = 0LL;
		long long int AskCount10 = 0LL;
		double BidPrice2 = 0;
		long long int BidVolume2 = 0LL;
		long long int BidCount2 = 0LL;
		double BidPrice3 = 0;
		long long int BidVolume3 = 0LL;
		long long int BidCount3 = 0LL;
		double BidPrice4 = 0;
		long long int BidVolume4 = 0LL;
		long long int BidCount4 = 0LL;
		double BidPrice5 = 0;
		long long int BidVolume5 = 0LL;
		long long int BidCount5 = 0LL;
		double BidPrice6 = 0;
		long long int BidVolume6 = 0LL;
		long long int BidCount6 = 0LL;
		double BidPrice7 = 0;
		long long int BidVolume7 = 0LL;
		long long int BidCount7 = 0LL;
		double BidPrice8 = 0;
		long long int BidVolume8 = 0LL;
		long long int BidCount8 = 0LL;
		double BidPrice9 = 0;
		long long int BidVolume9 = 0LL;
		long long int BidCount9 = 0LL;
		double BidPrice10 = 0;
		long long int BidVolume10 = 0LL;
		long long int BidCount10 = 0LL;
		int DataTimeStamp = 0;
		int IngressTimeStamp = 0;
		long long int IngressTimeUsec = 0LL;
		int ProcessTimeStamp = 0;
		long long int ProcessTimeUsec = 0LL;
		int PublishTimeStamp = 0;
		long long int PublishTimeUsec = 0LL;
		TriggerType Trigger = ::Lev2::TriggerType::Buy;
		::std::string TriggerName;
		long long int MaxBidVolume1 = 0LL;
		long long int MaxAskVolume1 = 0LL;
		SourceType Source = ::Lev2::SourceType::Snap;
		OrderVolumes FirstLevelBuyOrderVolumes;
		OrderVolumes FirstLevelSellOrderVolumes;
		UpdateTypeEnum UpdateType = ::Lev2::UpdateTypeEnum::OrderBuy;
		double UpdatePrice = 0;
		long long int UpdateVolume = 0LL;

		
	};

}

namespace stgapi
{

	struct AccountInfo
	{
		::std::string LogInAccount;
		char LogInAccountType;
		::std::string AccountID;
		::std::string AccountName;
		::std::string InvestorID;
		double AvailableMoney;
		double WithdrawQuota;
		double Deposit;
		double Withdraw;
		double FrozenMargin;
		double FrozenCash;
		double FrozenCommission;
		double CurrMargin;
		double Commission;
		double AccountType;
		::std::string AccountOwner;

		
	};
	/**
	* 白名单中的账户资金分配信息
	*/
	struct InstrumentAccountInfo
	{
		::std::string AccountID;
		double InitCapital;
	};
	using InstrumentAccountList = ::std::vector<InstrumentAccountInfo>;

	typedef ::std::map< ::std::string, ::std::string> PropertyDictionary;
	using TagList = ::std::vector<::std::string>;

	/**
	* 交易合约定义，白名单中一行
	*/
	struct Instrument
	{
		::std::string SecurityId;
		::std::string SecurityName;
		::std::string BuyPriceType;
		double BuyPrice;
		double BuyPriceFactor;
		long long int BuyVolume;
		bool BuyTriggered;
		bool BuyCanceled;
		::std::string SellPriceType;
		double SellPrice;
		double SellPriceFactor;
		long long int SellVolume;
		::std::string SellPolicy;
		bool SellTriggered;
		bool SellCanceled;
		InstrumentAccountList Accounts;
		PropertyDictionary ExProperties;

		/**
		* Obtains a tuple containing all of the exception's data members.
		* @return The data members in a tuple.
		*/

		std::tuple<const ::std::string&, const ::std::string&, const ::std::string&, const double&, const double&, const long long int&, const bool&, const bool&, const ::std::string&, const double&, const double&, const long long int&, const ::std::string&, const bool&, const bool&, const InstrumentAccountList&, const PropertyDictionary&> ice_tuple() const
		{
			return std::tie(SecurityId, SecurityName, BuyPriceType, BuyPrice, BuyPriceFactor, BuyVolume, BuyTriggered, BuyCanceled, SellPriceType, SellPrice, SellPriceFactor, SellVolume, SellPolicy, SellTriggered, SellCanceled, Accounts, ExProperties);
		}
	};

	/**
	* 触发器定义
	*/
	struct TriggerParameter
	{
		::std::string Name;
		::std::string Expression;

		bool operator==(const TriggerParameter& rhs_) const
		{
			if (this == &rhs_)
			{
				return true;
			}
			if (Name != rhs_.Name)
			{
				return false;
			}
			if (Expression != rhs_.Expression)
			{
				return false;
			}
			return true;
		}

		bool operator<(const TriggerParameter& rhs_) const
		{
			if (this == &rhs_)
			{
				return false;
			}
			if (Name < rhs_.Name)
			{
				return true;
			}
			else if (rhs_.Name < Name)
			{
				return false;
			}
			if (Expression < rhs_.Expression)
			{
				return true;
			}
			else if (rhs_.Expression < Expression)
			{
				return false;
			}
			return false;
		}

		bool operator!=(const TriggerParameter& rhs_) const
		{
			return !operator==(rhs_);
		}
		bool operator<=(const TriggerParameter& rhs_) const
		{
			return operator<(rhs_) || operator==(rhs_);
		}
		bool operator>(const TriggerParameter& rhs_) const
		{
			return !operator<(rhs_) && !operator==(rhs_);
		}
		bool operator>=(const TriggerParameter& rhs_) const
		{
			return !operator<(rhs_);
		}
	};


	using TriggerParameterDictionary = ::std::map<::std::string, TriggerParameter>;


	enum class StrategyMode : unsigned char
	{
		Realtime,
		Simulator
	};

	enum TimePharse
	{
		T925,
		T930
	};

	/**
	* 策略参数定义
	*/
	struct StrategyParameter
	{
		/**
		* 策略名称
		*/
		::std::string Name;
		/**
		* 策略扩展库名称
		*/
		::std::string SoName;
		/**
		* 策略运行模式
		*/
		StrategyMode Mode = ::stgapi::StrategyMode::Realtime;
		/**
		* 买入交易开始时间,精确到秒
		*/
		int TimeBegin = 91500;
		/**
		* 买入交易截止时间，精确到秒
		*/
		int TimeEnd = 150000;
		/**
		* 初始白名单名称
		*/
		::std::string InstrumentListName;
		/**
		* 单笔委托量拆单上限
		*/
		long long int BidVolumeUpperLimit = 100000LL;
		/**
		* 单笔委托量拆单下限
		*/
		long long int BidVolumeLowerLimit = 1000LL;
		/**
		* 可重复买入次数
		*/
		int BuyRepeatTimes = 2;
		/**
		* 行情延时阈值(秒)
		*/
		int LaterThanLocalTimeThreshold = 4;
		/**
		* 买入触发个股上限
		*/
		int BuyInstrumentNumUpperLimit = 80;
		/**
		* 买入触发热点个股上限
		*/
		int BuyInstrumentNumInTag = 3;
		/**
		* 买入概念涨停个股统计开始阶段
		*/
		TimePharse UpLmtCounterBeginTime = ::stgapi::TimePharse::T925;
		/**
		* TWAP每次标准卖出量除数
		*/
		int TwapSellNoofTimes = 20;
		/**
		* TWAP卖出时间间隔(秒)
		*/
		int TwapSellTimeInterval = 300;
		/**
		* TWAP卖出未成交撤单间隔(秒)
		*/
		int TwapCancelTimeInterval = 30;
		/**
		* 集合竞价卖出时间提前量(ms)
		*/
		int AuctionSellTimeAhead = 5;
		/**
		* 计划卖出比例(%)
		*/
		int ProposedSellingPercent = 0;
		/**
		* 单笔卖出金额下限
		*/
		double LowerLimitSellAmount = 20000;
		/**
		* 集合竞价卖单价格下浮调节量(分)
		*/
		int AuctionPriceDelt = 2;
		TriggerParameter BuyTriggerParameter;
		TriggerParameter SellTriggerParameter;
		TriggerParameter CancelTriggerParameter;
		TriggerParameterDictionary BuyTriggerParameterOthers;
		TriggerParameterDictionary CancelTriggerParameterOthers;
		TriggerParameterDictionary SellTriggerParameterOthers;
		/**
		* 附加动态属性
		*/
		PropertyDictionary ExProperties;

		/**
		* Obtains a tuple containing all of the exception's data members.
		* @return The data members in a tuple.
		*/

		std::tuple<const ::std::string&, const ::std::string&, const StrategyMode&, const int&, const int&, const ::std::string&, const long long int&, const long long int&, const int&, const int&, const int&, const int&, const TimePharse&, const int&, const int&, const int&, const int&, const int&, const double&, const int&, const TriggerParameter&, const TriggerParameter&, const TriggerParameter&, const TriggerParameterDictionary&, const TriggerParameterDictionary&, const TriggerParameterDictionary&, const PropertyDictionary&> ice_tuple() const
		{
			return std::tie(Name, SoName, Mode, TimeBegin, TimeEnd, InstrumentListName, BidVolumeUpperLimit, BidVolumeLowerLimit, BuyRepeatTimes, LaterThanLocalTimeThreshold, BuyInstrumentNumUpperLimit, BuyInstrumentNumInTag, UpLmtCounterBeginTime, TwapSellNoofTimes, TwapSellTimeInterval, TwapCancelTimeInterval, AuctionSellTimeAhead, ProposedSellingPercent, LowerLimitSellAmount, AuctionPriceDelt, BuyTriggerParameter, SellTriggerParameter, CancelTriggerParameter, BuyTriggerParameterOthers, CancelTriggerParameterOthers, SellTriggerParameterOthers, ExProperties);
		}
	};


}

using namespace Lev2;
using namespace stgapi;


struct ExMarketData
{
	//集合竞价最大涨停概念
	string GaiNianMaxUpLmtCount925;
	//集合竞价最大涨停概念的涨停数
	int	   MaxUpLmtCount925 = 0;
	//连续竞价阶段最大涨停概念
	string GaiNianMaxUpLmtCount930;
	//连续竞价阶段最大涨停概念的涨停数
	int    MaxUpLmtCount930 = 0;
};

struct InstrumentStrategyContext
{
	//当前盘口
	RealtimeDepthMarketDataEx MarketData;
	//是否已触发买入
	bool IsBuyTriggered = false;
	//触发买入的盘口行情快照
	RealtimeDepthMarketDataEx MarketDataBuyTriggered;
	//是否已触发卖出
	bool IsSellTriggered = false;
	//触发卖出的盘口行情快照
	RealtimeDepthMarketDataEx MarketDataSellTriggered;
	//是否已触发撤单
	bool IsCancelTriggered = false;
	//触发撤单的盘口行情快照
	RealtimeDepthMarketDataEx MarketDataCancelTriggered;

	//计算的扩展行情
	ExMarketData ExtendedMarketData;

	
	//买入触发次数
	int  NumberOfBuyTriggered = 0;
	//是否允许买入
	bool IsBuyable = true;
	//策略重置次数
	int ResetTimes = 0;
	//计划卖出量
	long ProposedSellingQty = 0;
	//是否禁止开板卖出
	bool DisableSellUpDown = false;

	//历史持仓
	std::map<std::string, long> HistoryPositions;
	//可卖持仓
	std::map<std::string, long> AvailablePositions;
};
struct TimeLongValue
{
	int dataTimeStamp = 0;
	long value = 0;
};

// 用于实时通知
struct StrategyExecuteReport
{
	string StrategyName;
	string Category;
	string Time;
	int DataTimeStamp;
	string Text;
};
//用户保存执行报告
struct InstrumentStrategyExecuteReport
{
	string TradingDay;
	string StrategyName;
	string SecurityId;
	string SecurityName;
	string Direction;
	string OrderTime;
	string CancelTime;
	string FirstFilledTime;
	string OrderTriggerName;
	string OrderTriggerReason;
	string OrderTriggerDetails;
	string CancelTriggerName;
	string CancelTriggerReason;
	string CanelTriggerDetails;
	string DisabledTime;
	string DisabledReason;
	string DisabledDetails;
	string EnabledTime;
	string EnabledReason;
	string EnabledDetails;

	static string toTitle()
	{
		stringstream ss;
		ss << "TradingDay," << "SecurityId," << "SecurityName," << "Direction," << "OrderTime," << "CancelTime," << "FirstFilledTime," << "OrderTriggerName," << "OrderTriggerReason," << "OrderTriggerDetails,"
			<< "CancelTriggerReason," << "CanelTriggerDetails," << "DisabledTime," << "DisabledReason," << "DisabledDetails," << "EnabledTime," << "EnabledReason," << "EnabledDetails" << endl;
		return ss.str();
	}
	string toString()
	{
		stringstream ss;
		ss << TradingDay << "," << SecurityId << "," << SecurityName << "," << Direction << "," << OrderTime << "," << CancelTime << "," << FirstFilledTime << "," << OrderTriggerName << "," << OrderTriggerReason << "," << OrderTriggerDetails << ","
			<< CancelTriggerReason << "," << CanelTriggerDetails << "," << DisabledTime << "," << DisabledReason << "," << DisabledDetails << "," << EnabledTime << "," << EnabledReason << "," << EnabledDetails << endl;
		return ss.str();
	}

};

struct StrategyOrderInfo
{
	int BuyTriggeredInstrumentNum = 0;
	int BuyOrderNum = 0;
	int WorkingBuyOrderNum = 0;
	int WorkingSellOrderNum = 0;
	int CanceledBuyOrderNum = 0;

	int SellOrderNum = 0;
	int FilledBuyOrderNum = 0;
	int FilledSellOrderNum = 0;
	int CanceledSellOrderNum = 0;
};


#endif