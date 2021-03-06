/*
	SOURCE===https://github.com/cacophonix/SPOJ/blob/master/MATCHING.cpp
	TIME COMPLEXITY IS   ((V^(0.5))*E)

	JUST PUSH PAIRINGS INTO G LIKE A BIDIRECTIONAL TREE EDGE AND CALL HOPCROFT_KARP FOR GETTING ANSWER
	Suppose n on left and m on right, then to add edge between x& y, add edge between x and (y+n)

*/
const int MAX=1e5,NIL=0,INF=1<<28;
vector< int > G[MAX];

int n, m, p, match[MAX], dist[MAX];

bool bfs() {
	int i, u, v, len;
	queue< int > Q;
	for(i=1; i<=n; i++) {
		if(match[i]==NIL) {
			dist[i] = 0;
			Q.push(i);
		}
		else dist[i] = INF;
	}
	dist[NIL] = INF;
	while(!Q.empty()) {
		u = Q.front(); Q.pop();
		if(u!=NIL) {
			len = G[u].size();
			for(i=0; i<len; i++) {
				v = G[u][i];
				if(dist[match[v]]==INF) {
					dist[match[v]] = dist[u] + 1;
					Q.push(match[v]);
				}
			}
		}
	}
	return (dist[NIL]!=INF);
}

bool dfs(int u) {
	int i, v, len;
	if(u!=NIL) {
		len = G[u].size();
		for(i=0; i<len; i++) {
			v = G[u][i];
			if(dist[match[v]]==dist[u]+1) {
				if(dfs(match[v])) {
					match[v] = u;
					match[u] = v;
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}

int hopcroft_karp() {
	int matching = 0, i;
	while(bfs())
		for(i=1; i<=n; i++)
			if(match[i]==NIL && dfs(i))
				matching++;
	return matching;
}


/*-------------------------------------------------------------
int main() {
	int i, u, v;
	cin>>n>>m>>p;

	for(i=0; i<p; i++) {
		cin>>u>>v;
		
		
		G[u].push_back(n+v);
		G[n+v].push_back(u);
	}
	int ans=hopcroft_karp();
	cout<<ans<<endl;
	return 0;
}
------------------------------------------------------------*/
