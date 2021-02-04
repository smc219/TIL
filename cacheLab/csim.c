#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "cachelab.h"
#include <stdio.h>

typedef struct l {
    char valid;
    int tag;
    int timestamp;
} line;

typedef struct s {
    line * lines;
}set;

typedef struct c{
    set * sets;
}cache;

cache C={};

int setNum;
int lineNum;
int bNum;
FILE * F = 0;
char buffer[100];
size_t miss;
size_t hit;
size_t eviction;

int main(int argc, char ** argv)
{
    printf("%lu\n", sizeof(line));
    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                break;
            case 'v':
                break;
            case 's':
                setNum = 2 << atoi(optarg);
                break;
            case 'E':
                lineNum = atoi(optarg);
                break;
            case 'b':
                bNum = atoi(optarg);
                break;
            case 't':
                F = fopen(optarg, "r");
		if (F == NULL)
		{
		    printf("%s", optarg);
		    return 1;
		}
		break;
            case '?':
                break;
            default:
                return 1;
        }
    }
    setNum = 1;
    printf("%d\n", !F);
    // 일단 캐시를 만들어보자! setNum * set Size를 malloc 해주면 캐시가 되고, Set은 0으로 초기화된 Line들로 만들면 된다.
    C.sets = malloc(sizeof(set) * setNum);
    for (int i = 0; i < setNum; ++i) {
        C.sets[i].lines = (line *)calloc(sizeof(line), lineNum);
    }

    char inst = 0;
    long long int addr = 0;
    while(fgets(buffer, sizeof(buffer), F) != NULL) // 대체 왠지 모르겠으나 fscanf는 계속 실패했고... fgets로 바꾸니 거짓말같이 들어간다..
    {
	if (buffer[0] == 'I') continue;
	
        int i;
        // 여기서부터 LRU Simulate
        // Set Bit만 출력해야한다. 일단 당연히 Block Size를 민 애를 하나 준비
        int blockDel = addr >> bNum;
        // 이렇게 될 경우에 blockDel 앞에 남는 애는 태그 + 세트. 그러면 여기서 태그만 날리고 싶다. 0x7fffffff을 tag + block 비트만큼 밀어버리자
        // 왜 0x7fffffff인가? Bits.c 때 당해봐서 알겠지만 앞에 1이면 당겨올때 1비트씩 찾다. 그래서 맨앞은 0을 해줘야... tag가 없진 않겠지
        int setIx = (0x7fffffff >> (31 - setNum)) & blockDel;
        int tag = (0xffffffff >> (setNum + bNum)) & addr;
	printf("Set Ic : %d, tag : %d\n", setIx, tag); 
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


        for (i = 0; i < lineNum && C.sets[setIx].lines[i].valid; ++i) {
            // 1.1. 에 해당
            if (C.sets[setIx].lines[i].tag == tag)
            {
                hit++;
                break;
            }
        }
        // 1.2에 해당
        if (i < lineNum)
        {
            C.sets[setIx].lines[i].valid = 1;
            C.sets[setIx].lines[i].tag = tag;
            C.sets[setIx].lines[i].timestamp = i;
            miss++;
        }
        else if(i == lineNum)
        {
            // Eviction이 발생
            for (int j = 0; j < lineNum; ++j)
            {
                if (C.sets[setIx].lines[j].timestamp == 0)
                {
                    C.sets[setIx].lines[i].valid = 1;
                    C.sets[setIx].lines[i].tag = tag;
                    C.sets[setIx].lines[i].timestamp = lineNum - 1;
                }
                else C.sets[setIx].lines[i].timestamp--;
            }
            eviction++;
            miss++;
        }

        if (inst == 'M') hit++;

    }
    printSummary(hit, miss, eviction);
    return 0;
}