/*���Ѵ���*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

ifstream input_file;
ifstream test_input_file;
ofstream output_file;
double all_stock[10000][10000]; //�Ҧ��Ѳ�
double test_all_stock[100][400];
int stock_no[50]; //�Ѳ��s��
int test_stock_no[50];
int index;
int test_index;
//read_file

double beta[50];
double partical[10][90000];
//int profolio[50];//���զX
//initial

int stock_index[10][50];//�O���C���ɤl(10)�ҿ�쪺���զX(50)
						//choose

int train_stock_index[50];
double initial_fund = 10000000; //��l���
double test_initial_fund;
double remaind;//�Ѿl���
double test_remaind;
double all_remain_fund;
double test_all_remain_fund;
double fund_standardization; //�������
double fee; //����O
double test_fee;
double total_fee[50000];
double one_fund_standardization[50][2500];
double n_fund_standardization[100][50][2500];//�U�ɸ������
double test_n_fund_standardization[50][300];//���մ��������
double partical_fund_standardization[100][2500];//���զX�������
double risk[10000]; //�C�魷�I
double test_risk;//�V�m���C�魷�I
double final_test_risk;
double m[10000]; //�w�����S
double test_m;
int share_money;//�C�ɤ��t����
int test_share_money;
double one_of_price; //�C�i����
double test_one_of_price;
double daily_risk[50][10000][10];//�C������C�N�C�魷�I
double expect_m[50][10000][10];//�C������C�N�w�����S
double Gbest_daily_risk;//�̨θѨC�魷�I
double Gbest_expect_retutn;//�̨θѹw�����S

int buy_papper;//�i�R���i��
int test_buy_paper;
double yi[10000][10000];//��i�ѯu��������
double test_yi[1000];
double all_final_yi[10000];//�C�@�Ӳɤl�̫�@�Ѫ�yi
						   //standardization

double m1;
int m2;
double all_standardization[2500];
double Yi[100][300];//�@���^�k�Ͷսu
double test_Yi[300];
double r1;
double trend_ratio;//�Ͷխ�
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
int n[50];//��諸���զX���X��
int partical_num = 1;
int generation = 1;
int experiment_time = 1;
int s_stock_index = 0;//train stock num
int test_stock_index = 0;

int total_n;
int day;
int test_day;
//compare

double all_max = 0;
int all_max_solution[10000];
double random;
int file_num = 8;
double Gbest[50];
double all_max_tmp[50];
double Gbest_max;
int best_experimrentime;
int best_generation;
double real_all_trend_ratio[50][10000][10];
double real_yi[50][10000][10];
double Gbest_yi;
int Gbest_num;//Gbest���X�{����
int final_n[50][10000][10];//�s�̨θ��ɼ�
int Gbest_n;//Gbest��쪺�ɼ�
int Gbest_i;
int selection_stock_no[10][50];
int real_partical[50][10][50];
int final_portfolio[50];
int all_buy_paper[50];//�s�i�R�i�ƪ��}�C
int last_test_all_buy_paper[50];
int test_all_buy_paper[50];
int all_share_money[10];//�s���t������}�C
int test_all_share_money[10];
int compare_share_money[50][10000][10];//�s�C������C�ӥ@�N�C�Ӳɤl�����t����}�C
int compare_buy_paper[50][10][50];//�s�C�ӹ��礤���զX�Ѳ��i�R�i��
int Gbest_share_money;
int Gbest_buy_paper[50];//Gbest�զX���Ѳ��i�R���i��
double real_all_remain_fund[50];
double test_real_all_remain_fund[50];
double compare_remain_fund[50][50];
double Gbest_all_remain_fund[50];//Gbest���R���U�ѳѾl���
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
double test_total_all_period_m;//���մ��`��w�����S
double test_all_period_Yi[10000];
double test_all_period_risk;
double test_all_period_trend_ratio;
double test_all_period_m1;
int test_all_period_m2;
double last_total_std[10000];//�s�Ҧ����մ��`�������
double last_total_Yi[10000];//�p���`����մ��w���������
double real_last_total_std[100][10000];//�s�Ҧ����մ��`�������
int day_count;
double all_test_m;
double final_all_test_m;//�`����մ��̲׹w�����S
double final_test_m1;
double final_test_m2;
double final_test_r1;
int day_count_risk;//�`����մ��p�⭷�I�Ѽ�counter
int day_count_result;//�`����մ���X���G�Ѽ�counter

string AAPL[] = { "AAPL-2012.csv", "AAPL-2013.csv", "AAPL-2014.csv", "AAPL-2015.csv", "AAPL-2016.csv", "AAPL-2017.csv", "AAPL-2018.csv", "AAPL-2019.csv" };
string AMZN[] = { "AMZN-2012.csv", "AMZN-2013.csv", "AMZN-2014.csv", "AMZN-2015.csv", "AMZN-2016.csv", "AMZN-2017.csv", "AMZN-2018.csv", "AMZN-2019.csv" };
string BABA[] = { "BABA-2014.csv", "BABA-2015.csv", "BABA-2016.csv", "BABA-2017.csv", "BABA-2018.csv", "BABA-2019.csv" };
string BRK[] = { "BRK-A-2012.csv", "BRK-A-2013.csv", "BRK-A-2014.csv", "BRK-A-2015.csv", "BRK-A-2016.csv", "BRK-A-2017.csv", "BRK-A-2018.csv", "BRK-A-2019.csv" };
string FB[] = { "FB-2012.csv", "FB-2013.csv", "FB-2014.csv", "FB-2015.csv", "FB-2016.csv", "FB-2017.csv", "FB-2018.csv", "FB-2019.csv" };
string GOOG[] = { "GOOG-2012.csv", "GOOG-2013.csv", "GOOG-2014.csv", "GOOG-2015.csv", "GOOG-2016.csv", "GOOG-2017.csv", "GOOG-2018.csv", "GOOG-2019.csv" };
string GOOGL[] = { "GOOGL-2012.csv", "GOOGL-2013.csv", "GOOGL-2014.csv", "GOOGL-2015.csv", "GOOGL-2016.csv", "GOOGL-2017.csv", "GOOGL-2018.csv", "GOOGL-2019.csv" };
string JNJ[] = { "JNJ-2012.csv", "JNJ-2013.csv", "JNJ-2014.csv", "JNJ-2015.csv", "JNJ-2016.csv", "JNJ-2017.csv", "JNJ-2018.csv", "JNJ-2019.csv" };
string JPM[] = { "JPM-2012.csv", "JPM-2013.csv", "JPM-2014.csv", "JPM-2015.csv", "JPM-2016.csv", "JPM-2017.csv", "JPM-2018.csv", "JPM-2019.csv" };
string MSFT[] = { "MSFT-2012.csv", "MSFT-2013.csv", "MSFT-2014.csv", "MSFT-2015.csv", "MSFT-2016.csv", "MSFT-2017.csv", "MSFT-2018.csv", "MSFT-2019.csv" };
string TECHY[] = { "TCEHY-2012.csv", "TCEHY-2013.csv", "TCEHY-2014.csv", "TCEHY-2015.csv", "TCEHY-2016.csv", "TCEHY-2017.csv", "TCEHY-2018.csv", "TCEHY-2019.csv"};
string V[] = { "V-2012.csv", "V-2013.csv", "V-2014.csv", "V-2015.csv", "V-2016.csv", "V-2017.csv", "V-2018.csv", "V-2019.csv" };
string XOM[] = { "XOM-2012.csv", "XOM-2013.csv", "XOM-2014.csv", "XOM-2015.csv", "XOM-2016.csv", "XOM-2017.csv", "XOM-2018.csv", "XOM-2019.csv" };

void read_file(int a) {

	input_file.open(AAPL[a], ios::in);
	cout << endl << AAPL[a] << endl;
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
				stringstream num;
				num << tmp;
				num >> stock_no[s_stock_index];//�s��
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
				price >> all_stock[s_stock_index][index - 1];//�ѻ�
				s_stock_index++;
			}
			index++;
		}
	}
	input_file.close();
	day = index - 1;
}//Ū��

void test_read_file(int a) {

	test_input_file.open(AAPL[a], ios::in);
	cout << endl << AAPL[a] << endl;
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
				test_num >> test_stock_no[test_stock_index];//�s��
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
				test_price >> test_all_stock[test_stock_index][test_index - 1];//�ѻ�
				test_stock_index++;
			}
			test_index++;
		}
	}
	test_input_file.close();
	test_day = test_index - 1;
	total_test_day += test_day;
}//Ū��

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
		n[i] = 0;//�d�U����R
		for (int j = 0; j < s_stock_index; j++) {

			random = rand() / 32767.0;
			/*if (random < beta[j]) {
				partical[i][j] = 1;
			}
			else partical[i][j] = 0;*///�H����0��1
									if (j == 0/* || j == 1 || j == 2*/)
									partical[i][j] = 1;
									else partical[i][j] = 0;
			if (partical[i][j] == 1)
			{
				stock_index[i][n[i]] = j;
				//cout << stock_no[stock_index[i][n[i]]] << endl; //�Ѳ��s��
				//cout << stock_index[i][n[i]]  << endl;//��쪺�Ѳ� index
				n[i] = n[i]++;//�X��
			}

		}

	}
}

void standardization()
{
	for (int i = 0; i < partical_num; i++)
	{
		share_money = initial_fund / n[i];//�C����ܫᥭ���C�ɪ����,���n�R!!!!
		all_share_money[i] = share_money;//��C�Ӳɤl�����t����s�_��
		remaind = initial_fund - share_money * n[i];//���զX���t���ѤU����
		for (int j = 0; j < n[i]; j++) {
			all_buy_paper[j] = 0;
			real_all_remain_fund[j] = 0;
			for (int k = 0; k < day; k++) {

				if (k == 0)
				{
					one_of_price = all_stock[stock_index[i][j]][k] * 1000 + all_stock[stock_index[i][j]][k] * 1.425;//��i����
					buy_papper = share_money / one_of_price;//�i�R�i��
					all_buy_paper[j] = buy_papper;
					all_remain_fund = share_money - one_of_price * buy_papper;//�R���U�ѳѾl���
					real_all_remain_fund[j] = all_remain_fund;//��R���U�ѳѾl����s�J�}�C���i��P�_
					fee = all_stock[stock_index[i][j]][k] * buy_papper * 1.425;//����O v
					n_fund_standardization[i][j][k] = share_money - fee;//������� v
				}
				else
				{
					n_fund_standardization[i][j][k] = all_stock[stock_index[i][j]][k] * buy_papper * 1000 -
						all_stock[stock_index[i][j]][k] * buy_papper * 4.425 + all_remain_fund;
				}
			}
		}

		for (int k = 0; k < day; k++)
		{
			yi[i][k] = 0;
			for (int j = 0; j < n[i]; j++)
			{
				yi[i][k] = yi[i][k] + n_fund_standardization[i][j][k];//yi total
			}
			yi[i][k] += remaind;//v
			all_total_yi[k] = yi[i][k];
		}
	}
}

void test_standardization(int a)//���մ��������p��
{
	test_share_money = test_initial_fund / Gbest_n;//�C����ܫᥭ���C�ɪ����,���n�R!!!!
	test_remaind = test_initial_fund - test_share_money * Gbest_n;//���զX���t���ѤU����


	for (int v = 0; v < s_stock_index; v++)
	{
		if (final_portfolio[v] != 0)
		{
			for (int s = 0; s < test_stock_index; s++)
			{
				//cout << test_stock_no[s] << endl;
				if (final_portfolio[v] == test_stock_no[s])
				{
					//cout << s << endl;
					for (int k = 0; k < test_day; k++) {
						//	test_all_stock[s][k] = 0;
						if (k == 0)
						{
							test_one_of_price = test_all_stock[s][k] * 1000 + test_all_stock[s][k] * 1.425;//��i����
							test_buy_paper = test_share_money / test_one_of_price;//�i�R�i��
							test_all_buy_paper[s] = test_buy_paper;
							test_all_remain_fund = test_share_money - test_one_of_price * test_buy_paper;//�R���U�ѳѾl���
							test_real_all_remain_fund[s] = test_all_remain_fund;//��R���U�ѳѾl����s�J�}�C���i��P�_;
							test_fee = test_all_stock[s][k] * test_buy_paper * 1.425;//����O 
							test_n_fund_standardization[s][k] = test_share_money - test_fee;//������� 
						}
						else
						{
							test_n_fund_standardization[s][k] = test_all_stock[s][k] * test_buy_paper * 1000 -
								test_all_stock[s][k] * test_buy_paper * 4.425 + test_all_remain_fund;
						}
					}
				}
			}

		}
	}

	for (int k = 0; k < test_day; k++)
	{
		test_yi[k] = 0;

		for (int v = 0; v < s_stock_index; v++)
		{
			if (final_portfolio[v] != 0)
			{
				for (int s = 0; s < test_stock_index; s++)
				{
					if (final_portfolio[v] == test_stock_no[s])
					{
						test_yi[k] = test_yi[k] + test_n_fund_standardization[s][k];//yi total
					}
				}
			}
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
				day_count_risk++;//�֥[�s�J�}�C������0������,�÷�@�`�Ѽƨϥ�
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
		final_test_trend_ratio = all_test_m / final_test_risk;//�Ͷխ�
	}
	cout << "����w�����S: " << final_all_test_m << endl;
	cout << "���魷�I:" << final_test_risk << endl;
	cout << "�����Ͷխ�: " << final_test_trend_ratio << endl;
}

void test_fitness()//�p����մ��U�϶��Ͷխ�
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
		test_Yi[k] = test_m * (k + 1) + test_initial_fund;//�@���^�k�Ͷսu//v
		test_r1 += ((test_yi[k] - test_Yi[k]) * (test_yi[k] - test_Yi[k]));//(yi-Yi)
	}
	test_risk = sqrt(test_r1 / (test_day));//���I

	if (test_m < 0)
	{
		test_trend_ratio = test_m * test_risk;
	}
	else if (test_m > 0)
	{
		test_trend_ratio = test_m / test_risk;//�Ͷխ�
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
			Yi[i][k] = m[i] * (k + 1) + initial_fund;//�@���^�k�Ͷսu//v
			r1 += ((yi[i][k] - Yi[i][k]) * (yi[i][k] - Yi[i][k]));//(yi-Yi)
		}
		risk[i] = sqrt(r1 / (day));//���I

		if (m[i] < 0)
		{
			trend_ratio = m[i] * risk[i];
		}
		else if (m[i] > 0)
		{
			trend_ratio = m[i] / risk[i];//�Ͷխ�
		}
		all_trend_ratio[i] = trend_ratio;
	}

}

void compare()
{
	max_fitness = all_trend_ratio[0];//�p�G�o��]��0,��쪺���@�w�O��N�ɤl���̤j�ȡC(�p�G��N�ɤl���O�t��)
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
	}//��Best&Worst

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

void experiment_compre() /*50������Gbest���,�ç�XGbest�������*/
{
	Gbest_max = all_max_tmp[0];
	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max <= all_max_tmp[j])
		{
			Gbest_max = all_max_tmp[j];
		}//��50�����窺Gbest,�p�G�u���@������i����
	}

	for (int j = 0; j < experiment_time; j++)
	{
		if (Gbest_max == all_max_tmp[j])
		{
			best_experimrentime = j + 1;//��̨θѹ��禸��
			break;
		}
	}
}

void Gbest_num_find()//��Gbest����禸�Ƥ��X�{������
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
					best_generation = t + 1;//�̨θѥ@�N��
					Gbest_daily_risk = daily_risk[j][t][i];//�̨θѭ��I
					Gbest_expect_retutn = expect_m[j][t][i];//�̨θѹw�����S
					Gbest_n = final_n[j][t][i];
					Gbest_share_money = compare_share_money[j][t][i];
					Gbest_i = i;
					for (int k = 0; k < Gbest_n; k++)
					{
						Gbest_all_remain_fund[k] = 0;
						Gbest_buy_paper[k] = compare_buy_paper[j][i][k];//�i�R�i��
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
					final_portfolio[s] = 0;
					if (real_partical[best_experimrentime - 1][i][s] == 1)
					{
						final_portfolio[s] = stock_no[s];//Gbest���զX��
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
	string ouput_file = "Larry_result_" + AAPL[a].substr(0, AAPL[a].length());//��X�ɮצW��
	output_file.open(ouput_file, ios::app);//�ɮ׿�X
	output_file << "�N��" << "," << generation << endl;
	output_file << "�ɤl��" << "," << partical_num << endl;
	output_file << "���ਤ�פW��" << "," << theta << endl;
	output_file << "���ਤ�פU��" << "," << theta << endl;
	output_file << "���ਤ��" << "," << theta << endl;
	output_file << "���禸��" << "," << experiment_time << endl << endl;
	output_file << "��l���" << "," << initial_fund << endl;
	output_file << "�̫���" << "," << fixed << setprecision(15) << Gbest_yi << endl;
	output_file << "�u����S" << "," << fixed << setprecision(15) << Gbest_yi - initial_fund << endl << endl;
	output_file << "�w�����S" << "," << fixed << setprecision(15) << Gbest_expect_retutn << endl;
	output_file << "���I" << "," << fixed << setprecision(15) << Gbest_daily_risk << endl;
	output_file << "Gbest" << "," << fixed << setprecision(11) << Gbest_max << endl;
	output_file << "���̨θѥ@�N" << "," << best_generation << endl;
	output_file << "���̨θѹ���#" << "," << best_experimrentime << endl;
	output_file << "���̨θѦ���" << "," << Gbest_num << endl << endl;
	output_file << "���զX�ɼ�" << "," << Gbest_n << endl;
	for (int s = 0; s < s_stock_index; s++)
	{
		if (final_portfolio[s] != 0)
		{
			output_file << final_portfolio[s] << "(" << s << ")" << ",";
		}
	}
	output_file << endl;
	output_file << "Stock#" << ",";
	for (int s = 0; s < s_stock_index; s++)
	{
		if (final_portfolio[s] != 0)
		{
			output_file << final_portfolio[s] << "(" << s << ")" << ",";
		}
	}
	output_file << endl;
	output_file << "�i��" << ",";
	for (int k = 0; k < Gbest_n; k++)
	{
		output_file << Gbest_buy_paper[k] << ",";
	}
	output_file << endl;
	output_file << "���t���" << ",";
	for (int k = 0; k < Gbest_n; k++)
	{
		output_file << Gbest_share_money << ",";
	}
	output_file << endl;
	output_file << "�Ѿl���" << ",";
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
	string ouput_file = "Larry_result_" + AAPL[a].substr(0, AAPL[a].length());//��X�ɮצW��
	output_file.open(ouput_file, ios::app);//�ɮ׿�X
	output_file << "�N��" << "," << generation << endl;//v
	output_file << "�ɤl��" << "," << partical_num << endl;//v
	output_file << "���ਤ��" << "," << theta << endl;//v
	output_file << "���禸��" << "," << experiment_time << endl << endl;//v
	output_file << "��l���" << "," << test_initial_fund << endl;//v
	output_file << "�̫���" << "," << fixed << setprecision(15) << test_all_final_fund << endl;
	output_file << "�u����S" << "," << fixed << setprecision(15) << test_all_final_fund - test_initial_fund << endl << endl;
	output_file << "�w�����S" << "," << fixed << setprecision(15) << test_m << endl;//v
	output_file << "���I" << "," << fixed << setprecision(15) << test_risk << endl;//v
	output_file << "Gbest" << "," << fixed << setprecision(11) << test_trend_ratio << endl;//v
	output_file << endl;
	output_file << "���զX�ɼ�" << "," << Gbest_n << endl;
	for (int s = 0; s < test_stock_index; s++)
	{
		for (int v = 0; v < s_stock_index; v++)
		{
			if (final_portfolio[s] != 0)
			{
				if (final_portfolio[v] == test_stock_no[s])
				{
					output_file << test_stock_no[s] << "(" << s << ")" << ",";
				}
			}
		}
	}
	output_file << endl;
	output_file << "Stock#" << ",";
	for (int s = 0; s < test_stock_index; s++)
	{
		for (int v = 0; v < s_stock_index; v++)
		{
			if (final_portfolio[s] != 0)
			{
				if (final_portfolio[v] == test_stock_no[s])
				{
					output_file << test_stock_no[s] << "(" << s << ")" << ",";
				}
			}
		}
	}
	output_file << endl;
	output_file << "�i��" << ",";

	for (int s = 0; s < test_stock_index; s++)
	{
		for (int v = 0; v < s_stock_index; v++)
		{
			if (final_portfolio[s] != 0)
			{
				if (final_portfolio[v] == test_stock_no[s])
				{
					output_file << test_all_buy_paper[s] << ",";

				}
			}
		}
	}
	output_file << endl;
	output_file << "���t���" << ",";
	for (int k = 0; k < Gbest_n; k++)
	{
		output_file << test_share_money << ",";
	}
	output_file << endl;
	output_file << "�Ѿl���" << ",";
	for (int s = 0; s < test_stock_index; s++)
	{
		for (int v = 0; v < s_stock_index; v++)
		{
			if (final_portfolio[s] != 0)
			{
				if (final_portfolio[v] == test_stock_no[s])
				{
					output_file << test_real_all_remain_fund[s] << ",";
				}
			}
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
				if (final_portfolio[s] != 0)
				{
					if (final_portfolio[v] == test_stock_no[s])
					{
						output_file << fixed << setprecision(15) << test_n_fund_standardization[s][d] << ",";
					}
				}
			}
		}
		output_file << fixed << setprecision(15) << test_all_total_yi[d] << "," << endl;
	}
	output_file.close();
}

void all_testperiod_final_result()
{
	string ouput_file = "Larry_H#_total_test_result_.csv";//��X�ɮצW��
	output_file.open(ouput_file, ios::app);//�ɮ׿�X
	output_file << "���մ��϶�" << "," << "test_2010_Q1-Q2(2009 Q1).csv - test_2017_Q3-Q4(2016 Q1).csv" << endl;
	output_file << "�@�N��" << "," << generation << endl;
	output_file << "���ਤ��" << "," << theta << endl;
	output_file << "�ɤl��" << "," << partical_num << endl;
	output_file << "���禸��" << "," << experiment_time << endl;
	output_file << "��l���" << "," << initial_fund << endl;
	output_file << "�u����S" << "," << fixed << setprecision(15) << test_all_final_fund - initial_fund << endl << endl;
	output_file << "�w�����S" << "," << fixed << setprecision(15) << all_test_m << endl;
	output_file << "���I" << "," << fixed << setprecision(15) << final_test_risk << endl;
	output_file << "�Ͷխ�" << "," << fixed << setprecision(15) << final_test_trend_ratio << endl;
	output_file << "*�o�̪��_�I�ȬO�ιw�����S���W���I" << endl << endl;
	output_file << "�`�Ѽ�" << "," << day_count << endl;
	output_file << "�Ѽ�" << "," << "�`�������" << endl;
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

int main()
{
	srand(114);
	for (int a = 0; a < file_num; a++)
	{
		read_file(a);
		for (int j = 0; j < experiment_time; j++)
		{
			index = 0;
			all_max = 0;
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
						compare_buy_paper[j][i][k] = all_buy_paper[k];
						compare_remain_fund[j][k] = real_all_remain_fund[k];
						for (int d = 0; d < day; d++)
						{
							all_n_fund_standardization[j][k][d] = n_fund_standardization[i][k][d];
							compare_total_yi[j][d] = all_total_yi[d];

						}
					}

				}
			}
			all_max_tmp[j] = all_max;//�N�C�������쪺Gbest��J�}�C��				
		}
		experiment_compre();
		Gbest_num_find();
		generation_compare();
		Gbest_stock_selection();
		for (int s = 0; s < s_stock_index; s++)
		{
			if (final_portfolio[s] != 0)
			{
				cout << final_portfolio[s] << "(" << s << ")" << endl;
			}
		}
		out_file(a);//�V�m�����G��X
		//test_index = 0;
		//test_read_file(a);//���մ�Ū��
		/*if (a == 0)
		{
			test_initial_fund = initial_fund;//�p�G�O�Ĥ@�Ӵ��մ��ɮ�,�h��l�����10000000
											 //day_index = 0;
		}
		else if (a != 0)
		{
			test_initial_fund = test_all_final_fund;//�ĤG�Ӵ��մ��ɮ׶}�l,��l������W�@�϶��̫���
		}*/
		//test_standardization(a);
		//test_fitness();
		//all_test_return();//�`����մ��w�����S�p��
						  //test_out_file(a);//���մ��ɮ׿�X
	}
	//all_test_risk();//�`����մ����I�p��
	//all_testperiod_final_result();//�`����մ����G��X
	return 0;
}