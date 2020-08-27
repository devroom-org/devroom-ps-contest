#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull MOD = 1e9 + 7;
int a[1010101];
int tree[4040404];
int N, Q;
int init(int node, int start, int end) {
    if (start == end) {
        return tree[node] = a[start];
    } else {
        return tree[node] = ((ull) init(node << 1, start, (start + end) >> 1) * (ull) init((node << 1) | 1, ((start + end) >> 1) + 1, end)) % MOD;
    }
}
int calc(int node, int start, int end, int left, int right) {
    if (left > end || right < start) {
        return 1;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    return ((ull) calc(node << 1, start, (start + end) >> 1, left, right) * (ull) calc((node << 1) | 1, ((start + end) >> 1) + 1, end, left, right)) % MOD;
}
int update(int node, int start, int end, int index) {
    if (index < start || index > end) return tree[node];
    if (start != end) {
        ull l = update(node << 1, start, (start + end) >> 1, index);
        ull r = update((node << 1) | 1, ((start + end) >> 1) + 1, end, index);
        return tree[node] = (l * r) % MOD;
    } else {
        return tree[node] = a[index];
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }
    init(1, 0, N - 1);
    while (Q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            cout << calc(1, 0, N - 1, l, r) << '\n';
        } else {
            int i, x;
            cin >> i >> x;
            a[--i] = x;
            update(1, 0, N - 1, i);
        }
    }
}