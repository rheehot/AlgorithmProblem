#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector< pair<int, int> > lock_zip;
vector< pair<int, int> > key_zip;

int LOCK_SIZE = 0;
int KEY_SIZE = 0;

inline pair<int, int> Bangle(int y, int x){
    pair<int, int> temp;
    temp.first = x;
    temp.second = -y+(KEY_SIZE-1);
    
    return temp;
}


int Check(vector< pair<int, int> > temp){
    
    if(lock_zip.size() == 0){
        if(key_zip.size() == 0)
            return 1;
        
        for(int i=0; i<temp.size(); i++){
            if((temp[i].first ==  0 && temp[i].second == 0) ||
              (temp[i].first ==  0 && temp[i].second == KEY_SIZE-1) ||
              (temp[i].first ==  KEY_SIZE-1 && temp[i].second == 0) ||
              (temp[i].first ==  KEY_SIZE-1 && temp[i].second == KEY_SIZE-1))
                return 1;
        }
        
        return 0;
        
        
    }
    
    if(key_zip.size() == 0)
        return 0;
    
    pair<int, int> start = lock_zip[0];
    
    int start_y = start.first;
    int start_x = start.second;
    
    for(int i=0; i<temp.size(); i++){
    
        int y_weight = start_y - temp[i].first;
        int x_weight = start_x - temp[i].second;
        
        if(key_zip.size()-(i+1) < lock_zip.size())
            return 0;
        
        int answer_count = 0;
        int out_check[400] = {0,};
        int out_count = 0;
        
        for(int k =0; k<temp.size(); k++){
            if(0<= temp[k].first + y_weight && temp[k].first + y_weight < LOCK_SIZE && 
               0<= temp[k].second + x_weight && temp[k].second + x_weight < LOCK_SIZE){
                continue;
            }
            else{
                out_count++;
                out_check[k] = 1;
            }
        }

        for(int j = 0; j<lock_zip.size(); j++){
            for(int temp_count = 0; temp_count< temp.size(); temp_count++){
                if(temp[temp_count].first + y_weight == lock_zip[j].first &&
                   temp[temp_count].second + x_weight == lock_zip[j].second &&
                   out_check[temp_count] == 0){
                        answer_count++;
                        break;
                    }
            }
            
        }
        
            printf("%d %d\n",answer_count, out_count);
        if(answer_count == lock_zip.size() && temp.size() - out_count == answer_count){

            return 1;
        }
        
    }
    
    return 0;
}

//Clock Right (1/2*radian)
int Rotate(){
    
    vector< pair<int, int> > temp;

    
    for(int i=0; i<key_zip.size(); i++){
        pair<int, int> after_rotate = Bangle(key_zip[i].first, key_zip[i].second);
        temp.push_back({after_rotate.first,after_rotate.second});
    }
    
    
    sort(temp.begin(), temp.end());
   

    
    if(Check(temp))
        return 1;
    
    key_zip = temp;
    
    return 0;
}


bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = false;
    
    LOCK_SIZE = lock.size();
    KEY_SIZE = key.size();    
    
    for(int i=0; i<LOCK_SIZE; i++){
        for(int j=0; j<LOCK_SIZE; j++){
            if(lock[i][j] == 0){
                lock_zip.push_back({i,j});
            }
        }
    }
    
    for(int i=0; i<KEY_SIZE; i++){
        for(int j=0; j<KEY_SIZE; j++){
            if(key[i][j] == 1){
                key_zip.push_back({i,j});
            }
        }
    }
    
    for(int i=0; i<4; i++){
        if(Rotate()){
            return true;
        }
    }
    
    
    return answer;
}