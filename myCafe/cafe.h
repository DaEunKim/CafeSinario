#include <string>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "json.h"

#define NUM_MENU 13
#define NUM_BARISTA 4
#define MAX_ORDER 10

#define PATH_BARISTA "/Users/lunahc/Desktop/barista.json"
#define PATH_MENU "/Users/lunahc/Desktop/menu.json"
#define PATH_ORDER "/Users/lunahc/Desktop/order.json"
#define PATH_RESULT "/Users/lunahc/Desktop/result.json"

class State{
public:
    int left_time[NUM_BARISTA] = {0};
    int current_coffee[NUM_BARISTA];
    int current_customer[NUM_BARISTA];
};

class Log{
public:
    int order_time[MAX_ORDER];
    int end_time[MAX_ORDER];
};

class Menu{
public:
    char name[20];
    int cost;
    int id;
    
    void setMenu(int id, const char *name, int cost){
        this->id = id;
        strcpy(this->name, name);
        this->cost = cost;
    }
};

class Barista{
public:
    int id;
    char name[20];
    
    void setBarista(int id, const char *name){
        this->id = id;
        strcpy(this->name, name);
    }
};

class OrderList{
public:
    int orderId;
    int orderTime;
    int nCoffee[NUM_MENU];
    int nLeftCoffee[NUM_MENU];
    
    void setOrderList(int orderId, int orderTime, int *nCoffee){
        this->orderId = orderId;
        this->orderTime = orderTime;
        for(int i=0; i<NUM_MENU; ++i){
            this->nCoffee[i] = nCoffee[i];
            this->nLeftCoffee[i] = nCoffee[i];
        }
    }
    
    int get_cost(Menu menu[]){ // 해당order의 주문의 총합
        int sum = 0;
        for(int i=0; i<NUM_MENU; i++){
            sum += menu[i].cost * nLeftCoffee[i];
        }
        return sum;
    }
    
    bool isOver(){
        for(int i=0; i<NUM_MENU; ++i)
            if(nLeftCoffee[i] != 0)
                return false;
        return true;
    }
};



class Cafe{
public:
    char *read_file(const char *file);
    int write_file(const char* file, const char* buffer, unsigned long len);
    int parse_menu(const char *file);
    int parse_barista(const char *file);
    int parse_order(const char *file);
    int parse_result(const char *file);
    
    /* 1 단위 시간이 지나감... true : 모든 주문 처리 완료 */
    bool go_one_time(int mode);
    
    /* 주문한 coffee가 다 나가면 order_in vector에서 지우는 함수 */
    bool isFin(int mode);
    void remove_if_fin(int order_num, int mode);
    bool Mode1(int id);
    bool Mode2(int id);
    bool Mode3(int id);
    
private:
    int time = 0;
    int latest_order = 0;
    
    Menu menu[NUM_MENU];
    Barista barista[NUM_BARISTA];
    std::vector<OrderList> order;
    std::vector<OrderList> order_in;
    
    Log log;
    State state;
};
