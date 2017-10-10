#include "cafe.h"

char* Cafe::read_file(const char *file)
{
    int fd;
    if((fd = open(file, O_RDONLY)) <= 0){
        perror(file);
        return NULL;
    }
    
    struct stat st;
    if(fstat(fd, &st) < 0){
        perror("Stat error");
        return NULL;
    }
    int file_size = (int)st.st_size;
    
    char *buf;
    if((buf = (char*)malloc(sizeof(char)*file_size)) == NULL){
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }
    
    if(read(fd, buf, file_size) < file_size){
        fprintf(stderr, "File read error\n");
        return NULL;
    }
    
    return buf;
}

int Cafe::parse_menu(const char *file)
{
    int i;
    char *buf = read_file(file);
    free(buf);
    
    std::string str_menu = buf;
    Json::Value root;
    Json::Reader reader;
    
    if (!reader.parse(str_menu, root)){
        puts(reader.getFormatedErrorMessages().c_str());
        return -1;
    }
    
    i=0;
    for(auto c : root)
        menu[i++].setMenu(c["id"].asInt(), c["name"].asCString(), c["cost"].asInt());
    
    
    return 0;
}

int Cafe::parse_barista(const char *file)
{
    int i;
    char *buf = read_file(file);
    
    std::string str_barista = buf;
    free(buf);
    Json::Value root;
    Json::Reader reader;
    
    if (!reader.parse(str_barista, root)){
        puts(reader.getFormatedErrorMessages().c_str());
        return -1;
    }
    
    i=0;
    for(auto c : root)
        barista[i++].setBarista(c["id"].asInt(), c["name"].asCString());
    
    
    return 0;
}

int Cafe::parse_order(const char *file)
{
    int i;
    char *buf = read_file(file);
    
    std::string str_order = buf;
    free(buf);
    
    Json::Value root;
    Json::Reader reader;
    
    if (!reader.parse(str_order, root)){
        puts(reader.getFormatedErrorMessages().c_str());
        return -1;
    }
    
    i=0;
    int orderId = 0;
    int orderTime = 0;
    int nCoffee[NUM_MENU] = {0};
    for(auto c : root){
        for(auto d : c){
            int id = d["id"].asInt();
            nCoffee[id] += d["quantity"].asInt();
            orderTime = d["Order Time"].asInt();
        }
        OrderList *order = new OrderList();
        order->setOrderList(orderId++, orderTime++, nCoffee);
        this->order.emplace_back(*order);
    }
    
    return 0;
}

int Cafe::write_file(const char* filename, const char* buffer, unsigned long len)
{
    FILE* fp = fopen(filename, "wb");
    
    if (fp == NULL){
        puts("Write file open error");
    	return -1;
    }
    
    fwrite(buffer, 1, len, fp);
    
    fclose(fp);
    return 0;
}

int Cafe::parse_result(const char *file)
{    
    Json::Value root;
    int nOrder = (int)order.size();
    
    for(int i=0; i<nOrder; ++i){
        Json::Value order;
        order["id"] = i+1;
        order["orderTime"] = this->order[i].orderTime;
        order["endTime"] = log.end_time[i];
#include <string>
        for(int c=0; c<NUM_MENU; ++c)
            order[std::to_string(c)] = this->order[i].nCoffee[c];
        
        root[std::to_string(i)] = order;
    }
    
    Json::StyledWriter writer;
    std::string outputConfig = writer.write( root );
    return write_file(file, outputConfig.c_str(), outputConfig.length());
}
