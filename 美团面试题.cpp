/*
http://www.iteye.com/topic/1134016
二维数组（N*N），沿对角线方向，从右上角打印到左下角如N=4： 
4*4二维数组 
{ 1 2 3 4 }  
{ 5 6 7 8 }  
{ 9 10 11 12 }  
{13 14 15 16 }  
打印顺序 
4  
3 8  
2 7 12  
1 6 11 16  
5 10 15  
9 14  
13  
要求半个小时内写出可完整运行的代码。*/

/*
  王昊在公司群里发的题，随便写了下，这是C++实现，用的矩阵旋转（实际转的是坐标轴）
  矩阵乘法用的cocos2dx自带的库,其实自己写个也很简单的0.0
*/

int N = 4;
	int * arr = new int [N * N];
	int * newArr = new int [5 * N * 5 * N];
	for (int i = 0; i < N * N; i++)
		arr[i] = i + 1;
	memset(newArr, -1, sizeof(int) * 5 * N * 5 * N);

	Mat4 mat = {// 绕 z 轴逆时针旋转 π/4 的矩阵
		cosf(-M_PI / 4), sinf(-M_PI / 4), 0.f, 0.f,
		-sinf(-M_PI / 4), cosf(-M_PI / 4), 0.f, 0.f,
		0.f,              0.f,             1.f, 0.f,
		0.f,              0.f,             0.f, 1.f
	};

	for (int i = 0; i < N * N; i++)
	{
		float x = i % N, y = -float(i / N);// 偷懒,直接设定锚点，不再乘一个平移矩阵了
		Vec3 vec(x - (N - 1) / 2.f, y + (N - 1) / 2.f, 0);
		vec.x *= 2; vec.y *= 2;// 因为坐标为整数但矩阵为浮点数，所以让它变大减小误差
		mat.transformVector(&vec);
		int newX = round(vec.x) + N;
		int newY = round(vec.y) + N;
		newArr[(5 * N - newY - 1) * 5 * N + newX] = arr [i];
	}

	for (int y = 0; y < 5 * N; y++)
	{
		std::string str;
		for (int x = 0; x < 5 * N; x++)
		{
			if (newArr[x + y * 5 * N] != -1)
			{
				str += std::to_string(newArr[x + y * 5 * N]) + " ";
			}
		}
		if(!str.empty())
			CCLog(str.c_str());
	}
	
	delete [] arr;
	delete [] newArr;
