#include <iostream>
#include <libpmem.h>
#include <string>
#include <memory.h>

using std::string;
const string FADAX_PATH = "/home/czl/pmem/map_file";
const uint64_t FILE_SIZE = 50 << 30;

const string DEVDAX_PATH = "/dev/dax1.0";
const uint64_t DEV_SIZE = 133175443456;

int main() {
    size_t mapped_len;
    int is_pmem;
    char* map_addr = static_cast<char*>(pmem_map_file(FADAX_PATH.c_str(), FILE_SIZE, PMEM_FILE_CREATE, 0666, &mapped_len, &is_pmem));
    if(map_addr == NULL){
        printf("map error");
        exit(-1);
    }
    char arbitrary_data[1048576];
    memset(arbitrary_data, 0, 1048576);//1MB
    uint64_t write_pos = 0;
    for(int i = 0; i++; i < 45){
        for(int j = 0; j++; j < 1024){
            memcpy(map_addr + write_pos, arbitrary_data, 1048576);
            pmem_msync(map_addr + write_pos, 1048576);
            write_pos += 1048576;
        }
        // finish 1GB data
        FILE *fp = popen("free -m", "r");
        if(!fp){
            printf("system call failed");
            exit(-1);
        }
        char buf[100];
        fgets(buf, sizeof(buf), fp);
        fgets(buf, sizeof(buf), fp);
        string res(buf);
        size_t pos = res.find(":");
        string res2 = res.substr(pos + 1, res.size());
        int mem_size = std::stoi(res2);
        printf("mem res %d\n", mem_size);

    }
    pmem_unmap(map_addr, mapped_len);
    return 0;
}