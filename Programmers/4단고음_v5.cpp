#include <vector>
#include <map>
#include <math.h>

int answer=0;

int solve(int num, int cur_plus){ 
    int result = 0;

        if(num < 1 || num < pow(3, cur_plus/2)) return 0;
        
        if(num == 3){
            if(cur_plus == 2){
                answer++;
                return 1;
            }
            
            return 0;
            
        }
    
        else if(num >3){
            if(num % 3 == 0 && cur_plus >= 2){
                result += solve(num/3, cur_plus-2);
            }

            result +=solve(num-1, cur_plus+1);
        }
    
    
    return result;
        
    
    
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n){
    int _answer = 0;
    
    
    _answer = solve(n,0);
    
    //_answer = answer;
    
    printf("%d %d",answer, _answer);
    
    
    
    return _answer;
}