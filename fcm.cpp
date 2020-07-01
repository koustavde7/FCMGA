#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<algorithm>  //Contains std::equal
using namespace std;

/*Step 2 : Centroid Calculation*/
void Cal_Centroid(vector<vector<float>> &centroid, int c, int n, vector<float> &X, vector<float> &Y, vector<vector<float>> &C)
{
	int j, k;
	float sum = 0, mem_sum = 0;
	for(j = 0; j < c; j++)
	{
			sum = 0;
			mem_sum = 0;
			for(k = 0; k < n; k++)
			{
				sum += X[k] * pow(C[k][j], 2);
				mem_sum += pow(C[k][j], 2);
			}
			centroid[j][0] = sum/mem_sum;
			sum = 0;
			for(k = 0; k < n; k++)
				sum += Y[k] * pow(C[k][j], 2);
			centroid[j][1] = sum/mem_sum;
	}
}
/*Step 2 ends here*/

/*Step 3 : Euclidean Distance from each cluster centroid*/
float euclid(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}
void Cal_Distance(vector<vector<float>> &distance, vector<vector<float>> centroid, vector<float> X, vector<float> Y, int c, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < c; j++)
		{
			distance[i][j] = euclid(X[i], Y[i], centroid[j][0], centroid[j][1]);
		}
	}
}
/*Step 3 ends here*/

/*Step 4 : Update the membership Value*/
void Cal_Miu(vector<vector<float>> &Miu, vector<vector<float>> distance, int c, int n, int m)
{
	int i, j, k;
	float sum;
	for(j = 0; j < c; j++)
	{
		for(i = 0; i < n; i++)
		{
			sum = 0;
			for(k = 0; k < c; k++)
			{
				sum+= pow((1/distance[i][k]), (1/(m-1)));
			}
			Miu[i][j] = pow((1/distance[i][j]), (1/(m-1))) / sum;
		}
	}
}
/*Step 4 ends here*/
void print(vector<vector<float>> Vec)
{
	int i, j;
	for(i = 0; i < Vec.size(); i++)
	{	
		for(j = 0; j < Vec[0].size(); j++)
			cout<<Vec[i][j]<<"  ";
		cout<<endl;
	}
}

int main()
{
	int n, c, i, j, m = 2;
	float x,y,mem;
	cout<<"Enter number of data points : ";
	cin>>n;
	cout<<"Now enter number of clusters : ";
	cin>>c;

	/*Step 1 : Random Initialization Starts*/
	vector<float> X,Y;
	vector<vector<float>> C(n);
	for(i = 0; i < n; i++)
		C[i] = vector<float>(c);
	cout<<endl<<"Enter the Coordinates and membership of the points e.g. (X,Y) :-"<<endl;
	for(i = 0; i < n; i++)
	{
		cout<<"X["<<i<<"] = ";
		cin>>x;
		cout<<"Y["<<i<<"] = ";
		cin>>y;
		X.push_back(x);
		Y.push_back(y);
		for(j = 0; j < c; j++)
		{
			cout<<"C["<<i<<"]["<<j<<"] = ";
			cin>>mem;
			C[i][j] = mem;
		}
	}
	/*Random Initialization Ends*/

	/*Centroid Assignment*/
	vector<vector<float>> centroid_old(c);
	for(j = 0; j < c; j++)
	{
		centroid_old[j] = vector<float>(2);
		centroid_old[j][0] = -1;
		centroid_old[j][1] = -1;
	}

	while(true)
	{
		/*Step 2 : Calculation of the centroids*/
		vector<vector<float>> centroid(c);
		for(j = 0; j < c; j++)
			centroid[j] = vector<float>(2);
		Cal_Centroid(centroid, c, n, X, Y, C);
		//cout<<endl<<"Centroid :-"<<endl;
		//print(centroid);
		/*Step 2 Ends*/

		/*Checking for loop termination*/
		if(equal(centroid.begin(), centroid.end(), centroid_old.begin()))
			break;
		/*Checking Ends*/

		/*Step 3 : Calculation of the Euclidean Distance*/
		vector<vector<float>> distance(n);
		for(i = 0; i < n ; i++)
			distance[i] = vector<float>(c);
		Cal_Distance(distance, centroid, X, Y, c, n);
		//cout<<endl<<"Distance :-"<<endl;
		//print(distance);
		/*Step 3 Ends*/
		
		/*Step 4 : Update the new Membership Matrix*/
		vector<vector<float>> Miu(n);
		for(i = 0; i < n ; i++)
			Miu[i] = vector<float>(c);
		Cal_Miu(Miu, distance, c, n, m);
		cout<<endl<<"Membership after another iteration :-"<<endl;
		print(Miu);
		/*Step 4 Ends*/

		/*Step 5 : Go Back to step 2 unless the centroids are same*/
		C = Miu;
		centroid_old = centroid;
		/*Step 5 Ends*/
	}
	return 0;
}