#include "cafe.h"

/* 1 단위 시간이 지나감... true : 모든 주문 처리 완료 */
bool Cafe::go_one_time(int mode)
{
    ++time;
    
    if(isFin(mode)){
        puts("끝~");
        return true;
    }
    
    // 다음 주문 시간이랑 같을 때 == 새로운 주문이 들어감
    if(latest_order < order.size() && time == order[latest_order].orderTime)
        order_in.push_back(order[latest_order++]);
    
    // barista의 일이 끝났을 때
    for(int i=0; i<NUM_BARISTA; ++i)
        if(--state.left_time[i] == 0)
            printf("[%ds]%d번 바리스타가 %d번 손님의 %s를 만들었습니다.\n",
                   time, i, state.current_customer[i], menu[state.current_coffee[i]].name);
    
    // order_in이 비어있을 때
    if(!order_in.size()) return false;
    
    // order_in에 주문이 있고 barista가 비어있을때 주문을 전달
    for(int i=0; i<NUM_BARISTA; ++i)
        if(state.left_time[i] <= 0){
            bool isWork;
            if(mode == 1) isWork = Mode1(i);
            else if(mode == 2) isWork = Mode2(i);
            else if(mode == 3) isWork = Mode3(i);
            if(isWork){
                remove_if_fin(state.current_customer[i], mode);
                printf("[%ds]%d번 바리스타가 %d번 손님의 %s를 만들기 시작했습니다.\n",
                       time, i, state.current_customer[i], menu[state.current_coffee[i]].name);
            }
        }
    return false;
}

bool Cafe::Mode1(int id)
{
    if(!order_in.size()){
        state.current_customer[id] = -1;
        state.left_time[id] = -1;
        state.current_coffee[id] = -1;
        return false;
    }
    for(int i=0; i<NUM_MENU; ++i) // 가장 긴 시간을 가진 coffee를 골라서 barista에서 할당
        if(order_in.front().nLeftCoffee[i] != 0){
            state.left_time[id] = menu[i].cost;
            state.current_coffee[id] = i;
            state.current_customer[id] = order_in.front().orderId;
            --order_in.front().nLeftCoffee[i];
            break;
        }
    return true;
}

bool Cafe::Mode2(int id)
{
    if(!order_in.size()){
        state.current_customer[id] = -1;
        state.left_time[id] = -1;
        state.current_coffee[id] = -1;
        return false;
    }
    for(int i=0; i<NUM_MENU; ++i) // 가장 긴 시간을 가진 coffee를 골라서 barista에서 할당
        if(order_in.front().nLeftCoffee[i] != 0){
            state.left_time[id] = menu[i].cost;
            state.current_coffee[id] = i;
            state.current_customer[id] = order_in.front().orderId;
            --order_in.front().nLeftCoffee[i];
            break;
        }
    return true;
}

bool Cafe::Mode3(int id)
{
    if(!order_in.size()){
        state.current_customer[id] = -1;
        state.left_time[id] = -1;
        state.current_coffee[id] = -1;
        return false;
    }
    
    for(int i=NUM_MENU-1; i>=0; --i){ // 가장 긴 시간을 가진 coffee를 골라서 barista에서 할당
        int orderNum = 0;
        for(auto o : order_in){
            if(o.nLeftCoffee[i] > 0){
                --order_in[orderNum].nLeftCoffee[i];
                state.left_time[id] = menu[i].cost;
                state.current_coffee[id] = i;
                state.current_customer[id] = o.orderId;
                goto out;
            }
            ++orderNum;
        }
    }
out:;
    return true;
};

bool Cafe::isFin(int mode)
{
    if(order.size() != latest_order) return false;
    if(order_in.size()) return false;
    for(auto i : state.left_time)
        if(i > 0) return false;
    return true;
}

void Cafe::remove_if_fin(int order_id, int mode)
{
    int minimum_cost = MAX_ORDER*100;
    
    int selected_order = 0;
    OrderList tmp_order;
    for(auto i=order_in.begin(); i!=order_in.end(); ++i)
        if(i->orderId == order_id)
            if(i->isOver()){
                order_in.erase(i);
                log.end_time[order_id] = time;
                
                if(mode == 2){
                    for(int i=0; i<order.size(); i++)
                        if(minimum_cost > order[i].get_cost(menu)){
                            minimum_cost = order[i].get_cost(menu);
                            selected_order = i;
                        }
                        
                    tmp_order = order_in.front();
                    order_in.front() = order_in[selected_order];
                    order_in[selected_order]  = tmp_order;
                }
                break;
            }
}



//
//
// main
int main(int argc, const char * argv[])
{
    Cafe cafe;
    
    cafe.parse_barista(PATH_BARISTA);
    cafe.parse_menu(PATH_MENU);
    cafe.parse_order(PATH_ORDER);
    
    char mode_in[10];
    int mode, leftTime;
    
    while(1){
        fputs("Mode를 선택하세요[1-3]\n >> ", stdout);
        scanf("%s", mode_in);
        if(!strcmp(mode_in, "1")){printf("FIFO mode selected\n"); mode = 1; break;}
        if(!strcmp(mode_in, "2")){printf("Prediction mode selected\n"); mode = 2; break;}
        if(!strcmp(mode_in, "3")){printf("Disorder mode selected\n"); mode = 3; break;}
    }
    
    while(1){
        fputs("실행시킬 시간을 입력하세요[0-10,000].\n >> ", stdout);
        scanf("%d", &leftTime);
        
        while(leftTime--)
            if(cafe.go_one_time(mode)){
                cafe.parse_result(PATH_RESULT);
                return 0;
            }
    }
}// main
