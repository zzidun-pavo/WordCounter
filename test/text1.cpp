#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxa = 1000000;
const int maxn = 100100;

static bitset<1100100> isNotPrime;
static int prime[maxn], primeId[1100100], pcnt;
static int qidian;

void initPrime()
{
    pcnt = 0;
    isNotPrime[1] = 1;
    qidian = 1;
    for(int i = 2; i <= maxa; ++i){
        if(!isNotPrime[i]){
            prime[++pcnt] = i;
            primeId[i] = pcnt;
            if(i < 1000) qidian++;
        }
        for(int j = 1; j <= pcnt; ++j){
            if(1ll*i*prime[j] > maxa) break;
            isNotPrime[i*prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}

static int n, a[maxn];
static vector<int> G[maxn];
static int to[maxn<<1], ecnt = 1;

int add(int x)
{
    int dcnt = 0, div[4];
    for(int i = 1; i <= pcnt; ++i)
    {
        if(prime[i] * prime[i] > x) break;
        if(x % prime[i] == 0)
        {
            while(x % (prime[i]*prime[i]) == 0) x /= prime[i]*prime[i];
            if(x % prime[i] == 0) div[++dcnt] = i, x/= prime[i];
        }
    }
    if(x > 1) div[++dcnt] = primeId[x];
    if(!dcnt) return 1;
    else if(dcnt == 1){
        G[0].push_back(++ecnt); to[ecnt] = div[1];
        G[div[1]].push_back(++ecnt); to[ecnt] = 0;
    }else if(dcnt == 2){
        G[div[1]].push_back(++ecnt); to[ecnt] = div[2];
        G[div[2]].push_back(++ecnt); to[ecnt] = div[1];
    }
    return 0;
}

static int siz, dep[maxn];
void bfs(int x)
{
    if(G[x].size() == 0) return;
    fill(dep, dep+80000, 0x3f3f3f3f);
    queue<pair<int,int> > que;
    que.push(make_pair(x, 0));
    dep[x] = 0;
    while(que.size())
    {
        int u = que.front().first;
        int path = que.front().second;

        for(int e : G[u])
        {
            if((e^1) == path) continue;
            if(dep[to[e]] == 0x3f3f3f3f)
            {
                dep[to[e]] = dep[u]+1;
                que.push(make_pair(to[e], e));
            }else siz = min(siz, dep[u]+dep[to[e]]+1);
        }
        que.pop();
    }
}

int main()
{

    initPrime();
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        if(add(a[i]))
        {
            puts("1");
            return 0;
        }
    }
    siz = 0x3f3f3f3f;
    for(int i = 0; i <= qidian; ++i)
        bfs(i);
    if(siz == 0x3f3f3f3f) puts("-1");
    else printf("%d\n", siz);
    return 0;
}
