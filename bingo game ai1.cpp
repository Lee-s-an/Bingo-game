#include<iostream>
#include<time.h>
using namespace std;

enum AI_MODE
{
	AM_EASY =1,
	AM_HARD
};

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};
	int iAINumber[25] = {};
	//1~25까지 숫자를 넣어준다.
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	//숫자를 섞어준다.
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;

		//AI 숫자도 섞어준다.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = iTemp;
	}

	int iBingo = 0, iAIBingo = 0;
	int iAIMode;
	//AI 난이도를 선택한다.
	while (true)
	{
		system("cls");
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI 모드를 선택하세요 : ";
		cin >> iAIMode;

		if (iAIMode >= AM_EASY && iAIMode <= AM_HARD)
			break;
	}
	


	//선택안된 목록 배열을 만들어준다.
	int iNoneSelect[25] = {};
	//선택안된 숫자 개수를 저장한다.
	int iNoneSelectCount = 0;
	while (true)
	{
		system("cls");

		//숫자를 5x5로 출력한다.
		cout << "===================player===============" << endl;

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";

				else
					cout << iNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}

		cout << "Bingo Line :" << iBingo << endl << endl;

		//AI 빙고 판을 출력한다.
		cout << "===================Ai===============" << endl;

		switch (iAIMode)
		{
		case AM_EASY:
			cout << "AIMode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "AIMode :HARD" << endl;
			break;
		}

		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iAINumber[i * 5 + j] == INT_MAX)
					cout << "*\t";

				else
					cout << iAINumber[i * 5 + j] << "\t";
			}

			cout << endl;
			
		}

		//AI 빙고 줄 수를 출력한다.
		cout << "AIBingo Line : " << iAIBingo << endl;

		//줄수가 5 이상일 경우 게임을 종료한다.
		if (iBingo >= 5)
		{
			cout << "Player 승리" << endl;
			break;
		}

		else if(iAIBingo >= 5)
		{
			cout << "AI승리" << endl;
			break;
		}

		cout << "숫자를 입력하세요(0 : 종료) :";
		int ilnput;
		cin >> ilnput;

		if (ilnput == 0)
			break;

		else if (ilnput < 1 || ilnput > 25)
			continue;

		//중복입력을 체크하기 위한 변수이다. 기본적으로 중복되었다라고
		//하기 위해 true로 잡아주었다.
		bool bAcc = true;

		//모든 숫자를 차례대로 검사해서 입력한 숫자와 같은 숫자가
		//있는지를 찾아낸다.
		for (int i = 0; i < 25; ++i)
		{
			//같은 숫자가 있을 경우
			if (ilnput == iNumber[i])
			{
				//숫자를 찾았을 경우 중복된 숫자가 아니므로
				//bAcc 변수를 false로 만들어준다.
				bAcc = false;

				//숫잘ㄹ *로 변경하기 위해 특수한 값인 INT_MAX로 해준다.
				iNumber[i] = INT_MAX;

				//더이상 다른 숫자를 찾아볼 필요가 없으므로
				//for문을 빠져나간다.
				break;
			}
		}

		//bAcc변수가 true일 경우 중복된 숫자를 입력해서 숫자를 *로
		//바꾸지 못했으므로 다시 입력받게 continue 해준다.
		if (bAcc)
			continue;

		//중복이 아니라면 Ai의 숫자도 찾아서 *로 바꿔준다.
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == ilnput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		//AI가 선택을 한다. AI가 선택하는 것은 AI모드에 따라서 달라진다.

		switch (iAIMode)
		{
			/*AI Easy 모드는 현재 AI의 숫자목록중 *로 바뀌지 않은 숫자 목록을 만들어서'
			그 목록중 하나를 선택하게 한다. (랜덤하게)
			*/
		case AM_EASY:
			// 선택안된 숫자목록을 만들어준다.
			//선택안된 숫자 개수는 목록을 만들때 카운팅해준다.
			iNoneSelectCount = 0;
			for (int i = 0; i < 25; ++i)
			{
				//현재 숫자가 *이 아닐 경우
				if (iAINumber[i] != INT_MAX)
				{
					//*이 아닌 숫자일 경우 iNoneSelectCount를 인덱스로 할용
					//한다. 선택 안된 목록에 추구하라때마다 개수를 1씩증가
					//시켜서 총 선택안된 개수를 구해준다.
					//그런데 0부터 카운트가 시작이므로 0번에 넣고 ++해서 1개
					//추가되었다 라고 해준다.
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					++iNoneSelectCount;
				}
			}

			//for문을 빠져나오게 되면 선택안된 목록이 만들어지고
			//선택안된 목록의 개수가 만들어지게 된다.
			//선택안된 목록으 숫자중 랜덤한 하나의 숫자를 얻어오기 위해
			//인덱스를 랜덤하게 구해준다.
			ilnput = iNoneSelect[rand() % iNoneSelectCount];
			break;
		case AM_HARD:
			break;
		}

		//Ai가 숫자를 선택했으므로 플레이어와 AI의 숫자를 *로 바꿔준다.
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == ilnput)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}

		//AI 숫자를 바꿔준다.
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == ilnput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		//빙고 줄 수를 체크하는 것은 매번 숫자를 입력할때마다 처음부터
		//새로 카운트를 할것이다. 그러므로 iBingo 변수를 0으로 매번
		//초기화하고 새롭게 줄 수를 구해주도록 한다.
		iBingo = 0;
		iAIBingo = 0;

		//가로, 세로 줄 수를 구해준다.
		int iStar1 = 0, iStar2 = 0;
		int iAIStar1 = 0, iAIStar2 = 0;
		for (int i = 0; i < 5; ++i)
		{
			//한줄을 체크하기 전에 먼저 0으로 별 개수를 초기화한다.
			iStar1 = iStar2 = 0;
			iAIStar1 = iAIStar2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				//가로 별 개수를 구해준다.
				if (iNumber[i * 5 + j] == INT_MAX)
					++iStar1;

				//세로 별 개수를 구해준다.
				if (iNumber[j * 5 + i] == INT_MAX)
					++iStar2;
				
				//AI줄체크
				if (iAINumber[i * 5 + j] == INT_MAX)
					++iAIStar1;

				if (iAINumber[j * 5 + i] == INT_MAX)
					++iAIStar2;
			}

			// j for문을 빠져나오고 나면 현재 줄의 가로 별 개수가 몇개인지
			// iStar1 변수에 들어가게 된다. iStar1의 값이 5이면 한줄이
			//모두 *이라는 의미이므로 빙고 줄 카운트를 추가해준다.
			if (iStar1 == 5)
				++iBingo;

			if (iStar2 == 5)
				++iBingo;

			if (iAIStar1 == 5)
				++iAIBingo;

			if (iAIStar2 == 5)
				++iAIBingo;
		}
		//왼쪽 상단 -> 오른쪽 하단으로가는 대각선 체크
		iStar1 = 0;
		iAIStar1 = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;

			if (iAINumber[i] == INT_MAX)
				++iAIStar1;
		}

		if (iStar1 == 5)
			++iBingo;

		if (iAIStar1 == 5)
			++iAIBingo;

		//오른쪽 상단에서 -> 왼쪽 하단 대각선 체크
		iStar1 = 0;
		iAIStar1 = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;

			if (iAINumber[i] == INT_MAX)
				++iAIStar1;
		}

		if (iStar1 == 5)
			++iBingo;

		if (iAIStar1 == 5)
			++iAIBingo;
	}
	return 0;

}