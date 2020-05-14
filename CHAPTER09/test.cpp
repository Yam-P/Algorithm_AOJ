/*

*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring> //memset
using namespace std;

const int MAX = 2000000000 + 1; //오버플로우 방지
int length;
int cacheLength[501], cacheCount[501], S[500];
//S[start]에서 시작하는 증가 부분 수열 중 최대 길이 반환
int LIS(int start)
{

        //메모이제이션

        int &result = cacheLength[start + 1];

        if (result != -1)

               return result;

        //항상 S[start]는 있기 때문에 길이는 최하 1

        result = 1;

        for (int next = start + 1;next < length; next++)

               if (start == -1 || S[start] < S[next]) //처음 인덱스이거나 증가 부분 수열 조건을 만족할 경우

                       result = max(result, LIS(next) + 1);

        return result;

}

 

//S[start]에서 시작하는 최대 증가 부분 수열의 수 반환

int count(int start)

{
        //기저 사례:LIS의 길이가 1인 경우
        if (LIS(start) == 1)
               return 1;
        //메모이제이션
        int &result = cacheCount[start + 1];
        if (result != -1)
               return result;
        result = 0;
        for (int next = start + 1;next < length;next++)
               //처음이거나 증가부분 수열을 만족하고 next가 start 다음에 오는 숫자이니 증가부분 수열의 길이는 start에서 시작하는 쪽이 next에서 시작하는 쪽보다 1 길어야한다.
               if ((start == -1 || S[start] < S[next]) && LIS(start) == LIS(next) + 1)
                       result = min<long long>(MAX, (long long)result + count(next)); //오버플로우 방지 위해 임의로 64비트 숫자
        return result;
}
//K번째 LIS 구하기
//S[start]에서 시작하는 LIS 중 사전순으로 skip개 건너뛴 수열을
//lis에 저장

void reconstruct(int start, int skip, vector<int> &lis)

{
        //1. S[start]는 항상 LIS에 포함
        if (start != -1)
               lis.push_back(S[start]);
        //2. 뒤에 올 수 있는 숫자들과 위치의 목록을 만든다
        //(숫자, 숫자의 위치)의 목록
        vector<pair<int, int>> followers;
        for (int next = start + 1; next < length; next++)
               //처음이거나 증가부분 수열을 만족하고 next가 start 다음에 오는 숫자이니 증가부분 수열의 길이는 start에서 시작하는 쪽이 next에서 시작하는 쪽보다 1 길어야한다.
               if ((start == -1 || S[start] < S[next]) && LIS(start) == LIS(next) + 1)
                       followers.push_back(make_pair(S[next], next));
        sort(followers.begin(), followers.end()); //정렬

        //3. k번쨰 LIS의 다음 숫자를 찾는다
        for (int i = 0; i < followers.size(); i++)
        {
               //이 숫자를 뒤에 이어서 만들 수 있는 LIS의 개수를 확인
               int idx = followers[i].second;
               int cnt = count(idx);
               if (cnt <= skip) //이 숫자를 뒤에 이어서 만들 수 있는 LIS의 개수가 skip보다 작다면 skip을 줄이고 건너뛴다
                       skip -= cnt;
               else
               {
                       //다음 숫자는 S[idx]임을 확인
                       //재귀호출
                       reconstruct(idx, skip, lis);
                       break;
               }
        }
}

 

int main(void)

{

        int test_case;

        cin >> test_case;

        if (test_case < 1 || test_case>50)

               exit(-1);

 

        for (int i = 0; i < test_case; i++)

        {

               int K; //K번째

               cin >> length >> K;

               if (length > 500 || length < 1)

                       exit(-1);

               for (int j = 0; j < length; j++)

               {

                       cin >> S[j];

                       if (S[j] < 1 || S[j]>100000)

                              exit(-1);

               }

               memset(cacheCount, -1, sizeof(cacheCount));

               memset(cacheLength, -1, sizeof(cacheLength));

               cout << LIS(-1) - 1 << endl; //최대 길이

               vector<int> result;

               cout << count(-1) << "\n";

               cout << endl;

        }

        return 0;

}
