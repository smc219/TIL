package com.company;
import java.io.*;
import java.util.*;

public class boj14428 {

    static int N;
    static int [] A;
    static int M;
    static int ts;
    static final int INF = Integer.MAX_VALUE;
    static int [] tree;

    static void update(int i, int v) {
        A[i] = v;

        i += (ts - 1);

        while(i > 1) {
            i /= 2;
            if (A[tree[i*2]] < A[tree[i*2+1]]) tree[i] = tree[i*2];
            else if (A[tree[i*2 + 1]] < A[tree[i*2]]) tree[i] = tree[i*2 + 1];
            else tree[i] = Math.min(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    static int search(int s, int e) {
        int ret;
        s += (ts-1);
        e += (ts-1);
        ret = tree[s];
        while(s <= e) {
            if ((s & 1) == 1) {
                if (A[ret] > A[tree[s]]) ret = tree[s];
                else if(A[ret] == A[tree[s]]) ret = Math.min(ret, tree[s]);
                s++;
            }
            if ((e & 1) == 0) {
                if (A[ret] > A[tree[s]]) ret = tree[e];
                else if(A[ret] == A[tree[e]]) ret = Math.min(ret, tree[e]);
                e--;
            }
            s/=2;
            e/=2;
        }
        return ret;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
        N = Integer.parseInt(br.readLine());

        for (ts = 1; ts <= N; ts *= 2);

        tree = new int[N * 4 + 1];
        A = new int[N + 1];
        A[0] = INF;
        st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= N; ++i) {
            A[i] = Integer.parseInt(st.nextToken());
            tree[i+ts-1] = i;
            update(i, A[i]);
        }

        M = Integer.parseInt(br.readLine());

        int n, j, v;
        for (int i = 1; i<= M; ++i){
            st = new StringTokenizer(br.readLine());
            n = Integer.parseInt(st.nextToken());
            j = Integer.parseInt(st.nextToken());
            v = Integer.parseInt(st.nextToken());
            if (n == 1) update(j, v);
            else bw.write(search(j, v) + "\n");
        }
        bw.flush();
    }
}
