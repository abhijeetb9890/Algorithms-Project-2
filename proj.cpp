
#include <iostream>
#include <math.h>
#include <vector>
#include <set>
#include <iterator>

using namespace std;

int dp[21][21];
int lcs_len = 0;
string conv_to_bin(int a, int n)
{
	int arr[21], i;
	char c;
	string p = "";
	for (i = 0; i < n; i++)
	{
		arr[i] = a % 2;
		a = a / 2;
	}
	for (i = i - 1; i >= 0; i--)
	{
		c = arr[i] + 48;
		p = p + c;
	}
	return p;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int find_max_lcs_len(string p, string q, int n)
{
	int i, j;
	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= n; j++)
		{
			if (i == 0 || j == 0)
				dp[i][j] = 0;
			else if (p[i - 1] == q[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[n][n];
}

vector<string> findLCS(string a, string b, int m, int n)
{
	if (m == 0 || n == 0)
	{
		vector<string> v(1);
		return v;
	}

	if (a[m - 1] == b[n - 1])
	{
		vector<string> lcs = findLCS(a, b, m - 1, n - 1);
		vector<string>::iterator it = lcs.begin();
		while(it != lcs.end())
		{
			it->push_back(a[m - 1]);
			it++;
		}

		return lcs;
	}

	if (dp[m - 1][n] > dp[m][n - 1])
		return findLCS(a, b, m - 1, n);

	if (dp[m][n - 1] > dp[m - 1][n])
		return findLCS(a, b, m, n - 1);

	vector<string> v1 = findLCS(a, b, m - 1, n);
	vector<string> v2 = findLCS(a, b, m, n - 1);

	v1.insert(v1.end(), v2.begin(), v2.end());

	return v1;
}

int main()
{
	int n, x, y, lim;
	char ans[21];

	string a = "", b = "";
	do
	{
		cout << "Enter value of n in range [3:20] : ";
		cin >> n;
		if (n < 3 || n > 20)
			cout << "Please enter value within given range.\n";
	} while (n < 3 || n > 20);
	lim = pow(2.0, n) - 1;
	do
	{
		cout << "Enter value of x in range [0:" << lim << "] : ";
		cin >> x;
		if (x < 0 || x > lim)
			cout << "Please enter value within given range.\n";
	} while (x < 0 || x > lim);

	do
	{
		cout << "Enter value of y in range [0:" << lim << "] : ";
		cin >> y;
		if (y < 0 || y > lim)
			cout << "Please enter value within given range.\n";
	} while (y < 0 || y > lim);

	a = conv_to_bin(x, n);
	b = conv_to_bin(y, n);
	cout << "\n";
	cout << "n: " << n << "\tx: " << x << "\ty: " << y << "\n";
	cout << "binstring(n,x): " << a << "\nbinstring(n,y) " << b << "\n";

	find_max_lcs_len(a, b, n);
	vector<string> allLCS = findLCS(a, b, n, n);
	set<string> lcs;

	for(int i=0;i<allLCS.size();i++)
	{
		lcs.insert(allLCS[i]);
	}

	cout << "Number of distinct LCS: " << lcs.size() << endl;

	cout << "\nList of distinct LCS:" << endl;
	cout << "---------------------\n" << endl;
	set<string>::iterator it = lcs.begin();
	while(it != lcs.end())
	{
		cout << *it << endl;
		it++;
	}
	cout << endl;

	return 0;
}

