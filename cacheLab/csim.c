/*
 * <2월 9일자 실수>
 * Eviction은 꼭 라인이 다 차있을때만 발생하는게 아니다 -> timestamp 잘못 잡음
 * 반복문 내부에서의 변수값 변화와 반복문 외부에서의 변수값 변화를 잘 구분해줄 것. -> 기초적인 디버깅
 *
 * <2월 8일자 실수>
 * 1. 첫번째로 틀린 지점 -> line의 경우에는 j가 들어가야하는 곳에 i를 집어넣음
 * 2. set ix가 최대한으로 가질 수 있는 숫자와 set bit 자체는 다르다
 * 3. 함수화가 왜 필요한지 알 수 있었음 -> hit가 뜨면 리턴 시키면 되는데, 지금은 굳이 플래그를 만들어 줘야한다..
 * */

#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "cachelab.h"
#include <stdio.h>

typedef struct l {
    int valid;
    unsigned long long tag;
    int timestamp;
} line;

typedef struct s {
    line * lines;
} set;

typedef struct c {
    set * sets;
} cache;

cache C = {};

int setNum;
int lineNum;
int bNum;
FILE *F = 0;
char buffer[100];
size_t miss;
size_t hit;
size_t eviction;

void debug(void)
{
    // printf("\ndebug start\n");
    for (int i = 0; i < (1 << setNum); ++i)
    {
        // printf("SET[%d]\n", i);
        for (int j = 0; j < lineNum; ++j)
        {
            // printf("%lld ", C.sets[i].lines[j].tag);
        }
        // printf("\n");
    }
    // printf("\ndebug end\n");
}

void simulate(char inst, unsigned long long addr)
{


    // printf("\n\n");
    int i;
    unsigned long long tag = addr >> (bNum+ setNum); // 태그만 남는다.
    // printf("%lld, %lld\n", (addr >> bNum), (tag << setNum));
    int setIx = (addr >> bNum) - (tag << setNum); // 빼기를 통해서 tag 부분을 없애주는 것이 가능하다.
    // printf("Set Ix : %d, tag : %lld\n", setIx, tag);
    // 그리고 나서 해야될게 뭘까? 입력이 들어오면 set Ix 만큼 돌아줘야한다.
    /*
    addr이 들어오고 전처리가 완료.
    setIx를 알았으니 해당 set의 라인을 돌면서 태그가 있는지 확인한다.
     1. 밸리드를 만난 경우
        1.1. 만났는데 태그가 같은 경우
            hit++해준다.
        1.2. 만났는데 태그가 다른 경우
            다음 라인으로 넘어간다.
     2. 밸리드를 만나지 못한 경우
        못한 경우에는 miss++ 해주고 끝난다.
     3. 끝까지 간 경우
        결국 못찾았기 때문에 타임스탬프에서 0인 애를 찾는다(for 문 이용)
        0을 만나면? 0위치에 있는 태그를 지금 태그로 바꾸고, lineNum을 타임스탬프에 넣어준다.
        0이 아닌애를 만나면? 그냥 다 --해준다.
        eviction++ 해주고, miss++ 해준다.
    마지막에 inst를 확인해주고 만약 M이었다면 hit도 하나 늘려준다.
    */

    if (inst == 'M') hit++;
    for (i = 0; i < lineNum; ++i) {
        // 1.1. 에 해당

        // printf("Val Num ? : %d\n", C.sets[setIx].lines[i].valid );

        if(C.sets[setIx].lines[i].valid == 0)
        {
            // printf("Val = 0\n");
            break;
        }
        else if (C.sets[setIx].lines[i].tag == tag) {
            hit++;
            // printf("hit In\n");
            // 원래 이 부분에 timestamp를 업데이트해주는 애가 없었음.
            int ts = C.sets[setIx].lines[i].timestamp;
            int max = 0;
            for (int j = 0; j < lineNum; ++j)
            {
                max = max < C.sets[setIx].lines[j].timestamp ? C.sets[setIx].lines[j].timestamp : max;
                if(ts < C.sets[setIx].lines[j].timestamp)
                {
                    C.sets[setIx].lines[j].timestamp--;
                }
            }

            C.sets[setIx].lines[i].timestamp = max;

            // printf("Hit End\n");
            return;
        }
    }
    // printf("ok 1\n");
    // 1.2에 해당
    miss++;
    if (i < lineNum) {
        C.sets[setIx].lines[i].valid = 1;
        C.sets[setIx].lines[i].tag = tag;
        C.sets[setIx].lines[i].timestamp = i;
        // printf("Miss In\n");

    } else if (i >= lineNum) {
        // Eviction이 발생
        for (int j = 0; j < lineNum; ++j) {
            if (C.sets[setIx].lines[j].timestamp == 0) {
                C.sets[setIx].lines[j].tag = tag;
                C.sets[setIx].lines[j].timestamp = lineNum - 1;
            } else C.sets[setIx].lines[j].timestamp--;
        }
        eviction++;
        // printf("eviction In\n");
    }

    // printf("ok 2\n");
    // printf("\n\n");
}

int main(int argc, char **argv) {
    // printf("%lu\n", sizeof(line));
    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (opt) {
            case 'h':
                break;
            case 'v':
                break;
            case 's':
                setNum = atoi(optarg);
                break;
            case 'E':
                lineNum = atoi(optarg);
                break;
            case 'b':
                bNum = atoi(optarg);
                break;
            case 't':
                F = fopen(optarg, "r");
                if (F == NULL) {
                    // printf("%s", optarg);
                    return 1;
                }
                break;
            case '?':
                break;
            default:
                return 1;
        }
    }
    // printf("%d\n", !F);
    // 일단 캐시를 만들어보자! setNum * set Size를 malloc 해주면 캐시가 되고, Set은 0으로 초기화된 Line들로 만들면 된다.
    C.sets = (set * )malloc(sizeof(set) *(1 <<  setNum));
    // printf("setnum 1<< : %d\n", 1 <<  setNum);
    for (int i = 0; i < (1 << setNum); ++i) {
        C.sets[i].lines = (line *) calloc(lineNum, sizeof(line));
    }
    char inst = 0;
    long long int addr = 0;
    while (fgets(buffer, sizeof(buffer), F) != NULL) // 대체 왠지 모르겠으나 fscanf는 계속 실패했고... fgets로 바꾸니 거짓말같이 들어간다..
    {
        if (buffer[0] == 'I') continue;
        // 이 단계에서 sscanf를 통해서 값을 입력 받는다.
        sscanf(buffer, " %c %llx,%*d", &inst, &addr);
        // printf("buffer : %s  inst : %c  addr : %lld\n", buffer, inst, addr);
        // 여기서부터 LRU Simulate
        // Set Bit만 출력해야한다. 일단 당연히 Block Size를 민 애를 하나 준비
        // 이렇게 될 경우에 blockDel 앞에 남는 애는 태그 + 세트. 그러면 여기서 태그만 날리고 싶다


        simulate(inst, addr);

    }
    // printf("%d %d\n", lineNum, setNum);
    printSummary(hit, miss, eviction);
    return 0;
}/*
 * <2월 8일자 실수>
 * 1. 첫번째로 틀린 지점 -> line의 경우에는 j가 들어가야하는 곳에 i를 집어넣음
 * 2. set ix가 최대한으로 가질 수 있는 숫자와 set bit 자체는 다르다
 * 3. 함수화가 왜 필요한지 알 수 있었음 -> hit가 뜨면 리턴 시키면 되는데, 지금은 굳이 플래그를 만들어 줘야한다..
 * */

#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "cachelab.h"
#include <stdio.h>

typedef struct l {
    int valid;
    unsigned long long tag;
    int timestamp;
} line;

typedef struct s {
    line * lines;
} set;

typedef struct c {
    set * sets;
} cache;

cache C = {};

int setNum;
int lineNum;
int bNum;
FILE *F = 0;
char buffer[100];
size_t miss;
size_t hit;
size_t eviction;

void debug(void)
{
    // printf("\ndebug start\n");
    for (int i = 0; i < (1 << setNum); ++i)
    {
        // printf("SET[%d]\n", i);
        for (int j = 0; j < lineNum; ++j)
        {
            // printf("%lld ", C.sets[i].lines[j].tag);
        }
        // printf("\n");
    }
    // printf("\ndebug end\n");
}

void simulate(char inst, unsigned long long addr)
{


    // printf("\n\n");
    int i;
    unsigned long long tag = addr >> (bNum+ setNum); // 태그만 남는다.
    // printf("%lld, %lld\n", (addr >> bNum), (tag << setNum));
    int setIx = (addr >> bNum) - (tag << setNum); // 빼기를 통해서 tag 부분을 없애주는 것이 가능하다.
    // printf("Set Ix : %d, tag : %lld\n", setIx, tag);
    // 그리고 나서 해야될게 뭘까? 입력이 들어오면 set Ix 만큼 돌아줘야한다.
    /*
    addr이 들어오고 전처리가 완료.
    setIx를 알았으니 해당 set의 라인을 돌면서 태그가 있는지 확인한다.
     1. 밸리드를 만난 경우
        1.1. 만났는데 태그가 같은 경우
            hit++해준다.
        1.2. 만났는데 태그가 다른 경우
            다음 라인으로 넘어간다.
     2. 밸리드를 만나지 못한 경우
        못한 경우에는 miss++ 해주고 끝난다.
     3. 끝까지 간 경우
        결국 못찾았기 때문에 타임스탬프에서 0인 애를 찾는다(for 문 이용)
        0을 만나면? 0위치에 있는 태그를 지금 태그로 바꾸고, lineNum을 타임스탬프에 넣어준다.
        0이 아닌애를 만나면? 그냥 다 --해준다.
        eviction++ 해주고, miss++ 해준다.
    마지막에 inst를 확인해주고 만약 M이었다면 hit도 하나 늘려준다.
    */

    if (inst == 'M') hit++;
    for (i = 0; i < lineNum; ++i) {
        // 1.1. 에 해당

        // printf("Val Num ? : %d\n", C.sets[setIx].lines[i].valid );

        if(C.sets[setIx].lines[i].valid == 0)
        {
            // printf("Val = 0\n");
            break;
        }
        else if (C.sets[setIx].lines[i].tag == tag) {
            hit++;
            // printf("hit In\n");
            // 원래 이 부분에 timestamp를 업데이트해주는 애가 없었음.
            int ts = C.sets[setIx].lines[i].timestamp;
            int max = 0;
            for (int j = 0; j < lineNum; ++j)
            {
                max = max < C.sets[setIx].lines[j].timestamp ? C.sets[setIx].lines[j].timestamp : max;
                if(ts < C.sets[setIx].lines[j].timestamp)
                {
                    C.sets[setIx].lines[j].timestamp--;
                }
            }

            C.sets[setIx].lines[i].timestamp = max;

            // printf("Hit End\n");
            return;
        }
    }
    // printf("ok 1\n");
    // 1.2에 해당
    miss++;
    if (i < lineNum) {
        C.sets[setIx].lines[i].valid = 1;
        C.sets[setIx].lines[i].tag = tag;
        C.sets[setIx].lines[i].timestamp = i;
        // printf("Miss In\n");

    } else if (i >= lineNum) {
        // Eviction이 발생
        for (int j = 0; j < lineNum; ++j) {
            if (C.sets[setIx].lines[j].timestamp == 0) {
                C.sets[setIx].lines[j].tag = tag;
                C.sets[setIx].lines[j].timestamp = lineNum - 1;
            } else C.sets[setIx].lines[j].timestamp--;
        }
        eviction++;
        // printf("eviction In\n");
    }

    // printf("ok 2\n");
    // printf("\n\n");
}

int main(int argc, char **argv) {
    // printf("%lu\n", sizeof(line));
    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (opt) {
            case 'h':
                break;
            case 'v':
                break;
            case 's':
                setNum = atoi(optarg);
                break;
            case 'E':
                lineNum = atoi(optarg);
                break;
            case 'b':
                bNum = atoi(optarg);
                break;
            case 't':
                F = fopen(optarg, "r");
                if (F == NULL) {
                    // printf("%s", optarg);
                    return 1;
                }
                break;
            case '?':
                break;
            default:
                return 1;
        }
    }
    // printf("%d\n", !F);
    // 일단 캐시를 만들어보자! setNum * set Size를 malloc 해주면 캐시가 되고, Set은 0으로 초기화된 Line들로 만들면 된다.
    C.sets = (set * )malloc(sizeof(set) *(1 <<  setNum));
    // printf("setnum 1<< : %d\n", 1 <<  setNum);
    for (int i = 0; i < (1 << setNum); ++i) {
        C.sets[i].lines = (line *) calloc(lineNum, sizeof(line));
    }
    char inst = 0;
    long long int addr = 0;
    while (fgets(buffer, sizeof(buffer), F) != NULL) // 대체 왠지 모르겠으나 fscanf는 계속 실패했고... fgets로 바꾸니 거짓말같이 들어간다..
    {
        if (buffer[0] == 'I') continue;
        // 이 단계에서 sscanf를 통해서 값을 입력 받는다.
        sscanf(buffer, " %c %llx,%*d", &inst, &addr);
        // printf("buffer : %s  inst : %c  addr : %lld\n", buffer, inst, addr);
        // 여기서부터 LRU Simulate
        // Set Bit만 출력해야한다. 일단 당연히 Block Size를 민 애를 하나 준비
        // 이렇게 될 경우에 blockDel 앞에 남는 애는 태그 + 세트. 그러면 여기서 태그만 날리고 싶다


        simulate(inst, addr);

    }
    // printf("%d %d\n", lineNum, setNum);
    printSummary(hit, miss, eviction);
    return 0;
}