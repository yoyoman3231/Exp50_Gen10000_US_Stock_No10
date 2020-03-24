/*美股測試*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

ifstream input_file;
ifstream test_input_file;
ofstream output_file;
double all_stock[10000][10000]; //所有股票
double test_all_stock[100][400];
string stock_no[50]; //股票編號
string test_stock_no[50];
int index;
int test_index;
//read_file

double beta[50];
double partical[10][90000];
//int profolio[50];//投資組合
//initial

int stock_index[10][50];//記錄每顆粒子(10)所選到的投資組合(50)
						//choose

int train_stock_index[50];
double initial_fund = 10000000; //初始資金
double test_initial_fund;
double remaind;//剩餘資金
double test_remaind;
double all_remain_fund;
double test_all_remain_fund;
double fund_standardization; //資金水位
double fee; //手續費
double test_fee;
double total_fee[50000];
double one_fund_standardization[50][2500];
double n_fund_standardization[100][50][2500];//各檔資金水位
double test_n_fund_standardization[50][300];//測試期資金水位
double partical_fund_standardization[100][2500];//投資組合資金水位
double risk[10000]; //每日風險
double test_risk;//訓練期每日風險
double final_test_risk;
double m[10000]; //預期報酬
double test_m;
int share_money;//每檔分配的錢
int test_share_money;
double one_of_price; //每張的錢
double test_one_of_price;
double daily_risk[50][10000][10];//每次實驗每代每日風險
double expect_m[50][10000][10];//每次實驗每代預期報酬
double Gbest_daily_risk;//最佳解每日風險
double Gbest_expect_retutn;//最佳解預期報酬

int buy_lots;//可買的張數
int test_buy_lots;
double yi[10000][10000];//第i天真實資金水位
double test_yi[1000];
double all_final_yi[10000];//每一個粒子最後一天的yi
						   //standardization

double m1;
int m2;
double all_standardization[2500];
double Yi[100][300];//一次回歸趨勢線
double test_Yi[300];
double r1;
double trend_ratio;//趨勢值
double test_trend_ratio;
double final_test_trend_ratio;
double all_trend_ratio[10];
//fitness

double theta = 0.0004;
double min_fitness = 0;
double max_fitness = 0;
double max_fitness_aray[100];
int min_fitness_tmp = 0;
int max_fitness_tmp = 0;
int Gbest_tmp = 0;
int t;
//update


int i, j, k, a;
int kind[50];
//double n;
int n[50];//算選的投資組合有幾個
int partical_num = 10;
int generation = 10000;
int experiment_time = 50;
int s_stock_index = 0;//train stock num
int test_stock_index = 0;

int total_n;
int day;
int test_day;
//compare

double all_max = 0;
int all_max_solution[10000];
double random;
int file_num = 28;
double Gbest[50];
double all_max_tmp[50];
double Gbest_max;
int best_experimrentime;
int best_generation;
double real_all_trend_ratio[50][10000][10];
double real_yi[50][10000][10];
double Gbest_yi;
int Gbest_num;//Gbest的出現次數
int final_n[50][10000][10];//存最佳解檔數
int Gbest_n;//Gbest選到的檔數
int Gbest_i;
int selection_stock_no[10][50];
int real_partical[50][10][50];
string final_portfolio[50];
int all_buy_lots[50];//存可買張數的陣列
int last_test_all_buy_paper[50];
int test_all_buy_lots[50];
int all_share_money[10];//存分配資金的陣列
int test_all_share_money[10];
int compare_share_money[50][10000][10];//存每次實驗每個世代每個粒子的分配資金陣列
int compare_buy_lots[50][10][50];//存每個實驗中的組合股票可買張數
int Gbest_share_money;
int Gbest_buy_lots[50];//Gbest組合中股票可買的張數
double real_all_remain_fund[50];
double test_real_all_remain_fund[50];
double compare_remain_fund[50][50];
double Gbest_all_remain_fund[50];//Gbest的買完各股剩餘資金
double all_n_fund_standardization[50][50][300];
double Gbest_n_fund_standardization[50][300];
double all_total_yi[300];
double test_all_total_yi[300];
double test_all_final_fund;
double final_fund[10];
double compare_total_yi[50][300];
double real_total_yi[300];
int total_test_day;
double test_total_yi[100][10000];
double final_total_test_yi[10000];
double test_total_all_period_m;//測試期總體預期報酬
double test_all_period_Yi[10000];
double test_all_period_risk;
double test_all_period_trend_ratio;
double test_all_period_m1;
int test_all_period_m2;
double last_total_std[10000];//存所有測試期總資金水位
double last_total_Yi[10000];//計算總體測試期預期資金水位
double real_last_total_std[100][10000];//存所有測試期總資金水位
int day_count;
double all_test_m;
double final_all_test_m;//總體測試期最終預期報酬
double final_test_m1;
double final_test_m2;
double final_test_r1;
int day_count_risk;//總體測試期計算風險天數counter
int day_count_result;//總體測試期輸出結果天數counter

double all_file_gbest_risk[100];
double all_file_gbest_return[100];
int all_file_gbest_num[100];
int all_file_gbest_generation[100];
int all_file_gbest_experiment[100];
int all_file_gbest_appear[100];
double all_gbest_trend_ratio[100];
string all_file_gbest_portfolio[100][50];

string AAPL[] = { "AAPL-2012.csv", "AAPL-2013.csv", "AAPL-2014.csv", "AAPL-2015.csv", "AAPL-2016.csv", "AAPL-2017.csv", "AAPL-2018.csv", "AAPL-2019.csv" };
string AMZN[] = { "AMZN-2012.csv", "AMZN-2013.csv", "AMZN-2014.csv", "AMZN-2015.csv", "AMZN-2016.csv", "AMZN-2017.csv", "AMZN-2018.csv", "AMZN-2019.csv" };
string BABA[] = { "BABA-2014.csv", "BABA-2015.csv", "BABA-2016.csv", "BABA-2017.csv", "BABA-2018.csv", "BABA-2019.csv" };
string BRKA[] = { "BRK-A-2012.csv", "BRK-A-2013.csv", "BRK-A-2014.csv", "BRK-A-2015.csv", "BRK-A-2016.csv", "BRK-A-2017.csv", "BRK-A-2018.csv", "BRK-A-2019.csv" };
string FB[] = { "FB-2013.csv", "FB-2014.csv", "FB-2015.csv", "FB-2016.csv", "FB-2017.csv", "FB-2018.csv", "FB-2019.csv" };
string GOOG[] = { "GOOG-2012.csv", "GOOG-2013.csv", "GOOG-2014.csv", "GOOG-2015.csv", "GOOG-2016.csv", "GOOG-2017.csv", "GOOG-2018.csv", "GOOG-2019.csv" };
string GOOGL[] = { "GOOGL-2012.csv", "GOOGL-2013.csv", "GOOGL-2014.csv", "GOOGL-2015.csv", "GOOGL-2016.csv", "GOOGL-2017.csv", "GOOGL-2018.csv", "GOOGL-2019.csv" };
string JNJ[] = { "JNJ-2012.csv", "JNJ-2013.csv", "JNJ-2014.csv", "JNJ-2015.csv", "JNJ-2016.csv", "JNJ-2017.csv", "JNJ-2018.csv", "JNJ-2019.csv" };
string JPM[] = { "JPM-2012.csv", "JPM-2013.csv", "JPM-2014.csv", "JPM-2015.csv", "JPM-2016.csv", "JPM-2017.csv", "JPM-2018.csv", "JPM-2019.csv" };
string MSFT[] = { "MSFT-2012.csv", "MSFT-2013.csv", "MSFT-2014.csv", "MSFT-2015.csv", "MSFT-2016.csv", "MSFT-2017.csv", "MSFT-2018.csv", "MSFT-2019.csv" };
string TCEHY[] = { "TCEHY_2012.csv", "TCEHY_2013.csv", "TCEHY_2014.csv", "TCEHY_2015.csv", "TCEHY_2016.csv", "TCEHY_2017.csv", "TCEHY_2018.csv", "TCEHY_2019.csv" };
string V[] = { "V-2012.csv", "V-2013.csv", "V-2014.csv", "V-2015.csv", "V-2016.csv", "V-2017.csv", "V-2018.csv", "V-2019.csv" };
string XOM[] = { "XOM-2012.csv", "XOM-2013.csv", "XOM-2014.csv", "XOM-2015.csv", "XOM-2016.csv", "XOM-2017.csv", "XOM-2018.csv", "XOM-2019.csv" };
string all_US_10[] = { "2012.csv", "2013.csv", "2014.csv", "2015.csv", "2016.csv", "2017.csv", "2018.csv", "2019.csv" };
string all_US_12[] = { "2012.csv", "2013.csv", "2014.csv", "2015.csv", "2016.csv", "2017.csv", "2018.csv", "2019.csv" };
/*美股市值前12大*/
string BRKB[] = { "BRK.B_2012.csv", "BRK.B_2013.csv", "BRK.B_2014.csv", "BRK.B_2015.csv", "BRK.B_2016.csv", "BRK.B_2017.csv", "BRK.B_2018.csv", "BRK.B_2019.csv" };
string CHT[] = { "CHT_2012.csv", "CHT_2013.csv", "CHT_2014.csv", "CHT_2015.csv", "CHT_2016.csv", "CHT_2017.csv", "CHT_2018.csv", "CHT_2019.csv" };
string HD[] = { "HD_2012.csv", "HD_2013.csv", "HD_2014.csv", "HD_2015.csv","HD_2016.csv","HD_2017.csv","HD_2018.csv","HD_2019.csv" };
string MA[] = { "MA_2012.csv","MA_2013.csv","MA_2014.csv","MA_2015.csv","MA_2016.csv","MA_2017.csv","MA_2018.csv","MA_2019.csv" };
string PG[] = { "PG_2012.csv", "PG_2013.csv","PG_2014.csv","PG_2015.csv","PG_2016.csv","PG_2017.csv","PG_2018.csv","PG_2019.csv" };
string SNP[] = { "SNP_2012.csv", "SNP_2013.csv", "SNP_2014.csv", "SNP_2015.csv", "SNP_2016.csv", "SNP_2017.csv", "SNP_2018.csv", "SNP_2019.csv" };
string T[] = { "T_2012.csv", "T_2013.csv", "T_2014.csv", "T_2015.csv", "T_2016.csv", "T_2017.csv", "T_2018.csv", "T_2019.csv" };
string TSM[] = { "TSM_2012.csv", "TSM_2013.csv", "TSM_2014.csv", "TSM_2015.csv", "TSM_2016.csv", "TSM_2017.csv", "TSM_2018.csv", "TSM_2019.csv" };
string UNH[] = { "UNH_2012.csv", "UNH_2013.csv", "UNH_2014.csv", "UNH_2015.csv", "UNH_2016.csv", "UNH_2017.csv", "UNH_2018.csv", "UNH_2019.csv" };
string VOD[] = { "VOD_2012.csv", "VOD_2013.csv", "VOD_2014.csv",  "VOD_2015.csv", "VOD_2016.csv", "VOD_2017.csv", "VOD_2018.csv", "VOD_2019.csv" };
string WMT[] = { "WMT_2012.csv", "WMT_2013.csv", "WMT_2014.csv", "WMT_2015.csv", "WMT_2016.csv", "WMT_2017.csv", "WMT_2018.csv", "WMT_2019.csv" };
string all_US_20[] = { "20_2012.csv", "20_2013.csv", "20_2014.csv", "20_2015.csv", "20_2016.csv", "20_2017.csv", "20_2018.csv", "20_2019.csv" };
/*美股市值前20大*/

string BAC[] = { "BAC_2012.csv",  "BAC_2013.csv", "BAC_2014.csv", "BAC_2015.csv", "BAC_2016.csv", "BAC_2017.csv", "BAC_2018.csv", "BAC_2019.csv" };
string CSCO[] = { "CSCO_2012.csv", "CSCO_2013.csv", "CSCO_2014.csv", "CSCO_2015.csv", "CSCO_2016.csv", "CSCO_2017.csv", "CSCO_2018.csv", "CSCO_2019.csv" };
string INTC[] = { "INTC_2012.csv", "INTC_2013.csv", "INTC_2014.csv", "INTC_2015.csv", "INTC_2016.csv", "INTC_2017.csv", "INTC_2018.csv", "INTC_2019.csv" };
string VZ[] = { "VZ_2012.csv", "VZ_2013.csv", "VZ_2014.csv", "VZ_2015.csv", "VZ_2016.csv", "VZ_2017.csv", "VZ_2018.csv", "VZ_2019.csv" };
string B_all_US_20[] = { "B_20_2012.csv", "B_20_2013.csv", "B_20_2014.csv", "B_20_2015.csv", "B_20_2016.csv", "B_20_2017.csv", "B_20_2018.csv", "B_20_2019.csv" };
string A_all_US_20[] = { "A_20_2012.csv", "A_20_2013.csv", "A_20_2014.csv", "A_20_2015.csv", "A_20_2016.csv", "A_20_2017.csv", "A_20_2018.csv", "A_20_2019.csv" };
string AB_all_US_20[] = { "AB_20_2012.csv", "AB_20_2013.csv", "AB_20_2014.csv", "AB_20_2015.csv", "AB_20_2016.csv", "AB_20_2017.csv", "AB_20_2018.csv", "AB_20_2019.csv" };
string LG_all_US_20[] = { "LG_20_2012.csv", "LG_20_2013.csv", "LG_20_2014.csv", "LG_20_2015.csv", "LG_20_2016.csv", "LG_20_2017.csv", "LG_20_2018.csv", "LG_20_2019.csv" };
/*確認過後的美股市值前20大*/

string Y2Y_train[] = { "train_2012(2012 Q1).csv", "train_2013(2013 Q1).csv", "train_2014(2014 Q1).csv", "train_2015(2015 Q1).csv", "train_2016(2016 Q1).csv", "train_2017(2017 Q1).csv", "train_2018(2018 Q1).csv" };
string Y2Q_train[] = { "train_2012(2012 Q1).csv", "train_2012_Q2~2013_Q1(2012 Q1).csv", "train_2012_Q3~2013_Q2(2012 Q1).csv", "train_2012_Q4~2013_Q3(2012 Q1).csv", "train_2013(2013 Q1).csv", "train_2013_Q2~2014_Q1(2013 Q1).csv",
"train_2013_Q3~2014_Q2(2013 Q1).csv", "train_2013_Q4~2014_Q3(2013 Q1).csv", "train_2014(2014 Q1).csv", "train_2014_Q2~2015_Q1(2014 Q1).csv", "train_2014_Q3~2015_Q2(2014 Q1).csv", "train_2014_Q4~2015_Q3(2014 Q1).csv", "train_2015(2015 Q1).csv",
"train_2015_Q2~2016_Q1(2015 Q1).csv", "train_2015_Q3~2016_Q2(2015 Q1).csv", "train_2015_Q4~2016_Q3(2015 Q1).csv", "train_2016(2016 Q1).csv", "train_2016_Q2~2017_Q1(2016 Q1).csv", "train_2016_Q3~2017_Q2(2016 Q1).csv", "train_2016_Q4~2017_Q3(2016 Q1).csv",
"train_2017(2017 Q1).csv", "train_2017_Q2~2018_Q1(2017 Q1).csv", "train_2017_Q3~2018_Q2(2017 Q1).csv", "train_2017_Q4~2018_Q3(2017 Q1).csv", "train_2018(2018 Q1).csv", "train_2018_Q2~2019_Q1(2018 Q1).csv", "train_2018_Q3~2019_Q2(2018 Q1).csv", "train_2018_Q4~2019_Q3(2018 Q1).csv" };
string Y2M_train[] = { "train_2012(2012 Q1).csv", "train_2012_02~2013_01(2012 Q1).csv", "train_2012_03~2013_02(2012 Q1).csv", "train_2012_04~2013_03(2012 Q1).csv", "train_2012_05~2013_04(2012 Q1).csv", "train_2012_06~2013_05(2012 Q1).csv", "train_2012_07~2013_06(2012 Q1).csv", "train_2012_08~2013_07(2012 Q1).csv", "train_2012_09~2013_08(2012 Q1).csv", "train_2012_10~2013_09(2012 Q1).csv", "train_2012_11~2013_10(2012 Q1).csv", "train_2012_12~2013_11(2012 Q1).csv",
"train_2013(2013 Q1).csv", "train_2013_02~2014_01(2013 Q1).csv", "train_2013_03~2014_02(2013 Q1).csv", "train_2013_04~2014_03(2013 Q1).csv", "train_2013_05~2014_04(2013 Q1).csv", "train_2013_06~2014_05(2013 Q1).csv", "train_2013_07~2014_06(2013 Q1).csv", "train_2013_08~2014_07(2013 Q1).csv", "train_2013_09~2014_08(2013 Q1).csv", "train_2013_10~2014_09(2013 Q1).csv", "train_2013_11~2014_10(2013 Q1).csv", "train_2013_12~2014_11(2013 Q1).csv",
"train_2014(2014 Q1).csv", "train_2014_02~2015_01(2014 Q1).csv", "train_2014_03~2015_02(2014 Q1).csv", "train_2014_04~2015_03(2014 Q1).csv", "train_2014_05~2015_04(2014 Q1).csv", "train_2014_06~2015_05(2014 Q1).csv", "train_2014_07~2015_06(2014 Q1).csv", "train_2014_08~2015_07(2014 Q1).csv", "train_2014_09~2015_08(2014 Q1).csv", "train_2014_10~2015_09(2014 Q1).csv", "train_2014_11~2015_10(2014 Q1).csv", "train_2014_12~2015_11(2014 Q1).csv",
"train_2015(2015 Q1).csv", "train_2015_02~2016_01(2015 Q1).csv", "train_2015_03~2016_02(2015 Q1).csv", "train_2015_04~2016_03(2015 Q1).csv", "train_2015_05~2016_04(2015 Q1).csv", "train_2015_06~2016_05(2015 Q1).csv", "train_2015_07~2016_06(2015 Q1).csv", "train_2015_08~2016_07(2015 Q1).csv", "train_2015_09~2016_08(2015 Q1).csv", "train_2015_10~2016_09(2015 Q1).csv", "train_2015_11~2016_10(2015 Q1).csv", "train_2015_12~2016_11(2015 Q1).csv",
"train_2016(2016 Q1).csv", "train_2016_02~2017_01(2016 Q1).csv", "train_2016_03~2017_02(2016 Q1).csv", "train_2016_04~2017_03(2016 Q1).csv", "train_2016_05~2017_04(2016 Q1).csv", "train_2016_06~2017_05(2016 Q1).csv", "train_2016_07~2017_06(2016 Q1).csv", "train_2016_08~2017_07(2016 Q1).csv", "train_2016_09~2017_08(2016 Q1).csv", "train_2016_10~2017_09(2016 Q1).csv", "train_2016_11~2017_10(2016 Q1).csv", "train_2016_12~2017_11(2016 Q1).csv",
"train_2017(2017 Q1).csv", "train_2017_02~2018_01(2017 Q1).csv", "train_2017_03~2018_02(2017 Q1).csv", "train_2017_04~2018_03(2017 Q1).csv", "train_2017_05~2018_04(2017 Q1).csv", "train_2017_06~2018_05(2017 Q1).csv", "train_2017_07~2018_06(2017 Q1).csv", "train_2017_08~2018_07(2017 Q1).csv", "train_2017_09~2018_08(2017 Q1).csv", "train_2017_10~2018_09(2017 Q1).csv", "train_2017_11~2018_10(2017 Q1).csv", "train_2017_12~2018_11(2017 Q1).csv",
"train_2018(2018 Q1).csv", "train_2018_02~2019_01(2018 Q1).csv", "train_2018_03~2019_02(2018 Q1).csv", "train_2018_04~2019_03(2018 Q1).csv", "train_2018_05~2019_04(2018 Q1).csv", "train_2018_06~2019_05(2018 Q1).csv", "train_2018_07~2019_06(2018 Q1).csv", "train_2018_08~2019_07(2018 Q1).csv", "train_2018_09~2019_08(2018 Q1).csv", "train_2018_10~2019_09(2018 Q1).csv", "train_2018_11~2019_10(2018 Q1).csv", "train_2018_12~2019_11(2018 Q1).csv" };
string Y2H_train[] = { "train_2012(2012 Q1).csv", "train_2012_Q3~2013_Q2(2012 Q1).csv", "train_2013(2013 Q1).csv", "train_2013_Q3~2014_Q2(2013 Q1).csv", "train_2014(2014 Q1).csv", "train_2014_Q3~2015_Q2(2014 Q1).csv", "train_2015(2015 Q1).csv", "train_2015_Q3~2016_Q2(2015 Q1).csv",
"train_2016(2016 Q1).csv", "train_2016_Q3~2017_Q2(2016 Q1).csv", "train_2017(2017 Q1).csv", "train_2017_Q3~2018_Q2(2017 Q1).csv", "train_2018(2018 Q1).csv", "train_2018_Q3~2019_Q2(2018 Q1).csv" };
string H2M_train[] = { "train_2009_07-12(2009 Q1).csv", "train_2009_08~2010_01(2009 Q1).csv", "train_2009_09~2010_02(2009 Q1).csv", "train_2009_10~2010_03(2009 Q1).csv", "train_2009_11~2010_04(2009 Q1).csv", "train_2009_12~2010_05(2009 Q1).csv", "train_2010_01-06(2010 Q1).csv", "train_2010_02-07(2010 Q1).csv", "train_2010_03-08(2010 Q1).csv", "train_2010_04-09(2010 Q1).csv", "train_2010_05-10(2010 Q1).csv", "train_2010_06-11(2010 Q1).csv", "train_2010_07-12(2010 Q1).csv",
"train_2010_08~2011_01(2010 Q1).csv", "train_2010_09~2011_02(2010 Q1).csv", "train_2010_10~2011_03(2010 Q1).csv", "train_2010_11~2011_04(2010 Q1).csv", "train_2010_12~2011_05(2010 Q1).csv", "train_2011_01-06(2011 Q1).csv", "train_2011_02-07(2011 Q1).csv", "train_2011_03-08(2011 Q1).csv", "train_2011_04-09(2011 Q1).csv", "train_2011_05-10(2011 Q1).csv", "train_2011_06-11(2011 Q1).csv", "train_2011_07-12(2011 Q1).csv", "train_2011_08~2012_01(2011 Q1).csv",
"train_2011_09~2012_02(2011 Q1).csv", "train_2011_10~2012_03(2011 Q1).csv", "train_2011_11~2012_04(2011 Q1).csv", "train_2011_12~2012_05(2011 Q1).csv", "train_2012_01-06(2012 Q1).csv", "train_2012_02-07(2012 Q1).csv", "train_2012_03-08(2012 Q1).csv", "train_2012_04-09(2012 Q1).csv", "train_2012_05-10(2012 Q1).csv", "train_2012_06-11(2012 Q1).csv", "train_2012_07-12(2012 Q1).csv", "train_2012_08~2013_01(2012 Q1).csv", "train_2012_09~2013_02(2012 Q1).csv",
"train_2012_10~2013_03(2012 Q1).csv", "train_2012_11~2013_04(2012 Q1).csv", "train_2012_12~2013_05(2012 Q1).csv", "train_2013_01-06(2013 Q1).csv", "train_2013_02-07(2013 Q1).csv", "train_2013_03-08(2013 Q1).csv", "train_2013_04-09(2013 Q1).csv", "train_2013_05-10(2013 Q1).csv", "train_2013_06-11(2013 Q1).csv", "train_2013_07-12(2013 Q1).csv", "train_2013_08~2014_01(2013 Q1).csv", "train_2013_09~2014_02(2013 Q1).csv",
"train_2013_10~2014_03(2013 Q1).csv", "train_2013_11~2014_04(2013 Q1).csv", "train_2013_12~2014_05(2013 Q1).csv", "train_2014_01-06(2014 Q1).csv", "train_2014_02-07(2014 Q1).csv", "train_2014_03-08(2014 Q1).csv", "train_2014_04-09(2014 Q1).csv", "train_2014_05-10(2014 Q1).csv", "train_2014_06-11(2014 Q1).csv", "train_2014_07-12(2014 Q1).csv", "train_2014_08~2015_01(2014 Q1).csv", "train_2014_09~2015_02(2014 Q1).csv", "train_2014_10~2015_03(2014 Q1).csv",
"train_2014_11~2015_04(2014 Q1).csv", "train_2014_12~2015_05(2014 Q1).csv", "train_2015_01-06(2015 Q1).csv", "train_2015_02-07(2015 Q1).csv", "train_2015_03-08(2015 Q1).csv", "train_2015_04-09(2015 Q1).csv", "train_2015_05-10(2015 Q1).csv", "train_2015_06-11(2015 Q1).csv", "train_2015_07-12(2015 Q1).csv", "train_2015_08~2016_01(2015 Q1).csv", "train_2015_09~2016_02(2015 Q1).csv", "train_2015_10~2016_03(2015 Q1).csv", "train_2015_11~2016_04(2015 Q1).csv",
"train_2015_12~2016_05(2015 Q1).csv", "train_2016_01-06(2016 Q1).csv", "train_2016_02-07(2016 Q1).csv", "train_2016_03-08(2016 Q1).csv", "train_2016_04-09(2016 Q1).csv", "train_2016_05-10(2016 Q1).csv", "train_2016_06-11(2016 Q1).csv", "train_2016_07-12(2016 Q1).csv", "train_2016_08~2017_01(2016 Q1).csv", "train_2016_09~2017_02(2016 Q1).csv", "train_2016_10~2017_03(2016 Q1).csv", "train_2016_11~2017_04(2016 Q1).csv", "train_2016_12~2017_05(2016 Q1).csv",
"train_2017_01-06(2017 Q1).csv", "train_2017_02-07(2017 Q1).csv", "train_2017_03-08(2017 Q1).csv", "train_2017_04-09(2017 Q1).csv", "train_2017_05-10(2017 Q1).csv", "train_2017_06-11(2017 Q1).csv" };
string H2Q_train[] = { "train_2009_Q3-Q4(2009 Q1).csv", "train_2009_Q4~2010_Q1(2009 Q1).csv", "train_2010_Q1-Q2(2010 Q1).csv", "train_2010_Q2-Q3(2010 Q1).csv", "train_2010_Q3-Q4(2010 Q1).csv", "train_2010_Q4~2011_Q1(2010 Q1).csv", "train_2011_Q1-Q2(2011 Q1).csv", "train_2011_Q2-Q3(2011 Q1).csv", "train_2011_Q3-Q4(2011 Q1).csv", "train_2011_Q4~2012_Q1(2011 Q1).csv", "train_2012_Q1-Q2(2012 Q1).csv", "train_2012_Q2-Q3(2012 Q1).csv", "train_2012_Q3-Q4(2012 Q1).csv", "train_2012_Q4~2013_Q1(2012 Q1).csv",
"train_2013_Q1-Q2(2013 Q1).csv", "train_2013_Q2-Q3(2013 Q1).csv", "train_2013_Q3-Q4(2013 Q1).csv", "train_2013_Q4~2014_Q1(2013 Q1).csv", "train_2014_Q1-Q2(2014 Q1).csv", "train_2014_Q2-Q3(2014 Q1).csv", "train_2014_Q3-Q4(2014 Q1).csv", "train_2014_Q4~2015_Q1(2014 Q1).csv", "train_2015_Q1-Q2(2015 Q1).csv", "train_2015_Q2-Q3(2015 Q1).csv", "train_2015_Q3-Q4(2015 Q1).csv", "train_2015_Q4~2016_Q1(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv", "train_2016_Q2-Q3(2016 Q1).csv",
"train_2016_Q3-Q4(2016 Q1).csv", "train_2016_Q4~2017_Q1(2016 Q1).csv", "train_2017_Q1-Q2(2017 Q1).csv", "train_2017_Q2-Q3(2017 Q1).csv" };
string Q2M_train[] = { "train_2009_10-12(2009 Q1).csv", "train_2009_11~2010_01(2009 Q1).csv", "train_2009_12~2010_02(2009 Q1).csv", "train_2010_01-03(2010 Q1).csv", "train_2010_02-04(2010 Q1).csv", "train_2010_03-05(2010 Q1).csv", "train_2010_04-06(2010 Q1).csv", "train_2010_05-07(2010 Q1).csv", "train_2010_06-08(2010 Q1).csv", "train_2010_07-09(2010 Q1).csv", "train_2010_08-10(2010 Q1).csv", "train_2010_09-11(2010 Q1).csv", "train_2010_10-12(2010 Q1).csv", "train_2010_11~2011_01(2010 Q1).csv",
"train_2010_12~2011_02(2010 Q1).csv", "train_2011_01-03(2011 Q1).csv", "train_2011_02-04(2011 Q1).csv", "train_2011_03-05(2011 Q1).csv", "train_2011_04-06(2011 Q1).csv", "train_2011_05-07(2011 Q1).csv", "train_2011_06-08(2011 Q1).csv", "train_2011_07-09(2011 Q1).csv", "train_2011_08-10(2011 Q1).csv", "train_2011_09-11(2011 Q1).csv", "train_2011_10-12(2011 Q1).csv", "train_2011_11~2012_01(2011 Q1).csv", "train_2011_12~2012_02(2011 Q1).csv", "train_2012_01-03(2012 Q1).csv",
"train_2012_02-04(2012 Q1).csv", "train_2012_03-05(2012 Q1).csv", "train_2012_04-06(2012 Q1).csv", "train_2012_05-07(2012 Q1).csv", "train_2012_06-08(2012 Q1).csv", "train_2012_07-09(2012 Q1).csv", "train_2012_08-10(2012 Q1).csv", "train_2012_09-11(2012 Q1).csv", "train_2012_10-12(2012 Q1).csv", "train_2012_11~2013_01(2012 Q1).csv", "train_2012_12~2013_02(2012 Q1).csv", "train_2013_01-03(2013 Q1).csv", "train_2013_02-04(2013 Q1).csv", "train_2013_03-05(2013 Q1).csv",
"train_2013_04-06(2013 Q1).csv", "train_2013_05-07(2013 Q1).csv", "train_2013_06-08(2013 Q1).csv", "train_2013_07-09(2013 Q1).csv", "train_2013_08-10(2013 Q1).csv", "train_2013_09-11(2013 Q1).csv", "train_2013_10-12(2013 Q1).csv", "train_2013_11~2014_01(2013 Q1).csv", "train_2013_12~2014_02(2013 Q1).csv", "train_2014_01-03(2014 Q1).csv", "train_2014_02-04(2014 Q1).csv", "train_2014_03-05(2014 Q1).csv", "train_2014_04-06(2014 Q1).csv", "train_2014_05-07(2014 Q1).csv",
"train_2014_06-08(2014 Q1).csv", "train_2014_07-09(2014 Q1).csv", "train_2014_08-10(2014 Q1).csv", "train_2014_09-11(2014 Q1).csv", "train_2014_10-12(2014 Q1).csv", "train_2014_11~2015_01(2014 Q1).csv", "train_2014_12~2015_02(2014 Q1).csv", "train_2015_01-03(2015 Q1).csv", "train_2015_02-04(2015 Q1).csv", "train_2015_03-05(2015 Q1).csv", "train_2015_04-06(2015 Q1).csv", "train_2015_05-07(2015 Q1).csv", "train_2015_06-08(2015 Q1).csv", "train_2015_07-09(2015 Q1).csv",
"train_2015_08-10(2015 Q1).csv", "train_2015_09-11(2015 Q1).csv", "train_2015_10-12(2015 Q1).csv", "train_2015_11~2016_01(2015 Q1).csv", "train_2015_12~2016_02(2015 Q1).csv", "train_2016_01-03(2016 Q1).csv", "train_2016_02-04(2016 Q1).csv", "train_2016_03-05(2016 Q1).csv", "train_2016_04-06(2016 Q1).csv", "train_2016_05-07(2016 Q1).csv", "train_2016_06-08(2016 Q1).csv", "train_2016_07-09(2016 Q1).csv", "train_2016_08-10(2016 Q1).csv", "train_2016_09-11(2016 Q1).csv",
"train_2016_10-12(2016 Q1).csv", "train_2016_11~2017_01(2016 Q1).csv", "train_2016_12~2017_02(2016 Q1).csv", "train_2017_01-03(2017 Q1).csv", "train_2017_02-04(2017 Q1).csv", "train_2017_03-05(2017 Q1).csv", "train_2017_04-06(2017 Q1).csv", "train_2017_05-07(2017 Q1).csv", "train_2017_06-08(2017 Q1).csv", "train_2017_07-09(2017 Q1).csv", "train_2017_08-10(2017 Q1).csv", "train_2017_09-11(2017 Q1).csv" };
string QQ_train[] = { "train_2009_Q1(2009 Q1).csv", "train_2009_Q2(2009 Q1).csv", "train_2009_Q3(2009 Q1).csv", "train_2009_Q4(2009 Q1).csv", "train_2010_Q1(2010 Q1).csv", "train_2010_Q2(2010 Q1).csv", "train_2010_Q3(2010 Q1).csv", "train_2010_Q4(2010 Q1).csv", "train_2011_Q1(2011 Q1).csv", "train_2011_Q2(2011 Q1).csv", "train_2011_Q3(2011 Q1).csv", "train_2011_Q4(2011 Q1).csv", "train_2012_Q1(2012 Q1).csv", "train_2012_Q2(2012 Q1).csv", "train_2012_Q3(2012 Q1).csv", "train_2012_Q4(2012 Q1).csv",
"train_2013_Q1(2013 Q1).csv", "train_2013_Q2(2013 Q1).csv", "train_2013_Q3(2013 Q1).csv", "train_2013_Q4(2013 Q1).csv", "train_2014_Q1(2014 Q1).csv", "train_2014_Q2(2014 Q1).csv", "train_2014_Q3(2014 Q1).csv", "train_2014_Q4(2014 Q1).csv", "train_2015_Q1(2015 Q1).csv", "train_2015_Q2(2015 Q1).csv", "train_2015_Q3(2015 Q1).csv", "train_2015_Q4(2015 Q1).csv", "train_2016_Q1(2016 Q1).csv", "train_2016_Q2(2016 Q1).csv", "train_2016_Q3(2016 Q1).csv", "train_2016_Q4(2016 Q1).csv" };
string HH_train[] = { "train_2009_Q1-Q2(2009 Q1).csv", "train_2009_Q3-Q4(2009 Q1).csv", "train_2010_Q1-Q2(2010 Q1).csv", "train_2010_Q3-Q4(2010 Q1).csv", "train_2011_Q1-Q2(2011 Q1).csv", "train_2011_Q3-Q4(2011 Q1).csv", "train_2012_Q1-Q2(2012 Q1).csv", "train_2012_Q3-Q4(2012 Q1).csv", "train_2013_Q1-Q2(2013 Q1).csv", "train_2013_Q3-Q4(2013 Q1).csv", "train_2014_Q1-Q2(2014 Q1).csv", "train_2014_Q3-Q4(2014 Q1).csv", "train_2015_Q1-Q2(2015 Q1).csv", "train_2015_Q3-Q4(2015 Q1).csv", "train_2016_Q1-Q2(2016 Q1).csv", "train_2016_Q3-Q4(2016 Q1).csv" };
string MM_train[] = { "train_2009_01(2009 Q1).csv", "train_2009_02(2009 Q1).csv", "train_2009_03(2009 Q1).csv", "train_2009_04(2009 Q1).csv", "train_2009_05(2009 Q1).csv", "train_2009_06(2009 Q1).csv", "train_2009_07(2009 Q1).csv", "train_2009_08(2009 Q1).csv", "train_2009_09(2009 Q1).csv", "train_2009_10(2009 Q1).csv", "train_2009_11(2009 Q1).csv", "train_2009_12(2009 Q1).csv", "train_2010_01(2010 Q1).csv", "train_2010_02(2010 Q1).csv", "train_2010_03(2010 Q1).csv", "train_2010_04(2010 Q1).csv", "train_2010_05(2010 Q1).csv",
"train_2010_06(2010 Q1).csv", "train_2010_07(2010 Q1).csv", "train_2010_08(2010 Q1).csv", "train_2010_09(2010 Q1).csv", "train_2010_10(2010 Q1).csv", "train_2010_11(2010 Q1).csv", "train_2010_12(2010 Q1).csv", "train_2011_01(2011 Q1).csv", "train_2011_02(2011 Q1).csv", "train_2011_03(2011 Q1).csv", "train_2011_04(2011 Q1).csv", "train_2011_05(2011 Q1).csv", "train_2011_06(2011 Q1).csv", "train_2011_07(2011 Q1).csv", "train_2011_08(2011 Q1).csv", "train_2011_09(2011 Q1).csv", "train_2011_10(2011 Q1).csv",
"train_2011_11(2011 Q1).csv", "train_2011_12(2011 Q1).csv", "train_2012_01(2012 Q1).csv", "train_2012_02(2012 Q1).csv", "train_2012_03(2012 Q1).csv", "train_2012_04(2012 Q1).csv", "train_2012_05(2012 Q1).csv", "train_2012_06(2012 Q1).csv", "train_2012_07(2012 Q1).csv", "train_2012_08(2012 Q1).csv", "train_2012_09(2012 Q1).csv", "train_2012_10(2012 Q1).csv", "train_2012_11(2012 Q1).csv", "train_2012_12(2012 Q1).csv", "train_2013_01(2013 Q1).csv", "train_2013_02(2013 Q1).csv", "train_2013_03(2013 Q1).csv",
"train_2013_04(2013 Q1).csv", "train_2013_05(2013 Q1).csv", "train_2013_06(2013 Q1).csv", "train_2013_07(2013 Q1).csv", "train_2013_08(2013 Q1).csv", "train_2013_09(2013 Q1).csv", "train_2013_10(2013 Q1).csv", "train_2013_11(2013 Q1).csv", "train_2013_12(2013 Q1).csv", "train_2014_01(2014 Q1).csv", "train_2014_02(2014 Q1).csv", "train_2014_03(2014 Q1).csv", "train_2014_04(2014 Q1).csv", "train_2014_05(2014 Q1).csv", "train_2014_06(2014 Q1).csv", "train_2014_07(2014 Q1).csv", "train_2014_08(2014 Q1).csv",
"train_2014_09(2014 Q1).csv", "train_2014_10(2014 Q1).csv", "train_2014_11(2014 Q1).csv", "train_2014_12(2014 Q1).csv", "train_2015_01(2015 Q1).csv", "train_2015_02(2015 Q1).csv", "train_2015_03(2015 Q1).csv", "train_2015_04(2015 Q1).csv", "train_2015_05(2015 Q1).csv", "train_2015_06(2015 Q1).csv", "train_2015_07(2015 Q1).csv", "train_2015_08(2015 Q1).csv", "train_2015_09(2015 Q1).csv", "train_2015_10(2015 Q1).csv", "train_2015_11(2015 Q1).csv", "train_2015_12(2015 Q1).csv", "train_2016_01(2016 Q1).csv",
"train_2016_02(2016 Q1).csv", "train_2016_03(2016 Q1).csv", "train_2016_04(2016 Q1).csv", "train_2016_05(2016 Q1).csv", "train_2016_06(2016 Q1).csv", "train_2016_07(2016 Q1).csv", "train_2016_08(2016 Q1).csv", "train_2016_09(2016 Q1).csv", "train_2016_10(2016 Q1).csv", "train_2016_11(2016 Q1).csv", "train_2016_12(2016 Q1).csv" };
/*訓練期*/

string Y2Y_test[] = { "test_2013(2012 Q1).csv", "test_2014(2013 Q1).csv", "test_2015(2014 Q1).csv", "test_2016(2015 Q1).csv", "test_2017(2016 Q1).csv", "test_2018(2017 Q1).csv", "test_2019(2018 Q1).csv" };
string Y2Q_test[] = { "test_2013_Q1(2012 Q1).csv", "test_2013_Q2(2012 Q1).csv", "test_2013_Q3(2012 Q1).csv", "test_2013_Q4(2012 Q1).csv", "test_2014_Q1(2013 Q1).csv","test_2014_Q2(2013 Q1).csv", "test_2014_Q3(2013 Q1).csv", "test_2014_Q4(2013 Q1).csv", "test_2015_Q1(2014 Q1).csv", "test_2015_Q2(2014 Q1).csv", "test_2015_Q3(2014 Q1).csv", "test_2015_Q4(2014 Q1).csv", "test_2016_Q1(2015 Q1).csv", "test_2016_Q2(2015 Q1).csv", "test_2016_Q3(2015 Q1).csv", "test_2016_Q4(2015 Q1).csv",
"test_2017_Q1(2016 Q1).csv", "test_2017_Q2(2016 Q1).csv", "test_2017_Q3(2016 Q1).csv", "test_2017_Q4(2016 Q1).csv", "test_2018_Q1(2017 Q1).csv", "test_2018_Q2(2017 Q1).csv", "test_2018_Q3(2017 Q1).csv", "test_2018_Q4(2017 Q1).csv", "test_2019_Q1(2018 Q1).csv", "test_2019_Q2(2018 Q1).csv", "test_2019_Q3(2018 Q1).csv", "test_2019_Q4(2018 Q1).csv" };
string Y2M_test[] = { "test_2012_12(2011 Q1).csv", "test_2013_01(2012 Q1).csv", "test_2013_02(2012 Q1).csv", "test_2013_03(2012 Q1).csv", "test_2013_04(2012 Q1).csv", "test_2013_05(2012 Q1).csv", "test_2013_06(2012 Q1).csv", "test_2013_07(2012 Q1).csv", "test_2013_08(2012 Q1).csv", "test_2013_09(2012 Q1).csv", "test_2013_10(2012 Q1).csv", "test_2013_11(2012 Q1).csv", "test_2013_12(2012 Q1).csv", "test_2014_01(2013 Q1).csv", "test_2014_02(2013 Q1).csv", "test_2014_03(2013 Q1).csv", "test_2014_04(2013 Q1).csv", "test_2014_05(2013 Q1).csv",
"test_2014_06(2013 Q1).csv", "test_2014_07(2013 Q1).csv", "test_2014_08(2013 Q1).csv", "test_2014_09(2013 Q1).csv", "test_2014_10(2013 Q1).csv", "test_2014_11(2013 Q1).csv", "test_2014_12(2013 Q1).csv", "test_2015_01(2014 Q1).csv", "test_2015_02(2014 Q1).csv", "test_2015_03(2014 Q1).csv", "test_2015_04(2014 Q1).csv", "test_2015_05(2014 Q1).csv", "test_2015_06(2014 Q1).csv", "test_2015_07(2014 Q1).csv", "test_2015_08(2014 Q1).csv", "test_2015_09(2014 Q1).csv", "test_2015_10(2014 Q1).csv", "test_2015_11(2014 Q1).csv",
"test_2015_12(2014 Q1).csv", "test_2016_01(2015 Q1).csv", "test_2016_02(2015 Q1).csv", "test_2016_03(2015 Q1).csv", "test_2016_04(2015 Q1).csv", "test_2016_05(2015 Q1).csv", "test_2016_06(2015 Q1).csv", "test_2016_07(2015 Q1).csv", "test_2016_08(2015 Q1).csv", "test_2016_09(2015 Q1).csv", "test_2016_10(2015 Q1).csv", "test_2016_11(2015 Q1).csv", "test_2016_12(2015 Q1).csv", "test_2017_01(2016 Q1).csv", "test_2017_02(2016 Q1).csv", "test_2017_03(2016 Q1).csv", "test_2017_04(2016 Q1).csv", "test_2017_05(2016 Q1).csv",
"test_2017_06(2016 Q1).csv", "test_2017_07(2016 Q1).csv", "test_2017_08(2016 Q1).csv", "test_2017_09(2016 Q1).csv", "test_2017_10(2016 Q1).csv", "test_2017_11(2016 Q1).csv", "test_2017_12(2016 Q1).csv", "test_2018_01(2017 Q1).csv", "test_2018_02(2017 Q1).csv", "test_2018_03(2017 Q1).csv", "test_2018_04(2017 Q1).csv", "test_2018_05(2017 Q1).csv", "test_2018_06(2017 Q1).csv", "test_2018_07(2017 Q1).csv", "test_2018_08(2017 Q1).csv", "test_2018_09(2017 Q1).csv", "test_2018_10(2017 Q1).csv", "test_2018_11(2017 Q1).csv",
"test_2018_12(2017 Q1).csv", "test_2019_01(2018 Q1).csv", "test_2019_02(2018 Q1).csv", "test_2019_03(2018 Q1).csv", "test_2019_04(2018 Q1).csv", "test_2019_05(2018 Q1).csv", "test_2019_06(2018 Q1).csv", "test_2019_07(2018 Q1).csv", "test_2019_08(2018 Q1).csv", "test_2019_09(2018 Q1).csv", "test_2019_10(2018 Q1).csv", "test_2019_11(2018 Q1).csv", "test_2019_12(2018 Q1).csv" };

void read_file(int a) {

	input_file.open(Y2Q_train[a], ios::in);
	cout << endl << Y2Q_train[a] << endl;
	string line;
	while (getline(input_file, line))
	{
		s_stock_index = 0;
		string tmp;
		stringstream ss(line);
		if (index == 0)
		{
			while (getline(ss, tmp, ','))
			{
				string num;
				num = tmp;
				stock_no[s_stock_index] = num; //編號
											   //cout << stock_no[s_stock_index] << endl;
				s_stock_index++;
			}
			index++;
		}
		else if (index > 0)
		{
			s_stock_index = 0;
			while (getline(ss, tmp, ','))
			{
				stringstream price;
				price << tmp;
				price >> all_stock[s_stock_index][index - 1];//股價
				s_stock_index++;
			}
			index++;
		}
	}
	input_file.close();
	day = index - 1;
}//讀檔

void test_read_file(int a) {

	test_input_file.open(Y2Q_test[a], ios::in);
	cout << endl << Y2Q_test[a] << endl;
	string test_line;
	while (getline(test_input_file, test_line))
	{
		test_stock_index = 0;
		string test_tmp;
		stringstream test_ss(test_line);
		if (test_index == 0)
		{
			while (getline(test_ss, test_tmp, ','))
			{
				stringstream test_num;
				test_num << test_tmp;
				test_num >> test_stock_no[test_stock_index];//編號
															//cout << test_stock_no[test_stock_index] << endl;
				test_stock_index++;
			}
			test_index++;
		}
		else if (test_index > 0)
		{
			test_stock_index = 0;
			while (getline(test_ss, test_tmp, ','))
			{
				stringstream test_price;
				test_price << test_tmp;
				test_price >> test_all_stock[test_stock_index][test_index - 1];//股價
				test_stock_index++;
			}
			test_index++;
		}
	}
	test_input_file.close();
	test_day = test_index - 1;
	total_test_day += test_day;
}//讀檔

void initial()
{
	for (int i = 0; i < s_stock_index; i++)
	{
		beta[i] = 0.5;
	}
}

void  measure()
{
	//cout << s_stock_index << endl;
	for (int i = 0; i < partical_num; i++) {
		n[i] = 0;//千萬不能刪
		for (int j = 0; j < s_stock_index; j++) {

			random = rand() / 32767.0;
			if (random < beta[j]) {
				partical[i][j] = 1;
			}
			else partical[i][j] = 0;//隨機給0或1
									/*if (j == 0)
									{
									partical[i][j] = 1;
									}
									else partical[i][j] = 0;*/

			if (partical[i][j] == 1)
			{
				stock_index[i][n[i]] = j;
				//cout << stock_no[stock_index[i][n[i]]] << endl; //股票編號
				//cout << stock_index[i][n[i]]  << endl;//選到的股票 index
				n[i] = n[i]++;//幾檔
			}

		}

	}
}

void standardization()
{
	for (int i = 0; i < partical_num; i++)
	{
		share_money = initial_fund / n[i];//每次選擇後平均每檔的資金,不要刪!!!!
		all_share_money[i] = share_money;//把每個粒子的分配資金存起來
		remaind = initial_fund - share_money * n[i];//投資組合分配完剩下的錢
		for (int j = 0; j < n[i]; j++) {
			all_buy_lots[j] = 0;
			real_all_remain_fund[j] = 0;
			for (int k = 0; k < day; k++) {
				n_fund_standardization[i][j][k] = 0;
				if (k == 0)
				{
					buy_lots = share_money / all_stock[stock_index[i][j]][k];//能夠買幾股
																			 //buy_papper = share_money / (all_stock[stock_index[i][j]][k] * 1000.0 + all_stock[stock_index[i][j]][k] * 1.425);//可買張數
					all_buy_lots[j] = buy_lots;
					all_remain_fund = share_money - buy_lots * all_stock[stock_index[i][j]][k];
					real_all_remain_fund[j] = all_remain_fund;//把買完各股剩餘資金存入陣列中進行判斷
															  //fee = all_stock[stock_index[i][j]][k] * buy_papper * 1000 * fee_rate;//手續費 v
					n_fund_standardization[i][j][k] = share_money;
					//n_fund_standardization[i][j][k] = share_money - all_stock[stock_index[i][j]][k] * buy_papper * 1000 * fee_rate;//資金水位 v

				}
				else
				{
					n_fund_standardization[i][j][k] = all_stock[stock_index[i][j]][k] * buy_lots + all_remain_fund;
					/*n_fund_standardization[i][j][k] = all_stock[stock_index[i][j]][k] * buy_papper -
					all_stock[stock_index[i][j]][k] * buy_papper * 1000 * fee_rate - buy_papper * all_stock[stock_index[i][j]][k] * 1000 * tax_rate + all_remain_fund;*/

				}
				if (share_money < 0)
				{
					n_fund_standardization[i][j][k] = 0;
				}
			}

		}

		for (int k = 0; k < day; k++)
		{
			yi[i][k] = 0;
			//all_total_yi[k] = 0;
			for (int j = 0; j < n[i]; j++)
			{
				yi[i][k] += n_fund_standardization[i][j][k];//yi total
			}
			yi[i][k] = yi[i][k] + remaind;//v
			all_total_yi[k] = yi[i][k];
		}
	}
}


void test_standardization(int a)//測試期資金水位計算
{
	test_share_money = test_initial_fund / Gbest_n;//每次選擇後平均每檔的資金,不要刪!!!!
	test_remaind = test_initial_fund - test_share_money * Gbest_n;//投資組合分配完剩下的錢


	for (int v = 0; v < s_stock_index; v++)
	{
		if (final_portfolio[v] != "/0")
		{
			for (int s = 0; s < test_stock_index; s++)
			{
				//cout << test_stock_no[s] << endl;
				/*if (final_portfolio[v] == test_stock_no[s])
				{*/
				//cout << s << endl;
				for (int k = 0; k < test_day; k++) {
					//	test_all_stock[s][k] = 0;
					if (k == 0)
					{
						//test_one_of_price = test_all_stock[s][k] * 1000 + test_all_stock[s][k] * 1.425;//單張價格
						test_buy_lots = test_share_money / test_all_stock[s][k];//可買張數
						test_all_buy_lots[s] = test_buy_lots;
						test_all_remain_fund = test_share_money - test_buy_lots * test_all_stock[s][k];//買完各股剩餘資金
						test_real_all_remain_fund[s] = test_all_remain_fund;//把買完各股剩餘資金存入陣列中進行判斷;
						test_n_fund_standardization[s][k] = test_share_money;//資金水位 
					}
					else
					{
						test_n_fund_standardization[s][k] = test_all_stock[s][k] * test_buy_lots + test_all_remain_fund;
					}
				}
				//}
			}

		}
	}

	for (int k = 0; k < test_day; k++)
	{
		test_yi[k] = 0;

		for (int v = 0; v < s_stock_index; v++)
		{
			/*if (final_portfolio[v] != 0)
			{*/
			for (int s = 0; s < test_stock_index; s++)
			{
				if (final_portfolio[v] == test_stock_no[s])
				{
					test_yi[k] = test_yi[k] + test_n_fund_standardization[s][k];//yi total
				}
			}
			//}
		}

		test_yi[k] += test_remaind;
		test_all_total_yi[k] = test_yi[k];
		test_all_final_fund = test_yi[test_day - 1];
		real_last_total_std[a][k] = test_yi[k];
	}
}

void all_test_return()
{
	for (int k = 0; k < test_day; k++)
	{
		for (int d = 0; d < total_test_day; d++)
		{
			last_total_std[d] = test_yi[k];

			if (last_total_std[d] != 0)
			{
				day_count++;
			}
			final_test_m1 += ((day_count * last_total_std[d]) - (day_count * initial_fund));
			final_test_m2 += day_count * day_count;
			all_test_m = final_test_m1 / final_test_m2;
			break;
		}
	}

	final_all_test_m = all_test_m;
}

void all_test_risk()
{
	for (int a = 0; a < file_num; a++)
	{
		for (int d = 0; d < total_test_day; d++)
		{
			if (real_last_total_std[a][d] != 0)
			{
				day_count_risk++;//累加存入陣列中不為0的項目,並當作總天數使用
				last_total_Yi[d] = (all_test_m * day_count_risk) + initial_fund;
				final_test_r1 += ((real_last_total_std[a][d] - last_total_Yi[d]) * (real_last_total_std[a][d] - last_total_Yi[d]));//(yi-Yi)
			}
		}
	}
	final_test_risk = sqrt(final_test_r1 / (day_count_risk));
	if (all_test_m < 0)
	{
		final_test_trend_ratio = all_test_m * final_test_risk;
	}
	else if (all_test_m > 0)
	{
		final_test_trend_ratio = all_test_m / final_test_risk;//趨勢值
	}
	cout << "整體預期報酬: " << final_all_test_m << endl;
	cout << "整體風險:" << final_test_risk << endl;
	cout << "整體趨勢值: " << final_test_trend_ratio << endl;
}

void test_fitness()//計算測試期各區間趨勢值
{
	double test_m1 = 0;
	double test_m2 = 0;

	for (int k = 0; k < test_day; k++)
	{
		test_m1 += (((k + 1) * test_yi[k]) - ((k + 1) * test_initial_fund));
		test_m2 += (k + 1) * (k + 1);
	}

	test_m = test_m1 / test_m2;//v


	double test_r1 = 0;

	for (int k = 0; k < test_day; k++)
	{
		test_Yi[k] = 0;
		test_Yi[k] = test_m * (k + 1) + test_initial_fund;//一次回歸趨勢線//v
		test_r1 += ((test_yi[k] - test_Yi[k]) * (test_yi[k] - test_Yi[k]));//(yi-Yi)
	}
	test_risk = sqrt(test_r1 / (test_day));//風險

	if (test_m < 0)
	{
		test_trend_ratio = test_m * test_risk;
	}
	else if (test_m > 0)
	{
		test_trend_ratio = test_m / test_risk;//趨勢值
	}
}

void fitness()
{
	for (int i = 0; i < partical_num; i++)
	{
		m1 = 0;
		m2 = 0;
		m[i] = 0;

		for (int k = 0; k < day; k++)
		{
			m1 += (((k + 1) * yi[i][k]) - ((k + 1) * initial_fund));
			m2 += (k + 1) * (k + 1);
		}
		m[i] = m1 / m2;//v
	}

	for (int i = 0; i < partical_num; i++) {
		risk[i] = 0;
		r1 = 0;
		for (int k = 0; k < day; k++)
		{
			Yi[i][k] = 0;
			Yi[i][k] = m[i] * (k + 1) + initial_fund;//一次回歸趨勢線//v
			r1 += ((yi[i][k] - Yi[i][k]) * (yi[i][k] - Yi[i][k]));//(yi-Yi)
		}
		risk[i] = sqrt(r1 / (day));//風險

		if (m[i] < 0)
		{
			trend_ratio = m[i] * risk[i];
		}
		else if (m[i] > 0)
		{
			trend_ratio = m[i] / risk[i];//趨勢值
		}
		all_trend_ratio[i] = trend_ratio;
	}

}

void compare()
{
	max_fitness = all_trend_ratio[0];//如果這邊設成0,找到的不一定是當代粒子的最大值。(如果當代粒子都是負的)
	max_fitness_tmp = 0;
	for (int i = 0; i < partical_num; i++)
	{
		if (max_fitness < all_trend_ratio[i])
		{
			max_fitness = all_trend_ratio[i];
			max_fitness_tmp = i;
		}
	}
	min_fitness = max_fitness;

	for (int i = 0; i < partical_num; i++)
	{

		if (min_fitness > all_trend_ratio[i])
		{
			min_fitness = all_trend_ratio[i];
			min_fitness_tmp = i;
		}
	}//找Best&Worst

	if (max_fitness > all_max)
	{
		all_max = max_fitness;
		for (int k = 0; k < s_stock_index; k++)
		{
			all_max_solution[k] = partical[max_fitness_tmp][k];
		}
	}//Gbest

	if (all_max <= 0)
	{
		for (int k = 0; k < s_stock_index; k++)
		{
			all_max_solution[k] = 0;
		}
	}

	for (int k = 0; k < s_stock_index; k++) {
		if (all_max_solution[k] == 0 && partical[min_fitness_tmp][k] == 1)
		{
			if (beta[k] > 0.5)
			{
				beta[k] = 1 - beta[k];
				beta[k] = beta[k] - theta;
			}

			else if (beta[k] <= 0.5)
			{
				beta[k] = beta[k] - theta;
			}
		}
		if (all_max_solution[k] == 1 && partical[min_fitness_tmp][k] == 0)
		{
			if (beta[k] < 0.5)
			{
				beta[k] = 1 - beta[k];
				beta[k] = beta[k] + theta;
			}
			else if (beta[k] >= 0.5)
			{
				beta[k] = beta[k] + theta;
			}
		}
	}
}

void experiment_compre() /*50次實驗Gbest比較,並找出Gbest的實驗數*/
{
	Gbest_max = all_max_tmp[0];
	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max <= all_max_tmp[j])
		{
			Gbest_max = all_max_tmp[j];
		}//找50次實驗的Gbest,如果只有一次實驗可註解
	}

	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max == all_max_tmp[j])
		{
			best_experimrentime = j + 1;//找最佳解實驗次數
			break;
		}
	}
}

void Gbest_num_find()//找Gbest於實驗次數中出現的次數
{
	Gbest_num = 0;
	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max == all_max_tmp[j])
		{
			Gbest_num += 1;
		}
	}
}

void generation_compare()
{
	for (int j = 0; j < experiment_time; j++)
	{
		for (int t = 0; t < generation; t++)
		{
			for (int i = 0; i < partical_num; i++)
			{
				if (Gbest_max == real_all_trend_ratio[j][t][i])
				{
					best_generation = t + 1;//最佳解世代數
					Gbest_daily_risk = daily_risk[j][t][i];//最佳解風險
					Gbest_expect_retutn = expect_m[j][t][i];//最佳解預期報酬
					Gbest_n = final_n[j][t][i];
					Gbest_share_money = compare_share_money[j][t][i];
					Gbest_i = i;
					for (int k = 0; k < Gbest_n; k++)
					{
						Gbest_all_remain_fund[k] = 0;
						Gbest_buy_lots[k] = compare_buy_lots[j][i][k];//可買張數
						Gbest_all_remain_fund[k] = compare_remain_fund[j][k];
						for (int d = 0; d < day; d++)
						{
							Gbest_n_fund_standardization[k][d] = all_n_fund_standardization[j][k][d];
						}
					}
					for (int d = 0; d < day; d++)
					{
						real_total_yi[d] = compare_total_yi[j][d];
						Gbest_yi = real_total_yi[day - 1];
					}
					return;
				}
			}
		}
	}
}

void Gbest_stock_selection()
{
	for (int j = 0; j < experiment_time; j++)
	{
		for (int t = 0; t < generation; t++)
		{
			for (int i = 0; i < partical_num; i++)
			{
				for (int s = 0; s < s_stock_index; s++)
				{
					final_portfolio[s] = "\0";
					//cout << real_partical[j][i][s] << endl;
					if (real_partical[best_experimrentime - 1][i][s] == 1)
					{
						final_portfolio[s] = stock_no[s];//Gbest投資組合中
						train_stock_index[s] = s;
					}
				}
				return;
			}
		}
	}
}


void out_file(int a)
{
	string ouput_file = "Larry_result_" + Y2Q_train[a].substr(0, Y2Q_train[a].length());//輸出檔案名稱
	output_file.open(ouput_file, ios::app);//檔案輸出
	output_file << "代數" << "," << generation << endl;
	output_file << "粒子數" << "," << partical_num << endl;
	output_file << "旋轉角度上界" << "," << theta << endl;
	output_file << "旋轉角度下界" << "," << theta << endl;
	output_file << "旋轉角度" << "," << theta << endl;
	output_file << "實驗次數" << "," << experiment_time << endl << endl;
	output_file << "初始資金" << "," << initial_fund << endl;
	output_file << "最後資金" << "," << fixed << setprecision(15) << Gbest_yi << endl;
	output_file << "真實報酬" << "," << fixed << setprecision(15) << Gbest_yi - initial_fund << endl << endl;
	output_file << "預期報酬" << "," << fixed << setprecision(15) << Gbest_expect_retutn << endl;
	output_file << "風險" << "," << fixed << setprecision(15) << Gbest_daily_risk << endl;
	output_file << "Gbest" << "," << fixed << setprecision(30) << Gbest_max << endl;
	output_file << "找到最佳解世代" << "," << best_generation << endl;
	output_file << "找到最佳解實驗#" << "," << best_experimrentime << endl;
	output_file << "找到最佳解次數" << "," << Gbest_num << endl << endl;
	output_file << "投資組合檔數" << "," << Gbest_n << endl;
	for (int s = 0; s < s_stock_index; s++)
	{
		if (final_portfolio[s] != "\0")
		{
			output_file << final_portfolio[s] << "(" << s << ")" << ",";
		}

	}
	output_file << endl;
	output_file << "Stock#" << ",";
	for (int s = 0; s < s_stock_index; s++)
	{
		if (final_portfolio[s] != "\0")
		{
			output_file << final_portfolio[s] << "(" << s << ")" << ",";
		}
	}
	output_file << endl;
	output_file << "股數" << ",";
	for (int k = 0; k < Gbest_n; k++)
	{
		output_file << Gbest_buy_lots[k] << ",";
	}
	output_file << endl;
	output_file << "分配資金" << ",";
	for (int k = 0; k < Gbest_n; k++)
	{
		output_file << Gbest_share_money << ",";
	}
	output_file << endl;
	output_file << "剩餘資金" << ",";
	for (int k = 0; k < Gbest_n; k++)
	{
		output_file << Gbest_all_remain_fund[k] << ",";
	}
	output_file << endl;
	for (int d = 0; d < day; d++)
	{
		output_file << "FS(" << d + 1 << ")" << ",";
		for (int k = 0; k < Gbest_n; k++)
		{
			output_file << fixed << setprecision(15) << Gbest_n_fund_standardization[k][d] << ",";
		}
		output_file << fixed << setprecision(15) << real_total_yi[d] << "," << endl;
	}
	output_file.close();
}


void test_out_file(int a)
{
	string ouput_file = "Larry_result_" + Y2Q_test[a].substr(0, Y2Q_test[a].length());//輸出檔案名稱
	output_file.open(ouput_file, ios::app);//檔案輸出
	output_file << "代數" << "," << generation << endl;//v
	output_file << "粒子數" << "," << partical_num << endl;//v
	output_file << "旋轉角度" << "," << theta << endl;//v
	output_file << "實驗次數" << "," << experiment_time << endl << endl;//v
	output_file << "初始資金" << "," << test_initial_fund << endl;//v
	output_file << "最後資金" << "," << fixed << setprecision(15) << test_all_final_fund << endl;
	output_file << "真實報酬" << "," << fixed << setprecision(15) << test_all_final_fund - test_initial_fund << endl << endl;
	output_file << "預期報酬" << "," << fixed << setprecision(15) << test_m << endl;//v
	output_file << "風險" << "," << fixed << setprecision(15) << test_risk << endl;//v
	output_file << "Gbest" << "," << fixed << setprecision(11) << test_trend_ratio << endl;//v
	output_file << endl;
	output_file << "投資組合檔數" << "," << Gbest_n << endl;
	for (int s = 0; s < test_stock_index; s++)
	{
		for (int v = 0; v < s_stock_index; v++)
		{
			/*if (final_portfolio[s] != 0)
			{*/
			if (final_portfolio[v] == test_stock_no[s])
			{
				output_file << test_stock_no[s] << "(" << s << ")" << ",";
			}
			//}
		}
	}
	output_file << endl;
	output_file << "Stock#" << ",";
	for (int s = 0; s < test_stock_index; s++)
	{
		for (int v = 0; v < s_stock_index; v++)
		{
			/*if (final_portfolio[s] != 0)
			{*/
			if (final_portfolio[v] == test_stock_no[s])
			{
				output_file << test_stock_no[s] << "(" << s << ")" << ",";
			}
			//}
		}
	}
	output_file << endl;
	output_file << "股數" << ",";

	for (int s = 0; s < test_stock_index; s++)
	{
		for (int v = 0; v < s_stock_index; v++)
		{
			/*if (final_portfolio[s] != 0)
			{*/
			if (final_portfolio[v] == test_stock_no[s])
			{
				output_file << test_all_buy_lots[s] << ",";

			}
			//}
		}
	}
	output_file << endl;
	output_file << "分配資金" << ",";
	for (int k = 0; k < Gbest_n; k++)
	{
		output_file << test_share_money << ",";
	}
	output_file << endl;
	output_file << "剩餘資金" << ",";
	for (int s = 0; s < test_stock_index; s++)
	{
		for (int v = 0; v < s_stock_index; v++)
		{
			/*if (final_portfolio[s] != 0)
			{*/
			if (final_portfolio[v] == test_stock_no[s])
			{
				output_file << test_real_all_remain_fund[s] << ",";
			}
			//}
		}
	}
	output_file << endl;
	for (int d = 0; d < test_day; d++)
	{
		output_file << "FS(" << d + 1 << ")" << ",";
		for (int s = 0; s < test_stock_index; s++)
		{
			for (int v = 0; v < s_stock_index; v++)
			{
				/*if (final_portfolio[s] != 0)
				{*/
				if (final_portfolio[v] == test_stock_no[s])
				{
					output_file << fixed << setprecision(15) << test_n_fund_standardization[s][d] << ",";
				}
				//}
			}
		}
		output_file << fixed << setprecision(15) << test_all_total_yi[d] << "," << endl;
	}
	output_file.close();
}

void all_testperiod_final_result()
{
	string ouput_file = "Larry_US_Y2Y_total_test_result_.csv";//輸出檔案名稱
	output_file.open(ouput_file, ios::app);//檔案輸出
	output_file << "測試期區間" << "," << "test_2013(2012 Q1).csv - test_2019(2018 Q1).csv" << endl;
	output_file << "世代數" << "," << generation << endl;
	output_file << "旋轉角度" << "," << theta << endl;
	output_file << "粒子數" << "," << partical_num << endl;
	output_file << "實驗次數" << "," << experiment_time << endl;
	output_file << "初始資金" << "," << initial_fund << endl;
	output_file << "真實報酬" << "," << fixed << setprecision(15) << test_all_final_fund - initial_fund << endl << endl;
	output_file << "預期報酬" << "," << fixed << setprecision(15) << all_test_m << endl;
	output_file << "風險" << "," << fixed << setprecision(15) << final_test_risk << endl;
	output_file << "趨勢值" << "," << fixed << setprecision(15) << final_test_trend_ratio << endl;
	output_file << "*這裡的起點值是用預期報酬除上風險" << endl << endl;
	output_file << "總天數" << "," << day_count << endl;
	output_file << "天數" << "," << "總資金水位" << endl;
	for (int a = 0; a < file_num; a++)
	{
		for (int d = 0; d < total_test_day; d++)
		{
			if (real_last_total_std[a][d] != 0)
			{
				day_count_result++;
				output_file << "FS(" << day_count_result << ")" << ",";
				output_file << real_last_total_std[a][d] << endl;

			}
		}
	}

	output_file.close();
}

void all_train_prtiod_result(int a)
{
	string ouput_file = "Larry_ US_train_Gbest_10000_10_50_0.0004.csv";//輸出檔案名稱
	output_file.open(ouput_file, ios::app);

	if (all_gbest_trend_ratio[a] != 0)
	{
		output_file << a + 1 << "," << all_file_gbest_num[a] << ",";
		for (int s = 0; s < s_stock_index; s++)
		{
			if (all_file_gbest_portfolio[a][s] != "\0")
			{
				output_file << all_file_gbest_portfolio[a][s] << "(" << s << ") " << " ";
			}
		}
		output_file << ",";
		output_file << "Gbest" << "," << fixed << setprecision(20) << all_gbest_trend_ratio[a] << ",";
		output_file << "預期報酬" << "," << fixed << setprecision(20) << all_file_gbest_return[a] << ",";
		output_file << "風險" << "," << fixed << setprecision(20) << all_file_gbest_risk[a] << ",";
		output_file << "最佳解實驗#" << "," << all_file_gbest_experiment[a] << ",";
		output_file << "最佳解世代#" << "," << all_file_gbest_generation[a] << ",";
		output_file << "最佳解出現次數" << "," << all_file_gbest_appear[a];
		output_file << endl;
	}

	/*else if (all_gbest_trend_ratio[a] > 0)
	{
	output_file << a + 1 << "," << 0 << "," << 0 << ",";
	output_file << "Gbest" << "," << 0 << ",";
	output_file << "預期報酬" << "," << 0 << ",";
	output_file << "風險" << "," << 0 << ",";
	output_file << "最佳解實驗#" << "," << 0 << ",";
	output_file << "最佳解世代#" << "," << 0 << ",";
	output_file << "最佳解出現次數" << "," << 0;
	output_file << endl;
	}*/
	output_file.close();

}

int main()
{
	srand(114);
	for (int a = 0; a < file_num; a++)
	{
		read_file(a);
		for (int j = 0; j < experiment_time; j++)
		{
			index = 0;
			all_max = -999999999999999.0;
			initial();
			for (int t = 0; t < generation; t++)
			{
				measure();
				standardization();
				fitness();
				compare();
				for (int i = 0; i < partical_num; i++)
				{
					real_all_trend_ratio[j][t][i] = all_trend_ratio[i];
					daily_risk[j][t][i] = risk[i];
					expect_m[j][t][i] = m[i];
					final_n[j][t][i] = n[i];
					compare_share_money[j][t][i] = all_share_money[i];

					for (int s = 0; s < s_stock_index; s++)
					{
						real_partical[j][i][s] = partical[i][s];//Think
					}

					for (int k = 0; k < n[i]; k++)
					{
						compare_buy_lots[j][i][k] = all_buy_lots[k];
						compare_remain_fund[j][k] = real_all_remain_fund[k];
						for (int d = 0; d < day; d++)
						{
							all_n_fund_standardization[j][k][d] = n_fund_standardization[i][k][d];
							compare_total_yi[j][d] = all_total_yi[d];

						}
					}

				}
			}
			all_max_tmp[j] = all_max;//將每次實驗找到的Gbest放入陣列中				
		}
		experiment_compre();
		Gbest_num_find();
		generation_compare();
		Gbest_stock_selection();
		for (int s = 0; s < s_stock_index; s++)
		{
			/*if (final_portfolio[s] != 0)
			{*/
			//cout << final_portfolio[s] << "(" << s << ")" << endl;
			//}
		}
		out_file(a);
		test_index = 0;
		test_read_file(a);//測試期讀檔
		if (a == 0)
		{
			test_initial_fund = initial_fund;//如果是第一個測試期檔案,則初始資金為10000000
		}
		if (test_all_final_fund <= 0)
		{
			test_initial_fund = test_initial_fund;
		}
		else if (a != 0)
		{
			test_initial_fund = test_all_final_fund;//第二個測試期檔案開始,初始資金為上一區間最後資金

		}
		test_standardization(a);
		test_fitness();
		all_test_return();//總體測試期預期報酬計算
		test_out_file(a);//測試期檔案輸出
		all_file_gbest_risk[a] = Gbest_daily_risk;
		all_file_gbest_return[a] = Gbest_expect_retutn;
		all_file_gbest_num[a] = Gbest_n;
		all_file_gbest_generation[a] = best_generation;
		all_file_gbest_experiment[a] = best_experimrentime;
		all_file_gbest_appear[a] = Gbest_num;
		all_gbest_trend_ratio[a] = Gbest_max;
		for (int s = 0; s < s_stock_index; s++)
		{
			if (final_portfolio[s] != "/0")
			{
				all_file_gbest_portfolio[a][s] = final_portfolio[s];
			}
		}
		all_train_prtiod_result(a);
	}
	all_test_risk();//總體測試期風險計算
	all_testperiod_final_result();//總體測試期結果輸出
	system("pause");
	return 0;
}