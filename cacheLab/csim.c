//
// Created by 석민창 on 2021/02/04.
//

#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "cachelab.h"
#include <stdio.h>
#define DEBUG 1
typedef struct l {
    char valid;
    int tag;
} line;

typedef struct s {
    line * lines;
}set;

typedef struct c{
    set * sets;
}cache;

cache C;

int setNum;
int lineNum;
int bNum;
FILE * F;

//int main(int argc, char ** argv)
int main(void)
{
#IF !DEBUG
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
                setNum = 2 << atoi(optarg)
                break;
            case 'E':
                lineNum = atoi(optarg)
                break;
            case 'b':
                bNum = atoi(optarg)
                break;
            case 't':
                F = fopen(optarg, 'r')
            case '?':
                break;
            case default:
                print("Wrong!\n")
                return 1;
        }
    }
#ENDIF
    setNum = 1;

    // 일단 캐시를 만들어보자! setNum * set Size를 malloc 해주면 캐시가 되고, Set은 0으로 초기화된 Line들로 만들면 된다.
    C = (cache *)malloc(sizeof(s) * setNum);
    for (int i = 0; i < setNum; ++i) {
        C.sets[i] = (set *)calloc(sizeof(line) * lineNum);
    }
    char inst;
    int addr;

    while(fscanf(F, "%c %x%*c%*x",&inst, &addr ))
    {
        if (inst == 'I') continue;

        // 여기서부터 LRU Simulate
        // Set Bit만 출력해야한다. 일단 당연히 Block Size를 민 애를 하나 준비
        int blockDel = addr >> bNum;
        // 이렇게 될 경우에 blockDel 앞에 남는 애는 태그 + 세트. 그러면 여기서 태그만 날리고 싶다. 0x7fffffff을 tag + block 비트만큼 밀어버리자
        // 왜 0x7fffffff인가? Bits.c 때 당해봐서 알겠지만 앞에 1이면 당겨올때 1비트씩 찾다. 그래서 맨앞은 0을 해줘야... tag가 없진 않겠지
        int setIx = (0x7fffffff >> (31 - setNum)) & blockDel;
        int tag = (0xffffffff >> (setNum + bNum)) & addr;




    }
    printSummary(0, 0, 0);
    return 0;
}

