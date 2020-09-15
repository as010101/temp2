#define	_CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <map>
#include <time.h> 
#include <iostream>
#include <algorithm>
#include "StrategySample.h"
#include "json.hpp"
#include <fstream>
//using namespace std;
// txt    tick time

//classPoolPtr
//9:30 ǰʹ��share_ptr
//9��30��copy classPoolCopy��num
//��ʼ������tick �͸���
//9��30ǰ  ʵʱ����
//
//1.�������ж�Ӧtick �� ����  ʵʱ���� classPoolPtr  classPoolCopy
//tick  tickclass  tickclassNum
//
//
//2 9��30��ֻ���¶�Ӧtick �� ����  ʵʱ���� classPoolCopy
//tick  tickclass  tickclassNum
//
//3.   9:30ǰ��classPoolPtr   ȡ

//struct classPool
//{
//	char tick[8];
//    int8_t  num;
//};
//struct classPool
//{
//	char tick[8];
//    int8_t  num;
//};

using PoolElement = map<string, int>;			



//bool isEqual(const std::pair<std::string, int>& element)
//{
//	return element.first == User.name;
//}
//it = std::find_if(sortList.begin(), sortList.end(), isEqual);
int main()
{
	
	std::string s = "����";
	ifstream  ss1();
	for (size_t i = 0; i < s.size(); ++i)
	{
		std::cout << i << " " << std::hex << static_cast<int>(static_cast<uint8_t>(s[i])) << std::endl;
	}
	//string mypars = "{\"000000\":[\"����\",\"���ڷ���\"],\"000001\":[\"����\",\"���ڷ���\"]}";
	//string mypars = R"({"000000":["2","2"],"000001":["2","2"]})"_json;
//	json j = "{\"000000\":[\"����\",\"���ڷ���\"],\"000001\":[\"����\",\"���ڷ���\"]}"_json;
	//string mypars;
	//ifstream  in("my.json");
	//while

	using json = nlohmann::json;

	//std::ifstream i("my.json");
	//json j;
	//i >> j;


	//json j_original = R"({
 // "baz": ["one", "two", "three"],
 // "foo": ["one", "two", "three"]})"_json;
		
//	json j = "{\"000000\":[\"����\",\"���ڷ���\"],\"000001\":[\"����\",\"���ڷ���\"]}"_json;

	//auto jsosns = json::parse("{\"000000\":[\"����\",\"���ڷ���\"],\"000001\":[\"����\",\"���ڷ���\"]}");
	//string 
	//auto jsosns=json::parse("{\"000000\":[\"����\",\"���ڷ���\"]}");
	RealtimeDepthMarketDataEx testData;	
	testData.LastPrice = 1.2;
	testData.BidPrice1= 1.2;
	testData.UpperLimitPrice = 1.2;
	testData.DataTimeStamp = 92500000;
	testData.SecurityID = "000001";
	StrategySample *fsda = new StrategySample(new InstrumentStrategyI);
	fsda->init();
	fsda->OnRealtimeMarketData(testData);
	fsda->SendStrategyReport();
	vector<int> L;
	L.push_back(1);
	L.push_back(2);
	L.push_back(3);
	L.push_back(4);
	L.push_back(5);
	vector<int>::iterator result = find(L.begin(), L.end(), 3);

	vector<pair<string, vector<string>>> ssxd;
	vector<string>  vecmy;
	string ssdxd = "s";
	vecmy.push_back("xxx");
	ssxd.push_back(make_pair("1", vecmy));
	ssxd.push_back(make_pair("2", vecmy));
	ssxd.push_back(make_pair("3", vecmy));
	ssxd.push_back(make_pair("123", vecmy));

	auto it = std::find_if(ssxd.begin(), ssxd.end(),
		[&ssdxd](const std::pair<std::string, vector<string>>& element) { return element.first == ssdxd; });
	//vector<pair<string, vector<string>>>::iterator rlt = find(ssxd.begin(), ssxd.end(), "123");

	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	cout <<8+p->tm_hour;

	string tick="000001";

	string time="9150101000";
	map<string, int> classPoolPtr, classPoolCopy;
	vector<pair<string, vector<string>>>       allTickClass;     /// ���й�Ʊ�ĸ���

	if (stoi(time) < 93000000)
	{
		auto  itrGetPtr = classPoolPtr.find(tick);
		auto  itrGetCopy = classPoolCopy.find(tick);
		if (itrGetPtr != classPoolPtr.end())   ///�Ѵ���
		{
			(*itrGetPtr).second++;
		}
		else
		{
			classPoolPtr.insert(make_pair(tick, 1));

		}

		if (itrGetCopy != classPoolPtr.end())   ///�Ѵ���
		{
			(*itrGetCopy).second++;

		}
		else
		{
			classPoolCopy.insert(make_pair(tick, 1));

		}


	}
	else              ///9:30��Ĵ���
	{
		auto  itrGetCopy = classPoolCopy.find(tick);
		if (itrGetCopy != classPoolPtr.end())   ///�Ѵ���
		{
			(*itrGetCopy).second++;

		}
		else
		{
			classPoolCopy.insert(make_pair(tick, 1));

		}

	}

}

