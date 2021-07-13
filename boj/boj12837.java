package com.company;
import java.io.*;
import java.util.*;

public class boj12837 {
    static int N;
    static int Q;
    static long []tree;
    static int ts;

    static void update(int s, long v) {
        s += (ts -1);

        tree[s] += v;

        while(s > 1) {
            s /= 2;
            tree[s] = tree[s*2] + tree[s*2+1];
        }
    }

    static long search(int s, int e) {
        long ret = 0;
        s += (ts - 1);
        e += (ts - 1);

        while(s<=e) {
            if ((s & 1) == 1) {
                ret += tree[s];
                s++;
            }
            if ((e & 1) == 0) {
                ret += tree[e];
                e--;
            }
            s/=2; e/=2;
        }
        return 0;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        tree = new long[N * 4 + 1];
        for (ts = 1; ts <= N; ts *= 2);
        for (int i = 1; i <= Q; ++i) {
            int n, p, q;
            st = new StringTokenizer(br.readLine());
            n = Integer.parseInt(st.nextToken());
            p = Integer.parseInt(st.nextToken());
            q = Integer.parseInt(st.nextToken());

            if (n == 1) update(p, q);
            else System.out.println(search(p, q));

        }
    }
}
